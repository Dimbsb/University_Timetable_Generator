#include "Professor.h"
#include "Semester.h"
#include "Course.h"
#include "Room.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

void generateTimetable(const vector<Professor>& professors, const vector<Room>& rooms, vector<Semester>& semesters) {
    for (auto& semester : semesters) {
        for (auto& course : semester.getCourses()) {
            for (int day = 0; day < 5; ++day) {
                for (int hour = 9; hour <= 18; hour += 2) {
                    bool assigned = false;
                    for (const auto& professor : professors) {
                        if (isProfessorAvailable(professor, day, hour)) {
                            // Logic to check room availability and assign room
                            // Logic to check if the course already scheduled and avoid overlap
                            if (!assigned) {
                                // Assign course to professor and room
                                assigned = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void printTimetable(const vector<Semester>& semesters) {
    for (const auto& semester : semesters) {
        cout << "Semester " << semester.getId() << " (" << semester.getFieldofStudies() << "):" << endl;
        for (const auto& course : semester.getCourses()) {
            cout << "  " << course.getName() << " (" << course.getId() << "): ";
            // Print course schedule details
        }
    }
}

int main() {
    cout << "Starting Timetable Generator..." << endl;

    vector<Professor> professors;
    vector<Room> rooms;
    vector<Semester> semesters;

    // Initialize professors, rooms, and semesters
    // Example initialization, replace with actual data
    int unavailability[5][2] = {{0, 9}, {1, 14}, {2, 11}, {3, 10}, {4, 15}};
    professors.push_back(Professor("Prof. A", {"MKH3", "MK1"}, unavailability));
    professors.push_back(Professor("Prof. B", {"MK2", "MK4-H"}, unavailability));

    rooms.push_back(Room("R101", "Building A", 30));
    rooms.push_back(Room("R102", "Building B", 25));

    Semester semester1(1, 7, "core course");
    semester1.addCourse(Course("MKH3", "Mechanics", true, false, 4));
    semester1.addCourse(Course("MK1", "Mathematical Analysis I", true, false, 4));
    semester1.addCourse(Course("MK2", "Linear Algebra", true, false, 4));
    semester1.addCourse(Course("MK4-H", "Structured Programming", true, true, 4));
    semesters.push_back(semester1);

    generateTimetable(professors, rooms, semesters);
    printTimetable(semesters);

    cout << "Timetable generation completed." << endl;

    return 0;
}