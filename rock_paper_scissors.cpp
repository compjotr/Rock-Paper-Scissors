#include "rock_paper_scissors.hpp"
#include <eosiolib/print.hpp>
#include <eosiolib/memory.hpp>
#include <string>

using namespace eosio;

namespace rock {
using  std::cin;


class rock_paper_scissors : public contract {

    using contract::contract;
    
public: 
    rock_paper_scissors(account_name self):contract(self) {}



    
      /// @abi action 
    void hi( account_name user ) {
        prints( "Hello akdljsføjdsføldsajføajds " );
        }
   
        //abi action
    void create(const account_name& challenger, const account_name& host){
        print("create kjører");
        print("host name: ", name{host});
    }
    
        //abi action
        void restart(const account_name& challenger, const account_name& host, const account_name& by){}
    
    //abi action
        void close(const account_name& challenger, const account_name& host){
            print("ta å print for faen i helvete. ");
        }
        //abi action
        void move(const account_name& challenger, const account_name& host, const account_name& by, char handAction){}

    account_name get_winner(account_name winner){
        print("getwinner kjører");
        return N(winner);
    };


    account_name get_round_winner(char play1, char play2, game& g ){
        print("winner kjører");
        if(play1 == play2){
            return N(draw);
            print( "it's a draw! Play agian");
        }

        //vinning possibliities player1
        if ((play1 =='r' && play2 == 's') || (play1 == 's' && play2 == 'p') || (play1 == 'p' && play2 == 'r')){
            print(" the winner is player 1!");
            return g.host;
        }
        //vinning for player2 
        else {
            print("The Winner is player 2!");
            return g.challenger;
        }
    };

     account_name get_game_winner(const game& g) {
        // Calculate score
        uint8_t host_score = 0;
        uint8_t foe_score = 0;
        for (int i = 0; i < g.round; i++) {
            if (g.round_winner[i] == g.host) {
                host_score++;
            } else if (g.round_winner[i] == g.foe) {
                foe_score++;
            }
        }
        // Determine winner
        if (host_score >= 6 ) {
            return g.host;
        } else if (foe_score >= 6) {
            return g.foe;
        } else if (g.round > 9 && host_score == foe_score) {
            return N(draw);
        } else {
            return N(none);
        }

    }


    bool is_valid_movement(char hand) {
        print("valid kjører");
        return (hand == 'r' || hand == 'p' || hand == 's');
        //input has to be r=rock p=paper s=scissors
    }

    void get_game_input(){
        print("game input kjører");
        char play1;
        char play2;
        print("Hi player1, please enter a hand action. 'r' for rock, 'p' for paper, and 's' for scissors: ");
        cin >> play1;
        while (!is_valid_movement(play1)){
            print( "Illegal move, enter again:");
            cin >> play1;
            }
        print("Hi player2, please enter a hand action. 'r' for rock, 'p' for paper, and 's' for scissors: ");
        cin >> play2;
        while (!is_valid_movement(play2)){
            print("Illegal move, enter again:");
            cin >> play2;
            }
        };

    };



    EOSIO_ABI(rock_paper_scissors, (create)(restart)(close)(move)(hi))
 

} 
             