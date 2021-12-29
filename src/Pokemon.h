/*
 * Pokemon.h
 *
 *  Created on: Nov 19, 2021
 *      Author: yarin bnyamin 208896548
 */

#ifndef POKEMON_H_
#define POKEMON_H_
#include "Defs.h"


typedef struct type_st {
    char*  name;
    int counter;
    int stronger_vs_me;
    struct type_st **effective_against_me;
    int weeker_vs_me;
    struct type_st **effective_against_other;
}Type;

Type* create_type(char* name);
// add type other to the effective_against_me list of me
status add_stronger_vs_me(Type* me, Type* other);
// add type other to the effective_against_other list of me
status add_weeker_vs_me(Type* me, Type* other);
// delete type other to the effective_against_me list of me
status del_stronger_vs_me(Type* me, Type* other);
// delete type other to the effective_against_other list of me
status del_weeker_vs_me(Type* me, Type* other);
// print type
status print_type(Type* type);
// free memory of type
void extinct_type(Type* type);


typedef struct bio_info_st {
    double  height;
    double weight;
    int attack;
}Bio_Info;

Bio_Info* create_bio(double h, double w, int att);
// print bio info
status print_bio(Bio_Info* bio);
// free memory of bio info
void del_bio(Bio_Info* bio);


typedef struct pokemon_st {
    char*  name;
    char*  species;
    Type* type;
    Bio_Info* bio;
}Pokemon;

Pokemon* create_pokemon(char* name, char* species, Type* type, double h, double w, int att);
// print pokemon
status print_pokemon(Pokemon* poke);
// free memory of pokemon
void kill_pokemon(Pokemon* poke);


#endif /* POKEMON_H_ */
