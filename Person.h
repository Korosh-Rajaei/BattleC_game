#include <iostream>
#include <string.h>
using namespace std;
#ifndef PERSON_H_
#define PERSON_H_
#include "Patch.h"
#include "Ship.h"
#include "Board.h"

class Person{
protected:
    bool strike_value;
    bool won_status;
    Board player_board;
    Ship carrier;
    Ship battleship;
    Ship cruiser;
    Ship submarine;
    Ship destroyer;
public:
    void create_boards(){}
    void enter_a_ship(){}
    void enter_ships(){}
    void Activate_bombs(){}
    bool won_status_getter(){
        return this->won_status;
    }
};

class Human: public Person{
    int sunked_ships=0;
public:
    int sunked_ships_getter(){return this->sunked_ships;}
    void create_boards(){
        //this function draws the players board
        cout<<"----------------------------------------------"<<endl;
        cout<<"board created for the human player:"<<endl;
        this->player_board.Draw_board();
    }
    Ship enter_a_ship(string ship_type, int ship_size){
        //this function takes a ship type and size and randomly puts the ship into a avaiable location in board.
        string directions[2]={"H","V"};
        string columns[10]={"A","B","C","D","E","F","G","H","I","J"};
        string rows[10]={"0","1","2","3","4","5","6","7","8","9"};
        bool wrong_position=true;
        string position;
        string direction=directions[rand() % 2];
        //horizontal
        srand(time(0));
        if (direction=="H")
        {
            while (wrong_position)
            {
                string chosen_col=columns[rand() % (11-ship_size)];
                string chosen_row=rows[rand() % 10];
                position=chosen_col+chosen_row;
                Ship ship=Ship(position,direction,ship_size);

                if(this->player_board.check_position(ship))
                {
                    this->player_board.Put_ship(ship);
                    return ship;
                    wrong_position=false;
                }
                else{
                    wrong_position=true;
                    //wwrong position try finding another location
                }
            }
                
                
        }
        //vertical
        else{
            while (wrong_position)
            {
                string chosen_col=columns[rand() % 10];
                string chosen_row=rows[rand() % (11-ship_size)];
                position=chosen_col+chosen_row;
                Ship ship=Ship(position,direction,ship_size);

                if(this->player_board.check_position(ship))
                {
                    this->player_board.Put_ship(ship);
                    return ship;
                    wrong_position=false;
                }
                else{
                    wrong_position=true;
                    //wwrong position try finding another location
                }
            }            
        }
    }
    void enter_ships(){
        //this function submits ships to the board and gives the details of that ship to the player's ships
        Ship ship=enter_a_ship("carrier", 5);
        this->carrier=Ship(ship.Ship_mainloc_getter(),ship.Ship_dir_getter(), ship.Ship_size_getter());
        Ship ship2=enter_a_ship("battleship", 4);
        this->battleship=Ship(ship2.Ship_mainloc_getter(),ship2.Ship_dir_getter(), ship2.Ship_size_getter());
        Ship ship3=enter_a_ship("cruiser", 3);
        this->cruiser=Ship(ship3.Ship_mainloc_getter(),ship3.Ship_dir_getter(), ship3.Ship_size_getter());
        Ship ship4=enter_a_ship("submarine", 3);
        this->submarine=Ship(ship4.Ship_mainloc_getter(),ship4.Ship_dir_getter(), ship4.Ship_size_getter());
        Ship ship5=enter_a_ship("destroyer", 2);
        this->destroyer=Ship(ship5.Ship_mainloc_getter(),ship5.Ship_dir_getter(), ship5.Ship_size_getter());
        cout<<endl<<"ships have been added successfully!"<<endl;

    }
    void Activate_bombs(){
        //this function asks the human player to give a location to attack and check if hit or miss and continue until miss or sunk
        this->player_board.Draw_covered_board();
        this->strike_value=true;
        while (strike_value)
        {
            string attack_location;
            cout<<endl<<"where to attack?";
            cin>>attack_location;
            //start checking for new sunked ships
            Ship board_ships[5]={this->carrier,this->battleship,this->cruiser,this->submarine,this->destroyer};
            int current_sunked_ships = 0;
            //see how many ships are sunk before attacking
            for (int i = 0; i < 5; i++)
            {
                if (board_ships[i].sunk_getter()==true)
                {
                    current_sunked_ships++;
                        
                }
                    
            }
            cout<<endl<<"Attacking location: "<<attack_location<<endl;
            if (this->player_board.Hit_check(attack_location))
            {
                //mark the results of the attack, if h put h if not put m
                this->player_board.Mark_attack_result(attack_location);
                //check if any ship is sunk
                this->player_board.Sunk_check(&(this->carrier));
                this->player_board.Sunk_check(&(this->battleship));    
                this->player_board.Sunk_check(&(this->cruiser));    
                this->player_board.Sunk_check(&(this->submarine));    
                this->player_board.Sunk_check(&(this->destroyer));
                //start checking for new sunked ships
                Ship board_ships2[5]={this->carrier,this->battleship,this->cruiser,this->submarine,this->destroyer};
                int after_attack_sunked_ships = 0;
                for (int i = 0; i < 5; i++)
                {
                    if (board_ships2[i].sunk_getter()==true)
                    {
                        after_attack_sunked_ships++;
                        
                    }
                    
                }
                //see if any ships has been sunkbeacuse of this attack, if so change turn
                if (after_attack_sunked_ships==(current_sunked_ships+1))
                {
                    this->player_board.Draw_covered_board();
                    cout<<endl<<"A SHIP WAS SUNKED!"<<endl;
                    this->strike_value=false;
                }
                else
                {
                    
                    this->player_board.Draw_covered_board();
                    cout<<endl<<"HIT!"<<endl;
                    //hit
                    this->strike_value=true;
                }

            }
            else
            {
                this->player_board.Mark_attack_result(attack_location);
                this->player_board.Draw_covered_board();
                cout<<endl<<"MISS!"<<endl;
                //miss
                this->strike_value=false;
            }
        }
    }
    bool won_status_getter(){
        //this function checks if the palyer has sunk all its ships, if so, is the winner
        this->sunked_ships=0;
        Ship ships[5]={this->carrier,this->battleship,this->cruiser,this->submarine,this->destroyer};
        for (int i = 0; i < 5; i++)
        {
            if (ships[i].sunk_getter()==true)
            {
                this->sunked_ships++;
            }
        } 
        if (this->sunked_ships==5)
        {
            //all ships sunk
            this->won_status=true;
            return this->won_status;
        }
        else
        {
            this->won_status=false;
            return this->won_status;
        }
    }
    void Draw_Covered_Player_Board(){
        //this function draws a cowered board that player cannot see where ships are only hit/mis/sunkness
        cout<<"----------------------------------------------"<<endl;
        cout<<endl<<"The board for you:"<<endl;
        this->player_board.Draw_covered_board();
    }
    void Draw_Full_Player_Board(){
        //this is the last displaying board shown at the end of the game
        cout<<"----------------------------------------------"<<endl;
        cout<<endl<<"The board for you:"<<endl;
        this->player_board.Draw_board();
    }
};

class AI:public Person{
private:
    string masked_board[10][10];
    int sunked_ships=0;

public:
    int sunked_ships_getter(){return this->sunked_ships;}
    void create_boards(){
        //this function draws the players board
        cout<<"----------------------------------------------"<<endl;
        cout<<"board created for the AI player:"<<endl;
        this->player_board.Draw_board();
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
               this->masked_board[i][j]="-";
            }
            
        }
        
    }
    Ship enter_a_ship(string ship_type, int ship_size){
        //this function asks the user to give a location and a direction to put the ship in the board
        bool wrong_position=true;
        string position;
        string direction;
        while (wrong_position)
        {
            cout<<endl<<"where to put the "<<ship_type<<"? ";
            cin>>position;
            cout<<endl<<"which direction(H/V)? ";
            cin>>direction;
            Ship ship=Ship(position,direction,ship_size);

            if(this->player_board.check_position(ship))
            {
                //the location is valid put the ship to the board
                this->player_board.Put_ship(ship);
                return ship;
                wrong_position=false;
            }
            else{
                //the location/direction is not valid. ask for another location/direction
                cout<<endl<<"wrong PLACE or DIRECTION!";
                wrong_position=true;
            }
        }

    }
    void enter_ships(){
        //put the ships into the board and get the details and change this players' ships
        Ship ship=enter_a_ship("carrier", 5);
        this->carrier=Ship(ship.Ship_mainloc_getter(),ship.Ship_dir_getter(), ship.Ship_size_getter());
        Ship ship2=enter_a_ship("battleship", 4);
        this->battleship=Ship(ship2.Ship_mainloc_getter(),ship2.Ship_dir_getter(), ship2.Ship_size_getter());
        Ship ship3=enter_a_ship("cruiser", 3);
        this->cruiser=Ship(ship3.Ship_mainloc_getter(),ship3.Ship_dir_getter(), ship3.Ship_size_getter());
        Ship ship4=enter_a_ship("submarine", 3);
        this->submarine=Ship(ship4.Ship_mainloc_getter(),ship4.Ship_dir_getter(), ship4.Ship_size_getter());
        Ship ship5=enter_a_ship("destroyer", 2);
        this->destroyer=Ship(ship5.Ship_mainloc_getter(),ship5.Ship_dir_getter(), ship5.Ship_size_getter());
        cout<<endl<<"ships have been added successfully!"<<endl;

    }
    void Activate_bombs(){
        //the function for AI agent to choose where to attack and then see results of the attack
        string directions[2]={"H","V"};
        string columns[10]={"A","B","C","D","E","F","G","H","I","J"};
        string rows[10]={"0","1","2","3","4","5","6","7","8","9"};
        this->player_board.Draw_covered_board();
        this->strike_value=true;
        while (strike_value)
        {   
            bool found_target=false;
            string attack_location;
            int final_chosen_row;
            int final_chosen_column;
            //first step, look for horizontal/vertical patterns
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (this->masked_board[i][j]=="H")
                    {
                        if (this->masked_board[i+1][j]=="H"&&this->masked_board[i+2][j]=="-")
                        {
                            if (i+2 <= 9)
                            {
                                //pattern found
                                attack_location=columns[j]+rows[i+2];
                                final_chosen_row=i+2;
                                final_chosen_column=j;
                                found_target=true;
                            }
                            
                        }
                        if (this->masked_board[i][j+1]=="H"&&this->masked_board[i][j+2]=="-")
                        {
                            if (j+2<=9)
                            {
                                //pattern found
                                attack_location=columns[j+2]+rows[i];
                                final_chosen_row=i;
                                final_chosen_column=j+2;
                                found_target=true;
                            }
                        }
                        if(this->masked_board[i-1][j]=="H"&&this->masked_board[i-2][j]=="-")
                        {
                            if (i-2 >=0)
                            {
                                //pattern found
                                attack_location=columns[j]+rows[i-2];
                                final_chosen_row=i-2;
                                final_chosen_column=j;
                                found_target=true;
                            }
                        }
                        if(this->masked_board[i][j-1]=="H"&&this->masked_board[i][j-2]=="-")
                        {
                            if (j-2>=0)
                            {
                                //pattern found
                                attack_location=columns[j-2]+rows[i];
                                final_chosen_row=i;
                                final_chosen_column=j-2;
                                found_target=true;
                            }
                        }
                        
                    }
                }
            }
            //no pattern was found, look for single hit locations
            if (found_target==false)
            {
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        if (this->masked_board[i][j]=="H")
                        {
                            if (this->masked_board[i+1][j]=="-")
                            {
                                if (i+1 <= 9)
                                {
                                    //found a neighboring area of a hit location
                                    attack_location=columns[j]+rows[i+1];
                                    final_chosen_row=i+1;
                                    final_chosen_column=j;
                                    found_target=true;
                                }
                                
                            }
                            if (this->masked_board[i][j+1]=="-")
                            {
                                if (j+1<=9)
                                {
                                    //found a neighboring area of a hit location
                                    attack_location=columns[j+1]+rows[i];
                                    final_chosen_row=i;
                                    final_chosen_column=j+1;
                                    found_target=true;
                                }
                            }
                            if(this->masked_board[i-1][j]=="-")
                            {
                                if (i-1 >=0)
                                {
                                    //found a neighboring area of a hit location
                                    attack_location=columns[j]+rows[i-1];
                                    final_chosen_row=i-1;
                                    final_chosen_column=j;
                                    found_target=true;
                                }
                            }
                            if(this->masked_board[i][j-1]=="-")
                            {
                                if (j-1>=0)
                                {
                                    //found a neighboring area of a hit location
                                    attack_location=columns[j-1]+rows[i];
                                    final_chosen_row=i;
                                    final_chosen_column=j-1;
                                    found_target=true;
                                }
                            }
                            
                        }
                    }
                }
            }
            
            
            // no pattern, no empty neighbor of a hit patch, choose a random location
            while(found_target==false)
            {
                int chosen_col=rand() % 10;
                int chosen_row=rand() % 10;
                if (this->masked_board[chosen_row][chosen_col]=="-")
                {
                    attack_location=columns[chosen_col]+rows[chosen_row];
                    final_chosen_row=chosen_row;
                    final_chosen_column=chosen_col;
                    found_target=true;
                }
                else
                {
                    found_target=false;
                }
                
            }
            cout<<endl<<"Attacking location: "<<attack_location<<endl;
            //chose the location
            //start checking for new sunked ships
            Ship board_ships[5]={this->carrier,this->battleship,this->cruiser,this->submarine,this->destroyer};
            int current_sunked_ships = 0;
            //see how many ships are sunk before attacking
            for (int i = 0; i < 5; i++)
            {
                if (board_ships[i].sunk_getter()==true)
                {
                    current_sunked_ships++;
                        
                }
                    
            }
            //see if you hit/sunk a ship
            if (this->player_board.Hit_check(attack_location))
            {
                //update the masked board and mark the results of the attack
                this->player_board.Mark_attack_result(attack_location);
                this->masked_board[final_chosen_row][final_chosen_column]="H";
                //check if any ship is sunk
                this->player_board.Sunk_check(&(this->carrier));
                this->player_board.Sunk_check(&(this->battleship));    
                this->player_board.Sunk_check(&(this->cruiser));    
                this->player_board.Sunk_check(&(this->submarine));    
                this->player_board.Sunk_check(&(this->destroyer));
                //start checking for new sunked ships
                Ship board_ships2[5]={this->carrier,this->battleship,this->cruiser,this->submarine,this->destroyer};
                int after_attack_sunked_ships = 0;
                string board_letters[10]={"A","B","C","D","E","F","G","H","I","J"};
                string board_numbers[10]={"0","1","2","3","4","5","6","7","8","9"};
                //check the masked board, if all parts of a ship is hit, then the ship is sunk so do not have to check its neighbors
                for (int m = 0; m < 5; m++)
                {
                    if (board_ships2[m].sunk_getter()==true)
                    {
                        after_attack_sunked_ships++;
                        for (int i = 0; i < 10; i++)
                        {
                            for (int j = 0; j < 10; j++)
                            {
                                if (board_letters[j]+board_numbers[i]==board_ships2[m].Ship_mainloc_getter())
                                {
                                    if (this->masked_board[i][j]=="H")
                                    {
                                        if (board_ships2[m].Ship_dir_getter()=="H")
                                        {
                                            for (int z = 0; z <board_ships2[m].Ship_size_getter(); z++)
                                            {
                                                this->masked_board[i][j+z]="X";
                                            }
                                        }
                                        if (board_ships2[m].Ship_dir_getter()=="V")
                                        {
                                            for (int z = 0; z <board_ships2[m].Ship_size_getter(); z++)
                                            {
                                                this->masked_board[i+z][j]="X";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                }
                //see if any ships has been sunkbeacuse of this attack, if so change turn
                if (after_attack_sunked_ships==(current_sunked_ships+1))
                {
                    this->player_board.Draw_covered_board();
                    
                    cout<<endl<<"A SHIP WAS SUNKED!"<<endl;
                    this->strike_value=false;
                }
                else
                {
                    
                    this->player_board.Draw_covered_board();
                    //hit
                    cout<<endl<<"HIT!"<<endl;
                    this->strike_value=true;
                }

            }
            else
            {
                this->player_board.Mark_attack_result(attack_location);
                this->masked_board[final_chosen_row][final_chosen_column]="M";
                this->player_board.Draw_covered_board();
                //miss
                cout<<endl<<"MISS!"<<endl;
                this->strike_value=false;
            }
            
        }
    }
    bool won_status_getter(){
        //this function checks if the palyer has sunk all its ships, if so, is the winner
        this->sunked_ships=0;
        Ship ships[5]={this->carrier,this->battleship,this->cruiser,this->submarine,this->destroyer};
        for (int i = 0; i < 5; i++)
        {
            if (ships[i].sunk_getter()==true)
            {
                this->sunked_ships++;
            }
        }
        if (this->sunked_ships==5)
        {
            //all ships sunk
            this->won_status=true;
            return this->won_status;
        }
        else
        {
            this->won_status=false;
            return this->won_status;
        }
    }
    void Draw_Covered_Player_Board(){
        //this function draws a cowered board that player cannot see where ships are only hit/mis/sunkness
        cout<<"----------------------------------------------"<<endl;
        cout<<endl<<"The board for A. Smith:"<<endl;
        this->player_board.Draw_covered_board();
    }
    void Draw_Full_Player_Board(){
        //this is the last displaying board shown at the end of the game
        cout<<"----------------------------------------------"<<endl;
        cout<<endl<<"The board for A. Smith:"<<endl;
        this->player_board.Draw_board();
    }
};  
#endif /* PERSON_H_ */