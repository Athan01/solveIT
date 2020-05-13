#pragma once
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "util.h"
#include "repo.h"

using namespace std;

enum results
{
	correct,
	incorrect,
	timeout
};

class problem
{
	

	vector<string>solutions;
public:
	file& path;
	file& path_req;
	string name;

private:

public:
	problem(file& problem);
	vector<string>get_solutions();
	results check(std::string& solution);
};

extern string working_dir;

