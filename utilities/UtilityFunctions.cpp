#include "UtilityFunctions.h"

void clearScreen() {
    printf(0,0,"\033c");
}

int kbhit(int t1,int t2) {
  struct timeval        timeout;
  fd_set                readfds;
  int                   how;

  /* look only at stdin (fd = 0) */
  FD_ZERO(&readfds);
  FD_SET(0, &readfds);

  /* poll: return immediately */
  timeout.tv_sec = t1;
  timeout.tv_usec = t2;

  how = select(1, &readfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
  /* Change "&timeout" above to "(struct timeval *)0"       ^^^^^^^^
   * if you want to wait until a key is hit
   */

  if ((how > 0) && FD_ISSET(0, &readfds))
    return 1;
  else
    return 0;
  
}

int playerInput(WINDOW *menu_win) {
    nodelay(stdscr, TRUE);
    if(kbhit(1,0)) {
        return wgetch(menu_win);    
    } else {
        return -1;
    }
}

void relativeCameraPos(Entity * centerentity, Entity * drawEntity, int arr[2], int height, int width) {
    arr[0] = height/2 + centerentity->getX() - drawEntity->getX();
    arr[1] = width/2 + centerentity->getY() - drawEntity->getY();
}

void gameLoopInputHandler(int ch, bool *game_paused) {
    switch(ch)
    {	case KEY_BACKSPACE:
            *game_paused = !(*game_paused);
		break;
	default:
		break;
    }
}

void splitString(std::string str_to_split, std::vector< std::string > * splits, char delimiter) {
    int prevsplit = 0;
    
    for(int i = 0; i < str_to_split.length(); i++) {
        char c = str_to_split[i];
        if(c == delimiter) {
            (*splits).push_back( str_to_split.substr(prevsplit,i-prevsplit) );
            prevsplit = i+1;
        } else if (i == str_to_split.length() -1 ) {
            (*splits).push_back( str_to_split.substr(prevsplit,i-prevsplit+1) );
        }
    }
}


