#pragma once

// Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "objects.h"

// Prototypes
void runInstance();

// Classes
class GameScore
{
private:
	std::pair<int, int> score;
public:
	int getScore(char player);
	void addScore(char player);
	void subTractScore(char player, int count);
	void reset();
};