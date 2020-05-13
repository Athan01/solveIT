#pragma once
#include "repo.h"
class client_profile
{
	string username;
	
	repo* profile = nullptr;

	repo* tree = &root;
	file* tree_file = nullptr;
	bool logged = 0;
public:

public:
	/// <summary>
	/// returns -1 if it found a file
	/// return 0 if it cannot advance in the tree
	/// returns 1 if it found a file;
	/// </summary>
	char advance(string local_path);
	void go_back(string local_path);

	void log(repo* profile_repo);


	repo& get_repo() { return *tree; }
	file& get_file() { if (tree_file)return *tree_file; return nullfile; }
	client_profile(int id){}
};

