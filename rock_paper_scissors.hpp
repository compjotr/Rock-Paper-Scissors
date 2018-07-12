/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosiolib/eosio.hpp>
#include <iostream>
#include <string>


/*class rock_paper_scissors : public eosio::contract {
    public: 
    rock_paper_scissors( account_name self ): contract(self){} 
    */
using namespace std;
 namespace rock_paper_scissors {
        static const account_name games_account = N(games);
        static const account_name code_account = N(letsplay);



struct game {

   account_name challenger; 
   account_name host;

   account_name winner = N(none);

   auto primary_key() const { return challenger; }
    //The primary_key method is required by the above table definition for games. That is how the table knows what field is the lookup key for the table
   EOSLIB_SERIALIZE(game, (challenger)(host)(winner))
};

struct create {
    account_name   challenger;
    account_name   host;

    EOSLIB_SERIALIZE( create, (challenger)(host) )
    };
struct restart {
    account_name   challenger;
    account_name   host;
    account_name   by; // the account who wants to restart the game

    EOSLIB_SERIALIZE( restart, (challenger)(host)(by) )
};

struct close {
    account_name   challenger;
    account_name   host;

    EOSLIB_SERIALIZE( close, (challenger)(host) )
};


struct move {
    account_name   challenger;
    account_name   host;
    account_name   by; // the account who wants to make the move
    char       handAction;

    EOSLIB_SERIALIZE( move, (challenger)(host)(by)(handAction) )
 };
  
 };