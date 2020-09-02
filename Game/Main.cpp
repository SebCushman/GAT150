#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Core/Json.h"
#include "Core/EventManager.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;

void OnPlayerDead(const nc::Event& event) {
    int* pdata = static_cast<int*>(event.data);
    int score = *pdata;

    std::cout << "Player Dead: " << score << std::endl;
}

int main(int, char**) {   
    engine.Startup();

    nc::ObjectFactory::Instance().Initialize();
    nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
    nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

    nc::EventManager::Instance().Subscribe("PlayerDead", &OnPlayerDead);

    rapidjson::Document document;
    nc::json::Load("scene.txt", document);
    scene.Create(&engine);
    scene.Read(document);

    nc::json::Load("tileMap.txt", document);
    nc::TileMap tileMap;
    tileMap.Read(document);
    tileMap.Create(&scene);

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
        scene.Update();

        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED) {
            quit = true;
        }
        
        engine.GetSystem<nc::Renderer>()->BeginFrame();

        scene.Draw();

        engine.GetSystem<nc::Renderer>()->EndFrame();
    }

    engine.Shutdown();
    scene.Destroy();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
