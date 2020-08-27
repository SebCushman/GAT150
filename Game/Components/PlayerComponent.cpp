#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"

namespace nc {
	void nc::PlayerComponent::Create(void* data)
	{
        m_owner = static_cast<nc::GameObject*>(data);
	}

	void nc::PlayerComponent::Destroy()
	{
	}

	void nc::PlayerComponent::Update()
	{
        auto contacts = m_owner->GetContactsWithTag("Floor");
        bool onGround = !contacts.empty();

        nc::Vector2 force{ 0,0 };
        
        if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
        {
            force.x = -200;
            //m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
        }
        if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
        {
            force.x = 200;
            //m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
        }

        if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::HELD)
        {
            force.y = -1500;
        }
        /*if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
        {
            force = nc::Vector2::forward * 1000.0f;
        }
        force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));*/

        PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
        if(component){
            component->SetForce(force);
        }

        //check collision
        auto coinContacts = m_owner->GetContactsWithTag("Coin");
        for (auto contact : coinContacts) {
            contact->m_flags[GameObject::eFlags::DESTROY] = true;
        }
	}

}
