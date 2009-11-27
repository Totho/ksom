/* 
 * File:   config.h
 * Author: John
 *
 * Created on November 22, 2009, 9:53 PM
 */

#ifndef _CONFIG_H
#define	_CONFIG_H

#include <string>
#include <map>

using std::string;
using std::map;

class Config {
public:
    Config(char* filename);
    ~Config();

    int getIntOption(string k);
    double getDoubleOption(string k);
private:
    map<string, string> args;
};

#endif	/* _CONFIG_H */

