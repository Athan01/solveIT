#include "repo.h"

repo root("C:\\Users\\ioanm\\Desktop\\root");
repo nullrepo;
file nullfile("null");

file::file(string path,bool load) : path(path)
{
	if (load)
	{
		if (load_file(path, content) > 0)
		{
			cerr << current_time << ": Loaded file " << path << " .\n";
			
		}
		else
		{
			cerr << current_time << ": Failed to load file " << path << "\n";
			//delete this;
			content.clear();
			ofstream f(path.c_str());
			f.close();
		}
	}
	else
	{
		cerr << current_time << "Created file " << path << "\n";
	}

	for (short i = path.size() - 1; i >= 0; i--)
	{
		if (path[i] == '\\')
		{
			name = path.substr(i + 1);
			break;
		}
	}
}


repo::repo(const string directory) : path(directory)
{
	
	for (auto& entry : fs::directory_iterator(directory))
	{
		if (fs::is_directory(entry.path()))
		{
			subrepos.push_back(repo(entry.path().u8string()));
		}
		else
		{
			/// DONT LOAD THESE FORMATS
			if (entry.path().u8string().substr(entry.path().u8string().find('.') + 1) == "exe")
			{
				files.push_back(file(entry.path().u8string(),0));
			}
			else if (entry.path().u8string().substr(entry.path().u8string().find('.') + 1) == "prb")
			{
				files.push_back(file(entry.path().u8string(), 0));
			}
			else if (entry.path().u8string().substr(entry.path().u8string().find('.') + 1) == "quiz")
			{
				files.push_back(file(entry.path().u8string(), 0));
			}
			/// LOAD FILES NOT OF ANY OF THESE 3 FORMATS
			else
			{
				files.push_back(file(entry.path().u8string()));
			}
		}
		cerr << current_time << "Created repository with with path " << directory << " and " << files.size() << " files, and " << subrepos.size() << " repositores\n";
	}

	for (short i = directory.size() - 1; i >= 0; i--)
	{
		if (directory[i] == '\\')
		{
			name = directory.substr(i+1);
			break;
		}
	}
}

unsigned int repo::size()
{
	unsigned int size = 0;
	for (unsigned int i = 0; i < subrepos.size(); i++)
		size += subrepos[i].size();
	for (unsigned int i = 0; i < files.size(); i++)
		size += files[i].size();
	return size;
}

file& repo::get_file(string relative_path)
{
	for (unsigned int i = 0; i < files.size(); i++)
	{
		if (files[i].name == relative_path)
		{
			return files[i];
		}
	}
	relative_path.erase(relative_path.begin(), relative_path.begin() + relative_path.find(':')+1);
	string current = relative_path.substr(0, relative_path.find(':'));
	for (unsigned int i = 0; i < files.size(); i++)
	{
		if (files[i].name == current)
		{
			return files[i];
		}
	}

	for (unsigned int i = 0; i < subrepos.size(); i++)
	{
		if (subrepos[i].name == current)
		{
			return subrepos[i].get_file(relative_path);
		}
	}
	return nullfile;
}

repo& repo::get_repo(string relative_path)
{
	if (relative_path == name)
	{
		return *this;
	}

	string current;
	if (relative_path.find(':') != string::npos)
	{
		relative_path.erase(relative_path.begin(), relative_path.begin() + relative_path.find(':') + 1);
		current = relative_path.substr(0, relative_path.find(':'));
	}
	else
	{
		current = relative_path;
	}
	
	for (unsigned int i = 0; i < subrepos.size(); i++)
	{
		if (subrepos[i].name == current)
		{
			return subrepos[i];
		}
	}

	return nullrepo;
}

repo& repo::find_by_name(const string name)
{
	if (name == this->name)
		return *this;
	for (short i = 0; i < subrepos.size(); i++)
	{
		if (subrepos[i].name == name)
			return subrepos[i];
		if (&subrepos[i].find_by_name(name) != &nullrepo)
		{
			return subrepos[i].find_by_name(name);
		}
	}
	return nullrepo;
}

file& repo::find_by_name_f(const string name)
{
	for (short i = 0; i < files.size(); i++)
		if (files[i].name == name)
			return files[i];
	for (short i = 0; i < subrepos.size(); i++)
	{
		auto& a = subrepos[i].find_by_name_f(name);
			if (&a != &nullfile)
				return a;
	}
	return nullfile;
}

pair<vector<string>, vector<string>> repo::get_members()
{
	vector<string>repos;
	vector<string>file;

	for (short i = 0; i < subrepos.size(); i++)
		repos.push_back(subrepos[i].name);
	for (short i = 0; i < files.size(); i++)
		file.push_back(files[i].name);
	/// first repos, then files
	pair<vector<string>, vector<string> >a(repos, file);
	return a;
}

repo& repo::add_repo(const string name)
{
	experimental::filesystem::create_directory(experimental::filesystem::path(path + '\\' + name));
	subrepos.push_back(path + '\\' + name);
	return subrepos.back();
}

file& repo::add_file(const string name,bool load)
{
	files.push_back(file(path + '\\' + name,load));
	return files.back();
}





