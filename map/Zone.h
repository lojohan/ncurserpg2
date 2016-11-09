#ifndef ZONE_H
#define ZONE_H

#include <string>

class Zone {
    protected:
        std::string name;
        
    public:
        int x_upperleft;
        int y_upperleft;
        
        int x_lowerright;
        int y_lowerright;
        
        bool friendly;
        
        Zone(std::string name, int x_upperleft[2], int lowerright[2], bool friendly);
        
        std::string getName();
        void setName(std::string name);
};

#endif

