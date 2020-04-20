#include "app.h"

app::app()
{
	load_triggers();
	load_menus();
	connection conn("127.0.0.1");
	win.create(VideoMode(720, 512), "win",Style::Close);
	win.setFramerateLimit(30);
	gui::SFML::Init(win);

	

	

	

	
	
	run();
	gui::SFML::Shutdown();
}

void app::load_menus()
{
	menus.push_back(menu(menu0, 0, "connecting"));
	menus.push_back(menu(menu1, 1, "login"));
	menus.push_back(menu(menu2, 2, "profile"));
}

void app::load_triggers()
{

	auto disconnect = [](vector<void*>) {
		find_int("state") = 0;
		universal_triggers.find_bool("connected").ran = 0;
		cout << " disc ";
	};

	auto connect = [](vector<void*>) {
		find_int("state") = 1;
		universal_triggers.find_bool("disconnected").ran = 0;
		cout << " con ";
	};

	universal_triggers.add_trigger("disconnected", find_bool("connected"), 0, 0);
	universal_triggers.find_bool("disconnected").add_function(disconnect);
	

	universal_triggers.add_trigger("connected", find_bool("connected"), 0);
	universal_triggers.find_bool("connected").add_function(connect);
	


}



void app::run()
{
	Event e;
	Clock time;
	while (win.isOpen())
	{
		if (win.pollEvent(e))
		{
			gui::SFML::ProcessEvent(e);
			if (e.type == Event::Closed)
			{
				find_bool("exit") = 1;
				win.close();
			}
		}
		universal_triggers.run();
		gui::SFML::Update(win, time.restart());
		for (short i = 0; i < menus.size(); i++)
			menus[i].run();

		
		win.clear();
		gui::SFML::Render(win);
		win.display();
	}
}
