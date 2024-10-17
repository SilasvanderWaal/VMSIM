#include "../../header/libraries.h"
#include "../../header/functions.h"
#include "../../header/constants.h"
#include <cstddef>
#include <cstdio.h>
#include <cstdlib.h>
#include <cstring>

<<<<<<< HEAD
void fifo(){
=======
//Program that reads the pages into
int fifo(int address_array[], int number_of_frames){
    int page_table[NUMBER_OF_PAGES][2];
    int frame_table[number_of_frames][2];
    int lines = 0;

    for(size_t i = 0; i < NUMBER_OF_PAGES; i++){
        //Setting all the valid-invalid bits to invalid
        page_table[i][1] = 0;
    }

    for(size_t i = 0; i < number_of_frames; i++){
        //Setting all the frames to free
        frame_table[i][1] = 0;
    }



    for(size_t i = 0; i < lines; i++){
        int page_table_index = address_array[i] / 256;

        if(page_table[page_table_index][1] == 1){
            printf("Address %x is on page %d which is already in physical memory", address_array[i], page_table_index);
        }else{
            for(size_t i = 0; i < number_of_frames; i++){
                if(frame_table[i][1] == 1){

                }
            }
        }
    }

    return 0;
>>>>>>> d4f17f721858ca5cef49b090864d16b8c983b8c8
}
