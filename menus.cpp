#include "menus.h"


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
	
	//PopStyleColor();
}

void menu2()
{

}
