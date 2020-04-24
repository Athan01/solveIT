#include "client_profile.h"

void client_profile::log(repo* profile_repo)
{
	profile = profile_repo;
	logged = 1;
}
