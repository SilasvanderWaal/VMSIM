#include "../../header/libraries.h"
#include "../../header/functions.h"
#include "../../header/constants.h"
#include "../../header/structures.h"


int lru(int * address_buffer, int address_buffer_size, int frames){

    struct lru_item page_table[frames];

    for ( int i = 0; i < frames; i++ ) {
        page_table[i].address = 0x0;
        page_table[i].time = 0;
    }


    for (int j = 0; j < address_buffer_size; j++) {
        printf("%X is requested from process\n", address_buffer[j]);
        for (int i = 0; i < frames; i++) {
            if (page_table[i].address/256 == address_buffer[j]/256) {
                printf("Page 0x%X already in memory\n", address_buffer[j]);
                break;
            }
        }
    }

}
