#pragma once
#include <SFML/Network/Packet.hpp>
#include <vector>
#include <fstream>
#include "resource.h"
#include "menu.h"
using namespace std;
using namespace sf;

///<summary>
///class that handles the response of the server based on the initial request sent by the client
///</summary>
struct response_interpretor
{
	void login_response(Packet& pack);
	void register_response(Packet& pack);
	void browser_response(Packet& pack);
	void file_response(Packet& pack);
	void handle_response(Packet& pack);
	void problem_response(Packet& pack);
	void quiz_response(Packet& pack);
	// problem score
	void score_response(Packet& pack);

	void data_response(Packet& pack);
	void image_response(Packet& pack);
	void ranking_response(Packet& pack);

	bool bad(Packet& pack, Uint8 type);
}extern responses;


