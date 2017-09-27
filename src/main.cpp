#include <iostream>
#include "../include/button.h"
#include "../include/movedcircle.h"
#include "../include/init.h"
#include "../include/singlylinkedlist.h"
#include "../include/textbox.h"
using std::cout;
using std::endl;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
LButton* Button;

void init();
void loadMedia();
void close();

int main(int argc, char* args[]) {
    bool quit = false;
    std::string text = "0";
    init();
    loadMedia();
    TextBox tb(BUTTON_WIDTH + 10, 0, BUTTON_WIDTH, BUTTON_HEIGHT);

    SinglyLinkedList sll;
    sll.setMode() = OFF;
    while (!quit) {
        bool renderText = false;
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            for (int i=0; i < BUTTON_TOTAL; ++i) {
                Button[i].handleEvent( &e );
            }
            tb.handleEvent(&e, text, renderText, gRenderer);
            sll.handleEvent(&e);
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        for (int i=0; i < BUTTON_TOTAL; ++i) {
            Button[i].render(gRenderer);
        }
        if (Button[BUTTON_LOAD].isUsed()) {
            if (sll.getMode() == OFF)
                sll.load("input.txt", gRenderer);
            else
                sll.SBSLoad("input.txt", gRenderer);
            Button[BUTTON_LOAD].setUsedBackToFalse();
        }
        if (Button[BUTTON_SAVE].isUsed()) {
            sll.save("save.txt");
            Button[BUTTON_SAVE].setUsedBackToFalse();
        }

        if (Button[BUTTON_INIT].isUsed()) {
            sll.removeAll();
            Button[BUTTON_INIT].setUsedBackToFalse();
        }

        if (Button[BUTTON_INSERT_BF].isUsed()) {
            if (sll.getMode() == OFF)
                sll.insertBefore(text, gRenderer);
            else
                sll.SBSInsertBefore(text, gRenderer);
            Button[BUTTON_INSERT_BF].setUsedBackToFalse();
        }

        if (Button[BUTTON_INSERT_H].isUsed()) {
            if (sll.getMode() == OFF)
                sll.insertHead(text, gRenderer);
            else
                sll.SBSInsertHead(text, gRenderer);
            Button[BUTTON_INSERT_H].setUsedBackToFalse();
        }

        if (Button[BUTTON_INSERT_T].isUsed()) {
            if (sll.getMode() == OFF)
                sll.insertTail(text, gRenderer);
            else
                sll.SBSInsertTail(text, gRenderer);
            Button[BUTTON_INSERT_T].setUsedBackToFalse();
        }

        if (Button[BUTTON_TRAVERSE].isUsed()) {
            if (sll.getMode() == ON)
                sll.ToggleTraversedCircle(gRenderer);
            else sll.Traverse(gRenderer);
            Button[BUTTON_TRAVERSE].setUsedBackToFalse();
        }
        if (Button[BUTTON_FIND].isUsed()) {
            if (sll.getMode() == OFF)
                sll.find(text);
            else
                sll.SBSFind(text, gRenderer);
            Button[BUTTON_FIND].setUsedBackToFalse();
        }
        if (Button[BUTTON_RANDOM].isUsed()) {
            if (sll.getMode() == OFF)
                sll.random(gRenderer);
            else {
                sll.SBSRandom(gRenderer);
            }
            Button[BUTTON_RANDOM].setUsedBackToFalse();
        }

        if (Button[BUTTON_REMOVE_T].isUsed()) {
            sll.removeTail();
            Button[BUTTON_REMOVE_T].setUsedBackToFalse();
        }

        if (Button[BUTTON_REMOVE_ALL].isUsed()) {
            sll.removeAll();
            Button[BUTTON_REMOVE_ALL].setUsedBackToFalse();
        }

        if (Button[BUTTON_CHANGE_MOD].isUsed()) {
            if (sll.getMode() == OFF) sll.setMode() = ON;
            else sll.setMode() = OFF;
            Button[BUTTON_CHANGE_MOD].setUsedBackToFalse();
        }
        sll.render(gRenderer);
        tb.render(gRenderer);
        SDL_RenderPresent( gRenderer );
    }
    close();
    return 0;
}

void init() {
    SDL_Init( SDL_INIT_VIDEO );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    TTF_Init();
    gWindow = SDL_CreateWindow( "Singly Linked List Illustration", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    Button = new LButton[BUTTON_TOTAL];
}

void loadMedia() {
    Button[BUTTON_LOAD].loadSpriteButtonSheets("../resources/LOAD FILE.png", gRenderer);
    Button[BUTTON_SAVE].loadSpriteButtonSheets("../resources/SAVE FILE.png", gRenderer);
    Button[BUTTON_INIT].loadSpriteButtonSheets("../resources/INIT.png", gRenderer);
    Button[BUTTON_INSERT_BF].loadSpriteButtonSheets("../resources/INSERT BF.png", gRenderer);
    Button[BUTTON_INSERT_H].loadSpriteButtonSheets("../resources/INSERT H.png", gRenderer);
    Button[BUTTON_INSERT_T].loadSpriteButtonSheets("../resources/INSERT T.png", gRenderer);
    Button[BUTTON_TRAVERSE].loadSpriteButtonSheets("../resources/TRAVERSE.png", gRenderer);
    Button[BUTTON_FIND].loadSpriteButtonSheets("../resources/FIND INT.png", gRenderer);
    Button[BUTTON_RANDOM].loadSpriteButtonSheets("../resources/RANDOM.png", gRenderer);
    Button[BUTTON_REMOVE_T].loadSpriteButtonSheets("../resources/REMOVE_T.png", gRenderer);
    Button[BUTTON_REMOVE_ALL].loadSpriteButtonSheets("../resources/REMOVE_A.png", gRenderer);
    Button[BUTTON_CHANGE_MOD].loadSpriteButtonSheets("../resources/CH.MODE.png", gRenderer);
    for (int i=0; i<BUTTON_TOTAL; ++i) {
        Button[i].setPosition(0, i* 60);
    }
}

void close() {
    TTF_Quit();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
}
