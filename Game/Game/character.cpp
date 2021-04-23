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
	m_speed = 600;

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
	m_maxjump = 300;

	// номер кадру
	m_Frame = 1;
	//m_onGround = true;
	m_onJump = false;
	m_X = 0;
	m_Y = 0.1;
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
	if (m_right && !m_left)
	{
		m_Frame += 10 *_time;
		//cout << "\nframe" <<_time<< endl;
		if (m_Frame > 8) { m_Frame -= 7; }
		m_sprite.setTextureRect(IntRect(109*int(m_Frame), 8, m_pAnimBuff, m_pHeight));
		m_sprite.move(0.1*_time, 0);
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

	if (m_onJump)
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
	m_pos.y += 1.2 * m_speed * powf(_time, 0.756)* m_Y;
}


void skell::not_jump()
{
	m_space = false;
}

// Функція оновлення кадру (відбувається рух персонажу гравця)
void skell::update(float _time)
{
	int temp = 0;
	 
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
	
	if (m_space && m_onGround)
	{
		m_onJump = true;
		
		
		m_pos.y -= 1.2*m_speed * powf(_time, 0.987);
		m_Y = -0.1;
		if (m_pos.y < m_groundlvl - m_maxjump)
		{
			cout << m_groundlvl - m_maxjump << endl;
			m_onGround = false;
		}
		
	}
	
	
	/*if ((m_pos.y + m_pHeight * m_pScale < m_groundlvl)&&!m_space)
	{
		m_onGround = false;
	}
	*/
	//cout << "time: " << _time << endl;
	animation(_time);
	
	//m_onGround = true;
	

	
	//if (!m_onGround)
	
		
		
	fall(_time);
		
	mapInteraction(m_X, 0);
	mapInteraction(0, m_Y);
	
		//if (m_Y != 0)
	//if (m_Y != 0)
	{
		m_Y = m_Y + _time * 0.95;
	}
	
	
	if (m_onGround)
	{
		m_onJump = false;
		cout << m_onGround << "|| j " << m_onJump << endl;
	}
	
	m_pos.y = round(m_pos.y - 0.5);

	// Зміна позиції спрайту
	m_sprite.setPosition(m_pos.x, m_pos.y);
	m_score += 1;
	
	//fall(_time);
}


/*/ Віддзеркалення спрайту
void skell::setRot()
{
	int temp_x = getpos_x();
	int temp_y = getpos_y();
	if (m_left)
	{
		m_sprite.setScale(-0.7, 0.7);
		m_sprite.setPosition(temp_x-150, temp_y);
	}

	if (m_right)
	{
		m_sprite.setScale(0.7, 0.7);
		m_sprite.setPosition(m_pos);
	}
}*/

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
	//m_skell.setpos(player.rect.left, player.rect.top);
	// Ініціалізація вектору об'єктів мапи

	vector<Object> obj = level.GetObjects("solid");

	for (int i = 0; i < obj.size(); i++)
	{

		if (player.rect.intersects(obj[i].rect))
		{
			if (obj[i].type == "ground")
			{

				//cout << m_Y << endl;
				//m_Y = round(m_Y);
				
				if (y > 0)
				{
					setPosY(obj[i].rect.top - player.rect.height);
					m_Y = 0;
					m_onGround = true;
					setGround(obj[i].rect.top);
				}
				if (y < 0)
				{
					setPosY(obj[i].rect.top + obj[i].rect.height);
					m_Y = 0;
					m_onGround = false;
				}
				/*if (x > 0)
				{
					setPosX(obj[i].rect.left - player.rect.width);

				}
				if (x < 0)
				{
					setPosX(obj[i].rect.left + obj[i].rect.width);

				}*/
				//cout << i << endl;
				
				if ((i > 0) && (i < obj.size()))
				{
					if (player.rect.intersects(obj[i + 1].rect))
					{
						cout << "i - 1 " << obj[i].rect.left << endl;
						setPosX(obj[i + 1].rect.left - player.rect.width - 15);
						
					}
					if (player.rect.intersects(obj[i - 1].rect))
					{
						
					}
				}


			}
			/*if (obj[i].type == "wall")
			{
				if (m_X > 0)
				{
					m_skell.setPosX(obj[i].rect.left - player.rect.width);
					m_skell.m_X = 0;
				}
				if (m_skell.m_X < 0)
				{
					m_skell.setPosX(obj[i].rect.left + obj[i].rect.width);
					m_skell.m_X = 0;
				}
			}*/
		}
		/*cout << "player top " << player.rect.top << endl;
		cout << "obj top " << obj[i].rect.top << endl;*/
		//cout << "map_coll" << endl;
		//if (player.rect.left >= obj[i].rect.left)
		//{
		//	if (obj[i].type == "ground")
		//	{
		//		m_skell.setGround(obj[i].rect.top);// +obj[i].rect.height);
		//		//groundTop = obj[i].rect.top;
		//	}
		//}
		//

		//if (player.rect.intersects(obj[i].rect))
		//{
		//	
		//	if (obj[i].type == "ground")
		//	{
		//		m_skell.setGround(obj[i].rect.top);// +obj[i].rect.height);
		//		m_skell.setPos(player.rect.left, obj[i].rect.top - m_skell.getHeight() * m_skell.getScale());
		//		
		//		//cout << "obj top " << player.rect.top << endl;
		//	}
		//	if (obj[i].type == "wall")
		//	{
		//		if (player.rect.left < obj[i].rect.left)
		//		{
		//			m_skell.setPos(obj[i].rect.left - m_skell.getWidth() * m_skell.getScale(), player.rect.top + m_skell.getHeight() * m_skell.getScale());
		//		}
		//		else
		//		{
		//			m_skell.setPos(obj[i].rect.left + obj[i].rect.width, player.rect.top + m_skell.getHeight() * m_skell.getScale());
		//		}
		//	}
		//}
	}
}