#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <iostream>
#include "resource.h"
#include "requests.h"
#define PORT 3030
using namespace sf;
using namespace std;

class connection
{
	TcpSocket sock;
	string ip;
	thread* connector;
	thread* inbound;
	thread* outbound;

	Mutex out_lock;
	Mutex in_lock;

	bool& exit;
	bool& connected;
private:
	void disconnect();
	void connect();
	void handle_input();
	void handle_output();
	void handle_requests();
public:
	connection(const string ip);
	~connection();
	thread spawn();	
	thread spawn_in();
	thread spawn_out();


	void run();
	bool is_connected() { return connected; }

	Packet& get_inbound(bool lock = 1);
	Packet& get_outbound(bool lock = 1);
};

