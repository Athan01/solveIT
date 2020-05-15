#pragma once
#include "resource.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "connection.h"
#include "trigger_manager.h"
#include "profile.h"
using namespace ImGui;
using namespace std;

void bar();

// connecting menu
void menu0();
// login menu
void menu1();
// register menu
void menu2();
// profile menu
void menu3();
// problem finder menu
void menu4();
// problem solver menu
void menu5();
// quiz solver menu
void menu6();
// problem viewing menu
void menu7();



