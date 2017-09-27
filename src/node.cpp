#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../include/init.h"
#include "../include/node.h"


Node::Node() {
    Position.x = Position.y = 0;
    CurrentPosition.x = CurrentPosition.y = 0;
    SpriteClips = new SDL_Rect[NODE_SPRITE_TOTAL];
    nodeTexture = NULL;
    itemTexture = NULL;
    CurrentSprite = NODE_SPRITE_NORMAL;
    used = false;
}

Node::~Node() {
    freeNodeTexture();
    freeItemTexture();
    Position.x = Position.y = 0;
    CurrentSprite = NODE_SPRITE_NORMAL;
    used = false;
    delete [] SpriteClips;
}

void Node::setCurrentPosition(int x, int y) {
    CurrentPosition.x = x;
    CurrentPosition.y = y;
}

void Node::setPosition(int x, int y) {
    Position.x = x;
    Position.y = y;
}

int& Node::setCurrentSprite() {
    return CurrentSprite;
}

SDL_Point Node::getPosition() const {
    return Position;
}

int Node::getCurrentSprite() const {
    return CurrentSprite;
}

void Node::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if( x < Position.x ) inside = false;
        else if( x > Position.x + NODE_WIDTH ) inside = false;
        else if( y < Position.y ) inside = false;
        else if( y > Position.y + NODE_WIDTH ) inside = false;
        //Mouse is inside Node 
        else
        {
            //Set mouse over sprite
            switch( e->type)
            {
                case SDL_MOUSEBUTTONDOWN:
                used = true;
                break;

                case SDL_MOUSEBUTTONUP:
                break;
            }
        }
    }
}

bool Node::isUsed() const {
    return used;
}

void Node::setUsedBackToFalse() {
    used = false; // because only need it once the envent occurs
}

bool Node::loadSpriteNodeSheets(std::string path, SDL_Renderer* gRenderer) {
    freeNodeTexture();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface) return false;

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0, 0xFF ));
    nodeTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!nodeTexture) return false;

    for( int i = 0; i < NODE_SPRITE_TOTAL; ++i ) {
        SpriteClips[ i ].x = 0;
        SpriteClips[ i ].y = i * NODE_HEIGHT;
        SpriteClips[ i ].w = NODE_WIDTH;
        SpriteClips[ i ].h = NODE_HEIGHT;
    }
    return nodeTexture != NULL;
}

bool Node::loadRenderedText(std::string str, SDL_Renderer* gRenderer) {
    freeItemTexture();
    TTF_Font* gFont = TTF_OpenFont("../resources/Literation Mono Powerline.ttf", 28);
    SDL_Color textColor = {0x00, 0x00, 0x00};
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, str.c_str(), textColor );
    if (!textSurface)
        return false;
    else
        itemTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(gFont);
    return itemTexture != NULL;
}

void Node::loadNode(std::string n, int x, int y, SDL_Renderer* gRenderer, bool move) {
    loadSpriteNodeSheets("../resources/Node.png", gRenderer);
    loadRenderedText(n, gRenderer);
    if (move) setCurrentPosition(50, (SCREEN_HEIGHT - NODE_HEIGHT) / 4);
    else setCurrentPosition(x, y);
    setPosition(x, y);
}

void Node::move() {
    if (CurrentPosition.x < Position.x)
        CurrentPosition.x += NODE_VEL;
    else if (CurrentPosition.x > Position.x)
        CurrentPosition.x -= NODE_VEL;
    else if (CurrentPosition.y > Position.y)
        CurrentPosition.y -= NODE_VEL;
    else if (CurrentPosition.y < Position.y)
        CurrentPosition.y += NODE_VEL;
}

void Node::render(SDL_Renderer* gRenderer) {
    SDL_Rect renderQuad = {CurrentPosition.x, CurrentPosition.y, NODE_WIDTH, NODE_HEIGHT};
    SDL_Rect renderQuadText = {CurrentPosition.x + (NODE_WIDTH - 50) / 4, CurrentPosition.y + NODE_HEIGHT / 4, (NODE_WIDTH - 50 )/ 2, NODE_HEIGHT / 2};
    SDL_RenderCopy(gRenderer, nodeTexture, &SpriteClips[ CurrentSprite ], &renderQuad);
    SDL_RenderCopy(gRenderer, itemTexture, NULL, &renderQuadText);
}

void Node::freeNodeTexture() {
    if (nodeTexture) {
        SDL_DestroyTexture(nodeTexture);
        nodeTexture = NULL;
    }
}

void Node::freeItemTexture() {
    if (itemTexture) {
        itemTexture = NULL;
        SDL_DestroyTexture(itemTexture);
    }
}

Node& Node::operator=(const Node& n) {
    if (this == &n) return *this;
    CurrentSprite = n.CurrentSprite;
    Position = n.Position;

    delete [] SpriteClips;
    SpriteClips = new SDL_Rect[NODE_SPRITE_TOTAL];
    freeNodeTexture();
    freeItemTexture();
    nodeTexture = n.nodeTexture;
    itemTexture = n.itemTexture;
    for (int i=0; i < NODE_SPRITE_TOTAL; ++i) 
        SpriteClips[i] = n.SpriteClips[i];
    return *this;
}

