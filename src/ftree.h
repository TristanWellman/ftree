#ifndef FTREE_FTREE_H
#define FTREE_FTREE_H

#if defined _WIN32 | defined _WIN64 | defined __WIN32__
#include "../include/dirent.h"
#else
#include <dirent.h>
#endif

#define MAX_FUNCS_INPROJ 2147483647

struct n_func {

    char *file_name;
    char *func_name;
    char *func_line;

};

struct f_data {

    DIR *dir;
    struct dirent *direct;

    char *fdir;
    char *files[256];
    char *c_files[256];
    char *main_file;
    char *line;
    int main_line_num;

};

int ftree_init(char *fdir);
void ftree_run();

#endif
