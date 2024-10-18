#pragma once
#include "./constants.h"
#include "./libraries.h"

int fifo(int address_array[], int number_of_frames, int lines);
int lru(int * address_buffer, int address_buffer_size, int frames);
int opt();
