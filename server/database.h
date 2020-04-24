#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <SFML/System/String.hpp>
#include <SFML/System/Clock.hpp>
#include "repo.h"
using namespace std;
using namespace sf;
class database
{
	map<string, string>users;
	map<string, int>user_repo;
	// CHANGE TO MAP
	vector<pair<float, string> >temp_bans;
	vector<Clock> temp_clocks;
	vector<string>blacklist;
	repo *accounts;
public:

private:
	
public:
	database();
	/// <summary>
	///-1 user not found, 0 password wrong, 1 login successful
	/// </summary>
	char login(const string username, const string password); 
	/// <summary>
	/// returns the repo associated with the username in the std::map user_repo
	///</summary>
	repo* get_associated_repo(const string username);

	bool is_blacklisted(const string ip_adress);
	void temp_ban(const string ip, float time);
	void add_to_blacklist(const string ip_adress);
	void add_user(const string username, const string password);
	void remove_blacklisted(const string ip);
};

