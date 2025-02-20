#include "GoBoard2D.h"
#include <SDL.h>
#include <iostream>

GoBoard2D::GoBoard2D(std::shared_ptr<GoBoard> board, const int windowWidth, const int windowHeight) /*: board(board)*/
{
    this->board = board;
    window = SDL_CreateWindow("Go", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        throw std::runtime_error("GoBoard2D could not be created! SDL_Error: " + std::string(SDL_GetError()));

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
        throw std::runtime_error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));

    init();
}

GoBoard2D::~GoBoard2D()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void GoBoard2D::init()
{
    
    double boardWidth = static_cast<double>(board->getWidth());
    double boardHeight = static_cast<double>(board->getHeight());

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    double boardBorder = 25.f;
    lineWidth = 4.0;


    
    xCoordinateSpacing = ((static_cast<double>(windowWidth) - (2.0)*boardBorder - lineWidth) / (boardWidth-(1.0)));
    yCoordinateSpacing = ((static_cast<double>(windowHeight) - (2.0)*boardBorder - lineWidth) / (boardHeight-(1.0)));

    for (int i = 0; i < board->getSize(); i++) {
        int x = i % board->getWidth();
        int y = i / board->getHeight();
        intersections.push_back(Point{
            boardBorder + lineWidth/2.0 + xCoordinateSpacing*static_cast<double>(x),
            boardBorder + lineWidth/2.0 + yCoordinateSpacing*static_cast<double>(board->getHeight()-y-1)
        });
    }


    //verticalLineSpacing = xCoordinateSpacing
    //verticalLineSpacing = ((windowWidth - 2*boardBorder - boardWidth*lineWidth) / (boardWidth - 1)) + lineWidth;
    //horizontalLineSpacing = ((windowHeight - 2*boardBorder - boardHeight*lineWidth) / (boardHeight - 1)) + lineWidth;

    lines = (SDL_Rect*)malloc((board->getWidth()+board->getHeight())*sizeof(SDL_Rect));
    for (int x = 0; x < boardWidth; x++)
        lines[x] = {(int)(x*xCoordinateSpacing+boardBorder), (int)(boardBorder), (int)lineWidth, windowHeight - 2*(int)boardBorder};
    for (int  y = 0; y < boardHeight; y++)
        lines[(int)boardWidth + y] = {(int)boardBorder, (int)(y*yCoordinateSpacing+boardBorder), windowWidth - 2*(int)boardBorder, (int)lineWidth};
        
}



void GoBoard2D::draw()
{
    SDL_SetRenderDrawColor(renderer, 210, 175, 120, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRects(renderer, lines, (int)(board->getWidth()+board->getHeight()));

    for (std::size_t i = 0; i < intersections.size(); i++) {
        std::shared_ptr<Stone> s = board->getPieceAt(i).value();
        if (!s->isEmpty()) {
            SDL_Rect stone = {static_cast<int>(intersections.at(i).x)-10, static_cast<int>(intersections.at(i).y)-10, 20, 20};
            if (s->getId() == 7)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            else
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &stone);
        }
    }
    //std::cout<<"("<<x<<","<<y<<")"<<std::endl;

    SDL_RenderPresent(renderer); //Update screen
}

std::optional<std::size_t> GoBoard2D::closestIntersection(int x, int y)
{
    if (intersections.empty())
        return std::nullopt;
    int xIndex = (((double)x - (*(intersections.begin())).x + (xCoordinateSpacing/2.0)) / xCoordinateSpacing);
    int yIndex = (((double)y - (*(intersections.end()-1)).y + (yCoordinateSpacing/2.0)) / yCoordinateSpacing);
    return (board->getWidth()-1-yIndex)*board->getWidth()+xIndex;
}
