#include "Physics.h"

#include "../game/Game.h"


// should be rewritten so that all moves are performed first, then move things
// back, then perform onCollision;
void physicsLoop(int ch, std::vector<Entity*> entityList, std::unordered_map< std::string,std::vector<Entity*> >  & entityMap, int t) {

    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        
        int arr[2];
        arr[0] = (*it)->getX();
        arr[1] = (*it)->getY();
        
        (*it)->getNextMove(ch, arr, t);
        
        if(arr[0] == (*it)->getX() && arr[1] == (*it)->getY()) 
            continue;
        
        std::stringstream s;
        s << arr[0] << "," << arr[1];
        std::string newCoords = s.str();
        
        if(entityMap.find(newCoords) != entityMap.end()) {
            std::vector<Entity*> collidees = entityMap.find(newCoords)->second;
            
            
            for (size_t i = 0; i < collidees.size(); i++) {
                collidees[i]->onCollision( *it );
                //TODO: all onCollision calls now happen at least twice. fix
                (*it)->onCollision(collidees[i]);
                
            }
        } else {
            
            game->removeEntityFromMap(entityMap, *it);
            
            (*it)->move(arr);
            
            game->addEntityToMap(entityMap, *it);
            
            
        }
    }
}

