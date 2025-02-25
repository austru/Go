#include "GoUI.h"
#include "Go.h"
#include "GoBoard2D.h"
#include <iostream>

namespace GUI {

int startUI()
{
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return 1;
        }
    
        // Game loop
        bool quit = false;
        SDL_Event event;
    
        Go g;
    
        //boost::asio::io_context io_context;
        //GoServer server(io_context, 12345);
        //io_context.run();
    
        GoBoard2D board(g.getBoard(), 800, 800);
        board.draw();
    
        while (!quit) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                    int x = event.motion.x;
                    int y = event.motion.y;
                    std::optional<std::size_t> p = board.closestIntersection(x, y);
                    if (p.has_value()) {
                        g.placeStone(p.value());
                        board.draw();
                    }
                }
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    board.draw();
                }
            }
            //board.draw();
        }
    
        return 0;
}

}