// Semester.h
#ifndef SEMESTER_H
#define SEMESTER_H

#include<iostream>
#include<string>
#include <utility>
#include <vector>
#include "Course.h"
#include "Professor.h"
using namespace std;

class Semester {
public:
    Semester(int id,int CapacityofCourses, string FieldofStudies);
    int getId() const;
    int getCapacityofCourses() const;
    string getFieldofStudies() const;
    void addCourse(Course course);
    const vector<Course> getCourses() const;
    static void initializeCourses(vector<Semester>& semesters);
    void assignProfessorToCourse(string courseId, Professor professor); 

private:
    int CapacityofCourses;
    int id;
    vector<Course> courses;
    string FieldofStudies;
};

#endif