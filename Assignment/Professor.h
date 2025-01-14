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
		string ProfessorName;
		vector<int> coursesCodes;
		int unavailability[5][2];
	public:
		Professor ();
		Professor (string ProfessorName, vector<int> coursesCodes, int unavailability[5][2]);
		string getProfessorName();
		vector<int> getCourseCodes();
		vector<pair<int, int> > getunavailability();
};

#endif