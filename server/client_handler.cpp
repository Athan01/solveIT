#include "client_handler.h"

void client_handler::send_response(const int id,const Uint8 type, const signed char response)
{
	clients[id]->first.get_outbound() << type << response;
}

void client_handler::send_problem(const int id)
{
	auto client = clients[id];
	if (tests->problem_top != nullptr)
	{
		string buffer;
		client->first.lock_out();
		client->first.get_outbound_n() << Uint8('p');
		client->first.get_outbound_n() << tests->problem_top->name;
		ifstream in(root.find_by_name_f(tests->problem_top->name + ".prb").path);
		in >> buffer;
		client->first.get_outbound_n() << buffer;
		while (getline(in,buffer))
		{
			buffer.erase(buffer.begin() + buffer.length());
			client->first.get_outbound_n() << buffer + '\n';
		}
		in.close();
		client->first.unlock_out();
	}
	
}

void client_handler::send_quiz(const int id)
{
	auto client = clients[id];
	if (tests->quiz_top != nullptr)
	{
		string buffer;
		client->first.lock_out();
		client->first.get_outbound_n() << Uint8('q');
		client->first.get_outbound_n() << tests->quiz_top->title;
		for (short i = 0; i < tests->quiz_top->questions.size(); i++)
		{
			client->first.get_outbound_n() << tests->quiz_top->questions[i].enunciation;

			for (short j = 0; j < 4; j++)
			{
				client->first.get_outbound_n() << tests->quiz_top->questions[i].answers[j];
			}
		}

		client->first.unlock_out();
	}
}

void client_handler::send_file(file& file, const int id)
{
	clients[id]->first.lock_out();
	clients[id]->first.get_outbound_n() << Uint8('f') <<  file.name << file.content;
	clients[id]->first.unlock_out();
}

void client_handler::handle_login(const int id)
{
	
	static string user;
	static string pass;
	auto client = clients[id];

	client->first.get_inbound() >> user;
	client->first.get_inbound() >> pass;
	signed char response = db->login(user, pass);
	switch (response)
	{
	case 1:
		client->second.log(db->get_associated_repo(user));
		break;
	case 0:
		break;

	}

	send_response(id,'l',response);
}

void client_handler::handle_registration(const int id)
{
	static string user;
	static string pass;
	auto client = clients[id];

	client->first.get_inbound() >> user >> pass;
	signed char response = db->add_user(user, pass);
	if (response == 1)
	{
		client->second.log(db->get_associated_repo(user));
	}
	send_response(id, 'r', response);
}

void client_handler::handle_file(const int id)
{


}

void client_handler::handle_problem(const int id)
{
	clients[id]->first.lock_in();
	string name;
	clients[id]->first.get_inbound_n() >> name;
	string pr;
	clients[id]->first.get_inbound_n() >> pr;
	results res = tests->check(name, pr);
	send_response(id, 's', res);
	clients[id]->first.unlock_in();

}

void client_handler::handle_quiz(const int id)
{

}

void client_handler::handle_browser(const int id)
{
	string path;

	

	int dir;
	auto client = clients[id];
	client->first.get_inbound() >> dir;
	client->first.get_inbound() >> path;
	if (dir > 0)
	{
		switch (client->second.advance(path))
		{
		case -1:
			switch (tests->find_by_file(root.find_by_name_f(path)))
			{
			case -1:
				cout << "SNED PROBL";
				send_problem(id);
				break;
			case 0:
				break;
			case 1:
				send_quiz(id);
				break;
			
			}
			
		case 0:
			break;
		case 1:
			clients[id]->first.lock_out();
			clients[id]->first.get_outbound_n() << Uint8('b');
			clients[id]->first.get_outbound_n() << clients[id]->second.get_repo().path.substr(28);
			for (auto& a : client->second.get_repo().get_members().first)
			{
				clients[id]->first.get_outbound_n() << a;

			}

			for (auto& a : client->second.get_repo().get_members().second)
			{
				clients[id]->first.get_outbound_n() << a;
			}

			clients[id]->first.unlock_out();
			break;
		}
	}
	else
	{
		client->second.go_back(path);
		clients[id]->first.lock_out();
		clients[id]->first.get_outbound_n() << Uint8('b');
		clients[id]->first.get_outbound_n() << clients[id]->second.get_repo().path.substr(28);
		for (auto& a : client->second.get_repo().get_members().first)
		{
			clients[id]->first.get_outbound_n() << a;

		}

		for (auto& a : client->second.get_repo().get_members().second)
		{
			clients[id]->first.get_outbound_n() << a;
		}

		clients[id]->first.unlock_out();
	}
	
		

	
	


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
			case 'b':
				handle_browser(a.first);
				break;
			case 'p':
				handle_problem(a.first);
				break;
			case 'q':
				handle_quiz(a.first);
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
