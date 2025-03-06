#include "TextRenderer.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <SDL_ttf.h>

TextRenderer::TextRenderer(const std::string& text, std::shared_ptr<dae::Font> font) :
	m_needsUpdate(true), m_text(text), m_font(font), m_textTexture(nullptr)
{
}

void TextRenderer::Update()
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<dae::Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void TextRenderer::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = GetOwner()->GetComponent<TransformComponent>()->GetPosition();
		const auto& relativePos = GetOwner()->GetComponent<TransformComponent>()->GetRelativePosition();
		const auto& rotation = GetOwner()->GetComponent<TransformComponent>()->GetRotation();
		const auto& truePos = pos + relativePos + rotation;
		dae::Renderer::GetInstance().RenderTexture(*m_textTexture, truePos.x, truePos.y);
	}
}

void TextRenderer::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}