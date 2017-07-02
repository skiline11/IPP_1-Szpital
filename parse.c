/* Michał Radecki mr371591 */
/* IPP - Pierwsze zadanie zaliczeniowe "Szpital" */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MaxSize 100001
char buffer[MaxSize];

void get_empty_char()
{
    getchar();
}

int read_number()
{
   int number;
   scanf("%d", &number);
   return number;
}

int read_to_buffer()
{
    scanf("%s", buffer);
    return strlen(buffer);
}

void copy_from_buffer_to_name(char *name, int size)
{
	strncpy(name, buffer, size + 1);
}

void default_read()
{
	fgets(buffer, sizeof(buffer), stdin);
}


int return_command_type(char *main_buffer)
{
	int command = -1;
	if(strcmp(main_buffer, "NEW_DISEASE_ENTER_DESCRIPTION") == 0) command = 1;
	else if(strcmp(main_buffer, "NEW_DISEASE_COPY_DESCRIPTION") == 0) command = 2;
	else if(strcmp(main_buffer, "CHANGE_DESCRIPTION") == 0) command = 3;
	else if(strcmp(main_buffer, "PRINT_DESCRIPTION") == 0) command = 4;
	else if(strcmp(main_buffer, "DELETE_PATIENT_DATA") == 0) command = 5;
	return command;
}
