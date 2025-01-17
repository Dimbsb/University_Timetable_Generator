#ifndef SEMESTER_H
#define SEMESTER_H

#include <vector>
#include <string>
#include "Course.h"
#include "Professor.h"
using namespace std;

class Semester {
    int id;
    int CapacityofCourses;
    string FieldofStudies;
    vector<Course> courses;

public:
    Semester();
    Semester(int id, int CapacityofCourses, string FieldofStudies);

    int getId() const;
    int getCapacityofCourses() const;
    string getFieldofStudies() const;
    vector<Course> getCourses() const;

    void addCourse(Course course);
    void assignProfessorToCourse(string courseId, Professor& professor);
    void initializeCourses(vector<Semester>& semesters);
};

#endif
