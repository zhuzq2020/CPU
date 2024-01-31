/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * File:   rrc_phy_ifc.h
 * Author: sat01
 *
 * Created on November 10, 2023, 3:26 PM
 ******************************************************************************/

#ifndef RRC_PHY_IFC_H
#define RRC_PHY_IFC_H

#ifdef __cplusplus
extern "C" {
#endif
    
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "wnrrc_phy_ifc.h"
    
/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/

/*******************************************************************************
*  ENUM TYPE DEFINITION
*******************************************************************************/


/*******************************************************************************
*  COMMON TYPE DEFINITION
*******************************************************************************/


/*******************************************************************************
*  MSG TYPE DEFINITION
*******************************************************************************/
/********************* MSG_PHY_WNRRC_SIB1_BIS_IND *****************************/
typedef struct
{
    nr_si_buffer_t sib1bis;
} s_phy_nrrc_sib1bis_ind_t;

/*******************************************************************************
* TYPE DEFINITION
*******************************************************************************/
typedef struct
{
    BOOL pbch_flag;/* get mib_info flag */
    u8 k_ssb;
    u8 ssb_index;/* SSB block index */
    u16 sfn10;/* 10bits SFN */
    nrrc_phy_cell_info_t find_cell_info;
    nr_mib_info_t cell_mib_info;
} s_l1c_cell_info_t;

typedef struct
{
    u16 pci;
    wnrrc_serv_cell_cfg_comm_sib_t serv_cell_cfg_common_sib;
    wnrrc_ue_tmr_and_cons_t ue_tmr_val;
    wnrrc_sib19_info_t ntn_cfg;
    wnrrc_si_schdl_info_t si_schdl_cfg;
    nr_sib1_v1610_t sib1_ext;
} s_l1c_ue_camp_on_info_t;

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
nrrc_phy_result_ind_e phy_ue_state_deal(wnrrc_phy_rrc_state_change_ind_t *p_state);
nrrc_phy_result_ind_e phy_ueid_deal(wnrrc_phy_ueid_info_ind_t *p_ueid_info);
nrrc_phy_result_ind_e phy_pss_sss_sync_deal(wnrrc_phy_cell_search_req_t *p_cell_search_req);
int phy_search_next_req_deal(wnrrc_phy_search_next_req_t *p_search_next_req);
int phy_stop_search_deal(wnrrc_phy_stop_search_ind_t *p_stop_search_ind);
nrrc_phy_result_ind_e phy_pbch_detection(nrrc_phy_read_mibsib1_req_t *p_read_mibsib1_req);
nrrc_phy_result_ind_e phy_ue_camp_on_info_deal(nrrc_phy_camp_on_req *p_camp_on_req);
nrrc_phy_result_ind_e phy_read_osi_detection(nrrc_phy_read_other_si_req_t *p_si_req);

#ifdef __cplusplus
}
#endif

#endif /* RRC_PHY_IFC_H */

