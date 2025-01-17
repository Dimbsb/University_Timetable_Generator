#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
    string id;
    string name;
    bool isLecture;
    bool isLab;
    int TeachingHours;

public:
    Course();
    Course(string id, string name, bool isLecture, bool isLab, int TeachingHours);

    string getId() const;
    string getName() const;
    string getType() const;
    int getTeachinHours() const;
};

#endif
