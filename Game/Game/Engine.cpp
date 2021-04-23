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
//Object player;

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

	
}




void Engine::start()
{
	cout << "Engine start" << endl;
	// ����������� ��������� ����� ����
	Clock clock;
	
	// ������������ ����� � ������ tmx
	level.LoadFromFile("maps/test3.tmx");

	// ������������ ������ ��'���� ������ � �����
	//player = level.GetObject("player");
	
	// ������������ ������� ��������� � ��'��� ������
	//player.sprite = m_skell.getSprite();

	// ���������� ����� ����
	m_skell.setGround(1000);

	// ������� ���������� ������
	/*m_skell.setPosX(player.rect.left);
	m_skell.setPosY(player.rect.top + m_skell.getHeight() * m_skell.getScale());*/
	// ����������� ���� "�����" ����
	while (m_window.isOpen())
	{
		//player.sprite = m_skell.getSprite();
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
	
		setPlayerView(m_skell.getpos_x(), m_skell.getpos_y());
		m_window.setView(view);
		//�������� ������
		m_window.clear();

		// ³��������� ����
		m_window.draw(m_BackgroundSprite);

		level.Draw(m_window);
		// ³��������� ��������� ������
		m_window.draw(m_skell.getSprite());//player.sprite);

		// ��� ���� ������ �� �����
		m_window.display();
		//draw(m_window);
	}
}

// ������
void Engine::setPlayerView(float X, float Y)
{
	float tempX = X;
	float tempY = Y;

	if (X < 640) { tempX = 640; }
	if (Y > 500) { tempY = 600; }
	//if (Y < 400) { tempY = 400; }
	view.setCenter(tempX, tempY);
}

// ������� � ��'������ �����
//void Engine::mapInteraction()
//{
//	// ���������� ������
//	player.rect.top = m_skell.getpos_y();// -m_skell.getHeight() * m_skell.getScale();
//	player.rect.left = m_skell.getpos_x();
//	//m_skell.setpos(player.rect.left, player.rect.top);
//	// ����������� ������� ��'���� ����
//	
//	vector<Object> obj = level.GetObjects("solid");
//	
//	for (int i = 0; i < obj.size(); i++)
//	{
//		
//		if (player.rect.intersects(obj[i].rect))
//		{
//			if (obj[i].type == "ground")
//			{
//				
//
//				if (m_skell.m_Y > 0)
//				{
//					m_skell.setPosY(obj[i].rect.top - player.rect.height);
//					m_skell.m_Y = 0;
//					m_skell.m_onGround = true;
//					m_skell.setGround(obj[i].rect.top);
//				}
//				if (m_skell.m_Y < 0)
//				{
//					m_skell.setPosY(obj[i].rect.top + obj[i].rect.height);
//					m_skell.m_Y = 0;
//					m_skell.m_onGround = false;
//				}
//				//cout << i << endl;
//				if ((i > 0) && (i < obj.size()))
//				{
//					if (player.rect.intersects(obj[i + 1].rect))
//					{
//						cout << "i - 1 " << obj[i].rect.left << endl;
//						if (m_skell.m_X > 0)
//						{
//							m_skell.setPosX(obj[i + 1].rect.left - player.rect.width);
//							
//						}
//					}
//					if (player.rect.intersects(obj[i - 1].rect))
//					{
//						if (m_skell.m_X < 0)
//						{
//							m_skell.setPosX(obj[i - 1].rect.left + obj[i - 1].rect.width);
//							
//						}
//					}
//				}
//
//
//			}
//			if (obj[i].type == "wall")
//			{
//				if (m_skell.m_X > 0)
//				{
//					m_skell.setPosX(obj[i].rect.left - player.rect.width);
//					m_skell.m_X = 0;
//				}
//				if (m_skell.m_X < 0)
//				{
//					m_skell.setPosX(obj[i].rect.left + obj[i].rect.width);
//					m_skell.m_X = 0;
//				}
//			}
//		}
//		/*cout << "player top " << player.rect.top << endl;
//		cout << "obj top " << obj[i].rect.top << endl;*/
//		//cout << "map_coll" << endl;
//		//if (player.rect.left >= obj[i].rect.left)
//		//{
//		//	if (obj[i].type == "ground")
//		//	{
//		//		m_skell.setGround(obj[i].rect.top);// +obj[i].rect.height);
//		//		//groundTop = obj[i].rect.top;
//		//	}
//		//}
//		//
//
//		//if (player.rect.intersects(obj[i].rect))
//		//{
//		//	
//		//	if (obj[i].type == "ground")
//		//	{
//		//		m_skell.setGround(obj[i].rect.top);// +obj[i].rect.height);
//		//		m_skell.setPos(player.rect.left, obj[i].rect.top - m_skell.getHeight() * m_skell.getScale());
//		//		
//		//		//cout << "obj top " << player.rect.top << endl;
//		//	}
//		//	if (obj[i].type == "wall")
//		//	{
//		//		if (player.rect.left < obj[i].rect.left)
//		//		{
//		//			m_skell.setPos(obj[i].rect.left - m_skell.getWidth() * m_skell.getScale(), player.rect.top + m_skell.getHeight() * m_skell.getScale());
//		//		}
//		//		else
//		//		{
//		//			m_skell.setPos(obj[i].rect.left + obj[i].rect.width, player.rect.top + m_skell.getHeight() * m_skell.getScale());
//		//		}
//		//	}
//		//}
//	}
//}


