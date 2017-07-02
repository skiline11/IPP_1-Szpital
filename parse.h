/* Michał Radecki mr371591 */
/* IPP - Pierwsze zadanie zaliczeniowe "Szpital" */

#ifndef PARSE_H
#define PARSE_H

void get_empty_char();
int read_number();
int read_to_buffer();
void copy_from_buffer_to_name(char *name, int size);
void default_read();
int return_command_type();

#endif
