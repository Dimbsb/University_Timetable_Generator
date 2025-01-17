#include "Professor.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

// Default constructor
Professor::Professor() : ProfessorName(""), day(0), startHour(0) {
    // Initializing unavailability array to zero for default case
    for (int i = 0; i < 5; ++i) {
        unavailability[i][0] = 0;
        unavailability[i][1] = 0;
    }
}

// Parameterized constructor
Professor::Professor(string ProfessorName, vector<string> coursesCodes, int unavailability[5][2], int day, int startHour)
    : ProfessorName(ProfessorName), coursesCodes(coursesCodes), day(day), startHour(startHour) {
    // Copy the unavailability data
    for (int i = 0; i < 5; ++i) {
        this->unavailability[i][0] = unavailability[i][0];
        this->unavailability[i][1] = unavailability[i][1];
    }
}

// Getter for ProfessorName
string Professor::getProfessorName() const {
    return ProfessorName;
}

// Getter for coursesCodes
vector<string> Professor::getCourseCodes() const {
    return coursesCodes;
}

// Getter for unavailability (returns a vector of pairs)
vector<pair<int, int>> Professor::getunavailability() const {
    vector<pair<int, int>> unavailabilityVec;
    for (int i = 0; i < 5; ++i) {
        unavailabilityVec.push_back(make_pair(unavailability[i][0], unavailability[i][1]));
    }
    return unavailabilityVec;
}

// Method to assign a course to the professor
void Professor::assignCourse(string courseId) {
    // Check if the course is already assigned to the professor
    if (find(coursesCodes.begin(), coursesCodes.end(), courseId) == coursesCodes.end()) {
        coursesCodes.push_back(courseId); // Add course if not already assigned
    }
}

// Method to check if a professor is available at a specific day and time
bool Professor::isProfessorAvailable(const Professor& professor, int day, int startHour) {
    for (int i = 0; i < 5; ++i) {
        if (professor.unavailability[i][0] == day) {
            // Check if the professor's unavailability overlaps with the requested time
            if (startHour >= professor.unavailability[i][0] && startHour < professor.unavailability[i][1]) {
                return false; // Professor is not available
            }
        }
    }
    return true; // Professor is available
}
