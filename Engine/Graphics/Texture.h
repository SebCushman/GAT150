#pragma once
#include "Math/Vector2.h"
#include <SDL_image.h>
#include <SDL.h>
#include <string>

namespace nc {
	class Texture {
	public:
		bool Create(const std::string& name, SDL_Renderer* renderer);
		void Destroy();

		void Draw(const Vector2& posistion, const Vector2& scale, float angle);

		Vector2 GetSize() const;

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}