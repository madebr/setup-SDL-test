#include <SDL3/SDL.h>
#include <SDL3/SDL_test.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_rtf/SDL_rtf.h>
#ifdef WITH_SDLNET
#include <SDL3_net/SDL_net.h>
#endif

#define LOG_SDL_VERSION(WHAT, COMPILED_VERSION, LINKED_CBFN)                    \
    do {                                                                        \
        int compiled_version = COMPILED_VERSION;                                \
        int linked_version = LINKED_CBFN();                                     \
        LOG_CV_LV(WHAT, compiled_version, linked_version);                      \
    } while (0)

#define LOG_CV_LV(WHAT, CV, LV)                                                             \
    do {                                                                                    \
        SDL_Log(WHAT ": compiled version: %d.%d.%d, linked version: %d.%d.%d",              \
            SDL_VERSIONNUM_MAJOR(CV), SDL_VERSIONNUM_MINOR(CV), SDL_VERSIONNUM_MICRO(CV),   \
            SDL_VERSIONNUM_MAJOR(LV), SDL_VERSIONNUM_MINOR(LV), SDL_VERSIONNUM_MICRO(LV));  \
    } while (0)

int main(int argc, char *argv[]) {
    int i;
    SDLTest_CommonState *state;
    SDL_Window *window;
    SDL_Renderer *renderer;

    int vv = IMG_Version();

    LOG_SDL_VERSION("SDL", SDL_VERSION, SDL_GetVersion);
    LOG_SDL_VERSION("SDL_image", SDL_IMAGE_VERSION, IMG_Version);
    LOG_SDL_VERSION("SDL_mixer", SDL_MIXER_VERSION, Mix_Version);
    LOG_SDL_VERSION("SDL_ttf", SDL_TTF_VERSION, TTF_Version);
    LOG_SDL_VERSION("SDL_rtf", SDL_RTF_VERSION, RTF_Version);
#ifdef WITH_SDLNET
    LOG_SDL_VERSION("SDL_net", SDL_NET_VERSION, SDLNet_Version);
#endif

    /* Initialize test framework */
    state = SDLTest_CommonCreateState(argv, SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    if (state == NULL) {
        return 1;
    }

    for (i = 1; i < argc;) {
        int consumed;

        consumed = SDLTest_CommonArg(state, i);
        if (consumed == 0) {
        }
        if (consumed < 0) {
            static const char *options[] = {
                    NULL
            };
            SDLTest_CommonLogUsage(state, argv[0], options);
            return 1;
        }
        i += consumed;
    }

    state->num_windows = 1;

    if (!SDLTest_CommonInit(state)) {
        SDL_Log("SDL_Init failed (%s)", SDL_GetError());
        return 2;
    }

    window = state->windows[0];
    renderer = state->renderers[0];

    IMG_Init(0);
    TTF_Init();
#ifdef WITH_SDLNET
    SDLNet_Init();
#endif

    while (1) {
        int finished = 0;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                finished = 1;
                break;
            }
        }
        if (finished) {
            break;
        }

        SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDLTest_CommonQuit(state);

    return 0;
}
