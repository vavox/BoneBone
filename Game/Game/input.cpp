/*
���� � ���������� ������� �����
*/
#include "Engine.h"
#include <iostream>
using namespace std;

// // ������� ����� � ��������� (���������)
void Engine::input()
{
	cout << "input" << endl;
	// ����� � ���/� ���� �����
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_window.close();
	}

	// ��� ����
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_skell.setRot();
		m_skell.moveleft();
	}
	else
	{
		m_skell.stopleft();
	}

	// ��� ������
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		cout << "Pressed D" << endl;
		m_skell.setRot();
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

}