
		#include <fstream>
#include <iostream>
using namespace std;

int main(int argc,char* argv[])
{

ifstream in("pr1.txt");
ofstream out("pr1o.txt");
int a,b;
in >> a >> b;
out << a+b+3;
return 1;
}
		
	