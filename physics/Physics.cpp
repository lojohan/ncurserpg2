#include "Physics.h"

// should be rewritten so that all moves are performed first, then move things
// back, then perform onCollision;
void physicsLoop(int ch, std::vector<Entity*> entityList, int t) {

    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        int collision = 0;
        Entity * collidee[1024];
        
        int arr[2];
        arr[0] = (*it)->getX();
        arr[1] = (*it)->getY();
        
        (*it)->getNextMove(ch, arr, t);
        
        for(std::vector<Entity*>::iterator it2 = entityList.begin(); it2 != entityList.end(); ++it2) {
            if( *it == *it2 ) {
                continue;
            }
            if((*it)->getSolid() && (*it2)->getSolid() ) {
                if(arr[0] == (*it2)->getX() && arr[1] == (*it2)->getY()) {
                    collidee[collision++] = *it2;
                }  
           }
        }
        
        if(collision != 0) {
            for (int i = 0; i < collision; i++) {
                collidee[i]->onCollision( *it );
                //TODO: all onCollision calls now happen at least twice. fix
                (*it)->onCollision(collidee[i]);
                
            }
        } else {
            (*it)->move(arr);
        }
    }
}
