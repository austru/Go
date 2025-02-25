#include "GoBoard2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <iostream>

GoBoard2D::GoBoard2D(std::shared_ptr<GoBoard> board, const int windowWidth, const int windowHeight) /*: board(board)*/
{
    this->board = board;
    window = SDL_CreateWindow("Go", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        throw std::runtime_error("GoBoard2D could not be created! SDL_Error: " + std::string(SDL_GetError()));

    SDL_SetWindowResizable(window, SDL_TRUE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
        throw std::runtime_error("Renderer could not be created! SDL_Error: " + std::string(SDL_GetError()));

    SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;

    SDL_Surface *whiteStone = IMG_Load("../resources/whiteStone.png");
    if (!whiteStone)
        std::cout<<"white stone not found"<<std::endl;
    whiteTexture = SDL_CreateTextureFromSurface(renderer, whiteStone);
    SDL_FreeSurface(whiteStone);

    SDL_Surface *blackStone = IMG_Load("../resources/blackStone.png");
    if (!blackStone)
        std::cout<< SDL_GetError() << std::endl;
    blackTexture = SDL_CreateTextureFromSurface(renderer, blackStone);
    SDL_FreeSurface(blackStone);

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

    xCoordinateSpacing = static_cast<double>(windowWidth) / boardWidth;
    yCoordinateSpacing = static_cast<double>(windowHeight) / boardHeight;

    const double xBorder = xCoordinateSpacing / 2.f;
    const double yBorder = yCoordinateSpacing / 2.f;

    const double lineWidth = xBorder / 10.f;
    const double halfLineWidth = lineWidth / 2.f;


    intersections.clear();
    for (int i = 0; i < board->getSize(); i++) {
        int x = i % board->getWidth();
        int y = i / board->getHeight();
        intersections.push_back(
            Point{
                xBorder + xCoordinateSpacing*static_cast<double>(x),
                yBorder + yCoordinateSpacing*static_cast<double>(board->getHeight()-y-1)
            }
        );
    }

    lines.clear();
    for (int x = 0; x < boardWidth; x++) {
        double x1 = xBorder + static_cast<double>(x) * xCoordinateSpacing - halfLineWidth;
        double y1 = yBorder - halfLineWidth;
        double x2 = lineWidth;
        double y2 = windowHeight - yCoordinateSpacing + lineWidth;
        lines.push_back({
            static_cast<int>(x1),
            static_cast<int>(y1),
            static_cast<int>(x2),
            static_cast<int>(y2)
        });
    }
    for (int  y = 0; y < boardHeight; y++) {
        double x1 = xBorder - halfLineWidth;
        double y1 = yBorder + static_cast<double>(y) * yCoordinateSpacing - halfLineWidth;
        double x2 = windowWidth - xCoordinateSpacing + lineWidth;
        double y2 = lineWidth;
        lines.push_back({
            static_cast<int>(x1),
            static_cast<int>(y1),
            static_cast<int>(x2),
            static_cast<int>(y2)
        });
    }
        
}



void GoBoard2D::draw()
{
    SDL_SetRenderDrawColor(renderer, 210, 175, 120, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRects(renderer, lines.data(), (int)(board->getWidth()+board->getHeight()));


    for (std::size_t i = 0; i < intersections.size(); i++) {
        std::shared_ptr<Stone> s = board->getPieceAt(i).value();
        if (!s->isEmpty()) {
            SDL_Rect stone = {
                    static_cast<int>(intersections.at(i).x-(xCoordinateSpacing/2.0)),
                    static_cast<int>(intersections.at(i).y-(yCoordinateSpacing/2.0)),
                    static_cast<int>(xCoordinateSpacing),
                    static_cast<int>(yCoordinateSpacing)
                };

            if (s->getId() == 7)
                SDL_RenderCopy(renderer, blackTexture, NULL, &stone);
                //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            else
                SDL_RenderCopy(renderer, whiteTexture, NULL, &stone);
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            
            //SDL_RenderFillRect(renderer, &stone);
        }
    }

    SDL_RenderPresent(renderer); //Update screen
}

std::optional<std::size_t> GoBoard2D::closestIntersection(int x, int y)
{
    SDL_RenderGetLogicalSize(renderer, &windowHeight, &windowWidth);
    if (x < 0 || y < 0 || x >= windowWidth || y >= windowHeight || intersections.empty())
        return std::nullopt;
    int xIndex = (((double)x - (*(intersections.begin())).x + (xCoordinateSpacing/2.0)) / xCoordinateSpacing);
    int yIndex = (((double)y - (*(intersections.end()-1)).y + (yCoordinateSpacing/2.0)) / yCoordinateSpacing);
    return (board->getWidth()-1-yIndex)*board->getWidth()+xIndex;
}
