#include "gmock/gmock.h"

using namespace testing;

extern "C" {

double matrix_element(unsigned rowCount, unsigned columnCount, double matrix[], unsigned row, unsigned column);

void matrix_2x2_add(
        double matrix1[][2],
        double matrix2[][2],
        double matrix3[][2]
)
{
    matrix3[0][0] = matrix1[0][0] + matrix2[0][0];
    matrix3[0][1] = matrix1[0][1] + matrix2[0][1];
    matrix3[1][0] = matrix1[1][0] + matrix2[1][0];
    matrix3[1][1] = matrix1[1][1] + matrix2[1][1];
}

void matrix_3x3_add(
        double matrix1[][3],
        double matrix2[][3],
        double matrix3[][3]
)
{
    for( unsigned row = 0; row < 3; row ++){
        for( unsigned column = 0; column < 3; column++ ){
            matrix3[row][column] = matrix1[row][column] + matrix2[row][column];
        }
    }
}

void matrix_add(
        unsigned rowCount,
        unsigned columnCount,
        double matrix1[],
        double matrix2[],
        double matrix3[]
)
{
    for( unsigned row = 0; row < rowCount; row ++){
        for( unsigned column = 0; column < columnCount; column++ ){
            matrix3[row * rowCount + column] = matrix1[row * rowCount + column] + matrix2[row * rowCount + column];
        }
    }
}

double matrix_multiply_element(
        unsigned rowCount1,
        unsigned columnCount1,
        double matrix1[],
        unsigned rowCount2,
        unsigned columnCount2,
        double matrix2[],
        unsigned row,
        unsigned column)
{
    if( columnCount1 != rowCount2 ){
        // Error !
        return 0;
    }
    double value = 0;
    for( unsigned i = 0; i < columnCount1; i++ ){
        value += (matrix_element(rowCount1, columnCount1, matrix1, row, i )
                  * matrix_element(rowCount2, columnCount2, matrix2, i, column) );
    }
    return value;
}

void matrix_multiply(
        unsigned rowCount1,
        unsigned columnCount1,
        double matrix1[],
        unsigned rowCount2,
        unsigned columnCount2,
        double matrix2[],
        double matrix3[]
)
{
    if( columnCount1 != rowCount2 ){
        // Error !
        return;
    }
    for( unsigned row = 0; row < rowCount1; row ++){
        for( unsigned column = 0; column < rowCount2; column++ ){
            matrix3[row * rowCount1 + column]
                = matrix_multiply_element(
                        rowCount1,columnCount1,matrix1,
                        rowCount2,columnCount2,matrix2,
                        row,column);
        }
    }
}

double matrix_element(
        unsigned rowCount,
        unsigned columnCount,
        double matrix[],
        unsigned row,
        unsigned column
        )
{
    return matrix[ row * columnCount + column ];
}

}


TEST( matrix, canAddMatrix2x2 )
{
    double matrix1[2][2] = { {1,2},{3,4} };
    double matrix2[2][2] = { {5,6},{7,8} };
    double matrix3[2][2] = { {0,0},{0,0} };
    matrix_2x2_add( matrix1, matrix2, matrix3 );

    ASSERT_THAT( matrix3[0][0], Eq(1+5) );
    ASSERT_THAT( matrix3[0][1], Eq(2+6) );
    ASSERT_THAT( matrix3[1][0], Eq(3+7) );
    ASSERT_THAT( matrix3[1][1], Eq(4+8) );
}

TEST( matrix, canAddMatrix3x3 )
{
    double matrix1[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
    double matrix2[3][3] = { {11,12,13},{14,15,16},{17,18,19} };
    double matrix3[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
    matrix_3x3_add( matrix1, matrix2, matrix3 );

    for( unsigned row = 0; row < 3; row ++){
        for( unsigned column = 0; column < 3; column++ ){
            ASSERT_THAT( matrix3[row][column], Eq( matrix1[row][column] + matrix2[row][column] ) );
        }
    }
}

TEST( matrix, canAddMatrix3x3_2 )
{
    double matrix1[3 * 3] = { 1,2,3,4,5,6,7,8,9 };
    double matrix2[3 * 3] = { 11,12,13,14,15,16,17,18,19 };
    double matrix3[3 * 3] = { 0,0,0,0,0,0,0,0,0 };
    matrix_add( 3, 3, matrix1, matrix2, matrix3 );

    for( unsigned row = 0; row < 3; row ++){
        for( unsigned column = 0; column < 3; column++ ){
//            ASSERT_THAT( matrix3[row * 3 + column], Eq( matrix1[row * 3 + column] + matrix2[row * 3 + column] ) );
            ASSERT_THAT( matrix_element(3,3,matrix3,row,column ),
                         Eq( matrix_element(3,3,matrix1,row,column )
                            + matrix_element(3,3,matrix2,row,column ) ) );
        }
    }
}

TEST( matrix, canMultilyMatrix )
{
    double matrix1[ 2 * 3 ] = { 1,2,3,
                                4,5,6 };
    double matrix2[ 3 * 2 ] = { 11,12,
                                13,14,
                                15,16 };
    double matrix3[ 2 * 2 ] = { 0,0,
                                0,0 };
    double matrix4[ 2 * 2 ] = { (1 * 11 + 2 * 13 + 3 * 15), (1 * 12 + 2 * 14 + 3 * 16),
                                (4 * 11 + 5 * 13 + 6 * 15), (4 * 12 + 5 * 14 + 6 * 16)};

    matrix_multiply( 2, 3, matrix1, 3, 2, matrix2, matrix3 );
    for( unsigned row = 0; row < 2; row ++){
        for( unsigned column = 0; column < 2; column++ ){
            ASSERT_THAT( matrix_element(2,2,matrix3,row,column ),
                         matrix_element(2,2,matrix4,row,column ) );
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

