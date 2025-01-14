#ifndef PROFESSOR_H
#define PROFESSOR_H
#include<iostream>
#include<string>
#include <utility>
#include <vector>
using namespace std;

class Professor
{
private:
    string ProfessorName;
    vector<string> coursesCodes; // Change to vector<string>
    int unavailability[5][2];
public:
    Professor ();
    Professor (string ProfessorName, vector<string> coursesCodes, int unavailability[5][2]);
    string getProfessorName();
    vector<string> getCourseCodes();
    vector<pair<int, int> > getunavailability();
    void assignCourse(string courseId); // Method to assign course
};

#endif