/* Michał Radecki mr371591 */
/* IPP - Pierwsze zadanie zaliczeniowe "Szpital" */

#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct {} type_of_disease;
typedef struct {} type_of_personal_disease_list;
typedef struct {} type_of_name_list;

void make_list();
type_of_name_list* return_patient(char *name);
type_of_name_list* return_patient_if_he_is_on_name_list(char *name);
type_of_personal_disease_list* add_and_return_place_for_new_disease_in_personal_disease_list(type_of_name_list *patient);
type_of_disease* return_disease();
void connect_place_with_disease(type_of_personal_disease_list *new_place, type_of_disease *disease);
void delete_patient_data(type_of_name_list *name, int *amount_of_disease);
void release_memory(int *amount_of_disease);
void new_disease_enter_description(char *name, int *amount_of_disease_description);
void new_disease_copy_description(char *name, char *name2);
void change_description(char *name, int number, int *amount_of_disease_description);
void print_description(char *name, int number);
void find_and_delete_patient_data(char *name, int *amount_of_disease_description);

#endif
