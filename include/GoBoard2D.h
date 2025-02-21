#ifndef GOBOARD2D_H
#define GOBOARD2D_H

#include "GoBoard.h"
#include <SDL.h>

struct Point {
        double x;
        double y;
};

class GoBoard2D {

public:
    GoBoard2D(std::shared_ptr<GoBoard>, const int, const int);
    ~GoBoard2D();

    void init();
    void draw();
    std::optional<std::size_t> closestIntersection(int, int);


protected:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::shared_ptr<GoBoard> board;
    std::vector<Point> intersections;
private:
    double lineWidth;
    double xCoordinateSpacing;
    double yCoordinateSpacing;
    SDL_Rect* lines;

    int windowWidth;
    int windowHeight;
};

#endif
