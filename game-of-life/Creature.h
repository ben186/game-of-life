#pragma once
#include <SFML/Graphics.hpp>

class Creature : public sf::RectangleShape
{
public:
	Creature();

	void	setAbsolutePosition(int AbsPosX, int AbsPosY);
	int		getAbsolutePositionX();
	int		getAbsolutePositionY();
	bool	getAliveStatus();								// Check whether this creature alive or nah
	void	setAliveStatus(bool status);					// Directly change the live of this creature 

private:
	int		AbsPosX, AbsPosY;
	bool	isAlive;
};
