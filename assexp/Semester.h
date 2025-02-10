#ifndef SEMESTER_H
#define SEMESTER_H
#include "Course.h"
#include "Professor.h"
#include<iostream>
#include<string>
#include <utility>
#include <vector>
using namespace std;

class Semester {
private:
    int CapacityofCourses;             // Maximum number of courses in the semester
    int id;                            // Semester ID
    vector<Course> courses;            // List of courses offered in the semester
    string FieldofStudies;             // Field of studies for the semester (e.g., Science, Arts)

public:
    Semester();                        // Default constructor
    Semester(int id, int CapacityofCourses, string FieldofStudies); // Parameterized constructor
    int getId() const;                 // Getter for semester ID
    int getCapacityofCourses() const;  // Getter for the capacity of courses
    string getFieldofStudies() const;  // Getter for field of studies
    vector<Course> getCourses() const; // Getter for the list of courses in the semester
    void addCourse(Course course);     // Add a course to the semester
    static void initializeCourses(vector<Semester>& semesters); // Initialize courses for all semesters
    void assignProfessorToCourse(string courseId, Professor& professor); // Assign professor to a specific course
};

#endif

