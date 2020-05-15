#pragma once
#include "repo.h"
#include "problem_holder.h"
class client_profile
{
	
	
	repo* profile = nullptr;

	repo* tree = &root;
	file* tree_file = nullptr;
	
	bool logged = 0;
public:
	string username;
	short points;
	short pfp;
	problem* problem_top = nullptr;
	quiz* quiz_top = nullptr;
	vector<string>finished_problems;
	
	vector<string>finished_quizes;
	// scores for finished_problems start at 0 and scores for finished quizes start at finished_problems.size()
	vector<short>scores;
public:
	/// <summary>
	/// returns -1 if it found a file
	/// return 0 if it cannot advance in the tree
	/// returns 1 if it found a file;
	/// </summary>
	char advance(string local_path);
	void go_back(string local_path);

	void log(repo* profile_repo);
	void finish_problem();
	void finish_quiz(int perc);


	repo& get_repo() { return *tree; }
	file& get_file() { if (tree_file)return *tree_file; return nullfile; }
	client_profile(int id){}
	~client_profile();
};

