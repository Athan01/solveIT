#pragma once
#include <SFML/Network/Packet.hpp>
#include <vector>
#include "resource.h"
#include "menu.h"
using namespace std;
using namespace sf;

///<summary>
///class that handles the response of the server based on the initial request sent by the client
///</summary>
struct response_interpretor
{
	const Uint8 request_type;
	void (*f)(const char,Packet&);
	response_interpretor(const Uint8 initial_request);
};

void login_response(const char response,Packet& pack);
void register_response(const char response,Packet& pack);

map<Uint8,response_interpretor>responses;