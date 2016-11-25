#include "Physics.h"

#include "../game/Game.h"

size_t getEntitiesAtPoint(int x, int y, std::vector<Entity*> &result, std::unordered_map< std::string,std::vector<Entity*> >  &entityMap) {
	std::stringstream s;
	s << x << "," << y;
	std::string coords = s.str();
	if(entityMap.find(coords) != entityMap.end()) {
		std::vector<Entity*> collidees = entityMap.find(coords)->second;
		// copy the pointers to the end of the output list.
		
		result.insert(result.end(), collidees.begin(), collidees.end());
		return collidees.size();
	} else {
		return 0;
	}
}

// should be rewritten so that all moves are performed first, then move things
// back, then perform onCollision;
void physicsLoop(Input input, std::vector<Entity*> entityList, std::unordered_map< std::string,std::vector<Entity*> >  &entityMap, long t) {

	std::vector<Entity*> entitiesOnPosition;
	std::vector<Entity*> collidees;

    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        
    	int origX = (*it)->getX();
    	int origY = (*it)->getY();

        int arr[2];
        arr[0] = (*it)->getX();
        arr[1] = (*it)->getY();
        
        (*it)->getNextMove(input, arr, t);
        
        if(arr[0] == origX && arr[1] == origY)
            continue;
        
        bool entityDisappeared = false;
        bool collidedWithSolid = false;

        collidees.clear();
        if(getEntitiesAtPoint(arr[0], arr[1], collidees, entityMap) > 0) {
            for (size_t i = 0; i < collidees.size(); i++) {
                if (collidees[i]->getSolid())
                    collidedWithSolid = true;
                    
                collidees[i]->onCollision( *it );
                //TODO: all onCollision calls now happen at least twice. fix
                (*it)->onCollision(collidees[i]);
                
                // check that *it is still there, otherwise break the loop.
                entitiesOnPosition.clear();
                entityDisappeared = true;
                if (getEntitiesAtPoint(origX, origY, entitiesOnPosition, entityMap) > 0) {
                	for (size_t j = 0; j < entitiesOnPosition.size(); j++) {
                		if (entitiesOnPosition[j] == *it) {
                			entityDisappeared = false;
                			break;
                		}
                	}
                }
                if (entityDisappeared) {
                    // The entity is gone (died, teleported...?).
                    break;
                }
            }
        } 
        if (!collidedWithSolid && !entityDisappeared) {
            
            game->removeEntityFromMap(entityMap, *it);
            
            (*it)->move(arr);
            
            game->addEntityToMap(entityMap, *it);
        }
    }
}
