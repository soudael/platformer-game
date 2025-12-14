#include "GodLibrary.h"

int main(int argc, char *argv[])
{
    // AWAKE -------------------------------------------------------------------
    callVideoDrivers();
    Window window("Platform Game", WIDTH, HEIGHT);
    Renderer renderer(window.getWindowObj());
    SDL_SetRenderLogicalPresentation(renderer.getRendererObj(), SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Objects
    Player player(WIDTH/2, 0.0f);
    player.loadPlayerTexture(renderer.getRendererObj());
    SDL_SetTextureScaleMode(player.playerIdleSprite, SDL_SCALEMODE_NEAREST);

    SDL_FRect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    std::vector<Platforms> platforms;
    platforms.emplace_back( 0.0f - WIDTH*3, HEIGHT - 20.0f, WIDTH*7, 20.0f ); // Bottom
    platforms.emplace_back( 0.0f + WIDTH/4, 0.0f + HEIGHT/2.5, WIDTH/2, 20.0f ); // Middle
    platforms.emplace_back( 0.0f - WIDTH/2, 0.0f, WIDTH/2, 20.0f ); // Left
    platforms.emplace_back( WIDTH + WIDTH/2, 0.0f, WIDTH/2, 20.0f ); // Right
    platforms.emplace_back( WIDTH + 20.0f, HEIGHT - 120.0f, 100.0f, 100.0f ); // Cube

    // START -------------------------------------------------------------------
    SDL_Event globalEvent;
    bool gameRunning = true;

    // Delta Time
    Uint64 lastTime = SDL_GetTicksNS();
    Uint64 currentTime;
    float deltaTime;

    // UPDATE ------------------------------------------------------------------
    while(gameRunning)
    {
        // Delta Time
        currentTime = SDL_GetTicksNS();
        deltaTime = (currentTime - lastTime) / 1'000'000'000.0f;
        lastTime = currentTime;

        camera.x = player.getPlayerRectObj().x + 25.0f - SCREEN_WIDTH/2;
        camera.y = player.getPlayerRectObj().y + 25.0f - SCREEN_HEIGHT/2;

        // Global Events
        while (SDL_PollEvent(&globalEvent))
        {
            // Check for Window Events
            if (globalEvent.type == SDL_EVENT_WINDOW_MOVED || 
                globalEvent.type == SDL_EVENT_WINDOW_RESIZED ||
                globalEvent.type == SDL_EVENT_WINDOW_EXPOSED ||
                globalEvent.type == SDL_EVENT_WINDOW_FOCUS_LOST) 
            {
                lastTime = SDL_GetTicksNS();
                deltaTime = 0.0f;
            }

            if (globalEvent.type == SDL_EVENT_QUIT) { gameRunning = false; }
        }
        player.update(deltaTime, platforms);

        // Render
        SDL_SetRenderDrawColor(renderer.getRendererObj(), 30, 30, 30, 255); // Background color
        SDL_RenderClear(renderer.getRendererObj()); // Background paint

        for (auto& platform : platforms)
        { // Platforms
            platform.render(renderer.getRendererObj(), camera.x, camera.y);
        }
        player.render(renderer.getRendererObj(), camera.x, camera.y); // Player
        
        SDL_RenderPresent(renderer.getRendererObj()); // Rendering Update
    }

    // // Destroy -----------------------------------------------------------------
    SDL_DestroyTexture(player.playerIdleSprite);
    SDL_DestroyRenderer(renderer.getRendererObj());
    SDL_DestroyWindow(window.getWindowObj());
    SDL_Quit();
    return EXIT_SUCCESS;
}