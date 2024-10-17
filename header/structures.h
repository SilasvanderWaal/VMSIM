#pragma once
extern const struct argp_option in_args_options[];
extern struct argp main_argp;
struct in_args{
    char * algorithm;
    int frames;
    char * trace_file;
};


struct lru_page_item {
    bool valid_bit;
    // Virtual address is vec index
    // Physical addresses in a real world scenario
    // int physical_address_index;
    unsigned int time;
};
