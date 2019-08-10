#include "pch.h"
#include "Creature.h"
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

constexpr bool DEAD = false;
constexpr bool LIVE = true;

std::vector<bool> tempStatus(10000);

void initCreatures(std::vector<Creature>& creature, uint16_t (&AbsolutePosition)[100][100])
{
	int count = 0;
	for (int x = 0; x < 100; ++x)
	{
		for (int y = 0; y < 100; ++y)
		{
			AbsolutePosition[x][y] = count;
			creature[count].setAbsolutePosition(x, y);
			++count;
		}
	}

	count = 0; // Reset counter
	for (int x = 0; x < 1000; x += 10)
	{
		for (int y = 0; y < 1000; y += 10)
		{
			creature[count].setPosition(sf::Vector2f((float)x, (float)y));
			++count;
		}
	}

	for (auto i = creature.begin(); i != creature.end(); ++i)
	{
		i->setSize(sf::Vector2f(10.0f, 10.0f));
		i->setAliveStatus(DEAD);
		i->setOutlineThickness(1);
		i->setOutlineColor(sf::Color(211, 217, 227, 255));
	}
}

void startCreatures(std::vector<Creature>& creature, uint16_t (&AbsolutePosition)[100][100])
{
	tempStatus.clear(); // Somehow it will become double when i dont add this

	for (int x = 0; x < 100; ++x)
	{
		for (int y = 0; y < 100; ++y)
		{
			if (x != 0 && y != 0 && x != 99 && y != 99)
			{
				int aliveCount = 0;

				/*if (creature[AbsolutePosition[x + 1][y + 1]].getAliveStatus()) { ++aliveCount; }
				if (creature[AbsolutePosition[x][y + 1]].getAliveStatus()) { ++aliveCount; }
				if (creature[AbsolutePosition[x - 1][y + 1]].getAliveStatus()) { ++aliveCount; }
				if (creature[AbsolutePosition[x - 1][y]].getAliveStatus()) { ++aliveCount; }
				if (creature[AbsolutePosition[x + 1][y]].getAliveStatus()) { ++aliveCount; }
				if (creature[AbsolutePosition[x - 1][y - 1]].getAliveStatus()) { ++aliveCount; }
				if (creature[AbsolutePosition[x][y - 1]].getAliveStatus()) { ++aliveCount; }
				if (creature[AbsolutePosition[x + 1][y - 1]].getAliveStatus()) { ++aliveCount; }*/
				
				aliveCount += creature[AbsolutePosition[x + 1][y + 1]].getAliveStatus();
				aliveCount += creature[AbsolutePosition[x][y + 1]].getAliveStatus();
				aliveCount += creature[AbsolutePosition[x - 1][y + 1]].getAliveStatus();
				aliveCount += creature[AbsolutePosition[x - 1][y]].getAliveStatus();
				aliveCount += creature[AbsolutePosition[x + 1][y]].getAliveStatus();
				aliveCount += creature[AbsolutePosition[x - 1][y - 1]].getAliveStatus();
				aliveCount += creature[AbsolutePosition[x][y - 1]].getAliveStatus();
				aliveCount += creature[AbsolutePosition[x + 1][y - 1]].getAliveStatus();

				if (aliveCount != 2 && aliveCount != 3)
				{
					tempStatus.push_back(DEAD);
				}
				else {
					tempStatus.push_back(LIVE);
					if (aliveCount == 2 && creature[AbsolutePosition[x][y]].getAliveStatus() == DEAD) { tempStatus.pop_back(); tempStatus.push_back(DEAD); }
				}
				aliveCount = 0;
			}
			else
			{
				tempStatus.push_back(DEAD);
			}
		}
	}

	int count = 0;
	for (auto t : tempStatus)
	{
		creature[count].setAliveStatus(t);
		++count;
	}
	
	tempStatus.clear();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "GAME OF LIFE");

	std::vector<Creature> creature(10000);
	uint16_t AbsolutePosition[100][100];

	initCreatures(creature, AbsolutePosition);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Write it this way can process the click continuously
			{
				auto getPos = sf::Mouse::getPosition(window);
				auto transPos = window.mapPixelToCoords(getPos); // I DONT UNDERSTAND BUT I DID IT ANYWAY

				for (auto i = creature.begin(); i != creature.end(); ++i)
				{
					if (i->getGlobalBounds().contains(transPos))
					{
						i->setAliveStatus(LIVE);
					}
				}
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) // Temp button for keep it going
			{
				startCreatures(creature, AbsolutePosition);
				window.clear();

				// Draw all individual creatures
				for (auto i = creature.begin(); i != creature.end(); ++i)
				{
					window.draw(*i);
				}

				window.display();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
			{
				for (auto i = creature.begin(); i != creature.end(); ++i)
				{
					i->setAliveStatus(DEAD);
				}
			}
		}

		window.clear();

		// Draw all individual creatures
		for (auto i = creature.begin(); i != creature.end(); ++i)
		{
			window.draw(*i);
		}

		window.display();
	}

	return 0;
}
