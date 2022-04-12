#include <iostream>
#include <stdexcept>
#include "Matrix.hpp"
#include <vector>
using namespace std;
 

namespace zich {
  
    // Constructor with  three parameters - throw exceptions for invalid conditions
    Matrix::Matrix(vector<double> mat, const int &my_rows,const int &my_cols) {


        if ( my_rows <= 0 || my_cols <= 0) {
            throw invalid_argument("Error, row and col must be positive numbers");
        }
        if ( mat.size() != my_cols*my_rows) {
            throw invalid_argument("Error, size is different of col*row");
        }
        if ( mat.empty()) {
            throw invalid_argument("Error, size vector cannot be 0");
        }

        this->rows = (size_t)my_rows;
        this->cols = (size_t)my_cols;
        
        this->mat=new double* [(size_t)my_rows];

        for(uint i =0; i<my_rows; i++) {
            this->mat[i]=new double[(size_t)my_cols]; 
        }
        uint k =0;
        for(uint i=0;i<my_rows;i++) {
            for(uint j=0;j<my_cols;j++) {
                this->mat[i][j] = mat[k++];
            }
        }
    }

    // Constructor with two parameters
    Matrix::Matrix(const int &my_rows,const int &my_cols) {

        if ( my_rows <= 0 || my_cols <= 0) {
            throw invalid_argument("Error, row and col must be positive numbers");
        }

        this->rows = (size_t)my_rows;
        this->cols = (size_t)my_cols;

        this->mat=new double* [(size_t)my_rows];
        
        for(uint i =0;i<my_rows;i++)
        {
            this->mat[i]=new double[(size_t)my_cols]; 
        
        }

        uint k =0;
        for(uint i=0;i<my_rows;i++) {
            for(uint j=0;j<my_cols;j++) {
                this->mat[i][j] = 1;
            }
        }
    }

    // Copy constructor
    Matrix::Matrix(const Matrix &other){ 
        rows = other.rows;
        cols = other.cols;

        mat = new double* [other.rows];
        
        for(int i =0;i<other.rows;i++)
        {
        mat[i]=new double[other.cols];
        
        }
        for(int i=0;i<other.rows;i++) {
            for(int j=0;j<other.cols;j++) {
                    mat[i][j] = other.mat[i][j];
                }
        }

    }

    // Desconstructor
    Matrix::~Matrix(){

        for(int i =0;i<rows;i++) {
            delete [] mat[i]; 
        }
        delete [] mat;
    }


    // **************************************************   1 - Addition / Soustraction operations **********************************************************

    // Addition of two matrix  - Return a new matrix
    Matrix Matrix::operator+(const Matrix& my_mat) {

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }

        // Create a new matrix for addition 
        Matrix plus_mat(this->rows, this->cols);

        for(int i=0; i<plus_mat.cols ;i++) {
            for(int j=0; j<plus_mat.cols ;j++) {
                plus_mat.mat[i][j] = this->mat[i][j] + my_mat.mat[i][j];
            }
        }

        return plus_mat;
    }


    // Soustraction of two matrix - Return a new matrix
    Matrix Matrix::operator-(const Matrix& my_mat) {

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }

        // Create a new matrix for soustraction 
        Matrix minus_mat(my_mat.rows, my_mat.cols);
        
        for(int i=0; i<minus_mat.cols ;i++) {
            for(int j=0; j<minus_mat.cols ;j++) {
                minus_mat.mat[i][j] = this->mat[i][j] - my_mat.mat[i][j];
            }
        }
        return minus_mat;
    }

    // Plus/equal operator (+=)
    Matrix& Matrix::operator+=(const Matrix &my_mat) {                         

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }

        for (int i = 0; i < this->rows; i++) {
            for ( int j = 0; j < this->cols; j++) {
                this->mat[i][j] += my_mat.mat[i][j];
            }
        }
        return *this;
    }

    // Minus/equal operator (-=)
    Matrix &Matrix::operator-=(const Matrix &my_mat) {

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }

    
        for (int i = 0; i < this->rows; i++) {
            for ( int j = 0; j < this->cols; j++) {
                this->mat[i][j] -= my_mat.mat[i][j];
            }
        }
        return *this;
    }

    // Plus unary operator
    Matrix Matrix::operator+() {

        Matrix plusUnary(*this);
        return plusUnary;

    }

    // Minus unary operator
    Matrix Matrix::operator-(){

        Matrix temp_mat(this->rows, this->cols);

        for (int i =0; i < temp_mat.rows; i++) {
            for (int j =0; j < temp_mat.cols; j++) {
                if (this->mat[i][j] == 0) {
                    temp_mat.mat[i][j] = 0;
                }
                else {
                    temp_mat.mat[i][j] = this->mat[i][j]*(-1);           
                }
            }
        }
        return temp_mat;
    }



    // *******************************************************   2 - Compare operations  *********************************************************************

    // Equal (==)
    bool Matrix::operator==(const Matrix& my_mat) const {    
        
        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }

        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                if(this->mat[i][j] != my_mat.mat[i][j]) {
                    return false;     
                    }
                }
            }
            return true;
    }

    // Not Equal (!=)
    bool Matrix::operator!=(const Matrix& my_mat) const{

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                if ( this->mat[i][j] != my_mat.mat[i][j]) {
                    return true;     
                    }
                }
            }
            return false;
    }

    // Greater than (>)
    bool Matrix::operator>(const Matrix& my_mat) const {

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }
        bool flag = false;
        double sum1 =0;
        double sum2 =0;

        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                sum1 += (size_t)this->mat[i][j];
            }
        }

        for (size_t i = 0; i < my_mat.rows; i++) {
            for (size_t j = 0; j < my_mat.cols; j++) {
                sum2 += (size_t)my_mat.mat[i][j];
            }
        }

        if (sum1 > sum2) {
            flag = true;
        }
        return flag;

    }

    // Greater or equal (>=)
    bool Matrix::operator>=(const Matrix& my_mat) const {

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }
        bool flag = false;
        double sum1 =0;
        double sum2 =0;

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                sum1 += this->mat[i][j];
            }
        }

        for (int i = 0; i < my_mat.rows; i++) {
            for (int j = 0; j < my_mat.cols; j++) {
                sum2 += my_mat.mat[i][j];
            }
        }

        if (sum1 >= sum2) {
            flag = true;
        }
        return flag;

    }

    // Less than (<)
    bool Matrix::operator<(const Matrix& my_mat) const {

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two must matrix have the same size");
        }
        bool flag = false;
        double sum1 =0;
        double sum2 =0;

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                sum1 += this->mat[i][j];
            }
        }

        for (int i = 0; i < my_mat.rows; i++) {
            for (int j = 0; j < my_mat.cols; j++) {
                sum2 += my_mat.mat[i][j];
            }
        }

        if (sum1 < sum2) {
            flag = true;
        }
        return flag;

    }

    // Less or equal (<=)
    bool Matrix::operator<=(const Matrix& my_mat) const{

        if ( this->rows != my_mat.rows || this->cols != my_mat.cols) {
            throw invalid_argument("Error, the two matrix must have the same size");
        }

        bool flag = false;
        double sum1 =0;
        double sum2 =0;

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                sum1 += this->mat[i][j];
            }
        }

        for (int i = 0; i < my_mat.rows; i++) {
            for (int j = 0; j < my_mat.cols; j++) {
                sum2 += my_mat.mat[i][j];
            }
        }

        if (sum1 <= sum2) {
            flag = true;
        }
        return flag;

    }


    // *******************************************************  3 - Increment / Decrement operations ************************************************************

    // Prefix increment (_++)
    Matrix &Matrix::operator++() {

        for (int i = 0; i < this->rows; i++) {
            for ( int j = 0; j < this->cols; j++) {
                this->mat[i][j]++;
            }
        }
        return *this;
    }

    // Postfix increment (++_)
    Matrix Matrix::operator++(int) {
        Matrix mat_copy(*this);
        for (int i = 0; i < this->rows; i++) {
            for ( int j = 0; j < this->cols; j++) {
                this->mat[i][j]++;
            }
        }
        return mat_copy;
    }

    // Prefix decrement (_--)
    Matrix &Matrix::operator--() {

        for (int i = 0; i < this->rows; i++) {
            for ( int j = 0; j < this->cols; j++) {
                (this->mat[i][j])--;
            }
        }
        return *this;
    }

    // Postfix decrement (--_)
    Matrix Matrix::operator--(int) {
        Matrix mat_copy(*this);
        for (int i = 0; i < this->rows; i++) {
            for ( int j = 0; j < this->cols; j++) {
                this->mat[i][j]--;
            }
        }
        return mat_copy;
    }


    // **************************************** 4 - Multiplication operations between matrix and double *********************************************************
  
    // Multiplication of matrix and number - store the results in the matrix
    Matrix &Matrix::operator*=(const double num) {

        for ( int i = 0; i < this->rows; i++) {
            for ( int j = 0; j < this->cols; j++) {
                this->mat[i][j] *= num;
            }
        }
      return *this;
    }

    // Multiplication of num*matrix
    Matrix operator*(const double num, const Matrix &matrix) {

        Matrix mul_mat(matrix.rows, matrix.cols);

        for ( int i = 0; i < matrix.rows; i++) {
            for ( int j = 0; j < matrix.cols; j++) {
                mul_mat.mat[i][j] = num*matrix.mat[i][j];
            }
        }
        return mul_mat;
    }

    // Multiplication of matrix* num
    Matrix operator*(const Matrix &matrix, double num) {

        Matrix mul_mat(matrix.rows, matrix.cols);
        uint size = (uint) (matrix.rows*matrix.cols);
        vector<double> vect_mult(size, 0);
        size_t k=0;
        size_t n = matrix.rows;
        size_t m = matrix.cols;
        
        for(size_t i = 0; i<matrix.rows; i++){
            for(size_t j=0; j<matrix.cols; j++){
                vect_mult[i*matrix.cols + j]=matrix.mat[i][j]*num;    
        }
        }
        return Matrix(vect_mult,n,m);
    }

    // **************************************** 5 -  Multiplication operation between two matrix  *********************************************************

    // Multiplication of two matrix - store the results in a new matrix
    Matrix operator*(const Matrix &mat_1, const Matrix &mat_2) {

        if ( mat_1.cols != mat_2.rows) {
            throw invalid_argument(" Error, you cannot multiply those two matrix");
        }
        if(mat_1.rows<=0 || mat_1.cols<=0 || mat_2.rows<=0 || mat_2.cols<=0){
            throw invalid_argument("Error ,row and col matrix arguments must be positive");
        }

        vector<double> vect_multi;
        vect_multi.resize(mat_1.rows*mat_2.cols);
        size_t count=0;
        for(int i  = 0; i < mat_1.rows; i++) {
            for(int j = 0; j < mat_2.cols; j++) {
                double curr=0;
                for(int k = 0; k < mat_1.cols; k++) {
                    curr += mat_1.mat[i][k] * mat_2.mat[k][j];
                }
                vect_multi[count++]=curr;
            }
        }
        return Matrix(vect_multi,mat_1.rows,mat_2.cols);
    }


    // Multiplication of two matrix - store th results into this(obj)
    Matrix Matrix::operator*=(const Matrix &my_mat) {

        if (this->cols != my_mat.rows) {
            throw invalid_argument(" Error, you cannot multiply those two matrix");
        }
        
        if(this->rows<=0 || this->cols<=0 || my_mat.rows<=0 || my_mat.cols<=0){
            throw invalid_argument("Error ,row and col matrix arguments must be positive");
        }

        *this = *this*my_mat;
        return *this;    

    }
    Matrix& Matrix::operator=(const Matrix& a){

        if (this != &a) {

            Matrix cpy = +(*this);
            for(size_t i = 0;i< this->rows;i++){
                delete [] this->mat[i];
            }
            delete [] this->mat;
            this->mat = new double*[a.rows];
            this->cols = a.cols;
            this->rows = a.rows;
            for(size_t i=0;i<this->rows;i++){
                this->mat[i] = new double[this->cols];
            }
            for(size_t i=0;i<this->rows;i++){
                for(size_t j=0;j<this->cols;j++){
                    this->mat[i][j]=a.mat[i][j];
                }
            }
        }
        return *this;
}

     // ********************************************************  6 - Input / Output operations  *********************************************************

    // Print the output of a matrix
    ostream& operator<<(ostream& out, const Matrix &matrix) {
        size_t row = (size_t)matrix.rows;
        size_t col = (size_t)matrix.cols;

        for ( size_t i = 0; i < row; i++) {
            out << '['; 
            for (size_t j = 0; j < col; j++) {
                    out << matrix.mat[i][j];
                if ( j < col - 1) {
                    out << ' ';
                }
            }
            out << ']';
            if (i < row - 1) {
                
                out << '\n';
            }
        
        }
        return out;


    }

    istream& operator>>(istream& input, Matrix &matrix) {

        string s;
        string ans;
        while(getline(input,s)){
            ans+=s;
        }
        for(size_t i=0; i<ans.size()-1;i++){
            if(ans[i] == ','  && ans[i+1]!=' '){
                throw invalid_argument("Error, the character ' ' must be after ',' " );
            }
            if(ans[i] == ']'  && ans[i+1]!=','){
                throw invalid_argument("Error, the character ',' cannot be after ']' ");
            }
        }
        size_t rows=0;
        size_t cols=0;
        int size =0;
        for(size_t i =0; i<ans.length();i++){
            if(ans[i]==']'){
                rows++;
            }
        }
        size_t count=1;
        while(ans[count]!=']'){
            cols++;
            count++;
        }
        
        string num;
        count=0;
        size_t count_mat=0;
        vector<double> mat((size_t)(cols*rows));
        for(size_t i =0; i<ans.length();i++){
            if(ans[i+1]==' ' && ans[i]==','){
                i+=2;
            }
            else if(ans[i]==' ' || ans[i]==','){
                mat[count_mat]= stod(num);
                count_mat++;
                num=' ';
                count =0;
            }
            else if(ans[i]=='[' || ans[i]==']'){
                continue;
            }
            else{
                num[count] = ans[i];
                count++;
            }
        }
        matrix.rows = rows;
        matrix.cols = cols;
        matrix.mat = matrix.mat;
        return input;
    }
}   
    
