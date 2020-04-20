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
	file(string path);
	unsigned int size() { return content.size(); }
}extern nullfile;


class repo
{
public:
	vector<repo>subrepos;
	vector<file>files;
	string name;
private:

public:
	repo(const string directory);
	unsigned int size();
	file& get_file(string relative_path);
	repo& get_repo(string relative_path);
	/// first repos, then members
	pair<vector<string>, vector<string> >get_members();
	// ok retard
}extern root;

