// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <cmath>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);
bool isNumber(std::string string);
bool isInt(std::string string);

int main(int argc, char **argv)
{
    Student student;
    double average;

    student.f_name = new char[128];//create char space
    student.l_name = new char[128];

    // Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 0, 1000000000);
    std::cout << "Please enter the student's first name: ";
    std::cin.getline(student.f_name, 128);
    //std::chrono::seconds dura(1);
    //std::this_thread::sleep_for( dura );
    std::cout << "Please enter the student's last name: ";
    std::cin.getline(student.l_name, 128);
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);

    int numass = student.n_assignments;
    student.grades = new double[numass];
    int i;
    int counter = 0;
    double check;
    for(i = 0; i < numass; i++){
        std::string p1 = "Please enter grade for assignment ";
        std::string num = std::to_string ( i );
        std::string p3 = ": ";
        std::string question = p1 + num + p3; //built string for entering assignment numbers
        check = promptDouble(question, 0, 1000.0); //call prompt double for error checking and getting double
        student.grades[i] = check;
        counter = counter + 1; //for getting size in calculateStudentAverage
    }

    
    average = counter;
    calculateStudentAverage(student.grades, &average);
    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;
    std::cout << "  Average grade: " << average << std::endl;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    int value;
    std::string sValue;
    std::cout << message; //get initial input
    std::cin >> sValue;
    std::cin.ignore();

    if(isInt(sValue)){ //check if its only ints
        value = stoi(sValue);
    }

    while(!isInt(sValue) || value < min || value > max){ //check if int, < min and > max
        std::cin.clear();
        std::cout << "Sorry, I cannot understand your answer\n";
        std::cout << message; //get new input if any fail
        std::cin >> sValue;
        std::cin.ignore();
        
        if(isInt(sValue)){ //if pass then set new value
            value = stoi(sValue);
        }
    }
    //std::cout << "Got: " << value << std::endl;
    return value; 
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    double value;
    std::string sValue;
    std::cout << message; 
    std::cin >> sValue;
    std::cin.ignore();

    //std::cout << "svalue: " <<sValue << "\n" << std::endl;
    if(isNumber(sValue)){
        value = stod(sValue);
        //std::cout << "value: " << value << "\n" << std::endl;
    }

    while(!isNumber(sValue) || value < min || value > max){
        std::cin.clear();
        std::cout << "Sorry, I cannot understand your answer\n";
        std::cout << message;
        std::cin >> sValue;
        std::cin.ignore();
        
        if(isNumber(sValue)){
            value = stod(sValue);
        }
    }
    return value; 
    
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg) //object = student.grades    *avg = &average
{
    // Code to calculate and store average grade
    double* average = (double*) object;
    double maths = 0;
    int size = (int)*avg;
    //std::cout << "size: " << size << std::endl;
    for(int i = 0; i < size; i++){
        maths += *(average + i);
        //maths += average[i];
        //std::cout << "maths at "<< i << ":" << average[i] << std::endl;
    }
    double final;
    //std::cout << "maths: " << maths << std::endl;
    double rounded = round((maths / size) * 10) / 10;
    //final = rounded;
    //std::cout << "final: " << final << std::endl;
    *avg = rounded;
}

bool isNumber(std::string string){ //to check if a passed string has only ints and a single . for doubles
    int dCount = 0;
    for(int i = 0; i < string.length(); i ++){
        if(isdigit(string[i]) == false){
            if(string[i] == '.' && dCount < 1){
                dCount++;
            }
            else{
                return false;
            }
            
        }
    }
    return true;
}

bool isInt(std::string string){ //for checking if a passed string only has ints for an input that is an int
    int dCount = 0;
    for(int i = 0; i < string.length(); i ++){
        if(isdigit(string[i]) == false){
            return false;
        }
    }
    return true;
}
