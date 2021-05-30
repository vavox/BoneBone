/*
���� � ����������� ����� �����
*/
#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "character.h"
//#include "map.h"



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


	Font font;
	Text life;
	Text gameover[2];
	Text checkp;

	// Menu
	int menuElem;
	int currentMenuElem;
	bool toLevel;
	bool info;
	bool menuStart;
	Text menu[3];
	Text infoT;
	Text hp;
	Text layerInf;

public:
	// ����������� ����� �����
	Engine();

	// ������� ��� ������� ��������� ����� ����� �����
	void start();

	// ������� ����� � ��������� (���������)
	void input();

	// ������
	void setPlayerView(float X, float Y);

	// Menu
	void menuInit();
	void menuDraw(RenderWindow& window);
	void menuMoveUp();
	void menuMoveDown();
	void menuEnter();
	void menuInfo();
	// Combat system
	void combatInit();
	void combatSystem(float _time);

	void initWorld();
};
