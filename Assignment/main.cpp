#include <iostream>
#include "Semester.h"
#include "Course.h"

int main() {
    Semester semester1(1, 2);
    Course c1;     // h na to kanoume me new
    cout << "The number of courses you are allowed to add is: " << semester1.getCapacityofCourses() << endl;

    //Course course1(101, "Mathematics", "Lecture","Energy");

    for(int i=0; i<semester1.getCapacityofCourses(); i++){
        c1.readDataCourse();
        semester1.addCourse(c1);
    }

    if (semester1.getCourses().size()-1 > semester1.getCapacityofCourses()) { //na to do to evala tora logo c1
        cout << "Program terminated...added more courses than allowed." << endl;
        return 0; 
    }

    cout << "Semester ID: " << semester1.getId() << endl;

    cout << "Courses in Semester:" << endl;
    const vector<Course>& courses = semester1.getCourses();
    for (size_t i = 0; i < courses.size(); ++i) {
        const Course& course = courses[i]; 
        cout << "  Course ID: " << course.getId()
             << ", Name: " << course.getName()
             << ", Type: " << course.getType() 
             << ", Type: " << course.getFieldofStudies() << endl;
    }

    return 0;
}