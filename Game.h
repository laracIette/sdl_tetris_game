#pragma once

#include <SDL.h>

class Game
{
    bool isRunning;
    SDL_Window *window;

    Uint32 pieceStartTime;

    SDL_Event event;

    bool isLCtrlPressed;
    bool isLAltPressed;
    bool isLeftPressed;
    bool isRightPressed;
    bool isDownPressed;
    bool isSpacePressed;

    bool isLCtrlLock;
    bool isLAltLock;
    bool isLeftLock;
    bool isRightLock;
    bool isDownLock;
    bool isSpaceLock;

    bool isReset;

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
