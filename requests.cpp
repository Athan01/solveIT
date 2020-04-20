#include "requests.h"
vector<request>requests;
request bad_request;
void create_request(const Uint8 type)
{
	requests.push_back(request(type));
	cout << "request created " << type << " " << requests.size();
}

bool load_request(initializer_list<void*> list)
{
	for (void* i : list)
	{
		for (short j = 0; j < requests.back().adresses.size(); j++)
		{
			if (i == requests.back().adresses[j])
				return 0;
		}
	}
	requests.back().adresses.insert(requests.back().adresses.end(), list.begin(), list.end());
	requests.back().wait_for--;
	return 1;
}

void set_types(initializer_list<char> list)
{
	requests.back().types.insert(requests.back().types.end(), list.begin(), list.end());
}

void set_waiting_time(const short number_of_loads)
{
	requests.back().wait_for = number_of_loads;
}

void load_in_position(void* ptr, const short pos,const Uint8 type)
{
	if (pos > requests.back().size()-1)
	{
		requests.back().adresses.resize(pos+1);
		requests.back().types.resize(pos+1);
	}
	requests.back().adresses[pos] = ptr;
	requests.back().types[pos] = type;
	requests.back().wait_for--;
}

request* find_of_type(const Uint8 type)
{
	for (short i = 0; i < requests.size(); i++)
		if (requests[i].type == type)
		{
			return &requests[i];
		}
			
	return &bad_request;
}



bool request::load_request(initializer_list<void*> list)
{
	for (void* i : list)
	{
		for (short j = 0; j < adresses.size(); j++)
			if (i == adresses[j])
				return 0;
	}

	adresses.insert(requests.back().adresses.end(), list.begin(), list.end());
	wait_for--;
	return 1;
}

void request::load_in_position(void* ptr, const short pos,const Uint8 type)
{
	if (pos > this->size()-1)
	{
		adresses.resize(pos+1);
		types.resize(pos+1);
	}
	adresses[pos] = ptr;
	types[pos] = type;
	wait_for--;
}

void request::set_types(initializer_list<char> list)
{
	types.insert(requests.back().types.end(), list.begin(), list.end());

}

void request::set_waiting_time(const short a)
{
	wait_for = a;
}
