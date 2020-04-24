#include "util.h"

std::time_t t;
std::tm* now;
std::string current_time;
bool closed = 0;

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

int stri(string a)
{
	return stoi(a);
}

float strf(string a)
{
	return stof(a);
}

TCHAR* tchar(string& a)
{
	TCHAR* t = new TCHAR[a.size() + 1];
	t[a.size()] = '\0';
	copy(a.begin(), a.end(), t);
	return t;
}

void update_time()
{
	while (!closed)
	{
		t = std::time(0);
		now = std::localtime(&t);
		current_time = std::to_string(now->tm_hour) + ' ' + std::to_string(now->tm_min) + ' ' + std::to_string(now->tm_sec) + ": ";
	}
	sleep(seconds(0.3));
}

int load_file(const std::string filename, std::string &output)
{
	 char* arr;
	 FileInputStream a;
	 if (a.open(filename))
	 {
		 arr = new char[a.getSize()+1];
		 a.read(arr, a.getSize());
		 arr[a.getSize()] = '\0';
		 output.append(arr,a.getSize());
	 }
	 return a.getSize();
}

 std::string split(std::string& a)
 {
	 std::string f = "";

	 for (short i = 0; i < a.size(); i++)
	 {
		 if (a[i] == ' ')
			 break;
		 else f.push_back(a[i]);
	 }
	 
	 if (a.size() == f.size())
		 a.clear();
	 else
		 a.erase(a.begin(), a.begin() + f.size() + 1);
	 return f;
 }

 unsigned int load_image(const std::string filename, std::string& out)
 {
	 char* arr;
	 FileInputStream a;
	 if (a.open(filename))
	 {
		 arr = new char[a.getSize() + 1];
		 a.read(arr, a.getSize());
		 arr[a.getSize()] = '\0';
		 out.append(arr,a.getSize());
	 }
	 return a.getSize();
 }


