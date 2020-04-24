#pragma once
#include "repo.h"
class client_profile
{
	string username;
	repo* profile = nullptr;
	bool logged = 0;

public:
	void log(repo* profile_repo);
	client_profile(int id){}
};

