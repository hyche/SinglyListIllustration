#ifndef _SINGLYLINKEDLIST_H
#define _SINGLYLINKEDLIST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "movedcircle.h"
#include "node.h"

enum ModeSBS {
    OFF = 0,
    ON = 1,
};

class SinglyLinkedList {
private:
    Node* pHead;
    TCircle* TraversedCircle;
    SCircle* StepByStepCircle;
    int xPos, yPos;
    int elements;
    int modeSBS;
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    int getMode() const;
    int& setMode();
    void render(SDL_Renderer* gRenderer);
    void handleEvent( SDL_Event* e);
    void move(Node* n, int x, int y); // move each nodes from n in the linked list to the set distances
    void reset(); // reset all effect to normal
    void ToggleTraversedCircle(SDL_Renderer* gRenderer);
    void TurnOnSBSCircle(SDL_Renderer* gRenderer);
    bool hasTraversedCircle(int x, int y);
    bool hasSBSCircle(int x, int y);
    void random(SDL_Renderer* gRenderer);
    void find(std::string n);
    void load(std::string path, SDL_Renderer* gRenderer);
    void insertBefore(std::string n, SDL_Renderer* gRenderer);
    void insertHead(std::string n, SDL_Renderer* gRenderer);
    void insertTail(std::string n, SDL_Renderer* gRenderer);
    void save(std::string path);
    void Traverse(SDL_Renderer* gRenderer);
    void SBSLoad(std::string path, SDL_Renderer* gRenderer);
    void SBSFind(std::string n, SDL_Renderer* gRenderer);
    void SBSInsertBefore(std::string n, SDL_Renderer* gRenderer);
    void SBSInsertHead(std::string n, SDL_Renderer* gRenderer);
    bool SBSInsertTail(std::string n, SDL_Renderer* gRenderer);
    void SBSRandom(SDL_Renderer* gRenderer);
    void removeTail();
    void removeAll();
};

#endif
