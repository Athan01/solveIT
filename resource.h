#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Network/Packet.hpp>
#include "util.h"
using namespace std;
using sf::Texture;

extern map<string, string>strings;
extern map<string, int>integers;
extern map<string, float>floats;
extern map<string, short>shorts;
extern map<string, bool>booleans;
extern map<string, Texture>textures;
struct chr
{
	char* ptr = nullptr;
	size_t size;
	chr(){}
	chr(const string copy);
	~chr();
	void operator=(const string val);
	// MEMORY LEAK
	void resize(const size_t newsize) {  ptr = new char[newsize](); size = newsize; }
};

sf::Packet& operator<<(sf::Packet& out, chr& a);
extern map<string, chr>arrays;

string& create_string(const string name, string value = "");
int& create_int(const string name, int value = 0);
float& create_float(const string name, float value = 0.f);
bool& create_bool(const string name, bool value = 0);
chr& create_array(const string name, string value = "");
Texture& create_texture(const string name, const string filename);

string& find_str(const string name);
int& find_int(const string name);
float& find_float(const string name);
bool& find_bool(const string name);
chr& find_array(const string name); 
Texture& find_texture(const string name);

void basic_resources();