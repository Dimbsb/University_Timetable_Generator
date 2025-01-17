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
    map<int, map<string, vector<TimeSlot>>> semesterSchedules; // Semester schedules per day
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
            int semester = semester;

            // Split hours into lab and lecture
            bool isLabCourse = course->isLabCourse();
            bool isLectureCourse = course->isLectureCourse();
            int labHours = (isLabCourse && isLectureCourse) ? requiredHours / 2 : (isLabCourse ? requiredHours : 0);
            int lectureHours = (isLabCourse && isLectureCourse) ? requiredHours / 2 : (isLectureCourse ? requiredHours : 0);

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
                for (TimeSlot& availableSlot : availableSlots) {
                    if (remainingHours <= 0) break;

                    // Schedule lecture hours first
                    if (lectureHours > 0) {
                        int lectureSlotLength = min(lectureHours, availableSlot.end - availableSlot.start);
                        TimeSlot lectureSlot = {availableSlot.start, availableSlot.start + lectureSlotLength};

                        // Check availability for lecture rooms
                        for (LectureRoom& room : lectureRooms) {
                            bool roomAvailable = true;
                            for (const TimeSlot& roomSlot : roomSchedules[room.getRoomName()]) {
                                if (!(lectureSlot.end <= roomSlot.start || lectureSlot.start >= roomSlot.end)) {
                                    roomAvailable = false;
                                    break;
                                }
                            }
                            if (roomAvailable) {
                                Assignment lectureAssignment = {room.getRoomName(), *course, lectureSlot};
                                weeklySchedule[day][professor.getProfessorName()].push_back(lectureAssignment);
                                roomSchedules[room.getRoomName()].push_back(lectureSlot);
                                professorSchedules[professor.getProfessorName()][day].push_back(lectureSlot);

                                lectureHours -= lectureSlotLength;
                                remainingHours -= lectureSlotLength;
                                availableSlot.start += lectureSlotLength;
                                break;
                            }
                        }
                    }

                    // Schedule lab hours next
                    if (labHours > 0 && availableSlot.start < availableSlot.end) {
                        int labSlotLength = min(labHours, availableSlot.end - availableSlot.start);
                        TimeSlot labSlot = {availableSlot.start, availableSlot.start + labSlotLength};

                        // Check availability for laboratory rooms
                        for (Laboratory& room : labRooms) {
                            bool roomAvailable = true;
                            for (const TimeSlot& roomSlot : roomSchedules[room.getRoomName()]) {
                                if (!(labSlot.end <= roomSlot.start || labSlot.start >= roomSlot.end)) {
                                    roomAvailable = false;
                                    break;
                                }
                            }
                            if (roomAvailable) {
                                Assignment labAssignment = {room.getRoomName(), *course, labSlot};
                                weeklySchedule[day][professor.getProfessorName()].push_back(labAssignment);
                                roomSchedules[room.getRoomName()].push_back(labSlot);
                                professorSchedules[professor.getProfessorName()][day].push_back(labSlot);

                                labHours -= labSlotLength;
                                remainingHours -= labSlotLength;
                                availableSlot.start += labSlotLength;
                                break;
                            }
                        }
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
    lectureRooms.push_back(LectureRoom("L104", "Building A", 50, "Lecture Room"));
    lectureRooms.push_back(LectureRoom("L105", "Building B", 75, "Lecture Room"));
    lectureRooms.push_back(LectureRoom("L106", "Building C", 100, "Lecture Room"));

    // Add some laboratory rooms
    laboratories.push_back(Laboratory("Lab201", "Building A", 30, "Computer Lab1"));
    laboratories.push_back(Laboratory("Lab202", "Building B", 25, "Computer Lab2"));
    laboratories.push_back(Laboratory("Lab203", "Building C", 20, "Computer Lab3"));
    laboratories.push_back(Laboratory("Lab204", "Building A", 30, "Computer Lab4"));
    laboratories.push_back(Laboratory("Lab205", "Building B", 25, "Computer Lab5"));
    laboratories.push_back(Laboratory("Lab206", "Building C", 20, "Computer Lab6"));

    // Define unavailability
    vector<pair<int, int>> unavailability1 = {{9, 9}, {9, 9}, {9, 10}, {9, 20}, {9, 20}};
    vector<pair<int, int>> unavailability2 = {{9, 20}, {9, 20}, {9, 10}, {9, 20}, {9, 9}};
    vector<pair<int, int>> unavailability3 = {{9, 10}, {9, 10}, {9, 20}, {9, 10}, {9, 10}};
    vector<pair<int, int>> unavailability4 = {{9, 20}, {9, 20}, {9, 20}, {9, 10}, {9, 10}};
    vector<pair<int, int>> unavailability5 = {{9, 15}, {9, 20}, {9, 20}, {9, 10}, {9, 10}};
    vector<pair<int, int>> unavailability6 = {{9, 9}, {9, 20}, {9, 20}, {9, 20}, {9, 9}};



    // Professor 1
    vector<string> courses1 = {"MK1", "MK2"};
    Professor professor1("EceTeacher-1", courses1, unavailability1);
    semesters[0].assignProfessorToCourse("MK1", professor1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    professors.push_back(professor1);

    // Professor 2
    vector<string> courses2 = {"MK7"};
    Professor professor2("EceTeacher-2", courses2, unavailability2);
    semesters[0].assignProfessorToCourse("MK7", professor2);
    professors.push_back(professor2);

    // Professor 3
    vector<string> courses3 = {"MKH2"};
    Professor professor3("EceTeacher-3", courses3, unavailability3);
    semesters[0].assignProfessorToCourse("MKH2", professor3);
    professors.push_back(professor3);

    // Professor 4
    vector<string> courses4 = {"MKH3"};
    Professor professor4("EceTeacher-4", courses4, unavailability4);
    semesters[0].assignProfessorToCourse("MKH3", professor4);
    professors.push_back(professor4);

    // Professor 5
    vector<string> courses5 = {"MK4-H"};
    Professor professor5("EceTeacher-4", courses5, unavailability5);
    semesters[0].assignProfessorToCourse("MK4-H", professor5);
    professors.push_back(professor5);

    // Professor 6
    vector<string> courses6 = {"MK9"};
    Professor professor6("EceTeacher-4", courses6, unavailability6);
    semesters[0].assignProfessorToCourse("MK9", professor6);
    professors.push_back(professor6);


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