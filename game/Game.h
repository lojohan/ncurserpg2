#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../map/Map.h"
#include "../physics/Physics.h"

class Map;

class Game {
    private: 
        std::vector<Entity*> entityList;
        Map * map;
        Player * player;
        
        bool game_paused;

        // should be in drawing bit
        WINDOW *super_window;
        
        WINDOW *title_window;
        
        WINDOW *game_box;
        WINDOW *game_window;
        
        WINDOW *gui1_box;
        WINDOW *gui1_window;

        WINDOW *gui2_box;        
        WINDOW *gui2_window;
    
    public:
        const static int GAME_HEIGHT = 15;
        const static int GAME_WIDTH = 30;
        
        const static int GUI1_HEIGHT = 15;
        const static int GUI1_WIDTH = 30;
        
        const static int GUI2_HEIGHT = 5;
        const static int GUI2_WIDTH = 62;
        
        const static int TITLE_HEIGHT = 2;
        const static int TITLE_WIDTH = GUI2_WIDTH + 2;
        
        const static int START_X = 0;
        const static int START_Y = 0;
        
        const static int time_passed = 15;

    public:
        Game();
        
        void fillTileMap();
        Map * getMap();
        std::vector<Entity*> getEntities();
        
        void init();
        
        void start();
        
        // closes all windows on close.
        void end();
        
        void togglePause();
        
        // run logic for entities
        void updateMovables(int ch, int t);
        
        void getPlayerFromEntities(Player ** player);
        
        // inits things related to ncurses (graphics)
        void initNCurses();
        void initColors();
        
        // creates windows and boxes.
        void createWindows();
        
        // separate this drawing bit here
        void clearBeforeDraw(WINDOW * win, int startX, int startY, int height, int width);
        void clearGUI1();
        void clearGUI2();
        void clearGameWindow();
        void clearAll();
        
        void drawTitle();
        void drawEntities();
        void drawEntity(WINDOW * window, Entity * e, int x, int y);
        void drawGUI1Elements();
        void drawGUI2Elements();
        void drawPause();
        void draw();
        
        void refreshGameScreen();
        void refreshGUI1();
        void refreshGUI2();
        void refreshTitle();
        void refreshAll();
        
        WINDOW * getGameWindow();
        WINDOW * getGUI1Window();
        WINDOW * getGUI2Window();
             
};

// The Game pointer!
extern Game * game;

#endif
