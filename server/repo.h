#pragma once
#include "log.h"
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
namespace fs = std::experimental::filesystem;
extern string default_directory;

struct file
{
	string path;
	string content;
	string name;
	file(string path,bool load = 1);
	unsigned int size() { return content.size(); }
	void write(bool append = 0) { ofstream out; if (append)out.open(path.c_str(), ios::app); else out.open(path.c_str()); out << content; out.close(); }
}extern nullfile;


class repo
{
public:
	vector<repo>subrepos;
	vector<file>files;
	string name;
	string path;
private:

public:
	repo(const string directory);
	unsigned int size();
	file& get_file(string relative_path);
	repo& get_repo(string relative_path);
	/// first repos, then members
	pair<vector<string>, vector<string> >get_members();
	repo& add_repo(const string name);
	file& add_file(const string name,bool load = 1);
}extern root;

