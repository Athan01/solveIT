#include "client_process.h"

Packet& client_process::get_outbound()
{
	Lock lock(out_bound);
	return outbound;
}

Packet& client_process::get_inbound()
{
	Lock lock(in_bound);
	return inbound;
}

thread client_process::spawn_in()
{
	return thread([=] {return handle_input(); });
}

thread client_process::spawn_out()
{
	return thread([=] {return handle_output(); });
}

void client_process::handle_input()
{
	UINT32 status;
	while (!disconnected)
	{

		status = sock->receive(inbound);
		if (status == Socket::Done)
		{
			
		}
		else if (status == Socket::Disconnected)
		{

			disconnected = 1;
		}
		sleep(milliseconds(DELAY));
	}
}

void client_process::handle_output()
{
	Uint32 status;
	while (!disconnected)
	{
		
		out_bound.lock();
		if (get_outbound().getDataSize() > 0)
		{
			status = sock->send(get_outbound());
			if (status == Socket::Done)
			{
				get_outbound().clear();
			}
			
		}
		out_bound.unlock();
		sleep(milliseconds(DELAY));
	}
}



client_process::client_process(TcpSocket*sock,long id)
{
	this->id = id;
	this->sock = sock;
	in = new thread(spawn_in());
	out = new thread(spawn_out());
	
	//log(sock->getRemoteAddress());
}

client_process::~client_process()
{
	sock->disconnect();
	in->join();
	out->join();
	delete in;
	delete out;
	delete sock;
}