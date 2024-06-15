#include <SFML/Graphics.hpp>

sf::View view;

sf::View getpleyercoordforview(float x, float y) {
	float tempX = x, tempY = y;

	if (x < 400) tempX = 400;
	if (y < 300) tempY = 300;
	if (y > 500) tempY = 500;

	view.setCenter(tempX, tempY);
	return view;
}
