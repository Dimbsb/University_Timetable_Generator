#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Professor {
private:
    string ProfessorName;               // Professor's name
    vector<string> coursesCodes;        // List of course codes taught by the professor
    vector<pair<int, int> > unavailability; // Unavailability schedule (pair of start and end time)

public:
    Professor();                        // Default constructor
    Professor(string ProfessorName, vector<string> coursesCodes, const vector<pair<int, int> >& unavailability); // Parameterized constructor
    string getProfessorName() const;     // Getter for professor's name
    vector<string> getCourseCodes() const; // Getter for the list of courses taught
    vector<pair<int, int> > getunavailability() const; // Getter for unavailability schedule
    void assignCourse(string courseId); // Assign a course to the professor
};

#endif

