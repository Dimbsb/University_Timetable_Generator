#include "Professor.h"
#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

Professor::Professor () {}
Professor::Professor (string profName1, vector<int> coursesCodes1, int anavailability1[5][2])
{
	profName=profName1;
	coursesCodes=coursesCodes1;
	for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 2; ++j) {
            anavailability[i][j] = anavailability1[i][j];
        }
    }
}
string Professor::getProfName()
{
	return profName;
}
vector<int> Professor::getCourseCodes()
{
	return coursesCodes;
}
vector<pair<int, int> > Professor::getAnavailability() {
    vector<pair<int, int> > availabilityList;
    for (int i = 0; i < 5; ++i) {
        availabilityList.push_back(make_pair(anavailability[i][0], anavailability[i][1]));
    }
    return availabilityList;
}
