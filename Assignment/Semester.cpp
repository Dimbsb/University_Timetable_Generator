#include "Semester.h"
#include <iostream> 
using namespace std;

Semester::Semester(int id, int CapacityofCourses, const string& FieldofStudies) {
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


void Semester::addCourse(const Course& course) {
    if (courses.size() >= CapacityofCourses) {
        cout << "Cannot add more than " << CapacityofCourses << " courses." << endl;
        return ; 
    }
    courses.push_back(course);
}

const vector<Course>& Semester::getCourses() const {
    return courses;
}

void Semester::initializeCourses(vector<Semester>& semesters) {

    Semester semester1(1, 7,"Y");
    semester1.addCourse(Course("MKH3", "Mechanics", "Lecture"));
    semester1.addCourse(Course("MK1", "Mathematical Analysis I", "Lecture"));
    semester1.addCourse(Course("MK2", "Linear Algebra", "Lecture"));
    semester1.addCourse(Course("MK4-H", "Structured Programming", "Lecture"));
    semester1.addCourse(Course("MK9", "Digital Design", "Lecture"));
    semester1.addCourse(Course("MKH2", "Design", "Lecture"));
    semester1.addCourse(Course("MK7", "English", "Lecture"));
    semesters.push_back(semester1);

    Semester semester2(2, 6,"Y");
    semester2.addCourse(Course("MK8", "Mathematical Analysis II", "Lecture"));
    semester2.addCourse(Course("MK18-H", "Electrical Circuits I", "Lecture"));
    semester2.addCourse(Course("MK12", "Discrete Mathematics", "Lecture"));
    semester2.addCourse(Course("MKH1", "Electrical Materials", "Lecture"));
    semester2.addCourse(Course("MK16", "Probability and Statistics", "Lecture"));
    semester2.addCourse(Course("MK10", "Object-Oriented Programming I", "Lecture"));
    semesters.push_back(semester2);

    Semester semester3(3, 6,"Y");
    semester3.addCourse(Course("MKH4", "Electrical Measurements", "Lecture"));
    semester3.addCourse(Course("MK15", "Applied Mathematics I", "Lecture"));
    semester3.addCourse(Course("MK17", "Algorithms & Data Structures", "Lecture"));
    semester3.addCourse(Course("MKH5", "Electrical Circuits II", "Lecture"));
    semester3.addCourse(Course("MK6", "Introduction to Telecommunications", "Lecture"));
    semester3.addCourse(Course("E26", "Thermodynamics", "Lecture"));
    semesters.push_back(semester3);

    Semester semester4(4, 7,"Y");
    semester4.addCourse(Course("MK21", "Applied Mathematics II", "Lecture"));
    semester4.addCourse(Course("MK3", "Electromagnetism", "Lecture"));
    semester4.addCourse(Course("MK23", "Signals and Systems Theory", "Lecture"));
    semester4.addCourse(Course("MK26-H", "Numerical Analysis", "Lecture"));
    semester4.addCourse(Course("MK25", "Electronics I", "Lecture"));
    semester4.addCourse(Course("MK14", "English II (Academic Skills)", "Lecture"));
    semester4.addCourse(Course("MK11", "Telecommunication Networks", "Lecture"));
    semesters.push_back(semester4);

    Semester semester5(5, 6,"Y");
    semester5.addCourse(Course("MKH8", "Economic-Technical Analysis", "Lecture"));
    semester5.addCourse(Course("MKH7", "Introduction to Electric Power Systems", "Lecture"));
    semester5.addCourse(Course("MK27", "Electromagnetic Waves", "Lecture"));
    semester5.addCourse(Course("MK28", "Digital Signal Processing", "Lecture"));
    semester5.addCourse(Course("MK30", "Electronics II", "Lecture"));
    semester5.addCourse(Course("MK20", "Computer Architecture", "Lecture"));
    semesters.push_back(semester5);

    Semester semester6(6, 6,"Y");
    semester6.addCourse(Course("MK29-H", "Communication Systems", "Lecture"));
    semester6.addCourse(Course("MK38", "Databases", "Lecture"));
    semester6.addCourse(Course("MK19-H", "Computer Networks", "Lecture"));
    semester6.addCourse(Course("Y4-H", "Automatic Control Systems I", "Lecture"));
    semester6.addCourse(Course("E22", "Microprocessors", "Lecture"));
    semester6.addCourse(Course("MKH9", "Electric Machines I", "Lecture"));
    semesters.push_back(semester6);

}