#include "Professor.h"
#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

Professor::Professor () {}
Professor::Professor (string ProfessorName, vector<string> coursesCodes, int unavailability[5][2]){
    this->ProfessorName = ProfessorName;
    this->coursesCodes = coursesCodes;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 2; ++j) {
            this->unavailability[i][j] = unavailability[i][j];
        }
    }
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