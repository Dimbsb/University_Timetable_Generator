#include "Semester.h"

#include<iostream>
#include<string>
#include <utility>
#include <iostream> 
using namespace std;

Semester::Semester() {
    id = 0;
    CapacityofCourses = 0;
    FieldofStudies = "";
}

Semester::Semester(int id, int CapacityofCourses, string FieldofStudies) {
    this->id = id;
    this->CapacityofCourses = CapacityofCourses;
    this->FieldofStudies = FieldofStudies;
}

int Semester::getId() const { 
    return id; 
}

int Semester::getCapacityofCourses() const { 
    return CapacityofCourses; 
}

string Semester::getFieldofStudies() const { 
    return FieldofStudies; 
}


vector<Course> Semester::getCourses() const {
    return courses;
}

void Semester::addCourse(Course course) {
    if (courses.size() >= CapacityofCourses) {
        cout << "Cannot add more than " << CapacityofCourses << " courses." << endl;
        return ; 
    }
    courses.push_back(course);
}

void Semester::assignProfessorToCourse(string courseId, Professor& professor) {
    for (Course course : courses) {
        if (course.getId() == courseId) {
            professor.assignCourse(courseId);
            return;
        }
    }
    cout << "Course ID " << courseId << " not found in Semester " << id << endl;
}


void Semester::initializeCourses(vector<Semester>& semesters) {

    Semester semester1(1, 7,"Y");
    semester1.addCourse(Course("MKH3", "Mechanics", true, false));
    semester1.addCourse(Course("MK1", "Mathematical Analysis I", true, false));
    semester1.addCourse(Course("MK2", "Linear Algebra", true, false));
    semester1.addCourse(Course("MK4-H", "Structured Programming", true, true));
    semester1.addCourse(Course("MK9", "Digital Design", true, true));
    semester1.addCourse(Course("MKH2", "Design", true, true));
    semester1.addCourse(Course("MK7", "English", true, false));
    semesters.push_back(semester1);

    Semester semester2(2, 6,"Y");
    semester2.addCourse(Course("MK8", "Mathematical Analysis II", true, false));
    semester2.addCourse(Course("MK18-H", "Electrical Circuits I", true, true));
    semester2.addCourse(Course("MK12", "Discrete Mathematics", true, false));
    semester2.addCourse(Course("MKH1", "Electrical Materials", true, false));
    semester2.addCourse(Course("MK16", "Probability and Statistics", true, false));
    semester2.addCourse(Course("MK10", "Object-Oriented Programming I", true, true));
    semesters.push_back(semester2);

    Semester semester3(3, 6,"Y");
    semester3.addCourse(Course("MKH4", "Electrical Measurements", true, true));
    semester3.addCourse(Course("MK15", "Applied Mathematics I", true, false));
    semester3.addCourse(Course("MK17", "Algorithms & Data Structures", true, true));
    semester3.addCourse(Course("MKH5", "Electrical Circuits II", true, true));
    semester3.addCourse(Course("MK6", "Introduction to Telecommunications", true, false));
    semester3.addCourse(Course("E26", "Thermodynamics", true, false));
    semesters.push_back(semester3);

    Semester semester4(4, 7,"Y");
    semester4.addCourse(Course("MK21", "Applied Mathematics II", true, false));
    semester4.addCourse(Course("MK3", "Electromagnetism", true, false));
    semester4.addCourse(Course("MK23", "Signals and Systems Theory", true, true));
    semester4.addCourse(Course("MK26-H", "Numerical Analysis", true, true));
    semester4.addCourse(Course("MK25", "Electronics I", true, true));
    semester4.addCourse(Course("MK14", "English II (Academic Skills)", true, false));
    semester4.addCourse(Course("MK11", "Telecommunication Networks", true, false));
    semesters.push_back(semester4);

    Semester semester5(5, 6,"Y");
    semester5.addCourse(Course("MKH8", "Economic-Technical Analysis", true, false));
    semester5.addCourse(Course("MKH7", "Introduction to Electric Power Systems", true, true));
    semester5.addCourse(Course("MK27", "Electromagnetic Waves", true, false));
    semester5.addCourse(Course("MK28", "Digital Signal Processing", true, true));
    semester5.addCourse(Course("MK30", "Electronics II", true, true));
    semester5.addCourse(Course("MK20", "Computer Architecture", true, true));
    semesters.push_back(semester5);

    Semester semester6(6, 6,"Y");
    semester6.addCourse(Course("MK29-H", "Communication Systems", true, false));
    semester6.addCourse(Course("MK38", "Databases", true, true));
    semester6.addCourse(Course("MK19-H", "Computer Networks", true, true));
    semester6.addCourse(Course("Y4-H", "Automatic Control Systems I", true, true));
    semester6.addCourse(Course("E22", "Microprocessors", true, true));
    semester6.addCourse(Course("MKH9", "Electric Machines I", true, true));
    semesters.push_back(semester6);

}