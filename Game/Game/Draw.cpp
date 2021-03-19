/*
���� � ���������� ������� Draw ����� Engine (�������� ����, ��������� �� ����� ���� �� ��������� ������)
*/
#include "Engine.h"

using namespace sf;

void Engine::draw()
{
	// �������� ������
	m_window.clear();

	// ³��������� ����
	m_window.draw(m_BackgroundSprite);

	// ³��������� ��������� ������
	m_window.draw(m_skell.getSprite());

	// ��� ���� ������ �� �����
	m_window.display();
}