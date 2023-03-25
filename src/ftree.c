#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ftree.h"

struct f_data FDATA;

int ftree_init(char *fdir) {

    FDATA.fdir = fdir;

    FDATA.dir = opendir(fdir);
    int i, j;
    for(i=0; (FDATA.direct = readdir(FDATA.dir)) != NULL; i++) {
        FDATA.files[i] = (char *)malloc(sizeof(FDATA.direct->d_name));
        strcpy(FDATA.files[i], FDATA.direct->d_name);
    }

    closedir(FDATA.dir);

    int k = 0;
    for(j=0; j < sizeof(FDATA.c_files); j++) {
        if(FDATA.files[j] == NULL) {
            break;
        }
        char *check = strstr(FDATA.files[j], ".c");
        if(check != NULL) {
            FDATA.c_files[k] = (char *)malloc(sizeof(FDATA.files[j]));
            strcpy(FDATA.c_files[k], FDATA.files[j]);
            k++;
        }
    }

    int l;
    for(l=0; l < sizeof(FDATA.c_files); l++) {
        if(FDATA.c_files[l] == NULL) {
            break;
        }
        char buf[0x100];
        snprintf(buf, sizeof(buf), "%s/%s", FDATA.fdir, FDATA.c_files[l]);
        FILE *main_c_file = fopen(buf, "r");
        char line[256];
        while(fgets(line, sizeof(line), main_c_file) != NULL) {
            char *int_m = "int main(";
            char* find = strstr(line, int_m);
            if(find != NULL) {
                FDATA.main_file = (char *)malloc(sizeof(char *)+100);
                strcpy(FDATA.main_file, FDATA.c_files[l]);
                printf("Main function: %s\n   | %s", FDATA.main_file, line);
                break;
            } else {
                continue;
            }
        }
        fclose(main_c_file);
    }

    return 0;
}