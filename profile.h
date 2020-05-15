#pragma once
#include <vector>
#include <SFML/Network/Packet.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include "util.h"
#include <iostream>
using namespace std;

struct quiz_data
{
	string title;
	vector<string>question;
	vector<string*>answers;
	vector<string>right_answer;
	sf::Clock* timer = nullptr;

	bool* buttons = nullptr;

	vector<char>player_choices;
	void flush() { for (short i = 0; i < answers.size(); i++)delete[] answers[i]; }
	void start() { if (timer)delete timer; timer = new sf::Clock; }
	void load_quiz(sf::Packet& pack);
	string elapsed_str();
	float elapsed() { return timer->getElapsedTime().asSeconds(); }
	short percentage();
}extern quiz;


struct problem_data
{
	string title;
	string requirement;
	bool finished = 0;
	
	string result;

}extern problem;

struct user_data
{
	string username;
	vector<string>solved;
	vector<short>scores;
	short pfp;
	short points;

	vector<string>files;
	vector<bool>completed;



	string current_path;
}extern profile;

extern vector<string>rankings;

