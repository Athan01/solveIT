#include "response.h"
response_interpretor responses;


void response_interpretor::login_response(Packet& pack)
{
	Int8 ans;
	pack >> ans;
	cout << (int)ans;
	switch (ans)
	{
	case -1:
		menus[find_int("state")]->create_popup("login failed user not found");
		break;
	case 0:
		menus[find_int("state")]->create_popup("login failed password wrong");
		break;
	case 1:
		menus[find_int("state")]->create_popup("login succesful");
		find_bool("logged") = 1;
		break;
	}
}

void response_interpretor::register_response(Packet& pack)
{
	Int8 ans;
	pack >> ans;
	switch (ans)
	{
	case -1:
		menus[find_int("state")]->create_popup("register failed password wrong");
	case 0:
		menus[find_int("state")]->create_popup("register failed username already in use");
		break;
	case 1:
		/*menus[find_int("state")]->create_popup("registration succesful");*/
		find_bool("logged") = 1;
		break;
	}
}

void response_interpretor::browser_response(Packet& pack)
{
		string buffer;
		profile.files.clear();
		pack >> profile.current_path;
		cout << profile.current_path << " ";
		while (pack >> buffer)
		{
			profile.files.push_back(buffer);
			cout << buffer << " ";
		}
}

void response_interpretor::file_response(Packet& pack)
{
	string filename;
	string file;
	pack >> filename;
	ofstream out(filename.c_str());
	pack >> file;

	file.erase(file.end());
	out << file;

	
	
	out.close();
	string cmd = "start " + filename;
	system(cmd.c_str());
}


void response_interpretor::handle_response(Packet& pack)
{
	static Uint8 type;
	pack >> type;
	cout << type;
	switch (type)
	{
	case 'l':
		login_response(pack);
		break;
	case 'r':
		register_response(pack);
		break;
	case 'b':
		browser_response(pack);
		break;
	case 'f':
		file_response(pack);
		break;
	case 'p':
		problem_response(pack);
		break;
	case 'q':
		quiz_response(pack);
		break;
	case 's':
		score_response(pack);
		break;
	case 'd':
		data_response(pack);
		break;
	case 'i':
		image_response(pack);
		break;
	case 'c':
		ranking_response(pack);
		break;

	}
}

void response_interpretor::problem_response(Packet& pack)
{
	find_int("state") = 5;
	find_array("problem");
	pack >> problem.title;
	string buffer;
	while (pack >> buffer)
	{
		problem.requirement += buffer;
	}
}

void response_interpretor::quiz_response(Packet& pack)
{
	find_int("state") = 6;
	quiz.load_quiz(pack);
	
}

void response_interpretor::score_response(Packet& pack)
{
	problem.finished = 1;
	Uint8 result;
	pack >> result;
	if (result == 0)
	{
		problem.result = "Correct";
	}
	else if (result == 1)
	{
		problem.result = "Incorrect";
	}
	else
	{
		problem.result = "Time out";
	}
}

void response_interpretor::data_response(Packet& pack)
{
	pack >> profile.username;
	pack >> profile.points;
	cout << "NEW P";
	cout << profile.points;
	profile.solved.clear();
	profile.scores.clear();
	do
	{
		profile.solved.push_back({});
		profile.scores.push_back({});
	} while (pack >> profile.solved.back() >> profile.scores.back());
	profile.solved.pop_back();
	profile.scores.pop_back();
}

void response_interpretor::image_response(Packet& pack)
{
	pack >> profile.pfp;
	cout << "IMAGE" << profile.pfp;
}

void response_interpretor::ranking_response(Packet& pack)
{
	rankings.clear();
	string buff;
	while (pack >> buff)
	{
		rankings.push_back(buff);
	}
}

bool response_interpretor::bad(Packet& pack, Uint8 type)
{
	if (pack.getDataSize() > 3)
	{
		return 1;
	}
	else
	{
		cout << "Bad packet of type " + type + '\n';
		create_request(type);
		*find_of_type(type) = *find_archived(type);
		return 0;
	}

}
