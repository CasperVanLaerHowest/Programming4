#include "TextureRenderer.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

TextureRenderer::TextureRenderer(const std::string& fullPath)
{
	if (fullPath.empty())
	{
		throw std::runtime_error("File path is empty");
	}
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(fullPath).get();
}

TextureRenderer::TextureRenderer(dae::Texture2D* texture)
	: m_texture{ texture }
{
	assert(m_texture != nullptr);
}

void TextureRenderer::Render() const
{
	const auto& pos = GetOwner()->GetComponent<TransformComponent>()->GetPosition();
	const auto& relativePos = GetOwner()->GetComponent<TransformComponent>()->GetRelativePosition();
	const auto& rotation = GetOwner()->GetComponent<TransformComponent>()->GetRotation();
	const auto& truePos = pos + relativePos + rotation;
	RenderTexture(truePos.x, truePos.y);
}

dae::Texture2D* TextureRenderer::GetTexture() const
{
	if (m_texture == nullptr)
	{
		throw std::runtime_error("Texture is nullptr");
	}
	return m_texture;
}

void TextureRenderer::SetTexture(const std::string& filename)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename).get();
}

void TextureRenderer::RenderTexture(float x, float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(m_texture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(dae::Renderer::GetInstance().GetSDLRenderer(), m_texture->GetSDLTexture(), nullptr, &dst);
}