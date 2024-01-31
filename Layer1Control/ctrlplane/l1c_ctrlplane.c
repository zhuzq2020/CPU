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
#include <errno.h>
#include "l1c_ctrlplane.h"
#include "../l1c_typedef.h"
#include "../l1c_para.h"
#include "../util/msg/l1c_msg.h"
#include "rrc_phy_ifc/rrc_phy_ifc.h"
#include "../util/ctimer/ctimer.h"

/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define LOG_TAG "CTRLPLANE : "
#define CTRL_MQUEUE_NAME "/ctrl_mqueue"

/*******************************************************************************
 * GLOBAL VARIABLES DECLARATION
 ******************************************************************************/
extern u8 g_l1c_ue_state;
extern s_l1c_para g_l1c_syspara;
mqd_t g_ctrl_mq = -1;

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
void fsm_hander(void *pArg, ...);
void msg_deal(l1c_msg_t *p_msg);

/*******************************************************************************
 * @funtion:l1c_ctrlplane_thread()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void *l1c_ctrlplane_thread(void *arg)
{
    int nlen = 0;
    unsigned int prio = 1;
    pid_t self_pid = syscall(SYS_gettid);
    int cpu_set_core = (self_pid % 16);
    cpu_set_t smask;
    CPU_ZERO(&smask);   
    CPU_SET((cpu_set_core), &smask);
    sched_setaffinity(self_pid, sizeof(smask), &smask);
    S_TimerInfo s_fsm_timer;
    
    /* state machine */
    init_timer(&s_fsm_timer, "fsm_timer");
    start_timer(&s_fsm_timer, LOOP, 1100, fsm_hander, NULL);
    
    g_ctrl_mq = l1c_mqueue_open(CTRL_MQUEUE_NAME);
    if (g_ctrl_mq == (mqd_t)-1) {
        RLOGE("l1c_mqueue_open fail.");
        exit(-1);
    }
    
    RLOGI("l1c_ctrlplane_thread start, run on cpu%d", cpu_set_core);
    while (1) {
        l1c_msg_t *p_msg = (l1c_msg_t *)malloc(L1C_MSG_TRANSMIT_LENGTH);
        nlen = file_mq_receive(g_ctrl_mq, (char *)p_msg,
                L1C_MSG_TRANSMIT_LENGTH, &prio);
        if (nlen <= 0) {
            free(p_msg);
            p_msg = NULL;
            continue;
        }
        printf("nlen = %d \n", nlen);
        msg_deal(p_msg);
        
        free(p_msg);
        p_msg = NULL;
//        sleep(1);
    }
}

/*******************************************************************************
 * @funtion:fsm_hander()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void fsm_hander(void *pArg, ...)
{
    srand(time(NULL));
    
    switch (g_l1c_syspara.ue_state) {
        case RRC_STATE_REEST:
            RLOGI("l1c state : reset!");
            break;
        case RRC_STATE_IDLE:
            usleep((rand() & 0xff) << 10);
            RLOGI("l1c state : idle!");
            break;
        case RRC_STATE_CONNECTED:
            usleep((rand() & 0xff) << 10);
            RLOGI("l1c state : connected!");
            break;
        default:
            break;
    }
}

/*******************************************************************************
 * @funtion:msg_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void msg_deal(l1c_msg_t *p_msg)
{
    int i, ret;
    if (p_msg->st_msg_head.msg_size <= 8) return;
    char *p_msg_body = (char *)L1C_GET_MSG_BODY(p_msg);
    
    printf("msg_id = %d, msg_size = %d \n", p_msg->st_msg_head.msg_id,
            p_msg->st_msg_head.msg_size);
    for (i = 0; i < (p_msg->st_msg_head.msg_size - L1C_MSG_HEADER_LENGTH); i++) {
        printf(" %02X", p_msg_body[i]);
    }
    printf("\n");
    
    switch (p_msg->st_msg_head.msg_id) {
        case MSG_WNRRC_PHY_DEDICATED_CONFIG_REQ:/* MSG_WNRRC_PHY_DEDICATED_CONFIG_REQ */
            RLOGI("MSG_WNRRC_PHY_DEDICATED_CONFIG_REQ.");
            break;
        case MSG_WNRRC_PHY_HO_REQ:
            RLOGI("MSG_WNRRC_PHY_HO_REQ.");
            break;
        case MSG_WNRRC_PHY_DEDICATED_RELEASE_REQ:
            RLOGI("MSG_WNRRC_PHY_DEDICATED_RELEASE_REQ.");
            break;
        case MSG_WNRRC_PHY_STATECHG_IND:
            RLOGI("MSG_WNRRC_PHY_STATECHG_IND.");
            phy_ue_state_deal((wnrrc_phy_rrc_state_change_ind_t *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_MEAS_CONTROL_REQ:
            RLOGI("MSG_WNRRC_PHY_MEAS_CONTROL_REQ.");
            break;
        case MSG_WNRRC_PHY_CAMP_ON_REQ:
            RLOGI("MSG_WNRRC_PHY_CAMP_ON_REQ.");
            phy_ue_camp_on_info_deal((nrrc_phy_camp_on_req *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_CELL_SEARCH_REQ:/* MSG_WNRRC_PHY_CELL_SEARCH_REQ */
            RLOGI("MSG_WNRRC_PHY_CELL_SEARCH_REQ.");
            ret = phy_pss_sss_sync_deal((wnrrc_phy_cell_search_req_t *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_SEARCH_NEXT_REQ:/* MSG_WNRRC_PHY_SEARCH_NEXT_REQ */
            RLOGI("MSG_WNRRC_PHY_SEARCH_NEXT_REQ.");
            ret = phy_search_next_req_deal((wnrrc_phy_search_next_req_t *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_STOP_SEARCH_IND:
            RLOGI("MSG_WNRRC_PHY_STOP_SEARCH_IND.");
            phy_stop_search_deal((wnrrc_phy_stop_search_ind_t *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_STOP_READ_SI_IND:
            RLOGI("MSG_WNRRC_PHY_STOP_READ_SI_IND.");
            break;
        case MSG_WNRRC_PHY_READ_MIBSIB1_REQ:
            RLOGI("MSG_WNRRC_PHY_READ_MIBSIB1_REQ.");
            ret = phy_pbch_detection((nrrc_phy_read_mibsib1_req_t *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_READ_SI_REQ:
            RLOGI("MSG_WNRRC_PHY_READ_SI_REQ.");
            ret = phy_read_osi_detection((nrrc_phy_read_other_si_req_t *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_BG_CELL_SEARCH_REQ:
            RLOGI("MSG_WNRRC_PHY_BG_CELL_SEARCH_REQ.");
            break;
        case MSG_WNRRC_PHY_BG_SEARCH_NEXT_REQ:
            RLOGI("MSG_WNRRC_PHY_BG_SEARCH_NEXT_REQ.");
            break;
        case MSG_WNRRC_PHY_BG_READ_MSI_REQ:
            RLOGI("MSG_WNRRC_PHY_BG_READ_MSI_REQ.");
            break;
        case MSG_WNRRC_PHY_STOP_BG_SEARCH_IND:
            RLOGI("MSG_WNRRC_PHY_STOP_BG_SEARCH_IND.");
            break;
        case MSG_WNRRC_PHY_STOP_BG_READ_MSI_IND:
            RLOGI("MSG_WNRRC_PHY_STOP_BG_READ_MSI_IND.");
            break;
        case MSG_WNRRC_PHY_READ_CGI_SI_REQ:
            RLOGI("MSG_WNRRC_PHY_READ_CGI_SI_REQ.");
            break;
        case MSG_WNRRC_PHY_UEID_INFO_IND:
            RLOGI("MSG_WNRRC_PHY_UEID_INFO_IND.");
            phy_ueid_deal((wnrrc_phy_ueid_info_ind_t *)p_msg_body);
            break;
        case MSG_WNRRC_PHY_CONN_DEFAULT_CONFIG_REQ:
            RLOGI("MSG_WNRRC_PHY_CONN_DEFAULT_CONFIG_REQ.");
            break;
        case MSG_WNRRC_PHY_IDLE_MEAS_CFG_IND:
            RLOGI("MSG_WNRRC_PHY_IDLE_MEAS_CFG_IND.");
            break;
        case MSG_WNRRC_PHY_IDLE_STOP_MEAS_IND:
            RLOGI("MSG_WNRRC_PHY_IDLE_STOP_MEAS_IND.");
            break;
        case MSG_WNRRC_PHY_IDLE_START_MEAS_IND:
            RLOGI("MSG_WNRRC_PHY_IDLE_START_MEAS_IND.");
            break;
        default:
            RLOGI("msg type %d no exist.", p_msg->st_msg_head.msg_id);
            break;
    }
}

/*******************************************************************************
 * @funtion:mq_send_msg()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int mq_send_msg(const char *p_smsg, const int msg_len)
{
    if (NULL == p_smsg) return 0;
    if (0 == msg_len) return 0;
    int ret;
    unsigned int prio = 1;
    
    ret = file_mq_send(g_ctrl_mq, (char *)p_smsg, msg_len, prio);
    if (ret < 0) {
        RLOGE("mq_send_msg fail, ret = %d, errno = %d ", ret, errno);
    }
    
    return ret;
}
