#include "client_handler.h"

void client_handler::send_response(const int id, const char response)
{
	clients[id]->first.get_outbound() << response;
}

void client_handler::handle_login(const int id)
{
	static string user;
	static string pass;

	clients[id]->first.get_inbound() >> user;
	clients[id]->first.get_inbound() >> pass;

	char response = db->login(user, pass);
	switch (response)
	{
	case 1:
		clients[id]->second.log(db->get_associated_repo(user));
		break;

	}

	send_response(id, response);
}

void client_handler::handle_registration(const int id)
{


}

void client_handler::handle_file(const int id)
{


}

void client_handler::handle_problem(const int id)
{


}

void client_handler::handle_clients()
{
	static Uint8 type;
	for (auto& a : clients)
	{
		if (a.second->first.get_inbound().getDataSize() > 0)
		{
			Uint8 type;
			a.second->first.get_inbound() >> type;
			switch (type)
			{
			case 'l':
				handle_login(a.first);
				break;
			case 'r':
				handle_registration(a.first);
				break;
			case 'f':
				handle_file(a.first);
				break;
			case 'p':
				handle_problem(a.first);
				break;
			}
		}
	}
}

void client_handler::add_client(TcpSocket* sock)
{
	static int last_id = 0;
	if (!db->is_blacklisted(sock->getRemoteAddress().toString()))
	{
		clients[last_id] = new pair<client_process, client_profile>(sock, 1);
		cout << current_time << "New client at " << sock->getRemoteAddress() << '\n';
	}
	else
		cout << current_time << "Banned client at " << sock->getRemoteAddress() << " attempting to connect\n";
	
}
