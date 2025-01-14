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
public:
    Course(string id, string name, string type);
    Course();
    string getId() const;
    string getName() const;
    string getType() const;
    void readDataCourse();

private:
    string id;
    string name;
    string type;
};

#endif
