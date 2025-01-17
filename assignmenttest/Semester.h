// Semester.h
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
private: int CapacityofCourses;
    int id;
    vector < Course > courses;
    string FieldofStudies;
public: Semester();
    Semester(int id, int CapacityofCourses, string FieldofStudies);
    int getId() const;
    int getCapacityofCourses() const;
    string getFieldofStudies() const;
    vector < Course > getCourses() const;
    void addCourse(Course course);
    static void initializeCourses(vector < Semester > & semesters);
    void assignProfessorToCourse(string courseId, Professor & professor);
};
#endif