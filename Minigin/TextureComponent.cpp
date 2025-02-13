#include "TextureComponent.h"
#include <SDL.h>
#include <SDL_image.h>

#include <cassert>

#include "Renderer.h"
#include "ResourceManager.h"


dae::TextureComponent::~TextureComponent()
{
	//destroys the texture
	SDL_DestroyTexture(m_texture);
}

dae::TextureComponent::TextureComponent(const std::string& fullPath)
{
	//loads the texture from the renderer
	m_texture = IMG_LoadTexture(dae::Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (m_texture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
}

dae::TextureComponent::TextureComponent(SDL_Texture* texture)
	: m_texture{ texture }
{
	//checks if the texture is not a nullptr 
	//and then places the texture in the m_texture
	assert(m_texture != nullptr);
}

dae::TextureComponent::TextureComponent()
{
	//default constructor
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	//returns the texture
	if (m_texture == nullptr)
	{
		throw std::runtime_error("Texture is nullptr");
	}
	return m_texture;
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	//loads the texture from the renderer
	m_texture = IMG_LoadTexture(dae::Renderer::GetInstance().GetSDLRenderer(), filename.c_str());
	if (m_texture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
}