#ifndef DocumentController_h
#define DocumentController_h
#include"ECObserver.h"
#include"document.h"
#include"ECTextViewImp.h"
#include"command.h"
#include<sstream>
#include<set>
enum EditorMode{
    COMMAND_MODE,
    EDIT_MODE
};

class DocumentController : public ECObserver
{
public:
    DocumentController(document *doc, ECTextViewImp *view) : doc_(doc), view_(view){}
    ~DocumentController(){
    }
    void Update() ;
    void insert();
    void remove();
    void moveUp();
    void moveLeft();
    void moveRight();
    void moveDown();
    void enterNewline();
    void highlightKeywords();
    void UndoActivity();
    void RedoActivity();
    
    


   
private:
   document *doc_;
   ECTextViewImp *view_;
   commandHistroy histCmds;
   EditorMode currentmode = COMMAND_MODE;
   int modeSwitch = 0;
   


};




#endif /* DocumentController_h */