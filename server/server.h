#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <thread>
#include <string>
#include "client_handler.h"
#define PORT 3030
using namespace sf;
using namespace std;

class server
{
	TcpListener listener;
	thread* listening_thread;
	thread* command_thread;
	string command = "";
	client_handler clients;

	

public:

private:
	void listen();
	void cmd();
	thread spawn_listen();
	thread spawn_cmd();

	void ban();
	void kick();
	
public:
	server();
	~server();
	
	void run();
};

