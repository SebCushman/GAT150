#include <iostream>
#include <SDL.h>

int main(int, char**){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cout << "Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	int width = 128;
	int height = 128;
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	Uint32* pixels = new Uint32[width * height];
	memset(pixels, 255, width * height * sizeof(Uint32));
	SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));

	SDL_Surface* surface = SDL_LoadBMP("sf2.bmp");
	if (surface == nullptr) {
		std::cout << "Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);

		for (int i = 0; i < width * height; i++) {
			Uint8 c = rand() % 256;
			pixels[i] = (c << 24 | c << 16 | c << 8);
		}
		SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));

		SDL_Rect rect;
		rect.x = 140;
		rect.y = 140;
		rect.w = width;
		rect.h = height;
		SDL_RenderCopy(renderer, texture, NULL, &rect);

		SDL_Rect rect2;
		rect2.x = 20;
		rect2.y = 20;
		SDL_QueryTexture(texture2, NULL, NULL, &rect2.w, &rect.h);
		SDL_RenderCopy(renderer, texture2, NULL, &rect2);

		//SDL_RenderCopy(renderer, texture2, NULL, NULL);

		SDL_RenderPresent(renderer);
	}
	


	SDL_Quit();

	return 0;

}
