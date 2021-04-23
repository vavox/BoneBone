/*
���� � ����������� ����� �����
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
	// ���������� ��'���� ����
	RenderWindow m_window;

	// ���������� �������� �� ������� ����
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Vector2f resolution;
	// ��������� ����� ������
	skell m_skell;
	Level level;
	// ������� ����� � ��������� (���������), ��������� ����� �� ������ �� �����
	void input();
	void update(float _time);
	void draw(RenderWindow& window);


public:
	// ����������� ����� �����
	Engine();

	// ������� ��� ������� ��������� ����� ����� �����
	void start();

	// ������
	void setPlayerView(float X, float Y);

	// ������� � ��'������ �����
	//void mapInteraction();

};