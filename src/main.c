#include "../header/libraries.h"
#include "../header/functions.h"
#include "../header/constants.h"
#include "../header/structures.h"

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

    int test = strtol("6A34", NULL, 16);
    printf("%d %X\n", test, test/256);

}
