// main.cpp
#include<iostream>
#include<string>
#include <utility>
#include <iostream>
#include <vector>

#include "Semester.h"
#include "Course.h"
#include "Professor.h"

using namespace std;

int main() {
    vector<Semester> semesters;
    Semester::initializeCourses(semesters);

    // Create a professor
    vector<string> coursesCodes;
    int unavailability[5][2] = {{0, 1}, {1, 0}, {1, 1}, {0, 0}, {1, 1}};
    Professor professor("Dr. Smith", coursesCodes, unavailability);
    // Assign professor to a course
    semesters[0].assignProfessorToCourse("MK1", professor);
    semesters[0].assignProfessorToCourse("MK2", professor);
    // Display professor's assigned courses
    cout << "Professor " << professor.getProfessorName() << " is assigned to the following courses:" << endl;
    for (const string& courseId : professor.getCourseCodes()) {
        cout << " - " << courseId << endl;
    }

    int selectedSemesterId;
    cout << "Enter the semester ID to view courses: ";
    cin >> selectedSemesterId;

    for (const auto& semester: semesters) {
        if (semester.getId() == selectedSemesterId) {
            cout << "Semester: " << semester.getId() << " NumberofCourses: " << semester.getCapacityofCourses()  << " Field: " << semester.getFieldofStudies() << endl;
            cout << "Courses in Semester:" << endl;
            const vector<Course>& courses = semester.getCourses();
            for (const Course& course: courses) {
                cout << "  Course ID: " << course.getId()<< ", Name: " << course.getName()<< ", Type: " << course.getType() << endl;
            }
            break;
        }
    }





    return 0;
}