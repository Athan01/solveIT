#include <iostream>
#include <string>
#include "server.h"
#include <ctime>
#include "problem_holder.h"
#include "repo.h"
using namespace sf;
using std::cout;



int main(int argc,char* argv[])
{
	if (argc > 1)
		if (strcmp(argv[1],"-noconsole")==0)
		{
			FreeConsole();
		}
	server a;
	a.run();
	system("pause");
	
}