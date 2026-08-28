#include <iostream>
#include <thread>
#include <chrono>
#include "Defines.h"
#include "RenderEngine.h"

using namespace std;

int main()
{
	size_t sizeZoo;
	std::cin >> sizeZoo;
	RenderEngine engine(sizeZoo);

	engine.printZoo();
	engine.move("cat", Directions::LEFT);
	engine.move("cat", Directions::RIGHT);
	engine.move("mouse", Directions::UP);
	engine.printZoo();

	//while (true) {
	//	renderer.render();
	//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//}
}