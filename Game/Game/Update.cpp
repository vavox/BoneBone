/*
���� � ���������� ������� Update ����� Engine
*/
#include "Engine.h"
#include <iostream>

using namespace std;

using namespace sf;

void Engine::update(float _time)
{
	// ������ ������� ��������� ��������� ������
	m_skell.update(_time);
}