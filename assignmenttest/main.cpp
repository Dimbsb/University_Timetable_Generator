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
    vector<pair<int, int> > unavailable = professor.getunavailability(); // Get the unavailable times
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
        int requiredHours = 0; // Declare requiredHours here
        for (size_t k = 0; k < allCourses.size(); ++k) {
            if (allCourses[k].getId() == courseId) {
                course = &allCourses[k];
                requiredHours = course->getTeachinHours(); // Assign value when course is found
                break;
            }
        }
        if (!course) continue;

        int remainingHours = requiredHours;
        int semesterId = -1;
        for (map<int, vector<Course*> >::iterator it = coursesBySemester.begin(); it != coursesBySemester.end(); ++it) {
            int id = it->first;
            vector<Course*>& courses = it->second;
            for (size_t m = 0; m < courses.size(); ++m) {
                if (courses[m] == course) {
                    semesterId = id;
                    break;
                }
            }
            if (semesterId != -1) break;
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

    for (size_t index = 0; index < availableSlots.size(); ++index) {
        if (remainingHours <= 0) break;

        // Declare and initialize availableSlot inside the loop
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
	
	    // Iterate over room schedules
	    vector<TimeSlot>& roomSchedule = roomSchedules[room.getClassCode()];
	    for (size_t roomSlotIndex = 0; roomSlotIndex < roomSchedule.size(); ++roomSlotIndex) {
	        const TimeSlot& roomSlot = roomSchedule[roomSlotIndex];
	        if (!(lectureSlot.end <= roomSlot.start || lectureSlot.start >= roomSlot.end)) {
	            roomAvailable = false;
	            break;
	        }
	    
	
	    // Iterate over semester schedules
	    vector<TimeSlot>& semesterSchedule = semesterSchedules[semesterId][day];
	    for (size_t semesterSlotIndex = 0; semesterSlotIndex < semesterSchedule.size(); ++semesterSlotIndex) {
	        const TimeSlot& semesterSlot = semesterSchedule[semesterSlotIndex];
	        if (!(lectureSlot.end <= semesterSlot.start || lectureSlot.start >= semesterSlot.end)) {
	            semesterAvailable = false;
	            break;
	        }
	    }
	
	}

                            if (roomAvailable && semesterAvailable) {
                                Assignment lectureAssignment = {room.getClassCode(), *course, lectureSlot};
                                weeklySchedule[day][professor.getProfessorName()].push_back(lectureAssignment);
                                roomSchedules[room.getClassCode()].push_back(lectureSlot);
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
		
		    // Iterate over room schedules
		    vector<TimeSlot>& roomSchedule = roomSchedules[room.getClassCode()];
		    for (size_t roomSlotIndex = 0; roomSlotIndex < roomSchedule.size(); ++roomSlotIndex) {
		        const TimeSlot& roomSlot = roomSchedule[roomSlotIndex];
		        if (!(labSlot.end <= roomSlot.start || labSlot.start >= roomSlot.end)) {
		            roomAvailable = false;
		            break;
		        }
		    }
		
		
		    // Iterate over semester schedules
		    vector<TimeSlot>& semesterSchedule = semesterSchedules[semesterId][day];
		    for (size_t semesterSlotIndex = 0; semesterSlotIndex < semesterSchedule.size(); ++semesterSlotIndex) {
		        const TimeSlot& semesterSlot = semesterSchedule[semesterSlotIndex];
		        if (!(labSlot.end <= semesterSlot.start || labSlot.start >= semesterSlot.end)) {
		            semesterAvailable = false;
		            break;
		        }
		    }
		
		    if (roomAvailable && semesterAvailable) {
		        // Your logic for room and semester availability goes here
		    }
		
	

                            if (roomAvailable && semesterAvailable) {
                                Assignment labAssignment = {room.getClassCode(), *course, labSlot};
                                weeklySchedule[day][professor.getProfessorName()].push_back(labAssignment);
                                roomSchedules[room.getClassCode()].push_back(labSlot);
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
	
	    // Access the schedule for the current day
	    map<string, vector<Assignment> >& dailySchedule = weeklySchedule[day];
	    for (map<string, vector<Assignment> >::iterator it = dailySchedule.begin(); it != dailySchedule.end(); ++it) {
	        const string& professorName = it->first;
	        const vector<Assignment>& assignments = it->second;
	
	        cout << "  Professor " << professorName << ":\n";
	
	        // Iterate through assignments
	        for (size_t assignmentIndex = 0; assignmentIndex < assignments.size(); ++assignmentIndex) {
	            const Assignment& assignment = assignments[assignmentIndex];
	            cout << "    - Course: " << assignment.course.getName()
	                 << ", Room: " << assignment.room
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

	// Professor 1
	vector<pair<int, int> > unavailability1;
	unavailability1.push_back(pair<int, int>(9, 9));
	unavailability1.push_back(pair<int, int>(9, 9));
	unavailability1.push_back(pair<int, int>(9, 10));
	unavailability1.push_back(pair<int, int>(9, 20));
	unavailability1.push_back(pair<int, int>(9, 20));
	
	vector<string> courses1;
	courses1.push_back("Y1");
	courses1.push_back("YYH1");
	
	Professor professor1("EceTeacher-1", courses1, unavailability1);
	semesters[6].assignProfessorToCourse("Y1", professor1);
	semesters[6].assignProfessorToCourse("YYH1", professor1);
	professors.push_back(professor1);

	// Professor 2
	vector<pair<int, int> > unavailability2;
	unavailability2.push_back(pair<int, int>(9, 20));
	unavailability2.push_back(pair<int, int>(9, 20));
	unavailability2.push_back(pair<int, int>(9, 10));
	unavailability2.push_back(pair<int, int>(9, 20));
	unavailability2.push_back(pair<int, int>(9, 9));
	
	vector<string> courses2;
	courses2.push_back("Y2");
	
	Professor professor2("EceTeacher-2", courses2, unavailability2);
	semesters[6].assignProfessorToCourse("Y2", professor2);
	professors.push_back(professor2);
	
	// Professor 3
	vector<pair<int, int> > unavailability3;
	unavailability3.push_back(pair<int, int>(9, 10));
	unavailability3.push_back(pair<int, int>(9, 10));
	unavailability3.push_back(pair<int, int>(9, 20));
	unavailability3.push_back(pair<int, int>(9, 10));
	unavailability3.push_back(pair<int, int>(9, 10));

	vector<string> courses3;
	courses3.push_back("YEH1");
	
	Professor professor3("EceTeacher-3", courses3, unavailability3);
	semesters[6].assignProfessorToCourse("MKH7", professor3);
	professors.push_back(professor3);



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
