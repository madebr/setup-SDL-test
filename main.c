#include <SDL3/SDL.h>
#include <SDL3/SDL_test.h>

int main(int argc, char *argv[]) {
    int i;
    SDLTest_CommonState *state;
    SDL_Window *window;
    SDL_Renderer *renderer;

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

    SDL_SetWindowTitle(window, "SDL issue");

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
