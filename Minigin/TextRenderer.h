#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "Font.h"
#include <memory>
#include "Font.h"
#include "ResourceManager.h"


class TextRenderer :
    public dae::Component
{
public:
	void Update() override;
	void Render() const override;
	
	void SetText(const std::string& text);

	TextRenderer(const std::string& text, std::shared_ptr<dae::Font> font);
	virtual ~TextRenderer() = default;
	TextRenderer(const TextRenderer& other) = delete;
	TextRenderer(TextRenderer&& other) = delete;
	TextRenderer& operator=(const TextRenderer& other) = delete;
	TextRenderer& operator=(TextRenderer&& other) = delete;

private:
	bool m_needsUpdate;
	std::string m_text;
	std::shared_ptr<dae::Font> m_font;
	std::shared_ptr<dae::Texture2D> m_textTexture;

};

