#include "problem.h"
string working_dir = "C:\\Users\\ioanm\\Desktop\\root\\solutions";

problem::problem(file& problem) : path(problem) , path_req(root.find_by_name_f(problem.name.substr(0,problem.name.find('.'))+".prb"))
{
	cout << "HANDICAP" << problem.name.substr(0,problem.name.find('.')) + ".prb";
	name = path.name.substr(0, path.name.find('.'));
	solutions = get_solutions();
	cerr << "Problem" << name << " loaded with solutions ";
	for (short i = 0; i < solutions.size(); i++)
		cerr << solutions[i] << " ";
	cerr << '\n';
}

vector<string> problem::get_solutions()
{
	vector<string>solutions;
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pi;

	
	TCHAR* cmdt = tchar(path.path);
	TCHAR* w_dir = tchar(working_dir);
	
	CreateProcess(cmdt, 0, 0, 0, 0, 0, 0, w_dir, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);

	

	//string cmd ="start " + problem_name + ".exe";
	//system(cmd.c_str());
	string namec = working_dir+"\\" +name + "o.txt";
	ifstream in(namec);

	do
	{
		solutions.push_back(string());
	} while (in >> solutions.back());
	in.close();


	remove(namec.c_str());
		
	delete[] cmdt;
	delete[] w_dir;
	solutions.pop_back();
	return solutions;
}

results problem::check(std::string& solution)
{
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	// process information of the compiler
	PROCESS_INFORMATION pi;
	// process information of the application
	PROCESS_INFORMATION pi2;
	ofstream out(working_dir +'\\' +name+ ".cpp");
	out << solution;
	out.close();

	//string cmd = "cd " + working_dir;
	string cmd = "g++ " + name + ".cpp -o " + name + "test.exe";
	TCHAR* cmdt = tchar(cmd);
	TCHAR* w_dir = tchar(working_dir);

	CreateProcess(0, cmdt, 0, 0, 0, 0, 0, w_dir, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);
	
	cmd = working_dir + '\\' + name + "test.exe";
	cmdt = tchar(cmd);
	CreateProcess(cmdt,0, 0, 0, 0, 0, 0, w_dir, &si, &pi2);
	if (WaitForSingleObject(pi2.hProcess, 10000) == WAIT_TIMEOUT)
	{
		return results::timeout;
	}


	ifstream in(working_dir + '\\' + name + "o.txt");
	string buffer;
	unsigned int index = 0;
	while (in >> buffer && index < solutions.size())
	{
		if (buffer != solutions[index])
		{
			break;
		}
		index++;
	}
	in.close();
	cmd = path.path + "o.txt";
	//remove(cmd.c_str());
	delete[] cmdt;
	delete[] w_dir;
	if (index == solutions.size())
		return results::correct;
	else return results::incorrect;

}
