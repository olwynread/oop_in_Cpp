// Code submission for Assignment 4 19/03/2021\
The following code contains a class to handle complex numbers and operations on them, it is possible to enter these complex numbers\
by hard coding them or by user input. 

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<limits>
class complex // Class for handling complex numbers
{
        double re, im;
    public:
        complex() = default; // Default contructor
        complex(double a, double b): re{a}, im{b} {}; // Parameterized constructor
        ~complex(){std::cout<<"destroyed"<<std::endl;} // Destructor


        double real() const {return re;}
        double imaginary() const {return im;}
        double modulus() const {double m; m = pow(pow(re,2) + pow(im, 2), 0.5); return m;}
        double argument() const {double arg; arg = atan2(im, re); return arg;}
        complex conjugate() const {complex temp{re, -im}; return temp;} // Returns the complex conjugate
        complex operator+(const complex &c) const {complex temp{re+c.re, im+c.im}; return temp;} // The following are overloaded
        complex operator-(const complex &c) const {complex temp{re-c.re, im-c.im}; return temp;} // functions for +,-,*,/ operators
        complex operator*(const complex &c) const {complex temp{(re*c.re - im*c.im), (im*c.re + re*c.im)}; return temp;}
        complex operator/(const complex &c) const {complex temp{(re*c.re + im*c.im)/(pow(c.re,2) + pow(c.im,2)), 
                                                                (im*c.re - re*c.im)/(pow(c.re,2) + pow(c.im,2))}; return temp;}
        
        friend void output(const complex &c); // Friend of class to deal with outputting
        friend complex input(); // Friend of class to deal with inputing 
};


complex input(){ // Allows a user to input an object of the complex class
    double a, b; char sign; std::string bi;  int length;
    // The following while loop is an attempt at input validation and works for cases where letters are entered first 
    while(std::cout<<"Enter complex number in the form a +/- bi, including the spaces: ", !(std::cin>>a) || !(std::cin>>sign) || !(std::cin>>bi))
    {    
        if(std::cin.fail()){
            std::cout<<"Enter a valid input"<<std::endl;
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    length = bi.size() - 1; b = stod(bi.substr(0, length));
    complex temp;
    if(sign == '-'){
        temp.re = a; temp.im = -b;
    }else{
        temp.re = a; temp.im = b;
    }
    return temp;
}

void output(const complex &c){ // Outputs an object of the complex class
    std::cout.precision(3);
    if(c.im < 0){
        std::cout<<"z = "<<c.re<<" - "<<fabs(c.im)<<"i"<<std::endl;
    }else{
        std::cout<<"z = "<<c.re<<" + "<<fabs(c.im)<<"i"<<std::endl;
    }
}

int main() // Some examples of the above functions being used
{
    complex a(3, 4);
    complex b(1, -2);
    complex c = input();
    output(a); std::cout<<"Modulus and argument for 3 + 4i: "<<a.modulus()<<" "<<a.argument()<<std::endl;
    output(b); output(c);
    std::cout<<"1 - 2i divided by user input: "<<std::endl;
    complex d(b/c); output(d);
    return 0;
}