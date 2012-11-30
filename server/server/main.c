/* 
 * File:   main.c
 * Author: black
 *
 * Created on November 30, 2012, 11:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t semCtrlBox;
/*
 * 
 */
int main(int argc, char** argv) {

    sem_init(&semCtrlBox, 0, 1);
    printf("Hello, world\n");
    return (EXIT_SUCCESS);
}

