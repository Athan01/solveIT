#include "trigger_manager.h"

trigger_manager universal_triggers;

void trigger_manager::run()
{
	for (auto &a : bool_triggers)
	{
		if (a.second.finished())
			a.second.run();
	}

	for (auto& a : string_triggers)
	{
		if (a.second.finished())
			a.second.run();
	}

	for (auto& a : int_triggers)
	{
		if (a.second.finished())
			a.second.run();
	}

	for (auto& a : float_triggers)
	{
		if (a.second.finished())
			a.second.run();
	}


}

void trigger_manager::add_trigger(const string name, bool& var, bool autoreset)
{
	bool_triggers.insert(pair<string, trigger<bool> >(name, trigger<bool>(var)));
	bool_triggers[name].autoreset = autoreset;
}

void trigger_manager::add_trigger(const string name, bool& var, const bool desired, bool autoreset)
{
	bool_triggers.insert(pair<string, trigger<bool> >(name, trigger<bool>(var,desired)));
	bool_triggers[name].autoreset = autoreset;
}

void trigger_manager::add_trigger(const string name, string& var, bool autoreset)
{
	string_triggers.insert(pair<string, trigger<string> >(name, trigger<string>(var)));
	string_triggers[name].autoreset = autoreset;
}

void trigger_manager::add_trigger(const string name, string& var, const string desired, bool autoreset)
{
	string_triggers.insert(pair<string, trigger<string> >(name, trigger<string>(var)));
	string_triggers[name].autoreset = autoreset;
}

void trigger_manager::add_trigger(const string name, int& var, bool autoreset)
{
	int_triggers.insert(pair<string, trigger<int> >(name, trigger<int>(var)));
	int_triggers[name].autoreset = autoreset;
}

void trigger_manager::add_trigger(const string name, int& var, const int desired, bool autoreset)
{
	int_triggers.insert(pair<string, trigger<int> >(name, trigger<int>(var)));
	int_triggers[name].autoreset = autoreset;
}

void trigger_manager::add_trigger(const string name, float& var, bool autoreset)
{
	float_triggers.insert(pair<string, trigger<float> >(name, trigger<float>(var)));
	float_triggers[name].autoreset = autoreset;
}

void trigger_manager::add_trigger(const string name, float& var, const float desired, bool autoreset)
{
	float_triggers.insert(pair<string, trigger<float> >(name, trigger<float>(var)));
	float_triggers[name].autoreset = autoreset;
}
