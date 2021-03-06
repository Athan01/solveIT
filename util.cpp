#include "util.h"

std::time_t t;
std::tm* now;


void init_time()
{
	t = std::time(0);
	now = std::localtime(&t);
}

string istr(const int a)
{
	stringstream in;
	in << a;
	return in.str();
}

string fstr(const float a)
{
	stringstream in;
	in << a;
	return in.str();
}

string cstr(sf::Clock& clock)
{

	return istr(clock.getElapsedTime().asSeconds() / 3600) + ':' + istr((int)clock.getElapsedTime().asSeconds() % 3600 / 60) + ':' + istr((int)clock.getElapsedTime().asSeconds() % 60);
}



int stri(string a)
{
	return stoi(a);
}

float strf(string a)
{
	return stof(a);
}



