#pragma once
#include <SFML/Graphics.hpp>

class Creature : public sf::RectangleShape
{
public:
	Creature();

	void	setAbsolutePosition(int AbsPosX, int AbsPosY);
	int		getAbsolutePositionX();
	int		getAbsolutePositionY();

	void	setPos(int pos);
	int		getPos();
	bool	getAliveStatus();								// Check whether this creature alive or nah
	void	setAliveStatus(bool status);					// Directly change the live of this creature 
	void	setTempStatus(bool status);
	void	applyStatus();								// Applying changes from tempstatus to alivestatus

private:
	int		Pos;
	int		AbsPosX, AbsPosY;
	bool	isAlive;
	bool	tempStatus;
};
