#ifndef KNN_H
#define KNN_H

#define VALUES_NUMBER 132


typedef struct element {
  long id;
  int n_values;
  int size;
  double * values;
} Element;

typedef struct numbers {
  long id;
  int n_element;
  int size;
  int size_scale;
  Element * elements;
} Number;

int initialize(Number *, long);
int insert_element(Number *, Element *);
Element * create_element(double * values);

#endif 
