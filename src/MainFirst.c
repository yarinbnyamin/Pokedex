/*
 * MainFirst.c
 *
 *  Created on: Nov 19, 2021
 *      Author: yarin bnyamin 208896548
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Defs.h"


int index_in_types(Type** types, int size, char* search){
	/* this function return the index of the string search in the list types
	  	  if not found return -1 */

	int i;
	for(i=0; i< size; i++){
		if(strcmp(types[i]->name, search) == 0)
			return i;
	}

	return -1;  // not found
}

status print_all_pokes(Pokemon** pokes, int num_pokes){
	/* this function print all the Pokemons in the list */

	if(pokes == NULL)
		return failure;

	status done;

	int i;
	for(i=0; i<num_pokes; i++){
		done = print_pokemon(pokes[i]);
		if(done == err)
			return err;
	}

	return success;
}

status print_all_types(Type** types, int num_types){
	/* this function print all the Types in the list */

	if(types == NULL)
		return failure;

	status done;

	int i;
	for(i=0; i<num_types; i++){
		done = print_type(types[i]);
		if(done == err)
			return err;
	}

	return success;
}

status add_stronger_against_me(Type** types, int num_types){
	/* this function add type to effective against me list */

	if(types == NULL)
		return failure;

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter type name:\n");
	scanf("%s", name );
	int pos1 = index_in_types(types, num_types, name);
	if(pos1 == -1){
		printf("Type name doesn't exist.\n");
		free(name);
		return failure;
	}

	printf("Please enter type name to add to %s effective against me list:\n", name);
	scanf("%s", name );
	int pos2 = index_in_types(types, num_types, name);
	free(name);
	if(pos2 == -1){
		printf("Type name doesn't exist.\n");
		return failure;
	}

	status done = add_stronger_vs_me(types[pos1], types[pos2]);
	if(done == failure){
		printf("This type already exist in the list.\n");
		return failure;
	}

	 if(done == err)
		 return err;

	print_type(types[pos1]);
	return success;
}

status add_weeker_against_me(Type** types, int num_types){
	/* this function add type to effective against others list */

	if(types == NULL)
		return failure;

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter type name:\n");
	scanf("%s", name );
	int pos1 = index_in_types(types, num_types, name);
	if(pos1 == -1){
		printf("Type name doesn't exist.\n");
		free(name);
		return failure;
	}

	printf("Please enter type name to add to %s effective against others list:\n", name);
	scanf("%s", name );
	int pos2 = index_in_types(types, num_types, name);
	free(name);
	if(pos2 == -1){
		printf("Type name doesn't exist.\n");
		return failure;
	}

	status done = add_weeker_vs_me(types[pos1], types[pos2]);
	if(done == failure){
		printf("This type already exist in the list.\n");
		return failure;
	}

	if(done == err)
		return err;

	done = print_type(types[pos1]);
	return done;
}

status del_stronger_against_me(Type** types, int num_types){
	/* this function remove type from effective against me list */

	if(types == NULL)
		return failure;

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter type name:\n");
	scanf("%s", name );
	int pos1 = index_in_types(types, num_types, name);
	if(pos1 == -1){
		printf("Type name doesn't exist.\n");
		free(name);
		return failure;
	}

	printf("Please enter type name to remove from %s effective against me list:\n", name);
	scanf("%s", name );
	int pos2 = index_in_types(types, num_types, name);
	free(name);
	if(pos2 == -1){
		printf("Type name doesn't exist in the list.\n");
		return failure;
	}

	status done = del_stronger_vs_me(types[pos1], types[pos2]);
	if(done == failure){
		printf("Type name doesn't exist in the list.\n");
		return failure;
	}

	if(done == err)
		return err;


	done = print_type(types[pos1]);
	return done;

}

status del_weeker_against_me(Type** types, int num_types){
	/* this function remove type from effective against others list */

	if(types == NULL)
		return failure;

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter type name:\n");
	scanf("%s", name );
	int pos1 = index_in_types(types, num_types, name);
	if(pos1 == -1){
		printf("Type name doesn't exist.\n");
		free(name);
		return failure;
	}

	printf("Please enter type name to remove from %s effective against others list:\n", name);
	scanf("%s", name );
	int pos2 = index_in_types(types, num_types, name);
	free(name);
	if(pos2 == -1){
		printf("Type name doesn't exist in the list.\n");
		return failure;
	}

	status done = del_weeker_vs_me(types[pos1], types[pos2]);

	if(done == failure){
		printf("Type name doesn't exist in the list.\n");
		return failure;
	}

	if(done == err)
		return err;


	print_type(types[pos1]);
	return success;
}

status print_by_name(Pokemon** pokes, int num_pokes){
	/* this function print Pokemon by given name */

	if(pokes == NULL)
		return failure;

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter Pokemon name:\n");
	scanf("%s", name );

	int i;
	for(i=0; i < num_pokes; i++)
		if(strcmp(pokes[i]->name, name) == 0){
			status done = print_pokemon(pokes[i]);
			free(name);
			return done;
		}

	printf("The Pokemon doesn't exist.\n");
	free(name);
	return failure;
}

status print_by_type(Pokemon** pokes, int num_pokes, Type** types, int num_types){
	/* this function all the Pokemons of given type */

	if(pokes == NULL)
		return failure;

	char* name = (char*)malloc(300 * sizeof(char));
	if(name == NULL)
		return err;

	printf("Please enter type name:\n");
	scanf("%s", name );
	int pos = index_in_types(types, num_types, name);
	if(pos == -1){
		printf("Type name doesn't exist.\n");
		free(name);
		return failure;
	}

	if(types[pos]->counter == 0){
		printf("There are no Pokemons with this type.\n");
		free(name);
		return success;
	}


	status done;

	printf("There are %d Pokemons with this type:\n", types[pos]->counter);
	int i;
	for(i=0; i < num_pokes; i++)
		if(strcmp(pokes[i]->type->name, name) == 0){
			done = print_pokemon(pokes[i]);
			if(done == err){
				free(name);
				return err;
			}
		}

	free(name);
	return success;

}

status armageddon(Pokemon** pokes, int num_pokes, Type** types, int num_types){
	/* this function free all the allocated memory */

	int i;
	if(pokes != NULL){
	for(i=0; i<num_pokes; i++)
			kill_pokemon(pokes[i]);
		free(pokes);
	}

	if(types != NULL){
		for(i=0; i<num_types; i++)
			extinct_type(types[i]);
		free(types);
	}

	return success;
}


int main(int argc,char*argv[]){

	if(argv == NULL){
		printf("Didn't got args");
		return -1;
	}

	int num_types = atoi(argv[1]);
	int num_pokes = atoi(argv[2]);
	FILE *fp = fopen(argv[3],"r");

	if(fp == NULL){
		printf("Memory Problem");
		return -1;
	}

	//check if need
	int i, pos1, pos2;
	char* line = (char*)malloc(300*sizeof(char));
	char* word= NULL;

	char* name = (char*)malloc(300 * sizeof(char));
	char* species = (char*)malloc(300 * sizeof(char));

	if(line == NULL || name == NULL || species == NULL){
		free(line);
		free(name);
		free(species);

		printf("Memory Problem");
		return -1;
	}

	double h, w;
	int att;

	Type** types = (Type**)malloc(num_types*sizeof(Type*));
	Pokemon** pokes = (Pokemon**)malloc(num_pokes*sizeof(Pokemon*));

	if(types == NULL || pokes == NULL){
		free(line);
		free(name);
		free(species);

		free(types);
		free(pokes);

		printf("Memory Problem");
		return -1;
	}

	// extract data from file
	fgets(line, 300,fp);
	if(strcmp(line,"Types\r\n") == 0){  // types to array
		fgets(line, 300,fp);
		line[strlen(line)-2] = '\0';  // remove last \r\n
		word = strtok(line, ",");
		for(i=0; i< num_types; i++){
			types[i] = create_type(word);
			word = strtok(NULL, ",");
		}
		fgets(line, 300,fp);

		while(strcmp(line,"Pokemons\r\n") != 0){

			for(i=0; i< strlen(line); i++)
				if(line[i] == '\t' || line[i] == '-' || line[i] == ':' || line[i] == ',' || line[i] == '\n' || line[i] == '\r')
					line[i] = ' ';

			word = strtok(line, " ");
			pos1 = index_in_types(types, num_types, word);
			word = strtok(NULL, " ");  // drop effective
			word = strtok(NULL, " ");  // drop against
			word = strtok(NULL, " ");
			if(strcmp(word,"me") == 0){  // effective against me
				word = strtok(NULL, " ");
				while(word != NULL)
				{
					pos2 = index_in_types(types, num_types, word);
					add_stronger_vs_me(types[pos1], types[pos2]);
					word = strtok(NULL, " ");
				}
			}else{  // effective against other
				word = strtok(NULL, " ");
				while(word != NULL)
				{
					pos2 = index_in_types(types, num_types, word);
					add_weeker_vs_me(types[pos1], types[pos2]);
					word = strtok(NULL, " ");
				}
			}

			fgets(line, 300,fp);
		}

	}


	if(strcmp(line,"Pokemons\r\n") == 0){ // pokemons to array
		for(i=0; i< num_pokes; i++){
			fgets(line, 300,fp);

			if(i < num_pokes-1)
				line[strlen(line)-2] = '\0';  // remove last \r\n

			word = strtok(line, ",");  // pokemon name
			strcpy(name, word);
			word = strtok(NULL, ",");  // pokemon species
			strcpy(species, word);
			word = strtok(NULL, ",");  // pokemon height
			h = atof(word);
			word = strtok(NULL, ",");  // pokemon weight
			w = atof(word);
			word = strtok(NULL, ",");  // pokemon attack
			att = atoi(word);
			word = strtok(NULL, ",");  // pokemon type
			pos1 = index_in_types(types, num_types, word);

			pokes[i] = create_pokemon(name, species, types[pos1], h, w, att);

		}
	}

	fclose(fp);
	free(name);
	free(species);
	free(line);

	status done = failure;  // check if we got error (err)

	char choice = '0';

	while(choice != '9')
	{
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons\n");
	    printf("2 : Print all Pokemons types\n");
		printf("3 : Add type to effective against me list\n");
		printf("4 : Add type to effective against others list\n");
		printf("5 : Remove type from effective against me list\n");
		printf("6 : Remove type from effective against others list\n");
		printf("7 : Print Pokemon by name\n");
		printf("8 : Print Pokemons by type\n");
		printf("9 : Exit\n");

		scanf(" %c", &choice);

		switch( choice )
		{
			case '1':  // Print all Pokemons
				done = print_all_pokes(pokes, num_pokes);
				break;
			case '2':  // Print all Pokemons types
				done = print_all_types(types, num_types);
				break;
			case '3':  // Add type to effective against me list
				done = add_stronger_against_me(types, num_types);
				break;
			case '4':  // Add type to effective against others list
				done = add_weeker_against_me(types, num_types);
				break;
			case '5':  // Remove type from effective against me list
				done = del_stronger_against_me(types, num_types);
				break;
			case '6':  // Remove type from effective against others list
				done = del_weeker_against_me(types, num_types);
				break;
			case '7':  // Print Pokemon by name
				done = print_by_name(pokes, num_pokes);
				break;
			case '8':  // Print Pokemons by type
				done = print_by_type(pokes, num_pokes, types, num_types);
				break;
			case '9':  // Exit
				done = armageddon(pokes, num_pokes, types, num_types);  // free memory
				printf("All the memory cleaned and the program is safely closed.\n");
				break;
			default:  // Not a valid option
				printf("Please choose a valid number.\n");
				break;
		}

		if(done == err){
			armageddon(pokes, num_pokes, types, num_types);  // free memory
			printf("Memory Problem\n");
			return -1;
		}

	}
	return 0;

}
