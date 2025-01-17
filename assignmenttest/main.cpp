#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Professor.h"
#include "Semester.h"
#include "Course.h"
#include "Room.h"
#include "Laboratory.h"
#include "LectureRoom.h"

using namespace std;

struct TimeSlot {
    int start; // e.g., 9 for 9 AM, 14 for 2 PM
    int end;   // e.g., 11 for 11 AM, 17 for 5 PM
};

struct Assignment {
    string room;
    Course course;
    TimeSlot timeSlot;
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
                    if (!rooms.empty()) {
                        Assignment assignment = {rooms[0], *course, slot};  // Assign the first room (for simplicity)
                        weeklySchedule[professor.getProfessorName()].push_back(assignment);
                        rooms.erase(rooms.begin()); // Remove the assigned room from the list
                    } else {
                        cout << "No available rooms for course " << course->getName() << " taught by " << professor.getProfessorName() << endl;
                    }
                } else {
                    cout << "Professor " << professor.getProfessorName() << " is not available for course " << course->getName() << " at the specified time." << endl;
                }
            }
        }
    }

    // Display the weekly schedule
    for (const auto& entry : weeklySchedule) {
        cout << entry.first << "'s schedule:" << endl;
        for (const Assignment& assignment : entry.second) {
            cout << "  Room: " << assignment.room << ", Course: " << assignment.course.getName()
                 << ", Hours: " << assignment.timeSlot.start << " to " << assignment.timeSlot.end << endl;
        }
    }
}

int main() {
    cout << "Starting Timetable Generator..." << endl;

    vector<Semester> semesters;
    Semester::initializeCourses(semesters);
    vector<string> coursesCodes;
    vector<Professor> professors;
    vector<LectureRoom> lectureRooms;
    vector<Laboratory> laboratories;

    // Add some lecture rooms
    lectureRooms.push_back(LectureRoom("L101", "Building A", 50, "Lecture Room"));
    lectureRooms.push_back(LectureRoom("L102", "Building B", 75, "Lecture Room"));
    lectureRooms.push_back(LectureRoom("L103", "Building C", 100, "Lecture Hall"));

    // Add some laboratory rooms
    laboratories.push_back(Laboratory("Lab201", "Building A", 30, "Computer Lab1"));
    laboratories.push_back(Laboratory("Lab202", "Building B", 25, "Computer Lab2"));
    laboratories.push_back(Laboratory("Lab203", "Building C", 20, "Computer Lab3"));

    // Define unavailability
    int unavailability1[5][2] = {
        {13, 15}, // Monday
        {14, 16}, // Tuesday
        {12, 14}, // Wednesday
        {10, 12}, // Thursday
        {9, 11}   // Friday
    };

    // Professor 1
    vector<string> courses1 = {"MK1", "MK2"};
    Professor professor1("Dr. Smith", courses1, unavailability1);
    semesters[0].assignProfessorToCourse("MK1", professor1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    professors.push_back(professor1);


    // Retrieve courses from semesters
    vector<Course> allCourses;
    for (const Semester& semester : semesters) {
        vector<Course> courses = semester.getCourses();
        allCourses.insert(allCourses.end(), courses.begin(), courses.end());
    }

    // Initialize rooms
    vector<string> rooms = {"lectureRooms", "laboratories"};

    // Generate and print the weekly schedule
    generateSchedule(professors, allCourses, rooms);

    cout << "Timetable generation completed." << endl;

    return 0;
}