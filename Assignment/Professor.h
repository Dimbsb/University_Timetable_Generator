#ifndef PROFESSOR_H
#define PROFESSOR_H
#include<iostream>
#include<string>
#include <utility>
#include <vector>
using namespace std;

class Professor
{
	private:
		string profName;
		vector<int> coursesCodes;
		int anavailability[5][2];
	public:
		Professor ();
		Professor (string profName, vector<int> coursesCodes, int anavailability[5][2]);
		string getProfName();
		vector<int> getCourseCodes();
		vector<pair<int, int> > getAnavailability();
};

#endif
