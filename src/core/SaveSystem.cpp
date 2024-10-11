#include "SaveSystem.h"
#include <fstream>

using namespace std;



void SaveSystem::saveData(int data) {
   
    
    
    ofstream fout;
    
    fout.open("savedata.txt");

    fout << data << endl;
    
    fout.close();

}



int SaveSystem::loadData() {
    return 0;
}
