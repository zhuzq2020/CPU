/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * File:   main.c
 * Author: sat01
 *
 * Created on November 10, 2023, 9:54 AM
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <pthread.h>
#include <string.h>
#include "l1c_typedef.h"
#include "init/l1c_init.h"
#include "dataplane/l1c_dataplane.h"
#include "ctrlplane/l1c_ctrlplane.h"

/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define LOG_TAG "MAIN : "
#define SIZE 1000

/*******************************************************************************
 * GLOBAL VARIABLES DECLARATION
 ******************************************************************************/

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
void setup_trap(void);
void fault_trap(int n, siginfo_t *p_sig_info, void *p_myact);
void input_para_deal(int argc, char **argv);

/*******************************************************************************
 * @funtion:
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int main(int argc, char **argv)
{
    int ret;
    pthread_t l1c_dataplane_task, l1c_ctrlplane_task;
    
    setup_trap();
    input_para_deal(argc, argv);
    init_l1c();

    ret = pthread_create(&l1c_dataplane_task, NULL, l1c_dataplane_thread, NULL);
    if (0 != ret) {
        RLOGE("create l1c_dataplane thread error!");
        exit(-1);
    }

    ret = pthread_create(&l1c_ctrlplane_task, NULL, l1c_ctrlplane_thread, NULL);
    if (0 != ret) {
        RLOGE("create l1c_ctrlplane thread error!");
        exit(-1);
    }

//    validLic((char *)".lic");
    
    pthread_join(l1c_dataplane_task, NULL);
    pthread_join(l1c_ctrlplane_task, NULL);
    
    return (EXIT_SUCCESS);
}

/*******************************************************************************
 * @funtion:setup_trap()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void setup_trap(void)
{ 
    struct sigaction st_act; 
    
    sigemptyset(&st_act.sa_mask);   
    st_act.sa_flags = SA_SIGINFO;     
    st_act.sa_sigaction = fault_trap; 
    sigaction(SIGSEGV, &st_act, NULL); 
    sigaction(SIGINT, &st_act, NULL);
    sigaction(SIGKILL, &st_act, NULL);
}

/*******************************************************************************
 * @funtion:fault_trap()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void fault_trap(int n, siginfo_t *p_sig_info, void *p_myact)
{ 
    int i, num; 
    char **pCalls; 
    void *pBuffer[SIZE];
     
    if (p_sig_info->si_signo == SIGINT) exit(1);
    if (p_sig_info->si_signo == SIGKILL) exit(1);
    
    RLOGE("Fault address:0x%lx", (unsigned long)p_sig_info->si_addr);
    num = backtrace(pBuffer, SIZE); 
    pCalls = backtrace_symbols(pBuffer, num); 
    for (i = 0; i < num; i++) printf("%s\n", pCalls[i]);

    exit(1); 
}

/*******************************************************************************
 * @funtion:input_para_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void input_para_deal(int argc, char **argv)
{
    if (argc < 2) return;
    int i;
    
    for (i = 1; i < argc; i++) {
        if (!strcasecmp(argv[i], "-v")) {
            RLOGI("Compile Time: UTC %s %s.", __DATE__, __TIME__);   
            exit(1); 
        }
        
        if (!strcasecmp(argv[i], "-h")) {
            RLOGI("use ./layer1control to run.");            
            exit(1);
        }
    }  
}
