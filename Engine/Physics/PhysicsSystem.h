#pragma once
#include "Core/System.h"
#include "box2d/box2d.h"

namespace nc {
	class PhysicsSystem : public System {
	public:
		// Inherited via System
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		b2Body* CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic = true);

	protected:
		b2World* m_world{ nullptr };
	};
}