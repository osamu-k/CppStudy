#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix_struct matrix;

matrix *matrix_new( unsigned row_count, unsigned column_count );

void matrix_delete( matrix *m );

unsigned matrix_row_count( matrix *m );

unsigned matrix_column_count( matrix *m );

void matrix_set_value( matrix *m, unsigned row, unsigned column, double value );

void matrix_set_values( matrix *m, double values[] );

double matrix_value( matrix *m, unsigned row, unsigned column );

matrix *matrix_add( matrix *m1, matrix *m2 );

matrix *matrix_multiply( matrix *m1, matrix *m2 );

int matrix_count();

#endif // MATRIX_H
