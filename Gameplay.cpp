#include <iostream>
#include <string.h>
using namespace std;
#include "Patch.h"
#include "Ship.h"
#include "Board.h"
#include "Person.h"
int main(){
    //setting random number be different every time it is used during program
    srand(time(0)); 
    //creating different players, their boards, and placing ships
    Human human_player;
    AI ai_player;
    human_player.create_boards();
    human_player.enter_ships();
    ai_player.create_boards();
    ai_player.enter_ships();
    bool gamecontinue=true;
    //gameplay. game goes on until a player wins and each time a player attack then the other.
    while (gamecontinue==true)
    {
        cout<<endl<<"---------Your turn:---------"<<endl;
        cout<<endl<<"---------Your sunked ships: "<<human_player.sunked_ships_getter()<<" ---------"<<endl;
        human_player.Activate_bombs();
        //check if human won
        if (human_player.won_status_getter())
        {
            cout<<endl<<"You won!"<<endl;
            gamecontinue=false;
            break;
        }
        cout<<endl<<"---------Smith's turn:---------"<<endl;
        cout<<endl<<"---------Smith's sunked ships: "<<ai_player.sunked_ships_getter()<<" ---------"<<endl;
        ai_player.Activate_bombs();
        //check if AI won
        if (ai_player.won_status_getter())
        {
            cout<<endl<<"A. Smith won!"<<endl;
            gamecontinue=false;
            break;
        }
    }
    cout<<endl<<"end of the game!"<<endl;
    //last time displaying the boards of two players
    human_player.Draw_Full_Player_Board();
    ai_player.Draw_Full_Player_Board();
    return 0;
}