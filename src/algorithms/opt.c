#include "../../header/libraries.h"
#include "../../header/functions.h"
#include "../../header/constants.h"

int select_victim_frame(int frame_table[][2], int number_of_frames, int* address_array, int lines, int current_line);

//Program that reads the pages into
int opt(int address_array[], int number_of_frames, int lines){
    int page_table[NUMBER_OF_PAGES][2];
    int frame_table[number_of_frames][2];
    int frame_index = 0;
    int memory_accesses = 0;
    int page_hits = 0;
    int page_faults = 0;
    int page_replacements = 0;

    for(size_t i = 0; i < NUMBER_OF_PAGES; i++){
        //Setting all the valid-invalid bits to invalid
        page_table[i][1] = 0;
    }

    for(size_t i = 0; i < number_of_frames; i++){
        //Setting all the frames to free
        frame_table[i][1] = 0;
    }

    //Iterating over all the memory addresses
    for(size_t i = 0; i < lines; i++){
        int page_table_index = address_array[i] / PAGE_SIZE_BYTES;

        //Checking if the page is already loaded into memory by checking if the valid-bit is 1 (true)
        if(page_table[page_table_index][1] == 1){
            printf("Address %.4x is on page %d which is already in physical memory\n", address_array[i], page_table_index);
            page_hits++;
        }else{
            //If the page is not in main memory
            printf("Address %.4x not in physical memory\n", address_array[i]);
            page_faults++;

            //We check if the next frame is free
            if(frame_table[frame_index][1] == 1){
                //If not free, we need to find a victim frame to replace. Using the OPT algorithm
                frame_index = select_victim_frame(frame_table, number_of_frames, address_array, lines, i);
                page_table[frame_table[frame_index][0]][1] = 0;
                frame_table[frame_index][1] = 0;
                page_replacements++;
                printf("Page #%d paged out\n", frame_table[frame_index][0]);
            }

            //Write the page into the frame and set the frame free bit to 1 (not free)
            frame_table[frame_index][0] = page_table_index;
            frame_table[frame_index][1] = 1;

            //Updating the page table with the new information about the frame table
            page_table[page_table_index][0] = frame_index;
            page_table[page_table_index][1] = 1;
            printf("Page #%d paged in\n", page_table_index);
            frame_index++;

            //Check if count is out of bounds, if so reset to first item in frame table
            if(frame_index >= number_of_frames){
                frame_index = 0;
            }
        }

        memory_accesses++;
    }

    printf("Algorithm:          OPT\n");
    printf("Frames:             %d\n", number_of_frames);
    printf("Memory accesses:    %d\n", memory_accesses);
    printf("Page hits:          %d\n", page_hits);
    printf("Page faults:        %d\n", page_faults);
    printf("Page replacements:  %d\n", page_replacements);

    return 0;
}

int select_victim_frame(int frame_table[][2], int number_of_frames, int* address_array, int lines, int current_line){
    int victim_frame = -1, farthest = 0;

    //Iterating over all the memory requests that are left
    for (int i = 0 ; i < number_of_frames; i++) {
       int page = frame_table[i][0];

       //Looping over all the coming pages.
       //Have we get a hit, we check if the distance is greater than furthest
       size_t j;
        for(j = current_line; j < lines; j++){
            if(page == (address_array[j] / 256)){
                if(j > farthest){
                    farthest = j;
                    victim_frame = i;
                }
                break;
            }
        }

        //If we have checked all the coming pages but still have not found the page at index i, index i should be replaced
        if(j == lines){
            return i;
        }
    }

    return victim_frame;
}
