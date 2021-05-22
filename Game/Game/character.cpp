/*
Файл з реалізацією функцій класу гравця
*/
#include "character.h"
#include <iostream>


using namespace std;
Level level;
Object player;


skell::skell()
{
	// Швидкість гравця
	m_speed = 350; // 400 default

	// Завантаження текстури
	m_texture.loadFromFile("res/skullMainTestNew.png");

	// Створення спрайту з текстури
	m_sprite.setTexture(m_texture);

	// Висота та ширина спрайту гравця
	m_pHeight = 130;
	m_pWidth = 55;
	m_pAnimBuff = 114;

	// Значеня маcштабу (спрайту гравця)
	m_pScale = 1.f;

	// Зміщення до фрагменту спрайту
	m_sprite.setTextureRect(IntRect(0, 263, m_pAnimBuff, m_pHeight));
	
	// Маштаб спрайту
	m_sprite.setScale(m_pScale, m_pScale);


	//m_sprite.setOrigin(0, (m_pWidth* m_pScale)/2);

	// Позиція спрайту гравця в пікселях
	level.LoadFromFile("maps/test3.tmx");
	player = level.GetObject("player");
	player.sprite = getSprite();
	setPosX(player.rect.left);
	setPosY(player.rect.top + m_pHeight*m_pScale);
	m_life = 100;
	m_score = 0;

	m_checkpointScore = 0;
	// 
	//m_groundlvl3= 600;
	m_maxjump = 400;//250;

	// номер кадру
	m_Frame = 1;
	m_onGround = true;
	m_onJump = false;
	m_onGroundAnim = false;
	m_X = 0;
	m_Y = 0.1;
	m_fall = false;

	m_range = false;
	m_melee = false;
	
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

void skell::rangeAttack()
{
	m_range = true;
}

void skell::notAttack()
{
	m_range = false;
	m_melee = false;
}

void skell::meleeAtack()
{
	m_melee = false;
}

bool skell::getAttack()
{
	if (m_range || m_melee) { return true; }
	else { return false; }
}
// Функція роботи анімації
void skell::animation(float _time)
{
	// Анімація руху вправо, вліво та стрибка
	if (m_onGroundAnim && !m_onJump)
	{
		if (m_right && !m_left)
		{
			m_Frame += 17 * _time;
			//cout << "\nframe" <<_time<< endl;
			if (m_Frame > 8) { m_Frame -= 8; }
			m_sprite.setTextureRect(IntRect(115 * int(m_Frame), 0, m_pAnimBuff, m_pHeight));
			m_sprite.move(0.1 * _time, 0);
			//player.rect.width = m_pAnimBuff;
		}
		else if (m_left && !m_right)
		{
			m_Frame +=  17 * _time;
			//cout << "\nframe" <<_time<< endl;
			if (m_Frame > 8) { m_Frame -= 7; }
			m_sprite.setTextureRect(IntRect(115 * int(m_Frame), 131, m_pAnimBuff, m_pHeight));
			m_sprite.move(-0.1 * _time, 0);
			//player.rect.width = m_pAnimBuff;
		}
		else
		{
			//player.rect.width = m_pWidth;
			if (!m_right)
			{
				m_sprite.setTextureRect(IntRect(30, 263, 84, m_pHeight));
			}
			if (!m_left)
			{
				m_sprite.setTextureRect(IntRect(30, 263, 84, m_pHeight));
			}
			if (m_right && m_left)
			{
				m_sprite.setTextureRect(IntRect(30, 263, 84, m_pHeight));
			}
		}
	}
	if (m_onJump || !m_onGround)
	{
		//player.rect.width = m_pWidth;
		if (m_right)
		{
			m_sprite.setTextureRect(IntRect(231, 0, m_pAnimBuff, m_pHeight));
		}
		else if (m_left)
		{
			m_sprite.setTextureRect(IntRect(231, 131, m_pAnimBuff, m_pHeight));
		}
		else
		{
			m_sprite.setTextureRect(IntRect(231, 0, m_pAnimBuff, m_pHeight));
		}
		
	}
	
}

// Функція "Гравітації"
void skell::fall(float _time)
{
	m_pos.y += 1.2 * (m_speed + 50.0) * powf(_time, 0.656)* m_Y;
}


void skell::not_jump()
{
	m_space = false;
}

// Функція оновлення кадру (відбувається рух персонажу гравця)
void skell::update(float _time)
{
	if (m_life <= 0)
	{
		m_canMove = false;
	}
	//m_X = 0;
	if (!m_fall)
	{
		m_canJump = true;	
	}

	if (m_canMove)
	{
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
			m_onJump = true;
			m_onGroundAnim = false;
			m_fall = true;

			m_pos.y -= 1.2 * (m_speed + 50.0) * powf(_time, 0.987);
			m_Y = -0.1;
			if (m_pos.y < m_groundlvl - m_maxjump)
			{
				m_onGround = false;
				m_canJump = false;
			}
		}
		else
		{
			m_canJump = false;
		}
	}
	
	
	
	//cout << "time: " << _time << endl;
	animation(_time);
	
	if (m_onGround)
	{
		m_onJump = false;
		m_canMove = true;
	}
	
	if ((m_pos.x + m_pWidth * m_pScale < m_groundleft) || (m_pos.x > m_groundright))
	{
		if (!m_fall)
		{
			m_Y = 0.01;  
		}
		m_fall = true;
		m_onJump = true;
		m_X = 0;		
	}
	
	m_Y = m_Y + _time * 0.95;
	if (m_Y > 10)
	{
		m_Y = 10;
	}

	fall(_time);
	
	if (!m_fall)
	{
		m_pos.y = m_groundlvl - m_pHeight * m_pScale;
	}
	/*okrema function yaka pereviryaye chi intersects z object pered perevirkoyu X, yakshco intersects po Y v mezhah objecta to m_X = 0*/
	
	if (mapHelp())
	{
		m_X = 0;
	}
	
	mapInteraction(m_X, 0);

	mapInteraction(0, m_Y);

	// Зміна позиції спрайту
	m_sprite.setPosition(m_pos.x, m_pos.y);
	
	m_score += 1;
		
}

int skell::getLife()
{
	return m_life;
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

bool skell::getCanMove()
{
	return m_canMove;
}

void skell::setBools(bool tmp)
{
	m_onGround = tmp;
}

void skell::setLife(int newLife)
{
	m_life = newLife;
}

void skell::drawlevel(RenderWindow& window)
{
	level.Draw(window);

}

void skell::drawlevelbylayer(RenderWindow& window, int layer)
{
	level.DrawByLayer(window, layer);
}

void skell::toCheckpoint()
{
	m_life = 100;
	setPosX(m_checkpointPos.x);
	setPosY(m_checkpointPos.y);
	m_score = m_checkpointScore;
}

bool skell::checkpoint()
{
	vector<Object> obj = level.GetObjects("checkpoint");
	for (int i = 0; i < obj.size(); i++)
	{
		
		if (player.rect.intersects(obj[i].rect))
		{
			//cout << "checkpoint passed\n";
			//m_checkpointLife = m_life;
			m_checkpointScore = m_score;
			m_checkpointPos.x = obj[i].rect.left + obj[i].rect.width + 1;
			m_checkpointPos.y = m_pos.y;
			/*cout << m_checkpointPos.x << " " << m_checkpointPos.y << endl;*/
			return true;
		}
		
	}
	return false;
}

void skell::enemyColl(vector<Object>& obj)
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (player.rect.intersects(obj[i].rect))
		{
			
			m_life -= 100;
			if (m_pos.x > obj[i].rect.left)
			{
				m_pos.x += 50;
				m_canMove = false;
			}
			if (m_pos.x < obj[i].rect.left)
			{
				m_pos.x -= 50;
				m_canMove = false;
			}
		}
	}
}

bool skell::mapHelp()
{
	player.rect.top = m_pos.y;
	player.rect.left = m_pos.x;
	// Ініціалізація вектору об'єктів мапи
	
	vector<Object> obj = level.GetAllObjects();
	//vector<Object> tmp = level.GetObjects("notX");
	for (int i = 0; i < obj.size(); i++)
	{
		if (obj[i].name == "solid")
		{
			if (player.rect.intersects(obj[i].rect))
			{
				if (((player.rect.left + player.rect.width) > obj[i].rect.left + player.rect.width / 3) && (player.rect.left < obj[i].rect.left + obj[i].rect.width - player.rect.width / 3))
				{
					if (player.rect.top + player.rect.height > obj[i].rect.top) { return true; }
				}
			}
		}
		if (obj[i].name == "notX")
		{
			if (player.rect.intersects(obj[i].rect))
			{
				if (m_right) { m_X = 1; }
				if (m_left) { m_X = -1; }
				return false;
			}
		}
		if (obj[i].name == "ur_dead")
		{
			if (player.rect.intersects(obj[i].rect))
			{
				m_life = 0;
			}
		}
	}
	return false;
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
				if ((y > 0))
				{
					setPosY(obj[i].rect.top - player.rect.height);

					m_Y = 0;
					m_onGround = true;
					m_onGroundAnim = true;
					m_fall = false;
					m_groundleft = obj[i].rect.left;
					m_groundright = obj[i].rect.left + obj[i].rect.width;
					m_canMove = true;
					setGround(obj[i].rect.top);
				}
				if (y < 0)
				{
					if (player.rect.top + player.rect.height > obj[i].rect.top + obj[i].rect.height)
					{
						setPosY(obj[i].rect.top + obj[i].rect.height);
						m_onGround = false;
						m_Y = 0;
					}

				}
				if ((player.rect.top + player.rect.height >= obj[i].rect.top + obj[i].rect.height))
				{
					if ((player.rect.left + player.rect.width > obj[i].rect.left) || (player.rect.left < obj[i].rect.left + obj[i].rect.width))
					{
						if (m_Y < 0) { x = 0; }
					}
				}

				if (x > 0)
				{
					setPosX(obj[i].rect.left - player.rect.width);
				}
				if (x < 0)
				{
					setPosX(obj[i].rect.left + obj[i].rect.width);
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


enemy::enemy()
{
	// Швидкість гравця
	e_speed_heavy = 200;
	e_speed_fly = 150; // 400 default
	
	// Клас Ворогу
	vector<Object> e_enemy = level.GetObjects("enemy");
	cout << e_enemy.size() << endl;

	// Позиція спрайту гравця в пікселях
	for(int i = 0; i < e_enemy.size(); i++)
	{
		if (e_enemy[i].type == "heavy")
		{
			heavy.push_back(e_enemy[i]);
		}

		if (e_enemy[i].type == "range")
		{
			range.push_back(e_enemy[i]);
		}

		if (e_enemy[i].type == "fly")
		{
			fly.push_back(e_enemy[i]);
		}

	}
	j = 0;
	e_type = 3;
	start();
	//m_sprite.setOrigin(m_pWidth * m_pScale, m_pHeight* m_pScale);
}

Sprite enemy::getSprite()
{
	return e_sprite_heavy;
}

void enemy::start()
{
	for (int i = 0; i < heavy.size(); i++)
	{
		e_pos.x = heavy[i].rect.left;
		e_pos.y = heavy[i].rect.top;
		
		// Висота та ширина спрайту гравця
		e_pHeight = heavy[i].rect.height;
		e_pWidth = heavy[i].rect.width;
		e_pAnimBuff = heavy[i].rect.width;

		// Завантаження текстури
		e_texture_heavy.loadFromFile("res/heavy.png");
		e_sprite_heavy.setTexture(e_texture_heavy);
		e_sprite_heavy.setTextureRect(IntRect(0, 0, e_pWidth, e_pHeight));
		e_sprite_heavy.setPosition(e_pos.x, e_pos.y);
		// Значееня маcштабу (спрайту гравця)
		e_pScale = 1.f;

		// Маштаб спрайту
		e_sprite_heavy.setScale(e_pScale, e_pScale);
		heavy[i].sprite = e_sprite_heavy;
	}

	for (int i = 0; i < range.size(); i++)
	{
		e_pos.x = range[i].rect.left;
		e_pos.y = range[i].rect.top;

		// Висота та ширина спрайту гравця
		e_pHeight = range[i].rect.height;
		e_pWidth = range[i].rect.width;
		e_pAnimBuff = range[i].rect.width;

		// Завантаження текстури
		e_texture_range.loadFromFile("res/red_bob.png");
		e_sprite_range.setTexture(e_texture_range);
		e_sprite_range.setTextureRect(IntRect(10, 0, e_pWidth, e_pHeight));
		e_sprite_range.setPosition(e_pos.x, e_pos.y);
		// Значееня маcштабу (спрайту гравця)
		e_pScale = 1.f;

		// Маштаб спрайту
		e_sprite_range.setScale(e_pScale, e_pScale);
		range[i].sprite = e_sprite_range;
	}

	for (int i = 0; i < fly.size(); i++)
	{
		e_pos.x = fly[i].rect.left;
		e_pos.y = fly[i].rect.top;

		// Висота та ширина спрайту гравця
		e_pHeight = fly[i].rect.height;
		e_pWidth = fly[i].rect.width;
		e_pAnimBuff = fly[i].rect.width;

		// Завантаження текстури
		e_texture_fly.loadFromFile("res/skullhead_small.png");
		e_sprite_fly.setTexture(e_texture_fly);
		e_sprite_fly.setTextureRect(IntRect(0, 0, e_pWidth, e_pHeight));
		e_sprite_fly.setPosition(e_pos.x, e_pos.y);
		// Значееня маcштабу (спрайту гравця)
		e_pScale = 1.f;

		// Маштаб спрайту
		e_sprite_fly.setScale(e_pScale, e_pScale);
		fly[i].sprite = e_sprite_fly;
	}
	
}

void enemy::rangeAttack(float _time)
{

}

void enemy::flyMove(float _time)
{
	int tmp = 1;
	for (int i = 0; i < fly.size(); i++)
	{
		j ++;
		fly[i].rect.left -= 2 *e_speed_fly * _time;
		if (j > 2)
		{
			tmp *= -1;
			j = 0;
		}

		//fly[i].rect.top += tmp  * e_speed_fly * _time;
		fly[i].sprite.setPosition(fly[i].rect.left, fly[i].rect.top);
	}
}

void enemy::heavyMove(float _time)
{
	vector<Object> obj = level.GetObjects("solid");
	for (int i = 0; i < heavy.size(); i++)
	{

		moveTimer += _time;
		if (moveTimer > 2)
		{
			e_speed_heavy *= -1;
			moveTimer = 0;
		}
		
		if (e_speed_heavy < 0)
		{
			e_left = true;
		}
		else
		{
			e_left = false;
		}

		
		heavy[i].rect.left += e_speed_heavy * _time;
		for (int k = 0; k < obj.size(); k++)
		{
			if (heavy[i].rect.intersects(obj[k].rect))
			{
				if (e_left)
				{
					heavy[i].rect.left = obj[k].rect.left + obj[k].rect.width;
				}
				else
				{
					heavy[i].rect.left = obj[k].rect.left - heavy[i].rect.width;
				}
			}
		}
		heavy[i].sprite.setPosition(heavy[i].rect.left, heavy[i].rect.top);
	}
}



void enemy::draw(RenderWindow& window)
{
	for (int i = 0; i < heavy.size(); i++)
	{
		if (!heavy.empty())
		{
			window.draw(heavy[i].sprite);
		}
	}
	for (int i = 0; i < range.size(); i++)
	{
		if (!range.empty())
		{
			window.draw(range[i].sprite);
		}
	}
	for (int i = 0; i < fly.size(); i++)
	{
		if (!fly.empty())
		{
			window.draw(fly[i].sprite);
		}
	}
}

void enemy::update(float _time)
{
	animation(_time);
	heavyMove(_time);	
	flyMove(_time);
}

void enemy::animation(float _time)
{
	for (int i = 0; i < heavy.size(); i++)
	{
		if (e_left)
		{
			e_Frame += 5 * _time;
			//cout << "\nframe" <<_time<< endl;
			if (e_Frame > 3) { e_Frame -= 3; }
			e_sprite_heavy.setTextureRect(IntRect(96 * int(e_Frame), 0, heavy[i].rect.width, heavy[i].rect.height));
			e_sprite_heavy.move(0.1 * _time, 0);
		}
		else
		{
			e_Frame += 5 * _time;
			//cout << "\nframe" <<_time<< endl;
			if (e_Frame > 3) { e_Frame -= 3; }
			e_sprite_heavy.setTextureRect(IntRect(96 * int(e_Frame), 0 + heavy[i].rect.height , heavy[i].rect.width, heavy[i].rect.height));
			e_sprite_heavy.move(0.1 * _time, 0);
		}
		heavy[i].sprite = e_sprite_heavy;
	}
	
}

vector<Object> enemy::getEnemy(int type)
{
	switch (type)
	{
	case 1: 
		if (!heavy.empty())
		{
			return heavy;
		}
	case 2:
		if (!range.empty())
		{
			return range;
		}
	case 3:
		if (!fly.empty())
		{
			return fly;
		}
	default:
		return {};
	}
}

bool enemy::combatColl(Object obj)
{
	vector<Object> enemTemp;
	vector<Object> allobj = level.GetObjects("solid");
	for (int i = 0; i < e_type; i++)
	{
		
		enemTemp = getEnemy(i + 1);
		if (enemTemp.empty())
		{
			return false;
		}
		for (int l = 0; l < enemTemp.size(); l++)
		{
			if (obj.rect.intersects(enemTemp[l].rect))
			{
				switch (i)
				{
				case 0:
					heavy.erase(heavy.begin() + l);
					return true;
					//break;
				case 1:
					range.erase(range.begin() + l);
					return true;
					//break;
				case 2:
					fly.erase(fly.begin() + l);
					return true;
					//break;
				default:
					break;
				}

			}
		}
		for (int k = 0; k < allobj.size(); k++)
		{
			if (obj.rect.intersects(allobj[k].rect))
			{
				return true;
			}
		}
	}

	return false;
}
