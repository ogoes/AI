#ifndef FILE_H
#define FILE_H


int get_line_size (FILE *);
long get_lines_number (FILE *);
long get_features_number(char []);
char * get_line (FILE *, int);
double * parse_line (char [], int);


#endif
