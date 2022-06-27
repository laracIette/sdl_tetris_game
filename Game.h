#pragma once

#include <SDL.h>

class Game
{
    bool isRunning;
    SDL_Window *window;

    Uint32 pieceStartTime;

    SDL_Event event;

    static const int KEYS{ 6 };

    SDL_KeyCode keyCode[KEYS]{
        SDLK_x,
        SDLK_v,
        SDLK_LEFT,
        SDLK_RIGHT,
        SDLK_DOWN,
        SDLK_SPACE
    };

    bool keyPressed[KEYS];
    bool keyLock[KEYS];

    bool isReset;
    bool isPaused;

public:
    Game();
    ~Game();

    void Init( const char *title, int moveX, int moveY, bool fullscreen );

    void HandleEvents();

    void Update();
    void Render();
    void Clean();

    void Reset();

    bool Running() { return isRunning; }

	static SDL_Renderer *renderer;

};
