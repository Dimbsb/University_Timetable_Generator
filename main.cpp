#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Professor.h"
#include "Semester.h"

using namespace std;

struct TimeSlot {
    int start; // e.g., 9 for 9 AM, 14 for 2 PM
    int end;   // e.g., 11 for 11 AM, 17 for 5 PM
};

// We check if the professor is available at a certain time
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

// Function to generate the schedule based on professors and courses data
void generateSchedule(vector<Professor>& professors, vector<Course>& allCourses) {
    map<string, vector<TimeSlot>> professorSchedule; // Using a map to store each professor's schedule

    for (Professor& professor : professors) {
        vector<string>& professorCourses = professor.coursesCodes;
        vector<TimeSlot> assignedTimeSlots;

        // Loop through all courses of the professor
        for (const string& courseId : professorCourses) {
            // Find the course (assuming it's in the list of all courses)
            Course* course = nullptr;
            for (Course& c : allCourses) {
                if (c.id == courseId) {
                    course = &c;
                    break;
                }
            }
            if (!course) continue;  // If the course is not found, skip it

            // Handle courses longer than 3 hours
            if (course->getTeachinHours() > 3) {
                // Split the course into two parts, assigning them different days or times
                int mid = (course->timeslot.end + course->timeslot.start) / 2;
                TimeSlot slot1 = {course->timeslot.start, mid};
                TimeSlot slot2 = {mid, course->timeslot.end};
                // Try assigning valid time slots
                if (isProfessorAvailable(professor, slot1)) {
                    assignedTimeSlots.push_back(slot1);
                }
                if (isProfessorAvailable(professor, slot2)) {
                    assignedTimeSlots.push_back(slot2);
                }
            } else {
                // If the course is 3 hours or less, assign it in one time slot
                TimeSlot slot = course->timeslot;
                if (isProfessorAvailable(professor, slot)) {
                    assignedTimeSlots.push_back(slot);
                }
            }
        }

        // Save the professor's courses and assigned time slots in the map
        professorSchedule[professor.getProfessorName()] = assignedTimeSlots;
    }

    // Display the schedule
    for (const auto& entry : professorSchedule) {
        cout << entry.first << "'s schedule:" << endl;
        for (const TimeSlot& slot : entry.second) {
            cout << "  From " << slot.start << " to " << slot.end << endl;
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
    vector<string> courses1;
    courses1.push_back("MK1");
    courses1.push_back("MK2");
    Professor professor1("Dr. Smith", courses1, unavailability1);
    semesters[0].assignProfessorToCourse("MK1", professor1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    professors.push_back(professor1);

    // Professor 2
    vector<string> courses2;
    courses2.push_back("MK4-H");
    Professor professor2("Dr. Johnson", courses2, unavailability1);
    semesters[0].assignProfessorToCourse("MK4-H", professor2);
    professors.push_back(professor2);

    // Professor 3
    vector<string> courses3;
    courses3.push_back("MK7");
    Professor professor3("Dr. Brown", courses3, unavailability1);
    semesters[0].assignProfessorToCourse("MK7", professor3);
    professors.push_back(professor3);

    // Professor 4
    vector<string> courses4;
    courses4.push_back("MK8");
    Professor professor4("Dr. Davis", courses4, unavailability1);
    semesters[1].assignProfessorToCourse("MK8", professor4);
    professors.push_back(professor4);

    // Professor 5
    vector<string> courses5;
    courses5.push_back("MK9");
    courses5.push_back("MK10");
    Professor professor5("Dr. Wilson", courses5, unavailability1);
    semesters[0].assignProfessorToCourse("MK9", professor5);
    semesters[1].assignProfessorToCourse("MK10", professor5);
    professors.push_back(professor5);

    // Professor 6
    vector<string> courses6;
    courses6.push_back("MK11");
    courses6.push_back("MK12");
    Professor professor6("Dr. Martinez", courses6, unavailability1);
    semesters[3].assignProfessorToCourse("MK11", professor6);
    semesters[1].assignProfessorToCourse("MK12", professor6);
    professors.push_back(professor6);

    // Professor 7
    vector<string> courses7;
    courses7.push_back("MK14");
    Professor professor7("Dr. Anderson", courses7, unavailability1);
    semesters[3].assignProfessorToCourse("MK14", professor7);
    professors.push_back(professor7);

    // Professor 8
    vector<string> courses8;
    courses8.push_back("MK15");
    courses8.push_back("MK16");
    Professor professor8("Dr. Taylor", courses8, unavailability1);
    semesters[2].assignProfessorToCourse("MK15", professor8);
    semesters[1].assignProfessorToCourse("MK16", professor8);
    professors.push_back(professor8);
    
    vector<Course> allCourses = {course1, course2, course3, course4, course5, course6, course7, course8};

    // Print professor assignments
	for (vector<Professor>::const_iterator professor = professors.begin(); professor != professors.end(); ++professor) {
	    cout << "Professor " << professor->getProfessorName() << " is assigned to the following courses:" << endl;
	    const vector<string>& courseCodes = professor->getCourseCodes();
	    for (vector<string>::const_iterator courseId = courseCodes.begin(); courseId != courseCodes.end(); ++courseId) {
	        cout << " - " << *courseId << endl;
	    }
	    cout << endl;
	}


    // Prompt user for semester ID
    int selectedSemesterId;
    cout << "Enter the semester ID to view courses: ";
    cin >> selectedSemesterId;

    // Display selected semester's courses
	for (vector<Semester>::const_iterator semester = semesters.begin(); semester != semesters.end(); ++semester) {
	    if (semester->getId() == selectedSemesterId) {
	        cout << "Semester: " << semester->getId() 
	             << ", Field: " << semester->getFieldofStudies() << endl;
	
	        const vector<Course>& courses = semester->getCourses();
	        for (vector<Course>::const_iterator course = courses.begin(); course != courses.end(); ++course) {
	            cout << "  Course ID: " << course->getId()
	                 << ", Name: " << course->getName()
	                 << ", Type: " << course->getType()
	                 << ", Hours: " << course->getTeachinHours() << endl;
	        }
	    }
	}


    return 0;
}

