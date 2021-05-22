/*
Файл з оголошенням класу гравця
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"


using namespace sf;

class skell
{
private:
	/*
	   Vector2f - клас бібліотеки SFML, який призначений для роботи з двовимірними векторами.
	   Клас визначає математичний вектор з координатами x та y. Його можна використовувати для визначення що має два параметри.
	*/
	// Вектор з координатами(позицією) гравця
	Vector2f m_pos; 

	// Оголошення об'єкту Sprite
	Sprite m_sprite; 
	
	// Оголошення об'єкту Texture
	Texture m_texture;

	// Логічні змінні для відслідження руху
	bool m_left;
	bool m_right;
	
	// Допоміжні логічні змінні для відслідження стрибку та перебування на землі
	bool m_fall;
	bool m_onGround;
	bool m_canJump;
	bool m_onJump;
	bool m_space;
	bool m_onGroundAnim;
	bool m_canMove;
	bool m_range;
	bool m_melee;
	
	
	// Кількість очків життя та загальний рахунок очків
	int m_life; 
	int m_score; 

	// Координата крайніх верхньої , лівої та правої координати об'єкта землі
	float m_groundlvl; 
	float m_groundleft;
	float m_groundright;

	// Максимальна висота стрибку в пікселях
	int m_maxjump; 

	 // Кадр (використовується для збільшення або зменшення швидкості(плавності) анімації)
	float m_Frame;
	
	// Швидкість гравця в пікселях в секунду
	float m_speed;

	// Значееня маcштабу (спрайту гравця)
	float m_pScale;

	// Висота та ширина спрайту гравця
	float m_pHeight;
	float m_pWidth;
	float m_pAnimBuff;

	// Змінні для збереження координат гравця на чекпоінті
	Vector2f m_checkpointPos;
	//int m_checkpointLife;
	int m_checkpointScore;

	//
	float m_X;
	float m_Y;

public:
	// Конструктор класу
	skell();

	// Доступ до спрайту
	Sprite getSprite();

	// Функції початку, припинення руху та падіння
	void moveleft();
	void moveright();
	void stopleft();
	void stopright();
	void jump();
	void not_jump();
	void rangeAttack();
	void notAttack();
	void meleeAtack();
	void fall(float _time);

	// Функція роботи з анімацією
	void animation(float _time);

	//
	int getLife();
	void setLife(int newLife);
	float getpos_y();
	float getpos_x();
	float getHeight();
	float getWidth();
	float getScale();
	float getGround();
	void setBools(bool tmp);
	bool getCanMove();
	bool getAttack();
	//Віддзеркалення спрайту
	//void setRot();
	// Встановлення координат гравця та рівня землі
	void setPosX(float y);
	void setPosY(float y);
	void setGround(float tmp);
	void drawlevel(RenderWindow& window);
	void drawlevelbylayer(RenderWindow& window, int layer);
	// Функіця оновлення кадру
	void update(float _time);

	// Функції взаємодії з картою
	void mapInteraction(float x, float y);
	bool mapHelp();
	bool checkpoint();
	void enemyColl(vector<Object> &obj);

	
	// Функція повернення на чекпоінт
	void toCheckpoint();
	
};

class enemy
{
private:
	// Вектор з координатами(позицією) гравця
	Vector2f e_pos;

	// Оголошення об'єкту Sprite
	Sprite e_sprite_heavy;
	Sprite e_sprite_range;
	Sprite e_sprite_fly;
	vector<Object> heavy;
	vector<Object> range;
	vector<Object> fly;

	// Оголошення об'єкту Texture
	Texture e_texture_heavy;
	Texture e_texture_range;
	Texture e_texture_fly;
	// Логічні змінні для відслідження руху
	bool e_left;
	bool e_right;

	int e_life;

	int j;
	int e_type;// тип ворога

	float e_pAnimBuff;
	float e_speed_heavy;
	float e_speed_fly;
	float e_pScale;
	float e_Frame;
	float e_pHeight;
	float e_pWidth;

	

	float moveTimer;

	string enemyType;

public:
	enemy();

	Sprite getSprite();

	void draw(RenderWindow &window);
	void start();
	void update(float _time);
	void animation(float _time);
	void heavyMove(float _time);
	void rangeAttack(float _time);
	void flyMove(float _time);

	bool combatColl(Object obj);

	vector<Object> getEnemy(int type);
};
