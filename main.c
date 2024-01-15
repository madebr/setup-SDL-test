#include "SDL.h"
#include "SDL_test.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_rtf.h"
#ifdef WITH_SDLNET
#include "SDL_net.h"
#endif

#define LOG_SDL_VERSION(WHAT, COMPILED_CBFN, LINKED_CBFN)                       \
    do {                                                                        \
        SDL_version compiled_;                                                  \
        SDL_version linked_;                                                    \
        COMPILED_CBFN(&compiled_)                                               \
        LINKED_CBFN(&linked_);                                                  \
        LOG_CV_LV(WHAT, &compiled_, &linked_);                                  \
    } while (0)

#define LOG_SDL_VERSION_RET(WHAT, COMPILED_CBFN, LINKED_CBFN)                   \
    do {                                                                        \
        SDL_version compiled_;                                                  \
        const SDL_version *linked_;                                             \
        COMPILED_CBFN(&compiled_)                                               \
        linked_ = LINKED_CBFN();                                                \
        LOG_CV_LV(WHAT, &compiled_, linked_);                                   \
    } while (0)

#define LOG_CV_LV(WHAT, CV, LV)                                                 \
    do {                                                                        \
        SDL_Log(WHAT ": compiled version: %d.%d.%d, linked version: %d.%d.%d",  \
            (CV)->major, (CV)->minor, (CV)->patch,                              \
            (LV)->major, (LV)->minor, (LV)->patch);                             \
                                                                                \
    } while (0)

int main(int argc, char *argv[]) {
    int i;
    SDLTest_CommonState *state;
    SDL_Window *window;
    SDL_Renderer *renderer;

    LOG_SDL_VERSION("SDL", SDL_VERSION, SDL_GetVersion);
    LOG_SDL_VERSION_RET("SDL_image", SDL_IMAGE_VERSION, IMG_Linked_Version);
    LOG_SDL_VERSION_RET("SDL_mixer", SDL_MIXER_VERSION, Mix_Linked_Version);
    LOG_SDL_VERSION_RET("SDL_ttf", SDL_TTF_VERSION, TTF_Linked_Version);
    LOG_SDL_VERSION_RET("SDL_rtf", SDL_RTF_VERSION, RTF_Linked_Version);
#ifdef WITH_SDLNET
    LOG_SDL_VERSION_RET("SDL_net", SDL_NET_VERSION, SDLNet_Linked_Version);
#endif

    /* Initialize test framework */
    state = SDLTest_CommonCreateState(argv, SDL_INIT_EVERYTHING);
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
            if (event.type == SDL_QUIT) {
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
