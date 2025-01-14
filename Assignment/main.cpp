// main.cpp

#include <iostream>
#include <vector>
#include "Semester.h"
#include "Course.h"

using namespace std;

int main() {
    vector<Semester> semesters;
    Semester::initializeCourses(semesters);

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