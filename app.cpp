#include "app.h"

// NOT MY CODE https://gist.github.com/FRex/3f7b8d1ad1289a2117553ff3702f04af
LONG_PTR originalsfmlcallback = 0x0;

LRESULT CALLBACK mycallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{

	static chr file = create_array("file");
	static bool loaded = create_bool("file_loaded");
	if (message == WM_DROPFILES)
	{
		HDROP hdrop = reinterpret_cast<HDROP>(wParam);
		POINT p;


		const UINT filescount = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
		for (UINT i = 0; i < filescount; ++i)
		{
			const UINT bufsize = DragQueryFile(hdrop, i, NULL, 0);
			std::string str;
			str.resize(bufsize + 1);
			if (DragQueryFile(hdrop, i, &str[0], bufsize + 1))
			{
				std::string stdstr;
				sf::Utf8::fromWide(str.begin(), str.end(), std::back_inserter(stdstr));
				sf::FileInputStream a;
				a.open(stdstr);
				if (file.size < a.getSize())
					file.resize(a.getSize()+1);
				a.read(file.ptr, a.getSize());
				file.ptr[a.getSize()] = '\0';
			}
		}
		DragFinish(hdrop);
	}//if WM_DROPFILES
	return CallWindowProcW(reinterpret_cast<WNDPROC>(originalsfmlcallback), handle, message, wParam, lParam);
}
// NOT MY CODE 
app::app()
{
	load_triggers();
	load_menus();
	connection conn("127.0.0.1");
	win.create(VideoMode(720, 512), "win",Style::None);
	win.setFramerateLimit(30);
	gui::SFML::Init(win);

	run();
	gui::SFML::Shutdown();
	
}

void app::load_menus()
{
	menus.insert(pair<int, menu*>(0, new menu(menu0, "connecting")));
	menus.insert(pair<int, menu*>(1, new menu(menu1, "login")));
	menus.insert(pair<int,menu*>(2,new menu(menu2,"register")));
	menus.insert(pair<int, menu*>(3, new menu(menu3, "profile")));
	menus.insert(pair<int, menu*>(4, new menu(menu4, "problem_picker")));
	menus.insert(pair<int, menu*>(5, new menu(menu5, "problem_solver")));
	menus.insert(pair<int, menu*>(6, new menu(menu6, "quiz_solver")));
	
}

void app::load_triggers()
{

	auto disconnect = [](vector<void*>) {
		find_int("state") = 0;
		universal_triggers.find_bool("connected").ran = 0;
		universal_triggers.find_bool("logged").ran = 0;
		find_bool("logged") = 0;
		cout << " disc ";
	};

	auto connect = [](vector<void*>) {
		find_int("state") = 1;
		universal_triggers.find_bool("disconnected").ran = 0;
		cout << " con ";
	};

	auto log = [](vector<void*>) {
		find_int("state") = 3;
		create_request('b');
		auto req = find_of_type('b');
		auto &str = create_string("browser", "problems");
		req->load_in_position(&find_int("dir_forward"), 0, 'i');
		req->load_in_position(&str,1,'s');
	};

	universal_triggers.add_trigger("disconnected", find_bool("connected"), 0, 0);
	universal_triggers.find_bool("disconnected").add_function(disconnect);
	

	universal_triggers.add_trigger("connected", find_bool("connected"), 0);
	universal_triggers.find_bool("connected").add_function(connect);

	universal_triggers.add_trigger("logged", find_bool("logged"),1,0);
	universal_triggers.find_bool("logged").add_function(log);
	
}

void app::run()
{
	
	originalsfmlcallback = SetWindowLongPtrW(win.getSystemHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(mycallback));

	Event e;
	Clock time;
	
	while (win.isOpen())
	{
		DragAcceptFiles(win.getSystemHandle(), 1);
		while (win.pollEvent(e))
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
		menus[find_int("state")]->run();

		
		win.clear();
		gui::SFML::Render(win);
		win.display();
	}
	exit(EXIT_SUCCESS);
}
