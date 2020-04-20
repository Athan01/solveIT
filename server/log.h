#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include "util.h"
using namespace std;





struct cstr
{
	ofstream error;
	thread* time_updater;
	cstr();
	~cstr() { error.close();  closed = 1; time_updater->join(); delete time_updater; }
}extern first;


void erlog();


template <typename T,typename ... Types>
void erlog(T first, Types... second);

template<typename T, typename ...Types>
inline void erlog(T first, Types ...second)
{
	cerr << first << " ";
	erlog(second...);
}
