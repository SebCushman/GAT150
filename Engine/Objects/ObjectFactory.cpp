#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace nc {
    void nc::ObjectFactoryImpl::Initialize()
    {
        nc::ObjectFactory::Instance().Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
        nc::ObjectFactory::Instance().Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
        nc::ObjectFactory::Instance().Register("SpriteComponent", nc::Object::Instantiate<nc::SpriteComponent>);
        nc::ObjectFactory::Instance().Register("SpriteAnimationComponent", nc::Object::Instantiate<nc::SpriteAnimationComponent>);
    }
}

