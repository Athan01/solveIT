#pragma once
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "util.h"

using namespace std;

class problem
{
	vector<string>solutions;
	const string name;
public:

private:
public:
	problem(const std::string problem_name);
	bool check(const std::string solution);
};

