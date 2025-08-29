#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_error.h>

SDL_Window* window = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	// create a window
    window = SDL_CreateWindow("Hello, Triangle!", 960, 540, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window Error", "Error creating window.\nSDL_GetError()", window);
        return SDL_APP_FAILURE;
    }
	return SDL_APP_CONTINUE;
};

SDL_AppResult SDL_AppIterate(void *appstate) {
	return SDL_APP_CONTINUE;
};

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // close the window on request
    if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
};

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // destroy the window
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }
};
