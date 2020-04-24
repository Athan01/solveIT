#pragma once
#include <vector>
#include <SFML/Config.hpp>
#include <iostream>
#include "response.h"
using namespace std;
using namespace sf;

struct request
{
	vector<void*>adresses;
	vector<char>types;
	 Uint8 type;

	short wait_for = 0;
	request() : type('\0'){}
	request(const Uint8 type) : type(type) {};
	request& operator=(const request& other)
	{
		adresses.assign(other.adresses.begin(), other.adresses.end());
		types.assign(other.types.begin(), other.types.end());
		type = other.type;
		wait_for = other.wait_for;
		return *this;
	}

	bool load_request(initializer_list<void*>list);
	void load_in_position(void* ptr, const short pos,const Uint8 type);
	void set_types(initializer_list<char>list);
	void set_waiting_time(const short);

	short size() { return adresses.size(); }
};

extern vector<request>requests;
extern request bad_request;

void create_request(const Uint8 type);
bool load_request(initializer_list<void*>list);
void load_in_position(void* ptr, const short pos,const Uint8 type);
void set_types(initializer_list<char>list);
void set_waiting_time(const short);

request* find_of_type(const Uint8 type);
