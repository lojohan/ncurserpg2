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

bool isEntityGone(int x, int y, Entity * e, std::unordered_map< std::string,std::vector<Entity*> >  &entityMap) {
    std::vector<Entity*> entitiesOnPosition;
    if (getEntitiesAtPoint(x, y, entitiesOnPosition, entityMap) > 0) {
    	for (size_t j = 0; j < entitiesOnPosition.size(); j++) {
    		if (entitiesOnPosition[j] == e) {
    			return false;
    		}
    	}
    }
    return true;
}

// should be rewritten so that all moves are performed first, then move things
// back, then perform onCollision;
void physicsLoop(Input input, std::vector<Entity*> &entityList, std::unordered_map< std::string,std::vector<Entity*> >  &entityMap, long t) {


    std::vector<Entity*> gones;
    std::vector<Entity*> collidedWith;
	std::vector<Entity*> collidees;

    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        
        if (std::find(gones.begin(), gones.end(), *it) != gones.end()) {
            // the entity was gone'd in a previous collision. It may be dead (deallocated) or was just teleported... But we just skip its further collisions anyway.
            //LOG << "physicsLoop: Entity was gone'd, skipping " << std::endl;
            continue;
        }
        
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

        collidedWith.clear();
        while (!entityDisappeared) {
            
            Entity *other = NULL;
            collidees.clear();
            if(getEntitiesAtPoint(arr[0], arr[1], collidees, entityMap) > 0) {
                for (size_t i = 0; i < collidees.size() && !entityDisappeared; i++) {
                    if (std::find(collidedWith.begin(), collidedWith.end(), collidees[i]) != collidedWith.end()) {
                        continue;
                    } else {
                        other = collidees[i];
                    }
                }
            }
            if (other == NULL) {
                // we did the needful already.
                // we collided with everyone on the new position already.
                break;
            }
            
            collidedWith.push_back(other);
            
            if (other->getSolid())
                collidedWithSolid = true;
                
            //LOG << "physicsLoop: Collision detected! " << **it << " -> " << *other << std::endl;
            
            //LOG << "physicsLoop: 1st onCollision" << *other << " -> " << **it << std::endl;
            other->onCollision( *it );
            
            // check that *it is still there, otherwise break the loop.
            bool otherDisappeared = isEntityGone(arr[0], arr[1], other, entityMap);
            entityDisappeared = isEntityGone(origX, origY, *it, entityMap);
            if (otherDisappeared) {
                gones.push_back(other);
            }
            if (otherDisappeared || entityDisappeared) {
                // An entity is gone (died, teleported...?).
                if (otherDisappeared) LOG << "physicsLoop: otherDisappeared" << std::endl;
                if (entityDisappeared) LOG << "physicsLoop: entityDisappeared" << std::endl;
                continue;
            }
            
            
            //LOG << "physicsLoop: 2nd onCollision" << **it << "->" << *other << std::endl;
            
            (*it)->onCollision(other);
            
            otherDisappeared = isEntityGone(arr[0], arr[1], other, entityMap);
            entityDisappeared = isEntityGone(origX, origY, *it, entityMap);
            if (otherDisappeared) {
                gones.push_back(other);
            }
            if (otherDisappeared || entityDisappeared) {
                // An entity is gone (died, teleported...?).
                if (otherDisappeared) LOG << "physicsLoop: otherDisappeared" << std::endl;
                if (entityDisappeared) LOG << "physicsLoop: entityDisappeared" << std::endl;
                continue;
            }
        }
        //LOG << "physicsLoop: end for entity" << std::endl;
        if (!collidedWithSolid && !entityDisappeared) {
            //LOG << "physicsLoop: moving entity to new position "<< **it << std::endl;
            
            game->removeEntityFromMap(entityMap, *it);
            
            (*it)->move(arr);
            
            game->addEntityToMap(entityMap, *it);
            
            //LOG << "physicsLoop: moved entity to new position "<< **it << std::endl;
        }
        //LOG << "physicsLoop: end 4 realz for entity" << std::endl;
    }
    
    //LOG << "physicsLoop: end function" << std::endl;
}
