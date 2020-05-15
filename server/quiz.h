#pragma once
#include "util.h"
#include "repo.h"
struct question
{
	string enunciation;
	string answers[4];

	question() { } 
};

struct quiz
{
	string title;
	short reward;
	vector<question>questions;
	file& path;
	quiz(file& quiz);
};

