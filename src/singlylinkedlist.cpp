#include <iostream>
#include <fstream>
#include "../include/init.h"
#include "../include/node.h"
#include "../include/singlylinkedlist.h"


SinglyLinkedList::SinglyLinkedList() {
    pHead = NULL;
    TraversedCircle = NULL;
    StepByStepCircle = NULL;
    modeSBS = OFF;
    xPos = 150;
    yPos = 100;
}

SinglyLinkedList::~SinglyLinkedList() {
    while (pHead) {
        Node* ptemp = pHead;
        pHead = pHead->pNext;
        delete ptemp;
    }
    if (TraversedCircle)
        delete TraversedCircle;
    if (StepByStepCircle)
        delete StepByStepCircle;
}

int SinglyLinkedList::getMode() const {
    return modeSBS;
}

int& SinglyLinkedList::setMode() {
    return modeSBS;
}

void SinglyLinkedList::render(SDL_Renderer* gRenderer) {
    Node* pcur = pHead;
    while (pcur) {
        pcur->move();
        pcur->render(gRenderer);
        pcur = pcur->pNext;
    }
    if (TraversedCircle) {
        TraversedCircle->move();
        TraversedCircle->render(gRenderer);
    }

    if (StepByStepCircle) {
        StepByStepCircle->move();
        StepByStepCircle->render(gRenderer);
    }
}

void SinglyLinkedList::handleEvent(SDL_Event* e) {
    Node* pcur = pHead;
    while (pcur) {
        pcur->handleEvent(e);
        pcur = pcur->pNext;
    }

    if (TraversedCircle)
        TraversedCircle->handleEvent(e);
}

void SinglyLinkedList::move(Node* n, int x, int y) {
    Node* pcur = n;
    bool canMove = true;
    while (pcur) {
        if (hasTraversedCircle(pcur->getPosition().x, pcur->getPosition().y) && canMove) {
            TraversedCircle->setPosition(pcur->getPosition().x + x, pcur->getPosition().y + y);
            canMove = false;
        }

        if (hasSBSCircle(pcur->getPosition().x, pcur->getPosition().y) && canMove) {
            StepByStepCircle->setPosition(pcur->getPosition().x + x, pcur->getPosition().y +y);
            canMove = false;
        }

        pcur->setPosition(pcur->getPosition().x + x, pcur->getPosition().y + y);
        pcur = pcur->pNext;
    }
}

void SinglyLinkedList::reset() {
    Node* pcur = pHead;
    while (pcur) {
        pcur->setCurrentSprite() = NODE_SPRITE_NORMAL;
        pcur = pcur->pNext;
    }
}

void SinglyLinkedList::ToggleTraversedCircle(SDL_Renderer* gRenderer) {
    if (!TraversedCircle && pHead){
        TraversedCircle = new TCircle;
        TraversedCircle->loadSpriteSheet("../resources/Circle.png", gRenderer);
        TraversedCircle->setCurrentPosition(xPos, (SCREEN_HEIGHT - NODE_HEIGHT) - 100);
        TraversedCircle->setPosition(pHead->getPosition().x, pHead->getPosition().y);
        TraversedCircle->setPHead(pHead);
    }
    else if (TraversedCircle){
        delete TraversedCircle;
        TraversedCircle = NULL;
    }
}

void SinglyLinkedList::TurnOnSBSCircle(SDL_Renderer* gRenderer) {
    if (!StepByStepCircle){
        StepByStepCircle = new SCircle;
        StepByStepCircle->loadSpriteSheet("../resources/Circle.png", gRenderer);
        StepByStepCircle->setCurrentPosition(xPos, (SCREEN_HEIGHT - NODE_HEIGHT) - 100);
        StepByStepCircle->setPosition(xPos, yPos);
        StepByStepCircle->setPHead(pHead);
        StepByStepCircle->pcur = pHead;
        //std::cout << "OK" << std::endl;
    }

}

bool SinglyLinkedList::hasTraversedCircle(int x, int y) {
    if (TraversedCircle && TraversedCircle->getPosition().x == x && TraversedCircle->getPosition().y == y)
        return true;
    return false;
}

bool SinglyLinkedList::hasSBSCircle(int x, int y) {
    if (StepByStepCircle && StepByStepCircle->getPosition().x == x && StepByStepCircle->getPosition().y == y)
        return true;
    return false;
}

void SinglyLinkedList::random(SDL_Renderer* gRenderer) {
    int a = rand() % 5 + 1;
    int i = 0;
    while (i < a) {
        int b = rand() % 9999 + 1;
        std::string c = std::to_string(b);
        insertTail(c, gRenderer);
        ++i;
        //render(gRenderer);
    }
}

void SinglyLinkedList::find(std::string n) {
    Node* pcur = pHead;
    while (pcur) {
        if (pcur->item == n && pcur->getCurrentSprite() != NODE_SPRITE_MARK)
            pcur->setCurrentSprite() = NODE_SPRITE_MARK;
        else
            pcur->setCurrentSprite() = NODE_SPRITE_NORMAL;
        pcur = pcur->pNext;
    }
}

void SinglyLinkedList::load(std::string path, SDL_Renderer* gRenderer) {
    std::ifstream fin(path.c_str());
    if (!fin.is_open()) {
        std::cout << "can't open input file " << std::endl;
        exit(0);
    }
    removeAll();
    std::string n;
    while (fin >> n) {
        insertTail(n, gRenderer);
    }
    fin.clear();
    fin.close();
}

void SinglyLinkedList::insertBefore(std::string n, SDL_Renderer* gRenderer) {
    Node* pcur = pHead;
    if (!pcur) return;
    if (pcur->isUsed()) {
        insertHead(n, gRenderer);
        pcur->setUsedBackToFalse();
    }
    while (pcur->pNext) {
        if (pcur->pNext->isUsed()) {
            pcur->pNext->setUsedBackToFalse();
            move(pcur->pNext, NODE_WIDTH, 0);
            Node* ptemp = new Node;
            ptemp->item = n;
            ptemp->loadNode(n, pcur->getPosition().x + NODE_WIDTH, yPos, gRenderer);
            ptemp->pNext = pcur->pNext;
            pcur->pNext = ptemp;
        }
        pcur = pcur->pNext;
    }
}

void SinglyLinkedList::insertTail(std::string n, SDL_Renderer* gRenderer) {
    if (!pHead) {
        pHead = new Node;
        pHead->item = n;
        pHead->pNext = NULL;
        pHead->loadNode(n, xPos, yPos, gRenderer);
    }
    else {
        Node* pcur = pHead;
        while (pcur->pNext) pcur = pcur->pNext;
        pcur->pNext = new Node;
        pcur->pNext->item = n;
        pcur->pNext->pNext = NULL;
        pcur->pNext->loadNode(n, pcur->getPosition().x + NODE_WIDTH, yPos, gRenderer);
    }
}

void SinglyLinkedList::insertHead(std::string n, SDL_Renderer* gRenderer) {
    if (pHead)
        move(pHead, NODE_WIDTH, 0);
    Node* ptemp = new Node;
    ptemp->item = n;
    ptemp->pNext = pHead;
    ptemp->loadNode(n, xPos, yPos, gRenderer);
    pHead = ptemp;
    if (TraversedCircle)
        TraversedCircle->setPHead(pHead);
    if (StepByStepCircle)
        StepByStepCircle->setPHead(pHead);
}

void SinglyLinkedList::save(std::string path) {
    std::ofstream fout(path.c_str());
    if (!fout.is_open()) {
        std::cout << "can't open output file " << std::endl;
        exit(0);
    }
    Node* pcur = pHead;
    while (pcur) {
        fout << pcur->item << " ";
        pcur = pcur->pNext;
    }
    fout.close();
}

void SinglyLinkedList::Traverse(SDL_Renderer* gRenderer) {
    if (!TraversedCircle && pHead){
        Node* pcur = pHead;
        while (pcur->pNext) pcur = pcur->pNext;
        TraversedCircle = new TCircle;
        TraversedCircle->loadSpriteSheet("../resources/Circle.png", gRenderer);
        TraversedCircle->setCurrentPosition(xPos, (SCREEN_HEIGHT - NODE_HEIGHT) - 100);
        TraversedCircle->setPosition(pcur->getPosition().x, yPos);
        TraversedCircle->setPHead(pHead);
    }
    else {
        delete TraversedCircle;
        TraversedCircle = NULL;
    }
}

void SinglyLinkedList::SBSLoad(std::string path, SDL_Renderer* gRenderer) {
    std::ifstream fin(path.c_str());
    if (!fin.is_open()) {
        std::cout << "can't open input file " << std::endl;
        exit(0);
    }
    removeAll();
    std::string n;
    while (fin >> n)
        while (!SBSInsertTail(n, gRenderer)) {
            for (int i=0; i<200; ++i) {
            render(gRenderer);
            SDL_RenderPresent(gRenderer);

            }
        }

    fin.close();
}

void SinglyLinkedList::SBSFind(std::string n, SDL_Renderer* gRenderer) {
    if (!StepByStepCircle) {
        TurnOnSBSCircle(gRenderer);
        return;
    }
    if (!StepByStepCircle->pcur && pHead) {
        reset();
        delete StepByStepCircle;
        StepByStepCircle = NULL;
        return;
    }
    if (pHead) {
        if (StepByStepCircle->pcur->item == n) {
            if (StepByStepCircle->pcur->getCurrentSprite() == NODE_SPRITE_MARK) {
                StepByStepCircle->pcur = StepByStepCircle->pcur->pNext;
                StepByStepCircle->setCurrentSprite() = YELLOW_CIRLCE;
            }
            else if (StepByStepCircle->getCurrentSprite() == YELLOW_CIRLCE)
                StepByStepCircle->setCurrentSprite() = RED_CIRCLE;
            else if (StepByStepCircle->getCurrentSprite() == RED_CIRCLE)
                StepByStepCircle->pcur->setCurrentSprite() = NODE_SPRITE_MARK;
        }
        else
            StepByStepCircle->pcur = StepByStepCircle->pcur->pNext;
        if (StepByStepCircle->pcur)
            StepByStepCircle->setPosition(StepByStepCircle->pcur->getPosition().x, StepByStepCircle->pcur->getPosition().y);
    }
    else {
        if (StepByStepCircle->getCurrentSprite() == YELLOW_CIRLCE) {
            StepByStepCircle->setCurrentSprite() = RED_CIRCLE;
        }
        else {
            delete StepByStepCircle;
            StepByStepCircle = NULL;
            return;
        }
    }
}

void SinglyLinkedList::SBSInsertBefore(std::string n, SDL_Renderer* gRenderer) {
    if (!StepByStepCircle) {
        TurnOnSBSCircle(gRenderer);
        return;
    }
    if (pHead && pHead->isUsed()) {
        SBSInsertHead(n, gRenderer);
        return;
    }

    if (!StepByStepCircle->pcur) {
        delete StepByStepCircle;
        StepByStepCircle = NULL;
        return;
    }
    if (pHead) {
        if (StepByStepCircle->getCurrentSprite() == RED_CIRCLE) {
            Node* ptemp = new Node;
            ptemp->item = n;
            ptemp->loadNode(n, StepByStepCircle->pcur->getPosition().x +NODE_WIDTH, yPos, gRenderer, true);
            ptemp->pNext = StepByStepCircle->pcur->pNext;
            StepByStepCircle->pcur->pNext = ptemp;
            delete StepByStepCircle;
            StepByStepCircle = NULL;
        }
        else if (StepByStepCircle->pcur->pNext && StepByStepCircle->pcur->pNext->isUsed()) {
            StepByStepCircle->setCurrentSprite() = RED_CIRCLE;
            move(StepByStepCircle->pcur->pNext, NODE_WIDTH, 0);
            StepByStepCircle->pcur->pNext->setUsedBackToFalse();
        }
        else {
            StepByStepCircle->pcur = StepByStepCircle->pcur->pNext;
            if (StepByStepCircle->pcur)
                StepByStepCircle->setPosition(StepByStepCircle->pcur->getPosition().x, StepByStepCircle->pcur->getPosition().y);
        }
    }
    else {
        if (StepByStepCircle->getCurrentSprite() == YELLOW_CIRLCE) {
            StepByStepCircle->setCurrentSprite() = RED_CIRCLE;
        }
        else {
            delete StepByStepCircle;
            StepByStepCircle = NULL;
            return;
        }
    }
}

void SinglyLinkedList::SBSInsertHead(std::string n, SDL_Renderer* gRenderer) {
    if (!StepByStepCircle) {
        TurnOnSBSCircle(gRenderer);
        return;
    }

    if (pHead) {
        if (StepByStepCircle->getCurrentSprite() == RED_CIRCLE) {
            delete StepByStepCircle;
            StepByStepCircle = NULL;
            return;
        }
        delete StepByStepCircle;
        StepByStepCircle = NULL;
    }
    else
            StepByStepCircle->setCurrentSprite() = RED_CIRCLE;

    move(pHead, NODE_WIDTH, 0);
    Node* ptemp = new Node;
    ptemp->item = n;
    ptemp->loadNode(n, xPos, yPos, gRenderer, true);
    ptemp->pNext = pHead;
    pHead = ptemp;
}

bool SinglyLinkedList::SBSInsertTail(std::string n, SDL_Renderer* gRenderer) {
    if (!StepByStepCircle) {
        TurnOnSBSCircle(gRenderer);
        return false;
    }
    if (pHead) {
        if (!StepByStepCircle->pcur->pNext) {
            if (StepByStepCircle->getCurrentSprite() == RED_CIRCLE) {
                StepByStepCircle->pcur->pNext = new Node;
                StepByStepCircle->pcur->pNext->item = n;
                StepByStepCircle->pcur->pNext->pNext = NULL;
                StepByStepCircle->pcur->pNext->loadNode(n, StepByStepCircle->pcur->getPosition().x + NODE_WIDTH, yPos, gRenderer, true);
                delete StepByStepCircle;
                StepByStepCircle = NULL;
                return true;
            }
            else {
                StepByStepCircle->setCurrentSprite() = RED_CIRCLE;
            }
        }
        else {
            StepByStepCircle->setPosition(StepByStepCircle->pcur->getPosition().x + NODE_WIDTH, StepByStepCircle->pcur->getPosition().y);
            StepByStepCircle->pcur = StepByStepCircle->pcur->pNext;
        }
    }
    else {
        if (StepByStepCircle->getCurrentSprite() == RED_CIRCLE) {
            pHead = new Node;
            pHead->item = n;
            pHead->pNext = NULL;
            pHead->loadNode(n, xPos, yPos, gRenderer, true);
            delete StepByStepCircle;
            StepByStepCircle = NULL;
            return true;
        }
        else
            StepByStepCircle->setCurrentSprite() = RED_CIRCLE;
    }
    return false;
}

void SinglyLinkedList::SBSRandom(SDL_Renderer* gRenderer) {
    int b = rand() % 9999 + 1;
    std::string c = std::to_string(b);
    SBSInsertTail(c, gRenderer);
}

void SinglyLinkedList::removeTail() {
    Node* pcur = pHead;
    if (!pcur) {
        return;
    }

    if (!pcur->pNext) {
        delete pHead;
        pHead = NULL;
        return;
    }

    while (pcur->pNext->pNext) pcur = pcur->pNext;

    if (hasTraversedCircle(pcur->pNext->getPosition().x, pcur->pNext->getPosition().y)) {
        delete TraversedCircle;
        TraversedCircle = NULL;
    }
    if (hasSBSCircle(pcur->pNext->getPosition().x, pcur->pNext->getPosition().y)) {
        delete StepByStepCircle;
        StepByStepCircle = NULL;
    }
    delete pcur->pNext;
    pcur->pNext = NULL;
}

void SinglyLinkedList::removeAll() {
    Node* pcur = pHead;
    while (pcur) {
        Node* ptemp = pcur;
        delete ptemp;
        pcur = pcur->pNext;
    }
    if (TraversedCircle) {
        delete TraversedCircle;
        TraversedCircle = NULL;
    }
    if (StepByStepCircle) {
        delete StepByStepCircle;
        StepByStepCircle = NULL;
    }
    pHead = NULL;
}
