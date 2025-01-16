#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Professor.h"
#include "Semester.h"
#include "Course.h"

using namespace std;

struct TimeSlot {
    int start; // e.g., 9 for 9 AM, 14 for 2 PM
    int end;   // e.g., 11 for 11 AM, 17 for 5 PM
};

struct Assignment {
    string room;
    Course course;
};

// Check if the professor is available at a certain time
bool isProfessorAvailable(const Professor& professor, const TimeSlot& slot) {
    vector<pair<int, int>> unavailable = professor.getunavailability();
    for (const auto& time : unavailable) {
        if ((slot.start < time.second && slot.end > time.first) ||
            (slot.start >= time.first && slot.end <= time.second)) {
            return false;
        }
    }
    return true;
}

// Generate the schedule based on professors, courses, and rooms data
void generateSchedule(vector<Professor>& professors, vector<Course>& allCourses, vector<string>& rooms) {
    map<string, vector<Assignment>> weeklySchedule; // Using a map to store the weekly schedule

    for (Professor& professor : professors) {
        vector<string> professorCourses = professor.getCourseCodes();

        // Loop through all courses of the professor
        for (const string& courseId : professorCourses) {
            // Find the course (assuming it's in the list of all courses)
            Course* course = nullptr;
            for (Course& c : allCourses) {
                if (c.getId() == courseId) {
                    course = &c;
                    break;
                }
            }
            if (!course) continue;  // If the course is not found, skip it

            // Handle courses longer than 3 hours by splitting them
            vector<TimeSlot> courseTimeSlots;
            if (course->getTeachinHours() > 3) {
                int mid = course->getTeachinHours() / 2;
                TimeSlot slot1 = {9, 9 + mid};  // Example: 9 AM to mid
                TimeSlot slot2 = {9 + mid, 9 + course->getTeachinHours()};  // Example: mid to end
                courseTimeSlots.push_back(slot1);
                courseTimeSlots.push_back(slot2);
            } else {
                TimeSlot slot = {9, 9 + course->getTeachinHours()};  // Example: 9 AM to end
                courseTimeSlots.push_back(slot);
            }

            // Assign course to available slots and rooms
            for (const TimeSlot& slot : courseTimeSlots) {
                if (isProfessorAvailable(professor, slot)) {
                    Assignment assignment = {rooms[0], *course};  // Assign the first room (for simplicity)
                    weeklySchedule[professor.getProfessorName()].push_back(assignment);
                    rooms.erase(rooms.begin()); // Remove the assigned room from the list
                }
            }
        }
    }

    // Display the weekly schedule
    for (const auto& entry : weeklySchedule) {
        cout << entry.first << "'s schedule:" << endl;
        for (const Assignment& assignment : entry.second) {
            cout << "  Room: " << assignment.room << ", Course: " << assignment.course.getName() << ", Hours: " << assignment.course.getTeachinHours() << endl;
        }
    }
}

int main() {
    vector<Semester> semesters;
    Semester::initializeCourses(semesters);
    vector<Professor> professors;

    // Define unavailability
    int unavailability1[5][2] = {{9, 11}, {13, 15}, {10, 12}, {14, 16}, {11, 13}};

    // Professor 1
    vector<string> courses1 = {"MK1", "MK2"};
    Professor professor1("Dr. Smith", courses1, unavailability1);
    semesters[0].assignProfessorToCourse("MK1", professor1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    professors.push_back(professor1);

    // Professor 2
    vector<string> courses2 = {"MK4-H"};
    Professor professor2("Dr. Johnson", courses2, unavailability1);
    semesters[0].assignProfessorToCourse("MK4-H", professor2);
    professors.push_back(professor2);

    // Professor 3
    vector<string> courses3 = {"MK7"};
    Professor professor3("Dr. Brown", courses3, unavailability1);
    semesters[0].assignProfessorToCourse("MK7", professor3);
    professors.push_back(professor3);

    // Professor 4
    vector<string> courses4 = {"MK8"};
    Professor professor4("Dr. Davis", courses4, unavailability1);
    semesters[1].assignProfessorToCourse("MK8", professor4);
    professors.push_back(professor4);

    // Professor 5
    vector<string> courses5 = {"MK9", "MK10"};
    Professor professor5("Dr. Wilson", courses5, unavailability1);
    semesters[0].assignProfessorToCourse("MK9", professor5);
    semesters[1].assignProfessorToCourse("MK10", professor5);
    professors.push_back(professor5);

    // Professor 6
    vector<string> courses6 = {"MK11", "MK12"};
    Professor professor6("Dr. Martinez", courses6, unavailability1);
    semesters[3].assignProfessorToCourse("MK11", professor6);
    semesters[1].assignProfessorToCourse("MK12", professor6);
    professors.push_back(professor6);

    // Professor 7
    vector<string> courses7 = {"MK14"};
    Professor professor7("Dr. Anderson", courses7, unavailability1);
    semesters[3].assignProfessorToCourse("MK14", professor7);
    professors.push_back(professor7);

    // Professor 8
    vector<string> courses8 = {"MK15", "MK16"};
    Professor professor8("Dr. Taylor", courses8, unavailability1);
    semesters[2].assignProfessorToCourse("MK15", professor8);
    semesters[1].assignProfessorToCourse("MK16", professor8);
    professors.push_back(professor8);

    // Retrieve courses from semesters
    vector<Course> allCourses;
    for (const Semester& semester : semesters) {
        vector<Course> courses = semester.getCourses();
        allCourses.insert(allCourses.end(), courses.begin(), courses.end());
    }

    // Initialize rooms
    vector<string> rooms = {"Room A", "Room B", "Room C", "Room D"};

    // Generate and print the weekly schedule
    generateSchedule(professors, allCourses, rooms);

    return 0;
}