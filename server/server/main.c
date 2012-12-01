/* 
 * File:   main.c
 * Author: black
 *
 * Created on November 30, 2012, 11:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
/*
 * 
 */
int main(int argc, char** argv)
{
    int i;
    Sems = semget ( IPC_PRIVATE, NB_SEM, 0700 );
    for (i = 0; i < NB_SEM; ++i)
        semctl ( Sems, i, SETVAL, SEMS_START[i] );

    return (EXIT_SUCCESS);
}

