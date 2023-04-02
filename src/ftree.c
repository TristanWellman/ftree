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
    char *lline;
    int final_lnum;
    for(l=0; l < sizeof(FDATA.c_files); l++) {
        if(FDATA.c_files[l] == NULL) {
            break;
        }
        char buf[0x100];
        snprintf(buf, sizeof(buf), "%s/%s", FDATA.fdir, FDATA.c_files[l]);
        FILE *main_c_file = fopen(buf, "r");
        char line[256];
        int lnum = 0;
        while(fgets(line, sizeof(line), main_c_file) != NULL) {
            lnum++;
            char *int_m = "int main(";
            char* find = strstr(line, int_m);
            if(find != NULL) {
                FDATA.main_file = (char *)malloc(sizeof(char *)+100);
                strcpy(FDATA.main_file, FDATA.c_files[l]);
                lline = (char *)malloc(sizeof(char *)+100);
                strcpy(lline, line);
                final_lnum = lnum;
                break;
            } else {
                continue;
            }
        }
        fclose(main_c_file);
    }

    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s/%s", FDATA.fdir, FDATA.main_file);
    FDATA.main_file = buf;
    FDATA.line = lline;
    printf("Main function: %s\n %d| %s",
           FDATA.main_file,
           final_lnum,
           FDATA.line);

    return 0;
}

struct n_func next_function(struct n_func last_func) {
    struct n_func R_FUNC;
    FILE *last_file = fopen(last_func.file_name, "r");
    char line[256];
    int is_in_func = 0;
    while(fgets(line, sizeof(line), last_file) != NULL) {
        char *find_line = strstr(line, last_func.func_line);
        if(is_in_func == 1) {
            /*to be parsed*/
        }
        if(find_line != NULL) {
            is_in_func = 1;
        } else {
            continue;
        }
    }
    fclose(last_file);
    return R_FUNC;
}

void ftree_run() {
    struct n_func LFUNC;
    struct n_func NFUNC;

    LFUNC.file_name = FDATA.main_file;
    LFUNC.func_name = "main";
    LFUNC.func_line = FDATA.line;

    int i;
    for(i=0;i < MAX_FUNCS_INPROJ;i++) {
        NFUNC = next_function(LFUNC);
        LFUNC = NFUNC;
        break; /* <-- temporary */
    }
}