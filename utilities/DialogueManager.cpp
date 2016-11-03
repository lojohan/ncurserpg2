

#include "DialogueManager.h"

#include <boost/regex.hpp>

static bool loaded = false;

static std::map<int,std::string*> dialogueMap;

static boost::regex expr("^(\\d+):$");

static void loadDialogues() {
    if (!loaded) {
        loaded = true;
        
        // load...
        std::string * dialogueItem;
        std::string line;
        std::ifstream myfile ("res/Dialogues.txt");
        myfile.imbue(std::locale("en_US.UTF8"));
        if (myfile.is_open())
        {
            while ( std::getline (myfile,line) )
            {
                boost::smatch matches;
                if (boost::regex_search(line, matches, expr)) {
                    int id = atoi( ((std::string)matches[1]).c_str() );
                    dialogueMap[id] = dialogueItem = new std::string();
                    
                } else {
                    dialogueItem->append(line+"\n");
                }
            }
        }
        myfile.close();
    }
}

std::string DialogueManager::getDialogue(int id){
    loadDialogues();
    return *dialogueMap[id];
}

