#include "../../header/libraries.h"
#include "../../header/functions.h"
#include "../../header/constants.h"

//Program that reads the pages into
int fifo(int address_array[], int number_of_frames, int lines){
    int page_table[NUMBER_OF_PAGES][2];
    int frame_table[number_of_frames][2];
    int count = 0;
    int memory_accesses = 0;
    int page_hits = 0;
    int page_faults = 0;
    int page_replacements = 0;

    printf("%d", lines);

    for(size_t i = 0; i < NUMBER_OF_PAGES; i++){
        //Setting all the valid-invalid bits to invalid
        page_table[i][1] = 0;
    }

    for(size_t i = 0; i < number_of_frames; i++){
        //Setting all the frames to free
        frame_table[i][1] = 0;
    }

    for(size_t i = 0; i < lines; i++){
        int page_table_index = address_array[i] / PAGE_SIZE_BYTES;

        if(page_table[page_table_index][1] == 1){
            printf("Address %.4x is on page %d which is already in physical memory\n", address_array[i], page_table_index);
            page_hits++;
        }else{
            printf("Address %.4x not in physical memory\n", address_array[i]);
            page_faults++;

            if(frame_table[count][1] == 1){
                page_table[frame_table[count][0]][1] = 0;
                frame_table[count][1] = 0;
                page_replacements++;
                printf("Page #%d paged out\n", frame_table[count][0]);
            }

            frame_table[count][0] = page_table_index;
            frame_table[count][1] = 1;

            page_table[page_table_index][0] = count;
            page_table[page_table_index][1] = 1;
            printf("Page #%d paged in\n", page_table_index);
            count++;

            if(count >= number_of_frames){
                count = 0;
            }
        }

        memory_accesses++;
    }

    printf("Algorithm:          FIFO\n");
    printf("Frames:              %d\n", number_of_frames);
    printf("Memory accesses:    %d\n", memory_accesses);
    printf("Page hits:          %d\n", page_hits);
    printf("Page faults:        %d\n", page_faults);
    printf("Page replacements:  %d\n", page_replacements);

    return 0;
}
