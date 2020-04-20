#pragma once
#include "menus.h"
namespace gui = ImGui;
class menu
{
	std::string menu_name;
	void (*setup)();
	short id;
	int& id_ref;
	
public:
	menu(void (*setup)(),const short id=0,std::string menu_name="ERROR_NO_WINDOW_NAME") : setup(setup), id(id),menu_name(menu_name),id_ref(find_int("state")){}
	void run();
};



