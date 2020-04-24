#pragma once
#include "menus.h"

namespace gui = ImGui;

struct popup {
	static int id;
	string name;
	string message;
	bool closed;
	popup(const string message) : message(message) { name = istr(id); id++; }
	void run();
};

class menu
{
	std::string menu_name;
	popup* current_popup = nullptr;
	void (*setup)();
	short id;
	int& id_ref;
	
public:
	menu(void (*setup)(),const short id=0,std::string menu_name="ERROR_NO_WINDOW_NAME") : setup(setup), id(id),menu_name(menu_name),id_ref(find_int("state")){}
	void create_popup(const std::string pop_message);
	void run();
};

extern map<int, menu>menus;


