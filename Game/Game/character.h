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
	
	bool m_onJump;
	bool m_space;

	int m_life; // Кількість очків життя
	int m_score; // Кількість очків
	int m_groundlvl; // Координата "рівня (Y)" землі
	int m_maxjump; // Максимальна висота стрибку в пікселях

	float m_Frame; // Кадр
	
	// Швидкість гравця в пікселях в секунду
	float m_speed;

	// Значееня маcштабу (спрайту гравця)
	float m_pScale;

	// Висота та ширина спрайту гравця
	int m_pHeight;
	int m_pWidth;
	int m_pAnimBuff;

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

	// Функція роботи з анімацією
	void animation(float _time);

	//
	float getpos_y();
	float getpos_x();
	float getHeight();
	float getWidth();
	float getScale();
	float getGround();
	void setBools(bool tmp);

	//Віддзеркалення спрайту
	//void setRot();
	// Встановлення координат гравця та рівня землі
	void setPosX(float y);
	void setPosY(float y);
	void setGround(float tmp);

	// Функіця оновлення кадру
	void update(float _time);
	void mapInteraction(float x, float y);
	float m_X;
	float m_Y;
	float m_Ytemp;
	bool m_onGround;
};