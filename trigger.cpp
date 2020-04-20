#include "trigger.h"

template <>
void trigger<int>::run()
{
	if (autoreset)
		ran = 0;
	if (!ran)
	{
		ran = 1;
		f(args);
		
	}
		
}


template <>
void trigger<bool>::run()
{
	if (autoreset)
		ran = 0;
	if (!ran)
	{
		ran = 1;
		f(args);
		
	}
}

template <>
void trigger<std::string>::run()
{
	if (autoreset)
		ran = 0;
	if (!ran)
	{
		ran = 1;
		f(args);
		
	}
}

template <>
void trigger<float>::run()
{
	if (autoreset)
		ran = 0;
	if (!ran)
	{
		ran = 1;
		f(args);
		
	}
}