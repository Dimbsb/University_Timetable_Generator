#include "Professor.h"

Professor::Professor() {}

Professor::Professor(string ProfessorName, vector<string> coursesCodes, const vector<pair<int, int>>& unavailability) {
    this->ProfessorName = ProfessorName;
    this->coursesCodes = coursesCodes;
    this->unavailability = unavailability; // Use vector assignment
}

string Professor::getProfessorName() const {
    return ProfessorName;
}

vector<string> Professor::getCourseCodes() const {
    return coursesCodes;
}

vector<pair<int, int>> Professor::getunavailability() const {
    return unavailability; // Return the vector directly
}

void Professor::assignCourse(string courseId) {
    coursesCodes.push_back(courseId);
}
