#include <stdio.h>
#include <stdlib.h>
#include "ftree.h"

#define DEFAULT_DIR "./"

int main(int argc, char *argv[]) {

    int has_external_dir;
    char *fdir;
    if (argc > 0) {
        has_external_dir = 1;
        fdir = argv[1];
    } else {
        has_external_dir = 0;
        fdir = DEFAULT_DIR;
    }

    int i = ftree_init(fdir);
    if(i != 0) {
        printf("ERROR:: Could not init Ftree\n");
        return 1;
    } else {
        ftree_run();
    }

#if defined _WIN32 | defined _WIN64 | defined __WIN32__
    system("generate.exe;");
#else
    system("mono generate.exe;");
#endif

    return 0;

}