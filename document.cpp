#include"document.h"
document::document(const std::string &filename) : filename(filename) {
    readFromFile();
}

document::~document() {
   
}

void document::readFromFile() {
    std::ifstream Infile(filename);
    if (Infile.is_open()) {
        std::string line;
        // int maxColum = view_ ->GetColNumInView();
        bool isempty = true;
        while (std::getline(Infile, line)) {
            isempty = false;
            // size_t startPos = 0;
            // while(line.length() > maxColum){
            //     std::string subStr = line.substr(startPos, maxColum);
            //     line.erase(0, maxColum);
            //     text.push_back(subStr);
            //     startPos += maxColum;
            //     Iswrappedtext = true;
            // }
            text.push_back(line);
        }
        if(isempty){
            text.push_back("");
        }
        Infile.close();
    }
}

void document::writeToFile() {
    std::ofstream Outfile(filename);
    if (Outfile.is_open()) {
        for (int i = 0; i < text.size(); i++) {
            Outfile << text[i] << std::endl;
        }
        Outfile.close();
    }
}









