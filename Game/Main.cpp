#include "Game.h"
#include <variant>

Game game;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	game.Update(dt);



	/*std::vector<ds::Color> colors = { ds::Color::white, ds::Color::red, ds::Color::blue, ds::Color::green, ds::Color::purple, ds::Color::cyan, ds::Color::orange };

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		engine.Get<ds::ParticleSystem>()->Create(psPosition, 100, 10, colors, 150);
		engine.Get<ds::AudioSystem>()->PlayAudio("explosion");
	}*/

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	/*int x, y;
	Core::Input::GetMousePos(x, y);
	graphics.DrawString(10, 10, std::to_string(x).c_str());
	graphics.DrawString(10, 30, std::to_string(y).c_str());*/

	game.Draw(graphics);
}

int inc(int i) { return ++i; }
int dec(int i) { return --i; }

union Data
{
	int i;
	char str[5];
	bool b;
};

int main()
{
	Data data{ 0 };
	data.b = true;
	data.i = 534;
	data.str[0] = '#';

	//std::cout << data.i << std::endl;
	//std::cout << data.b << std::endl;
	//std::cout << data.str << std::endl;

	std::variant<int, std::string, float, bool> var;
	var = 20;
	var = true;

	//std::cout << std::get<int>(var) << std::endl;
	std::cout << std::get<3>(var) << std::endl;

	/*int (*operation)(int);
	operation = &inc;

	std::cout << operation(5) << std::endl;*/
	//system("pause");

	char name[] = "CSC196";
	Core::Init(name, 1000, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();

	Core::GameLoop();

	Core::Shutdown();
	game.Shutdown();
}