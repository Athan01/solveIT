#include "profile.h"

quiz_data quiz;
user_data profile;
problem_data problem;

void quiz_data::load_quiz(sf::Packet& pack)
{
	player_choices.clear();
	question.clear();
	answers.clear();
	right_answer.clear();


	srand(time(0));
	if (buttons != nullptr)
		delete[] buttons;
	pack >> title;
	question.push_back(string());
	
	while (pack >> question.back())
	{
		answers.push_back({});
		answers.back() = new string[4];
		for (short i = 0; i < 4; i++)
			pack >> answers.back()[i];
		right_answer.push_back(*answers.back());

		random_shuffle(answers.back(), answers.back() + 3);
		question.back() = istr(question.size()) + ')' + question.back();
		question.push_back({});
	}
	question.pop_back();
	player_choices.resize(question.size(),-1);

	buttons = new bool[question.size() * 4];
	for (short i = 0; i < question.size() * 4; i++)
		buttons[i] = 0;
}

string quiz_data::elapsed_str()
{
	string cpy = fstr(elapsed());
	return cpy.substr(0, cpy.find('.') + 1);
}

short quiz_data::percentage()
{
	short score = 0;
	for (short i = 0; i < question.size(); i++)
	{
		if (player_choices[i] >=0)
			if (answers[i][player_choices[i]] == right_answer[i])
			{
				score++;
			}
	}
	return ((score*100) / question.size());
}
