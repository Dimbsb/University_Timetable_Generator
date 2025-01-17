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
    const auto& unavailable = professor.getunavailability();
    for (const auto& time : unavailable) {
        if (!(slot.end <= time.first || slot.start >= time.second)) {
            return false; // Overlap detected
        }
    }
    return true;
}



// Generate the schedule based on professors, courses, and rooms data
void generateSchedule(vector<Professor>& professors, vector<Course>& allCourses, vector<LectureRoom>& lectureRooms, vector<Laboratory>& labRooms) {
    map<string, map<string, vector<Assignment>>> weeklySchedule; // Weekly schedule by day
    map<string, vector<TimeSlot>> roomSchedules; // Room schedules
    map<string, map<string, vector<TimeSlot>>> professorSchedules; // Professor schedules per day
    vector<string> daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    for (Professor& professor : professors) {
        vector<string> professorCourses = professor.getCourseCodes();

        for (const string& courseId : professorCourses) {
            Course* course = nullptr;
            for (Course& c : allCourses) {
                if (c.getId() == courseId) {
                    course = &c;
                    break;
                }
            }
            if (!course) continue;

            int requiredHours = course->getTeachinHours();
            int remainingHours = requiredHours;

            // Process each day of the week
            for (int dayIndex = 0; dayIndex < 5; ++dayIndex) {
                if (remainingHours <= 0) break;

                const string& day = daysOfWeek[dayIndex];
                pair<int, int> unavailability = professor.getunavailability()[dayIndex];
                vector<TimeSlot> availableSlots;

                // Determine available slots for the day
                int dailyStart = 9, dailyEnd = 20; // Working hours: 9 AM to 8 PM
                if (unavailability.first > dailyStart) {
                    availableSlots.push_back({dailyStart, unavailability.first});
                }
                if (unavailability.second < dailyEnd) {
                    availableSlots.push_back({unavailability.second, dailyEnd});
                }

                // Try to schedule the course within the available slots
                for (const TimeSlot& availableSlot : availableSlots) {
                    if (remainingHours <= 0) break;

                    for (int startHour = availableSlot.start; startHour < availableSlot.end; ++startHour) {
                        // Time slot length is adjusted based on remaining hours
                        int slotLength = min(remainingHours, availableSlot.end - startHour);
                        TimeSlot slot = {startHour, startHour + slotLength};

                        // Check if the professor is available during this time slot
                        bool professorAvailable = true;
                        for (const TimeSlot& professorSlot : professorSchedules[professor.getProfessorName()][day]) {
                            if (!(slot.end <= professorSlot.start || slot.start >= professorSlot.end)) {
                                professorAvailable = false;
                                break;
                            }
                        }
                        if (!professorAvailable) continue; // Skip if the professor is already assigned another course

                        // Check room availability and assign
                        bool assigned = false;
                        if (course->isLabCourse()) {
                            for (Laboratory& room : labRooms) {
                                bool roomAvailable = true;
                                for (const TimeSlot& roomSlot : roomSchedules[room.getRoomName()]) {
                                    if (!(slot.end <= roomSlot.start || slot.start >= roomSlot.end)) {
                                        roomAvailable = false;
                                        break;
                                    }
                                }
                                if (roomAvailable) {
                                    Assignment assignment = {room.getRoomName(), *course, slot};
                                    weeklySchedule[day][professor.getProfessorName()].push_back(assignment);
                                    roomSchedules[room.getRoomName()].push_back(slot);
                                    professorSchedules[professor.getProfessorName()][day].push_back(slot);
                                    remainingHours -= slotLength;
                                    assigned = true;
                                    break;
                                }
                            }
                        } else {
                            for (LectureRoom& room : lectureRooms) {
                                bool roomAvailable = true;
                                for (const TimeSlot& roomSlot : roomSchedules[room.getRoomName()]) {
                                    if (!(slot.end <= roomSlot.start || slot.start >= roomSlot.end)) {
                                        roomAvailable = false;
                                        break;
                                    }
                                }
                                if (roomAvailable) {
                                    Assignment assignment = {room.getRoomName(), *course, slot};
                                    weeklySchedule[day][professor.getProfessorName()].push_back(assignment);
                                    roomSchedules[room.getRoomName()].push_back(slot);
                                    professorSchedules[professor.getProfessorName()][day].push_back(slot);
                                    remainingHours -= slotLength;
                                    assigned = true;
                                    break;
                                }
                            }
                        }
                        if (assigned) break; // Move to the next slot if assigned
                    }
                }
            }

            if (remainingHours > 0) {
                cout << "Warning: Unable to schedule all hours for course " << course->getName()
                     << " taught by Professor " << professor.getProfessorName() << ". Remaining hours: " << remainingHours << "\n";
            }
        }
    }

    // Print the weekly schedule
    for (const string& day : daysOfWeek) {
        cout << day << ":\n";
        for (const auto& [professorName, assignments] : weeklySchedule[day]) {
            cout << "  Professor " << professorName << ":\n";
            for (const Assignment& assignment : assignments) {
                cout << "    - Course: " << assignment.course.getName() << ", Room: " << assignment.room
                     << ", Hours: " << assignment.timeSlot.start << " to " << assignment.timeSlot.end << "\n";
            }
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
    vector<pair<int, int>> unavailability1 = {{9, 10}, {9, 10}, {9, 20}, {9, 13}, {9, 13}};
    vector<pair<int, int>> unavailability2 = {{9, 10}, {9, 10}, {9, 20}, {9, 13}, {9, 13}};


    // Professor 1
    vector<string> courses1 = {"MK1", "MK2"};
    Professor professor1("Dr. Smith", courses1, unavailability1);
    semesters[0].assignProfessorToCourse("MK1", professor1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    professors.push_back(professor1);

    // Professor 2
    vector<string> courses2 = {"MK15", "MK17"};
    Professor professor2("Dr. Dimitris", courses2, unavailability2);
    semesters[2].assignProfessorToCourse("MK15", professor2);
    semesters[2].assignProfessorToCourse("MK17", professor2);
    professors.push_back(professor2);


    // Retrieve courses from semesters
    vector<Course> allCourses;
    for (const Semester& semester : semesters) {
        vector<Course> courses = semester.getCourses();
        allCourses.insert(allCourses.end(), courses.begin(), courses.end());
    }

    // Generate and print the weekly schedule
    generateSchedule(professors, allCourses, lectureRooms, laboratories);

    cout << "Timetable generation completed." << endl;

    return 0;
}