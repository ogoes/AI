#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "knn.h"



int initialize (Number * number, long id) {

  number->size = 1;
  number->size_scale = 1;  
  number->n_element = 0;
  number->id = id;

  number->elements = (Element *) calloc (number->size, sizeof (Element));
  if (number->elements == NULL) return -1;

  return 0;
}
