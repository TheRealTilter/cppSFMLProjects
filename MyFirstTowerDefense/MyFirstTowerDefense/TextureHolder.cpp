#include "stdafx.h"
#include "TextureHolder.h"

// Include the "assert feature"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(std::string const& filename)
{
	// get a reference to m_Textures using m_s_Instance
	map<string, Texture>& m = m_s_Instance->m_Textures;

	// Create an iterator
	map<string, Texture>::iterator keyValuePair = m.find(filename);

	if (keyValuePair != m.end())
	{
		//Found it, return the texture
		return keyValuePair->second;
	}
	else
	{
		// Didnt it find, create new key-value pair
		auto& texture = m[filename];
		// Load the texture in the usual way
		texture.loadFromFile(filename);

		//return it
		return texture;

	}
}