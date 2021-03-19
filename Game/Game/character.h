/*
���� � ����������� ����� ������
*/
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class skell
{
private:
	/*
	   Vector2f - ���� �������� SFML, ���� ����������� ��� ������ � ����������� ���������.
	   ���� ������� ������������ ������ � ������������ x �� y. ���� ����� ��������������� ��� ���������� �� �� ��� ���������.
	*/
	// ������ � ������������(��������) ������
	Vector2f m_pos; 

	// ���������� ��'���� Sprite
	Sprite m_sprite; 
	
	// ���������� ��'���� Texture
	Texture m_texture;

	// ����� ���� ��� ���������� ����
	bool m_left;
	bool m_right;
	bool m_onGround;
	bool m_onJump;
	bool m_space;

	// �������� ������ � ������� � �������
	float m_speed;

public:
	// ����������� �����
	skell();

	// ������ �� �������
	Sprite getSprite();

	// ������� �������, ���������� ���� �� ������
	void moveleft();
	void moveright();
	void stopleft();
	void stopright();
	void jump();
	void not_jump();
	void fall(float _time);

	int getpos_y();
	int getpos_x();

	//³������������ �������
	void setRot();

	// ������ ��������� �����
	void update(float _time);
};