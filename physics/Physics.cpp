#include "Physics.h"


void physicsLoop(int ch, std::vector<Entity*> entityList) {

    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        int arr[2];
        arr[0] = (*it)->getX();
        arr[1] = (*it)->getY();
        
        (*it)->getNextMove(ch, arr);
        for(std::vector<Entity*>::iterator it2 = entityList.begin(); it2 != entityList.end(); ++it2) {
            if( *it == *it2 ) {
                continue;
            }
            if((*it)->getSolid() && (*it2)->getSolid() ) {
                if(arr[0] == (*it2)->getX() && arr[1] == (*it2)->getY()) {
                    arr[0] = (*it)->getX();
                    arr[1] = (*it)->getY();
                }  
           }
        }
        
        (*it)->move(arr);
    }
}
