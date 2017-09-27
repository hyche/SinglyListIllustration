#include <iostream>
#include "../include/movedcircle.h"
#include "../include/init.h"

MCircle::MCircle() {
    Position.x = Position.y = 0;
    CurrentSprite = YELLOW_CIRLCE;
    SpriteClips = new SDL_Rect [CIRCLE_SPRITE_TOTAL];
    mTexture = NULL;
    pHead = NULL;
}

MCircle::~MCircle() {
    free();
    delete [] SpriteClips;
    CurrentSprite = YELLOW_CIRLCE;
}

SDL_Texture* MCircle::getTexture() {
    return mTexture;
}

void MCircle::free() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        pHead = NULL;
        Position.x = Position.y = 0;
    }
}

bool MCircle::loadSpriteSheet(std::string path, SDL_Renderer* gRenderer) {
    free();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface) return false;

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0, 0xFF ));
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    for (int i=0; i < CIRCLE_SPRITE_TOTAL; ++i) {
        SpriteClips[i].x = 0;
        SpriteClips[i].y = i * NODE_HEIGHT;
        SpriteClips[i].w = NODE_WIDTH;
        SpriteClips[i].h = NODE_HEIGHT;
    }

    return mTexture != NULL;
}

bool MCircle::hasNode(int x, int y) {
    Node* pcur = pHead;
    while (pcur) {
        if (pcur->getPosition().x == x && pcur->getPosition().y == y)
            return true;
        pcur = pcur->pNext;
    }
    return false;
}

void MCircle::setPHead(Node* pNode) {
    pHead = pNode;
}

Node* MCircle::getPHead() {
    return pHead;
}

void MCircle::setPosition(int x, int y) {
    Position.x = x;
    Position.y = y;
}

void MCircle::setCurrentPosition(int x, int y) {
    CurrentPosition.x = x;
    CurrentPosition.y = y;
}

int& MCircle::setCurrentSprite() {
    return CurrentSprite;
}

int MCircle::getCurrentSprite() const {
    return CurrentSprite;
}

SDL_Point MCircle::getCPosition() const {
    return CurrentPosition;
}

SDL_Point MCircle::getPosition() const {
    return Position;
}

void MCircle::move() {
    if (CurrentPosition.y > Position.y)
        CurrentPosition.y -= MOVED_CIRCLE_VEL;
    else if (CurrentPosition.y < Position.y)
        CurrentPosition.y += MOVED_CIRCLE_VEL;
    else if (CurrentPosition.x < Position.x)
        CurrentPosition.x += MOVED_CIRCLE_VEL;
    else if (CurrentPosition.x > Position.x)
        CurrentPosition.x -= MOVED_CIRCLE_VEL;
}

void MCircle::render(SDL_Renderer* gRenderer) {
    SDL_Rect renderQuad = {CurrentPosition.x, CurrentPosition.y, NODE_WIDTH , NODE_HEIGHT};
    SDL_RenderCopy(gRenderer, mTexture, &SpriteClips[CurrentSprite], &renderQuad);
}


// =====================================Traversed Circle Definitions ===============================
//
TCircle::TCircle() {}
TCircle::~TCircle() {}
void TCircle::handleEvent(SDL_Event* e) {
    if ( (e->type == SDL_KEYDOWN) && e->key.repeat == 0 ) {
        //Set mouse over sprite
        switch( e->key.keysym.sym)
        {
            case SDLK_RIGHT:
                if (hasNode(getPosition().x + NODE_WIDTH, getPosition().y)){
                    setCurrentSprite() = YELLOW_CIRLCE;
                    setPosition(getPosition().x + NODE_WIDTH, getPosition().y);
                }
            break;
            case SDLK_LEFT:
                if (hasNode(getPosition().x - NODE_WIDTH, getPosition().y)){
                    setCurrentSprite() = YELLOW_CIRLCE;
                    setPosition(getPosition().x - NODE_WIDTH, getPosition().y);
                }
            break;
            case SDLK_UP:
                if (hasNode(getPosition().x, getPosition().y + NODE_HEIGHT)){
                    setCurrentSprite() = YELLOW_CIRLCE;
                    setPosition(getPosition().x, getPosition().y + NODE_HEIGHT);
                }
            break;
            case SDLK_DOWN:
                if (hasNode(getPosition().x, getPosition().y - NODE_HEIGHT)) {
                    setCurrentSprite() = YELLOW_CIRLCE;
                    setPosition(getPosition().x, getPosition().y - NODE_HEIGHT);
                }
            break;
            case SDLK_RETURN:
                setCurrentSprite() = RED_CIRCLE;
            break;
        }
    }
}

// =====================================SBS Circle Definitions ===============================
//
SCircle::SCircle() {
    pcur = NULL;
}

SCircle::~SCircle() {
    pcur = NULL;
}
