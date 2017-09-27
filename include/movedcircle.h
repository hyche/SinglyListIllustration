#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "node.h"
#include <string>

const int MOVED_CIRCLE_VEL = 5;

enum MovedCircleSprite {
    YELLOW_CIRLCE = 0,
    RED_CIRCLE = 1,
    CIRCLE_SPRITE_TOTAL = 2,
};

class MCircle {
private:
    SDL_Texture* mTexture;
    SDL_Point Position;
    SDL_Point CurrentPosition;
    SDL_Rect* SpriteClips;
    int CurrentSprite;
    Node* pHead;
public:
    MCircle();
    virtual ~MCircle();
    SDL_Texture* getTexture();
    bool loadSpriteSheet(std::string path, SDL_Renderer* gRenderer);
    bool hasNode(int x, int y);
    void setPHead(Node* pNode);
    void setPosition(int x, int y);
    void setCurrentPosition(int x, int y);
    int& setCurrentSprite();
    int getCurrentSprite() const;
    SDL_Point getCPosition() const;
    SDL_Point getPosition() const;
    Node* getPHead();
    void move();
    void render (SDL_Renderer* gRenderer);
    void free();
};

class TCircle : public MCircle {
    public:
        TCircle();
        virtual ~TCircle();
        void handleEvent(SDL_Event* e);
};

class SCircle : public MCircle {
    public:
        Node* pcur;
        SCircle();
        virtual ~SCircle();
};

#endif
