/*
Файл з реалізацією функцій вводу
*/
#include "Engine.h"
#include <iostream>
using namespace std;
using namespace sf;

// Функцій вводу з клавіатури (управління)
void Engine::input()
{
	// Вихід з гри/в меню паузи
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
		// Рух вліво
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			m_skell.moveleft();
		}
		else
		{
			m_skell.stopleft();
		}

		// Рух вправо
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			m_skell.moveright();
		}
		else
		{
			m_skell.stopright();
		}

		// Стрибок
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			m_skell.jump();
		}
		else
		{
			m_skell.not_jump();
		}
	}
}
