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
	results check(string& problem_name, string& problem);
	problem& find_problem(string& problem_name) {for (short i = 0; i < problems.size(); i++) if (problems[i]->name == problem_name)return *problems[i]; }
	quiz& find_quiz(string& quiz_name) { for (short i = 0; i < quizes.size(); i++) if (quizes[i]->title == quiz_name)return *quizes[i]; }

};

