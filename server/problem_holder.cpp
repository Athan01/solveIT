#include "problem_holder.h"

problem_holder::problem_holder()
{
	vector<string>files = root.find_by_name("easy").get_members().second;

	for (short i = 0; i < files.size(); i++)
	{
		// found file of type quiz, add quiz
		if (files[i].substr(files[i].find('.')+1)=="quiz")
		{
			quizes.push_back(new quiz(root.get_file("root:problems:easy:" + files[i])));
		}
		// found file of type prb, add problem
		else
		{
			problems.push_back(new problem(
				root.get_file("root:solutions:" + files[i].substr(0,files[i].find('.')) + ".exe")
			)
			);
		}
	}

}

signed char problem_holder::find_by_file(file& f)
{
	cout << "find " + f.path << '\n';
	for (short i = 0; i < problems.size(); i++)
	{
		if (&problems[i]->path_req == &f)
		{
			problem_top = problems[i];
			return -1;
		}
	}
	for (short i = 0; i < quizes.size(); i++)
	{
		if (&quizes[i]->path == &f)
		{
			quiz_top = quizes[i];
			return 1;
		}
	}
		

	return 0;
}

results problem_holder::check(string& problem_name, string& problem)
{
	for (short i = 0; i < problems.size(); i++)
	{
		if (problems[i]->name == problem_name)
		{
			return problems[i]->check(problem);
		}
	}
}
