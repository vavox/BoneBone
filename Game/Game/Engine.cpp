/*
���� � ���������� ������� ����� �����
*/
#include "Engine.h"
#include <iostream>

using namespace std;
using namespace sf;


Engine::Engine()
{
	/* 
	   Vector2f - ���� �������� SFML, ���� ����������� ��� ������ � ����������� ���������. 
	   ���� ������� ������������ ������ � ������������ x �� y. ���� ����� ��������������� ��� ���������� �� �� ��� ���������.
	*/
	// ������ ��� ��������� ������� ���������� ������
	Vector2f resolution;
	
	// ���������� ���������� ������ ���������
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	resolution.x = 1280;
	resolution.y = 720;

	// ��������� ���� SFML
	m_window.create(VideoMode(resolution.x, resolution.y), "Game", Style::Default);
	
	// ������������ ����� ���� � ��������
	m_BackgroundTexture.loadFromFile("res/background.jpg");

	// ��������� ����� � ��������
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
}

void Engine::start()
{
	cout << "Engine start" << endl;
	// ����������� ��������� ����� ����
	Clock clock;

	// ����������� ���� "�����" ����
	while (m_window.isOpen())
	{
		// ���� ��� ����� ���� ����
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		// ���������� ������� �� ����� ���� � �����
		Time dt = clock.restart();

		// ������������� ��������� ���� � ��������
		float dtAsSeconds = dt.asSeconds();

		// ������� ����� � ��������� (���������), ��������� ����� �� ������ �� �����
		input();
		update(dtAsSeconds);
		draw();
	}
}