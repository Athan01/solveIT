#pragma once
#include <vector>
//#include "util.h"
using namespace std;
template <typename T>
struct trigger
{
	bool on_change = 0;
	T* to_check;
	T desired_value;
	void (*f)(vector<void*>);
	vector<void*>args;

	bool ran = 0;
	bool autoreset = 0;
	bool finished() { if (!on_change)return *to_check == desired_value; else return *to_check != desired_value; }
	void run();
	trigger(){}
	trigger(T& to_check, const T desired_value) : to_check(&to_check), desired_value(desired_value) {}
	trigger(T& to_check) : to_check(&to_check), on_change(1),desired_value(to_check){}

	void add_function(void (*f)(std::vector<void*>)) { this->f = f; }
	void add_list(std::initializer_list<void*>list) { args.insert(args.end(), list); }
};


