#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <ostream>

class Character {

    protected:
        std::string name;
        int maxHp;
        int currentHp;
        

    public:
    
        Character(std::string name, int maxHp);
        
        std::string getName();
        int getMaxHp();
        int getCurrentHp();
        
        void setName(std::string name);
        void setMaxHp(int maxHp);
        void takeDamage(int dHp);
        void setCurrentHp(int currentHp);
        
        bool isDead();
};

std::ostream& operator<<(std::ostream &strm, Character &c);

#endif
