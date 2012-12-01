/* 
 * File:   common.h
 * Author: black
 *
 * Created on December 1, 2012, 1:14 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#include <sys/sem.h>

enum semaphores
{
    semCtrlBox,
    semCtrlPallet,
    semCtrlImp,
    semSyncBoxIm,
    semSyncImpPalette,
    semSocket,
    semStock
};
#define NB_SEM 8
int Sems;
const int SEMS_START[NB_SEM] = {1, 1, 1, 1, 1, 1, 1, 1};

#endif	/* COMMON_H */

