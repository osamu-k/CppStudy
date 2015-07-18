#include "gmock/gmock.h"

using namespace testing;

extern "C" {

#include "matrix.h"

}

TEST( matrix, canCreateMatrix2x3 )
{
    matrix *m = matrix_new(2,3);

    ASSERT_THAT( matrix_row_count( m ), Eq(2) );
    ASSERT_THAT( matrix_column_count( m ), Eq(3) );
    ASSERT_THAT( matrix_value( m, 0, 0 ), Eq(0) );
    ASSERT_THAT( matrix_value( m, 0, 1 ), Eq(0) );
    ASSERT_THAT( matrix_value( m, 0, 2 ), Eq(0) );
    ASSERT_THAT( matrix_value( m, 1, 0 ), Eq(0) );
    ASSERT_THAT( matrix_value( m, 1, 1 ), Eq(0) );
    ASSERT_THAT( matrix_value( m, 1, 2 ), Eq(0) );

    matrix_delete(m);
    ASSERT_THAT( matrix_count(), Eq(0) );
}

TEST( matrix, canSetValuesOnMatrix2x3 )
{
    matrix *m = matrix_new(2,3);

    matrix_set_value( m, 0, 0, 1 );
    matrix_set_value( m, 0, 1, 2 );
    matrix_set_value( m, 0, 2, 3 );
    matrix_set_value( m, 1, 0, 4 );
    matrix_set_value( m, 1, 1, 5 );
    matrix_set_value( m, 1, 2, 6 );

    ASSERT_THAT( matrix_value( m, 0, 0 ), Eq(1) );
    ASSERT_THAT( matrix_value( m, 0, 1 ), Eq(2) );
    ASSERT_THAT( matrix_value( m, 0, 2 ), Eq(3) );
    ASSERT_THAT( matrix_value( m, 1, 0 ), Eq(4) );
    ASSERT_THAT( matrix_value( m, 1, 1 ), Eq(5) );
    ASSERT_THAT( matrix_value( m, 1, 2 ), Eq(6) );

    matrix_delete(m);
    ASSERT_THAT( matrix_count(), Eq(0) );
}

TEST( matrix, canSetValuesOnMatrix2x3AtOnce )
{
    matrix *m = matrix_new(2,3);
    double values[] = {1,2,3,4,5,6};

    matrix_set_values( m, values );

    ASSERT_THAT( matrix_value( m, 0, 0 ), Eq(1) );
    ASSERT_THAT( matrix_value( m, 0, 1 ), Eq(2) );
    ASSERT_THAT( matrix_value( m, 0, 2 ), Eq(3) );
    ASSERT_THAT( matrix_value( m, 1, 0 ), Eq(4) );
    ASSERT_THAT( matrix_value( m, 1, 1 ), Eq(5) );
    ASSERT_THAT( matrix_value( m, 1, 2 ), Eq(6) );

    matrix_delete(m);
    ASSERT_THAT( matrix_count(), Eq(0) );
}

TEST( matrix, canAddMatrix2x2 )
{
    matrix *m1 = matrix_new( 2, 2 );
    matrix_set_value( m1, 0, 0, 1);
    matrix_set_value( m1, 0, 1, 2);
    matrix_set_value( m1, 1, 0, 3);
    matrix_set_value( m1, 1, 1, 4);

    matrix *m2 = matrix_new( 2, 2 );
    double values[] = {5,6,7,8};
    matrix_set_values( m2, values );

    matrix *m3 = matrix_add( m1, m2 );

    ASSERT_THAT( matrix_value( m3, 0, 0), Eq(1+5) );
    ASSERT_THAT( matrix_value( m3, 0, 1), Eq(2+6) );
    ASSERT_THAT( matrix_value( m3, 1, 0), Eq(3+7) );
    ASSERT_THAT( matrix_value( m3, 1, 1), Eq(4+8) );

    matrix_delete(m1);
    matrix_delete(m2);
    matrix_delete(m3);
    ASSERT_THAT( matrix_count(), Eq(0) );
}

TEST( matrix, canMultiplyMatrix_2x3_3x2 )
{
    matrix *m1 = matrix_new( 2, 3 );
    double values1[] = {1,2,3,
                        4,5,6};
    matrix_set_values( m1, values1 );

    matrix *m2 = matrix_new( 3, 2 );
    double values2[] = {11,12,
                       13,14,
                       15,16};
    matrix_set_values( m2, values2 );

    double values3[ 2 * 2 ] = { (1 * 11 + 2 * 13 + 3 * 15), (1 * 12 + 2 * 14 + 3 * 16),
                               (4 * 11 + 5 * 13 + 6 * 15), (4 * 12 + 5 * 14 + 6 * 16)};

    matrix *m3 = matrix_multiply( m1, m2 );

    for( unsigned row = 0; row < 2; row ++ ){
        for( unsigned column = 0;  column < 2; column++ ){
            ASSERT_THAT( matrix_value( m3, row, column), Eq(values3[ row * 2 + column ]));
        }
    }

    matrix_delete(m1);
    matrix_delete(m2);
    matrix_delete(m3);
    ASSERT_THAT( matrix_count(), Eq(0) );
}

TEST( matrix, canAddThreeMatrix )
{
    matrix *m1 = matrix_new(2,2);
    double values1[] = {11,12,13,14};
    matrix_set_values(m1,values1);

    matrix *m2 = matrix_new(2,2);
    double values2[] = {21,22,23,24};
    matrix_set_values(m2,values2);

    matrix *m3 = matrix_new(2,2);
    double values3[] = {31,32,33,34};
    matrix_set_values(m3,values3);

//    matrix *m4 = matrix_add( matrix_add(m1,m2),m3);
    matrix *tmp = matrix_add(m1,m2);
    matrix *m4 = matrix_add( tmp,m3);

    double values4[] = { 11+21+31, 12+22+32, 13+23+33, 14+24+34 };

    for( unsigned row = 0; row < 2; row ++ ){
        for( unsigned column = 0;  column < 2; column++ ){
            ASSERT_THAT( matrix_value( m4, row, column), Eq(values4[ row * 2 + column ]));
        }
    }

    matrix_delete(m1);
    matrix_delete(m2);
    matrix_delete(m3);
    matrix_delete(m4);
    matrix_delete(tmp);
    ASSERT_THAT( matrix_count(), Eq(0) );
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
