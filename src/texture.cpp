#include <iostream>
#include "../include/texture.h"
#include "../include/init.h"

LTexture::LTexture() {
    mWidth = 0;
    mHeight = 0;
    mTexture = NULL;
}

LTexture::~LTexture() {
    free();
}

SDL_Texture* LTexture::getTexture() {
    return mTexture;
}

void LTexture::free() {
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = mHeight = 0;
    }
}

int LTexture::getWidth() const {
    return mWidth;
}

int LTexture::getHeight() const {
    return mHeight;
}

bool LTexture::loadSpriteSheet(std::string path, SDL_Renderer* gRenderer) {
    free();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface) return false;

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0, 0xFF ));
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, TTF_Font* gFont, SDL_Color& textColor, SDL_Renderer* gRenderer ) {
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL ) {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else {
            //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL ) {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}

void LTexture::setPosition(int x, int y) {
    Position.x = x;
    Position.y = y;
}

void LTexture::setCurrentPosition(int x, int y) {
    CurrentPosition.x = x;
    CurrentPosition.y = y;
}

SDL_Point LTexture::getPosition() const {
    return Position;
}

void LTexture::move() {
    if (CurrentPosition.x < Position.x)
        CurrentPosition.x += TEXTURE_VEL;
    else if (CurrentPosition.x > Position.x)
        CurrentPosition.x -= TEXTURE_VEL;
    else if (CurrentPosition.y > Position.y)
        CurrentPosition.y -= TEXTURE_VEL;
    else if (CurrentPosition.y < Position.y)
        CurrentPosition.y += TEXTURE_VEL;
}

void LTexture::render(SDL_Renderer* gRenderer) {
    SDL_Rect renderQuad = {CurrentPosition.x, CurrentPosition.y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void LTexture::handleEvent(SDL_Event* e) {
    if ( (e->type == SDL_KEYDOWN) && e->key.repeat == 0) {
        //Set mouse over sprite
        switch( e->key.keysym.sym)
        {
            case SDLK_RIGHT:
                Position.x += mWidth;
            break;
            case SDLK_LEFT:
                if (Position.x > 50)
                    Position.x -= mWidth;
            break;
        }
    }
}
