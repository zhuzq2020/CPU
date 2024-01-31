/***********************************************************************************************************************
*
*  COPYRIGHT GuangZhou HaiGe TongXin
*
***********************************************************************************************************************/

/***********************************************************************************************************************
*
* FILE
*
*    wnrrc_phy.h
*
* DESCRIPTION
*
*    Header file
*    Comprises of include files, macro definition, type definition, global variables declaration
*    and global function prototype declaration.
*
* NOTE
*
*    
*
***********************************************************************************************************************/

/***********************************************************************************************************************
*  HISTORY OF CHANGES
************************************************************************************************************************
*
*    <date>        <author>                <CR_ID>              <DESCRIPTION>
*    2023-08-08                            Original             Create the file

*
***********************************************************************************************************************/
#ifndef WNRRC_PHY_IFC_H
#define WNRRC_PHY_IFC_H

/***********************************************************************************************************************
*  INCLUDE FILES
***********************************************************************************************************************/
//#include "oal_thread.h"
//#include "oal_msg.h"
#include "wnrrc_com_type.h"

/***********************************************************************************************************************
*  MACRO DEFINITION
***********************************************************************************************************************/
/*MSG_WNRRC_PHY_DEDICATED_CONFIG_REQ*/
typedef struct
{
    u8  trans_id;
    cell_group_config_t  master_cell_group;
}wnrrc_phy_dedicated_cfg_req_t;

/*MSG_WNRRC_PHY_DEDICATED_CONFIG_CNF*/
typedef struct
{ 
    u8  trans_id;
    u8  result;  /* 0 SUCC; 1 FAIL; */
    u8  padding[2];
}wnrrc_phy_dedi_cfg_cnf_t;


/*MSG_WNRRC_PHY_DEDICATED_RELEASE_REQ*/
/*MSG_WNRRC_PHY_DEDICATED_RELEASE_CNF*/

/*MSG_WNRRC_PHY_RELEASE_REQ*/
/*MSG_WNRRC_PHY_RELEASE_CNF*/


/*MSG_WNRRC_PHY_CONN_DEFAULT_CONFIG_REQ*/
typedef struct
{
    u8 paddings[4];
}wnrrc_phy_default_config_req_t;

/*MSG_WNRRC_PHY_CONN_DEFAULT_CONFIG_CNF*/
typedef struct
{
    u8 result; //0: success, 1:failure
    u8 paddings[3];
}wnrrc_phy_default_config_cnf_t;

/*MSG_WNRRC_PHY_STATECHG_IND*/
typedef struct
{
#define RRC_STATE_IDLE             (u8)0x00
#define RRC_STATE_CONNECTED        (u8)0x01
#define RRC_STATE_REEST            (u8)0x02
    u8 nrrc_state;
    u8 paddings[3];
}wnrrc_phy_rrc_state_change_ind_t;


/*MSG_WNRRC_PHY_HO_REQ*/
typedef struct
{
    u8  trans_id;
    cell_group_config_t  master_cell_group;
}wnrrc_phy_ho_cfg_req_t;

/*MSG_WNRRC_PHY_HO_CNF*/
typedef struct
{ 
    u8  trans_id;
    u8  result;  /* 0 SUCC; 1 FAIL; */
    u8  padding[2];
}wnrrc_phy_ho_cfg_cnf_t;


/*MSG_PHY_WNRRC_DL_OUTOFSYNC_IND*/

/*MSG_PHY_WNRRC_DL_INSYNC_IND*/


/*MSG_WNRRC_PHY_READ_MIBSIB1_REQ*/
typedef struct{
    u8                     read_type;/*nrrc_phy_mibsib1_read_type_e*/
    u8                     padding[3];
    nrrc_phy_cell_info_t   cell_info;
}nrrc_phy_read_mibsib1_req_t;

/*MSG_WNRRC_PHY_READ_SI_REQ*/
typedef struct{
    u8                                   pos_schdl_r16_valid:1;
    u8                                   si_schdl_info_r17_list_valid:1;
    u8                                   rsv:6;
    u8                                   si_win_len;
    u8                                   si_schdl_info_num;
    u8                                   pos_scddl_info_num;
    u8                                   si_schdl_r17_num;
    u8                                   padding[3];
    wnrrc_si_schdl_schdl_info_t          si_schdl_info_list[MAX_NR_SI_MSG_NUM];
    wnrrc_pos_schdl_info_r16_t           pos_schdl_r16_list[MAX_NR_SI_MSG_NUM];
    wnrrc_si_schdl_info2_r17_t           si_schdl_info_r17_list[MAX_NR_SI_MSG_NUM];
}nrrc_phy_read_other_si_req_t;

/*MSG_PHY_WNRRC_MIB_IND*/
typedef struct{
    nrrc_phy_cell_info_t  cell_info;
    nr_mib_info_t         mib;
}phy_nrrc_mib_ind_t;

/*MSG_PHY_WNRRC_SIB1_IND*/
typedef struct{
    nr_si_buffer_t sib1;
}phy_nrrc_sib1_ind_t;

/*MSG_PHY_WHRRC_SI_DATA_IND*/
typedef struct{
    nr_si_buffer_t si_data;
}phy_nrrc_si_ind_t;


/*MSG_WNRRC_PHY_STOP_READ_SI_IND*/


/*MSG_WNRRC_PHY_CELL_SEARCH_REQ*/
typedef struct{
    u8        trans_id;
    u8        search_type;/*enumerate refer to nrrc_phy_search_type_e*/
    u8        sort_priority;/*enumerate refer to wnrrc_cell_sort_priority_e*/
    u8        band_num;
    u8        cell_num;
    u8        arfcn_num;
    u8        padding[2];
    u16                            band_list_ind[MAX_NR_CELL_SEARCH_BAND_NUM];
    nrrc_phy_cell_info_t           store_cell_list[MAX_NR_CELL_SEARCH_CELL_NUM];
    u16                            store_arfcn_list[MAX_NR_CELL_SEARCH_ARFCN_NUM];
}wnrrc_phy_cell_search_req_t;

/*MSG_WNRRC_PHY_SEARCH_NEXT_REQ/*/
typedef struct 
{
    u16  trans_id;
    u16  padding;
}wnrrc_phy_search_next_req_t;

/*MSG_WNRRC_PHY_STOP_SEARCH_IND*/
typedef struct 
{
    u16  trans_id;
    u16  padding;
}wnrrc_phy_stop_search_ind_t;


/*MSG_WNRRC_PHY_STOP_READ_SI_IND*/


/*MSG_WNRRC_PHY_CELL_SEARCH_CNF/MSG_WNRRC_PHY_SEARCH_NEXT_CNF*/
typedef struct
{
    u8       trans_id; /*[0,254]*/ 
    u8       result_ind;/*enumerate refer to nrrc_phy_result_ind_e*/
    u8       is_search_end;/*1 means that physical layer completed the searching of all required cell.
                             0 means that physical layer hasn't completed the searching.
                           */
    u8       failure_cause; /* enumerate refer to nrrc_phy_cell_search_fail_cause_e*/
    u8       cell_num;
    u8       padding[3];
    nrrc_phy_cell_info_t  cellinfo_list[MAX_NR_CELL_SEARCH_CELL_NUM]; /*The cell information physical layer has found.*/
}wnrrc_phy_cell_search_cnf_t;


/*MSG_WNRRC_PHY_CAMP_ON_REQ*/
typedef struct{
    u8                                  serv_cell_cfg_common_sib_cfg_flag:1;
    u8                                  ue_tmr_val_cfg_flag:1;
    u8                                  ntn_cfg_flag:1;
    u8                                  si_schdl_cfg_flag:1;
    u8                                  sib1_ext_flag:1;
    u8                                  rsv:3;
    u8                                  padding[3];
    wnrrc_serv_cell_cfg_comm_sib_t      serv_cell_cfg_common_sib;
    wnrrc_ue_tmr_and_cons_t             ue_tmr_val;
    wnrrc_sib19_info_t                  ntn_cfg;
    wnrrc_si_schdl_info_t               si_schdl_cfg;
    nr_sib1_v1610_t                     sib1_ext;
}nrrc_phy_camp_on_req,nrrc_phy_idle_cell_cfg_req;


/*MSG_WNRRC_PHY_CAMP_ON_CNF*/
typedef struct{
    u8                result_ind;/*SUCC/FAIL*/
    u8                padding[3];
}nrrc_phy_camp_on_cnf_t;


/*MSG_WNRRC_PHY_IDLE_MEAS_CFG_IND*/
typedef struct{
    u8                      sib2_cfg_flag:1;
    u8                      sib3_cfg_flag:1;
    u8                      sib4_cfg_flag:1;
    u8                      rsv:5;
    u8                      padding[3];
    wnrrc_sib2_info_t       sib2;
    wnrrc_sib3_info_t       sib3;
    wnrrc_sib4_info_t       sib4;
}nrrc_phy_idle_measurement_cfg_ind_t;


/*MSG_WNRRC_PHY_BG_CELL_SEARCH_REQ*/
typedef struct{
    u8        trans_id;
    u8        search_type;/*enumerate refer to nrrc_phy_search_type_e*/
    u8        sort_priority;/*enumerate refer to wnrrc_cell_sort_priority_e*/
    u8        band_num;
    u8        cell_num;
    u8        arfcn_num;
    u8        padding[2];
    u16                            band_list_ind[MAX_NR_CELL_SEARCH_BAND_NUM];
    nrrc_phy_cell_info_t           store_cell_list[MAX_NR_CELL_SEARCH_CELL_NUM];
    u16                            store_arfcn_list[MAX_NR_CELL_SEARCH_ARFCN_NUM];
}wnrrc_phy_bg_cell_search_req_t;

/*WNRRC_PHY_BG_SEARCH_NEXT_REQ*/
typedef struct 
{
    u16  trans_id;
    u16  padding;
}wnrrc_phy_bg_search_next_req_t;

/*WNRRC_PHY_STOP_BG_SEARCH_IND*/
typedef struct 
{
    u16  trans_id;
    u16  padding;
}wnrrc_phy_stop_bg_search_ind_t;


/*MSG_WNRRC_PHY_BG_CELL_SEARCH_CNF/MSG_WNRRC_PHY_BG_SEARCH_NEXT_CNF*/
typedef struct
{
    u8       trans_id; /*[0,254]*/ 
    u8       result_ind;/*enumerate refer to nrrc_phy_result_ind_e*/
    u8       is_search_end;/*1 means that physical layer completed the searching of all required cell.
                             0 means that physical layer hasn't completed the searching.
                           */
    u8       failure_cause; /* enumerate refer to nrrc_phy_cell_search_fail_cause_e*/
    u8       cell_num;
    u8       padding[3];
    nrrc_phy_cell_info_t  cellinfo_list[MAX_NR_CELL_SEARCH_CELL_NUM]; /*The cell information physical layer has found.*/
}nrrc_phy_bg_cell_search_cnf_t;


/*MSG_WNRRC_PHY_BG_READ_MSI_REQ*/
typedef struct{
    u8                     read_type;/*nrrc_phy_mibsib1_read_type_e*/
    u8                     padding[3];
    nrrc_phy_cell_info_t   cell_info;
}nrrc_phy_bg_read_mibsib1_req_t;


/*MSG_WNRRC_PHY_STOP_BG_READ_MSI_IND*/


/*MSG_PHY_WNRRC_PAGING_IND*/
typedef struct
{
    u16  pch_data_length;
    u16  padding;
    u8   pch_data[200];
}phy_wnrrc_page_ind_t;

/*MSG_WNRRC_PHY_UEID_INFO_IND*/
typedef struct
{
    u8 vaild_flag;/*TRUE/FALSE*/
    u8  s_tmsi[6]; 
}wnrrc_phy_ueid_info_ind_t;

/*MSG_WNRRC_PHY_READ_CGI_SI_REQ*/
typedef struct{
    u8                     read_type;/*nrrc_phy_mibsib1_read_type_e*/
    u8                     padding[3];
    nrrc_phy_cell_info_t   cell_info;
}nrrc_phy_cgi_read_mibsib1_req_t;


/*TODO*/
/*MSG_WNRRC_PHY_MEAS_CONTROL_REQ*/
/*MSG_WNRRC_PHY_MEAS_CONTROL_CNF*/
/*MSG_PHY_WNRRC_INTERF_MEAS_REPORT_IND*/
/*MSG_PHY_WNRRC_INTRAF_MEAS_REPORT_IND*/
/*MSG_PHY_WNRRC_S_IND*/
/*MSG_PHY_WNRRC_IDLE_MEASEVA_IND*/
/*TODO*/

/***********************************************************************************************************************
*  GLOBAL VARIABLES DECLARATION
***********************************************************************************************************************/


/***********************************************************************************************************************
*  GLOBAL CONSTANT VARIABLES DECLARATION
***********************************************************************************************************************/



/***********************************************************************************************************************
*  GLOBAL FUNCTION PROTOTYPE DECLARATION
***********************************************************************************************************************/


/**********************************************************************************************************************/
#endif 

/********************************* END OF FILE ************************************************************************/

