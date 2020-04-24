#pragma once
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#define DELAY 10

using namespace sf;
using namespace std;

enum types
{
	numerical,
	username,
	ip
};

extern std::time_t t;
extern std::tm* now;
extern std::string current_time;
extern bool closed;
void update_time();

int load_file(const std::string filename, std::string &out);

unsigned int send_image(const std::string filename, std::string& out);

string split(std::string& a);

string istr(const int a);

string fstr(const float a);

int stri(string a);

float strf(string a);

TCHAR* tchar(string& a);

