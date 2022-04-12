#include <iostream>
#include <vector>
using namespace std;

namespace zich {

class Matrix {

    private:

       double **mat;
       size_t rows, cols;
       
    public:
       
        Matrix(vector<double> matrix, const int &my_rows,const int &my_cols) ;
        Matrix(const int &my_rows,const int &my_cols); 
        Matrix(const Matrix&);
       // Matrix();
        ~Matrix();

        // 1 - Addition / Soustraction operations
        
        Matrix operator+(const Matrix& my_mat);
        Matrix operator-(const Matrix& my_mat);
        Matrix &operator+=(const Matrix &my_mat);                 
        Matrix &operator-=(const Matrix &my_mat);
        Matrix operator+();  // Unary addition
        Matrix operator-();  // Unary soustraction

        // 2 - Compare operation
        bool operator==(const Matrix& my_mat) const;
        bool operator!=(const Matrix& my_mat) const;
        bool operator>(const Matrix& my_mat) const;
        bool operator>=(const Matrix& my_mat) const;
        bool operator<(const Matrix& my_mat) const;
        bool operator<=(const Matrix& my_mat) const;
        Matrix& operator=(const Matrix& a);

        // 3 - Increment / Decrement operations
        Matrix& operator++();   // prefix  ++mat
        Matrix operator++(int); // postfix mat++
        Matrix& operator--();   // prefix  --mat
        Matrix operator--(int); // postfix mat--

        // 4 - Multiplication operations between matrix and double
        Matrix &operator*=(const double num);
        friend Matrix operator*(const double num, const Matrix &matrix); 
        friend Matrix operator*(const Matrix &matrix, double num);
        
        // 5 -  Multiplication operation between two matrix 
        friend Matrix operator*(const Matrix &mat_1, const Matrix &mat_2); 
        Matrix operator*=(const Matrix &my_mat);
        

        // 6 - Input / Output operations
        friend ostream &operator<<(ostream &out, const Matrix &matrix);
        friend istream &operator>>(istream &input, Matrix &matrix);   
 };
}
