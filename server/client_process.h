#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <iostream>
#include "util.h"
#include "client_profile.h"
using namespace std;
using namespace sf;
class client_process
{
	
	
	TcpSocket *sock;

	
	thread* in;
	thread* out;

	Packet inbound;
	Packet outbound;
	
public:
	
	bool disconnected = 0;
	string name = "NaN";
	Mutex out_bound;
	Mutex in_bound;
private:
	
	thread spawn_in();
	thread spawn_out();

	void handle_input();
	void handle_output();
public:
	Packet& get_outbound();
	Packet& get_inbound();
	IpAddress ip() { return sock->getRemoteAddress(); }
	client_process(TcpSocket* sock);
	~client_process();
};

