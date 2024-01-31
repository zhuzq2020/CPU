/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/errno.h>
#include <time.h>
#include <stdarg.h>
#include "ctimer.h"

/*******************************************************************************
*  TYPE DEFINITION
*******************************************************************************/

/*******************************************************************************
 * GLOBAL VARIABLES DECLARATION
 ******************************************************************************/

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
static void launch(union sigval sg);

/*******************************************************************************
 * @funtion: launch(union sigval sg)
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
static void launch(union sigval sg)
{
    if(((S_TimerInfo*)sg.sival_ptr)->pHandler)
    {
        ((S_TimerInfo*)sg.sival_ptr)->pHandler(((S_TimerInfo*)sg.sival_ptr)->pArg,
                ((S_TimerInfo*)sg.sival_ptr)->pOptionArg[0],
                ((S_TimerInfo*)sg.sival_ptr)->pOptionArg[1]);
    }   
}

/*******************************************************************************
 * @funtion: init_timer(S_TimerInfo *p_timer, const char *p_name)
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int init_timer(S_TimerInfo *p_timer, const char *p_name)
{
    struct sigevent se;
    pthread_attr_t attr;
    struct sched_param s_param;
    
    memset(&se, 0, sizeof(se));
    memset(&attr, 0, sizeof(attr));
    memset(&s_param, 0, sizeof(s_param));
    
    strncpy(p_timer->name, p_name, 20);
    p_timer->id = 0;
    p_timer->creator = 0;
    p_timer->type = ONCE;
    p_timer->sec = 0;
    p_timer->msec = 0;
    p_timer->pHandler = NULL;
    p_timer->pArg = NULL;
    
    /* create timer here */
    se.sigev_notify = SIGEV_THREAD;
    se.sigev_signo = SIGALRM;
    se.sigev_value.sival_ptr = (void *)p_timer;
    se.sigev_notify_function = launch;

    if (-1 == pthread_attr_setschedpolicy(&attr, SCHED_FIFO)) {
        printf("[%s,%d]ERROR, pthread_attr_setschedpolicy() [%s] error[%s]\n",
                __FILE__, __LINE__, p_timer->name, strerror(errno));
        return -1;
    }

    if (-1 == pthread_attr_setstacksize(&attr, 0x10000)) {
        printf("[%s,%d]ERROR, pthread_attr_setstacksize() [%s] error[%s]\n",
                __FILE__, __LINE__, p_timer->name, strerror(errno));
        return -1;
    }

    s_param.sched_priority = 99;
    if (-1 == pthread_attr_setschedparam(&attr, &s_param)) {
        printf("[%s,%d]ERROR, pthread_attr_setschedparam() [%s] error[%s]\n",
                __FILE__, __LINE__, p_timer->name, strerror(errno));
        return -1;
    }
    se.sigev_notify_attributes = &attr;

    if (-1 == timer_create(CLOCK_REALTIME, &se, &p_timer->id)) {
        printf("[%s,%d]ERROR, timer_create() create timer[%s] error[%s]\n",
        __FILE__, __LINE__, p_timer->name, strerror(errno));
        p_timer->id = 0;
        return -1;
    }
    
    return 0;
}

/*******************************************************************************
 * @funtion: delete_timer(S_TimerInfo *p_timer)
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void delete_timer(S_TimerInfo *p_timer)
{
    if (-1 == timer_delete(p_timer->id)) {
        printf("[%s,%d]ERROR, timer_delete() delete timer[%s] error[%s]\n",
               __FILE__, __LINE__, p_timer->name, strerror(errno));
    }
    
    p_timer->id = 0;
}

/*******************************************************************************
 * @funtion: start_timer
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
__int32_t start_timer(S_TimerInfo *p_timer, E_TimerType type, __uint32_t msec,
        void(*pHandler)(void *pArg, ...), void *pArg, ...)
{
    va_list ap;
    va_start(ap, pArg);
    
    p_timer->creator = pthread_self();
    p_timer->type = type;
    p_timer->pArg = pArg;
    p_timer->sec = msec / MSEC_PER_SEC;
    p_timer->msec = msec % MSEC_PER_SEC;
    p_timer->pHandler = pHandler;
    p_timer->pOptionArg[0] = NULL;//va_arg(ap, (void *));
    p_timer->pOptionArg[1] = NULL;//va_arg(ap, (void *));
    
    va_end(ap);
    
    struct itimerspec its;
    memset(&its, 0, sizeof(its));
    its.it_value.tv_sec = p_timer->sec;
    its.it_value.tv_nsec = p_timer->msec * NSEC_PER_MSEC;  
    
    /* 循环定时器，设置二次启动定时时间 */
    if (LOOP == p_timer->type) {
        its.it_interval.tv_sec = p_timer->sec;
        its.it_interval.tv_nsec = p_timer->msec * NSEC_PER_MSEC;
    }

    /* 启动定时器 */
    if (-1 == timer_settime(p_timer->id, 0, &its, NULL)) {
        printf("[%s,%d]ERROR, timer_settime() start timer[%s,%d] error[%s]\n",
               __FILE__, __LINE__, p_timer->name, p_timer->id, strerror(errno));      
        return -1;
    }
    
    return 0;
}

/*******************************************************************************
 * @funtion: stop_timer
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
__int32_t stop_timer(S_TimerInfo *p_timer)
{
    struct itimerspec ts;
    
    memset(&ts, 0, sizeof(ts));
    if (-1 == timer_settime(p_timer->id, 0, &ts, NULL)) {
        printf("[%s,%d]ERROR, timer_settime() cancel timer[%s,%d] error[%s]\n",
               __FILE__, __LINE__, p_timer->name, p_timer->id, strerror(errno));
        return -1;
    }

    return 0;
}