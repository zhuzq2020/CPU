/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/

/*******************************************************************************
 * File:   l1c_ctrlplane.h
 * Author: sat01
 *
 * Created on November 10, 2023, 11:29 AM
 ******************************************************************************/

#ifndef L1C_CTRLPLANE_H
#define L1C_CTRLPLANE_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
void *l1c_ctrlplane_thread(void *arg);
int mq_send_msg(const char *p_smsg, const int msg_len);


#ifdef __cplusplus
}
#endif

#endif /* L1C_CTRLPLANE_H */

