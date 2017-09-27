#ifndef _BUTTON_H
#define _BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "singlylinkedlist.h"

const int BUTTON_WIDTH = 130;
const int BUTTON_HEIGHT = 54;
enum Buttons {
    BUTTON_LOAD = 0,
    BUTTON_SAVE = 1,
    BUTTON_INIT = 2,
    BUTTON_INSERT_BF = 3,
    BUTTON_INSERT_H = 4,
    BUTTON_INSERT_T = 5,
    BUTTON_TRAVERSE = 6,
    BUTTON_FIND = 7,
    BUTTON_RANDOM = 8,
    BUTTON_REMOVE_T = 9,
    BUTTON_REMOVE_ALL = 10,
    BUTTON_CHANGE_MOD = 11,
    BUTTON_TOTAL = 12,
};

enum LButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_OVER_MOUSE_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class LButton {
private:
    SDL_Point Position;
    SDL_Rect* SpriteClips;
    LButtonSprite CurrentSprite;
    SDL_Texture* buttonTexture;
    bool used; // check if this button is used
public:
    LButton();
    ~LButton();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    bool loadSpriteButtonSheets(std::string path, SDL_Renderer* gRenderer);
    LButtonSprite getCurrentSprite();
    void render(SDL_Renderer*);
    void free();
    bool isUsed() const;
    void setUsedBackToFalse();
};



#endif
