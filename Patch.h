#include <iostream>
#include <string.h>
using namespace std;
#ifndef PATCH_H_
#define PATCH_H_
class Patch{
private:
    const int height = 1;
    const int width = 1; 
    bool at_war_situation = false; 
    string val="---";
    string loc="";
public:
    Patch(){}
    void Loc_setter(string given_loc){
        this->loc=given_loc;
    }
    string Loc_getter(){
        return this->loc;
    }
    string Situation_getter(){
        return this->val;
    }
    void Situation_setter(string situation){
        this->val=situation;
    }
};
#endif /*PATCH_H_*/