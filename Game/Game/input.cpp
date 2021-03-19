/*
Файл з реалізацією функцій вводу
*/
#include "Engine.h"
#include <iostream>
using namespace std;

// // Функцій вводу з клавіатури (управління)
void Engine::input()
{
	cout << "input" << endl;
	// Вихід з гри/в меню паузи
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_window.close();
	}

	// Рух вліво
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_skell.setRot();
		m_skell.moveleft();
	}
	else
	{
		m_skell.stopleft();
	}

	// Рух вправо
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