#include<cmath>
#include<iostream>
#include<string>
#include<string.h>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>

double get_mean(std::vector<float> &arr,int size)  //Finds the mean of arr[]
{
    double mean; float sum{0};
    for(int i{0}; i < size; i++){
        sum += arr[i];
    }
    mean = sum/size;

    return mean;
}

double get_sd(std::vector<float> &arr,int size, double mean) //Finds the standard deviation of arr[]
{
    double sd; double sum{0}; double var;
    for(int i{0}; i < size; i++){
        sum += pow(arr[i]-mean, 2);
    }
    var = (1.0/(size-1))*sum;
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
    std::fstream data_file{"/Users/olwynread/Documents/Work/CPP/courselist.dat.txt"};
    std::string discard; int N;
    while(!data_file.eof()){
        getline(data_file, discard);
        N+=1;
    }   
    N-=1;
    
    // Goes back to the top of the file
    data_file.clear();    
    data_file.seekg(0);
    
    std::vector<float> mark(N); std::vector<std::string> course_id(N); std::vector<std::string> course_name(N);

    for(int i{0}; i < N; i++){
        data_file>>mark[i]; data_file>>course_id[i]; getline(data_file, course_name[i]);
    }
    data_file.close();

    //Asks the user to pick a year to view the results of
    char year{0};
    std::vector<char> answers(4); answers = {'1', '2', '3', '4'};
    while(std::find(answers.begin(), answers.end(), year) == answers.end()){
        std::cout<<"Which years marks would you like to view? 1,2,3 or 4. If you wish to view all years enter A: "<<std::endl;
        std::cin>>year;
        std::cin.ignore();
        if(year == 'A'){
            std::cout<<year<<std::endl;
            break;
        }
    }

    std::vector<float> mark_f(N); std::vector<std::string> course_id_f(N); std::vector<std::string> course_name_f(N);

    //Outputs the infor for all coursed in the chosen year
    if(std::find(answers.begin(), answers.end(), year) == answers.end()){
        for(int i{0}; i < N; i++){
            mark_f[i] = mark[i]; course_id_f[i] = course_id[i]; course_name_f[i] = course_name[i];
            std::cout<<"PHYS"<<course_id_f[i]<<" "<<course_name_f[i]<<" "<<mark_f[i]<<std::endl;
        }
    }else{
        int j{0};
        for(int i{0}; i < N; i++){
            std::string id; id = course_id[i];          
            if(id.at(0) == year){
                mark_f[j] = mark[i]; course_id_f[j] = course_id[i]; course_name_f[j] = course_name[i];
                std::cout<<mark_f[j]<<" "<<"PHYS"<<course_id_f[j]<<" "<<course_name_f[j]<<std::endl;
                j++;
            }
        }
        N = j;
    }

    //Calculates the required values
    double mean; mean = get_mean(mark_f, N);
    double standard_deviation = get_sd(mark_f, N, mean);
    double mean_error = get_mean_error(standard_deviation, N);

    std::cout<<"These results have a mean of "<<mean<<" +/- "<<mean_error<<" and a standard deviation of "<<standard_deviation<<std::endl;
    
    return 0;
}