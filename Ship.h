#include <iostream>
#include <string.h>
using namespace std;
#ifndef SHIP_H_
#define SHIP_H_
class Ship{
private:
    //location where the ship starts
    string main_patch_loc;
    string ship_direction;
    int size;
    bool sunked=false;

public:
    Ship(){
    }
    Ship(string main_loc, string direction,int size){
        this->main_patch_loc=main_loc;
        this->ship_direction=direction;
        this->size=size;
    }
    string Ship_mainloc_getter(){
        return this->main_patch_loc;
    }
    string Ship_dir_getter(){
        return this->ship_direction;
    }
    int Ship_size_getter(){
        return this->size;
    }
    bool sunk_getter(){
        return this->sunked;
    }
    void sunk_setter(bool sunk){
        this->sunked=sunk;
    }
};
#endif /*SHIP_H_*/