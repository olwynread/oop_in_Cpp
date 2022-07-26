#include<cmath>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

double get_mean(float arr[],int size) //Finds the mean of arr[]
{
    double mean; float sum{0};
    for(int i{0}; i < size; i++){
        sum += arr[i];
    }
    mean = sum/size;

    return mean;
}

double get_sd(float arr[],int size, double mean) //Finds the standard deviation of arr[]
{
    double sd; double sum{0}; double var;
    for(int i{0}; i < size; i++){
        sum += pow(arr[i]-mean, 2);
    }
    var = (1.0/(size-1))*sum;
    cout<<var<<endl;
    sd = pow(var, 0.5);

    return sd;
}

double get_mean_error(float sd, float size) //Finds the error on a mean given a standard deviation
{
    float error;
    error = sd/pow(size, 0.5);

    return error;
}

int main()
{
    // Finds the number of lines in the file
    fstream data_file{"/Users/olwynread/Documents/Work/CPP/courselist.dat.txt"};
    string discard; int N;
    while(!data_file.eof()){
        getline(data_file, discard);
        N+=1;
    }   
    N-=1;
    

    data_file.clear();    
    data_file.seekg(0);
    
    float *mark = new float[N]; int *course_id = new int[N]; string *course_name = new string[N];
    
    // Enters the data into its approprite array
    for(int i{0}; i < N; i++){
        data_file>>mark[i]; data_file>>course_id[i]; getline(data_file, course_name[i]);
    }
    data_file.close();

    delete[] course_id; delete[] course_name;

    // Calculates the required values
    double mean; mean = get_mean(mark, N);
    double standard_deviation = get_sd(mark, N, mean);
    double mean_error = get_mean_error(standard_deviation, N);

    delete[] mark;

    std::cout<<"These results have a mean of "<<mean<<" +/- "<<mean_error<<" and a standard deviation of "<<standard_deviation<<std::endl;
    return 0;
}