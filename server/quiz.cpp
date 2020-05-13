#include "quiz.h"





quiz::quiz(file& q) : path(q)
{
	ifstream in(q.path);
	if (in.is_open())
	{
		in >> title;
		string buffer;
		while (in >> buffer)
		{
			questions.push_back({});
			replace(buffer.begin(), buffer.end(), '_', ' ');
			questions.back().enunciation = buffer;

			for (short i = 0; i < 4; i++)
			{
				in >> questions.back().answers[i];
			}
		}
		cerr << current_time <<  "Quiz " << title << " created\n";
	}
	else cerr << current_time << "Failed to create quiz " << title << '\n';

	in.close();
	
}
