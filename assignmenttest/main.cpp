#include "Professor.h"
#include "Semester.h"
#include "Course.h"
#include "Room.h"
#include "Laboratory.h"
#include "LectureRoom.h"


#include<iostream>
#include<string>
#include <utility>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<Semester> semesters;
    vector<string> coursesCodes;
    vector<Professor> professors;
    vector<LectureRoom> lectureRooms;
    vector<Laboratory> laboratories;

    // Add some lecture rooms
    lectureRooms.push_back(LectureRoom("L101", "Building A", 50, "Lecture Room"));
    lectureRooms.push_back(LectureRoom("L102", "Building B", 75, "Lecture Room"));
    lectureRooms.push_back(LectureRoom("L103", "Building C", 100, "Lecture Hall"));

    // Add some laboratory rooms
    laboratories.push_back(Laboratory("Lab201", "Building A", 30, "Computer Lab1"));
    laboratories.push_back(Laboratory("Lab202", "Building B", 25, "Computer Lab2"));
    laboratories.push_back(Laboratory("Lab203", "Building C", 20, "Computer Lab3"));



    // Define unavailability: Monday (13:00–15:00), Tuesday (14:00–16:00), etc.
    pair<int, int> unavailability1[5] = {
        {13, 15}, // Monday
        {14, 16}, // Tuesday
        {12, 14}, // Wednesday
        {10, 12}, // Thursday
        {9, 11}   // Friday
    };

    pair<int, int> unavailability2[5] = {
        {13, 15}, 
        {14, 16}, 
        {12, 14}, 
        {10, 12}, 
        {9, 11}   
    };

    Professor professor1("Dr. Smith", {"MK1","MK2"}, {unavailability1});
    semesters[0].assignProfessorToCourse("MK1", professor1);
    semesters[0].assignProfessorToCourse("MK2", professor1);
    professors.push_back(professor1);

    Professor professor2("Dr. Johnson", {"MK4-H"}, {unavailability2});
    semesters[0].assignProfessorToCourse("MK4-H", professor2);
    professors.push_back(professor2);

    

    

    return 0;
}
