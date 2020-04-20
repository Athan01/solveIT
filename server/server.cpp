#include "server.h"



void server::listen()
{
	
	while (1)
	{
		TcpSocket* sock = new TcpSocket();
		Uint32 status = listener.accept(*sock);
		if (status == Socket::Done)
		{
			if (db->is_blacklisted(sock->getRemoteAddress().toString()))
			{
				cout << current_time << " Banned user attempting to connect " << sock->getRemoteAddress() << '\n';
				Packet p;
				p << Uint8(0);
				sock->send(p);
				delete sock;
			}
			else
			{
				cout << current_time << "New connection at: " << sock->getRemoteAddress() << '\n';
				Packet p;
				p.clear();
				p << Uint8(1);
				sock->send(p);
				clients.push_back(new client_process(sock, last_id));
				last_id = clients.size();
			}
			
		}
		else delete sock;
	}
}

void server::cmd()
{
	while (command != "quit")
	{
		getline(cin,command);
		string type = split(command);
		string secondary = split(command);

		if (type == "send")
		{
			string destination = split(command);
			send_file(secondary, find_id(destination));
		}
		else if (type == "kick")
		{
			kick(find_id(secondary));
		}
		else if (type == "ban")
		{
			ban(find_id(secondary));
		}
		else if (type == "unban")
		{
			db->remove_blacklisted(secondary);
		}
	}
}

thread server::spawn_listen()
{
	return thread([=] {return listen(); });
}

thread server::spawn_cmd()
{
	return thread([=] {return cmd(); });
}

void server::check_status()
{
	for (long i = 0; i < clients.size(); i++)
	{
		if (clients[i]->disconnected)
		{
			cout << current_time << "Client " << i << " name: " << clients[i]->name << " disconnected\n";
			delete clients[i];
			clients.erase(clients.begin() + i);
			last_id = i;
		}
	}
}

void server::handle_login(long client_id)
{
	string u;
	string p;

	clients[client_id]->get_inbound() >> u;
	clients[client_id]->get_inbound() >> p;

	

	cout << "login attempt " << u << "  " << p << '\n';
	switch (db->login(u, p))
	{
	case -1:
		send_response(client_id, -1);
		break;
	case 0:
		send_response(client_id, 0);
		break;
	case 1:
		send_response(client_id, 1);
		cout << current_time << u << " logged in from " << clients[client_id]->ip() << '\n';
		clients[client_id]->name = u;
		break;
	default:
		cout << "stupid code";
		break;
	}
}

void server::handle_message(long client_id)
{
	cout << "new mess   :";
	string mess;
	clients[client_id]->get_inbound() >> mess;
	cout << mess << " ";
}

void server::handle_requests()
{
	for (short i=0;i<clients.size();i++)
		if (clients[i]->get_inbound().getDataSize() > 0)
		{
			UINT8 req;
			clients[i]->get_inbound() >> req;
			switch (req)
			{
			case 'l':
				handle_login(i);
				break;
			case 'm':
				handle_message(i);
				break;
			default:
				break;
			}
		}
}

bool server::exists(const long id)
{
	for (short i = 0; i < clients.size(); i++)
		if (clients[i]->id == id)
			return 1;
	return 0;
}

long server::find_id(const string username)
{
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		if (clients[i]->name == username)
		{
			return clients[i]->id;
		}
	}
	return -1;
}

void server::send_response(const long id, const Uint8 response)
{
	if (id < 0)
		return;
	Uint8 r = 'r';
	if (clients.size() > id)
		clients[id]->get_outbound() << r << response;
	cout << response;
}

void server::ban(const long id)
{
	if (id < 0)
	{
		cout << "Client not found to ban\n";
		return;
	}
	
	client_process* cl = find_client(id);
	cl->disconnected = 1;
	db->add_to_blacklist(cl->ip().toString());
	cout << "Kicked " << id << '\n';
}

void server::kick(const long id)
{
	if (id < 0)
	{
		cout << "Client not found to kick\n";
		return;
	}
	client_process* cl = find_client(id);

	if (cl != nullptr)
	{
		cl->disconnected = 1;
		db->temp_ban(cl->ip().toString(),30);
		cout << "Kicked " << id << '\n';
	}
}

void server::send_file(const string filename,const long id)
{
	// maybe index file in memory
	if (id < 0)
	{
		cout << "Client not found to send the file\n";
		return;

	}

	string file;
	unsigned int size = load_file(filename, file);
	cout << "sending file of " <<(float)size / 1024.f << " KB\n";
	client_process* recepient = find_client(id);
	recepient->out_bound.lock();
	recepient->get_outbound() << Uint8('f');
	recepient->get_outbound() << filename;
	recepient->get_outbound() << size;

		/*for (unsigned int i = 0; i < size; i++)
		{
			recepient->get_outbound() << arr[i];
			if (i % 1000 == 0)
				cout << "KB";
		}*/
	recepient->get_outbound() << file;
	recepient->out_bound.unlock();
}



server::server()
{
	erlog(current_time, "Server started");
	listener.listen(PORT);// maybe add whitelist
	listening_thread = new thread(spawn_listen());
	command_thread = new thread(spawn_cmd());
	db = new database("users.txt");
	//db->add_to_blacklist("127.0.0.1");
	//db->add_to_blacklist("1.1.1.1.1");
	db->remove_blacklisted("1.1.1.1.1");
}

server::~server()
{
	
}

void server::run()
{

	while (1)
	{
		check_status();
		handle_requests();
		sleep(milliseconds(DELAY));
	}
}
