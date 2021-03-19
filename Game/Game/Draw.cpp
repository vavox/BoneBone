/*
Файл з реалізацією функції Draw класу Engine (очищення вікна, виведення на екран фону та персонажу гравця)
*/
#include "Engine.h"

using namespace sf;

void Engine::draw()
{
	// Очищення екрану
	m_window.clear();

	// Візуалізація фону
	m_window.draw(m_BackgroundSprite);

	// Візуалізація персонажу гравця
	m_window.draw(m_skell.getSprite());

	// Сам вивід всього на екран
	m_window.display();
}