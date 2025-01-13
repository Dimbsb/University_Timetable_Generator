// Course.h
#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
public:
    Course(int id, const string& name, const string& type, const string& FieldofStudies);
    Course();
    int getId() const;
    string getName() const;
    string getType() const;
    string getFieldofStudies() const;
    void readDataCourse();

private:
    int id;
    string name;
    string type;
    string FieldofStudies;
};

#endif
