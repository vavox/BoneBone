/*
Файл з реалізацією функцій класу рушія
*/
#include "Engine.h"
#include <iostream>

View view(Vector2f(640.f, 360.f), Vector2f(1280.f, 720.f));

using namespace std;
using namespace sf;

// Ініціалізація структури об'єкту гравця на карті
//Object player1;
Object boneBullet;

Engine::Engine()
{
	/* 
	   Vector2f - клас бібліотеки SFML, який призначений для роботи з двовимірними векторами. 
	   Клас визначає математичний вектор з координатами x та y. Його можна використовувати для визначення що має два параметри.
	*/
	// Вектор для зберігання значень розширення екрану
	
	
	// Визначення розширення екрану компєютера
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	resolution.x = 1280;
	resolution.y = 720;

	// Створення вікна SFML
	m_window.create(VideoMode(resolution.x, resolution.y), "Game", Style::Default);
	
	// Завантаження файлу фону в текстуру
	m_BackgroundTexture.loadFromFile("res/background1.png");

	// Створення файлу з текстури
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	font.loadFromFile("res/joystix.ttf");
	life.setFont(font);
	gameover.setFont(font);
	checkp.setFont(font);
	
}


void Engine::start()
{
	cout << "Engine start" << endl;
	// Ініціалізація створення змінної часу
	Clock clock;
	
	// Завантаження карти в форматі tmx
	//level.LoadFromFile("maps/test3.tmx");
	
		// Завантаження данних об'єкту гравця з карти
	
	
	// Завантаження спрайту персонажу в об'єкт гравця
	//player.sprite = m_skell.getSprite();

	// Початковий рівень землі
	m_skell.setGround(546);
	life.setCharacterSize(24);
	life.setFillColor(Color::Green);
	life.setOutlineColor(Color::Black);
	gameover.setCharacterSize(64);
	gameover.setFillColor(Color::Red);
	gameover.setOutlineColor(Color::Black);
	gameover.setString("U`r dead!");
	checkp.setCharacterSize(24);
	checkp.setFillColor(Color::White);
	checkp.setOutlineColor(Color::Black);
	checkp.setString("saved");

	Texture tx;
	tx.loadFromFile("res/bull.png");
	Sprite sp;
	sp.setTexture(tx);
	sp.setScale(0.75f, 0.75f);
	boneBullet.sprite = sp;
	boneBullet.rect.width = 35*0.75;
	boneBullet.rect.height = 11*0.75;
	// Стартові координати гравця
	//m_skell.setPosX(player1.rect.left);
	//m_skell.setPosY(player1.rect.top + m_skell.getHeight() * m_skell.getScale());
	// Нескінченний цикл "життя" вікна
	m_window.setFramerateLimit(120);
	m_window.setVerticalSyncEnabled(true);
	while (m_window.isOpen())
	{
		life.setString(to_string(m_skell.getLife()));
		//player.sprite = m_skell.getSprite();
		// Подія яка прймає стан вікна
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
			// Функцій вводу з клавіатури (управління), оновлення кадру та виводу на екран
			input();
		}
		
		
		// Перезапуск таймеру та запис часу в змінну
		Time dt = clock.restart();

		// Представлення виміряного часу в секундах
		float dtAsSeconds = dt.asSeconds();

		//// Функцій вводу з клавіатури (управління), оновлення кадру та виводу на екран
		//input(event);
		
		m_skell.update(dtAsSeconds);
		e_enem.update(dtAsSeconds);
		vector<Object> obj = e_enem.getEnemy(1);
		m_skell.enemyColl(obj);
		obj = e_enem.getEnemy(2);
		m_skell.enemyColl(obj);
		obj = e_enem.getEnemy(3);
		m_skell.enemyColl(obj);

		/*if (m_skell.getAttack())
		{
			combatInit();
		}*/

		if ((!e_enem.combatColl(boneBullet)) && m_skell.getAttack())
		{
			combatSystem(dtAsSeconds);
		}
		else
		{
			combatInit();
			m_skell.notAttack();
		}

		// Зміна позиції камери
		setPlayerView(m_skell.getpos_x(), m_skell.getpos_y());
		m_window.setView(view);
		// Очищення екрану
		m_window.clear();

		// Візуалізація фону та мапи
		m_window.draw(m_BackgroundSprite);
		m_skell.drawlevelbylayer(m_window, 0);
		//level.Draw(m_window);
		// Візуалізація персонажу гравця
		if (m_skell.getLife() > 0)
		{
			m_window.draw(m_skell.getSprite());//player.sprite);
		}
		if (m_skell.getAttack())
		{
			m_window.draw(boneBullet.sprite);
		}
		e_enem.draw(m_window);
		//m_skell.drawlevelbylayer(m_window, 1);
		m_window.draw(life);
		
		if (m_skell.getLife() <= 0)
		{
			m_window.draw(gameover);
		}
		if (m_skell.checkpoint())
		{
			m_window.draw(checkp);
		}
	
	
		

		
		// Сам вивід всього на екран
		m_window.display();
		
	}
}

// Камера
void Engine::setPlayerView(float X, float Y)
{
	float tempX = X;
	float tempY = Y;
	
	if (X < 640) { tempX = 640; }
	if (Y > 600) { tempY = 600; }
	//if (Y < 400) { tempY = 400; }

	checkp.setPosition(tempX - 102 + resolution.x / 2, tempY + resolution.y / 2 - 30);
	gameover.setPosition(tempX - 200, tempY);
	life.setPosition(tempX - resolution.x / 2, tempY - resolution.y / 2);

	if ((tempX + resolution.x / 2) < boneBullet.rect.left)
	{
		combatInit();
		m_skell.notAttack();
	}
	view.setCenter(tempX, tempY);
}

void Engine::menu(RenderWindow& window)
{

}

void Engine::combatInit()
{
	boneBullet.name = "boneBullet";
	boneBullet.sprite;
	
	boneBullet.rect.left = m_skell.getpos_x() + m_skell.getWidth()/2;
	boneBullet.rect.top = m_skell.getpos_y() + 50;

	boneBullet.sprite.setPosition(boneBullet.rect.left, boneBullet.rect.top);
}

void Engine::combatSystem(float _time)
{
	boneBullet.rect.left += _time * (/*m_skell.getSpeed()*/850);
	boneBullet.sprite.setPosition(boneBullet.rect.left, boneBullet.rect.top);
}