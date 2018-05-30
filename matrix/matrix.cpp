//
//  main.cpp
//  test
//
//  Created by Imanol Fernandez on 02/12/13.
//  Copyright (c) 2013 Ludei. All rights reserved.
//

#include <iostream>


struct Point{
    double x;
    double y;
    double z;
    Point(double x, double y, double z): x(x), y(y), z(z)
    {
    }
};

struct Matrix {
   
    typedef double MatrixData[4][4];
    MatrixData m_matrix;
    
    Matrix(double m11, double m12, double m13, double m14,
                double m21, double m22, double m23, double m24,
                double m31, double m32, double m33, double m34,
                double m41, double m42, double m43, double m44)
    {
        m_matrix[0][0] = m11; m_matrix[0][1] = m12; m_matrix[0][2] = m13; m_matrix[0][3] = m14;
        m_matrix[1][0] = m21; m_matrix[1][1] = m22; m_matrix[1][2] = m23; m_matrix[1][3] = m24;
        m_matrix[2][0] = m31; m_matrix[2][1] = m32; m_matrix[2][2] = m33; m_matrix[2][3] = m34;
        m_matrix[3][0] = m41; m_matrix[3][1] = m42; m_matrix[3][2] = m43; m_matrix[3][3] = m44;
    }
    
    void mapPoint(Point & p) const {
        const double x = m_matrix[3][0] + p.x * m_matrix[0][0] + p.y * m_matrix[1][0] + p.z * m_matrix[2][0];
        const double y = m_matrix[3][1] + p.x * m_matrix[0][1] + p.y * m_matrix[1][1] + p.z * m_matrix[2][1];
        const double z = m_matrix[3][2] + p.x * m_matrix[0][2] + p.y * m_matrix[1][2] + p.z * m_matrix[2][2];
        p.x = x;
        p.y = y;
        p.z = z;
    }
    
    static inline double determinant3x3(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3)
    {
        return a1 * (b2 * c3  - b3 * c2)
        - b1 * (a2 * c3 - a3 * c2)
        + c1 * (a2 * b3 - a3 * b2);
    }
    
    static inline double determinant(const Matrix& matrix)
    {
        const Matrix::MatrixData & m = matrix.m_matrix;
        const double a1 = m[0][0];
        const double b1 = m[0][1];
        const double c1 = m[0][2];
        const double d1 = m[0][3];
        const double a2 = m[1][0];
        const double b2 = m[1][1];
        const double c2 = m[1][2];
        const double d2 = m[1][3];
        const double a3 = m[2][0];
        const double b3 = m[2][1];
        const double c3 = m[2][2];
        const double d3 = m[2][3];
        const double a4 = m[3][0];
        const double b4 = m[3][1];
        const double c4 = m[3][2];
        const double d4 = m[3][3];
        
        return a1 * determinant3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4)
        - b1 * determinant3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4)
        + c1 * determinant3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4)
        - d1 * determinant3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);
    }
   
    
};


int main(int argc, const char * argv[])
{
    double sum = 0;
    for (int i = 0; i < 10000; ++i) {
        Matrix m(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16);
        for (int j = 0; j < 10000; ++j) {
            sum+=Matrix::determinant(m);
        }
        Point p1(1.1, 2.2, 3.3);
        for (int j = 0; j < 10000; j++) {
            m.mapPoint(p1);
        }
        sum+=p1.x;   
    }
    //printf("%f", sum);

    return 0;
}

