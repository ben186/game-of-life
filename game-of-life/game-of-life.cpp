#include "pch.h"
#include "Creature.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

constexpr bool DEAD = false;
constexpr bool LIVE = true;

void initCreatures(std::vector<Creature>& creature)
{
	for (int i = 0; i < 10000; ++i)
	{
		creature[i].setPos(i);
	}

	int count = 0; // Reset counter
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

// Hacky way to count neighbours
void startCreatures(std::vector<Creature>& creature)
{
	int count = 0;

	// Count neighbour that still alive
	for (int i = 98 + 3; i <= (98 + 2) * (98 + 1) - 2; ++i)
	{
		count =
			creature[i - 1 - (98 + 2)].getAliveStatus() +
			creature[i - (98 + 2)].getAliveStatus() +
			creature[i + 1 - (98 + 2)].getAliveStatus() +
			creature[i - 1].getAliveStatus() +
			creature[i + 1].getAliveStatus() +
			creature[i - 1 + (98 + 2)].getAliveStatus() +
			creature[i + (98 + 2)].getAliveStatus() +
			creature[i + 1 + (98 + 2)].getAliveStatus();

		if ((creature[i].getAliveStatus() && (count == 2 || count == 3)) || (!creature[i].getAliveStatus() && count == 3))
		{
			creature[i].setTempStatus(LIVE);
		}
		else {
			creature[i].setTempStatus(DEAD);
		}

		count = 0;
	}

	for (auto i = creature.begin(); i != creature.end(); ++i)
	{
		i->applyStatus();
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "GAME OF LIFE");

	std::vector<Creature> creature(10000);
	// uint16_t AbsolutePosition[100][100];

	initCreatures(creature);

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
				startCreatures(creature);
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