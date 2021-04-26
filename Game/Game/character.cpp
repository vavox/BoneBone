/*
Файл з реалізацією функцій класу гравця
*/
#include "character.h"
#include <iostream>
#include "map.h"

using namespace std;
Level level;
Object player;

skell::skell()
{
	// Швидкість гравця
	m_speed = 400;

	// Завантаження текстури
	m_texture.loadFromFile("res/scott2.png");

	// Створення спрайту з текстури
	m_sprite.setTexture(m_texture);

	// Висота та ширина спрайту гравця
	m_pHeight = 126;
	m_pWidth = 73;
	m_pAnimBuff = 104;

	// Значееня маcштабу (спрайту гравця)
	m_pScale = 0.5f;

	m_sprite.setTextureRect(IntRect(15, 263, m_pWidth, m_pHeight));
	
	// Маштаб спрайту
	m_sprite.setScale(m_pScale, m_pScale);

	//m_sprite.setOrigin(0, m_pHeight* m_pScale);

	// Позиція спрайту гравця в пікселях
	level.LoadFromFile("maps/test3.tmx");
	player = level.GetObject("player");
	player.sprite = getSprite();
	setPosX(player.rect.left);
	setPosY(player.rect.top + m_pHeight*m_pScale);
	m_life = 300;
	m_score = 0;
	// 
	//m_groundlvl3= 600;
	m_maxjump = 250;

	// номер кадру
	m_Frame = 1;
	//m_onGround = true;
	m_onJump = false;
	m_onGroundAnim = false;
	m_X = 0;
	m_Y = 0.1;
	m_fall = true;
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

// Функція роботи анімації
void skell::animation(float _time)
{
	// Анімація руху вправо, вліво та стрибка
	if (m_onGroundAnim && !m_onJump)
	{
		if (m_right && !m_left)
		{
			m_Frame += 10 * _time;
			//cout << "\nframe" <<_time<< endl;
			if (m_Frame > 8) { m_Frame -= 7; }
			m_sprite.setTextureRect(IntRect(109 * int(m_Frame), 8, m_pAnimBuff, m_pHeight));
			m_sprite.move(0.1 * _time, 0);
			//CurrnetFrame = 1;

		}
		else if (m_left && !m_right)
		{
			m_Frame += 10 * _time;
			//cout << "\nframe" <<_time<< endl;
			if (m_Frame > 8) { m_Frame -= 7; }
			m_sprite.setTextureRect(IntRect(108 * int(m_Frame), 145, m_pAnimBuff, m_pHeight));
			m_sprite.move(-0.1 * _time, 0);
			//CurrnetFrame = 1;

		}
		else
		{
			if (!m_right)
			{
				m_sprite.setTextureRect(IntRect(15, 263, m_pWidth, m_pHeight));
			}
			if (!m_left)
			{
				m_sprite.setTextureRect(IntRect(15, 263, m_pWidth, m_pHeight));
			}
			if (m_right && m_left)
			{
				m_sprite.setTextureRect(IntRect(15, 263, m_pWidth, m_pHeight));
			}
		}
	}
	if (m_onJump || !m_onGround)
	{
		if (m_right)
		{
			m_sprite.setTextureRect(IntRect(218, 8, m_pAnimBuff, m_pHeight));
		}
		else if (m_left)
		{
			m_sprite.setTextureRect(IntRect(218, 145, m_pAnimBuff, m_pHeight));
		}
		else
		{
			m_sprite.setTextureRect(IntRect(218, 8, m_pAnimBuff, m_pHeight));
		}
		
	}
	
}

// Функція "Гравітації"
void skell::fall(float _time)
{
	m_pos.y += 1.2 * m_speed * powf(_time, 0.656)* m_Y;
}


void skell::not_jump()
{
	m_space = false;
}

// Функція оновлення кадру (відбувається рух персонажу гравця)
void skell::update(float _time)
{
	if (!m_fall)
	{
		m_canJump = true;
	}
	
	

	if (m_right)
	{
		m_X = 1;
		m_pos.x += m_speed * _time * m_X;
		
	}
	

	if (m_left)
	{  
		m_X = -1;
		m_pos.x += m_speed * _time * m_X;
	
	}
	
	if (m_space && m_onGround && m_canJump)
	{
		if (m_right)
		{
			m_X = 1;
		}
		if (m_left)
		{
			m_X = -1;
		}
		m_onJump = true;
		m_onGroundAnim = false;
		m_fall = true;  
		
		m_pos.y -= 1.2*m_speed * powf(_time, 0.987);
		m_Y = -0.1;
		if (m_pos.y < m_groundlvl - m_maxjump)
		{
			cout << m_groundlvl - m_maxjump << endl;
			m_onGround = false;
			m_canJump = false;
		}
		
	}
	else
	{
		m_canJump = false;
	}
	
	
	//cout << "time: " << _time << endl;
	animation(_time);
	
	//m_onGround = true;
	
	if (m_onGround)
	{
		m_onJump = false;
		//cout << m_onGround << "|| j " << m_onJump << endl;
	}
	
	if ((m_pos.x + m_pWidth * m_pScale < m_groundleft) || (m_pos.x > m_groundright))
	{
	
		if (!m_fall)
		{
			m_Y = 0.01;  
		}
		m_fall = true;
		m_onJump = true;
		
	}
	m_Y = m_Y + _time * 0.95;

	if (!m_onGroundAnim || m_onJump)
	{
		m_X = 0; 
	}
	
	if (m_Y > 10)
	{
		m_Y = 10;
	}

	fall(_time);
	
	if (!m_fall)
	{
		m_pos.y = m_groundlvl - m_pHeight * m_pScale;
	}

	mapInteraction(m_X, 0);
	cout << "m_Y " << m_Y << endl;
	cout << "m_X " << m_X << endl;
	mapInteraction(0, m_Y);


	// Зміна позиції спрайту
	m_sprite.setPosition(m_pos.x, m_pos.y);
	
	
	m_score += 1;
		
}




float skell::getpos_y()
{
	return m_pos.y;
}

float skell::getpos_x()
{
	return m_pos.x;
}

void skell::setPosX(float x)
{
	m_pos.x = x;
}
void skell::setPosY(float y)
{
	m_pos.y = y;
}


void skell::setGround(float tmp)
{
	m_groundlvl = tmp;// -m_pHeight * m_pScale;
}

float skell::getHeight()
{
	return m_pHeight;
}

float skell::getScale()
{
	return m_pScale;
}

float skell::getWidth()
{
	return m_pWidth;
}

float skell::getGround()
{
	return m_groundlvl;
}

void skell::setBools(bool tmp)
{
	m_onGround = tmp;
}

void skell::mapInteraction(float x, float y)
{
	// Координати гравця
	player.rect.top = m_pos.y;// m_skell.getpos_y();// -m_skell.getHeight() * m_skell.getScale();
	player.rect.left = m_pos.x;//m_skell.getpos_x();
	
	// Ініціалізація вектору об'єктів мапи

	vector<Object> obj = level.GetObjects("solid");

	for (int i = 0; i < obj.size(); i++)
	{
		if (player.rect.intersects(obj[i].rect))
		{
			if (obj[i].type == "ground")
			{

				
				//m_Y = round(m_Y);
				
				if ((y > 0))
				{
					
					setPosY(obj[i].rect.top - player.rect.height);
					
					m_Y = 0;
					m_onGround = true;
					m_onGroundAnim = true;
					m_fall = false;
					m_groundleft = obj[i].rect.left;
					m_groundright = obj[i].rect.left + obj[i].rect.width;
					setGround(obj[i].rect.top);
					
					//cout << "Player top " << player.rect.top << "\nPlayer top + height - " << player.rect.top + player.rect.height << "\nObject top - " << obj[i].rect.top << endl;
					
				}
				if (y < 0)
				{
					setPosY(obj[i].rect.top + obj[i].rect.height);
					//setPosY(obj[i].rect.top + player.rect.height);
					m_onGround = false;
					//m_X = 0;
					m_Y = 0;
				}
				
				if (x > 0)
				{

					
					setPosX(obj[i].rect.left - player.rect.width);
					m_X = 0;
					
				}
				if (x < 0)
				{
					
					setPosX(obj[i].rect.left + obj[i].rect.width);
					m_X = 0;
					
					

				}
			}

			if (obj[i].type == "wall")
			{
				if (x > 0)
				{
					setPosX(obj[i].rect.left - player.rect.width);
					m_X = 0;
				}
				if (x < 0)
				{
					setPosX(obj[i].rect.left + obj[i].rect.width);
					m_X = 0;
				}
				
			}
		}
		
	}
}