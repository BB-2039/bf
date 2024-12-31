/* The main file for the brainf*ck interpreter
   Copyright (C) 2025 Mitchell <mitchell@segfault.net>

This file is part of BF.

BF is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

BF is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with BF; see the file LICENSE.  If not see
<http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.1"
#define TAPESIZE 30000
#define MAXLINE 30000

int __brackets[MAXLINE];
int __tape[TAPESIZE];
int __src_ptr = 0;

void print_help();
void reset();
void validate(char src[]);
void eval(char src[], int length);
void bf2c(char input_filename[], char output_filename[]);

int main(int argc, char *argv[])
{
    int opt;
    if (argc == 1)
    {
	reset();
	char src[MAXLINE], line[MAXLINE];
        while (fgets(line, MAXLINE,stdin))
	{
	    strcat(src, line);
	}
	int length = sizeof(src) / sizeof(char);
	validate(src);
	eval(src, length);
    }
    
    static struct option long_options[] =
	{
	    { "help", no_argument, NULL, 'h'},
	    { "file", optional_argument, NULL, 'f'},
	    { "convert", optional_argument, NULL, 'c'},
	    { 0, 0, 0, 0 }
	};

    while ((opt = getopt_long(argc, argv, "hfc", long_options, NULL)) != -1)
    {
	switch (opt)
	{
	case 'h':
	    print_help();
	    exit(EXIT_SUCCESS);
	case 'f':
	    reset();
	    if (optind + 1 == argc)
	    {
		FILE *file = fopen(argv[optind], "r");
		assert(file != NULL);
		char src[MAXLINE];
		size_t len = fread(src, sizeof(char), MAXLINE-1, file);
	        if (len == 0 && ferror(file))
		{
		    fprintf(stderr, "Error reading file\n");
		    fclose(file);
		    exit(EXIT_FAILURE);
		}
		src[len] = '\0';
		fclose(file);
		validate(src);
		eval(src, len);
		exit(EXIT_SUCCESS);
	    }
	    else
	    {
		fprintf(stderr, "Error: Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	    }
	    break;
	case 'c':
	    if (optind + 2 == argc)
	    {
		bf2c(argv[optind], argv[optind+1]);
	    }
	    else
	    {
		fprintf(stderr, "Error: Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	    }
	    break;
	case '?':
	    print_help();
	    exit(EXIT_FAILURE);
	}
    }

    return 0;
}

void print_help()
{
    printf("\nMiniBf %s\n", VERSION);
    printf("A simple Brainfuck interpreter\n");
    printf("\nUsage:\n");
    printf("  bf                      Run the interpreter interactively.\n");
    printf("  bf -h                   Display this help message.\n");
    printf("  bf -f <filename>        Execute Brainfuck code from a file.\n");
    printf("  bf -c <filename>        Convert Brainfuck code to C code.\n");
}

void reset()
{
    for (int i = 0; i < TAPESIZE; i++)
    {
	__tape[i] = 0;
    }

    for (int i = 0; i < MAXLINE; i++)
    {
	__brackets[i] = 0;
    }
    __src_ptr = 0;
}

void validate(char src[])
{
    int stack[MAXLINE];
    int top = -1;
    
    memset(__brackets, -1, sizeof(__brackets));
    
    for (int i = 0; src[i] != '\0'; i++)
    {
	if (src[i] == '[')
	{
	    stack[++top] = i;
	}
	else if (src[i] == ']')
	{
	    if (top < 0)
	    {
		fprintf(stderr, "Error: unmatched ']' at position %d\n", i);
		exit(EXIT_FAILURE);
	    }
	    int pos = stack[top--];
	    __brackets[pos] = i;
	    __brackets[i] = pos;
	}
    }

    if (top >= 0)
    {
	fprintf(stderr, "Error: unmatched '[' at position %d\n", stack[top]);
	exit(EXIT_FAILURE);
    }
}

void eval(char src[], int length)
{
    for (int i = 0; src[i] != '\0' && i < length; i++)
    {
	switch (src[i])
	{
	case '+':
	    __tape[__src_ptr] = (__tape[__src_ptr] == 255)
		                   ? 0
		                   : __tape[__src_ptr] + 1;
	    break;
	case '-':
	    __tape[__src_ptr] = (__tape[__src_ptr] == 0)
		                   ? 255
		                   : __tape[__src_ptr] - 1;
	    break;
	case '>':
	    assert(__src_ptr < TAPESIZE - 1);
	    __src_ptr++;
	    break;
	case '<':
	    assert(__src_ptr > 0);
	    __src_ptr--;
	    break;
	case ',':
	{
	    int c = getchar();
	    if (c != EOF)
	    {
		__tape[__src_ptr] = c;
	    }
	    break;
	}
	case '.':
	    putchar(__tape[__src_ptr]);
	    break;
	case '[':
	    if (__tape[__src_ptr] == 0)
	    {
		i = __brackets[i];
	    }
	    break;
	case ']':
	    if (__tape[__src_ptr] != 0)
	    {
		i = __brackets[i];
	    }
	    break;
	default:
	    break;
	}
    }
}

void bf2c(char *input_filename, char *output_filename)
{
  FILE *in = fopen(input_filename, "r");
  assert(in != NULL);

  FILE *out = fopen(output_filename, "w");
  assert(out != NULL);

  int c;
  int cellsize = TAPESIZE;

  fprintf(out,
          "#include <stdio.h>\n"
          "#include <stdlib.h>\n\n"
          "int main(int argc, char **argv)\n{\n"
          "\tunsigned char *cell = calloc(%d, 1);\n"
          "\tunsigned char *cells = cell;\n"
          "\tif (!cell) {\n"
          "\t\tfprintf(stderr, \"Error allocating memory.\\n\");\n"
          "\t\treturn 1;\n"
          "\t}\n\n", cellsize
          );
  
  while ((c = getc(in)) != EOF)
  {
    switch (c)
    {
    case '>': fprintf(out, "\t\t++cell;\n"); break;
    case '<': fprintf(out, "\t\t--cell;\n"); break;
    case '+': fprintf(out, "\t\t++*cell;\n"); break;
    case '-': fprintf(out, "\t\t--*cell;\n"); break;
    case '.': fprintf(out, "\t\tputchar(*cell);\n"); break;
    case ',': fprintf(out, "\t\t*cell = getchar();\n"); break;
    case '[': fprintf(out, "\twhile (*cell) {\n"); break;
    case ']': fprintf(out, "\t}\n"); break;
    default: break;
    }
  }
	
  fprintf(out, "\n\tfree(cells);\n\treturn 0;\n}\n\n");
  fclose(in);
  fclose(out);
  printf("Brainfuck code converted to C code in %s\n", output_filename);
}
