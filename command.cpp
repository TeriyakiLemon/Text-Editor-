#include "command.h"


commandHistroy::commandHistroy() : currentCommand(-1) {}

commandHistroy::~commandHistroy() {
   for (unsigned int i = 0; i < Command_List.size(); i++) {
       delete Command_List[i];
   }
   Command_List.clear();
   currentCommand = -1;
    
}

bool commandHistroy::Undo() {
    if (currentCommand < 0) {
        return false;
    }
    Command_List[currentCommand]-> UnExecute();
    currentCommand--;
    return true;
}

bool commandHistroy::Redo() {
    if (currentCommand >= (int)Command_List.size() - 1) {
        return false;
    }
    currentCommand++;
    Command_List[currentCommand]->Execute();
    return true;
}

void commandHistroy::ExecuteCommand(Command *command) {
    
    command->Execute();
    if( currentCommand >= -1 )
    {
        for(int i=currentCommand+1; i<Command_List.size(); ++i)
        {
            delete Command_List.back();
                Command_List.pop_back();
        }
    }
    Command_List.push_back(command);
    ++currentCommand;
  
}

void NewLine::Execute() {

   if(doc -> text.empty()){
       doc -> text.push_back("");
       return;
    }
   if(excuted == 0){
       positionX = view -> GetCursorX();
       positionY = view -> GetCursorY();
       excuted = 1;
      
}
    
    removeStr = "";
    if(positionX == static_cast<int>(doc -> text[positionY].size())){
        doc -> text.insert( doc -> text.begin() + positionY + 1, "" );
        view -> SetCursorX(0);
        view -> SetCursorY(positionY + 1);
    }
    else{
        std::string move_char = doc->text[positionY].substr(positionX, doc->text[positionY].size() );
        removeStr = move_char;
        doc->text[positionY].erase(positionX, doc->text[positionY].size());

        if (static_cast<int>(doc->text.size()) < positionY + 1) {
        doc->text.resize(positionY + 1);
    }

    doc->text.insert(doc->text.begin() +positionY + 1, std::move(move_char));
    view->SetCursorY(positionY + 1);
    view->SetCursorX(0);
    }
// if(view -> GetCursorY() >= int (doc->text.size())){
//     return;
// }
// if (view -> GetCursorX() >= int(doc -> text[view -> GetCursorY()].length())){
//     doc -> text.insert( doc -> text.begin() + view -> GetCursorY() + 1, "" );
//     view -> SetCursorX(0);
//     view -> SetCursorY(view -> GetCursorY() + 1);
// }
// else{
//     std::string temp = doc -> text[view -> GetCursorY()].substr(view -> GetCursorX());
//     doc -> text[view -> GetCursorY()].erase(view -> GetCursorX());
//     if(int(doc ->text.size())< view -> GetCursorY())
//     {
//         doc -> text.push_back("");
//     }
//     doc -> text.insert( doc -> text.begin() + view -> GetCursorY() + 1, temp );
//     view -> SetCursorX(0);
//     view -> SetCursorY(view -> GetCursorY() + 1);
// }

    
}

void NewLine::UnExecute() {

     doc -> text[positionY].insert(positionX, removeStr);
     doc -> text.erase(doc -> text.begin() + positionY + 1);
     view -> SetCursorX(positionX);
     view -> SetCursorY(positionY);

//     doc-> text[view->GetCursorX()].insert(view->GetCursorX(), doc->text[view->GetCursorY() - 1]);
//     doc->text.erase(doc->text.begin() + view->GetCursorY() - 1);
//     view->SetCursorY(view->GetCursorY() );
//     view->SetCursorX(view->GetCursorX());
    
//     if(view -> GetCursorX() ==0){
//       doc->text.erase(doc->text.begin() + view->GetCursorY());
//       view->SetCursorY(view->GetCursorY() - 1);
//     }
// else {
//         // Combine the text from the current line and the previous line
//         std::string temp = doc->text[view->GetCursorY()];
//         doc->text.erase(doc->text.begin() + view->GetCursorY());
//         view->SetCursorY(view->GetCursorY() - 1);
//         int prevLineLength = doc->text[view->GetCursorY()].length();
//         doc->text[view->GetCursorY()] += temp;
//         view->SetCursorX(prevLineLength);
//     }
}

void Insert:: Execute() {
    
  if(excuted == 0){
    positionX = view -> GetCursorX();
    positionY = view -> GetCursorY();
    
  }
   excuted = 1;
   int maxLineLength = view -> GetColNumInView();
   if (doc -> text.empty())
   {
       doc->text.push_back("");
   }
 if(positionY <static_cast<int> (doc->text.size())){
    if(positionX + 1 == maxLineLength){
        if(positionY + 1 == static_cast<int> (doc->text.size())){
            doc->text.push_back(std::string(1,charcter));
        }
        else{
            doc->text.insert( doc->text.begin() + positionY + 1, std::string(1,charcter));
        }

        positionX = 0;
        positionY += 1;
        view -> SetCursorX(0);
        view -> SetCursorY(positionY + 1);

    }
    else {
        doc ->  text[positionY].insert(positionX, 1, charcter);
        view-> SetCursorX(positionX + 1);
    }
 }

   
   
//    int x = view->GetCursorX();
//    int y = view->GetCursorY();
//    if(y <= int(doc->text.size()))
//    {
//       if (x > int(doc->text[y].size()) ){
//              doc->text[y].resize(x);
//       }
//         doc->text[y].insert(x, 1, ch);
//        view->SetCursorX(x + 1);
//    }
//    else{
//     doc->text.push_back(std::string(1, ch));
//    }
}

void Insert:: UnExecute() {
    if(doc -> text[positionY].size()>0){
        doc -> text[positionY].erase(positionX, 1);
        view -> SetCursorX(positionX);
    }
    else{
        if(!doc -> text.empty()){
            doc -> text.pop_back();
        }
    }
  
    // int x = view->GetCursorX() - 1; // We need to subtract 1 since the cursor was moved after insertion
    // int y = view->GetCursorY();

    // if (y < int(doc->text.size())) {
    //     doc->text[y].erase(x, 1);
    //     view->SetCursorX(x);
    // } else {
    //     // This case handles if the text was added to a new line at the end of the document
    //     if (!doc->text.empty()) {
    //         doc->text.pop_back();
    //     }
    // }
}

void Remove:: Execute() {
    if (view ->GetCursorX() > 0){
        removedCharX = view->GetCursorX() - 1;
        removedCharY = view->GetCursorY();
        removedChar = doc->text[removedCharY][removedCharX];
        doc -> text[view -> GetCursorY()].erase(doc -> text[view -> GetCursorY()].begin() + view -> GetCursorX() - 1);
        view -> SetCursorX(view -> GetCursorX() - 1);
    }
}

void Remove:: UnExecute() {
     if (removedCharX >= 0) {
        doc->text[removedCharY].insert(removedCharY, 1, removedChar);
        view->SetCursorX(removedCharX + 1);
}
}