#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

const int TEXTURE_VEL = 2;
class LTexture {
private:
    SDL_Texture* mTexture;
    int mWidth, mHeight;
    SDL_Point Position;
    SDL_Point CurrentPosition;
public:
    LTexture();
    ~LTexture();
    SDL_Texture* getTexture();
    bool loadSpriteSheet(std::string path, SDL_Renderer* gRenderer);
    bool loadFromRenderedText( std::string textureText, TTF_Font* gFont, SDL_Color& textColor, SDL_Renderer* gRenderer );
    void setPosition(int x, int y);
    void setCurrentPosition(int x, int y);
    SDL_Point getPosition() const;
    void move();
    void render (SDL_Renderer* gRenderer);
    void handleEvent(SDL_Event* e);
    void free();
    int getWidth() const;
    int getHeight() const;
};

#endif
