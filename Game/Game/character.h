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
	
	bool m_onJump;
	bool m_space;

	int m_life; // ʳ������ ���� �����
	int m_score; // ʳ������ ����
	int m_groundlvl; // ���������� "���� (Y)" ����
	int m_maxjump; // ����������� ������ ������� � �������

	float m_Frame; // ����
	
	// �������� ������ � ������� � �������
	float m_speed;

	// �������� ��c����� (������� ������)
	float m_pScale;

	// ������ �� ������ ������� ������
	int m_pHeight;
	int m_pWidth;
	int m_pAnimBuff;

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

	// ������� ������ � ��������
	void animation(float _time);

	//
	float getpos_y();
	float getpos_x();
	float getHeight();
	float getWidth();
	float getScale();
	float getGround();
	void setBools(bool tmp);

	//³������������ �������
	//void setRot();
	// ������������ ��������� ������ �� ���� ����
	void setPosX(float y);
	void setPosY(float y);
	void setGround(float tmp);

	// ������ ��������� �����
	void update(float _time);
	void mapInteraction(float x, float y);
	float m_X;
	float m_Y;
	float m_Ytemp;
	bool m_onGround;
};