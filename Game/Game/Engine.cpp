/*
Файл з реалізацією функцій класу рушія
*/
#include "Engine.h"
#include <iostream>

View view(Vector2f(640.f, 360.f), Vector2f(1280.f, 720.f));

using namespace std;
using namespace sf;

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
	m_window.create(VideoMode(resolution.x, resolution.y), "Engine", Style::Default);
	
	// Завантаження файлу фону в текстуру
	m_BackgroundTexture.loadFromFile("res/menu.png");

	// Створення файлу з текстури
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	menuElem = 3;
	currentMenuElem = 0;
	menuStart = true;
	toLevel = false;
	info = false;

	font.loadFromFile("res/joystix.ttf");
	life.setFont(font);
	gameover[0].setFont(font);
	gameover[1].setFont(font);
	checkp.setFont(font);
	hp.setFont(font);
	layerInf.setFont(font);
	
	menuInit();
	//initWorld();
}


void Engine::start()
{
	cout << "Engine start" << endl;
	// Ініціалізація створення змінної часу
	Clock clock;
	
	// Початковий рівень землі
	life.setCharacterSize(20);
	life.setFillColor(Color::Green);
	life.setOutlineColor(Color::Black);

	hp.setCharacterSize(20);
	hp.setFillColor(Color::White);
	hp.setOutlineColor(Color::Black);
	hp.setString("Health points: ");

	layerInf.setCharacterSize(20);
	layerInf.setFillColor(Color::White);
	layerInf.setOutlineColor(Color::Black);
	layerInf.setString("Num1 - 1st layer\nNum2 - 2nd layer\nNum3 - 3rd layer\nNum4 - all layers");

	gameover[0].setCharacterSize(64);
	gameover[0].setFillColor(Color::Red);
	gameover[0].setOutlineColor(Color::Black);
	gameover[0].setString("Press R to restart");
	gameover[1].setCharacterSize(64);
	gameover[1].setFillColor(Color::White);
	gameover[1].setOutlineColor(Color::Black);
	gameover[1].setString("Press R to start");

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
	boneBullet.rect.width = 35 * 0.75;
	boneBullet.rect.height = 11 * 0.75;
	// Стартові координати гравця

	// Нескінченний цикл "життя" вікна
	m_window.setFramerateLimit(120);
	m_window.setVerticalSyncEnabled(true);
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
			// Функцій вводу з клавіатури (управління), оновлення кадру та виводу на екран
			input();
		}
		
		if (menuStart)
		{
			m_window.setView(view);
			menuDraw(m_window);
		}

		if (toLevel)
		{
			
			//// Перезапуск таймеру та запис часу в змінну
			Time dt = clock.restart();

			// Представлення виміряного часу в секундах
			float dtAsSeconds = dt.asSeconds();
			//levelDraw(dtAsSeconds);
			life.setString(to_string(m_skell.getLife()));
			m_skell.update(dtAsSeconds);
			e_enem.update(dtAsSeconds);
			vector<Object> obj = e_enem.getEnemy(1);
			m_skell.enemyColl(obj);
			obj = e_enem.getEnemy(2);
			m_skell.enemyColl(obj);
			obj = e_enem.getEnemy(3);
			m_skell.enemyColl(obj);

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


			//m_skell.drawlevelbylayer(m_window, 0);
			m_skell.drawlevel(m_window);

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
			m_window.draw(hp);
			m_window.draw(layerInf);

			if ((m_skell.getLife() <= 0) && (m_skell.getLife() != -200))
			{
				m_window.draw(gameover[0]);
			}
			if (m_skell.getLife() == -200)
			{
				m_window.draw(gameover[1]);
			}
			if (m_skell.checkpoint())
			{
				m_window.draw(checkp);
			}
		}

		if (info)
		{
			menuInfo();
		}
		
		// Вивід всього на екран
		m_window.display();
		
	}
}

// Камера
void Engine::setPlayerView(float X, float Y)
{
	float tempX = X;
	float tempY = Y;
	
	if (X < 640) { tempX = 640; }
	if (Y > 1250) { tempY = 1250; }

	checkp.setPosition(tempX - 102 + resolution.x / 2, tempY + resolution.y / 2 - 30);
	gameover[0].setPosition(tempX - 450, tempY);
	gameover[1].setPosition(tempX - 400, tempY);

	hp.setPosition(tempX - resolution.x / 2, tempY - resolution.y / 2);
	life.setPosition(tempX  + 250 - resolution.x / 2, tempY - resolution.y / 2);
	layerInf.setPosition(tempX - 300 + resolution.x / 2, tempY - resolution.y / 2);

	if ((tempX + resolution.x / 2) < boneBullet.rect.left)
	{
		combatInit();
		m_skell.notAttack();
	}
	view.setCenter(tempX, tempY);
}

void Engine::menuInit()
{	
	menu[0].setFont(font);
	menu[0].setFillColor(Color::White);
	menu[0].setString("To level");
	menu[0].setPosition((resolution.x / 2) - 50, resolution.y / 2);
	menu[0].setCharacterSize(36);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Info");
	menu[1].setPosition((resolution.x / 2) - 50, resolution.y / 1.8);
	menu[1].setCharacterSize(24);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition((resolution.x / 2) - 50, resolution.y / 1.4);
	menu[2].setCharacterSize(24);

	infoT.setFont(font);
	infoT.setFillColor(Color::White);
	infoT.setString("The engine is working in real-time rendering mode.\nTo start an movement animation press these keys:\n    A - to move leftside;\n    D - to move rightside;\n    Space - to jump;\n    K - to shoot an object;\nAlso you can choose the layer of tiled map to render:\n    Num1 - to render only first layer;\n    Num2 - to render only second layer;\n    Num3 - to render only third layer;\n    Num4 - to render all layers;\nTo back to the menu press Escape.");
	infoT.setPosition(10, 10);
	infoT.setCharacterSize(24);
	view.setCenter(resolution.x / 2, resolution.y / 2);
}

void Engine::menuInfo()
{
	m_window.clear();
	m_window.draw(m_BackgroundSprite);
	m_window.draw(infoT);
}

void Engine::menuMoveUp()
{
	if (currentMenuElem - 1 >= 0)
	{
		menu[currentMenuElem].setCharacterSize(24);
		currentMenuElem--;
		menu[currentMenuElem].setCharacterSize(36);
	}
}

void Engine::menuMoveDown()
{
	if (currentMenuElem + 1 < menuElem)
	{
		menu[currentMenuElem].setCharacterSize(24);
		currentMenuElem++;
		menu[currentMenuElem].setCharacterSize(36);
	}
}

void Engine::menuDraw(RenderWindow& window)
{
	m_window.clear();
	m_window.draw(m_BackgroundSprite);
	for (int i = 0; i < menuElem; i++)
	{
		window.draw(menu[i]);
	}
}

void Engine::menuEnter()
{
	switch (currentMenuElem)
	{
	case 0:
		menuStart = false;
		info = false;
		toLevel = true;
		initWorld();
		break;
	case 1:
		menuStart = false;
		info = false;
		info = true;
		break;
	case 2:
		m_window.close();
		break;
	default:
		menuStart = true;
		info = false;
		toLevel = false;
		break;
	}
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


void Engine::initWorld()
{
	m_skell.setGround(546);
	m_skell.setLife(-200);
	//m_skell.loadMap("maps/test3.tmx");
}