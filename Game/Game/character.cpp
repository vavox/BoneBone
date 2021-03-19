/*
Файл з реалізацією функцій класу гравця
*/
#include "character.h"
#include <iostream>

using namespace std;

skell::skell()
{
	// Швидкість гравця
	m_speed = 700;

	// Завантаження текстури
	m_texture.loadFromFile("res/bob.png");

	// Створення спрайту з текстури
	m_sprite.setTexture(m_texture);

	// Маштаб спрайту
	m_sprite.setScale(0.5f, 0.5f);

	// Позиція спрайту гравця в пікселях
	m_pos.x = 700;
	m_pos.y = 300;

	m_onJump = false;
}

// Функція для доступу до спрайту
Sprite skell::getSprite()
{
	return m_sprite;
}

// Функції початку, припинення руху та падіння
void skell::moveleft()
{
	m_left = true;
}

void skell::moveright()
{
	m_right = true;
}

void skell::jump()
{
	m_space = true;
}

void skell::stopleft()
{
	m_left = false;
}

void skell::stopright()
{
	m_right = false;
}

void skell::fall(float _time)
{
	if (!m_onGround || m_onJump)
	{
		m_pos.y += m_speed * _time;
	}
	
	if(m_pos.y >= 600)
	{
		m_pos.y = 600;
		m_onGround = true;
		m_onJump = false;
	}	
}

void skell::not_jump()
{
	m_space = false;
}

// Функція оновлення кадру (відбувається рух персонажу гравця)
void skell::update(float _time)
{
	int temp = 0;
	
	cout << "skell update" << endl;

	
	
	if (m_right)
	{
		m_pos.x += m_speed * _time;
	}

	if (m_left)
	{
		m_pos.x -= m_speed * _time;
	}

	if (m_space && !m_onJump)
	{
		cout << m_pos.y << endl;
		m_pos.y -= m_speed * _time;
		if (m_pos.y < 350) { m_onJump = true; }
	}
	else
	{
		m_onGround = false;
	}

	
	fall(_time);

	// Зміна позиції спрайту
	m_sprite.setPosition(m_pos);
}


// Віддзеркалення спрайту
void skell::setRot()
{
	int temp_x = getpos_x();
	int temp_y = getpos_y();
	if (m_left)
	{
		m_sprite.setScale(0.5, 0.5);
		m_sprite.setPosition(temp_x-150, temp_y);
	}

	if (m_right)
	{
		m_sprite.setScale(-0.5, 0.5);
		m_sprite.setPosition(m_pos);
	}
}

int skell::getpos_y()
{
	return m_pos.y;
}

int skell::getpos_x()
{
	return m_pos.x;
}