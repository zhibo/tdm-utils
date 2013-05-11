/*
 * tdm-utils - TDM support utilities
 *
 * Copyright (C) 2013 Bo Zhi<bobo900128@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * File: tdmctl.c
 *	 TDM control program
 */

#include <sys/types.h>
#include <attr/xattr.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum tdm_trust_status {
    TRUSTED = 0x01,
    UNTRUSTED,
    UNKNOWN,
};

typedef short int8;

struct degree{
    int8 deg;
    int8 thd;
    enum tdm_trust_status sts;
} __attribute__((packed));

typedef struct degree tdm_value;


static int dump_tdm_value(tdm_value *degr)
{
    if (NULL == degr)
        return -1;
    printf("degree: %d threshold: %d status: %d\n",
            degr->deg, degr->thd, degr->sts);
    return 0;
}

static int set_degree(const char *file)
{
    int err, len;
    /* TODO: ugly
     */
    tdm_value *degr = malloc(sizeof(tdm_value));
    degr->deg = 100;
    degr->thd = 90;
    degr->sts = TRUSTED;
    len = sizeof(tdm_value);
    err = setxattr(file, "security.tdm", degr, len, 0);
	if (err < 0) {
		printf("setxattr failed: %s\n", file);
		return err;
    }
    printf("%s: setxattr ok!\n", file);
    return 0;
}

static int _get_degree(const char *file, tdm_value *degr, int *len)
{
    int err;
    *len = sizeof(tdm_value);
    err = getxattr(file, "security.tdm", degr, *len);
    if (err < 0){
        printf("getxattr failed: %s\n", file);
        return err;
    }
    return 0;
}

static int get_degree(const char *file)
{
    tdm_value *degr = malloc(sizeof(tdm_value));
    int err, len = 0;
    err = _get_degree(file, degr, &len);
    if (err < 0){
        printf("__get_degree failed: %s\n", file);
        return err;
    }
    printf("getxattr: %s\n", file);
    printf("length: %d\n", len);
    err = dump_tdm_value(degr);
    if (err < 0){
        printf("dump error: %s\n", file);
        return err;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int err;
    if (3 != argc){
        printf("Usage: tdmctl type[set|get] filename\n");
        return 0;
    }
    char *type = argv[1];
    char *file = argv[2];
    if (strcmp(type, "set") == 0){
        err = set_degree(file);
    }else if (strcmp(type, "get") == 0){
        err = get_degree(file);
    }else{
        err = -1;
    }
    if (0 != err)
        return err;
    return 0;
}
