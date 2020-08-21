#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace nc {
	class PhysicsComponent : public Component {
	public:
		// Inherited via Component
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new PhysicsComponent{ *this }; }

		virtual void Update() override;

		void SetForce(const Vector2& force) { m_force = force; }
	protected:
		Vector2 m_velocity;
		Vector2 m_force;
		float m_drag{ 1 };
	};
}