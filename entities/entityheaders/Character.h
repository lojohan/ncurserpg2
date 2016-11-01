#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {

    protected:
        std::string name;
        int maxHp;
        int currentHp;
        

    public:
    
        Character(std::string name, int maxHp, int currentHp);
        
        std::string getName();
        int getMaxHp();
        int getCurrentHp();
        
        void setName(std::string name);
        void setMaxHp(int maxHp);
        void setCurrentHp(int currentHp);
        
        bool isDead();
};

#endif
