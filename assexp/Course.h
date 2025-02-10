// Course.h
#ifndef COURSE_H
#define COURSE_H
#include<iostream>
#include<string>
#include <utility>
#include <vector>
using namespace std;

class Course {
    private:
        string id;                  // Course ID
        string name;                // Course name
        bool isLecture;             // Whether it's a lecture course
        bool isLab;                 // Whether it's a lab course
        int TeachingHours;          // Number of teaching hours

    public:
        Course(string id, string name, bool isLecture, bool isLab, int TeachingHours); // Parameterized constructor
        Course();                  // Default constructor
        string getId() const;      // Getter for course ID
        string getName() const;    // Getter for course name
        string getType() const;    // Getter for course type (lecture/lab)
        int getTeachinHours() const; // Getter for teaching hours
        bool isLabCourse() const;  // Check if it's a lab course
        bool isLectureCourse() const; // Check if it's a lecture course
};

#endif

