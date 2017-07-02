/* Michał Radecki mr371591 */
/* IPP - Pierwsze zadanie zaliczeniowe "Szpital" */

#define MaxSize 100001
char buffer[MaxSize];

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef struct type_of_disease
{
	char *description;
	int number_of_patients;
} type_of_disease;

typedef struct type_of_personal_disease_list
{
	type_of_disease *disease_specs;
	struct type_of_personal_disease_list *next_disease;
	struct type_of_personal_disease_list *last_disease;
} type_of_personal_disease_list;

typedef struct type_of_name_list
{
	struct type_of_name_list *next_name;
	type_of_personal_disease_list *personal_disease_list;
	int number_of_disease;
	char *name;
} type_of_name_list;

type_of_name_list *main_name_list;

void make_list()
{
	main_name_list = malloc(sizeof(type_of_name_list));
	main_name_list->next_name = NULL;
	main_name_list->name = NULL;
	main_name_list->personal_disease_list = NULL;
}

type_of_name_list* return_patient(char *name)
{
	type_of_name_list *name_list = main_name_list;
	if(name_list->next_name != NULL)
	{
		name_list = name_list->next_name;
		while( (strcmp(name_list->name, name) != 0) && name_list->next_name != NULL)
		{
			name_list = name_list->next_name;
		}
		if( (strcmp(name_list->name, name) != 0) && name_list->next_name == NULL)
		{
			type_of_name_list *new_patient = (type_of_name_list*)malloc(sizeof(type_of_name_list));
			new_patient->next_name = NULL;
			new_patient->number_of_disease = 0;
			new_patient->name = name;
			name_list->next_name = new_patient;
			type_of_personal_disease_list *new_personal_list = (type_of_personal_disease_list*)malloc(sizeof(type_of_personal_disease_list));
			new_patient->personal_disease_list = new_personal_list;
			new_personal_list->next_disease = NULL;
			new_personal_list->last_disease = NULL;
			name_list = name_list->next_name;
		}
		else free(name);
	}
	else
	{
		type_of_name_list *new_patient = (type_of_name_list*)malloc(sizeof(type_of_name_list));
		new_patient->next_name = NULL;
		new_patient->number_of_disease = 0;
		new_patient->name = name;
		name_list->next_name = new_patient;
		type_of_personal_disease_list *new_personal_list = (type_of_personal_disease_list*)malloc(sizeof(type_of_personal_disease_list));
		new_patient->personal_disease_list = new_personal_list;
		new_personal_list->next_disease = NULL;
		new_personal_list->last_disease = NULL;
		name_list = name_list->next_name;
	}
	return name_list;
}

type_of_name_list* return_patient_if_he_is_on_name_list(char *name)
{
	type_of_name_list *name_list = main_name_list;
	if(name_list->next_name == NULL) return NULL;
	else
	{
		name_list = name_list->next_name;
		while( (strcmp(name_list->name, name) != 0) && name_list->next_name != NULL)
		{
			name_list = name_list->next_name;
		}
		if( (strcmp(name_list->name, name) != 0) && name_list->next_name == NULL)
		{
			free(name);
			return NULL;
		}
		else
		{
			free(name);
			return name_list;
		}
	}
}

type_of_personal_disease_list* add_and_return_place_for_new_disease_in_personal_disease_list(type_of_name_list *patient)
{
	type_of_personal_disease_list *empty_place = (type_of_personal_disease_list*)malloc(sizeof(type_of_personal_disease_list));
	patient->number_of_disease += 1;
	if(patient->personal_disease_list->next_disease == NULL)
	{
		patient->personal_disease_list->next_disease = empty_place;
		patient->personal_disease_list->last_disease = empty_place;
	}
	else
	{
		patient->personal_disease_list->last_disease->next_disease = empty_place;
		patient->personal_disease_list->last_disease = empty_place;
	}
	empty_place->next_disease = NULL;
	return empty_place;
}

type_of_disease* return_disease()
{
	fgets(buffer, sizeof(buffer), stdin);
	int size = strlen(buffer);
	char* disease = (char*)malloc(sizeof(char) * (size + 1));
	strncpy(disease, buffer, size + 1);

	type_of_disease *new_disease = (type_of_disease*)malloc(sizeof(type_of_disease));
	new_disease->number_of_patients = 0;
	new_disease->description = disease;
	return new_disease;
}

void connect_place_with_disease(type_of_personal_disease_list *new_place, type_of_disease *disease)
{
	new_place->disease_specs = disease;
	disease->number_of_patients += 1;
}

void delete_patient_data(type_of_name_list *name, int *amount_of_disease)
{
	name->number_of_disease = 0;
	type_of_personal_disease_list *disease = name->personal_disease_list->next_disease;
	while(disease != NULL)
	{
		type_of_personal_disease_list *next_disease = disease->next_disease;
		disease->disease_specs->number_of_patients -= 1;
		if(disease->disease_specs->number_of_patients == 0)
		{
			free(disease->disease_specs->description);
			free(disease->disease_specs);
			(*amount_of_disease) -= 1;
		}
		free(disease);
		disease = next_disease;
	}
	name->personal_disease_list->next_disease = NULL;
	name->personal_disease_list->last_disease = NULL;
}

void release_memory(int *amount_of_disease)
{
	type_of_name_list *name = main_name_list;
	type_of_name_list *next_name = name->next_name;
	free(name);
	while(next_name != NULL)
	{
		type_of_name_list *name = next_name;
		next_name = next_name->next_name;
		delete_patient_data(name, amount_of_disease);
		free(name->personal_disease_list);
		free(name->name);
		free(name);
	}
}

void new_disease_enter_description(char *name, int *amount_of_disease_description)
{
	type_of_name_list *patient = return_patient(name);
	type_of_personal_disease_list *new_place = add_and_return_place_for_new_disease_in_personal_disease_list(patient);
	type_of_disease *disease = return_disease();
	connect_place_with_disease(new_place, disease);
	(*amount_of_disease_description) += 1;
	printf("OK\n");
}

void new_disease_copy_description(char *name, char *name2)
{
	type_of_name_list *patient2 = return_patient_if_he_is_on_name_list(name2);
	if(patient2 == NULL)
	{
		free(name);
		printf("IGNORED\n");
	}
	else if(patient2->number_of_disease == 0)
	{
		free(name);
		printf("IGNORED\n");
	}
	else
	{
		type_of_name_list *patient1 = return_patient(name);
		type_of_personal_disease_list *disease = add_and_return_place_for_new_disease_in_personal_disease_list(patient1);
		disease->disease_specs = patient2->personal_disease_list->last_disease->disease_specs;
		disease->disease_specs->number_of_patients += 1;
		printf("OK\n");
	}
}

void change_description(char *name, int number, int *amount_of_disease_description)
{
	type_of_name_list *patient = return_patient_if_he_is_on_name_list(name);

	if(patient == NULL)
	{
		fgets(buffer, sizeof(buffer), stdin);
		printf("IGNORED\n");
	}
	else if(patient->number_of_disease < number)
	{
		fgets(buffer, sizeof(buffer), stdin);
		printf("IGNORED\n");
	}
	else
	{
		type_of_personal_disease_list *new_place = patient->personal_disease_list->next_disease;
		number--;
		while(number > 0)
		{
			new_place = new_place->next_disease;
			number--;
		}
		new_place->disease_specs->number_of_patients -= 1;
		if(new_place->disease_specs->number_of_patients == 0)
		{
			free(new_place->disease_specs->description);
			free(new_place->disease_specs);
			(*amount_of_disease_description) -= 1;
		}
		type_of_disease *disease = return_disease();
		connect_place_with_disease(new_place, disease);
		(*amount_of_disease_description) += 1;
		printf("OK\n");
	}
}

void print_description(char *name, int number)
{
	type_of_name_list *patient = return_patient_if_he_is_on_name_list(name);

	if(patient == NULL)
	{
		printf("IGNORED\n");
	}
	else if(number < 0 || patient->number_of_disease < number)
	{
		printf("IGNORED\n");
	}
	else
	{
		type_of_personal_disease_list *new_place = patient->personal_disease_list->next_disease;
		number--;
		while(number > 0)
		{
			new_place = new_place->next_disease;
			number--;
		}
		printf("%s", new_place->disease_specs->description);
	}
}

void find_and_delete_patient_data(char *name, int *amount_of_disease_description)
{
	type_of_name_list *patient = return_patient_if_he_is_on_name_list(name);

	if(patient == NULL)
	{
		printf("IGNORED\n");
	}
	else
	{
		delete_patient_data(patient, amount_of_disease_description);
		printf("OK\n");
	}
}
