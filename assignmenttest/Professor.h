#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Professor {
private:
    string ProfessorName;
    vector<string> coursesCodes; 
    vector<pair<int, int>> unavailability; // Use a vector of pairs for unavailability
public:
    Professor();
    Professor(string ProfessorName, vector<string> coursesCodes, const vector<pair<int, int>>& unavailability);
    string getProfessorName() const;
    vector<string> getCourseCodes() const;
    vector<pair<int, int>> getunavailability() const; // Marked as const
    void assignCourse(string courseId); 
};

#endif
