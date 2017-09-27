#include <iostream>
#include "../include/textbox.h"

TextBox::TextBox(int x, int y, int w, int h) {
    Text = NULL;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    textColor = {0, 0, 0};
    gFont = TTF_OpenFont("../resources/Literation Mono Powerline.ttf", 26);
}

TextBox::TextBox() {
    Text = NULL;
    box.x = box.y = box.w = box.h = 0;
    TTF_CloseFont(gFont);
}

TextBox::~TextBox() {
    free();
}

bool TextBox::loadFromRenderedText(std::string textureText, SDL_Renderer* gRenderer) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface != NULL) {
        //Create texture from surface pixels
        Text = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (Text == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else {
            box.w = textSurface->w;
            box.h = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }
    else {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    return Text!= NULL;
}

void TextBox::free() {
    if (Text != NULL)
    {
        SDL_DestroyTexture(Text );
        Text = NULL;
        //box.x = box.y = box.w = box.h = 0;
    }
}

void TextBox::render(SDL_Renderer* gRenderer)  {;
    SDL_RenderCopy(gRenderer, Text , 0, &box);
}

void TextBox::handleEvent(SDL_Event* e, std::string& a, bool& renderText, SDL_Renderer* gRenderer) {
    int x = 0, y = 0;
    //If a mouse button was pressed
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        //If the left mouse button was pressed
        if (e->button.button == SDL_BUTTON_LEFT) {
            x = e->button.x;
            y = e->button.y;
            //If the mouse is over the button
            if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h)) {
                a = "";
                SDL_Event ee;
                SDL_StartTextInput();

                bool check_quit = false;
                renderText = false;
                while (check_quit == false)
                {
                    //Handle events on queue
                    while (SDL_PollEvent(&ee) != 0) {

                        if (ee.type == SDL_KEYDOWN) {
                                //Handle backspace
                            if (ee.key.keysym.sym == SDLK_BACKSPACE && a.length() > 0) {
                                //lop off character
                                a.pop_back();
                                renderText = true;
                            }
                        }
                        //Special text input event
                        else if (ee.type == SDL_TEXTINPUT) {
                            //Not copy or pasting
                            if (!((ee.text.text[0] == 'c' || ee.text.text[0] == 'C') && (ee.text.text[0] == 'v' || ee.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)){
                                    //Append character
                                    a += ee.text.text;
                                    renderText = true;
                                }
                            }
                        else if (ee.button.button == SDL_BUTTON_RIGHT) {
                                check_quit = true;
                        }
                        if (renderText) {
                            if (a != "")
                                loadFromRenderedText(a, gRenderer);
                            else
                                loadFromRenderedText(" ", gRenderer);
                        }
                        render(gRenderer);
                        SDL_RenderPresent(gRenderer);
                    }
                }
                SDL_StopTextInput();
            }
        }
    }

}
