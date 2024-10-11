#include "SaveSystem.h"
#include <fstream>




void SaveSystem::saveData(int data) {
   
    
    
    ofstream fout;
    
    fout.open("savedata.txt");

    fout << data << endl;
    
    fout.close();

}



int SaveSystem::loadData() {
    std::ifstream fin;
    fin.open("savedata.txt");
    if (fin.good()) {
        std::string savedata;
        getline(fin, savedata);
        return std::stoi(savedata);
    }
    return 0;
}