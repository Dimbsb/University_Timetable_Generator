#include "Professor.h"
#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

Professor::Professor () {}

Professor::Professor (string ProfessorName, vector<int> coursesCodes, int unavailability[5][2]){
    this->ProfessorName = ProfessorName;
	this->coursesCodes=coursesCodes;

	for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 2; ++j) {
            unavailability[i][j] = unavailability[i][j];
        }
    }
}

string Professor::getProfessorName(){
	return ProfessorName;
}


vector<int> Professor::getCourseCodes(){
	return coursesCodes;
}


vector<pair<int, int> > Professor::getunavailability() {
    vector<pair<int, int> > availabilityList;
    for (int i = 0; i < 5; ++i) {
        availabilityList.push_back(make_pair(unavailability[i][0], unavailability[i][1]));
    }
    return availabilityList;
}