

#include "DialogueManager.h"

#include <boost/regex.hpp>

static bool loaded = false;

static std::map<int,std::string*> dialogueMap;

static std::map<int,std::string*> randomDialogueMap;

static boost::regex expr("^(\\d+):$");

static void loadDialogueFile(const char * fname, std::map<int,std::string*> &map) {
    std::string * dialogueItem;
    std::string line;
    std::ifstream myfile (fname);
    myfile.imbue(std::locale("en_US.UTF8"));
    if (myfile.is_open())
    {
        while ( std::getline (myfile,line) )
        {
            boost::smatch matches;
            if (boost::regex_search(line, matches, expr)) {
                int id = atoi( ((std::string)matches[1]).c_str() );
                map[id] = dialogueItem = new std::string();
                
            } else {
                dialogueItem->append(line+"\n");
            }
        }
    }
    myfile.close();
}

static void loadDialogues() {
    if (!loaded) {
        loaded = true;
        
        // load...
        loadDialogueFile("res/Dialogues.txt", dialogueMap);
        loadDialogueFile("res/RandomDialogues.txt", randomDialogueMap);
    }
}

std::string DialogueManager::getRandomDialogue() {
    loadDialogues();
    return *randomDialogueMap[1 + ( rand() % randomDialogueMap.size() )];
}

std::string DialogueManager::getDialogue(int id){
    loadDialogues();
    return *dialogueMap[id];
}

