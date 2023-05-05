// Test code for editor
#include "ECTextViewImp.h"
#include "ECObserver.h"
#include "document.h"
#include "command.h"
#include "DocumentController.h"
#include <sstream>

using namespace  std;


class ECfunction: public ECObserver{
 public:
 ECfunction(ECTextViewImp &p): Textview(&p) {}
 void Update(){
//   if(Textview->GetPressedKey() == 27 || Textview->GetPressedKey() == 1){
//            Textview-> Refresh();
//            Textview-> InitRows();
//            Textview-> AddRow("It is command mode now, press any key to continue");
           
//         }
  

    
 }
 ECTextViewImp *Textview;
 DocumentController *docController;
};  




int main(int argc, char *argv[])
{
    //
    if(argc < 2){
        cout << "Usage: " << argv[0] << " filename" << endl;
        return 1;
    }
    string filename = argv[1];
       
    ECTextViewImp wndTest;
    wndTest.AddRow("CSE 3150 Tianchen Zhang");
    wndTest.AddRow("This is a very simple demo of the ECTextViewImp functionalities.");
    wndTest.AddRow("Press any key to continue");
    wndTest.AddRow("Press ctrl-q to quit");

    // add a status bar
    wndTest.AddStatusRow("Editor  Command Mode", "For demo only", true);
    document *doc = new document(filename);
    DocumentController *controller = new DocumentController(doc, &wndTest);
    ECfunction *fun = new ECfunction(wndTest); 
    doc->text.push_back(" ");
    wndTest.Attach(controller);
    wndTest.Attach(fun);
    wndTest.Show();
    
    return 0;
}
