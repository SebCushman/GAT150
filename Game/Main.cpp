#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"

nc::FrameTimer timer;

nc::Engine engine;

int main(int, char**) {
    /*nc::Timer timer;
    for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
    std::cout << timer.ElapsedTicks() << std::endl;
    std::cout << timer.ElapsedSeconds() << std::endl;*/
    engine.Startup();

    //IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
    nc::Texture* car = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", engine.GetSystem<nc::Renderer>());

    float angle{ 0 };
    nc::Vector2 position{ 400, 300 };
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
        timer.Tick();
        engine.Update();

        quit = (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

        //player controller
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
        {
           angle = angle - 200.0f * timer.DeltaTime();
        }
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
        {
            angle = angle + 200.0f * timer.DeltaTime();
        }
        
        nc::Vector2 force{ 0,0 };
        if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
        {
            force = nc::Vector2::forward * 1000.0f;
        }
        force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));
        
        //physics
        velocity = velocity + force * timer.DeltaTime();
        velocity = velocity * 0.95f;
        position = position + velocity * timer.DeltaTime();
        
        
        //SDL_SetRenderDrawColor(renderer, 20, 0, 30, 255);
        engine.GetSystem<nc::Renderer>()->BeginFrame();

        background->Draw({ 0, 0 });

        //player sprite draw
        car->Draw({ 64, 110, 60, 112 }, position, { 1,1 }, angle);

        engine.GetSystem<nc::Renderer>()->EndFrame();
    }

    engine.Shutdown();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
