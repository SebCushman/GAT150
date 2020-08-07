#pragma once
#include "Math/Vector2.h"
#include "Resources/Resource.h"
#include <SDL_image.h>
#include <SDL.h>
#include <string>

namespace nc {
	class Texture : public Resource {
	public:
		bool Create(const std::string& name, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& posistion, const Vector2& scale, float angle);

		Vector2 GetSize() const;

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}