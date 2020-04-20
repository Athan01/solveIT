#include "log.h"

cstr first;

cstr::cstr()
{
	error.open("log.txt");
	time_updater = new thread(update_time);
	std::cerr.rdbuf(error.rdbuf());
	sf::sleep(milliseconds(10));
}

void erlog()
{
	cerr << '\n';
}
