#include "menu.h"
#include <iostream>
void menu::run()
{
	if (id_ref == id)
	{
		//PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2, 0.8, 0.2, 1));
		gui::Begin(menu_name.c_str(), 0,ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoTitleBar);
		setup(); 
		gui::End();
		
	}
	
}
