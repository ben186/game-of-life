#include "Creature.h"
#include <SFML/Graphics.hpp>

Creature::Creature()
{
}

void Creature::setAbsolutePosition(int AbsPosX, int AbsPosY)
{
	this->AbsPosX = AbsPosX;
	this->AbsPosY = AbsPosY;
}

int Creature::getAbsolutePositionX()
{
	return this->AbsPosX;
}

int Creature::getAbsolutePositionY()
{
	return this->AbsPosY;
}

void Creature::setPos(int pos)
{
	this->Pos = pos;
}


int Creature::getPos()
{
	return this->Pos;
}

bool Creature::getAliveStatus()
{
	return this->isAlive;
}

void Creature::setAliveStatus(bool status)
{
	this->isAlive = status;
	if (status == true)
	{
		this->setFillColor(sf::Color::White);
	}
	else
	{
		this->setFillColor(sf::Color::Black);
	}
}

void Creature::setTempStatus(bool status)
{
	this->tempStatus = status;
}

void Creature::applyStatus()
{
	this->setAliveStatus(this->tempStatus);
}
