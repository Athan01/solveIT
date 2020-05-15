#include "database.h"

database::database()
{
	accounts = new repo("C:\\Users\\ioanm\\Desktop\\root\\accounts");
	string user;
	string pass;
	for (int i = 0; i < accounts->subrepos.size(); i++)
	{
		string& a = accounts->get_file("accounts:" + istr(i) + ":basic.txt").path;
		ifstream in(a.c_str());
		
		in >> user >> pass;
		users[user] = pass;
		user_repo[user] = i;
		in.close();
	}
}


signed char database::login(const string username, const string password)
{
	if (users.find(username) == users.end())
		return -1;
	else if (users[username] != password)
		return 0;
	else return 1;
}

repo* database::get_associated_repo(const string username)
{
	return &accounts->get_repo("accounts:" + istr(user_repo[username]));;
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

signed char database::add_user(const string username, const string password)
{

	// check if chr valid maybe?

	if (users.count(username) == 0)
	{
		cerr << current_time << username + " registered with password " + password << '\n';
		repo& a = accounts->add_repo(istr(accounts->subrepos.size()));
		file& b = a.add_file("basic.txt", 0);
		b.content += username + ' ' + password + '\n' + '0' + ' ' + '1';
		users[username] = password;
		user_repo[username] = users.size() - 1;
		b.write();
		a.add_file("history.txt");
		return 1;
	}
	else
	{
		return 0;
	}

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
}
