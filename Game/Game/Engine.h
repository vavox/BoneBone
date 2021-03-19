/*
Файл з оголошенням класу рушія
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"

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
	
	// Екземпляр класу гравця
	skell m_skell;

	// Функцій вводу з клавіатури (управління), оновлення кадру та виводу на екран
	void input();
	void update(float _time);
	void draw();

public:
	// Конструктор класу рушія
	Engine();

	// Функція для виклику приватних функій класу рушія
	void start();
};