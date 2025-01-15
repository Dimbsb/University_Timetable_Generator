// Semester.cpp
#include "Semester.h"

#include<iostream>
#include<string>
#include <utility>
#include <iostream>
#include <algorithm> 
using namespace std;

Semester::Semester() {
    id = 0;
    CapacityofCourses = 0;
    FieldofStudies = "";
}

Semester::Semester(int id, int CapacityofCourses, string FieldofStudies) {
    this -> id = id;
    this -> CapacityofCourses = CapacityofCourses;
    this -> FieldofStudies = FieldofStudies;
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

vector < Course > Semester::getCourses() const {
    return courses;
}

void Semester::addCourse(Course course) {
    if (courses.size() >= CapacityofCourses) {
        cout << "Cannot add more than " << CapacityofCourses << " courses." << endl;
        return;
    }
    courses.push_back(course);
}

void Semester::assignProfessorToCourse(string courseId, Professor & professor) {
    for (Course & course : courses) {
        if (course.getId() == courseId) {
            // Check if the professor is already assigned to this course
            const vector<string> & assignedCourses = professor.getCourseCodes();
            if (find(assignedCourses.begin(), assignedCourses.end(), courseId) == assignedCourses.end()) {
                professor.assignCourse(courseId);
            } 
            return;
        }
    }
    cout << "Course ID " << courseId << " not found in Semester " << id << endl;
}

void Semester::initializeCourses(vector < Semester > & semesters) {

    Semester semester1(1, 7, "core course");
    semester1.addCourse(Course("MKH3", "Mechanics", true, false, 4));
    semester1.addCourse(Course("MK1", "Mathematical Analysis I", true, false, 4));
    semester1.addCourse(Course("MK2", "Linear Algebra", true, false, 4));
    semester1.addCourse(Course("MK4-H", "Structured Programming", true, true, 4));
    semester1.addCourse(Course("MK9", "Digital Design", true, true, 4));
    semester1.addCourse(Course("MKH2", "Design", true, true, 4));
    semester1.addCourse(Course("MK7", "English", true, false, 4));
    semesters.push_back(semester1);

    Semester semester2(2, 6, "core course");
    semester2.addCourse(Course("MK8", "Mathematical Analysis II", true, false, 4));
    semester2.addCourse(Course("MK18-H", "Electrical Circuits I", true, true, 4));
    semester2.addCourse(Course("MK12", "Discrete Mathematics", true, false, 4));
    semester2.addCourse(Course("MKH1", "Electrical Materials", true, false, 4));
    semester2.addCourse(Course("MK16", "Probability and Statistics", true, false, 4));
    semester2.addCourse(Course("MK10", "Object-Oriented Programming I", true, true, 4));
    semesters.push_back(semester2);

    Semester semester3(3, 6, "core course");
    semester3.addCourse(Course("MKH4", "Electrical Measurements", true, true, 4));
    semester3.addCourse(Course("MK15", "Applied Mathematics I", true, false, 4));
    semester3.addCourse(Course("MK17", "Algorithms & Data Structures", true, true, 4));
    semester3.addCourse(Course("MKH5", "Electrical Circuits II", true, true, 4));
    semester3.addCourse(Course("MK6", "Introduction to Telecommunications", true, false, 4));
    semester3.addCourse(Course("E26", "Thermodynamics", true, false, 4));
    semesters.push_back(semester3);

    Semester semester4(4, 7, "core course");
    semester4.addCourse(Course("MK21", "Applied Mathematics II", true, false, 4));
    semester4.addCourse(Course("MK3", "Electromagnetism", true, false, 4));
    semester4.addCourse(Course("MK23", "Signals and Systems Theory", true, true, 4));
    semester4.addCourse(Course("MK26-H", "Numerical Analysis", true, true, 4));
    semester4.addCourse(Course("MK25", "Electronics I", true, true, 4));
    semester4.addCourse(Course("MK14", "English II (Academic Skills)", true, false, 4));
    semester4.addCourse(Course("MK11", "Telecommunication Networks", true, false, 4));
    semesters.push_back(semester4);

    Semester semester5(5, 6, "core course");
    semester5.addCourse(Course("MKH8", "Economic-Technical Analysis", true, false, 4));
    semester5.addCourse(Course("MKH7", "Introduction to Electric Power Systems", true, true, 4));
    semester5.addCourse(Course("MK27", "Electromagnetic Waves", true, false, 4));
    semester5.addCourse(Course("MK28", "Digital Signal Processing", true, true, 4));
    semester5.addCourse(Course("MK30", "Electronics II", true, true, 4));
    semester5.addCourse(Course("MK20", "Computer Architecture", true, true, 4));
    semesters.push_back(semester5);

    Semester semester6(6, 6, "core course ");
    semester6.addCourse(Course("MK29-H", "Communication Systems", true, false, 4));
    semester6.addCourse(Course("MK38", "Databases", true, true, 4));
    semester6.addCourse(Course("MK19-H", "Computer Networks", true, true, 4));
    semester6.addCourse(Course("Y4-H", "Automatic Control Systems I", true, true, 4));
    semester6.addCourse(Course("E22", "Microprocessors", true, true, 4));
    semester6.addCourse(Course("MKH9", "Electric Machines I", true, true, 4));
    semesters.push_back(semester6);

    Semester semester7(6, 6, "computer");
    semester7.addCourse(Course("MK29-H", "Communication Systems", true, false, 4));
    semester7.addCourse(Course("MK38", "Databases", true, true, 4));
    semester7.addCourse(Course("MK19-H", "Computer Networks", true, true, 4));
    semester7.addCourse(Course("Y4-H", "Automatic Control Systems I", true, true, 4));
    semester7.addCourse(Course("E22", "Microprocessors", true, true, 4));
    semester7.addCourse(Course("MKH9", "Electric Machines I", true, true, 4));

    Semester computerSemester7(7, 7, "Computer");
    computerSemester7.addCourse(Course("Y1", "Artificial Intelligence", true, false, 4));
    computerSemester7.addCourse(Course("YYH1", "Automatic Control Systems II", true, true, 4));
    computerSemester7.addCourse(Course("MK22", "Operating Systems", true, false, 4));
    computerSemester7.addCourse(Course("MK31", "Object-Oriented Programming II", true, false, 4));
    computerSemester7.addCourse(Course("E4", "Robotics", true, false, 4));
    computerSemester7.addCourse(Course("E2", "Electronic Health", true, false, 4));
    computerSemester7.addCourse(Course("E34", "Computer Graphics", true, false, 4));
    semesters.push_back(computerSemester7);

    Semester telecomSemester7(7, 7, "Telecommunications and Networks");
    telecomSemester7.addCourse(Course("Y2", "Communication Networks Analysis and Simulation", true, false, 4));
    telecomSemester7.addCourse(Course("Y3", "Antenna Systems and Wireless Propagation", true, false, 4));
    telecomSemester7.addCourse(Course("E45", "Digital Communications", true, false, 4));
    telecomSemester7.addCourse(Course("E9", "Queueing Systems", true, false, 4));
    telecomSemester7.addCourse(Course("E48", "Mobile and Satellite Communications", true, false, 4));
    telecomSemester7.addCourse(Course("ETH3", "Network Programming", true, false, 4));
    telecomSemester7.addCourse(Course("ETH1", "Electromagnetic Compatibility", true, false, 4));
    semesters.push_back(telecomSemester7);

    Semester energySemester7(7, 7, "Energy");
    energySemester7.addCourse(Course("YEH1", "Electric Power Transmission and Distribution", true, false, 4));
    energySemester7.addCourse(Course("YEH2", "Electric Machines II", true, false, 4));
    energySemester7.addCourse(Course("YEH3", "Power Electronics I", true, true, 4));
    energySemester7.addCourse(Course("YEH4", "Modern Electrical Installations", true, false, 4));
    energySemester7.addCourse(Course("EEH2", "Lighting Technology", true, false, 4));
    energySemester7.addCourse(Course("EEH4", "Heat Transfer", true, false, 4));
    energySemester7.addCourse(Course("EEH3", "Energy Automation", true, false, 4));
    semesters.push_back(energySemester7);

    Semester computerSemester8(8, 7, "Computer");
    computerSemester8.addCourse(Course("MK37", "Algorithm Analysis and Design", true, false, 4));
    computerSemester8.addCourse(Course("MK33", "Software Technology", true, false, 4));
    computerSemester8.addCourse(Course("MK34", "Parallel and Distributed Processing Systems", true, false, 4));
    computerSemester8.addCourse(Course("Y7", "Human-Computer Interaction", true, false, 4));
    computerSemester8.addCourse(Course("E15", "Biomedical Technology", true, false, 4));
    computerSemester8.addCourse(Course("EYI9", "Constraint Programming", true, false, 4));
    computerSemester8.addCourse(Course("E33", "Embedded Systems", true, false, 4));
    semesters.push_back(computerSemester8);

    Semester telecomSemester8(8, 7, "Telecommunications and Networks");
    telecomSemester8.addCourse(Course("Y6", "Optical Communications and Networks", true, false, 4));
    telecomSemester8.addCourse(Course("Y11", "Computer and Network Security", true, false, 4));
    telecomSemester8.addCourse(Course("Y5", "Mobile Communication Networks", true, false, 4));
    telecomSemester8.addCourse(Course("E14", "Wireless Sensor Networks", true, false, 4));
    telecomSemester8.addCourse(Course("E37", "Telecommunication Traffic Theory and Management", true, false, 4));
    telecomSemester8.addCourse(Course("E49", "Optics", true, false, 4));
    telecomSemester8.addCourse(Course("ETH11", "Big Data and Intelligent IoT Applications", true, false, 4));
    semesters.push_back(telecomSemester8);

    Semester energySemester8(8, 7, "Energy");
    energySemester8.addCourse(Course("EEH1", "Renewable Energy Sources", true, false, 4));
    energySemester8.addCourse(Course("EEH18", "High Voltage I", true, false, 4));
    energySemester8.addCourse(Course("EEH7", "Power Electronics II", true, false, 4));
    energySemester8.addCourse(Course("EEH8", "Special Topics in Power Systems", true, false, 4));
    energySemester8.addCourse(Course("EEH9", "Electromechanical Installations and Energy Analysis of Buildings", true, false, 4));
    energySemester8.addCourse(Course("EEH10", "Energy Economics and Markets", true, false, 4));
    energySemester8.addCourse(Course("EEH19", "Hydraulic and Pneumatic Power Systems I", true, false, 4));
    semesters.push_back(energySemester8);

    Semester computerSemester9(9, 7, "Computer");
    computerSemester9.addCourse(Course("E23", "Advanced Topics in Digital Design", true, false, 4));
    computerSemester9.addCourse(Course("YH2", "Design and Operation of Computer Networks", true, false, 4));
    computerSemester9.addCourse(Course("MK35", "Web Programming", true, false, 4));
    computerSemester9.addCourse(Course("E17", "Digital Image Processing", true, false, 4));
    computerSemester9.addCourse(Course("E10", "Complexity Theory", true, false, 4));
    computerSemester9.addCourse(Course("E11", "Data Mining", true, false, 4));
    computerSemester9.addCourse(Course("E24", "Mobile Computing", true, false, 4));
    semesters.push_back(computerSemester9);

    Semester telecomSemester9(9, 7, "Telecommunications and Networks");
    telecomSemester9.addCourse(Course("YH2", "Design and Operation of Computer Networks", true, false, 4));
    telecomSemester9.addCourse(Course("Y9", "Microwave Communications", true, false, 4));
    telecomSemester9.addCourse(Course("E35", "Management and Optimization of Communication Networks", true, false, 4));
    telecomSemester9.addCourse(Course("E3", "Next-Generation Networks and Services", true, false, 4));
    telecomSemester9.addCourse(Course("E5", "Micro- and Nanotechnology", true, false, 4));
    telecomSemester9.addCourse(Course("E11", "Data Mining", true, false, 4));
    telecomSemester9.addCourse(Course("E24", "Mobile Computing", true, false, 4));
    semesters.push_back(telecomSemester9);

    Semester energySemester9(9, 7, "Energy");
    energySemester9.addCourse(Course("YEH4", "Industrial Electrical Installations", true, false, 4));
    energySemester9.addCourse(Course("EEH24", "Photovoltaic Systems and Applications", true, false, 4));
    energySemester9.addCourse(Course("EEH11", "Electric Drive Systems", true, false, 4));
    energySemester9.addCourse(Course("EEH23", "Special Topics in Power Electronics", true, false, 4));
    energySemester9.addCourse(Course("EEH15", "Introduction to Smart Grids", true, false, 4));
    energySemester9.addCourse(Course("EEH21", "Stability and Protection of Power Systems", true, false, 4));
    energySemester9.addCourse(Course("EEH16", "Energy Storage Technologies", true, false, 4));
    semesters.push_back(energySemester9);

}