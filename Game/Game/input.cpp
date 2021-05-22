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
	// ����� � ���/� ���� �����
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_window.close();
	}

	if (m_skell.getLife() <= 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			m_skell.toCheckpoint();
		}
	}
	else//if(m_skell.getCanMove())
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
			else
			{
				//m_skell.notAttack();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::L))
		{
			cout << "L is pressed \n";
		}
		else
		{
			cout << "L isn`t pressed \n";
		}
	}
}
