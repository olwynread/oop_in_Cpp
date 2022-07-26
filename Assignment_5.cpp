//Program which demonstrates the manipulation of a matrix via standard operators +, -, and *. Also demonstrates deepcopying\
when using copy and move.

#include <iostream>
class matrix_2D
{
        size_t rows{}, columns{}; double *matrix{nullptr}; // Private data describing the number of columns, rows as well as a pointer to the matrix data
    public:
        matrix_2D(){std::cout<<"Default constructor called"<<std::endl;}
        matrix_2D(size_t m, size_t n);
        matrix_2D(matrix_2D&);
        matrix_2D(matrix_2D&&);
        ~matrix_2D(){delete matrix; std::cout<<"Destructor called and matrix deleted"<<std::endl;}
        matrix_2D& operator=(matrix_2D&);
        matrix_2D& operator=(matrix_2D&&);
        size_t numrows() const {return rows;}
        size_t numcolumns() const {return columns;}
        size_t length() const {double len; len = rows*columns - 1; return len;}
        double & operator[](size_t i);
        matrix_2D operator+(const matrix_2D &matr);
        matrix_2D operator-(const matrix_2D &matr);
        matrix_2D operator*(const matrix_2D &matr);
        matrix_2D remove();

        friend std::ostream& operator<<(std::ostream &os, const matrix_2D &matr);
        friend std::istream& operator>>(std::istream &is, const matrix_2D &matr);
        friend matrix_2D setm_n();
};
matrix_2D::matrix_2D(size_t m, size_t n){ // Paramertized constructor
    std::cout<<"Paramertized constructor called"<<std::endl;
    
    if(m < 1){std::cout<<"Error: trying to declare a matrix with rows < 1"<<std::endl; throw("size not positive");}
    if(n < 1){std::cout<<"Error: trying to declare a matrix with columns < 1"<<std::endl; throw("size not positive");}

    rows = m; columns = n;
    size_t length; length = (n-1) + (m-1)*n;
    matrix = new double[length];
    for(size_t i{}; i<length; i++) {matrix[i]=0;}
}
matrix_2D::matrix_2D(matrix_2D &matr){ // Copy constructor with deep copying
    matrix = nullptr; rows = matr.rows; columns = matr.columns;
    matrix = new double[matr.length()];
    for(size_t i{}; i<matr.length(); i++) {matrix[i]=matr[i];}
}
matrix_2D & matrix_2D::operator=(matrix_2D& matr){ //Assignment operator with deep copying
    if(&matr == this) return *this; //Deals with self assignment
    delete matrix; matrix=nullptr; rows = 0; columns = 0;
    rows=matr.rows; columns=matr.columns;
    matrix=new double[matr.length()];
    for(size_t i{0}; i<matr.length(); i++) {matrix[i]=matr[i];}
    return *this;
}
matrix_2D::matrix_2D(matrix_2D &&matr){ // Move constructor
    rows=matr.rows; columns=matr.columns; matrix=matr.matrix;
    matr.rows=0; matr.columns=0; matr.matrix=nullptr;
}
matrix_2D & matrix_2D::operator=(matrix_2D&& matr){ // Move assignment operator
    std::swap(rows,matr.rows);
    std::swap(columns,matr.columns);
    std::swap(matrix,matr.matrix);
    return *this;
}
double & matrix_2D::operator[](size_t i){ // Overload [] operator
    if(i<0 || i>=((columns-1)+(rows-1)*columns)){
        std::cout<<"Error: trying to access matrix element out of bounds\n"; throw("Out of Bounds error");}
    return matrix[i];
}
matrix_2D matrix_2D::operator+(const matrix_2D &matr){ // Overloading + operator for matrix addition
    if(rows != matr.rows || columns != matr.columns){
        std::cout<<"Error: attempting to add matricies with different dimensions\n"; matrix_2D temp; return temp;}
    else{
        matrix_2D temp(matr.rows, matr.columns);
        for(size_t i{0}; i<temp.rows; i++){
            for(size_t j{0}; j<temp.columns; j++){
                temp.matrix[j + i*temp.columns] = matrix[j + i*temp.columns] + matr.matrix[j + i*temp.columns];
            }
        }
        return temp;
    }
}
matrix_2D matrix_2D::operator-(const matrix_2D &matr){ // Overloading - operator for matrix subtraction
    if(rows != matr.rows || columns != matr.columns){
        std::cout<<"Error: attempting to subtract matricies with different dimensions\n"; matrix_2D temp; return temp;}
    else{
        matrix_2D temp(matr.rows, matr.columns);
        for(size_t i{0}; i<temp.rows; i++){
            for(size_t j{0}; j<temp.columns; j++){
                temp.matrix[j + i*temp.columns] = matrix[j + i*temp.columns] - matr.matrix[j + i*temp.columns];
            }
        }
        return temp;
    }
}
matrix_2D matrix_2D::operator*(const matrix_2D &matr){ // Overloading * operator for matrix multiplication
    if(columns != matr.rows){
        std::cout<<"Error: attempting to multiply matricies with different dimensions\n"; matrix_2D temp; return temp;}
    else{
        matrix_2D temp(rows, matr.columns);
        for(size_t i{0}; i<temp.rows; i++){
            for(size_t j{0}; j<temp.columns; j++){
                double hold{0};
                for(size_t k{0}; k<columns; k++){
                    hold += matrix[k + (i*columns)] * matr.matrix[j + (k*matr.columns)];
                }
                temp.matrix[j + i*temp.columns] = hold;
            }
        }
        return temp;
    }
}
matrix_2D matrix_2D::remove(){ // Rmoves a row or column from a matrix
    char colrow{}; size_t index{}; bool check{false};
    while(check == false){    
        std::cout<<"Enter (m) to remove a row and (n) to remove a column followed by a space and the index of said row/column, matrix dimensions "<<
                rows<<" "<<columns<<": ";
        std::cin>>colrow>>index;
        if(colrow == 'm' && rows == 1){std::cout<<"Error: cannot remove rows from matrix with 1 row\n"; matrix_2D temp; return temp;}
        if(colrow == 'n' && columns == 1){std::cout<<"Error: cannot remove columns from matrix with 1 column\n"; matrix_2D temp; return temp;}
        if(colrow == 'm' && index > 0 && index <= rows){
            check = true;
            matrix_2D temp(rows-1, columns);
            for(size_t i{0}; i<index-1; i++){
                for(size_t j{0}; j<columns; j++){
                    temp.matrix[j + i*temp.columns] = matrix[j + i*temp.columns];}
            }
            for(size_t k{index}; k < temp.rows; k++){
                for(size_t j{0}; j<columns; j++){
                    temp.matrix[j + k*temp.columns] = matrix[j + k*temp.columns];}
            }
            return temp;          
        }
        if(colrow == 'n' && index > 0 && index <= columns){
            check = true;
            matrix_2D temp(rows, columns-1);
            for(size_t i{0}; i<rows; i++){
                for(size_t j{0}; j<index-1; j++){
                    temp.matrix[j + i*temp.columns] = matrix[j + i*temp.columns];}
                for(size_t k{0}; k<temp.columns; k++){
                    temp.matrix[k + i*temp.columns] = matrix[k + i*temp.columns];}
            }
            return temp;
        }
        std::cout<<"Error: invalid inputs\n";    
    }
}


// Friend functions of the matrix_2D class
std::istream& operator>>(std::istream &is, const matrix_2D &matr){ // Overload >> operator to output matrix
        for(size_t i{0}; i<matr.numrows(); i++){
            for(size_t j{0}; j<matr.numcolumns(); j++){
                is >> matr.matrix[j + i*matr.numcolumns()];
            }
        }
    return is;
}
std::ostream& operator<<(std::ostream &os, const matrix_2D &matr){ // Overload << operator to output matrix
    size_t position{};
    for(size_t i{0}; i<matr.numrows(); i++){
        os << "[";
        for(size_t j{0}; j<matr.numcolumns(); j++){
            position = j + i*matr.numcolumns();
            os << " " << matr.matrix[position] << " |";
        }
        os << "]\n";
    }
    return os;
}
matrix_2D setm_n(){
    int rows{}; int columns{};
    std::cout<<"Enter the number for rows followed by the number of columns in your matrix, with space in between: ";
    std::cin>>rows>>columns;
    matrix_2D temp(rows, columns);
    return temp;
}

int main()
{
std::cout<<"Dimensions for M1\n"; matrix_2D M1 = setm_n();
std::cout<<"Dimensions for M2\n"; matrix_2D M2 = setm_n();
std::cout<<"Dimensions for M3\n"; matrix_2D M3 = setm_n();
std::cout<<"Enter values for M1: "; std::cin>>M1;
std::cout<<"Enter values for M2: "; std::cin>>M2;
std::cout<<"Enter values for M3: "; std::cin>>M3;
matrix_2D M4, M5, M6, M7, M8;
M4 = M1 + M2;
M5 = M1 - M2;
M6 = M2 * M3;
std::cout<<"M1 + M2:\n"<<M4<<"\n";
std::cout<<"M1 - M2:\n"<<M5<<"\n";
std::cout<<"M2 * M3:\n"<<M6<<"\n";
std::cout<<"Move M1 to M7 by assignment \n";
M7 = M1;
std::cout<<"Change M1: \n";
M1 = M1.remove();
std::cout<<"M1 and M7 are now: \n"<<M1<<"\n"<<M7;
return 0;
}
