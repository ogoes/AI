#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "knn.h"


int LINE_SIZE = 0;

double * parse_line (char * line) {

  double * values = (double *) calloc(VALUES_NUMBER + 1, sizeof (double));

  char * value_parsed;

  value_parsed = strtok(line, " ");
  int value_index = 0;
  while (value_parsed != NULL) {
    values[value_index++] = atof(value_parsed);
    value_parsed = strtok(NULL, " ");
  }

  for (int i = 0; i < value_index; ++i) {
    printf("%lf ", values[i]);
  }

  return values;

}

void get_line_size (const char filename[]) {
  FILE * file = fopen(filename, "r");

  int counter = 0;
  int charc = fgetc(file);
  while (charc != '\n') {
    ++counter;
    charc = fgetc(file);
  }

  LINE_SIZE = ++counter;

  fclose(file);
}




int main (int argc, char ** argv) {

  FILE * file;

  if (argc == 3) {;
    file = fopen(argv[1], "r");
  } else {
    errno = EBADF;
    perror("ERRO: Deve haver três argumentos");
    return EXIT_FAILURE;
  }


  get_line_size(argv[1]);

  Number numbers[10];
  for (int i = 0; i < 10; ++i) {
    if (initialize(&numbers[i], i) < 0) {
      return EXIT_FAILURE;
    }
  }


  char string[LINE_SIZE + 1];
  double * values;


  while (!feof(file)) {
    if (fgets(string, LINE_SIZE, file) != NULL) {
      values = parse_line(string);
      // insert_element(&numbers[(int)values[132]], create_element(values));
    }
  }



  fclose(file);
  
  return EXIT_SUCCESS;
}
