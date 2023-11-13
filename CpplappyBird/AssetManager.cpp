#include "AssetManager.hpp"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;

	if (tex.loadFromFile(fileName))
	{
		mTextures[name] = tex;
	}
	else
	{
		std::cout << "[AssetManager::LoadTexture] Unable to load texture " << name << "from file." << std::endl;
	}
}

const sf::Texture& AssetManager::GetTexture(std::string name)
{
	return mTextures.at(name);
}

void AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		mFonts[name] = font;
	}
	else
	{
		std::cout << "[AssetManager::LoadFont] Unable to load font " << name << "from file." << std::endl;
	}
}

const sf::Font& AssetManager::GetFont(std::string name)
{
	return mFonts.at(name);
}