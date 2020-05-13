#include "menus.h"


void bar()
{
	SetWindowFontScale(3);
	if (BeginMenuBar())
	{
		if (BeginMenu("menus"))
		{
			if (MenuItem("profile"))
			{
				find_int("state") = 3;
			}
			if (MenuItem("problems"))
			{
				find_int("state") = 4;
			}
			
			EndMenu();
		}
		
		EndMenuBar();
	}
}

void menu0()
{
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
		create_request('l');
		string *u = new string(user);
		string *p = new string(pass);
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
	bar();
	
	
	
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
	static auto ar =find_array("problem");
	static string pr;

	SetWindowFontScale(2.5);
	
	Button("Go Back");

	NewLine();

	NewLine();

	TextColored(ImVec4(201, 180, 34, 255), problem.title.c_str());
	TextWrapped(problem.requirement.c_str());

	if (Button("send"))
	{
		pr.clear();
		pr.append(ar.ptr);
		create_request('p');
		find_of_type('p')->load_in_position(&problem.title, 0, 's');
		find_of_type('p')->load_in_position(&pr, 1, 's');
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
	static string res = "You got " + istr(quiz.percentage());
	if (!start)
		if (Button("start"))
		{
			start = 1;
			finished = 0;
			quiz.start();
		}

	if (start)
	{
		Indent(150);
		ImGui::LabelText("",quiz.title.c_str());
		SameLine();
		ImGui::Text(cstr(*quiz.timer).c_str());
		Unindent();
		NewLine();
		for (short i = 0; i < quiz.question.size(); i++)
		{
			NewLine();
			ImGui::BulletText(quiz.question[i].c_str());
			for (short j = 0; j < 4; j++)
			{
				ImGui::Text(quiz.answers[i][j].c_str());
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
		
			find_int("results") = quiz.percentage();
			res = "You got " + istr(quiz.percentage());
			create_request('q');
			find_of_type('q')->load_in_position(&find_int("results"), 0, 'i');

			
		}
		if (finished)
		{
			ImGui::Text(res.c_str());
			if (Button("return"))
				find_int("state") = 3;
		}
			
	}
}

