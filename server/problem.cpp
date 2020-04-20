#include "problem.h"

problem::problem(const std::string problem_name) : name(problem_name)
{
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;

	string cmd =  problem_name + ".exe";;
	TCHAR* cmdt = tchar(cmd);

	CreateProcess(cmdt, 0, 0, 0, 0, 0, 0, 0, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);

	delete cmdt;
	cout << "   PRocess ended";

	//string cmd ="start " + problem_name + ".exe";
	//system(cmd.c_str());
	ifstream in(problem_name + "oo.txt");

	do
	{
		solutions.push_back(string());
		cout << solutions.back();
	} while (in >> solutions.back());
	in.close();

	cmd = problem_name + "oo.txt";
	//if (remove(cmd.c_str()) != 0)
	//	cout << "not removed";
	solutions.pop_back();
	remove(cmd.c_str());
	cout << "good solutions : ";
	for (short i = 0; i < solutions.size(); i++)
		cout << solutions[i];
}

bool problem::check(const std::string solution)
{
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;
	PROCESS_INFORMATION pi2;
	ofstream out(name + ".cpp");
	out << solution;
	out.close();

	string cmd = "g++ " + name + ".cpp -o " + name + "test.exe";
	TCHAR* cmdt = tchar(cmd);

	CreateProcess(0, cmdt, 0, 0, 0, 0, 0, 0, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);
	delete cmdt;
	cmd = name + "test.exe";
	cmdt = tchar(cmd);
	CreateProcess(cmdt,0, 0, 0, 0, 0, 0, 0, &si, &pi2);
	WaitForSingleObject(pi2.hProcess, INFINITE);


	ifstream in(name + "o.txt");
	string buffer;
	unsigned int index = 0;
	cout << "\n Problem: ";
	while (in >> buffer)
	{
		cout << buffer << " ";
		if (buffer != solutions[index])
		{
			break;
		}
		cout << solutions[index];
		index++;
	}
	in.close();
	cmd = name + "o.txt";
	remove(cmd.c_str());
	if (index == solutions.size())
		return 1;
	else return 0;
}
