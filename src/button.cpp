#include <iostream>
#include "../include/button.h"
#include "../include/singlylinkedlist.h"
#include "../include/init.h"

LButton::LButton() {
    Position.x = 0;
    Position.y = 0;
    CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    SpriteClips = new SDL_Rect[ BUTTON_SPRITE_TOTAL ];
    buttonTexture = NULL;
    used = false;
}

LButton::~LButton() {
    free();
    delete [] SpriteClips;
    Position.x = Position.y = 0;
    used = false;
}

void LButton::setPosition(int x, int y) {
    Position.x = x;
    Position.y = y;
}

void LButton::handleEvent(SDL_Event* e) {
    //if mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if( x < Position.x ) inside = false;
        else if( x > Position.x + BUTTON_WIDTH ) inside = false;
        else if( y < Position.y ) inside = false;
        else if( y > Position.y + BUTTON_HEIGHT ) inside = false;

        if( !inside ) CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type)
            {
                case SDL_MOUSEMOTION:
                CurrentSprite = BUTTON_SPRITE_OVER_MOUSE_MOTION;
                break;

                case SDL_MOUSEBUTTONDOWN:
                CurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                used = true;
                break;

                case SDL_MOUSEBUTTONUP:
                //mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
                break;
            }
        }
    }
}

void LButton::render(SDL_Renderer* gRenderer) {
    SDL_Rect renderQuad = {Position.x, Position.y, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderCopy(gRenderer, buttonTexture, &SpriteClips[ CurrentSprite ], &renderQuad);
}

bool LButton::loadSpriteButtonSheets(std::string path, SDL_Renderer* gRenderer) {
	using std::cout;
	using std::endl;

    free();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface) {
		cout << "fail to load surface\n" << endl;
		return false;
	}

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0, 0xFF ));
    buttonTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!buttonTexture) return false;

    for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i ) {
        SpriteClips[ i ].x = 0;
        SpriteClips[ i ].y = i * BUTTON_HEIGHT;
        SpriteClips[ i ].w = BUTTON_WIDTH;
        SpriteClips[ i ].h = BUTTON_HEIGHT;
    }

    return buttonTexture != NULL;
}

void LButton::free() {
    if (buttonTexture) {
        SDL_DestroyTexture(buttonTexture);
        buttonTexture = NULL;
    }
}

bool LButton::isUsed() const {
    return used;
}

void LButton::setUsedBackToFalse() {
    used = false; // because only need it once the envent occurs
}
