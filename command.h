# ifndef command_h 
# define command_h
#include "ECTextViewImp.h"
#include "document.h"
#include <vector>
#include <string>
class Command {
public:
    virtual ~Command() {} 
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
    
};

class commandHistroy{
public:
     commandHistroy();
     virtual ~commandHistroy();
     bool Undo();
     bool Redo();
     void ExecuteCommand(Command *command);
     int currentCommand = -1;
     std::vector<Command *> Command_List;
    
    
    
};

class NewLine: public Command{
public: 
NewLine(ECTextViewImp &view, document &doc) : view(&view),doc(&doc) {}
void Execute();
void UnExecute();
private:
ECTextViewImp* view;
document* doc;
std::string removeStr;
int positionX;
int positionY;
int excuted = 0;
};

class Insert: public Command{
public: 
Insert(ECTextViewImp &view, document &doc,char charcter) : view(&view),doc(&doc),charcter(charcter) {}
void Execute();
void UnExecute();
private:
ECTextViewImp* view;
document* doc;
char charcter;
int positionX;
int positionY;
int excuted = 0;

};

class Remove: public Command{
public: 
Remove(ECTextViewImp &view, document &doc) : view(&view),doc(&doc) {}
void Execute();
void UnExecute();
private:
ECTextViewImp* view;
document* doc;

private:
int removedCharX;
int removedCharY;
char removedChar;
};




#endif /* command_h */