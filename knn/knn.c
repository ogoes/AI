#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "knn.h"

int LINE_SIZE = 0;
int LINES_NUMBER = 0;

Case TRAINING;

void init () {
  TRAINING.n_element = 0;
  TRAINING.size = 10;
  TRAINING.size_scale = 1;
}

int initialize (Number * number, long id) {

  number->size = 10;
  number->size_scale = 1;  
  number->n_element = 0;
  number->id = id;

  number->elements = (Element **) calloc (number->size, sizeof (Element *));
  if (!number->elements) return -1;

  

  return 0;
}

Element * create_element(double * values) {
  Element * E = (Element *) malloc (sizeof (Element));
  if (!E) return NULL;

  E->id = (int)values[VALUES_NUMBER];
  E->values = values;

  if (!TRAINING.elements) {
    TRAINING.elements = (Element **) calloc (TRAINING.size, sizeof (Element *));
  }

  TRAINING.elements[TRAINING.n_element++] = E;

  if (TRAINING.n_element == TRAINING.size) {
    TRAINING.size *= (++TRAINING.size_scale);
    Element ** aux = TRAINING.elements;
    TRAINING.elements = (Element **) calloc (TRAINING.size, sizeof (Element *));

    for (unsigned int i = 0; i < TRAINING.n_element; ++i)
      TRAINING.elements[i] = aux[i];
  }

  return E;
}

int insert_element (Number * number, Element * element) {
  if (!element || !number) return -1;

  if (!number->elements) {
    number->elements = (Element **) calloc (number->size, sizeof (Element *));
    if (!number->elements) return -1;
  }

  number->elements[number->n_element++] = element;

  if (number->n_element == number->size) {
    number->size *= (++number->size_scale);
    Element ** aux = number->elements;

    number->elements = (Element **) calloc (number->size, sizeof (Element *));
    if (!number->elements) return -1;

    for (unsigned int i = 0; i < number->n_element; ++i) 
      number->elements[i] = aux[i];
  }

  return 0;
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


double * parse_line (char * line) {

  double * values = (double *) calloc(VALUES_NUMBER + 1, sizeof (double));

  char * value_parsed;

  value_parsed = strtok(line, " ");
  int value_index = 0;
  while (value_parsed != NULL) {
    values[value_index++] = atof(value_parsed);
    value_parsed = strtok(NULL, " ");
  }
  return values;

}


void get_lines_number (const char filename[]) {
  FILE * file = fopen(filename, "r");

  int counter = 0;
  int charc = fgetc(file);
  while (!feof(file)) {
    if (charc == '\n') ++counter;
    charc = fgetc(file);
  }

  LINES_NUMBER = counter;

  fclose(file);
}


int training (char * filename) {
  printf("Asdasd");


  init();
  FILE * file = fopen(filename, "r");

  get_line_size(filename);
  get_lines_number(filename);

  Number numbers[10];
  for (int i = 0; i < 10; ++i) {
    if (initialize(&numbers[i], i) < 0) {
      return -1;
    }
  }

  char string[LINE_SIZE + 1];
  double * values;

  int i = 0, ids = 0;
  while (!feof(file)) {
    if (fgets(string, LINE_SIZE + 2, file) != NULL) {
      values = parse_line(string);
      ids = (int)values[VALUES_NUMBER];
      insert_element(&numbers[ids], create_element(values));
      values = NULL;
    }
    ++i;
  }

  fclose(file);
  return 0;
}
int testing (char * filename) {

  FILE * file = fopen(filename, "r");

  char string[LINE_SIZE + 1];
  double * values;

  Element E;

  int ids = 0;
  while (!feof(file)) {
    if (fgets(string, LINE_SIZE + 2, file) != NULL) {
      values = parse_line(string);

      ids = (int)values[VALUES_NUMBER];
      E.values = values;
      E.id = ids;

      values = NULL;

      teste(&E);
    }
  }

  fclose(file);
  return 0;
}

double calculate_norm (Element * A, Element * B) {
  double norm = 0.0;

  for (unsigned int i = 0; i < VALUES_NUMBER; ++i) {
    norm += pow(A->values[i] - B->values[i], 2);
  }

  return sqrt(norm);
}

void teste (Element * E) {
  Element ** norms = TRAINING.elements;

  for (unsigned int i = 0; i < TRAINING.n_element; ++i) {
    norms[i]->norm = calculate_norm(E, norms[i]);
  }

  sort_by_norm(norms);

  for (unsigned int i = 0; i < TRAINING.n_element; ++i) {
    printf("%lf ", norms[i]->norm);
  }
  printf("\n");

}

unsigned int partition (Element ** normas, unsigned int pivo, unsigned int r) {
  Element * aux = normas[r];
	unsigned int i = pivo - 1;
	for (unsigned int j = pivo; j < r; ++j) {
		if (normas[j]->norm <= aux->norm) {
			++i;
			Element * aaa = normas[j];
      normas[j] = normas[i];
      normas[i] = aaa;
		}
	}

  Element * aaa = normas[i+1];
  normas[i+1] = normas[r];
  normas[r] = aaa;

	return i + 1;
}

void quick_sort (Element ** normas, unsigned int pivo, unsigned int r) {
  if (pivo < r) {
		int meio = partition(normas, pivo, r);
		quick_sort(normas, pivo, meio-1);
		quick_sort(normas, meio+1, r);
	}
}

void sort_by_norm (Element ** norms) {
  quick_sort(norms, 0, TRAINING.n_element-1);
}
