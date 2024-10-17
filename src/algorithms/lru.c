#include "../../header/libraries.h"
#include "../../header/functions.h"
#include "../../header/constants.h"
#include "../../header/structures.h"



int lru(int * address_buffer, int address_buffer_size, int frames){

    int page_hits = 0, page_faults = 0, page_replacements = 0;

    const int unsigned page_size = 0xFF;
    // Page table handles time, array index is the gratest two
    // hex values
    struct lru_page_item page_table[page_size];

    // This is used to see how many frames is used
    int frame_counter = 0;

    for ( int i = 0; i < page_size; i++ ) {
        page_table[i].valid_bit = false;
        page_table[i].time = 0;
    }

    int oldest_page_index = address_buffer[0]/256;

    for (int j = 0; j < address_buffer_size; j++) {

        // printf("Address %04X is requested from process\n", address_buffer[j]);

        int page_index = address_buffer[j]/256;
        // printf("%X\n", page_index);

        if (page_table[page_index].valid_bit == true) {
            printf("Address %04X is on page %X which is already in physical memory\n", address_buffer[j], page_index);
            page_table[page_index].time = 0;
            page_hits++;
            continue;   // Dont need to loop and increase here, the oldest will still be the oldest
        }

        printf("Address %04X not in physical memory\n", address_buffer[j]);
        page_faults++;

        // find place to replace
        // I dont need to loop this if
        for (int i = 0; i < page_size; i++) {
            // We dont need to replace something that is not allocated
            if (page_table[i].valid_bit != true) { continue; }
            // printf("%02X %d\n", i, page_table[i].time);
            page_table[i].time++;

            if (page_table[i].time > page_table[oldest_page_index].time) { oldest_page_index = i; }
        }

        if (frame_counter >= frames) {
            printf("Page #%d paged out\n", oldest_page_index);
            page_table[oldest_page_index].valid_bit = false;
            page_table[oldest_page_index].time = 0;
            page_replacements++;
        } else {
            frame_counter++;
        }

        printf("Page #%d paged in\n", page_index);
        page_table[page_index].valid_bit = true;
        page_table[page_index].time = 0;
    }

    // This can be done much better with a function, but cant be botherd to do it now
    printf("\nSimulation Summary\n\n");

    printf("Algorithm:          LRU\n");
    printf("Frames:             %d\n", frames);
    printf("Memory accesses:    %d\n", address_buffer_size);
    printf("Page hits:          %d\n", page_hits);
    printf("Page faults:        %d\n", page_faults);
    printf("Page replacements:  %d\n", page_replacements);

    return 0;
}
