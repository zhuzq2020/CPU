/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * File:   ctimer.h
 * Author: sat01
 *
 * Created on December 15, 2023, 3:12 PM
 ******************************************************************************/

#ifndef CTIMER_H
#define CTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <pthread.h>
    
/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define MSEC_PER_SEC  1000
#define USEC_PER_SEC  1000000
#define NSEC_PER_SEC  1000000000
#define NSEC_PER_MSEC 1000000
    
typedef pthread_t TaskId;

/*******************************************************************************
*  TYPE DEFINITION
*******************************************************************************/
/*******************************************************************************
*  CLOCK TYPE
*******************************************************************************/
typedef enum
{
    ONCE  =  0x5,
    LOOP  =  0xA
} E_TimerType;
/*******************************************************************************
*  CLOCK INFORMATION FORMAT TYPE
*******************************************************************************/
typedef struct
{
    char name[20];
    timer_t id;
    TaskId creator;
    E_TimerType type;
    __uint32_t sec;
    __uint32_t msec;
    void (*pHandler)(void* pArg,...);
    void *pArg;
    void *pOptionArg[2];
} S_TimerInfo;

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
int init_timer(S_TimerInfo *p_timer, const char *p_name);
void delete_timer(S_TimerInfo *p_timer);
__int32_t start_timer(S_TimerInfo *p_timer, E_TimerType type, __uint32_t msec,
        void(*pHandler)(void *pArg, ...), void *pArg, ...);
__int32_t stop_timer(S_TimerInfo *p_timer);

#ifdef __cplusplus
}
#endif

#endif /* CTIMER_H */

