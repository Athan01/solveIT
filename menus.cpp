#include "menus.h"


void bar()
{
	static bool pop = 0;
	SetWindowFontScale(3);
	if (BeginMenuBar())
	{
		if (BeginMenu("menus"))
		{
			if (MenuItem("profile"))
			{
				create_request('d');
				find_int("state") = 3;
			}
			if (MenuItem("finished problems"))
			{
				rankings.clear();
				create_request('d');
				find_int("state") = 7;
			}
			if (MenuItem("problems"))
			{
				find_int("state") = 4;
			}
			if (MenuItem("EXIT"))
			{
				pop = 1;
			}
			EndMenu();
		}
		
		EndMenuBar();
	}
	if (pop)
	{
		OpenPopup("exit?");
		if (BeginPopup("exit?"))
		{
			ImGui::Text("Are you sure you want to quit?");

			if (Button("yes"))
				exit(0);
			SameLine();
			if (Button("no"))
			{
				pop = 0;
				CloseCurrentPopup();
			}
			EndPopup();
		}
	}
}

void menu0()
{
	if (Button("close"))
		exit(0);
	SetWindowFontScale(2.5);
	//static char* loading = create_array("...", "connecting...").ptr;
	static sf::Clock wait;
	Indent(250);
	Dummy(ImVec2(0, 200));
	if (wait.getElapsedTime().asSeconds() < 1)
		LabelText("a", "connecting.");
	else if (wait.getElapsedTime().asSeconds() > 6)
	{
		LabelText("a", "connecting.");
		wait.restart();
	}
	else if (wait.getElapsedTime().asSeconds() > 5)
		LabelText("a", "connecting..");
	else if (wait.getElapsedTime().asSeconds() > 4)
		LabelText("a", "connecting...");
	else if (wait.getElapsedTime().asSeconds() > 3)
		LabelText("a", "connecting....");
	else if (wait.getElapsedTime().asSeconds() > 2)
		LabelText("a", "connecting...");
	else if (wait.getElapsedTime().asSeconds() > 1)
		LabelText("a","connecting..");

}

void menu1()
{
	
	static bool see_pass = 0;
	static char* user = find_array("username").ptr;
	static char* pass = find_array("password").ptr;

	

	SetWindowFontScale(2.5);
	InputTextWithHint("username","username", user, 19);
	if (!see_pass)
		InputTextWithHint("password","password", pass, 19,ImGuiInputTextFlags_Password);
	else
	{
		InputTextWithHint("password","password", pass, 19);
	}
	SameLine(640);
	Checkbox("x", &see_pass);
	
	

	Spacing();
	Dummy(ImVec2(0.0f, 100));
	Indent(250);
	
	if (Button("login"))
	{
		
		string *u = new string(user);
		string *p = new string(pass);

		create_request('l');
		find_of_type('l')->load_in_position(u,0,'s');
		find_of_type('l')->load_in_position(p, 1, 's');

		//find_of_type('l')->set_types({ 's','s' });
	}
	Dummy(ImVec2(0, 100));
	if (Button("register"))
	{
		find_int("state") = 2;
	}

	
	//PopStyleColor();
}

void menu2()
{
	SetWindowFontScale(2.5);
	static bool see_pass = 0;
	Indent(50);
	if (Button("go to login"))
	{
		find_int("state") = 1;
	}
	Dummy(ImVec2(0, 100));
	static char* user = find_array("username").ptr;
	static char* pass = find_array("password").ptr;

	InputTextWithHint("username", "username", user, 19);
	if (!see_pass)
		InputTextWithHint("password", "password", pass, 19, ImGuiInputTextFlags_Password);
	else
	{
		InputTextWithHint("password", "password", pass, 19);
	}
	Indent(250);
	Checkbox("x", &see_pass);
	if (Button("register"))
	{
		create_request('r');
		string* u = new string(user);
		string* p = new string(pass);
		find_of_type('r')->load_in_position(u, 0, 's');
		find_of_type('r')->load_in_position(p, 1, 's');
		//find_of_type('l')->set_types({ 's','s' });
	}
	
}

void menu3()
{
	static Texture& t = find_texture("points");
	bar();
	LabelText("", "profile: ");
	SameLine();
	LabelText("", profile.username.c_str());

	LabelText("", "total points: ");
	SameLine();
	LabelText("", istr(profile.points).c_str());
	ImGui::Image(find_texture(istr(profile.pfp)));
	
	
	
	
}
void menu4()
{
	SetWindowFontScale(3);
	bar();
	static string points = istr(find_int("points"));

	string path_cpy = profile.current_path;
	string cpy;
	NewLine();
	do
	{
		SameLine();
		cpy = path_cpy.substr(0, path_cpy.find('\\'));
		if (Button(cpy.c_str()))
		{
			create_request('b');
			find_str("back") = cpy;
			find_of_type('b')->load_in_position(&find_int("dir_back"), 0, 'i');
			find_of_type('b')->load_in_position(&find_str("back"), 1, 's');
		}
		path_cpy.erase(0, path_cpy.find('\\') + 1);

	} while (cpy != path_cpy);



	NewLine();
	NewLine();

	float sum = 0;
	for (short i = 0; i < profile.files.size(); i++)
	{
		if (sum + CalcTextSize(profile.files[i].c_str()).x + GetStyle().ItemSpacing.x + GetStyle().FramePadding.x < GetWindowWidth())
			SameLine();
		else
		{
			sum = 0;
		}
		if (Button(profile.files[i].c_str()))
		{
			create_request('b');
			find_of_type('b')->load_in_position(&find_int("dir_forward"), 0, 'i');
			find_of_type('b')->load_in_position(&profile.files[i], 1, 's');
		}
		sum += ImGui::GetItemRectSize().x;
	}
}


void menu5()
{
	static auto& ar =find_array("file");
	static string pr;

	SetWindowFontScale(2.5);
	
	if (Button("Go Back"))
	{
		create_request('d');
		find_int("state") = 3;
	}

	NewLine();

	NewLine();

	TextColored(ImVec4(0, 1.f, 0.5, 255), problem.title.c_str());
	TextWrapped(problem.requirement.c_str());
	cout << find_bool("file_loaded");
	if (find_bool("file_loaded"))
	{
		if (Button("send"))
		{
			pr = ar.ptr;
			create_request('p');
			find_of_type('p')->load_in_position(&problem.title, 0, 's');
			find_of_type('p')->load_in_position(&pr, 1, 's');
			
			
			find_bool("file_loaded") = 0;
		}
	}
	if (problem.finished)
	{
		ImGui::Text(problem.result.c_str());
	}

}


void menu6()
{
	//bar();
	
	SetWindowFontScale(1.5);
	static bool& start = find_bool("started");
	static bool finished = 0;
	static string res = "You got " + istr(quiz.percentage()) + "%";
	if (!start)
		if (Button("start"))
		{
			start = 1;
			finished = 0;
			quiz.start();
		}

	if (start)
	{
		//Indent(150);
		ImGui::LabelText("",quiz.title.c_str());
		SameLine();
		ImGui::Text(cstr(*quiz.timer).c_str());
		NewLine();
		for (short i = 0; i < quiz.question.size(); i++)
		{
			NewLine();
			ImGui::TextWrapped(quiz.question[i].c_str());
			
			for (short j = 0; j < 4; j++)
			{
				if (!finished)
					ImGui::Text(quiz.answers[i][j].c_str());
				if (finished)
				{
					if (quiz.answers[i][j] == quiz.right_answer[i])
						ImGui::TextColored(ImVec4(0,0.8,0.4,1),quiz.answers[i][j].c_str());
					else
					{
						ImGui::TextColored(ImVec4(1, 0, 0.1, 1), quiz.answers[i][j].c_str());
					}
				}
					

				SameLine();
				if (Checkbox(istr(i*4+j).c_str(),&quiz.buttons[i * 4 + j]))
				{
					for (short j2 = 0; j2 < 4; j2++)
						if (j != j2)
							quiz.buttons[i * 4 + j2] = 0;
					quiz.player_choices[i] = j;
				}

			}
		}
		NewLine();
		if (Button("finish"))
		{
			finished = 1;
			find_int("results") = (int)quiz.percentage();
			res = "You got " + istr(find_int("results")) + '%';
			create_request('q');
			find_of_type('q')->load_in_position(&find_int("results"), 0, 'i');
		}
		if (finished)
		{
			ImGui::Text(res.c_str());
			if (Button("return"))
			{
				finished = 0;
				create_request('d');
				find_int("state") = 3;
			}
				
		}
			
	}
}

void menu7()
{
	bar();
	Columns(2);
	for (short i = 0; i < profile.solved.size(); i++)
		ImGui::Text(profile.solved[i].c_str());
	NextColumn();
	for (short i = 0; i < profile.solved.size(); i++)
		ImGui::Text(istr(profile.scores[i]).c_str());

	NextColumn();
	if (rankings.empty())
	{
		if (Button("show rankings"))
			create_request('c');
	}
	else
	{
		TextColored(ImVec4(1, 0.8, 0, 1), rankings.back().c_str());
		for (short i = rankings.size()-2; i > -1; i--)
		{
			TextColored(ImVec4(1, 0.8, 0, 1), rankings[i].c_str());
		}
	}

}

