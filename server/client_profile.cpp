#include "client_profile.h"


char client_profile::advance(string local_path)
{
	if (local_path.find('.') != string::npos)
	{
		file& file = tree->get_file(local_path);
		if (&file != &nullfile)
		{
			tree_file = &file;
		}
		return -1;
	}

	else
	{
		repo& rep = tree->get_repo(local_path);
		if (&rep != &nullrepo)
		{
			tree = &rep;
			return 1;
		}
		
	}
	return 0;
	
}

void client_profile::go_back(string local_path)
{
	tree = &root.find_by_name(local_path);
}

void client_profile::log(repo* profile_repo)
{
	profile = profile_repo;
	logged = 1;

	string buffer;
	ifstream in(profile->get_file("basic.txt").path);
	in >> username;
	in >> buffer;
	in >> points;
	in >> pfp;
	in.close();

	in.open(profile->get_file("history.txt").path);
	short scor;
	while (in >> buffer)
	{
		in >> scor;
		if (buffer.substr(0, 2) == "pr")
		{
			finished_problems.push_back(buffer);
			scores.insert(scores.begin(),finished_problems.size(), { scor });
		}
		else
		{
			finished_quizes.push_back(buffer);
			scores.push_back(scor);
		}
	}
	in.close();

}

void client_profile::finish_problem()
{
	bool found = 0;

	cout << "S FOR " << problem_top->name;

	if (problem_top != nullptr)
	{
		for (short i = 0; i < finished_problems.size(); i++)
			if (finished_problems[i] == problem_top->name)
			{
				found = 1;
				cout << " O " << finished_problems[i];
				scores[i] = problem_top->reward;
				break;
			}
		if (!found)
		{
			finished_problems.push_back(problem_top->name);
			scores.push_back(problem_top->reward);
			this->points += problem_top->reward;
		}

		problem_top = nullptr;
	}
	

}

void client_profile::finish_quiz(int percentage)
{
	static short diff;
	bool found = 0;
	if (quiz_top != nullptr)
	{
		for (short i = 0; i < finished_quizes.size(); i++)
			if (finished_quizes[i] == quiz_top->title)
			{
				diff =  percentage - scores[finished_problems.size() + i];
				scores[finished_problems.size() + i] =  percentage;
				found = 1;
				break;
			}
		if (!found)
		{
			this->points += (quiz_top->reward * percentage) / 100;
			finished_quizes.push_back(quiz_top->title);
			scores.insert(scores.begin() + finished_problems.size(), percentage);
		}
		else
		{
			if (diff > 0)
				this->points += diff/100 * quiz_top->reward;
		}
				
		
		quiz_top = nullptr;
	}
	

}

client_profile::~client_profile()
{
	
	if (logged)
	{
		cout << "BAGA MARSALIER";
		string buff;
		ifstream in(profile->get_file("basic.txt").path);
		in >> buff; in >> buff;
		in.close();
		ofstream out(profile->get_file("basic.txt").path);
		out << username << ' ' << buff << ' ' << points << ' ' << pfp;
		out.close();

		ofstream bout(profile->get_file("history.txt").path);
		for (short i = 0; i < finished_problems.size(); i++)
		{
			cout << finished_problems[i];
			bout << finished_problems[i] << ' ' << scores[i] << '\n';
		}
		for (short i = 0; i < finished_quizes.size(); i++)
		{
			cout << finished_quizes[i];
			bout << finished_quizes[i] << ' ' << scores[finished_problems.size() + i] << '\n';
		}
		
		bout.close();
	}
}

