#include "../../header/libraries.h"
#include "../../header/functions.h"
#include "../../header/constants.h"
#include "../../header/structures.h"
#include <stdlib.h>



void lru(int * address_buffer, int address_buffer_size, int frames){

    struct lru_item page_table[frames];


    for (int j = 0; j < address_buffer_size; j++) {
        for (int i = 0; i < frames; i++) {
            if (page_table[i].address/256 == address_buffer[j]/256) {
                printf("Page 0x%X already in memory\n", address_buffer[j]);
                break;
            }
        }
    }

}
