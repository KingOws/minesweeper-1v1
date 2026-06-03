#pragma once
#include <random>
#include <cstdint>

struct NetworkInfo {
  char header[4]; // 4 BYTES that will define what state we are in H--- Hosting J--- Joining HI-- Hosting InGame JI-- Joining InGame
  uint32_t seed;
  uint8_t difficulty;
  uint16_t x;
  uint16_t y;
  uint16_t current_players;
  int8_t winners_id; // I wanted to leak their ip but e didnt wanna do that 
};
