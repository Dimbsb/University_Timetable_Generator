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
    int unavailability1[5][2] = {{9, 11}, {13, 15}, {10, 12}, {14, 16}, {11, 13}};
    // Define professors and assign them to courses
    Professor professor1("Dr. Smith", {"MK1","MK2"}, {unavailability1});
    semesters[0].assignProfessorToCourse("MK1", professor1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    professors.push_back(professor1);

    Professor professor2("Dr. Johnson", {"MK4-H"}, {unavailability1});
    semesters[0].assignProfessorToCourse("MK4-H", professor2);
    professors.push_back(professor2);

    Professor professor3("Dr. Brown", {"MK7"}, {unavailability1});
    semesters[0].assignProfessorToCourse("MK7", professor3);
    professors.push_back(professor3);

    Professor professor4("Dr. Davis", {"MK8"}, {unavailability1});
    semesters[1].assignProfessorToCourse("MK8", professor4);
    professors.push_back(professor4);

    Professor professor5("Dr. Wilson", {"MK9", "MK10"}, {unavailability1});
    semesters[0].assignProfessorToCourse("MK9", professor5);
    semesters[1].assignProfessorToCourse("MK10", professor5);
    professors.push_back(professor5);

    Professor professor6("Dr. Martinez", {"MK11", "MK12"}, {unavailability1});
    semesters[3].assignProfessorToCourse("MK11", professor6);
    semesters[1].assignProfessorToCourse("MK12", professor6);
    professors.push_back(professor6);

    Professor professor7("Dr. Anderson", {"MK14"}, {unavailability1});
    semesters[3].assignProfessorToCourse("MK14", professor7);
    professors.push_back(professor7);

    Professor professor8("Dr. Taylor", {"MK15", "MK16"}, {unavailability1});
    semesters[2].assignProfessorToCourse("MK15", professor8);
    semesters[1].assignProfessorToCourse("MK16", professor8);
    professors.push_back(professor8);

    for (const Professor & professor: professors) {
        cout << "Professor " << professor.getProfessorName() << " is assigned to the following courses:" << endl;
        for (const string & courseId: professor.getCourseCodes()) {
            cout << " - " << courseId << endl;
        }
        cout << endl;
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
