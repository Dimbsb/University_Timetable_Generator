// Course.h
#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Course {
public:
    Course(const string& id, const string& name, const string& type);
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
