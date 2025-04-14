#include <ui.h>
#include <emu.h>
#include <bus.h>
#include <gamepad.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;
SDL_Texture *sdlTexture;
SDL_Surface *screen;

SDL_Window *sdlDebugWindow;
SDL_Renderer *sdlDebugRenderer;
SDL_Texture *sdlDebugTexture;
SDL_Surface *debugScreen;

int scale =3;

void ui_init() {
    
    SDL_Init(SDL_INIT_VIDEO);
    printf("SDL INIT\n");
    TTF_Init();
    printf("TTF INIT\n");

    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &sdlWindow, &sdlRenderer);

    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                                            0x00FF0000,
                                            0x0000FF00,
                                            0x000000FF,
                                            0xFF000000);
    sdlTexture = SDL_CreateTexture(sdlRenderer,
                                                SDL_PIXELFORMAT_ARGB8888,
                                                SDL_TEXTUREACCESS_STREAMING,
                                                SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_CreateWindowAndRenderer(16 * 8 * scale, 32 * 8 * scale, 0, 
        &sdlDebugWindow, &sdlDebugRenderer);

    debugScreen = SDL_CreateRGBSurface(0, (16 * 8 * scale) + (16 * scale), 
                                            (32 * 8 * scale) + (64 * scale), 32,
                                            0x00FF0000,
                                            0x0000FF00,
                                            0x000000FF,
                                            0xFF000000);

    sdlDebugTexture = SDL_CreateTexture(sdlDebugRenderer,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            (16 * 8 * scale) + (16 * scale), 
                                            (32 * 8 * scale) + (64 * scale));

    int x, y;
    SDL_GetWindowPosition(sdlWindow, &x, &y);
    SDL_SetWindowPosition(sdlDebugWindow, x + SCREEN_WIDTH + 10, y);
}