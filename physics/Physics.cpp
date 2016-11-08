#include "Physics.h"

void removeEntityFromMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, Entity* entity) {

    std::stringstream s;
    s << entity->getX() << "," << entity->getY();
    std::string newCoords = s.str();
    
    if(entityMap.find(newCoords) != entityMap.end()) {
        std::vector<Entity*> * entities = &(entityMap.find(newCoords)->second);
        
        
        for (int i = 0; i < entities->size(); i++) {
            if (entities->at(i) == entity) {
                entities->erase(entities->begin() + i);
                if (entities->size() == 0) {
                    entityMap.erase(entityMap.find(newCoords));
                }
                break;
            }
        }
    }
}

void addEntityToMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, Entity* entity) {
    std::stringstream s;
    s << entity->getX() << "," << entity->getY();
    std::string pos = s.str();
    
    if(entityMap.find(pos) != entityMap.end()) {
        std::vector<Entity*> * entitiesAtPoint = &(entityMap.find(pos)->second);
        entitiesAtPoint->push_back(entity);
    } else {
        std::vector<Entity*> entitiesAtPoint;
        entitiesAtPoint.push_back(entity);
        entityMap.insert({pos,entitiesAtPoint}); 
    }

}

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
            
            
            for (int i = 0; i < collidees.size(); i++) {
                collidees[i]->onCollision( *it );
                //TODO: all onCollision calls now happen at least twice. fix
                (*it)->onCollision(collidees[i]);
                
            }
        } else {
            
            removeEntityFromMap(entityMap, *it);
            
            (*it)->move(arr);
            
            addEntityToMap(entityMap, *it);
            
            
        }
    }
}

