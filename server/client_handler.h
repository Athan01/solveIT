#pragma once
#include <SFML/Network/Packet.hpp>
#include "util.h"
#include "client_profile.h"
#include "client_process.h"
#include "database.h"
class client_handler
{
	map<int,pair<client_process, client_profile>* >clients;
	database* db;
private:
	/// nigger
	///
	void send_response(const int id,const char response);
	void handle_login(const int id);
	void handle_registration(const int id);
	void handle_file(const int id);
	void handle_problem(const int id);
	void handle_clients();
public:
	client_handler() { db = new database; }
	void add_client(TcpSocket* sock);
	void run(){}

};

