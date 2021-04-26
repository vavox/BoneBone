/*
Файл з реалізацією функції Update класу Engine
*/
#include "Engine.h"
#include <iostream>

using namespace std;

using namespace sf;

void Engine::update(float _time)
{
	// Виклик функції оновлення персонажу гравця
	m_skell.update(_time);
}