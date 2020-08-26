#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"
#include "Components/RigidBodyComponent.h"

namespace nc {
    void nc::ObjectFactoryImpl::Initialize()
    {
        nc::ObjectFactory::Instance().Register("GameObject", new Creator<GameObject, Object>);
        nc::ObjectFactory::Instance().Register("PhysicsComponent", new Creator<PhysicsComponent, Object>);
        nc::ObjectFactory::Instance().Register("SpriteComponent", new Creator<SpriteComponent, Object>);
        nc::ObjectFactory::Instance().Register("SpriteAnimationComponent", new Creator<SpriteAnimationComponent, Object>);
        nc::ObjectFactory::Instance().Register("RigidBodyComponent", new Creator<RigidBodyComponent, Object>);
    }
}

