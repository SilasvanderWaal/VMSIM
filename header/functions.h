#pragma once
#include "./constants.h"
#include "./libraries.h"

int fifo(int address_array[], int number_of_frames, int lines);
int lru();
int opt();
int convert_from_hex_to_decimal(char hex[MAX_ADDRESS_CHARACTERS_HEX]);
