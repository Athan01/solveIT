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
	Packet& get_outbound_n();
	Packet& get_inbound();
	Packet& get_inbound_n();
	IpAddress ip() { return sock->getRemoteAddress(); }
	
	void lock_out() { out_bound.lock(); }
	void lock_in() { in_bound.lock(); }
	void unlock_in() { in_bound.unlock(); }
	void unlock_out() { out_bound.unlock(); }

	client_process(TcpSocket* sock);
	~client_process();
};

