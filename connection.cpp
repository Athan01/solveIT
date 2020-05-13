#include "connection.h"



connection::connection(const string ip) : ip(ip) , exit(find_bool("exit")),  connected(find_bool("connected"))
{
	connector = new thread(spawn());
	inbound = new thread(spawn_in());
	outbound = new thread(spawn_out());
}

connection::~connection()
{
	connector->join();
	inbound->join();
	outbound->join();
	delete connector;
	delete inbound;
	delete outbound;
}

thread connection::spawn()
{
	return thread(
		[=] {return run(); }
	);
}

thread connection::spawn_in()
{
	return thread(
		[=] {return handle_input(); }
	);
}

thread connection::spawn_out()
{
	return thread(
		[=] {return handle_output(); }
	);
}

void connection::run()
{
	while (!exit)
	{
		if (!connected)
			connect();
		if (connected)
			handle_requests();
		sleep(milliseconds(20));
	}
}

Packet& connection::get_inbound(bool lock)
{
	static Packet inbound;
	if (lock)
		Lock lock(in_lock);
	return inbound;

}

Packet& connection::get_outbound(bool lock)
{
	static Packet outbound;
	if (lock)
		Lock lock(out_lock);
	return outbound;
}

void connection::connect()
{
	if (sock.connect(ip, PORT) == Socket::Done)
	{
		connected = 1;
		cerr  << "Succesfully connected to " << ip << ":" << PORT << "\n";
	}
}

void connection::handle_input()
{
	while (!exit)
	{
		if (connected)
		{
			if (sock.receive(get_inbound()) == Socket::Done)
			{
				cout << "Received pack ";
				responses.handle_response(get_inbound());
			}
			else
			{
				disconnect();
			}
		}
			
		sleep(milliseconds(20));
	}
		
}

void connection::handle_output()
{
	while (!exit)
	{
		if (connected)
			if (get_outbound().getDataSize() > 0)
			{
				if (sock.send(get_outbound()) == Socket::Done)
					get_outbound().clear();
			}
		sleep(milliseconds(20));
	}
		
			
}

void connection::handle_requests()
{
	out_lock.lock();
	for (short i = 0; i < requests.size(); i++)
	{
		get_outbound(0) << requests[i].type;
		
		for (short j = 0; j < requests[i].adresses.size(); j++)
		{
			switch (requests[i].types[j])
			{
			case 's':
				get_outbound(0) << *(string*)requests[i].adresses[j];
				break;
			case 'a':
				get_outbound(0) << *(char*)requests[i].adresses[j];
				break;
			case 'f':
				get_outbound(0) << *(float*)requests[i].adresses[j];
				break;
			case 'i':
				get_outbound(0) << *(int*)requests[i].adresses[j];
				break;
			// case 'v'
					// vectors, with subtypes TBI	
			}
		}

		
	}
	out_lock.unlock();
	requests.clear();
}

void connection::disconnect()
{
	cout << "Disconnected\n";
	sock.disconnect();
	connected = 0;
}
