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

static int set_degree(const char *file)
{
    int err, len;
    /* TODO: ugly
     */
    char *degree = "100";
    len = strlen(degree);
    err = setxattr(file, "security.tdm", degree, len, 0);
	if (err < 0) {
		printf("setxattr failed: %s\n", file);
		return err;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int err;
    if (2 != argc){
        printf("Usage: tdmctl file degree\n");
        return 0;
    }
    char *file = argv[1];
    err = set_degree(file);
    if (0 != err)
        return err;
    return 0;
}
