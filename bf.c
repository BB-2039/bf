#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.1"
#define TAPESIZE 30000
#define MAXLINE 30000

int __tape[TAPESIZE];
int __src_ptr = 0;

void print_help();
void reset();
void eval(char src[]);
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
	eval(src);
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
	    // printf("option F hit!\n");
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
		eval(src);
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
    __src_ptr = 0;
}

void eval(char src[])
{
    for (int i = 0; src[i] != '\0' && (unsigned long)i < strlen(src); i++)
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
	    __tape[__src_ptr] = getchar();
	    break;
	case '.':
	    putchar(__tape[__src_ptr]);
	    break;
	case '[':
	    if (__tape[__src_ptr] == 0)
	    {
		int bracket = 1;
		while (bracket > 0)
		{
		    // assert((i > 0)&&(i < MAXLINE));
		    i++;
		    if (src[i] == '[') bracket++;
		    if (src[i] == ']') bracket--;
		}
	    }
	    break;
	case ']':
	    if (__tape[__src_ptr] != 0)
	    {
		int bracket = 1;
		while (bracket > 0)
		{
		    // assert((i > 0)&&(i < MAXLINE));
		    i--;
		    if (src[i] == ']') bracket++;
		    if (src[i] == '[') bracket--;
		}
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
