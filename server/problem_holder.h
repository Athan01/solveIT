#pragma once
#include "problem.h"
#include "quiz.h"
class problem_holder
{
	vector<problem*>problems;
	vector<quiz*>quizes;

public:
	problem* problem_top = nullptr;
	quiz* quiz_top = nullptr;
public:
	problem_holder();
	/// <summary>
	/// returns -1 if it found a problem
	/// returns 0 if it found nothing
	/// returns 1 if it found a quiz 
	/// </summary>
	signed char find_by_file(file& f);
	results check(string& problem_name,string& problem);

};

