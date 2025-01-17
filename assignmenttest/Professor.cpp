#include "Professor.h"
#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

Professor::Professor () {}

Professor::Professor (string ProfessorName, vector<string> coursesCodes, int unavailability[5][2], int day, int startHour){
    this->ProfessorName = ProfessorName;
    this->coursesCodes = coursesCodes;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 2; ++j) {
            this->unavailability[i][j] = unavailability[i][j];
        }
    }
    this->day = day;
    this->startHour = startHour;
}
string Professor::getProfessorName() const{
    return ProfessorName;
}
vector<string> Professor::getCourseCodes() const{
    return coursesCodes;
}
vector<pair<int, int>> Professor::getunavailability() const {
    vector<pair<int, int>> availabilityList;
    for (int i = 0; i < 5; ++i) {
        availabilityList.push_back(make_pair(unavailability[i][0], unavailability[i][1]));
    }
    return availabilityList;
}


void Professor::assignCourse(string courseId) {
    coursesCodes.push_back(courseId); 
}

bool Professor::isProfessorAvailable(const Professor& professor, int day, int startHour) {
    auto unavailability = professor.getunavailability();
    for (const auto& period : unavailability) {
        if (day == period.first && startHour >= period.second && startHour < period.second + 2) {
            return false;
        }
    }
    return true;
}