#include <iostream>
#include <string.h>
using namespace std;
#ifndef BOARD_H_
#define BOARD_H_
#include "Patch.h"
#include "Ship.h"

class Board{
private:
    const int rows = 10;
    const int columns = 10;
    //board of 10x10 patches/bombs
    Patch board_patches[10][10];
public:
    void Draw_board(){
        //this function draws the board and value of patches with the row and column labels as well
        //below for loop and arrays are used only to help users navigate through the board
        string board_letters[10]={"A","B","C","D","E","F","G","H","I","J"};
        string board_numbers[10]={"0","1","2","3","4","5","6","7","8","9"};
        cout<<"    ";
        for (int i = 0; i < 10; i++)
        {
            cout<<" "<<board_letters[i]<<" "<<"   ";
        }
        cout<<endl;
        //displaying the board, patches inside it and their values
        for (int i = 0; i < this->rows; i++)
        {
            cout<<i<<" | ";
            for (int j = 0; j < this->columns; j++)
            {
                this->board_patches[i][j].Loc_setter(board_letters[j]+board_numbers[i]);
                cout<< this->board_patches[i][j].Situation_getter()<<" | ";
            }
            cout<<endl;
        }
        
    }
    bool check_position(Ship given_ship){
        //this function checks if a position is suitable to put a ship. if so return true. if not, false.
        bool occupied=false;
        bool position_exists=false;
        //checking if the location is occupied for horizontal direction ships
        if (given_ship.Ship_dir_getter()=="H")
        {
            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->columns; j++){
                    if (this->board_patches[i][j].Loc_getter()==given_ship.Ship_mainloc_getter())
                    {
                        position_exists=true;
                        for (int z = 0; z <given_ship.Ship_size_getter(); z++)
                        {
                            if (this->board_patches[i][j+z].Situation_getter()!="---")
                            {
                                occupied=true;
                            }
                        }
                    }
                }
            }
            //return false if the location is occupied
            if (occupied==true)
            {
                return false;
            }
            else{
                //return true if position exists and is not occupied
                if (position_exists==true)
                {
                    return true;
                }
                //return if the location does not even exist. because of wrong input
                else
                {
                    return false;
                }
            }
        }
        //checking if the location is occupied for vertical direction ships
        else if(given_ship.Ship_dir_getter()=="V"){
            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->columns; j++){
                    if (this->board_patches[i][j].Loc_getter()==given_ship.Ship_mainloc_getter())
                    {
                        position_exists=true;
                        for (int z = 0; z <given_ship.Ship_size_getter(); z++)
                        {
                            if (this->board_patches[i+z][j].Situation_getter()!="---")
                            {
                                occupied=true;
                            }
                            
                        }
                    }
                }
            }
            if (occupied==true)
            {
                return false;
            }
            else{
                if (position_exists==true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else{
            return false;
        }
    }
    void Put_ship(Ship given_ship){
        //this function places the given ship inside board by vhanging the value of patches that will contain the ship
        //it gets a ship which also will contain a size, and a main location which helps the function to know where to put the ship
        //puting ship horizontal
        if (given_ship.Ship_dir_getter()=="H")
        {
            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->columns; j++){
                    if (this->board_patches[i][j].Loc_getter()==given_ship.Ship_mainloc_getter())
                    {
                        for (int z = 0; z <given_ship.Ship_size_getter(); z++)
                        {
                           this->board_patches[i][j+z].Situation_setter("SSS");
                        }
                        
                    }
                    
                }
            }
        }
        //puting ship vertical
        else if(given_ship.Ship_dir_getter()=="V"){
            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->columns; j++){
                    if (this->board_patches[i][j].Loc_getter()==given_ship.Ship_mainloc_getter())
                    {
                        for (int z = 0; z <given_ship.Ship_size_getter(); z++)
                        {
                           this->board_patches[i+z][j].Situation_setter("SSS");
                           
                            
                        }
                    }
                }
            }
        }

    }
    void Draw_covered_board(){
        //this function draws a covered for the player so that the player does not know where actually hsips exist.
        string board_letters[10]={"A","B","C","D","E","F","G","H","I","J"};
        string board_numbers[10]={"0","1","2","3","4","5","6","7","8","9"};
        cout<<endl<<"current situation for this player:"<<endl;
        cout<<"    ";
        for (int i = 0; i < 10; i++)
        {
            cout<<" "<<board_letters[i]<<" "<<"   ";
        }
        cout<<endl;
        //do not show the ships to users but show the hit/miss/sunkness
        for (int i = 0; i < this->rows; i++)
        {
            cout<<i<<" | ";
            for (int j = 0; j < this->columns; j++)
            {
                if (this->board_patches[i][j].Situation_getter()=="SSS"){
                cout<<"--- | ";
                }
                else{
                    cout<<this->board_patches[i][j].Situation_getter()<<" | ";
                }

            }
            cout<<endl;
        }
        
    }
    bool Hit_check(string attack_loc){
        //this function checks if the given locayion contains a ship. return true/false
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (this->board_patches[i][j].Loc_getter() == attack_loc)
                {
                    if (this->board_patches[i][j].Situation_getter()=="SSS")
                    {
                        //patch contains ship
                        return true;
                    }
                    
                    else{
                        //patch does not contains ship
                        return false;
                    }
                }
                
            }   
        }
        //location does not exist
        cout<<endl<<"wrong input!"<<endl;
        return false; 

    }
    void Mark_attack_result(string attack_loc){
        //this function updates the board after the attack
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (this->board_patches[i][j].Loc_getter() == attack_loc)
                {
                    if (this->board_patches[i][j].Situation_getter()=="SSS")
                    {
                        //update the patch as hit
                        this->board_patches[i][j].Situation_setter("HHH");
                    }
                    
                    else if (this->board_patches[i][j].Situation_getter()=="---"){

                        //update patch as miss
                        this->board_patches[i][j].Situation_setter("MMM");
                    }
                }
                else
                {
                    //continue this not the given location
                }
              
            }   
        }
    }
    void Sunk_check(Ship* given_ship){
        //this function checks if a given ship is sunk. it receives a ship pointer and updates board and ship accordingly
        bool hitted_part=false;
        int hitted_part_counter=0;
        //check if it is horizontal
        if (given_ship->Ship_dir_getter()=="H")
        {
            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->columns; j++){
                    if (this->board_patches[i][j].Loc_getter()==given_ship->Ship_mainloc_getter())
                    {
                        for (int z = 0; z <given_ship->Ship_size_getter(); z++)
                        {
                            if (this->board_patches[i][j+z].Situation_getter()=="HHH")
                            {
                                //the parts of the ships that has been hit
                                hitted_part=true;
                                hitted_part_counter++;
                            }
                        }
                        
                    }
                    
                }
            }
            //if all parts of the ship is hit
            if (hitted_part_counter==given_ship->Ship_size_getter())
            {
                for (int i = 0; i < this->rows; i++)
                {
                    for (int j = 0; j < this->columns; j++)
                    {
                        if (this->board_patches[i][j].Loc_getter()==given_ship->Ship_mainloc_getter())
                        {
                            for (int z = 0; z <given_ship->Ship_size_getter(); z++)
                            {
                                //ship is sunk. update the board
                                this->board_patches[i][j+z].Situation_setter("XXX");
                                given_ship->sunk_setter(true);
                            }
                        }
                    
                    }
                }

            }
        }
        //check if it is vertical
        else if(given_ship->Ship_dir_getter()=="V"){
            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->columns; j++){
                    if (this->board_patches[i][j].Loc_getter()==given_ship->Ship_mainloc_getter())
                    {
                        for (int z = 0; z <given_ship->Ship_size_getter(); z++)
                        {
                            if (this->board_patches[i+z][j].Situation_getter()=="HHH")
                            {
                                //the parts of the ships that has been hit
                                // hitted_part=true;
                                hitted_part_counter++;
                            }
                        }
                    }
                }
            }
            //the parts of the ships that has been hit
            if (hitted_part_counter==given_ship->Ship_size_getter())
            {
                for (int i = 0; i < this->rows; i++)
                {
                    for (int j = 0; j < this->columns; j++)
                    {
                        if (this->board_patches[i][j].Loc_getter()==given_ship->Ship_mainloc_getter())
                        {
                            for (int z = 0; z <given_ship->Ship_size_getter(); z++)
                            {
                                //ship is sunk. update the board
                                this->board_patches[i+z][j].Situation_setter("XXX");
                                given_ship->sunk_setter(true);

                            
                           
                            }

                        }
                    
                    }
                }

            }
        }
    }
};

#endif /*BOARD_H_*/