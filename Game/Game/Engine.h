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
	enemy e_enem;
	//Level level;
	// ������� ����� � ��������� (���������), ��������� ����� �� ������ �� �����
	void input();
	/*void update(float _time);
	void draw(RenderWindow& window);*/
	Font font;
	Text life;
	Text gameover;
	Text checkp;

public:
	// ����������� ����� �����
	Engine();

	// ������� ��� ������� ��������� ����� ����� �����
	void start();

	// ������
	void setPlayerView(float X, float Y);

	void menu(RenderWindow& window);

	

	void combatInit();
	void combatSystem(float _time);
	// ������� � ��'������ �����
	// ������� �����䳿 � ������
	/*void mapInteraction(float x, float y);
	bool mapHelp();*/

};
