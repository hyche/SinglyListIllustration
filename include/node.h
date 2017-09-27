#ifndef _NODE_H
#define _NODE_H

#include <SDL2/SDL.h>
#include <string>
const int NODE_WIDTH = 150;
const int NODE_HEIGHT = 100;
const int NODE_VEL = 5;

enum NodeSprite {
    NODE_SPRITE_NORMAL = 0,
    NODE_SPRITE_MARK = 1,
    NODE_SPRITE_TOTAL = 2
};

class Node {
private:
    SDL_Point Position; //last position
    SDL_Point CurrentPosition;
    SDL_Rect* SpriteClips;
    int CurrentSprite;
    SDL_Texture* nodeTexture;
    SDL_Texture* itemTexture;
    bool used;
public:
    std::string item;
    Node* pNext;
    Node();
    ~Node();
    void setCurrentPosition(int x, int y);
    void setPosition(int x, int y);
    int& setCurrentSprite();
    SDL_Point getPosition() const;
    int getCurrentSprite() const;
    void handleEvent( SDL_Event* e );
    bool isUsed() const;
    void setUsedBackToFalse();
    bool loadSpriteNodeSheets(std::string path, SDL_Renderer* gRenderer);
    bool loadRenderedText(std::string str, SDL_Renderer* gRenderer);
    void loadNode(std::string n, int x, int y, SDL_Renderer* gRenderer, bool move=false);
    void move();
    void render(SDL_Renderer*);
    void freeNodeTexture();
    void freeItemTexture();
    Node & operator=(const Node& n);
};

#endif
