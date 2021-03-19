/*
Файл з оголошенням класу гравця
*/
#pragma once
#include <SFML/Graphics.hpp>

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
	bool m_onGround;
	bool m_onJump;
	bool m_space;

	// Швидкість гравця в пікселях в секунду
	float m_speed;

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
	void fall(float _time);

	int getpos_y();
	int getpos_x();

	//Віддзеркалення спрайту
	void setRot();

	// Функіця оновлення кадру
	void update(float _time);
};