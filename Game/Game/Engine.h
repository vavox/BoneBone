/*
Файл з оголошенням класу рушія
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"
#include "map.h"



using namespace sf;

//
class Engine
{
private:
	// Оголошення об'єкту вікна
	RenderWindow m_window;

	// Оголошення текстури та спрайту фону
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Vector2f resolution;
	// Екземпляр класу гравця
	skell m_skell;
	Level level;
	// Функцій вводу з клавіатури (управління), оновлення кадру та виводу на екран
	void input();
	void update(float _time);
	void draw(RenderWindow& window);


public:
	// Конструктор класу рушія
	Engine();

	// Функція для виклику приватних функій класу рушія
	void start();

	// Камера
	void setPlayerView(float X, float Y);

	// Взаємодія з об'єктами карти
	//void mapInteraction();

};