#pragma once
#include <SFML/Network/Packet.hpp>
#include <string>
#include "util.h"
#include "client_profile.h"
#include "client_process.h"
#include "database.h"
#include "problem_holder.h"
class client_handler
{
	map<int,pair<client_process, client_profile>* >clients;
	database* db;
	problem_holder* tests;
private:
	///
	///
	void send_data(const int id);
	void send_pfp(const int id);
	void send_response(const int id,const Uint8 type,const signed char response);
	void send_problem(const int id);
	void send_quiz(const int id);
	void send_file(file& file,const int id);
	void handle_login(const int id);
	void handle_registration(const int id);
	void handle_file(const int id);
	void handle_problem(const int id);
	void handle_rankings(const int id);
	void handle_quiz(const int id);
	void handle_browser(const int id);
	void handle_clients();
	
public:
	client_handler() { db = new database; tests = new problem_holder; }
	void add_client(TcpSocket* sock);
	void run() { handle_clients(); }

};

