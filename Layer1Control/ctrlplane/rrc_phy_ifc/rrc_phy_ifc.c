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
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "rrc_phy_ifc.h"
#include "../../l1c_para.h"
#include "../../util/msg/l1c_msg.h"
#include "../l1c_ctrlplane.h"
#include "../../inferface/l1c_phy_ifc.h"

/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define LOG_TAG "RRCPHYIFC : "
#define PSS_SSS_SYNC_TIMEOUT (300)/* 300s */

/*******************************************************************************
 * GLOBAL VARIABLES DECLARATION
 ******************************************************************************/
/* multiplex_pattern, rb_num, symbol_num, offset_rbs; */
int g_search_space_set_scs15[16][4] = {{1, 24, 2, 0}, 
                                       {1, 24, 2, 2},
                                       {1, 24, 2, 4},
                                       {1, 24, 3, 0},
                                       {1, 24, 3, 2},
                                       {1, 24, 3, 4},
                                       {1, 48, 1, 12},
                                       {1, 48, 1, 16},
                                       {1, 48, 2, 12},
                                       {1, 48, 2, 16},
                                       {1, 24, 3, 12},
                                       {1, 24, 3, 16},
                                       {1, 96, 1, 38},
                                       {1, 96, 2, 38},
                                       {1, 96, 3, 38},
                                       {0, 0, 0, 0}};                                                  
int g_search_space_set_scs30[16][4] = {{1, 24, 2, 0},
                                       {1, 24, 2, 1},
                                       {1, 24, 2, 2},
                                       {1, 24, 2, 3},
                                       {1, 24, 2, 4},
                                       {1, 24, 3, 0},
                                       {1, 24, 3, 1},
                                       {1, 24, 3, 2},
                                       {1, 24, 3, 3},
                                       {1, 24, 3, 4},
                                       {1, 48, 1, 12},
                                       {1, 48, 1, 14},
                                       {1, 48, 1, 16},
                                       {1, 48, 2, 12},
                                       {1, 48, 2, 14},
                                       {0, 48, 2, 16}};
int g_search_space_set_scs120[16][4] = {{1, 24, 2, 0},
                                        {1, 24, 2, 4},
                                        {1, 48, 1, 14},
                                        {1, 48, 2, 14},
                                        {3, 24, 2, -21},
                                        {3, 24, 2, 24},
                                        {3, 48, 2, -21},
                                        {3, 48, 2, 48},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 0}};
/* param_o, search_space_set_per_slot_num, param_m, first_symbol_index; */
int g_monitor_occasion_fr1[4][4] = {{2, 1, 2, 0},
                                    {4, 1, 2, 0},
                                    {8, 1, 2, 0},
                                    {0, 0, 0, 0}};
extern s_l1c_para g_l1c_syspara;
BOOL g_pss_sss_sync_flag = FALSE;

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
void pss_sync_start(void);
BOOL pss_sync_finish(void);
void sss_sync_start(int peak_pos);
BOOL sss_sync_finish(void);
void stop_cell_search(void);
void cell_search_cnf_ans_all(u8 result_ind, u8 is_search_end, u8 failure_cause);
void cell_search_cnf_ans_single(u8 result_ind, u8 failure_cause, u8 index);
void arrange_l1c_cell_list(void);
int get_peak_value(void);
void get_cell_info(void);
void *pss_sss_sync_thread(void *p_arg);

void pbch_detection_start(u16 pci);
BOOL pbch_detection_finish(void);
int get_pbch_info(s_l1c_cell_info_t *p_l1c_cell_info);
BOOL calculate_coreset0(s_l1c_cell_info_t *p_l1c_cell);
void pdcch_sib1_detection_start(s_l1c_cell_info_t *p_l1c_cell);
BOOL pdcch_sib1_detection_finish(void);
void pdsch_sib1_detection_start(void);
BOOL pdsch_sib1_detection_finish(void);
void pdsch_sib1bis_detection_start(void);
BOOL pdsch_sib1bis_detection_finish(void);
int get_sib1_data(u8 *p_sib1_data);
int get_sib1bis_data(u8 *p_sib1bis_data);

void pdcch_os_sib_detection_start(wnrrc_si_schdl_schdl_info_t *p_si_schdl_info);
BOOL pdcch_os_sib_detection_finish(void);
void pdcch_os_pos_sib_detection_start(wnrrc_pos_schdl_info_r16_t *p_pos_schdl_info_r16);
BOOL pdcch_os_pos_sib_detection_finish(void);
void pdcch_os_sib_r17_detection_start(wnrrc_si_schdl_info2_r17_t *p_si_schdl_info2_r17);
BOOL pdcch_os_sib_r17_detection_finish(void);

/*******************************************************************************
* FUNCTION PROTOTYPE
*******************************************************************************/
/*******************************************************************************
 * @funtion:phy_ue_state_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
nrrc_phy_result_ind_e phy_ue_state_deal(wnrrc_phy_rrc_state_change_ind_t *p_state)
{
    g_l1c_syspara.ue_state = p_state->nrrc_state;
}

/*******************************************************************************
 * @funtion:phy_ueid_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
nrrc_phy_result_ind_e phy_ueid_deal(wnrrc_phy_ueid_info_ind_t *p_ueid_info)
{
    if (!p_ueid_info->vaild_flag) return NRRC_PHY_RESULT_IND_FAILURE;
    memcpy(g_l1c_syspara.s_tmsi, p_ueid_info->s_tmsi, 6);
}

/*******************************************************************************
 * @funtion:pss_sync_start()
 * @description:rising edge;
 * @param:
 * @return:
 ******************************************************************************/
void pss_sync_start(void)
{
    l1c_phy_write(PSS_SYNC_START_REG, 0);
    l1c_phy_write(PSS_SYNC_START_REG, 1);
}

/*******************************************************************************
 * @funtion:pss_sync_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pss_sync_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 5000) {/* 5000us */
        if (TRUE == l1c_phy_read(PSS_SYNC_FINISH_REG)) break;
        time_cnt++;
        usleep(1);
    }
    if (5000 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:sss_sync_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void sss_sync_start(int peak_pos)
{
    if (peak_pos < 0) return;
    u32 nid2, peak_location, peak_angle;
    
    if (peak_pos < 4) nid2 = 0;
    else if (peak_pos < 8) nid2 = 1;
    else if (peak_pos < 12) nid2 = 2;
    else return;
    
    peak_location = l1c_phy_read(PEAK_LOCATION_0_REG + peak_pos);
    peak_angle = l1c_phy_read(PEAK_ANGLE_0_REG + peak_pos);
    
    l1c_phy_write(NID2_REG, nid2);
    l1c_phy_write(PSS_LOCATION_REG, peak_location);
    l1c_phy_write(PSS_ANGLE_REG, peak_angle);
    
    l1c_phy_write(SSS_SYNC_START_REG, 0);
    l1c_phy_write(SSS_SYNC_START_REG, 1);
}

/*******************************************************************************
 * @funtion:sss_sync_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL sss_sync_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 5000) {/* 5000us */
        if (TRUE == l1c_phy_read(SSS_SYNC_FINISH_REG)) break;
        time_cnt++;
        usleep(1);
    }
    if (5000 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:stop_cell_search()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void stop_cell_search(void)
{
    l1c_phy_write(PSS_SYNC_FINISH_CLR_REG, 0);
    l1c_phy_write(PSS_SYNC_FINISH_CLR_REG, 1);
    l1c_phy_write(SSS_SYNC_FINISH_CLR_REG, 0);
    l1c_phy_write(SSS_SYNC_FINISH_CLR_REG, 1);
}

/*******************************************************************************
 * @funtion:phy_cell_search_cnf_ans_all()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void cell_search_cnf_ans_all(u8 result_ind, u8 is_search_end, u8 failure_cause)
{
    static u8 s_trans_id = 0;
    int i;
    
    l1c_msg_t *p_ans_msg = l1c_msg_create(MSG_WNRRC_PHY_CELL_SEARCH_CNF,
            sizeof(wnrrc_phy_cell_search_cnf_t));
    wnrrc_phy_cell_search_cnf_t *p_phy_cell_search_cnf = 
            (wnrrc_phy_cell_search_cnf_t *)L1C_GET_MSG_BODY(p_ans_msg);
    p_phy_cell_search_cnf->trans_id = s_trans_id++;
    p_phy_cell_search_cnf->result_ind = result_ind;
    p_phy_cell_search_cnf->is_search_end = is_search_end;
    p_phy_cell_search_cnf->failure_cause = failure_cause;
    p_phy_cell_search_cnf->cell_num = g_l1c_syspara.l1c_cell_num;
    p_phy_cell_search_cnf->padding[0] = 0;
    p_phy_cell_search_cnf->padding[1] = 0;
    p_phy_cell_search_cnf->padding[2] = 0;
    for (i = 0; i < p_phy_cell_search_cnf->cell_num; i++) {
        if (NULL == g_l1c_syspara.l1c_cell_list[i]) continue;
        p_phy_cell_search_cnf->cellinfo_list[i].arfcn =
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.arfcn;
        p_phy_cell_search_cnf->cellinfo_list[i].band_id =
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.band_id;
        p_phy_cell_search_cnf->cellinfo_list[i].pci =
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.pci;
        p_phy_cell_search_cnf->cellinfo_list[i].rsrp =
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.rsrp;
        p_phy_cell_search_cnf->cellinfo_list[i].snr =
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.snr;
        p_phy_cell_search_cnf->cellinfo_list[i].padding[0] =
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.padding[0];
        p_phy_cell_search_cnf->cellinfo_list[i].padding[1] =
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.padding[i];
    }
    
    mq_send_msg((const char *)p_ans_msg, (const int)p_ans_msg->st_msg_head.msg_size);
    
    free(p_ans_msg);
    p_ans_msg = NULL;
}

/*******************************************************************************
 * @funtion:phy_cell_search_cnf_ans_single()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void cell_search_cnf_ans_single(u8 result_ind, u8 failure_cause, u8 index)
{
    if (g_l1c_syspara.l1c_cell_num <= index) return;
    static u8 s_trans_id = 0;
    
    l1c_msg_t *p_ans_msg = l1c_msg_create(MSG_WNRRC_PHY_CELL_SEARCH_CNF,
            sizeof(wnrrc_phy_cell_search_cnf_t));
    wnrrc_phy_cell_search_cnf_t *p_phy_cell_search_cnf = 
            (wnrrc_phy_cell_search_cnf_t *)L1C_GET_MSG_BODY(p_ans_msg);
    p_phy_cell_search_cnf->trans_id = s_trans_id++;
    p_phy_cell_search_cnf->result_ind = result_ind;
    if (g_pss_sss_sync_flag) p_phy_cell_search_cnf->is_search_end = 0;
    else p_phy_cell_search_cnf->is_search_end = 1;
    p_phy_cell_search_cnf->failure_cause = failure_cause;
    p_phy_cell_search_cnf->cell_num = 1;
    p_phy_cell_search_cnf->padding[0] = 0;
    p_phy_cell_search_cnf->padding[1] = 0;
    p_phy_cell_search_cnf->padding[2] = 0;
    p_phy_cell_search_cnf->cellinfo_list[0].arfcn =
            g_l1c_syspara.l1c_cell_list[index]->find_cell_info.arfcn;
    p_phy_cell_search_cnf->cellinfo_list[0].band_id =
            g_l1c_syspara.l1c_cell_list[index]->find_cell_info.band_id;
    p_phy_cell_search_cnf->cellinfo_list[0].pci =
            g_l1c_syspara.l1c_cell_list[index]->find_cell_info.pci;
    p_phy_cell_search_cnf->cellinfo_list[0].rsrp =
            g_l1c_syspara.l1c_cell_list[index]->find_cell_info.rsrp;
    p_phy_cell_search_cnf->cellinfo_list[0].snr =
            g_l1c_syspara.l1c_cell_list[index]->find_cell_info.snr;
    p_phy_cell_search_cnf->cellinfo_list[0].padding[0] =
            g_l1c_syspara.l1c_cell_list[index]->find_cell_info.padding[0];
    p_phy_cell_search_cnf->cellinfo_list[0].padding[1] =
            g_l1c_syspara.l1c_cell_list[index]->find_cell_info.padding[1];
    g_l1c_syspara.local_cell_pci = p_phy_cell_search_cnf->cellinfo_list[0].pci;
    
    mq_send_msg((const char *)p_ans_msg, (const int)p_ans_msg->st_msg_head.msg_size);

    free(p_ans_msg);
    p_ans_msg = NULL;
}

/*******************************************************************************
 * @funtion:arrange_l1c_cell_list()
 * @description:bubble sort
 * @param:
 * @return:
 ******************************************************************************/
void arrange_l1c_cell_list(void)
{
    s_l1c_cell_info_t *p_cell_temp = NULL;
    int i, j, m;
    
    m = g_l1c_syspara.l1c_cell_num;
    for (i = 0; i < g_l1c_syspara.l1c_cell_num; i++) {
        m -= 1;
        for (j = 0; j < m; j++) {
            if (WNRRC_CELL_SORT_PRIORITY_RSRP == g_l1c_syspara.sort_priority) {
                if (g_l1c_syspara.l1c_cell_list[j]->find_cell_info.rsrp
                        < g_l1c_syspara.l1c_cell_list[j + 1]->find_cell_info.rsrp) {
                    p_cell_temp = g_l1c_syspara.l1c_cell_list[j];
                    g_l1c_syspara.l1c_cell_list[j] = g_l1c_syspara.l1c_cell_list[j + 1];
                    g_l1c_syspara.l1c_cell_list[j + 1] = p_cell_temp;
                }
            } else {
                if (g_l1c_syspara.l1c_cell_list[j]->find_cell_info.snr
                        < g_l1c_syspara.l1c_cell_list[j + 1]->find_cell_info.snr) {
                    p_cell_temp = g_l1c_syspara.l1c_cell_list[j];
                    g_l1c_syspara.l1c_cell_list[j] = g_l1c_syspara.l1c_cell_list[j + 1];
                    g_l1c_syspara.l1c_cell_list[j + 1] = p_cell_temp;
                }
            }
        }
    }
}

/*******************************************************************************
 * @funtion:get_peak_value()
 * @description:pss peak judgment, get peak value
 * @param:
 * @return:
 ******************************************************************************/
int get_peak_value(void)
{
    u32 peak_abs[12];
    int peak_pos = 0, peak_max_pos;
    u32 peak_max, threshold_val = 1;
    
    /* get peak_abs */
    for (peak_pos = 0; peak_pos < 12; peak_pos++) {
        peak_abs[peak_pos] = l1c_phy_read(PEAK_ABS_0_REG + peak_pos);
    }
    
    peak_max = peak_abs[0];
    peak_max_pos = 0;
    for (peak_pos = 0; peak_pos < 12; peak_pos++) {
        if (peak_max < peak_abs[peak_pos]) {
            peak_max = peak_abs[peak_pos];
            peak_max_pos = peak_pos;
        }
    }
    /* cal threshold_val */
    
    if (threshold_val < peak_max) return peak_max_pos;

    return -1;
}

/*******************************************************************************
 * @funtion:get_cell_info()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void get_cell_info(void)
{
    if (MAX_NR_CELL_SEARCH_CELL_NUM <= g_l1c_syspara.l1c_cell_num) return;
//    u8 rsrp;/* cal */
    
    if (NULL == g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num])
        g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num] =
                (s_l1c_cell_info_t *)malloc(sizeof(s_l1c_cell_info_t));
    
    g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num]->pbch_flag = FALSE;
    /* get cell info to find_cell_info */
    g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num]->find_cell_info.rsrp
            = l1c_phy_read(SSS_RSRP_REG) & 0xFF;
    g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num]->find_cell_info.snr
            = l1c_phy_read(SSS_SNR_REG) & 0xFF;
    g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num]->find_cell_info.pci
            = l1c_phy_read(PCI_REG) & 0xFFFF;
    
    g_l1c_syspara.l1c_cell_num++;
}

/*******************************************************************************
 * @funtion:pss_sss_sync_thread()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void *pss_sss_sync_thread(void *p_arg)
{
    g_pss_sss_sync_flag = TRUE;
    struct timeval tv_start, tv_end;
    int count = 0, peak_pos;
    wnrrc_phy_cell_search_req_t *p_cell_search = (wnrrc_phy_cell_search_req_t *)p_arg;
    
    g_l1c_syspara.l1c_cell_num = 0;/* start search clean 0 */    
    gettimeofday(&tv_start, NULL);/* start time */    
    switch (p_cell_search->search_type) {
        case NRRC_PHY_CELL_SEARCH_TYPE_ALL_BAND:
            break;
        case NRRC_PHY_CELL_SEARCH_TYPE_BAND_LIST:
            while ((0 < (p_cell_search->band_num - count))
                    && (TRUE == g_pss_sss_sync_flag)) {
                pss_sync_start();/* pss_sync_start */
                if (!pss_sync_finish()) continue;/* wait pss_sync_finish */
                if ((peak_pos = get_peak_value()) < 0) continue;/* pss peak judgment */
                sss_sync_start(peak_pos);/* sss_sync_start */
                if (!sss_sync_finish()) continue;/* wait sss_sync_finish */
                get_cell_info();/* read find cell information */
                g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num - 1]->
                        find_cell_info.band_id = p_cell_search->band_list_ind[count];
                if (0 == count) {/* first sync */
                    cell_search_cnf_ans_single(NRRC_PHY_RESULT_IND_SUCCESS,
                            NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_OTHER, 0);                    
                }
                gettimeofday(&tv_end, NULL);
                if (PSS_SSS_SYNC_TIMEOUT < (tv_end.tv_sec - tv_start.tv_sec)) break;
                count++;                
            }
            break;
        case NRRC_PHY_CELL_SEARCH_TYPE_STORE_LIST_CELL:
            while ((0 < (p_cell_search->cell_num - count))
                    && (TRUE == g_pss_sss_sync_flag)) {
                pss_sync_start();/* pss_sync_start */
                if (!pss_sync_finish()) continue;/* wait pss_sync_finish */
                if ((peak_pos = get_peak_value()) < 0) continue;/* pss peak judgment */
                sss_sync_start(peak_pos);/* sss_sync_start */
                if (!sss_sync_finish()) continue;/* wait sss_sync_finish */
                get_cell_info();/* read find cell information */
                g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num - 1]->
                        find_cell_info.pci = p_cell_search->store_cell_list[count].pci;
                if (0 == count) {/* first sync */
                    cell_search_cnf_ans_single(NRRC_PHY_RESULT_IND_SUCCESS,
                            NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_OTHER, 0);                    
                }
                gettimeofday(&tv_end, NULL);
                if (PSS_SSS_SYNC_TIMEOUT < (tv_end.tv_sec - tv_start.tv_sec)) break;
                count++;
            }
            break;
        case NRRC_PHY_CELL_SEARCH_TYPE_STORE_LIST_ARFCN:
            while ((0 < (p_cell_search->arfcn_num - count))
                    && (TRUE == g_pss_sss_sync_flag)) {
                pss_sync_start();/* pss_sync_start */
                if (!pss_sync_finish()) continue;/* wait pss_sync_finish */
                if ((peak_pos = get_peak_value()) < 0) continue;/* pss peak judgment */
                sss_sync_start(peak_pos);/* sss_sync_start */
                if (!sss_sync_finish()) continue;/* wait sss_sync_finish */
                get_cell_info();/* read find cell information */
                g_l1c_syspara.l1c_cell_list[g_l1c_syspara.l1c_cell_num - 1]->
                        find_cell_info.arfcn = p_cell_search->store_arfcn_list[count];
                if (0 == count) {/* first sync */
                    cell_search_cnf_ans_single(NRRC_PHY_RESULT_IND_SUCCESS,
                            NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_OTHER, 0);                    
                }
                gettimeofday(&tv_end, NULL);
                if (PSS_SSS_SYNC_TIMEOUT < (tv_end.tv_sec - tv_start.tv_sec)) break;            
                count++;
            }
            break;
        case NRRC_PHY_CELL_SEARCH_TYPE_STORE_LIST_GSCN:
            RLOGI("NRRC_PHY_CELL_SEARCH_TYPE_STORE_LIST_GSCN.");
            break;
        default:
            RLOGI("pss_sss_sync search type %d no exist.", p_cell_search->search_type);
            break;
    }
    
    if (NULL != p_cell_search) {
        free(p_cell_search);
        p_cell_search = NULL;
    }
    g_pss_sss_sync_flag = FALSE;
    pthread_exit(NULL);
    
    return NULL;
}

/*******************************************************************************
 * @funtion:phy_pss_sss_sync_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
nrrc_phy_result_ind_e phy_pss_sss_sync_deal(wnrrc_phy_cell_search_req_t *p_cell_search_req)
{
    static u8 s_last_trans_id = 0xFF;
    pthread_t pss_sss_sync_task;
    int i, ret;
    wnrrc_phy_cell_search_req_t *p_arg = NULL;
    
    if (p_cell_search_req->trans_id == s_last_trans_id)
        return NRRC_PHY_RESULT_IND_FAILURE;
    p_arg = (wnrrc_phy_cell_search_req_t *)malloc(sizeof(wnrrc_phy_cell_search_req_t));
    memcpy(p_arg, p_cell_search_req, sizeof(wnrrc_phy_cell_search_req_t));
    s_last_trans_id = p_arg->trans_id;
    g_l1c_syspara.sort_priority = p_arg->sort_priority;
    if (!g_pss_sss_sync_flag) {
        ret = pthread_create(&pss_sss_sync_task, NULL,
                pss_sss_sync_thread, (void *)p_arg);
        if (0 != ret) return NRRC_PHY_RESULT_IND_FAILURE;
        pthread_detach(pss_sss_sync_task);
    }
    
    return NRRC_PHY_RESULT_IND_SUCCESS;
}

/*******************************************************************************
 * @funtion:phy_search_next_req_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int phy_search_next_req_deal(wnrrc_phy_search_next_req_t *p_search_next_req)
{
    static u8 s_last_trans_id = 0xFF;
    int i;
    
    if (p_search_next_req->trans_id == s_last_trans_id) return -1;
    s_last_trans_id = p_search_next_req->trans_id;
    
    arrange_l1c_cell_list();
    for (i = 0; i < g_l1c_syspara.l1c_cell_num; i++) {
        if (g_l1c_syspara.local_cell_pci ==
                g_l1c_syspara.l1c_cell_list[i]->find_cell_info.pci) break;
    }
    cell_search_cnf_ans_single(NRRC_PHY_RESULT_IND_SUCCESS,
            NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_OTHER, i + 1);
    
    return 0;
}

/*******************************************************************************
 * @funtion:phy_stop_search_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int phy_stop_search_deal(wnrrc_phy_stop_search_ind_t *p_stop_search_ind)
{
    static u8 s_last_trans_id = 0xFF;
    
    if (p_stop_search_ind->trans_id == s_last_trans_id) return -1;
    s_last_trans_id = p_stop_search_ind->trans_id;
    
    g_pss_sss_sync_flag = FALSE;
    stop_cell_search();/* stop cell search, phy pss sss */
    
    return 0;
}

/*******************************************************************************
 * @funtion:pbch_detection_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void pbch_detection_start(u16 pci)
{
    l1c_phy_write(PBCH_PCI_REG, (u32)pci);
    
    l1c_phy_write(PBCH_DETECTION_START_REG, 0);
    l1c_phy_write(PBCH_DETECTION_START_REG, 1);
}

/*******************************************************************************
 * @funtion:pbch_detection_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pbch_detection_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 5000) {/* 500us */
        if (TRUE == l1c_phy_read(PBCH_DETECTION_FINISH_REG)) break;
        time_cnt++;
        usleep(1);
    }
    if (5000 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:get_pbch_info()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int get_pbch_info(s_l1c_cell_info_t *p_l1c_cell_info)
{
    u32 mib, c_pbch_dmrs_init;
    u8 pbch_payload = 0;
    int L_max = 256;
    
    mib = l1c_phy_read(PBCH_MIB_PAYLOAD_REG);
    c_pbch_dmrs_init = l1c_phy_read(SSB_LOW3_REG);
    
    p_l1c_cell_info->cell_mib_info.sfn = ((mib >> 26) & 0x3F);
    p_l1c_cell_info->cell_mib_info.scs_com = ((mib >> 25) & 0x01);
    p_l1c_cell_info->cell_mib_info.ssb_subcarrier_offset = ((mib >> 21) & 0x0F);
    p_l1c_cell_info->cell_mib_info.dmrs_typeA_pos = ((mib >> 20) & 0x01);
    p_l1c_cell_info->cell_mib_info.sib1_cfg.ctrl_resource_zero = ((mib >> 16) & 0x0F);
    p_l1c_cell_info->cell_mib_info.sib1_cfg.search_space_zero = ((mib >> 12) & 0x0F);
    p_l1c_cell_info->cell_mib_info.cell_barred = ((mib >> 11) & 0x01);
    p_l1c_cell_info->cell_mib_info.intra_freq_reselect_allow = ((mib >> 10) & 0x01);

    if ((256 < p_l1c_cell_info->find_cell_info.band_id)
            && (p_l1c_cell_info->find_cell_info.band_id < 264)) {/* FR2 : n257~n263 */
        p_l1c_cell_info->k_ssb
                = p_l1c_cell_info->cell_mib_info.ssb_subcarrier_offset & 0x0F;
        pbch_payload = ((mib & 0x07) << 5);
        if (NRRC_PHY_MIB_SCS_COMMON_SCS30_OR_SCS120 
                == p_l1c_cell_info->cell_mib_info.scs_com) {/* SCS=120kHz */
            L_max = 256;
        } else {/* SCS=60kHz */
//            L_max = 256;
        }
    } else {/* FR1 */
        p_l1c_cell_info->cell_mib_info.ssb_subcarrier_offset += ((mib & 0x01) << 4);
        p_l1c_cell_info->k_ssb
                = p_l1c_cell_info->cell_mib_info.ssb_subcarrier_offset & 0x1F;
        pbch_payload = ((mib & 0x01) << 7) + (((mib >> 1) & 0x03) << 5);
        if (NRRC_PHY_MIB_SCS_COMMON_SCS30_OR_SCS120 
                == p_l1c_cell_info->cell_mib_info.scs_com) {/* SCS=30kHz */
//            L_max = 256;
        } else {/* SCS=15kHz */
//            L_max = 256;
        }
    }
    p_l1c_cell_info->sfn10 = p_l1c_cell_info->cell_mib_info.sfn
            + (((mib >> 4) & 0x0F) << 6);
    pbch_payload += (p_l1c_cell_info->sfn10 & 0x0F);
    pbch_payload += (((mib >> 3) & 0x01) << 4);
    
    if (4 == L_max) p_l1c_cell_info->ssb_index = c_pbch_dmrs_init & 0x03;
    else if (8 == L_max) p_l1c_cell_info->ssb_index = c_pbch_dmrs_init & 0x07;
    else if (64 == L_max) p_l1c_cell_info->ssb_index = (c_pbch_dmrs_init & 0x07)
            + (((pbch_payload >> 5) & 0x01) << 5)
            + (((pbch_payload >> 6) & 0x01) << 4)
            + (((pbch_payload >> 7) & 0x01) << 3);
    else if (128 == L_max) p_l1c_cell_info->ssb_index = (c_pbch_dmrs_init & 0x07)
            + (((pbch_payload >> 5) & 0x01) << 6)
            + (((pbch_payload >> 6) & 0x01) << 5)
            + (((pbch_payload >> 7) & 0x01) << 4)
            + (((p_l1c_cell_info->sfn10 >> 2) & 0x01) << 3);
    else if (256 == L_max) p_l1c_cell_info->ssb_index = (c_pbch_dmrs_init & 0x07)
            + (((pbch_payload >> 5) & 0x01) << 7)
            + (((pbch_payload >> 6) & 0x01) << 6)
            + (((pbch_payload >> 7) & 0x01) << 5)
            + (((p_l1c_cell_info->sfn10 >> 2) & 0x03) << 3);
    
    return 0;
}

/*******************************************************************************
 * @funtion:calculate_coreset0()
 * @description:kssb is 5bits of ssb_subcarrier_offset LSB on FR1, 
 *              kssb is 4bits of ssb_subcarrier_offset LSB on FR2.
 * @param:
 * @return:
 ******************************************************************************/
BOOL calculate_coreset0(s_l1c_cell_info_t *p_l1c_cell)
{    
    if ((256 < p_l1c_cell->find_cell_info.band_id)
            && (p_l1c_cell->find_cell_info.band_id < 264)) {/* FR2 : n257~n263 */
        if (p_l1c_cell->k_ssb < 12 ) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {/* FR1 */
        if (p_l1c_cell->k_ssb < 24) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:pdcch_sib1_detection_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void pdcch_sib1_detection_start(s_l1c_cell_info_t *p_l1c_cell)
{
    int mul_pat = 0, rb_num = 0, sym_num = 0, offset_rbs = 0;
    int miu, slot_n0, sfn_sib1, c_dmrs_init, c_init;
    int CCE[7], SI_RNTI;
    
    if ((256 < p_l1c_cell->find_cell_info.band_id)
            && (p_l1c_cell->find_cell_info.band_id < 264)) {/* FR2 : n257~n263 */
        if (NRRC_PHY_MIB_SCS_COMMON_SCS30_OR_SCS120
                == p_l1c_cell->cell_mib_info.scs_com) {/* SCS=120kHz */
            mul_pat = g_search_space_set_scs120[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][0];
            rb_num = g_search_space_set_scs120[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][1];
            sym_num = g_search_space_set_scs120[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][2];
            offset_rbs = g_search_space_set_scs120[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][3]; 
        } else {/* SCS=60kHz */
            
        }
        miu = 3;
    } else {/* FR1 */
        if (NRRC_PHY_MIB_SCS_COMMON_SCS30_OR_SCS120
                == p_l1c_cell->cell_mib_info.scs_com) {/* SCS=30kHz */
            mul_pat = g_search_space_set_scs30[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][0];
            rb_num = g_search_space_set_scs30[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][1];
            sym_num = g_search_space_set_scs30[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][2];
            offset_rbs = g_search_space_set_scs30[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][3];            
        } else {/* SCS=15kHz */
            mul_pat = g_search_space_set_scs15[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][0];
            rb_num = g_search_space_set_scs15[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][1];
            sym_num = g_search_space_set_scs15[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][2];
            offset_rbs = g_search_space_set_scs15[p_l1c_cell->cell_mib_info.sib1_cfg.ctrl_resource_zero][3];
        }
        miu = p_l1c_cell->cell_mib_info.scs_com;
    }
    
    slot_n0 = (int)((g_monitor_occasion_fr1[p_l1c_cell->cell_mib_info.sib1_cfg.search_space_zero][0]
            * pow(2, miu)) + (p_l1c_cell->ssb_index
            * g_monitor_occasion_fr1[p_l1c_cell->cell_mib_info.sib1_cfg.search_space_zero][2]))
            % ((int)(pow(2, miu) * 10)); 
    //sfn_ssb = p_mib_ind_t->mib.sfn*16+p_mib_ind_t->mib.lsb_4_sfn;
    sfn_sib1 = (g_monitor_occasion_fr1[p_l1c_cell->cell_mib_info.sib1_cfg.search_space_zero][0]
            * pow(2, miu)) + (((p_l1c_cell->ssb_index % 8)
            * g_monitor_occasion_fr1[p_l1c_cell->cell_mib_info.sib1_cfg.search_space_zero][2])
            / (pow(2, miu) * 10));
    if (1 <= sfn_sib1) sfn_sib1 = p_l1c_cell->sfn10 + 1;
    else if (0 == sfn_sib1) sfn_sib1 = p_l1c_cell->sfn10;
    c_dmrs_init = ((pow(2, 17) * ((sym_num * slot_n0)
            + g_monitor_occasion_fr1[p_l1c_cell->cell_mib_info.sib1_cfg.search_space_zero][1] + 1)
            * (p_l1c_cell->find_cell_info.pci + 1)) + (2 * p_l1c_cell->find_cell_info.pci))
            / pow(2, 31);
    c_init = p_l1c_cell->find_cell_info.pci % (int)pow(2, 31);
    CCE[0] = 4 * ((0 * rb_num / (6 * 4 * 4)) % (rb_num / (6 * 4)));
    CCE[1] = 4 * ((1 * rb_num / (6 * 4 * 4)) % (rb_num / (6 * 4)));
    CCE[2] = 4 * ((2 * rb_num / (6 * 4 * 4)) % (rb_num / (6 * 4)));
    CCE[3] = 4 * ((3 * rb_num / (6 * 4 * 4)) % (rb_num / (6 * 4)));
    CCE[4] = 4 * ((0 * rb_num / (6 * 8 * 2)) % (rb_num / (6 * 8)));
    CCE[5] = 4 * ((1 * rb_num / (6 * 8 * 2)) % (rb_num / (6 * 8)));
    CCE[6] = 4 * ((0 * rb_num / (6 * 16 * 1)) % (rb_num / (6 * 16)));
    SI_RNTI = 0xFFFF;
    /*send parameter
    l1c_phy_write(u32 reg_addr, u32 p_l1c_cell->k_ssb);
    l1c_phy_write(u32 reg_addr, u32 rb_num);
    l1c_phy_write(u32 reg_addr, u32 sym_num);
    l1c_phy_write(u32 reg_addr, u32 offset_rbs);
    l1c_phy_write(u32 reg_addr, u32 g_monitor_occasion_fr1[p_l1c_cell->cell_mib_info.sib1_cfg.search_space_zero][4]);
    l1c_phy_write(u32 reg_addr, u32 slot_n0);
    l1c_phy_write(u32 reg_addr, u32 sfn_sib1);
    l1c_phy_write(u32 reg_addr, u32 c_dmrs_init);
    l1c_phy_write(u32 reg_addr, u32 c_init);
    l1c_phy_write(u32 reg_addr, u32 CCE[0]);
    l1c_phy_write(u32 reg_addr, u32 CCE[1]);
    l1c_phy_write(u32 reg_addr, u32 CCE[2]);
    l1c_phy_write(u32 reg_addr, u32 CCE[3]);
    l1c_phy_write(u32 reg_addr, u32 CCE[4]);
    l1c_phy_write(u32 reg_addr, u32 CCE[5]);
    l1c_phy_write(u32 reg_addr, u32 CCE[6]);
    l1c_phy_write(u32 reg_addr, u32 SI_RNTI);
    ...
    */
}

/*******************************************************************************
 * @funtion:pdcch_sib1_detection_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pdcch_sib1_detection_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 500) {/* 500us */
//        if( *( unsigned short * )pBaseAddr == EMPTY ) break;
        time_cnt++;
        usleep(1);
    }
    if (500 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:pdsch_sib1_detection_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void pdsch_sib1_detection_start(void)
{
    
}

/*******************************************************************************
 * @funtion:pdsch_sib1_detection_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pdsch_sib1_detection_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 500) {/* 500us */
//        if( *( unsigned short * )pBaseAddr == EMPTY ) break;
        time_cnt++;
        usleep(1);
    }
    if (500 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:pdsch_sib1bis_detection_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void pdsch_sib1bis_detection_start(void)
{
    
}

/*******************************************************************************
 * @funtion:pdsch_sib1bis_detection_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pdsch_sib1bis_detection_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 500) {/* 500us */
//        if( *( unsigned short * )pBaseAddr == EMPTY ) break;
        time_cnt++;
        usleep(1);
    }
    if (500 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:get_sib1_data()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int get_sib1_data(u8 *p_sib1_data)
{
    
    
    return 0;
}

/*******************************************************************************
 * @funtion:get_sib1bis_data()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
int get_sib1bis_data(u8 *p_sib1bis_data)
{
    
    
    return 0;
}

/*******************************************************************************
 * @funtion:phy_pbch_detection()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
nrrc_phy_result_ind_e phy_pbch_detection(nrrc_phy_read_mibsib1_req_t *p_read_mibsib1_req)
{
    int i, ret, cell_pos;
    u8 sib1_data[MAX_NR_SI_SIZE], sib1bis_data[MAX_NR_SI_SIZE];
    
    for (cell_pos = 0; cell_pos < g_l1c_syspara.l1c_cell_num; cell_pos++) {
        if (p_read_mibsib1_req->cell_info.pci !=
                g_l1c_syspara.l1c_cell_list[cell_pos]->find_cell_info.pci)
            continue;
    }   
    if (g_l1c_syspara.l1c_cell_num <= cell_pos) return NRRC_PHY_RESULT_IND_FAILURE;
    
    if ((NRRC_PHY_MIBSIB1_READ_TYPE_MIBSIB1 == p_read_mibsib1_req->read_type)
            || (NRRC_PHY_MIBSIB1_READ_TYPE_MIB == p_read_mibsib1_req->read_type)) {/* read mib info */
        pbch_detection_start(g_l1c_syspara.l1c_cell_list[cell_pos]->find_cell_info.pci);/* pbch_detection_start */
        if (!pbch_detection_finish()) {
            g_l1c_syspara.l1c_cell_list[cell_pos]->pbch_flag = FALSE;
            return NRRC_PHY_RESULT_IND_FAILURE;/* wait pbch_mib_detection_finish */
        }
        get_pbch_info(g_l1c_syspara.l1c_cell_list[cell_pos]);/* get mib info */
        if (!calculate_coreset0(g_l1c_syspara.l1c_cell_list[cell_pos])) {
            g_l1c_syspara.l1c_cell_list[cell_pos]->pbch_flag = FALSE;
            return NRRC_PHY_RESULT_IND_FAILURE;
        }
        g_l1c_syspara.l1c_cell_list[cell_pos]->pbch_flag = TRUE;
        
        l1c_msg_t *p_mib_ans_msg = l1c_msg_create(MSG_PHY_WNRRC_MIB_IND,
                sizeof(phy_nrrc_mib_ind_t));
        phy_nrrc_mib_ind_t *p_mib_ind_t = 
                (phy_nrrc_mib_ind_t *)L1C_GET_MSG_BODY(p_mib_ans_msg);
        /* cell info */
        memcpy(&p_mib_ind_t->cell_info, &g_l1c_syspara.l1c_cell_list[i]->find_cell_info,
                sizeof(nrrc_phy_cell_info_t));
        /* mib info */
        memcpy(&p_mib_ind_t->mib,
                &g_l1c_syspara.l1c_cell_list[cell_pos]->cell_mib_info,
                sizeof(nr_mib_info_t));
        mq_send_msg((const char *)p_mib_ans_msg,
                (const int)p_mib_ans_msg->st_msg_head.msg_size);
        free(p_mib_ans_msg);
        p_mib_ans_msg = NULL;
        
        if (NRRC_PHY_MIBSIB1_READ_TYPE_MIBSIB1 == p_read_mibsib1_req->read_type) {/* read sib1 info */        
            pdcch_sib1_detection_start(g_l1c_syspara.l1c_cell_list[cell_pos]);/* pdcch_sib1_detection_start */
            if (!pdcch_sib1_detection_finish())/* pdcch_sib1_detection_finish */
                return NRRC_PHY_RESULT_IND_FAILURE;
            
            
            

            
            /* DCI format 1_0 decide */
            pdsch_sib1_detection_start();/* pdsch_sib1_detection_start */
            if (pdsch_sib1_detection_finish())/* pdsch_sib1_detection_finish */
                return NRRC_PHY_RESULT_IND_FAILURE;
            ret = get_sib1_data(sib1_data);/* p_sib1_ind_t fill */
            if (ret < 0) return NRRC_PHY_RESULT_IND_FAILURE;            
            l1c_msg_t *p_sib1_ans_msg = l1c_msg_create(MSG_PHY_WNRRC_SIB1_IND,
                sizeof(phy_nrrc_sib1_ind_t));
            phy_nrrc_sib1_ind_t *p_sib1_ind_t =
                    (phy_nrrc_sib1_ind_t *)L1C_GET_MSG_BODY(p_sib1_ans_msg);
            p_sib1_ind_t->sib1.data_len = ret;
            memcpy(p_sib1_ind_t->sib1.data, sib1_data, ret);
            mq_send_msg((const char *)p_sib1_ans_msg,
                    (const int)p_sib1_ans_msg->st_msg_head.msg_size);
            free(p_sib1_ans_msg);
            p_sib1_ans_msg = NULL; 
            
            /* DCI format 1_0 decide */
            pdsch_sib1bis_detection_start();/* pdsch_sib1bis_detection_start */
            if (!pdsch_sib1bis_detection_finish())/* pdsch_sib1bis_detection_finish */
                return NRRC_PHY_RESULT_IND_FAILURE;
            ret = get_sib1bis_data(sib1bis_data);/* p_sib1bis_ind_t fill */
            l1c_msg_t *p_sib1bis_ans_msg = l1c_msg_create(MSG_PHY_WNRRC_SIB1BIS_IND,
                sizeof(s_phy_nrrc_sib1bis_ind_t));
            s_phy_nrrc_sib1bis_ind_t *p_sib1bis_ind_t =
                    (s_phy_nrrc_sib1bis_ind_t *)L1C_GET_MSG_BODY(p_sib1bis_ans_msg);
            p_sib1bis_ind_t->sib1bis.data_len = ret;
            memcpy(&p_sib1bis_ind_t->sib1bis.data, sib1bis_data, ret);
            mq_send_msg((const char *)p_sib1bis_ans_msg,
                    (const int)p_sib1bis_ans_msg->st_msg_head.msg_size);
            free(p_sib1bis_ans_msg);
            p_sib1bis_ans_msg = NULL;
        }
    } else if (NRRC_PHY_MIBSIB1_READ_TYPE_SIB1 == p_read_mibsib1_req->read_type) {
        if (!g_l1c_syspara.l1c_cell_list[cell_pos]->pbch_flag)
            return NRRC_PHY_RESULT_IND_FAILURE;
        pdcch_sib1_detection_start(g_l1c_syspara.l1c_cell_list[cell_pos]);/* pdcch_sib1_detection_start */
        if (!pdcch_sib1_detection_finish())/* pdcch_sib1_detection_finish */
            return NRRC_PHY_RESULT_IND_FAILURE;
        
        
        
        
        
        ret = get_sib1_data(sib1_data);/* p_sib1_ind_t fill */
            if (ret < 0) return NRRC_PHY_RESULT_IND_FAILURE;
        
        l1c_msg_t *p_sib1_ans_msg = l1c_msg_create(MSG_PHY_WNRRC_SIB1_IND, 
                sizeof(phy_nrrc_sib1_ind_t));
        phy_nrrc_sib1_ind_t *p_sib1_ind_t = 
                (phy_nrrc_sib1_ind_t *)L1C_GET_MSG_BODY(p_sib1_ans_msg);
        p_sib1_ind_t->sib1.data_len = ret;
        memcpy(p_sib1_ind_t->sib1.data, sib1_data, ret);
        mq_send_msg((const char *)p_sib1_ans_msg, 
                (const int)p_sib1_ans_msg->st_msg_head.msg_size);
        free(p_sib1_ans_msg);
        p_sib1_ans_msg = NULL;        
        
        /* pdcch_sib1bis_detection_start */
        /* pdcch_sib1bis_detection_finish */        
    }
    
    return NRRC_PHY_RESULT_IND_SUCCESS;
}
/*******************************************************************************
 * @funtion:phy_ue_camp_on_info_deal()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
nrrc_phy_result_ind_e phy_ue_camp_on_info_deal(nrrc_phy_camp_on_req *p_camp_on_req)
{
    nrrc_phy_result_ind_e ret = NRRC_PHY_RESULT_IND_SUCCESS;
    l1c_msg_t *p_camp_on_ans_msg = NULL;
    nrrc_phy_camp_on_cnf_t *p_camp_on_cnf_t = NULL;
    
    if (NULL == g_l1c_syspara.ue_camp_on_info) {
        g_l1c_syspara.ue_camp_on_info = 
                (s_l1c_ue_camp_on_info_t *)malloc(sizeof(s_l1c_ue_camp_on_info_t));
        memset(g_l1c_syspara.ue_camp_on_info, 0, sizeof(s_l1c_ue_camp_on_info_t));
    }
    if (!g_l1c_syspara.ue_camp_on_info) {
        ret = NRRC_PHY_RESULT_IND_FAILURE;
        goto out;
    }
    g_l1c_syspara.ue_camp_on_info->pci = g_l1c_syspara.local_cell_pci;
    /* serv_cell_cfg_common_sib_cfg */
    if (p_camp_on_req->serv_cell_cfg_common_sib_cfg_flag) {
        memcpy(&g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib,
                &p_camp_on_req->serv_cell_cfg_common_sib,
                sizeof(wnrrc_serv_cell_cfg_comm_sib_t));
    }
    /* ue_tmr cfg */
    if (p_camp_on_req->ue_tmr_val_cfg_flag) {
        memcpy(&g_l1c_syspara.ue_camp_on_info->ue_tmr_val,
                &p_camp_on_req->ue_tmr_val, sizeof(wnrrc_ue_tmr_and_cons_t));
    }
    /* ntn_cfg */
    if (p_camp_on_req->ntn_cfg_flag) {
        memcpy(&g_l1c_syspara.ue_camp_on_info->ntn_cfg,
                &p_camp_on_req->ntn_cfg, sizeof(wnrrc_sib19_info_t));
    }
    /* si_schdl_cfg */
    if (p_camp_on_req->si_schdl_cfg_flag) {
        memcpy(&g_l1c_syspara.ue_camp_on_info->si_schdl_cfg,
                &p_camp_on_req->si_schdl_cfg, sizeof(wnrrc_si_schdl_info_t));
    }
    /* sib1_ext cfg */
    if (p_camp_on_req->sib1_ext_flag) {
        memcpy(&g_l1c_syspara.ue_camp_on_info->sib1_ext,
                &p_camp_on_req->sib1_ext, sizeof(nr_sib1_v1610_t));
    }    
    
out:
    p_camp_on_ans_msg = l1c_msg_create(MSG_WNRRC_PHY_CAMP_ON_CNF,
        sizeof(nrrc_phy_camp_on_cnf_t));
    p_camp_on_cnf_t = (nrrc_phy_camp_on_cnf_t *)L1C_GET_MSG_BODY(p_camp_on_ans_msg);
    p_camp_on_cnf_t->result_ind = ret;
    p_camp_on_cnf_t->padding[0] = 0;
    p_camp_on_cnf_t->padding[1] = 0;
    p_camp_on_cnf_t->padding[2] = 0;
    mq_send_msg((const char *)p_camp_on_ans_msg,
        (const int)p_camp_on_ans_msg->st_msg_head.msg_size);
    free(p_camp_on_ans_msg);
    p_camp_on_ans_msg = NULL;
    
    return ret;
}

/*******************************************************************************
 * @funtion:pdcch_os_sib_detection_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void pdcch_os_sib_detection_start(wnrrc_si_schdl_schdl_info_t *p_si_schdl_info)
{
    int i;
    int sfn, slot, sym;
    u8 monitor_slot_period;
    u16 monitor_slot_offset, duration, monitor_sym_within_slot;
    wnrrc_search_space_candi_num_t *p_nr_of_candidates = NULL;
    u64 freq_res_rb;
    u8 duration_symbol, precoder_granularity;
    wnrrc_cce_reg_interleave_info_t *p_cce_reg_interleave = NULL;
    int c_dmrs_init, c_init;
    int CCE[7];
    
    if (0 == g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.search_space_other_si) {
//        sfn = l1c_phy_read(u32 reg_addr);
//        slot = l1c_phy_read(u32 reg_addr);
//        sym = l1c_phy_read(u32 reg_addr);
    } else {
        for (i = 0; i < 4; i++) {
            if (g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.search_space_list[i].search_space_id == 
                    g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.search_space_other_si) {
                monitor_slot_period = g_l1c_syspara.ue_camp_on_info->
                        serv_cell_cfg_common_sib.dl_cfg_com_sib.initial_dl_bwp.
                        pdcch.search_space_list[i].monitor_slot_period;
                monitor_slot_offset = g_l1c_syspara.ue_camp_on_info->
                        serv_cell_cfg_common_sib.dl_cfg_com_sib.initial_dl_bwp.
                        pdcch.search_space_list[i].monitor_slot_offset;
                duration = g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
                        dl_cfg_com_sib.initial_dl_bwp.pdcch.search_space_list[i].duration;
                monitor_sym_within_slot = g_l1c_syspara.ue_camp_on_info->
                        serv_cell_cfg_common_sib.dl_cfg_com_sib.initial_dl_bwp.
                        pdcch.search_space_list[i].monitor_sym_within_slot[0];
                monitor_sym_within_slot = (monitor_sym_within_slot << 8) + 
                        g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
                        dl_cfg_com_sib.initial_dl_bwp.pdcch.search_space_list[i].
                        monitor_sym_within_slot[1];
                p_nr_of_candidates = &g_l1c_syspara.ue_camp_on_info->
                        serv_cell_cfg_common_sib.dl_cfg_com_sib.initial_dl_bwp.
                        pdcch.search_space_list[i].nr_of_candidates;
                break;
            }
        }
        if (3 < i) return;
    }
    for (i = 0; i < 4; i++) {
        if (g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.search_space_list[i].ctrl_res_set_id == 
                g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.ctrl_res_set.ctrl_res_set_id) {
            freq_res_rb = g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.ctrl_res_set.freq_res;
            duration_symbol = g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.ctrl_res_set.duration;
            precoder_granularity = g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.ctrl_res_set.precoder_granularity;
            p_cce_reg_interleave = &g_l1c_syspara.ue_camp_on_info->serv_cell_cfg_common_sib.
            dl_cfg_com_sib.initial_dl_bwp.pdcch.ctrl_res_set.cce_reg_interleave;
            break;
        }
    }
    if (3 < i) return;
    
    /* calc c_dmrs_init, c_init, CCE */
    
    /* send parameter */
//    l1c_phy_write(u32 reg_addr, u32 c_dmrs_init);

}

/*******************************************************************************
 * @funtion:pdcch_os_sib_detection_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pdcch_os_sib_detection_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 500) {/* 500us */
//        if( *( unsigned short * )pBaseAddr == EMPTY ) break;
        time_cnt++;
        usleep(1);
    }
    if (500 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:pdcch_os_pos_sib_detection_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void pdcch_os_pos_sib_detection_start(wnrrc_pos_schdl_info_r16_t *p_pos_schdl_info_r16)
{
    
}

/*******************************************************************************
 * @funtion:pdcch_os_pos_sib_detection_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pdcch_os_pos_sib_detection_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 500) {/* 500us */
//        if( *( unsigned short * )pBaseAddr == EMPTY ) break;
        time_cnt++;
        usleep(1);
    }
    if (500 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:pdcch_os_sib_r17_detection_start()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void pdcch_os_sib_r17_detection_start(wnrrc_si_schdl_info2_r17_t *p_si_schdl_info2_r17)
{
    
}

/*******************************************************************************
 * @funtion:pdcch_os_sib_r17_detection_finish()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
BOOL pdcch_os_sib_r17_detection_finish(void)
{
    int time_cnt = 0;
    
    while (time_cnt < 500) {/* 500us */
//        if( *( unsigned short * )pBaseAddr == EMPTY ) break;
        time_cnt++;
        usleep(1);
    }
    if (500 < time_cnt) return FALSE;
    
    return TRUE;
}

/*******************************************************************************
 * @funtion:phy_read_osi_detection()
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
nrrc_phy_result_ind_e phy_read_osi_detection(nrrc_phy_read_other_si_req_t *p_si_req)
{
    int i;
    
    for (i = 0; i < p_si_req->si_schdl_info_num; i++) {
        if (WNRRC_SI_BROADCAST_STATUS_NOT_ING == 
                p_si_req->si_schdl_info_list[i].si_broadcast_status) continue;
        pdcch_os_sib_detection_start(&p_si_req->si_schdl_info_list[i]);
        if (!pdcch_os_sib_detection_finish()) return NRRC_PHY_RESULT_IND_FAILURE;
    }
    
    if (p_si_req->pos_schdl_r16_valid) {
        for (i = 0; i < p_si_req->pos_scddl_info_num; i++) {
            if (WNRRC_POS_SCHDL_SI_BROADCAST_STATUS_R16_NOT_BRAODCASTING ==
                    p_si_req->pos_schdl_r16_list[i].si_broadcast_status_r16)
                continue;
            pdcch_os_pos_sib_detection_start(&p_si_req->pos_schdl_r16_list[i]);
            if (!pdcch_os_pos_sib_detection_finish())
                return NRRC_PHY_RESULT_IND_FAILURE;
        }
    }

    if (p_si_req->si_schdl_info_r17_list_valid) {
        for (i = 0; i < p_si_req->si_schdl_r17_num; i++) {
            if (WNRRC_SI_BROADCAST_STATUS_R17_NOT_BRAODCASTING ==
                    p_si_req->si_schdl_info_r17_list[i].si_broadcast_status_r17)
                continue;
            pdcch_os_sib_r17_detection_start(&p_si_req->si_schdl_info_r17_list[i]);
            if (!pdcch_os_sib_r17_detection_finish())
                return NRRC_PHY_RESULT_IND_FAILURE;
        }
    }
    
    return NRRC_PHY_RESULT_IND_SUCCESS;
}