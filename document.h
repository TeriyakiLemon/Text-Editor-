#ifndef document_h
#define document_h
#include"ECTextViewImp.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

class document {
public:
    document(const std::string &filename);
    ~document();
    void readFromFile();
    void writeToFile();
    
    
 ECTextViewImp *view_;
 //bool  Iswrappedtext = false;
 std::vector<std::string> text;
 std::string filename;


 
 
};

#endif /* document_h */