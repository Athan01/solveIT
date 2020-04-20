#include "database.h"

database::database(const string file)
{
	ifstream in(file.c_str());

	string user_buff, pass_buff;
	while (in >> user_buff >> pass_buff)
	{
		users.push_back(pair<string, string>(user_buff, pass_buff));
	}
	in.close();

	in.open("blacklist.txt");

	
	while (in >> user_buff)
	{
		blacklist.push_back(user_buff);
	}
	in.close();
}

// -1 user not found, 0 password wrong, 1 login successful
char database::login(const string username, const string password)
{
	for (short i = 0; i < users.size(); i++)
	{
		
		if (users[i].first == username)
		{
			if (users[i].second == password)
				return 1;
			else return 0;
		}
	}
	return -1;
}

bool database::is_blacklisted(const string ip_adress)
{
	// check clocks
	for (unsigned int i=0;i<temp_bans.size();i++)
		if (temp_clocks[i].getElapsedTime().asSeconds() > temp_bans[i].first)
		{
			temp_bans.erase(temp_bans.begin() + i);
			temp_clocks.erase(temp_clocks.begin() + i);
		}


	for (unsigned int i = 0; i < blacklist.size(); i++)
		if (blacklist[i] == ip_adress)
			return 1;
	for (unsigned int i = 0; i < temp_bans.size(); i++)
		if (temp_bans[i].second == ip_adress)
			return 1;

	return 0;
}

void database::temp_ban(const string ip, float time)
{
	temp_bans.push_back(pair<float, string>(time, ip));
	temp_clocks.push_back(Clock());
}

void database::add_to_blacklist(const string ip_adress)
{
	fstream out("blacklist.txt",ios::out|ios::in);
	// check repeats
	string buffer;
	bool found = 0;
	while (out >> buffer)
	{
		if (buffer == ip_adress)
		{
			found = 1;
			break;
		}
	}
	out.clear();
	if (!found)
	{
		out.seekg(0,ios::end);
		out << ip_adress << '\n';
		blacklist.push_back(ip_adress);
	}
	out.close();
}

void database::remove_blacklisted(const string ip)
{
	ifstream list("blacklist.txt");
	ofstream list2("blacklist2.txt");
	string buff;
	bool found = 0;
	while (list >> buff)
	{
		if (buff != ip)
		{
			list2 << buff;
			found = 1;
		}
	}

	
	
	list.close();
	list2.close();

	if (found)
	{
		remove("blacklist.txt");
		rename("blacklist2.txt", "blacklist.txt");
	}
	else
	{
		cout << ip << " not blacklisted\n";
	}
	

}
