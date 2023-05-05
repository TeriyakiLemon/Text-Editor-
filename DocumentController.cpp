#include "DocumentController.h"

void DocumentController::Update() {
    int command = view_->GetPressedKey();

    //Handle mode change
    
    switch(command) {
        case ARROW_UP:
            moveUp();
            break;
        case ARROW_LEFT:
            moveLeft();
            break;
        case ARROW_RIGHT:
            moveRight();
            break;
        case ARROW_DOWN:
            moveDown();
            break;
        case ENTER:
            enterNewline();
            break;
        case CTRL_Z:
            UndoActivity();
            break;
        case CTRL_Y:
            RedoActivity();
            break;
        default:
          if(currentmode == EDIT_MODE){
            if(command >= 32 && command <= 126){
                insert();
                }
            else if(command == BACKSPACE){
                remove();
            }
          }
            break;
            
    }
    if(command == 105) {
        currentmode = EDIT_MODE;
        view_ -> ClearStatusRows();
        view_ -> AddStatusRow("Edit Mode", "", true);
        modeSwitch = histCmds.currentCommand;
       
        
    }
    else if(command == 27 || command == 1) {
        currentmode = COMMAND_MODE;
        view_ -> ClearStatusRows();
        view_ -> AddStatusRow("Command Mode", "", true);
        
    }
    view_->InitRows();
    int i = 1;
    for(auto x : doc_->text)
    {   
        view_->AddRow(x);
        if(view_ -> GetRowNumInView() == i){
            break;
        }
       i++;
        
    }

    
     highlightKeywords();
     doc_->writeToFile();

    
}

void DocumentController::insert() {
    Insert *newinsert = new Insert(*view_, *doc_, view_->GetPressedKey());
    histCmds.ExecuteCommand(newinsert);
}

void DocumentController::remove() {
   if(view_->GetCursorX() !=0) {
     doc_ -> text[view_ -> GetCursorY()].erase(doc_ -> text[view_ -> GetCursorY()].begin() + view_ -> GetCursorX() - 1); 
     view_ -> SetCursorX(view_ -> GetCursorX() - 1);   
   }
   else if(view_->GetCursorX() == 0 && view_->GetCursorY() != 0) {
       int x = doc_->text[view_->GetCursorY()-1].length();
       doc_->text[view_->GetCursorY()-1] += doc_->text[view_->GetCursorY()];
       doc_->text.erase(doc_->text.begin() + view_->GetCursorY());
       view_->SetCursorX(x);
       view_->SetCursorY(view_->GetCursorY()-1);
   }
   else if(view_->GetCursorX() == 0 && view_->GetCursorY() == 0) {
       return;
   }
   
}

void DocumentController::moveUp() {
if (int (doc_ -> text [view_ -> GetCursorY()].length()) >= view_ ->GetCursorX()){
        view_ -> SetCursorY(view_ -> GetCursorY() - 1);
    }
    else if (int (doc_ -> text [view_ -> GetCursorY()].length()) < view_ ->GetCursorX()){
        view_ -> SetCursorY(view_ -> GetCursorY() - 1);
        view_ -> SetCursorX(int (doc_ -> text [view_ -> GetCursorY()].length()));
    }
    else if (view_ -> GetCursorY() == 0){
        return;
    }
    else{
        return;
    }
    
}

void DocumentController::moveLeft() {
    if (view_ -> GetCursorX() > 0){
        view_ -> SetCursorX(view_ -> GetCursorX() - 1);
    }
    else if ( view_ -> GetCursorY() > 0){
        view_ -> SetCursorY(view_ -> GetCursorY() - 1);
        view_ -> SetCursorX(doc_ -> text[view_ -> GetCursorY()].length());
    }
    else if (view_ -> GetCursorX() == 0 && view_ -> GetCursorY() == 0){
        return;
    }
   
    else{
        return;
    }
    
}

void DocumentController::moveRight() {
    if (view_ -> GetCursorX() < int(doc_ -> text[view_ -> GetCursorY()].length())){
        view_ -> SetCursorX(view_ -> GetCursorX() + 1);
    }
    else if (view_ -> GetCursorY() == int(doc_ -> text[view_ -> GetCursorY()].length()) && view_ -> GetCursorY() < int(doc_ -> text.size()) - 1){
        view_ -> SetCursorY(view_ -> GetCursorY() + 1);
        view_ -> SetCursorX(0);
    }
   



}

void DocumentController::moveDown() {
    if (int (doc_->text[view_ -> GetCursorY()].length()) >= view_ -> GetCursorX()){
        view_ -> SetCursorY(view_ -> GetCursorY() + 1);
    }
    else if (int (doc_ -> text.size()) > view_ -> GetCursorX()){
        view_ -> SetCursorY(view_ -> GetCursorY() + 1);
        view_ -> SetCursorX(int (doc_->text[view_ -> GetCursorY()].length()));
    }
    else if (view_ -> GetCursorY() == int(doc_ -> text.size()) - 1){
        return;
    }
    // else if(doc_ -> Iswrappedtext == true){
    //        while (view_ -> GetCursorY() < static_cast<int>(view_ -> GetRowNumInView()) - 1){
    //         view_ -> SetCursorY(view_ -> GetCursorY() + 1);
    //        if(doc_ ->Iswrappedtext == false){
    //           break;
    //        }
            
    // }
    // }
    else{
        return;
    }
}
    

   

void DocumentController::enterNewline() {
    NewLine *newline = new NewLine(*view_, *doc_);
    histCmds.ExecuteCommand(newline);
}

void DocumentController::highlightKeywords() {
    std::set<std::string> keywords;
    std::ifstream file("keywords.txt");
    std::string keyword;
    while (std::getline(file, keyword)) {
        keywords.insert(keyword);
    }

    for (int row = 0; row < int(doc_->text.size()); ++row) {
        std::string line = doc_->text[row];
        int colBegin = 0;
        int colEnd = 0;
        std::istringstream iss(line);
        std::string word;
        while(iss >> word) {
            colEnd = colBegin + word.size();
            if( keywords.count(word) > 0){
                view_->SetColor(row, colBegin, colEnd - 1, TEXT_COLOR_BLUE);
            }
            colBegin = colEnd + 1;
        }
 
    }

}

void DocumentController::UndoActivity(){
    if(currentmode != COMMAND_MODE){
        return;
    }
    if(histCmds.currentCommand >= 0){
        while(histCmds.currentCommand >= modeSwitch + 1){
            histCmds.Undo();
        }
    }
    else{
           histCmds.Undo();
    }
}

void DocumentController::RedoActivity(){
    if (currentmode != COMMAND_MODE){
        return;
    }
    while( histCmds.Redo()){}
    // if(histCmds.currentCommand < int(histCmds.Command_List.size()) - 1){
    //     while(histCmds.currentCommand < modeSwitch){
    //         histCmds.Redo();
    //     }
    // }
    // else{
    //     histCmds.Redo();
    // }
    
}






