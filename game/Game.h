#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../map/Map.h"
#include "../physics/Physics.h"

class Game {
    private: 
        std::vector<Entity*> entityList;
        Map map;
        Player * player;
        
        // should be in drawing bit
        WINDOW *super_window;
        
        WINDOW *game_box;
        WINDOW *game_window;
        
        WINDOW *gui1_window;
        
        WINDOW *gui2_window;
        
        const static int GAME_HEIGHT = 15;
        const static int GAME_WIDTH = 30;
        
        const static int GUI1_HEIGHT = 15;
        const static int GUI1_WIDTH = 30;
        
        const static int GUI2_HEIGHT = 5;
        const static int GUI2_WIDTH = 62;
        
        const static int START_X = 0;
        const static int START_Y = 0;

    public:
        Game();
        
        void fillTileMap();
        
        
        void init();
        
        // closes all windows on close.
        void end();
        
        // run logic for movables
        void updateMovables(int ch);
        
        // inits things related to ncurses (graphics)
        void initNCurses();
        
        // creates windows and boxes.
        void createWindows();
        
        // separate this drawing bit here
        void clearBeforeDraw(WINDOW * win, int startX, int startY, int heigt, int width);
        void drawEntities();
        void drawGUI1Elements();
        void drawGUI2Elements();
        void draw();
        void refreshGameScreen();
        void refreshGUI1();
        void refreshGUI2();
             
};

#endif
