#ifndef KNN_H
#define KNN_H

#define VALUES_NUMBER 132




typedef struct element {
  long id;
  double * values;
  double norm;
} Element;

typedef struct numbers {
  long id;
  int n_element;
  int size;
  int size_scale;
  Element ** elements;
} Number;

typedef struct cases {
  Element ** elements;
  long n_element;
  long size;
  int size_scale;
} Case;

void init();
int training (char *);
int testing (char *);

void get_line_size(const char *);
void get_lines_number(const char *);

double * parse_line (char *);

int initialize(Number *, long);
int insert_element(Number *, Element *);
Element * create_element(double *);

void sort_by_norm (Element **);

double calculate_norm (Element *, Element *);

void teste(Element *);

void quisk_sort (Element **, unsigned int, unsigned int);
unsigned int partition (Element **, unsigned int, unsigned int);


#endif 
