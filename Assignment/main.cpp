// main.cpp
#include "Semester.h"
#include "Course.h"
#include "Professor.h"

#include<iostream>
#include<string>
#include <utility>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<Semester> semesters;
    Semester::initializeCourses(semesters);
    vector<string> coursesCodes;
    vector<Professor> professors;

// Define professors and assign them to courses
Professor professor1("Dr. Smith", {"MK1", "MK2"}, {});
semesters[0].assignProfessorToCourse("MK1", professor1);
semesters[0].assignProfessorToCourse("MK2", professor1);

Professor professor2("Dr. Johnson", {"MK3", "MK4-H"}, {});
semesters[0].assignProfessorToCourse("MK3", professor2);
semesters[0].assignProfessorToCourse("MK4-H", professor2);

Professor professor3("Dr. Brown", {"MK5", "MK6"}, {});
semesters[0].assignProfessorToCourse("MK5", professor3);
semesters[0].assignProfessorToCourse("MK6", professor3);

Professor professor4("Dr. Davis", {"MK7", "MK8"}, {});
semesters[0].assignProfessorToCourse("MK7", professor4);
semesters[1].assignProfessorToCourse("MK8", professor4);

Professor professor5("Dr. Wilson", {"MK9", "MK10"}, {});
semesters[0].assignProfessorToCourse("MK9", professor5);
semesters[1].assignProfessorToCourse("MK10", professor5);

Professor professor6("Dr. Martinez", {"MK11", "MK12"}, {});
semesters[3].assignProfessorToCourse("MK11", professor6);
semesters[1].assignProfessorToCourse("MK12", professor6);

Professor professor7("Dr. Anderson", {"MK13", "MK14"}, {});
semesters[3].assignProfessorToCourse("MK13", professor7);
semesters[3].assignProfessorToCourse("MK14", professor7);

Professor professor8("Dr. Taylor", {"MK15", "MK16"}, {});
semesters[2].assignProfessorToCourse("MK15", professor8);
semesters[1].assignProfessorToCourse("MK16", professor8);

Professor professor9("Dr. Thomas", {"MK17", "MK18-H"}, {});
semesters[2].assignProfessorToCourse("MK17", professor9);
semesters[1].assignProfessorToCourse("MK18-H", professor9);

Professor professor10("Dr. Garcia", {"MK19-H", "MK20"}, {});
semesters[5].assignProfessorToCourse("MK19-H", professor10);
semesters[4].assignProfessorToCourse("MK20", professor10);

Professor professor11("Dr. Moore", {"MK21", "MK22"}, {});
semesters[3].assignProfessorToCourse("MK21", professor11);
semesters[7].assignProfessorToCourse("MK22", professor11);

Professor professor12("Dr. Jackson", {"MK23", "MK24"}, {});
semesters[3].assignProfessorToCourse("MK23", professor12);
semesters[4].assignProfessorToCourse("MK24", professor12);

Professor professor13("Dr. White", {"MK25", "MK26-H"}, {});
semesters[3].assignProfessorToCourse("MK25", professor13);
semesters[3].assignProfessorToCourse("MK26-H", professor13);

Professor professor14("Dr. Harris", {"MK27", "MK28"}, {});
semesters[4].assignProfessorToCourse("MK27", professor14);
semesters[4].assignProfessorToCourse("MK28", professor14);

Professor professor15("Dr. Martin", {"MK29-H", "MK30"}, {});
semesters[5].assignProfessorToCourse("MK29-H", professor15);
semesters[4].assignProfessorToCourse("MK30", professor15);

Professor professor16("Dr. Thompson", {"MK31", "MK32"}, {});
semesters[7].assignProfessorToCourse("MK31", professor16);
semesters[8].assignProfessorToCourse("MK32", professor16);

Professor professor17("Dr. Martinez", {"MK33", "MK34"}, {});
semesters[7].assignProfessorToCourse("MK33", professor17);
semesters[7].assignProfessorToCourse("MK34", professor17);

Professor professor18("Dr. Clark", {"MK35", "MK36"}, {});
semesters[8].assignProfessorToCourse("MK35", professor18);
semesters[8].assignProfessorToCourse("MK36", professor18);

Professor professor19("Dr. Lewis", {"MK37", "MK38"}, {});
semesters[7].assignProfessorToCourse("MK37", professor19);
semesters[5].assignProfessorToCourse("MK38", professor19);

Professor professor20("Dr. Walker", {"MK39", "MK40"}, {});
semesters[9].assignProfessorToCourse("MK39", professor20);
semesters[9].assignProfessorToCourse("MK40", professor20);

    // Display professor's assigned courses
    for (const Professor& professor : professors) {
        cout << "Professor " << professor.getProfessorName() << " is assigned to the following courses:" << endl;
        for (const string& courseId : professor.getCourseCodes()) { // Loop through the courses of this professor
            cout << " - " << courseId << endl;
        }
        cout << endl; // Add spacing between professors
    }


    int selectedSemesterId;
    cout << "Enter the semester ID to view courses: ";
    cin >> selectedSemesterId;

    for (const auto & semester: semesters) {
        if (semester.getId() == selectedSemesterId) {
            cout << "Semester: " << semester.getId() << ", Field: " << semester.getFieldofStudies() << endl;
            const vector < Course > & courses = semester.getCourses();
            for (const Course & course: courses) {
                cout << "  Course ID: " << course.getId() << ", Name: " << course.getName() << ", Type: " << course.getType() << ", Hours: " << course.getTeachinHours() << endl;
            }
        }
    }

    return 0;
    }