#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <ostream>
#include <vector>
#include "../../utilities/typedefs.h"

class Character {

    protected:
        std::string name;
        int maxHp;
        int currentHp;
        std::vector<std::string> attackOptionsNames;
        std::vector<AttackFnPtr> attackOptionsFns;
        

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

        const std::vector<std::string> getAttackOptionsNames();
        const std::vector<AttackFnPtr> getAttackOptionsFns();
};

std::ostream& operator<<(std::ostream &strm, Character &c);

#endif
