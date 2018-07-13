#pragma once
#include <eoslib/eos.hpp>
#include <eoslib/system.h>
#include <eoslib/db.hpp>
#include <eoslib/string.hpp>

using namespace eosio;
namespace rps {
  
  const static uint64_t contract_name = N(rps);

  /*
   * Moves
   */
  struct PACKED(moves) {
    uint8_t moves_val_len = 3;
    string moves_val[3]; 

    uint8_t nonces_len = 3;
    string nonces[3]; // Any random string, the larger it is, the better

    uint8_t hashed_moves_len = 3;
    checksum hashed_moves[3]; 

    uint8_t submit_turn = 0;
    uint8_t reveal_turn = 0;

    /*
     * Calculate the size of this object to be used by pack function
     */
    const uint32_t get_pack_size() const {
      uint32_t size = 0;
      size += sizeof(moves_val_len);
      for (int i = 0; i < moves_val_len; i++) {
        size += moves_val[i].get_size() + sizeof(moves_val[i].get_size());
      }
      size += sizeof(nonces_len);
      for (int i = 0; i < nonces_len; i++) {
        size += nonces[i].get_size() + sizeof(nonces[i].get_size());
      }
      size += sizeof(hashed_moves_len);
      for (int i = 0; i < hashed_moves_len; i++) {
        size += sizeof(hashed_moves[i]);
      }
      size += sizeof(submit_turn);
      size += sizeof(reveal_turn);
      return size;
    }
  };

  /*
   * Game
   */
  struct PACKED(game) {
    game() {
    };
    game(uint64_t id, account_name foe, account_name host):id(id), foe(foe), host(host) {
      created_time = now();
      for (int i = 0; i < round_winner_len; i++) {
        round_winner[i] = N(none);
      }
    };
    uint64_t id;
    account_name foe;
    account_name host;
    moves host_moves;
    moves foe_moves;
    uint8_t round = 0; // 0, 1, 2
    uint8_t round_winner_len = 3;
    account_name round_winner[3]; // none, draw, foe account name, host account name
    account_name game_winner = N(none); // none, draw, foe account name, host account name
    uint64_t host_stake = 0;
    uint64_t foe_stake = 0;
    time created_time;
    uint8_t is_active = 0;
    
    /*
     * Calculate the size of this object to be used by pack function
     */
    const uint32_t get_pack_size() const {
      uint32_t size=0;
      size += sizeof(foe);
      size += sizeof(host);
      size += host_moves.get_pack_size();
      size += foe_moves.get_pack_size();
      size += sizeof(round);
      size += sizeof(round_winner_len);
      size += sizeof(round_winner);
      size += sizeof(game_winner);
      size += sizeof(host_stake);
      size += sizeof(foe_stake);
      size += sizeof(created_time);
      size += sizeof(is_active);
      return size;
    }

  };

  /*
   * Balance
   */
  struct PACKED(balance) {
    const uint64_t key = N(account); // constant key
    uint64_t locked_amount = 0;
    uint64_t avail_amount = 0;
  };

  /*
   * Create New Game Action
   */
  struct PACKED(create) {
    account_name host;
    account_name foe;
  };


  /*
   * Cancel Active Game Action
   */
  struct PACKED(cancel) {
    uint64_t game_id;
    account_name by;
  };


  /*
   * Submit Move Action
   */
  struct PACKED(submit) {
    uint64_t game_id;
    account_name by;
    checksum   hashed_move;
  };


  /*
   * Reveal Move Action
   */
  struct PACKED(reveal) {
    uint64_t game_id;
    account_name by;
    string move_val;
    string nonce;
  };


  /*
   * Stake Money Action
   */
  struct PACKED(stake) {
    uint64_t game_id;
    uint64_t amount;
    account_name by;
  };

  /*
   * Withdraw Money Action
   */
  struct PACKED(withdraw) {
    account_name by;
    uint64_t amount;
  };

  
  /*
   * Games Table
   * Store all games information
   */
  using Games = table<contract_name,contract_name,N(games),game,uint64_t>;
  /*
   * Balance Table
   * Store all deposited money information of an account
   */
  using Balance = table<contract_name,contract_name,N(balance),balance,uint64_t>;
}