#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <utility>
using namespace std;

class Professor {
    string ProfessorName;
    vector<string> coursesCodes;
    int unavailability[5][2];
    int day;
    int startHour;

public:
    Professor();
    Professor(string ProfessorName, vector<string> coursesCodes, int unavailability[5][2], int day, int startHour);

    string getProfessorName() const;
    vector<string> getCourseCodes() const;
    vector<pair<int, int>> getunavailability() const;

    void assignCourse(string courseId);
    bool isProfessorAvailable(const Professor& professor, int day, int startHour);
};

#endif
