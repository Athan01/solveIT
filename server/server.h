#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <thread>
#include <string>
#include <sstream>
#include "client_process.h"
#include "database.h"
#include "log.h"
#define PORT 3030
using namespace sf;
using namespace std;

class server
{
	TcpListener listener;
	thread* listening_thread;
	thread* command_thread;
	vector<client_process*>clients;
	long last_id = 0;
	database* db;
	string command = "";
public:

private:
	void listen();
	void cmd();
	thread spawn_listen();
	thread spawn_cmd();
	void check_status();

	void handle_login(const long client_id);
	void handle_message(const long client_id);
	void handle_requests();
	bool exists(const long id);
	long find_id(const string username);
	client_process* find_client(const long id) { for (short i = 0; i < clients.size(); i++)if (clients[i]->id == id) return clients[i]; return nullptr; }
	client_process* find_client(const string username) { for (short i = 0; i < clients.size(); i++)if (clients[i]->name == username)return clients[i]; return nullptr; }

	void send_response(const long id,const Uint8 response);
	void send_message(const string message);
	void ban(const long id);
	void kick(const long id);
	void send_file(const string filename,const long id);
	//void send_whisper(const long userid, const string message);
public:
	server();
	~server();
	
	void run();
};

