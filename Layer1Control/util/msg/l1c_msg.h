/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * File:   l1c_msg.h
 * Author: sat01
 *
 * Created on November 10, 2023, 11:39 AM
 ******************************************************************************/

#ifndef L1C_MSG_H
#define L1C_MSG_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <mqueue.h>
#include "../../l1c_typedef.h"
#include "ps_phy_msg_id.h"
    
/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define L1C_MSG_HEADER_LENGTH      (sizeof(l1c_msg_head_t))
#define L1C_MSG_TRANSMIT_LENGTH    (1500)
#define L1C_GET_MSG_BODY(stp_msg)  (&((stp_msg)->vp_msg_body))
    
/*******************************************************************************
*  TYPE DEFINITION
*******************************************************************************/
typedef struct l1c_msg_head
{
    u32 msg_id;/* msg id */
    u32 msg_size;/* msg size including the msg head + msg body */
} l1c_msg_head_t;

/* waring,  head + vp_msg_body is a fix struct; 
 * only allow modify the msg head struct, please do not modify the oal msg struct */
typedef struct l1c_msg
{
    l1c_msg_head_t st_msg_head;/* msg head */
    void *vp_msg_body;/* msg body pointer */
} l1c_msg_t;

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
l1c_msg_t *l1c_msg_create(uint32_t msg_id, uint32_t msg_body_size);
mqd_t l1c_mqueue_open(char *mq_name);
mqd_t l1c_mqueue_noblock_open(char* mq_name);
int file_mq_send(mqd_t mqdes, const char *msg, size_t msglen, unsigned int prio);
ssize_t file_mq_receive(mqd_t mqdes, char *msg, size_t msglen, unsigned int *prio);

#ifdef __cplusplus
}
#endif

#endif /* L1C_MSG_H */

