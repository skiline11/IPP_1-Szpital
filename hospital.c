/* Michał Radecki mr371591 */
/* IPP - Pierwsze zadanie zaliczeniowe "Szpital" */

#define MaxSize 100
char main_buffer[MaxSize];

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#include"parse.h"
#include"structure.h"
int main(int argc, char *argv[])
{
	int mode = 0;
	if(argc == 2)
	{
		if(strcmp(argv[1], "-v") == 0)
		{
			mode = 1;
		}
	}
	else mode = 0;
	make_list();
	int amount_of_disease_description = 0;
	char *name, *name2;
	while(scanf("%s", main_buffer) != EOF)
	{
		int command_type = return_command_type(main_buffer);
		switch(command_type)
		{
			case 1:
			{
				get_empty_char();
				int size = read_to_buffer();
				get_empty_char();
				name = malloc(sizeof(char) * (size + 1));
				copy_from_buffer_to_name(name, size);
				new_disease_enter_description(name, &amount_of_disease_description);
				break;
			}
			case 2:
			{
				get_empty_char();
				int size = read_to_buffer();
				get_empty_char();
				name = malloc(sizeof(char) * (size + 1));
				copy_from_buffer_to_name(name, size);

				size = read_to_buffer();
				name2 = malloc(sizeof(char) * (size + 1));
				copy_from_buffer_to_name(name2, size);
				new_disease_copy_description(name, name2);
				break;
			}
			case 3:
			{
				get_empty_char();
				int size = read_to_buffer();
				get_empty_char();
				name = malloc(sizeof(char) * (size + 1));
				copy_from_buffer_to_name(name, size);

				int number = read_number();
				get_empty_char();
				change_description(name, number, &amount_of_disease_description);
				break;
			}
			case 4:
			{
				get_empty_char();
				int size = read_to_buffer();
				get_empty_char();
				name = malloc(sizeof(char) * (size + 1));
				copy_from_buffer_to_name(name, size);

				int number = read_number();
				print_description(name, number);
				break;
			}
			case 5:
			{
				get_empty_char();
				int size = read_to_buffer();
				get_empty_char();
				name = malloc(sizeof(char) * (size + 1));
				copy_from_buffer_to_name(name, size);
				find_and_delete_patient_data(name, &amount_of_disease_description);
				break;
			}
			default:
			{
				printf("IGNORED\n");
				default_read();
				break;
			}
		}
		if(mode == 1) fprintf(stderr, "DESCRIPTIONS: %d\n", amount_of_disease_description);
	}
	release_memory(&amount_of_disease_description);
	return 0;
}
