#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct matrix_struct {
    unsigned row_count;
    unsigned column_count;
    double *values;
};

static int count = 0;

static double matrix_multiply_element( matrix *m1, matrix *m2, unsigned row, unsigned column );

static unsigned index( matrix *m, unsigned row, unsigned column );

matrix *matrix_new( unsigned row_count, unsigned column_count )
{
    matrix *m = (matrix *)malloc(sizeof(matrix));
    m->row_count = row_count;
    m->column_count = column_count;
    m->values = (double *)malloc( sizeof(double) * row_count * column_count );
    for( int row = 0; row < row_count; row++ ){
        for( int column = 0; column < column_count; column++ ){
            m->values[ index(m,row,column) ] = 0;
        }
    }
    count++;
    return m;
}

void matrix_delete( matrix *m )
{
    free( m->values );
    free( m );
    count--;
}

unsigned matrix_row_count( matrix *m )
{
    return m->row_count;
}

unsigned matrix_column_count( matrix *m )
{
    return m->column_count;
}

void matrix_set_value( matrix *m, unsigned row, unsigned column, double value )
{
    m->values[index(m,row,column)] = value;
}

void matrix_set_values( matrix *m, double values[] )
{
    for( int row = 0; row < m->row_count; row++ ){
        for( int column = 0; column < m->column_count; column++){
            unsigned i = index(m,row,column);
            m->values[i] = values[i];
        }
    }
}

double matrix_value( matrix *m, unsigned row, unsigned column )
{
    return m->values[ index(m,row,column) ];
}

matrix *matrix_add( matrix *m1, matrix *m2 )
{
    unsigned row_count = matrix_row_count(m1);
    unsigned column_count = matrix_column_count(m1);
    matrix *m3 = matrix_new( row_count, column_count );
    for( unsigned row = 0; row < row_count; row++ ){
        for( unsigned column = 0; column < column_count; column++ ){
            matrix_set_value( m3, row, column, matrix_value(m1,row,column) + matrix_value(m2,row,column) );
        }
    }
    return m3;
}

matrix *matrix_multiply( matrix *m1, matrix *m2 )
{
    unsigned row_count = matrix_row_count(m1);
    unsigned column_count = matrix_column_count(m1);
    matrix *m3 = matrix_new( matrix_row_count(m1), matrix_column_count(m2) );
    for( unsigned row = 0; row < row_count; row++ ){
        for( unsigned column = 0; column < column_count; column++ ){
            matrix_set_value( m3, row, column, matrix_multiply_element(m1,m2,row,column) );
        }
    }
    return m3;
}

static unsigned index( matrix *m, unsigned row, unsigned column )
{
    return m->column_count * row + column;
}

static double matrix_multiply_element( matrix *m1, matrix *m2, unsigned row, unsigned column )
{
    double value = 0;
    for( unsigned i = 0; i < matrix_column_count(m1); i++ ){
        value += (matrix_value(m1, row, i ) * matrix_value(m2, i, column) );
    }
    return value;
}

int matrix_count()
{
    return count;
}
