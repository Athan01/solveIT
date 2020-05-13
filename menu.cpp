#include "menu.h"
#include <iostream>

map<int, menu*>menus;

int popup::id;

void menu::create_popup(const std::string pop_message)
{
	if (current_popup != nullptr)
	{
		delete current_popup;
	}
	current_popup = new popup(pop_message);
}

void menu::run()
{
	//PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2, 0.8, 0.2, 1));
	gui::Begin(menu_name.c_str(), 0,ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoTitleBar);
	setup(); 
	if (current_popup != nullptr && !current_popup->closed)
		current_popup->run();
	gui::End();
}

void popup::run()
{
	OpenPopup(name.c_str());
	BeginPopup(name.c_str());
	ImGui::Text(message.c_str());
	if (Button("close"))
	{
		CloseCurrentPopup();
		closed = 1;
	}
	EndPopup();
	
}
