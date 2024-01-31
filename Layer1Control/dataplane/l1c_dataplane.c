/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <sched.h>
#include <pthread.h>
#include "l1c_dataplane.h"
#include "../l1c_typedef.h"

/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define LOG_TAG "DATAPLANE : "

/*******************************************************************************
 * GLOBAL VARIABLES DECLARATION
 ******************************************************************************/

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/

/*******************************************************************************
 * @funtion:l1c_dataplane_thread()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void *l1c_dataplane_thread(void *arg)
{
    pid_t self_pid = syscall(SYS_gettid);
    int cpu_set_core = (self_pid % 16);
    cpu_set_t smask;
    CPU_ZERO(&smask);   
    CPU_SET((cpu_set_core), &smask);
    sched_setaffinity(self_pid, sizeof(smask), &smask);
    
    
    RLOGI("l1c_dataplane_thread start, run on cpu%d", cpu_set_core);
    while (1) {
        sleep(1);
    }
}
