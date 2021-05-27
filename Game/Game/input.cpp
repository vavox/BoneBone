/*
���� � ���������� ������� �����
*/
#include "Engine.h"
#include <iostream>
using namespace std;
using namespace sf;

// ������� ����� � ��������� (���������)
void Engine::input()
{
	

	if (menuStart)
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			menuMoveUp();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			menuMoveDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			menuEnter();
		}
	}
	else
	{
		// ����� � ���/� ���� �����
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			currentMenuElem = 0;
			toLevel = false;
			info = false;
			menuStart = true;
			menuInit();
		}
	}

	if (toLevel)
	{
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			m_skell.drawall = false;
			m_skell.draw2nd = false;
			m_skell.draw3d = false;
			m_skell.draw1st = true;
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			m_skell.drawall = false;
			m_skell.draw3d = false;
			m_skell.draw1st = false;
			m_skell.draw2nd = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			m_skell.drawall = false;
			m_skell.draw2nd = false;
			m_skell.draw1st = false;
			m_skell.draw3d = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			m_skell.draw2nd = false;
			m_skell.draw1st = false;
			m_skell.draw3d = false;
			m_skell.drawall = true;
		}

		if (m_skell.getLife() <= 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				m_skell.toCheckpoint();
				e_enem.start();
			}
		}
		else
		{
			// ��� ����
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				m_skell.moveleft();
			}
			else
			{
				m_skell.stopleft();
			}

			// ��� ������
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				m_skell.moveright();
			}
			else
			{
				m_skell.stopright();
			}

			// �������
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				m_skell.jump();
			}
			else
			{
				m_skell.not_jump();
			}

			if (!m_skell.getAttack())
			{
				if (Keyboard::isKeyPressed(Keyboard::K))
				{
					m_skell.rangeAttack();
					combatInit();
				}

			}

		}
	}
}

