#include <stdio.h>
#include "ftree.h"

#define DEFAULT_DIR "."

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
    }

    return 0;

}