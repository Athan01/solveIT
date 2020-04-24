#include "response.h"

response_interpretor::response_interpretor(const Uint8 initial_request) : request_type(initial_request)
{
	switch (request_type)
	{
	case 'l':
		f = login_response;
		break;
	case 'r':
		f = register_response;
		break;
	}
}

void login_response(const char response, Packet& pack)
{
	if (response == 1)
	{
		find_int("state") = 2;
	}
	else
	{
		menus[find_int("state")].create_popup("login failed");
	}
}

void register_response(const char response, Packet& pack)
{
}
