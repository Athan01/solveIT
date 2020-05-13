#pragma once
#include "menus.h"

namespace gui = ImGui;

class popup {
public:
	static int id;
	string name;
	string message;
	bool closed = 0;
	popup(const string message) : message(message) { name = istr(id); id++; }
	void run();
};

class menu
{
	std::string menu_name;
	popup* current_popup = nullptr;
	void (*setup)();
public:
	menu(void (*setup)(),std::string menu_name="ERROR_NO_WINDOW_NAME") : setup(setup),menu_name(menu_name){}
	void create_popup(const std::string pop_message);
	void run();
};

extern map<int, menu*>menus;


