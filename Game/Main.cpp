#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"

nc::Engine engine;

int main(int, char**) {
    
    engine.Startup();

    nc::ObjectFactory::Instance().Initialize();
    nc::ObjectFactory::Instance().Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);

    nc::GameObject* player = nc::ObjectFactory::Instance().Create<nc::GameObject>("GameObject");
    
    player->Create(&engine);

    rapidjson::Document document;
    nc::json::Load("player.txt", document);
    player->Read(document);

    nc::Component* component;
    component = nc::ObjectFactory::Instance().Create<nc::Component>("PhysicsComponent");
    component->Create(player);
    player->AddComponent(component);

    component = nc::ObjectFactory::Instance().Create<nc::Component>("SpriteComponent");
    nc::json::Load("sprite.txt", document);
    component->Create(player);
    component->Read(document);
    player->AddComponent(component);

    component = nc::ObjectFactory::Instance().Create<nc::Component>("PlayerComponent");
    component->Create(player);
    player->AddComponent(component);

    //IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
    //nc::Texture* car = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", engine.GetSystem<nc::Renderer>());

    //float angle{ 0 };
    //nc::Vector2 position{ 400, 300 };
    nc::Vector2 velocity{ 0,0 };

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }

        //update
        engine.Update();
        player->Update();

        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED) {
            quit = true;
        }
        
        //SDL_SetRenderDrawColor(renderer, 20, 0, 30, 255);
        engine.GetSystem<nc::Renderer>()->BeginFrame();

        background->Draw({ 0, 0 });

        //player sprite draw
        //car->Draw({ 64, 110, 60, 112 }, position, { 1,1 }, angle);
        player->Draw();

        engine.GetSystem<nc::Renderer>()->EndFrame();
    }

    engine.Shutdown();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
