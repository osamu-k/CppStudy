#include "gmock/gmock.h"

using namespace testing;

#include "matrix.h"

class matrix: public Test
{
    void SetUp()
    {

    }

    void TearDown()
    {
        Matrix::resetCount();
    }
};

TEST_F( matrix, canCreateMatrix_2x3 )
{
    {
        Matrix m(2,3);
        ASSERT_THAT( m.rowCount(), Eq(2) );
        ASSERT_THAT( m.columnCount(), Eq(3) );
        for( unsigned row = 0; row < m.rowCount(); row++ ){
            for( unsigned column = 0; column < m.columnCount(); column++ ){
                ASSERT_THAT( m.value(row,column), Eq(0) );
            }
        }
    }
    ASSERT_THAT( Matrix::instanceCount(), Eq(0) );
//    ASSERT_THAT( Matrix::totalCount(), Eq(1) );
    ASSERT_THAT( Matrix::valuesCount(), Eq(0) );
}

TEST_F( matrix, canSetValueToMatrix_2x3 )
{
    {
        Matrix m(2,3);
        m.setValue(0,0,1);
        m.setValue(0,1,2);
        m.setValue(0,2,3);
        m.setValue(1,0,4);
        m.setValue(1,1,5);
        m.setValue(1,2,6);

        ASSERT_THAT( m.value(0,0), Eq(1) );
        ASSERT_THAT( m.value(0,1), Eq(2) );
        ASSERT_THAT( m.value(0,2), Eq(3) );
        ASSERT_THAT( m.value(1,0), Eq(4) );
        ASSERT_THAT( m.value(1,1), Eq(5) );
        ASSERT_THAT( m.value(1,2), Eq(6) );
    }
    ASSERT_THAT( Matrix::instanceCount(), Eq(0) );
//    ASSERT_THAT( Matrix::totalCount(), Eq(1) );
    ASSERT_THAT( Matrix::valuesCount(), Eq(0) );
}

TEST_F( matrix, canSetValueToMatrix_2x3_atOnce )
{
    {
        Matrix m(2,3);
        double values[] = {1,2,3,4,5,6};
        m.setValues(values);

        ASSERT_THAT( m.value(0,0), Eq(1) );
        ASSERT_THAT( m.value(0,1), Eq(2) );
        ASSERT_THAT( m.value(0,2), Eq(3) );
        ASSERT_THAT( m.value(1,0), Eq(4) );
        ASSERT_THAT( m.value(1,1), Eq(5) );
        ASSERT_THAT( m.value(1,2), Eq(6) );
    }
    ASSERT_THAT( Matrix::instanceCount(), Eq(0) );
//    ASSERT_THAT( Matrix::totalCount(), Eq(1) );
    ASSERT_THAT( Matrix::valuesCount(), Eq(0) );
}

TEST_F( matrix, canAddMatrix2x2 )
{
    {
        Matrix m1(2,2);
        double values1[] = {1,2,3,4};
        m1.setValues(values1);

        Matrix m2(2,2);
        double values2[] = {5,6,7,8};
        m2.setValues(values2);

        Matrix m3 = m1 + m2;

        ASSERT_THAT( m3.value( 0, 0), Eq(1+5) );
        ASSERT_THAT( m3.value( 0, 1), Eq(2+6) );
        ASSERT_THAT( m3.value( 1, 0), Eq(3+7) );
        ASSERT_THAT( m3.value( 1, 1), Eq(4+8) );
    }
    ASSERT_THAT( Matrix::instanceCount(), Eq(0) );
//    ASSERT_THAT( Matrix::totalCount(), Eq(3) );
    ASSERT_THAT( Matrix::valuesCount(), Eq(0) );
}

TEST_F( matrix, canAddThreeMatrix )
{
    {
        Matrix m1(2,2);
        double values1[] = {11,12,13,14};
        m1.setValues(values1);

        Matrix m2(2,2);
        double values2[] = {21,22,23,24};
        m2.setValues(values2);

        Matrix m3(2,2);
        double values3[] = {31,32,33,34};
        m3.setValues(values3);

        Matrix m4 = m1 + m2 + m3;

        double values4[] = { 11+21+31, 12+22+32, 13+23+33, 14+24+34 };

        for( unsigned row = 0; row < 2; row ++ ){
            for( unsigned column = 0;  column < 2; column++ ){
                ASSERT_THAT( m4.value( row, column), Eq(values4[ row * 2 + column ]));
            }
        }
    }
    ASSERT_THAT( Matrix::instanceCount(), Eq(0) );
//    ASSERT_THAT( Matrix::totalCount(), Eq(4) );
    ASSERT_THAT( Matrix::valuesCount(), Eq(0) );
}

TEST_F( matrix, canCopyMatrix )
{
    {
        Matrix m1(2,2);
        double values1[] = {1,2,3,4};
        m1.setValues(values1);

        Matrix m2 = m1;
        Matrix m3;
        m3 = m1;

        ASSERT_THAT( m2.value(0,0), 1 );
        ASSERT_THAT( m2.value(0,1), 2 );
        ASSERT_THAT( m2.value(1,0), 3 );
        ASSERT_THAT( m2.value(1,1), 4 );
    }
    ASSERT_THAT( Matrix::instanceCount(), Eq(0) );
//    ASSERT_THAT( Matrix::totalCount(), Eq(2) );
    ASSERT_THAT( Matrix::valuesCount(), Eq(0) );
}

Matrix testFunction( Matrix m1, Matrix m2 )
{
    Matrix m3 = m1 + m2;
    return m3;
}

TEST_F( matrix, canbePassedAsFunctionArguments ){
    {
        Matrix m1(2,2);
        double values1[] = {1,2,3,4};
        m1.setValues(values1);

        Matrix m2(2,2);
        double values2[] = {5,6,7,8};
        m2.setValues(values2);

        Matrix m3 = testFunction(m1,m2);

        ASSERT_THAT( m3.value( 0, 0), Eq(1+5) );
        ASSERT_THAT( m3.value( 0, 1), Eq(2+6) );
        ASSERT_THAT( m3.value( 1, 0), Eq(3+7) );
        ASSERT_THAT( m3.value( 1, 1), Eq(4+8) );
    }
    ASSERT_THAT( Matrix::instanceCount(), Eq(0) );
//    ASSERT_THAT( Matrix::totalCount(), Eq(3) );
    ASSERT_THAT( Matrix::valuesCount(), Eq(0) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
