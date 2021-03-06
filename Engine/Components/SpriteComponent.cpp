#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc {
	void SpriteComponent::Create(void* data)
	{
		m_owner = static_cast<nc::GameObject*>(data);

		//m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());
		//ASSERT_MSG((m_texture != nullptr), "Error texture " + m_textureName + " not loaded");
	}

	void nc::SpriteComponent::Destroy()
	{
	}

	void SpriteComponent::Read(const rapidjson::Value& value)
	{
		json::Get(value, "texture", m_textureName);
		json::Get(value, "origin", m_origin);
		json::Get(value, "rect", m_rect);
	}

	void nc::SpriteComponent::Update()
	{
	}

	void nc::SpriteComponent::Draw()
	{
		//{ 125, 440, 60, 110 }

		Texture* texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<nc::Renderer>());
		texture->Draw(m_rect, m_owner->m_transform.position, m_owner->m_transform.angle, Vector2::one * m_owner->m_transform.scale, m_origin, m_flip);
	}
}

