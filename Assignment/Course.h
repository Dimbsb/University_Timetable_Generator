// Course.h
#ifndef COURSE_H
#define COURSE_H

#include<iostream>
#include<string>
#include <utility>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Course {

private:
    string id;
    string name;
    bool isLecture;
    bool isLab;


public:
    Course(string id, string name, bool isLecture, bool isLab);
    Course();
    string getId() const;
    string getName() const;
    string getType() const;

};

#endif
