#include "server.h"



void server::listen()
{
	
	while (1)
	{
		TcpSocket* sock = new TcpSocket();
		Uint32 status = listener.accept(*sock);
		if (status == Socket::Done)
		{
			clients.add_client(sock);
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
			//send_file(secondary, find_id(destination));
		}
		else if (type == "kick")
		{
			//kick(find_id(secondary));
		}
		else if (type == "ban")
		{
			//ban(find_id(secondary));
		}
		else if (type == "unban")
		{
			
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



void server::ban()
{
	
}

void server::kick()
{
	
}

server::server()
{
	erlog(current_time, "Server started");
	listener.listen(PORT);// maybe add whitelist
	listening_thread = new thread(spawn_listen());
	command_thread = new thread(spawn_cmd());
}

server::~server()
{
	delete listening_thread;
	delete command_thread;
	
}

void server::run()
{

	while (1)
	{
		clients.run();
		sleep(milliseconds(DELAY));
	}
}
