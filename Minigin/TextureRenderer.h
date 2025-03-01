#pragma once
#include "Component.h"
#include "Texture2D.h"

class TextureRenderer :
    public dae::Component
{
public:

	TextureRenderer(const std::string& fullPath);
	TextureRenderer(dae::Texture2D* texture);
	TextureRenderer() = default;
	virtual ~TextureRenderer() = default;

	virtual void Render() const;

	TextureRenderer(const TextureRenderer& other) = delete;
	TextureRenderer(TextureRenderer&& other) = delete;
	TextureRenderer& operator=(const TextureRenderer& other) = delete;
	TextureRenderer& operator=(TextureRenderer&& other) = delete;

	dae::Texture2D* GetTexture() const;
	void SetTexture(const std::string& filename);

	void RenderTexture(float x, float y) const;
private:
	dae::Texture2D* m_texture;
};
