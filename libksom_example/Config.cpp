#include "config.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

Config::Config(char* filename) {
    ifstream cfg(filename);
    string line, k, v;
    size_t eqPos;
    
    if (!cfg)
        return;

    do {
        cfg >> line;
        eqPos = line.find_first_of('=');
        if (eqPos == string::npos)
            break;
        k = line.substr(0, eqPos);               
        v = line.substr(eqPos+1, string::npos);
        args[k] = v;
    } while (!cfg.eof());

    cfg.close();
}

Config::~Config() {    
}

int Config::getIntOption(string k) {
    return atoi(args[k].c_str());
}

double Config::getDoubleOption(string k) {
    return atof(args[k].c_str());
}