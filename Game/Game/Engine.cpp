/*
Файл з реалізацією функцій класу рушія
*/
#include "Engine.h"
#include <iostream>

using namespace std;
using namespace sf;


Engine::Engine()
{
	/* 
	   Vector2f - клас бібліотеки SFML, який призначений для роботи з двовимірними векторами. 
	   Клас визначає математичний вектор з координатами x та y. Його можна використовувати для визначення що має два параметри.
	*/
	// Вектор для зберігання значень розширення екрану
	Vector2f resolution;
	
	// Визначення розширення екрану компєютера
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	resolution.x = 1280;
	resolution.y = 720;

	// Створення вікна SFML
	m_window.create(VideoMode(resolution.x, resolution.y), "Game", Style::Default);
	
	// Завантаження файлу фону в текстуру
	m_BackgroundTexture.loadFromFile("res/background.jpg");

	// Створення файлу з текстури
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
}

void Engine::start()
{
	cout << "Engine start" << endl;
	// Ініціалізація створення змінної часу
	Clock clock;

	// Нескінченний цикл "життя" вікна
	while (m_window.isOpen())
	{
		// Подія яка прймає стан вікна
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		// Перезапуск таймеру та запис часу в змінну
		Time dt = clock.restart();

		// Представлення виміряного часу в секундах
		float dtAsSeconds = dt.asSeconds();

		// Функцій вводу з клавіатури (управління), оновлення кадру та виводу на екран
		input();
		update(dtAsSeconds);
		draw();
	}
}