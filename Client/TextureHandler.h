#pragma once
////////////////////////////////////////////////////////////////////
//	PURPOSE: hide the ugly texture initializations in the game .cpps
////////////////////////////////////////////////////////////////////

#include <array>

#include "SFML/Graphics.hpp"

#include "Card.h"

class TextureHandler
{
public:
	void init_all();


	static void init_font(sf::Font& init_this);

	void set_font(sf::Font& copy_from);

	static void init_backcard(std::array<sf::Texture, 4>& rueckseiten);

	static void init_backcard_sprite(sf::Sprite& init_this);

	static void init_wish_card_sprites(std::array<Card, 4>& init_this);

private:
	
	
};