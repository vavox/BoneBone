/*
���� � ����������� ����� �����
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"

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
	
	// ��������� ����� ������
	skell m_skell;

	// ������� ����� � ��������� (���������), ��������� ����� �� ������ �� �����
	void input();
	void update(float _time);
	void draw();

public:
	// ����������� ����� �����
	Engine();

	// ������� ��� ������� ��������� ����� ����� �����
	void start();
};