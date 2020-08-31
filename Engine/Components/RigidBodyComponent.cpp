#include "pch.h"
#include "RigidBodyComponent.h"

namespace nc {
	void nc::RigidBodyComponent::Create(void* data)
	{
		m_owner = static_cast<nc::GameObject*>(data);
	}

	void nc::RigidBodyComponent::Destroy()
	{
		m_owner->m_engine->GetSystem<PhysicsSystem>()->DestroyBody(m_body);
	}

	void RigidBodyComponent::Read(const rapidjson::Value& value)
	{
		json::Get(value, "isDynamic", m_data.isDynamic);
		json::Get(value, "isSensor", m_data.isSensor);
		json::Get(value, "lockAngle", m_data.lockAngle);
		json::Get(value, "size", m_data.size);
		json::Get(value, "density", m_data.density);
		json::Get(value, "friction", m_data.friction);
		json::Get(value, "restitution", m_data.restitution);
		json::Get(value, "gravityScale", m_data.gravityScale);

	}

	void nc::RigidBodyComponent::Update()
	{
		if (m_body == nullptr) {
			m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_owner->m_transform.angle, m_data, m_owner);
			m_body->SetGravityScale(m_data.gravityScale);
			m_body->SetLinearDamping(2.0f);
		}

		m_owner->m_transform.position = PhysicsSystem::World2Screen(m_body->GetPosition());
		m_owner->m_transform.angle = nc::RadiansToDegrees(m_body->GetAngle());

		m_velocity = m_body->GetLinearVelocity();
		m_velocity.x = nc::Clamp(m_velocity.x, -5.0f, 5.0f);
		m_body->SetLinearVelocity(m_velocity);
	}

	void nc::RigidBodyComponent::ApplyForce(const Vector2& force)
	{
		if (m_body) {
			m_body->ApplyForceToCenter(force, true);
		}	
	}
}

