#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

View view(Vector2f(640.f, 360.f), Vector2f(1280.f, 720.f));

void setPlayerView(float X, float Y)
{
	float tempX = X;
	float tempY = Y;

	if (X < 640) { tempX = 640; }
	if (Y < 400) { tempY = 360; }
	
	view.setCenter(tempX , tempY);
}