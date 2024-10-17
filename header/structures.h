#pragma once
extern const struct argp_option in_args_options[];
extern struct argp main_argp;
struct in_args{
    char * algorithm;
    int frames;
    char * trace_file;
};

struct lru_item {
    int address;
    int unsigned time;
};
