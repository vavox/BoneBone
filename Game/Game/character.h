/*
���� � ����������� ����� ������
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"


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
	
	// ������� ����� ���� ��� ���������� ������� �� ����������� �� ����
	bool m_fall;
	bool m_onGround;
	bool m_canJump;
	bool m_onJump;
	bool m_space;
	bool m_onGroundAnim;
	bool m_canMove;
	bool m_range;
	bool m_melee;
	
	
	// ʳ������ ���� ����� �� ��������� ������� ����
	int m_life; 
	int m_score; 

	// ���������� ������ ������� , ��� �� ����� ���������� ��'���� ����
	float m_groundlvl; 
	float m_groundleft;
	float m_groundright;

	// ����������� ������ ������� � �������
	int m_maxjump; 

	 // ���� (��������������� ��� ��������� ��� ��������� ��������(��������) �������)
	float m_Frame;
	
	// �������� ������ � ������� � �������
	float m_speed;

	// �������� ��c����� (������� ������)
	float m_pScale;

	// ������ �� ������ ������� ������
	float m_pHeight;
	float m_pWidth;
	float m_pAnimBuff;

	// ���� ��� ���������� ��������� ������ �� �������
	Vector2f m_checkpointPos;
	//int m_checkpointLife;
	int m_checkpointScore;

	//
	float m_X;
	float m_Y;

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
	void rangeAttack();
	void notAttack();
	void meleeAtack();
	void fall(float _time);

	// ������� ������ � ��������
	void animation(float _time);

	//
	int getLife();
	void setLife(int newLife);
	float getpos_y();
	float getpos_x();
	float getHeight();
	float getWidth();
	float getScale();
	float getGround();
	void setBools(bool tmp);
	bool getCanMove();
	bool getAttack();
	//³������������ �������
	//void setRot();
	// ������������ ��������� ������ �� ���� ����
	void setPosX(float y);
	void setPosY(float y);
	void setGround(float tmp);
	void drawlevel(RenderWindow& window);
	void drawlevelbylayer(RenderWindow& window, int layer);
	// ������ ��������� �����
	void update(float _time);

	// ������� �����䳿 � ������
	void mapInteraction(float x, float y);
	bool mapHelp();
	bool checkpoint();
	void enemyColl(vector<Object> &obj);

	
	// ������� ���������� �� �������
	void toCheckpoint();
	
};

class enemy
{
private:
	// ������ � ������������(��������) ������
	Vector2f e_pos;

	// ���������� ��'���� Sprite
	Sprite e_sprite_heavy;
	Sprite e_sprite_range;
	Sprite e_sprite_fly;
	vector<Object> heavy;
	vector<Object> range;
	vector<Object> fly;

	// ���������� ��'���� Texture
	Texture e_texture_heavy;
	Texture e_texture_range;
	Texture e_texture_fly;
	// ����� ���� ��� ���������� ����
	bool e_left;
	bool e_right;

	int e_life;

	int j;
	int e_type;// ��� ������

	float e_pAnimBuff;
	float e_speed_heavy;
	float e_speed_fly;
	float e_pScale;
	float e_Frame;
	float e_pHeight;
	float e_pWidth;

	

	float moveTimer;

	string enemyType;

public:
	enemy();

	Sprite getSprite();

	void draw(RenderWindow &window);
	void start();
	void update(float _time);
	void animation(float _time);
	void heavyMove(float _time);
	void rangeAttack(float _time);
	void flyMove(float _time);

	bool combatColl(Object obj);

	vector<Object> getEnemy(int type);
};
