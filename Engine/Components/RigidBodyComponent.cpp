#include "pch.h"
#include "RigidBodyComponent.h"

namespace nc {
	void nc::RigidBodyComponent::Create(void* data)
	{
		m_owner = static_cast<nc::GameObject*>(data);
	}

	void nc::RigidBodyComponent::Destroy()
	{
	}

	void RigidBodyComponent::Read(const rapidjson::Value& value)
	{
		json::Get(value, "isDynamic", m_data.isDynamic);
		json::Get(value, "lockAngle", m_data.lockAngle);
		json::Get(value, "size", m_data.size);
		json::Get(value, "density", m_data.density);
		json::Get(value, "friction", m_data.friction);
		json::Get(value, "restitution", m_data.restitution);

	}

	void nc::RigidBodyComponent::Update()
	{
		if (m_body == nullptr) {
			m_body = m_owner->m_engine->GetSystem<PhysicsSystem>()->CreateBody(m_owner->m_transform.position, m_data, m_owner);
		}

		m_owner->m_transform.position = m_body->GetPosition();
		m_owner->m_transform.angle = m_body->GetAngle();
	}

	void nc::RigidBodyComponent::SetForce(const Vector2& force)
	{
		m_body->ApplyLinearImpulseToCenter(force, true);
	}
}

