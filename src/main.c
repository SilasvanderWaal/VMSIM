#include "../header/libraries.h"
#include "../header/functions.h"
#include "../header/constants.h"
#include "../header/structures.h"
#include <string.h>


const char docs[] = "";

const struct argp_option in_args_options[] = {
    {"algoritm", 'a', "ALRGORITHM", 0, "What algorithm to use"},
    {"frames", 'n', "FRAMES", 0, "Amount of frames"},
    {"file", 'f', "FILE", 0, "What tracefile to use"},
    {0}
};

error_t main_parse_opt(int key, char *arg, struct argp_state *state){
    /*
        Get the input argument from capture_argp_parse, which we
        know is a pointer to our arguments structure.
    */
    struct in_args *arguments = state->input;

    switch (key) {

    case ('a'):
        arguments->algorithm = arg;
        break;
    case ('n'):
        arguments->frames = atoi(arg);
        break;
    case ('f'):
        arguments->trace_file = arg;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

struct argp main_argp = { in_args_options, main_parse_opt, 0, docs };

int main(int argc, char * argv[]) {

    struct in_args *arguments = malloc(sizeof(struct in_args));

    argp_parse(&main_argp, argc, argv, 0, 0, arguments);

    if(arguments->frames <= 0) {
        return 0;
    }

    if(arguments->trace_file == NULL) {
        return 0;
    }

    FILE* trace_file = fopen(arguments->trace_file, "r");
    int lines = 0;

    //Allocating memory for all the addresses
    int * address_array = malloc(0);
    char buffer_string[MAX_ADDRESS_CHARACTERS_HEX];


    while(fgets(buffer_string, MAX_ADDRESS_CHARACTERS_HEX, trace_file)) {
        if (strcmp(buffer_string, "\n") == 0) { break;}
        lines++;
        address_array = realloc(address_array, lines * sizeof(int));
        address_array[lines - 1] = strtol(buffer_string, NULL, 16);
    }

    fclose(trace_file);

    printf("\nRunning simulation with %s...\n\n", arguments->algorithm);

    if(strcmp(arguments->algorithm, "fifo") == 0){
        fifo(address_array, arguments->frames, lines);
    }else if(strcmp(arguments->algorithm, "lru") == 0){
        lru(address_array, lines, arguments->frames);
    }else if(strcmp(arguments->algorithm, "opt") == 0){
        opt(address_array, arguments->frames, lines);
    }else{
        printf("Invalid algorithm\n");
    }

    free(address_array);

    return 0;
}
