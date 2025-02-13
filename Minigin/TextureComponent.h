#pragma once
#include "Component.h"


struct SDL_Texture;
namespace dae
{
	class TextureComponent final :
		public Component
	{
	public:

		TextureComponent(const std::string& fullPath);
		TextureComponent(SDL_Texture* texture);
		TextureComponent();

		virtual ~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		SDL_Texture* GetSDLTexture() const;
		void SetTexture(const std::string& filename);

	private:

		SDL_Texture* m_texture{};
	};
}

