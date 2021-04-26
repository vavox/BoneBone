/*
Файл з реалізацією функції Draw класу Engine (очищення вікна, виведення на екран фону та персонажу гравця)
*/
#include "Engine.h"




void Engine::draw(RenderWindow& window)
{
	Level level;
	level.LoadFromFile("maps/test.tmx");
	 //Очищення екрану
	m_window.clear();
	
	// Візуалізація фону
	m_window.draw(m_BackgroundSprite);

	level.Draw(window);
	// Візуалізація персонажу гравця
	m_window.draw(m_skell.getSprite());
	
	// Сам вивід всього на екран
	m_window.display();
}