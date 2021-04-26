/*
���� � ���������� ������� Draw ����� Engine (�������� ����, ��������� �� ����� ���� �� ��������� ������)
*/
#include "Engine.h"




void Engine::draw(RenderWindow& window)
{
	Level level;
	level.LoadFromFile("maps/test.tmx");
	 //�������� ������
	m_window.clear();
	
	// ³��������� ����
	m_window.draw(m_BackgroundSprite);

	level.Draw(window);
	// ³��������� ��������� ������
	m_window.draw(m_skell.getSprite());
	
	// ��� ���� ������ �� �����
	m_window.display();
}