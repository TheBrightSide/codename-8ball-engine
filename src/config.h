#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#if defined(USE_RAYLIB)
    #define WINDOW_TITLE "Game (raylib)"
#else
    #define WINDOW_TITLE "Game (unknown backend)"
#endif