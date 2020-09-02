#include "pch.h"
#include "EnemyComponent.h"
#include "Objects/Scene.h"
#include "Components/PhysicsComponent.h"

namespace nc {
	void nc::EnemyComponent::Create(void* data)
	{
		m_owner = static_cast<nc::GameObject*>(data);
	}

	void nc::EnemyComponent::Destroy()
	{
	}

	void nc::EnemyComponent::Update()
	{
		GameObject* player = m_owner->m_scene->Find("Player");
		if (player) {
			Vector2 direction = player->m_transform.position - m_owner->m_transform.position;
			Vector2 force = direction.Normalized() * 5.0f;

			PhysicsComponent* physicsComponent = m_owner->GetComponent<PhysicsComponent>();
			physicsComponent->ApplyForce(force);
		}
	}
}

