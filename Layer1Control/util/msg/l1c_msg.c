/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "l1c_msg.h"

/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define LOG_TAG "MSG : "
#define L1C_MQUEUE_DEPTH           (8)

/*******************************************************************************
 * GLOBAL VARIABLES DECLARATION
 ******************************************************************************/

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/

/*******************************************************************************
 * @funtion:l1c_msg_create()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
l1c_msg_t *l1c_msg_create(uint32_t msg_id, uint32_t msg_body_size)
{
    l1c_msg_t *stp_msg;
    
    stp_msg = (l1c_msg_t *)malloc(L1C_MSG_HEADER_LENGTH + msg_body_size);
    
    if (stp_msg != NULL) {
        stp_msg->st_msg_head.msg_id = msg_id;
        stp_msg->st_msg_head.msg_size = L1C_MSG_HEADER_LENGTH + msg_body_size;
    } else {
        RLOGE("msg create fail, errno = %d", errno);
    }
    
    return stp_msg;
}

/*******************************************************************************
 * @funtion:l1c_mqueue_open()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
mqd_t l1c_mqueue_open(char *mq_name)
{
    struct mq_attr st_mq_attr;
    mqd_t mq_des = -1;

    /* Fill in attributes for message queue */
    st_mq_attr.mq_maxmsg = L1C_MQUEUE_DEPTH;
    st_mq_attr.mq_msgsize = L1C_MSG_TRANSMIT_LENGTH;
    st_mq_attr.mq_flags	= 0;

    /* Set the flags for the open of the queue.
    * Make it a blocking open on the queue, meaning it will block if
    * this process tries to send to the queue and the queue is full.
    *
    *	O_CREAT - the queue will get created if it does not already exist.
    *	O_WRONLY - we are only planning to write to the queue.
    *
    * Open the queue, and create it if the receiving process hasn't
    * already created it.
    */
    //now for all the msg queue, open for both reand and write access
    mq_des = mq_open(mq_name, O_RDWR | O_CREAT | O_EXCL, 0666, &st_mq_attr);
    if ((mq_des < 0) && (errno == EEXIST)) {/* queue exist, O_RDWR open */
        mq_des = mq_open(mq_name, O_RDWR);
        RLOGI("mqueue exist, O_RDWR open.");
    }
    if (((mqd_t)-1) == mq_des) {
        RLOGE("mqueue open failed, errno = %d", errno);
        return -1;
    }

    return mq_des;
}

/*******************************************************************************
 * @funtion:l1c_mqueue_noblock_open()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
mqd_t l1c_mqueue_noblock_open(char* mq_name)
{
    struct mq_attr st_mq_attr;
    mqd_t mq_des;

    /* Fill in attributes for message queue */
    st_mq_attr.mq_maxmsg = L1C_MQUEUE_DEPTH;
    st_mq_attr.mq_msgsize = L1C_MSG_TRANSMIT_LENGTH;
    st_mq_attr.mq_flags	= 0;

    /* Set the flags for the open of the queue.
    * Make it a blocking open on the queue, meaning it will block if
    * this process tries to send to the queue and the queue is full.
    *
    *	O_CREAT - the queue will get created if it does not already exist.
    *	O_WRONLY - we are only planning to write to the queue.
    *
    * Open the queue, and create it if the receiving process hasn't
    * already created it.
    */
    //now for all the msg queue, open for both reand and write access
    mq_des = mq_open(mq_name, O_RDWR | O_CREAT | O_EXCL | O_NONBLOCK,
            0666, &st_mq_attr);
    if (mq_des < 0 && errno == EEXIST) {
//        mq_unlink(mq_name);
//        mq_des = mq_open(mq_name, O_RDWR | O_CREAT | O_NONBLOCK, 0666, &st_mq_attr);
        mq_des = mq_open(mq_name, O_RDWR | O_NONBLOCK);
        RLOGI("mqueue exist, O_RDWR | O_NONBLOCK open.");
    }
    if (((mqd_t)-1) == mq_des) {
        RLOGE("mqueue open failed, errno = %d", errno);
        return -1;
    }

    return mq_des;
}

int file_mq_send(mqd_t mqdes, const char *msg, size_t msglen, unsigned int prio)
{
    int ret = mq_send(mqdes, msg, msglen, prio);
    if (ret < 0) {
        RLOGE("mq_send fail: %d, %d ", ret, errno);
    }
    
    return ret;
}

ssize_t file_mq_receive(mqd_t mqdes, char *msg, size_t msglen, unsigned int *prio)
{
    ssize_t ret = mq_receive(mqdes, msg, msglen, prio);
    if (ret < 0) {
        RLOGE("mq_receive fail: %d,%d ", ret, errno);
    }
    
    return ret;
}
