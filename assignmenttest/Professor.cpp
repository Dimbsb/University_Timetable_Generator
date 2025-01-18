#include "Professor.h"

Professor::Professor() {}

Professor::Professor(string ProfessorName, vector<string> coursesCodes, const vector<pair<int, int>>& unavailability) {
    this->ProfessorName = ProfessorName;
    this->coursesCodes = coursesCodes;
    this->unavailability = unavailability;
}

string Professor::getProfessorName() const {
    return ProfessorName;
}

vector<string> Professor::getCourseCodes() const {
    return coursesCodes;
}

vector<pair<int, int>> Professor::getunavailability() const {
    return unavailability; 
}

void Professor::assignCourse(string courseId) {
    coursesCodes.push_back(courseId);
}
