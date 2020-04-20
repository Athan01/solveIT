#pragma once
#include "trigger.h"
#include <vector>
#include <map>
using namespace std;
class trigger_manager
{
	map<string,trigger<bool> >bool_triggers;
	map<string,trigger<string> >string_triggers;
	map<string,trigger<float> >float_triggers;
	map<string,trigger<int>>int_triggers;
public:
	void run();

	void add_trigger(const string name,bool& var,bool autoreset = 0);
	void add_trigger(const string name, bool& var, const bool desired,bool autoreset);
	void add_trigger(const string name, string& var,bool autoreset = 0);
	void add_trigger(const string name, string& var, const string desired, bool autoreset = 0);
	void add_trigger(const string name, int& var, bool autoreset = 0);
	void add_trigger(const string name, int& var, const int desired, bool autoreset = 0);
	void add_trigger(const string name, float& var, bool autoreset = 0);
	void add_trigger(const string name, float& var, const float desired = 0, bool autoreset = 0);

	trigger<bool>& find_bool(const string name) { return bool_triggers[name]; }
	trigger<string>& find_string(const string name) { return string_triggers[name]; }
	trigger<float>& find_float(const string name) { return float_triggers[name]; }
	trigger<int>& find_int(const string name) { return int_triggers[name]; }
}extern universal_triggers;;

