#pragma once
#include <iostream>
#include <map>
#include <SFML\Graphics.hpp>

class AssetManager
{
public:

	AssetManager();
	~AssetManager();

	void LoadTexture(std::string name, std::string fileName);
	const sf::Texture& GetTexture(std::string name);

	void LoadFont(std::string name, std::string fileName);
	const sf::Font& GetFont(std::string name);

private:

	std::map<std::string, sf::Texture> mTextures;
	std::map<std::string, sf::Font> mFonts;
};

