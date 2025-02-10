#include "Professor.h"
#include "Semester.h"
#include "Course.h"
#include "Room.h"
#include "Laboratory.h"
#include "LectureRoom.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
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
    const vector<pair<int, int> >& unavailable = professor.getunavailability();
    for (size_t i = 0; i < unavailable.size(); ++i) {
        if (!(slot.end <= unavailable[i].first || slot.start >= unavailable[i].second)) {
            return false; // Overlap detected
        }
    }
    return true;
}

// Generate the schedule based on professors, courses, and rooms data
void generateSchedule(vector<Professor>& professors, vector<Semester>& semesters, vector<Course>& allCourses, vector<LectureRoom>& lectureRooms, vector<Laboratory>& labRooms) {
    map<string, map<string, vector<Assignment> > > weeklySchedule; // Weekly schedule by day
    map<string, vector<TimeSlot> > roomSchedules; // Room schedules
    map<string, map<string, vector<TimeSlot> > > professorSchedules; // Professor schedules per day
    map<int, map<string, vector<TimeSlot> > > semesterSchedules; // Semester schedules per day
    vector<string> daysOfWeek;
    daysOfWeek.push_back("Monday");
    daysOfWeek.push_back("Tuesday");
    daysOfWeek.push_back("Wednesday");
    daysOfWeek.push_back("Thursday");
    daysOfWeek.push_back("Friday");

    // Group courses by semester
    map<int, vector<Course*> > coursesBySemester;
    for (size_t i = 0; i < allCourses.size(); ++i) {
        Course& course = allCourses[i];
        for (size_t semesterId = 0; semesterId < semesters.size(); ++semesterId) {
            const vector<Course>& semesterCourses = semesters[semesterId].getCourses();
            for (size_t j = 0; j < semesterCourses.size(); ++j) {
                if (semesterCourses[j].getId() == course.getId()) {
                    coursesBySemester[semesterId].push_back(&course);
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < professors.size(); ++i) {
        Professor& professor = professors[i];
        vector<string> professorCourses = professor.getCourseCodes();

        for (size_t j = 0; j < professorCourses.size(); ++j) {
            const string& courseId = professorCourses[j];
            Course* course = NULL;
            for (size_t k = 0; k < allCourses.size(); ++k) {
                if (allCourses[k].getId() == courseId) {
                    course = &allCourses[k];
                    break;
                }
            }
            if (!course) continue;

            int requiredHours = course->getTeachinHours();
            int remainingHours = requiredHours;
            int semesterId = -1;
            for (map<int, vector<Course*> >::iterator i = coursesBySemester.begin(); i != coursesBySemester.end(); ++i) {
                if (find(i->second.begin(), i->second.end(), course) != i->second.end()) {
                    semesterId = i->first;
                    break;
                }
            }

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
                for (size_t index = 0; index < availableSlots.size(); ++index) {
                    if (remainingHours <= 0) break;

                    TimeSlot& availableSlot = availableSlots[index];

                    // Schedule lecture hours first
                    if (lectureHours > 0) {
                        int lectureSlotLength = min(lectureHours, availableSlot.end - availableSlot.start);
                        TimeSlot lectureSlot = {availableSlot.start, availableSlot.start + lectureSlotLength};

                        // Check availability for lecture rooms and semester overlap
                        for (size_t roomIndex = 0; roomIndex < lectureRooms.size(); ++roomIndex) {
                            LectureRoom& room = lectureRooms[roomIndex];
                            bool roomAvailable = true;
                            bool semesterAvailable = true;

                            for (size_t roomSlotIndex = 0; roomSlotIndex < roomSchedules[room.getRoomName()].size(); ++roomSlotIndex) {
                                const TimeSlot& roomSlot = roomSchedules[room.getRoomName()][roomSlotIndex];
                                if (!(lectureSlot.end <= roomSlot.start || lectureSlot.start >= roomSlot.end)) {
                                    roomAvailable = false;
                                    break;
                                }
                            }
                            for (size_t semesterSlotIndex = 0; semesterSlotIndex < semesterSchedules[semesterId][day].size(); ++semesterSlotIndex) {
                                const TimeSlot& semesterSlot = semesterSchedules[semesterId][day][semesterSlotIndex];
                                if (!(lectureSlot.end <= semesterSlot.start || lectureSlot.start >= semesterSlot.end)) {
                                    semesterAvailable = false;
                                    break;
                                }
                            }
                            if (roomAvailable && semesterAvailable) {
                                Assignment lectureAssignment = {room.getRoomName(), *course, lectureSlot};
                                weeklySchedule[day][professor.getProfessorName()].push_back(lectureAssignment);
                                roomSchedules[room.getRoomName()].push_back(lectureSlot);
                                professorSchedules[professor.getProfessorName()][day].push_back(lectureSlot);
                                semesterSchedules[semesterId][day].push_back(lectureSlot);

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

                        // Check availability for laboratory rooms and semester overlap
                        for (size_t labIndex = 0; labIndex < labRooms.size(); ++labIndex) {
                            Laboratory& room = labRooms[labIndex];
                            bool roomAvailable = true;
                            bool semesterAvailable = true;

                            for (size_t roomSlotIndex = 0; roomSlotIndex < roomSchedules[room.getRoomName()].size(); ++roomSlotIndex) {
                                const TimeSlot& roomSlot = roomSchedules[room.getRoomName()][roomSlotIndex];
                                if (!(labSlot.end <= roomSlot.start || labSlot.start >= roomSlot.end)) {
                                    roomAvailable = false;
                                    break;
                                }
                            }
                            for (size_t semesterSlotIndex = 0; semesterSlotIndex < semesterSchedules[semesterId][day].size(); ++semesterSlotIndex) {
                                const TimeSlot& semesterSlot = semesterSchedules[semesterId][day][semesterSlotIndex];
                                if (!(labSlot.end <= semesterSlot.start || labSlot.start >= semesterSlot.end)) {
                                    semesterAvailable = false;
                                    break;
                                }
                            }
                            if (roomAvailable && semesterAvailable) {
                                Assignment labAssignment = {room.getRoomName(), *course, labSlot};
                                weeklySchedule[day][professor.getProfessorName()].push_back(labAssignment);
                                roomSchedules[room.getRoomName()].push_back(labSlot);
                                professorSchedules[professor.getProfessorName()][day].push_back(labSlot);
                                semesterSchedules[semesterId][day].push_back(labSlot);

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
    for (size_t dayIndex = 0; dayIndex < daysOfWeek.size(); ++dayIndex) {
        const string& day = daysOfWeek[dayIndex];
        cout << day << ":\n";
        map<string, vector<Assignment> >& dailySchedule = weeklySchedule[day];
        for (map<string, vector<Assignment> >::iterator i = dailySchedule.begin(); i != dailySchedule.end(); ++i) {
            const string& professorName = i->first;
            const vector<Assignment>& assignments = i->second;
            cout << "  Professor " << professorName << ":\n";
            for (size_t assignmentIndex = 0; assignmentIndex < assignments.size(); ++assignmentIndex) {
                const Assignment& assignment = assignments[assignmentIndex];
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
    lectureRooms.push_back(LectureRoom("L107", "Building B", 75, "Lecture Room"));
    lectureRooms.push_back(LectureRoom("L108", "Building C", 100, "Lecture Hall"));

    // Add some laboratory rooms
    laboratories.push_back(Laboratory("Lab201", "Building A", 30, "Computer Lab1"));
    laboratories.push_back(Laboratory("Lab202", "Building B", 25, "Computer Lab2"));
    laboratories.push_back(Laboratory("Lab203", "Building C", 20, "Computer Lab3"));
    laboratories.push_back(Laboratory("Lab204", "Building A", 30, "Computer Lab4"));
    laboratories.push_back(Laboratory("Lab205", "Building B", 25, "Computer Lab5"));
    laboratories.push_back(Laboratory("Lab206", "Building C", 20, "Computer Lab6"));
    laboratories.push_back(Laboratory("Lab207", "Building B", 25, "Computer Lab5"));
    laboratories.push_back(Laboratory("Lab208", "Building C", 20, "Computer Lab6"));

    // Professor 1
    vector<pair<int, int> > unavailability1;
    unavailability1.push_back(pair<int, int>(0, 0));
    unavailability1.push_back(pair<int, int>(0, 0));
    unavailability1.push_back(pair<int, int>(9, 10));
    unavailability1.push_back(pair<int, int>(9, 20));
    unavailability1.push_back(pair<int, int>(9, 20));

    vector<string> courses1;
    courses1.push_back("MK2");
    courses1.push_back("MK1");

    Professor professor1("EceTeacher-1", courses1, unavailability1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    semesters[0].assignProfessorToCourse("MK1", professor1);
    professors.push_back(professor1);

    // Professor 2
    vector<pair<int, int> > unavailability2;
    unavailability2.push_back(pair<int, int>(9, 20));
    unavailability2.push_back(pair<int, int>(0, 0));
    unavailability2.push_back(pair<int, int>(9, 10));
    unavailability2.push_back(pair<int, int>(9, 20));
    unavailability2.push_back(pair<int, int>(0, 0));

    vector<string> courses2;
    courses2.push_back("MKH3");

    Professor professor2("EceTeacher-2", courses2, unavailability2);
    semesters[0].assignProfessorToCourse("MKH3", professor2);
    professors.push_back(professor2);

    // Professor 3
    vector<pair<int, int> > unavailability3;
    unavailability3.push_back(pair<int, int>(9, 10));
    unavailability3.push_back(pair<int, int>(9, 10));
    unavailability3.push_back(pair<int, int>(9, 20));
    unavailability3.push_back(pair<int, int>(9, 10));
    unavailability3.push_back(pair<int, int>(9, 10));

    vector<string> courses3;
    courses3.push_back("MK4-H");

    Professor professor3("EceTeacher-3", courses3, unavailability3);
    semesters[0].assignProfessorToCourse("MK4-H", professor3);
    professors.push_back(professor3);

    // Professor 4
    vector<pair<int, int> > unavailability4;
    unavailability4.push_back(pair<int, int>(9, 10));
    unavailability4.push_back(pair<int, int>(9, 10));
    unavailability4.push_back(pair<int, int>(0, 0));
    unavailability4.push_back(pair<int, int>(9, 10));
    unavailability4.push_back(pair<int, int>(9, 10));

    vector<string> courses4;
    courses4.push_back("MK9");

    Professor professor4("EceTeacher-4", courses4, unavailability4);
    semesters[0].assignProfessorToCourse("MK9", professor4);
    professors.push_back(professor4);

    // Professor 5
    vector<pair<int, int> > unavailability5;
    unavailability5.push_back(pair<int, int>(13, 14));
    unavailability5.push_back(pair<int, int>(9, 20));
    unavailability5.push_back(pair<int, int>(9, 20));
    unavailability5.push_back(pair<int, int>(9, 10));
    unavailability5.push_back(pair<int, int>(9, 10));

    vector<string> courses5;
    courses5.push_back("MKH2");

    Professor professor5("EceTeacher-5", courses5, unavailability5);
    semesters[0].assignProfessorToCourse("MKH2", professor5);
    professors.push_back(professor5);

    // Professor 6
    vector<pair<int, int> > unavailability6;
    unavailability6.push_back(pair<int, int>(9, 12));
    unavailability6.push_back(pair<int, int>(13, 14));
    unavailability6.push_back(pair<int, int>(15, 17));
    unavailability6.push_back(pair<int, int>(10, 12));
    unavailability6.push_back(pair<int, int>(14, 16));

    vector<string> courses6;
    courses6.push_back("MK7");

    Professor professor6("EceTeacher-6", courses6, unavailability6);
    semesters[0].assignProfessorToCourse("MK7", professor6);
    professors.push_back(professor6);

    // Retrieve courses from semesters
    vector<Course> allCourses;
    for (size_t i = 0; i < semesters.size(); ++i) {
        vector<Course> courses = semesters[i].getCourses();
        for (size_t j = 0; j < courses.size(); ++j) {
            allCourses.push_back(courses[j]);
        }
    }

    // Generate and print the weekly schedule
    generateSchedule(professors, semesters, allCourses, lectureRooms, laboratories);

    cout << "Timetable generation completed." << endl;

    return 0;
}