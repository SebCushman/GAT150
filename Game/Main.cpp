#include "pch.h"
#include "Graphics/Texture.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include <SDL_image.h>


nc::Renderer renderer;
nc::ResourceManager resourceManager;
nc::InputSystem inputSystem;
nc::FrameTimer timer;

int main(int, char**) {
    /*nc::Timer timer;
    for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
    std::cout << timer.ElapsedTicks() << std::endl;
    std::cout << timer.ElapsedSeconds() << std::endl;*/

    renderer.Startup();
    resourceManager.Startup();
    inputSystem.Startup();

    renderer.Create("GAT150", 800, 600);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    nc::Texture* texture = resourceManager.Get<nc::Texture>("sf2.png", &renderer);
    nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);

    float angle{ 0 };
    nc::Vector2 position{ 400, 300 };

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }

        timer.Tick();
        resourceManager.Update();
        inputSystem.Update();

        if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
        {
            position.x = position.x - 200.0f * timer.DeltaTime();
        }
        if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
        {
            position.x = position.x + 200.0f * timer.DeltaTime();
        }


        //SDL_SetRenderDrawColor(renderer, 20, 0, 30, 255);
        renderer.BeginFrame();

        angle = angle + 90 * timer.DeltaTime();

        texture->Draw(position, { 1, 1 }, angle);
        texture2->Draw({ 300, 400 }, { 2, 2 }, angle + 90);

        renderer.EndFrame();
    }

    inputSystem.Shutdown();
    resourceManager.Shutdown();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
