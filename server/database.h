#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <SFML/System/String.hpp>
#include <SFML/System/Clock.hpp>
using namespace std;
using namespace sf;
class database
{
	vector<pair<string, string>>users;
	vector<pair<float, string> >temp_bans;
	vector<Clock> temp_clocks;
	vector<string>blacklist;

public:

private:

public:
	database(const string file);
	char login(const string username, const string password); // -1 for user not found , 0 for pass not found, 1 for ok
	bool is_blacklisted(const string ip_adress);

	void temp_ban(const string ip, float time);
	void add_to_blacklist(const string ip_adress);
	void remove_blacklisted(const string ip);
};

