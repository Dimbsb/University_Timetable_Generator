#include <iostream>

#include <vector>

#include "Semester.h"

#include "Course.h"

void initializeCourses(vector < Semester > & semesters) {

    Semester semester1(1, 7);
    semester1.addCourse(Course("MKH3", "Mechanics", "Lecture", "Y"));
    semester1.addCourse(Course("MK1", "Mathematical Analysis I", "Lecture", "Y"));
    semester1.addCourse(Course("MK2", "Linear Algebra", "Lecture", "Y"));
    semester1.addCourse(Course("MK4-H", "Structured Programming", "Lecture", "Y"));
    semester1.addCourse(Course("MK9", "Digital Design", "Lecture", "Y"));
    semester1.addCourse(Course("MKH2", "Design", "Lecture", "Y"));
    semester1.addCourse(Course("MK7", "English", "Lecture", "Y"));
    semesters.push_back(semester1);

    Semester semester2(2, 6);
    semester2.addCourse(Course("MK8", "Mathematical Analysis II", "Lecture", "Y"));
    semester2.addCourse(Course("MK18-H", "Electrical Circuits I", "Lecture", "Y"));
    semester2.addCourse(Course("MK12", "Discrete Mathematics", "Lecture", "Y"));
    semester2.addCourse(Course("MKH1", "Electrical Materials", "Lecture", "Y"));
    semester2.addCourse(Course("MK16", "Probability and Statistics", "Lecture", "Y"));
    semester2.addCourse(Course("MK10", "Object-Oriented Programming I", "Lecture", "Y"));
    semesters.push_back(semester2);

    Semester semester3(3, 6);
    semester3.addCourse(Course("MKH4", "Electrical Measurements", "Lecture", "Y"));
    semester3.addCourse(Course("MK15", "Applied Mathematics I", "Lecture", "Y"));
    semester3.addCourse(Course("MK17", "Algorithms & Data Structures", "Lecture", "Y"));
    semester3.addCourse(Course("MKH5", "Electrical Circuits II", "Lecture", "Y"));
    semester3.addCourse(Course("MK6", "Introduction to Telecommunications", "Lecture", "Y"));
    semester3.addCourse(Course("E26", "Thermodynamics", "Lecture", "Y"));
    semesters.push_back(semester3);

    Semester semester4(4, 7);
    semester4.addCourse(Course("MK21", "Applied Mathematics II", "Lecture", "Y"));
    semester4.addCourse(Course("MK3", "Electromagnetism", "Lecture", "Y"));
    semester4.addCourse(Course("MK23", "Signals and Systems Theory", "Lecture", "Y"));
    semester4.addCourse(Course("MK26-H", "Numerical Analysis", "Lecture", "Y"));
    semester4.addCourse(Course("MK25", "Electronics I", "Lecture", "Y"));
    semester4.addCourse(Course("MK14", "English II (Academic Skills)", "Lecture", "Y"));
    semester4.addCourse(Course("MK11", "Telecommunication Networks", "Lecture", "Y"));
    semesters.push_back(semester4);

    Semester semester5(5, 6);
    semester5.addCourse(Course("MKH8", "Economic-Technical Analysis", "Lecture", "Y"));
    semester5.addCourse(Course("MKH7", "Introduction to Electric Power Systems", "Lecture", "Y"));
    semester5.addCourse(Course("MK27", "Electromagnetic Waves", "Lecture", "Y"));
    semester5.addCourse(Course("MK28", "Digital Signal Processing", "Lecture", "Y"));
    semester5.addCourse(Course("MK30", "Electronics II", "Lecture", "Y"));
    semester5.addCourse(Course("MK20", "Computer Architecture", "Lecture", "Y"));
    semesters.push_back(semester5);

    Semester semester6(6, 6);
    semester6.addCourse(Course("MK29-H", "Communication Systems", "Lecture", "Y"));
    semester6.addCourse(Course("MK38", "Databases", "Lecture", "Y"));
    semester6.addCourse(Course("MK19-H", "Computer Networks", "Lecture", "Y"));
    semester6.addCourse(Course("Y4-H", "Automatic Control Systems I", "Lecture", "Y"));
    semester6.addCourse(Course("E22", "Microprocessors", "Lecture", "Y"));
    semester6.addCourse(Course("MKH9", "Electric Machines I", "Lecture", "Y"));
    semesters.push_back(semester6);

}

int main() {
    vector < Semester > semesters;
    initializeCourses(semesters);

    int selectedSemesterId;
    cout << "Enter the semester ID to view courses: ";
    cin >> selectedSemesterId;

    for (const auto & semester: semesters) {
        if (semester.getId() == selectedSemesterId) {
            cout << "Semester ID: " << semester.getId() << endl;
            cout << "Courses in Semester:" << endl;
            const vector < Course > & courses = semester.getCourses();
            for (const Course & course: courses) {
                cout << "  Course ID: " << course.getId() <<
                    ", Name: " << course.getName() <<
                    ", Type: " << course.getType() <<
                    ", Field of Studies: " << course.getFieldofStudies() << endl;
            }
            break;
        }
    }

    return 0;
}