#ifndef _TEXTBOX_H
#define _TEXTBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextBox
{
public:
    TextBox(int x, int y, int w, int h);
    TextBox();
    ~TextBox();

    bool loadFromRenderedText(std::string textureText, SDL_Renderer* gRenderer);
    void free();
    void render(SDL_Renderer* gRenderer);
    void handleEvent(SDL_Event* e, std::string& a, bool& renderText, SDL_Renderer* gRenderer);
private:
    SDL_Texture* Text;
    SDL_Color textColor;
    TTF_Font* gFont;
    SDL_Rect box;
};



#endif
