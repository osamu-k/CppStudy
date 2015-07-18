#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix();
    Matrix(unsigned rowCount, unsigned columnCount);
    Matrix( const Matrix &other );
    ~Matrix();
    unsigned rowCount() const;
    unsigned columnCount() const;
    void setValue(unsigned row, unsigned column, double value);
    void setValues(double value[]);
    double value(unsigned row, unsigned column) const;
    Matrix operator+( const Matrix &other ) const;
    Matrix &operator=( const Matrix &other);
    static int instanceCount();
    static int totalCount();
    static int valuesCount();
    static void resetCount();
private:
    unsigned index(unsigned row, unsigned column) const;
    unsigned m_rowCount;
    unsigned m_columnCount;
    double *m_values;
    static int m_instanceCount;
    static int m_totalCount;
    static int m_valuesCount;
};

#endif // MATRIX_H
