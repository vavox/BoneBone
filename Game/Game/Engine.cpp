/*
���� � ���������� ������� ����� �����
*/
#include "Engine.h"
//#include "view.h"
#include <iostream>

View view(Vector2f(640.f, 360.f), Vector2f(1280.f, 720.f));

using namespace std;
using namespace sf;

// ����������� ��������� ��'���� ������ �� ����
//Object player1;

Engine::Engine()
{
	/* 
	   Vector2f - ���� �������� SFML, ���� ����������� ��� ������ � ����������� ���������. 
	   ���� ������� ������������ ������ � ������������ x �� y. ���� ����� ��������������� ��� ���������� �� �� ��� ���������.
	*/
	// ������ ��� ��������� ������� ���������� ������
	
	
	// ���������� ���������� ������ ���������
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	resolution.x = 1280;
	resolution.y = 720;

	// ��������� ���� SFML
	m_window.create(VideoMode(resolution.x, resolution.y), "Game", Style::Default);
	
	// ������������ ����� ���� � ��������
	m_BackgroundTexture.loadFromFile("res/background1.png");

	// ��������� ����� � ��������
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	font.loadFromFile("res/joystix.ttf");
	life.setFont(font);
	gameover.setFont(font);
	checkp.setFont(font);
	
}


void Engine::start()
{
	cout << "Engine start" << endl;
	// ����������� ��������� ����� ����
	Clock clock;
	
	// ������������ ����� � ������ tmx
	//level.LoadFromFile("maps/test3.tmx");
	
		// ������������ ������ ��'���� ������ � �����
	
	
	// ������������ ������� ��������� � ��'��� ������
	//player.sprite = m_skell.getSprite();

	// ���������� ����� ����
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

	
	// ������� ���������� ������
	//m_skell.setPosX(player1.rect.left);
	//m_skell.setPosY(player1.rect.top + m_skell.getHeight() * m_skell.getScale());
	// ����������� ���� "�����" ����
	m_window.setFramerateLimit(120);
	m_window.setVerticalSyncEnabled(true);
	while (m_window.isOpen())
	{
		life.setString(to_string(m_skell.getLife()));
		//player.sprite = m_skell.getSprite();
		// ���� ��� ����� ���� ����
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
			// ������� ����� � ��������� (���������), ��������� ����� �� ������ �� �����
			input();
		}
		
		
		// ���������� ������� �� ����� ���� � �����
		Time dt = clock.restart();

		// ������������� ��������� ���� � ��������
		float dtAsSeconds = dt.asSeconds();

		//// ������� ����� � ��������� (���������), ��������� ����� �� ������ �� �����
		//input(event);
		
		m_skell.update(dtAsSeconds);
		
		// ���� ������� ������
		setPlayerView(m_skell.getpos_x(), m_skell.getpos_y());
		m_window.setView(view);
		// �������� ������
		m_window.clear();

		// ³��������� ���� �� ����
		m_window.draw(m_BackgroundSprite);
		m_skell.drawlevel(m_window);
		//level.Draw(m_window);
		// ³��������� ��������� ������
		m_window.draw(m_skell.getSprite());//player.sprite);
		m_window.draw(life);

		if (m_skell.getLife() <= 0)
		{
			m_window.draw(gameover);
		}
		if (m_skell.checkpoint())
		{
			m_window.draw(checkp);
		}
		heavy.update(dtAsSeconds);
		heavy.draw(m_window);
		vector<Object> obj = heavy.getEnemy(1);
		m_skell.enemyColl(obj);
		obj = heavy.getEnemy(2);
		m_skell.enemyColl(obj);
		obj = heavy.getEnemy(3);
		m_skell.enemyColl(obj);

		// ��� ���� ������ �� �����
		m_window.display();
		
	}
}

// ������
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


	view.setCenter(tempX, tempY);
}

