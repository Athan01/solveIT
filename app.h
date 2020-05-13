#pragma once
#include "SFML/Graphics.hpp"
#include "imgui-SFML.h"
#include <iostream>
#include <Windows.h>
#include "menu.h"

using namespace sf;
class app
{
	RenderWindow win;
	
	
private:
	void load_menus();
	void load_triggers();
	void run();
public:
	app();
	~app(){}
};

