#include "client_profile.h"


char client_profile::advance(string local_path)
{
	if (local_path.find('.') != string::npos)
	{
		file& file = tree->get_file(local_path);
		if (&file != &nullfile)
		{
			tree_file = &file;
		}
		return -1;
	}

	else
	{
		repo& rep = tree->get_repo(local_path);
		if (&rep != &nullrepo)
		{
			tree = &rep;
			return 1;
		}
		
	}
	return 0;
	
}

void client_profile::go_back(string local_path)
{
	tree = &root.find_by_name(local_path);
}

void client_profile::log(repo* profile_repo)
{
	profile = profile_repo;
	logged = 1;
}
