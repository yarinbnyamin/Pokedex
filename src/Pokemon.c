/*
 * Pokemon.c
 *
 *  Created on: Nov 19, 2021
 *      Author: yarin bnyamin 208896548
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Pokemon.h"
#include "Defs.h"


Pokemon* create_pokemon(char* name, char* species, Type* type, double h, double w, int att){

	if(name == NULL || species == NULL || type == NULL || h <= 0 || w <= 0)
		return NULL;

	Pokemon* poke = (Pokemon*)malloc(sizeof(Pokemon));
	if(poke == NULL)
		return NULL;

	poke->bio = create_bio(h, w, att);
	if(poke->bio == NULL){
		free(poke);
		return NULL;
	}

	poke->name = (char*)malloc((strlen(name)+1) * sizeof(char));
	if(poke->name == NULL){
		free(poke->bio);
		free(poke);
		return NULL;
	}
	strcpy(poke->name, name);
	poke->species = (char*)malloc((strlen(species)+1) * sizeof(char));
	if(poke->species == NULL){
		free(poke->name);
		free(poke->bio);
		free(poke);
		return NULL;
	}
	strcpy(poke->species, species);
	poke->type = type;
	type->counter++;

	return poke;
}


Bio_Info* create_bio(double h, double w, int att){

	Bio_Info* bio = (Bio_Info*)malloc(sizeof(Bio_Info));
	if(bio == NULL)
		return NULL;

	bio->height = h;
	bio->weight = w;
	bio->attack = att;
	return bio;
}


Type* create_type(char* name){

	Type* type = (Type*)malloc(sizeof(Type));
	if(type == NULL)
		return NULL;

	type->name = (char*)malloc((strlen(name)+1) * sizeof(char));
	if(type->name == NULL){
		free(type);
		return NULL;
	}
	strcpy(type->name, name);
	type->counter = 0;
	type->stronger_vs_me = 0;
	type->effective_against_me = NULL;
	type->weeker_vs_me = 0;
	type->effective_against_other = NULL;

	return type;
}


status print_pokemon(Pokemon* poke){

	if(poke == NULL)
		return failure;

	printf("%s :\n",poke->name);
	printf("%s, %s Type.\n", poke->species, poke->type->name);
	print_bio(poke->bio);
	printf("\n");
	return success;
}


status print_bio(Bio_Info* bio){

	if(bio == NULL)
		return failure;

	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n", bio->height, bio->weight, bio->attack);
	return success;
}


status print_type(Type* type){

	if(type == NULL)
		return failure;

	printf("Type %s -- %d pokemons\n", type->name, type->counter);

	int i;

	if(type->stronger_vs_me > 0){
		printf("\tThese types are super-effective against %s:", type->name);
		for(i=0; i < type->stronger_vs_me-1; i++)
			printf("%s ,", type->effective_against_me[i]->name);
		printf("%s\n", type->effective_against_me[i]->name);
	}

	if(type->weeker_vs_me > 0){
		printf("\t%s moves are super-effective against:", type->name);
		for(i=0; i < type->weeker_vs_me-1; i++)
			printf("%s ,", type->effective_against_other[i]->name);
		printf("%s\n", type->effective_against_other[i]->name);
	}


	printf("\n");
	return success;
}


status add_stronger_vs_me(Type* me, Type* other){
	// add type other to the effective_against_me list of me

	if(me == NULL || other == NULL)
		return failure;

	// check if already exist in the list
	int i;
	for(i=0; i < me->stronger_vs_me ; i++)
		if(me->effective_against_me[i] == other)
			return failure;

	me->stronger_vs_me++;
	if(me->effective_against_me != NULL)
		me->effective_against_me = (Type**)realloc(me->effective_against_me, me->stronger_vs_me*sizeof(Type*));
	else
		me->effective_against_me = (Type**)malloc(sizeof(Type*));


	if(me->effective_against_me == NULL)
		return err;

	me->effective_against_me[me->stronger_vs_me-1] = other;
	return success;
}


status add_weeker_vs_me(Type* me, Type* other){
	// add type other to the effective_against_other list of me

	if(me == NULL || other == NULL)
		return failure;

	// check if already exist in the list
	int i;
	for(i=0; i < me->weeker_vs_me ; i++)
		if(me->effective_against_other[i] == other)
			return failure;

	me->weeker_vs_me++;
	if(me->effective_against_other != NULL)
		me->effective_against_other = (Type**)realloc(me->effective_against_other, me->weeker_vs_me*sizeof(Type*));
	else
		me->effective_against_other = (Type**)malloc(sizeof(Type*));


	if(me->effective_against_other == NULL)
		return err;

	me->effective_against_other[me->weeker_vs_me-1] = other;
	return success;
}


status del_stronger_vs_me(Type* me, Type* other){
	// delete type other to the effective_against_me list of me

	if(me == NULL || other == NULL)
		return failure;

	int i;
	for(i=0; i < me->stronger_vs_me ; i++){
		if(me->effective_against_me[i] == other){

			me->stronger_vs_me--;

			for(;i < me->stronger_vs_me ; i++)
				me->effective_against_me[i] = me->effective_against_me[i+1];

			me->effective_against_me = (Type**)realloc(me->effective_against_me, me->stronger_vs_me*sizeof(Type*));

			if(me->stronger_vs_me != 0 && me->effective_against_me == NULL)
				return err;

			return success;
		}
	}

	return failure;
}


status del_weeker_vs_me(Type* me, Type* other){
	// delete type other to the effective_against_other list of me

	if(me == NULL || other == NULL)
		return failure;

	int i;
	for(i=0; i < me->weeker_vs_me ; i++){
		if(me->effective_against_other[i] == other){

			me->weeker_vs_me--;

			for(;i < me->weeker_vs_me ; i++)
				me->effective_against_other[i] = me->effective_against_other[i+1];

			me->effective_against_other = (Type**)realloc(me->effective_against_other, me->weeker_vs_me*sizeof(Type*));

			if(me->weeker_vs_me != 0 && me->effective_against_other == NULL)
				return err;

			return success;
		}
	}

	return failure;
}


void kill_pokemon(Pokemon* poke){
	// free memory of pokemon

	if(poke == NULL)
		return;

	free(poke->name);
	free(poke->species);
	del_bio(poke->bio);
	free(poke);
}


void del_bio(Bio_Info* bio){
	// free memory of bio info

	if(bio == NULL)
		return;

	free(bio);
}


void extinct_type(Type* type){
	// free memory of type

	if(type == NULL)
		return;

    free(type->name);
    free(type->effective_against_me);
    free(type->effective_against_other);
    free(type);
}

