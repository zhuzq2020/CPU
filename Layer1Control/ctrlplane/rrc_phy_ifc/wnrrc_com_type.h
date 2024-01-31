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
#ifndef WNRRC_PHY_COM_H
#define WNRRC_PHY_COM_H

/***********************************************************************************************************************
*  INCLUDE FILES
***********************************************************************************************************************/
//#include "oal_thread.h"
//#include "oal_msg.h"
#include "../../l1c_typedef.h"

/***********************************************************************************************************************
*  MACRO DEFINITION
***********************************************************************************************************************/




/***********************************************************************************************************************
*  TYPE DEFINITION
***********************************************************************************************************************/
#define MAX_NR_MULTI_BAND_NUM                         8
#define MAX_NR_NS_PMAX_NUM                            8
#define MAX_NR_SCS_NUM                                5
#define MAX_NR_TCI_STATE_PDCCH                        64
#define MAX_NR_DL_ALLOC_NUM                           16
#define MAX_NR_UL_ALLOC_NUM                           16
#define MAX_NR_ACCESS_CAT                             64
#define MAX_NR_PLMN_NUM                               12
#define MAX_NR_BAR_INFO_SET_NUM                       8
#define MAX_NR_SIB_NUM                                32
#define MAX_NR_SI_MSG_NUM                             32
#define MAX_NR_CELL_NTN_R17_NUM                       4
#define MAX_NR_PCI_NUM_PER_SMTC                       64
#define MAX_NR_TAC_R17_NUM                            12
#define MAX_NR_CELL_INTRA_NUM                         16
#define MAX_NR_CELL_EXCLUDE_NUM                       16
#define MAX_NR_CELL_ALLOW_NUM                         16
#define MAX_NR_CAG_CELL_R16_NUM                       16
#define MAX_NR_FREQ_NUM                               8
#define MAX_NR_CELL_INTER_NUM                         16


#define MAX_NR_CELL_SEARCH_ARFCN_NUM                  100
#define MAX_NR_CELL_SEARCH_GSCN_NUM                   100
#define MAX_NR_CELL_SEARCH_CELL_NUM                   100
#define MAX_NR_CELL_SEARCH_BAND_NUM                   100
#define MAX_NR_SI_SIZE                                372  //According to 38.331 5.2.1, the maximum SIB1 or SI message size is 2976 bits
#define SUCC                                          0
#define FAIL                                          1
#define MAX_NR_OF_SCCELLS                             2 //max value should be 31 in 38.331
#define MAX_NR_OF_SERVING_CELLS_TCI_R16               32
#define MAX_NR_OF_SERVING_CELLS                       32
#define MAX_NR_OF_REQ_COM_DC_LOCATION_R17             128
#define MAX_NR_OF_ENH_TYPE3_HARQ_ACK_R17              8
#define MAX_NR_OF_SLOTS                               320    
#define SEMISTASTIC                                   0
#define DYNAMIC                                       1
#define MAX_NR_OF_RATE_MATCH_PATTERNS                 4
#define MAX_SIMULTANEOUS_BANDS                        32
#define MAX_NR_OF_MULTI_BANDS                         8
#define MAX_SCSS                                      5
#define MAX_NR_OF_TCI_STATES_PDCCH                    64
#define MAX_NR_OF_TCI_STATES                          128
#define MAX_NR_OF_DL_ALLOCATIONS                      16
#define MAX_NR_OF_RATE_MATCH_PATTERNS_PERGROUP        8
#define MAX_NR_OF_ZP_CSI_RS_RESOURCES                 32




/**********************sib1 parameters start**********************/
typedef struct{
    u8            q_rx_lev_min_offset_valid:1;
    u8            q_rx_lev_min_sul_valid:1;
    u8            q_qual_min_valid:1;
    u8            q_qual_min_offset_valid:1;
    u8            rsv:4;
    s8            q_rx_lev_min;/*-70...-22*/
    u8            q_rx_lev_min_offset;/*1..8*/
    s8            q_rx_lev_min_sul;/*-70...-22*/
    s8            q_qual_min;/*-43...-12*/
    u8            q_qual_min_offset;/*1...8*/
    u8            padding[2];
}wnrrc_cell_select_info_t;

typedef struct{
    u8            mcc[3];/*integer 0...9*/
    u8            padding;
    u8            mnc[3];/*integer 0...9,0xff invalid*/
    u8            padding1;
}wnrrc_plmn_id_t;

typedef struct{
    u8                           tac_valid:1;
    u8                           ranac_valid:1;
    u8                           tac_list_r17_valid:1;
    u8                           g_nb_id_len_r17_valid:1;
    u8                           rsv:4;
    u8                           plmn_id_num;
    u8                           tac_r17_num;/*1...12*/    
    u8                           ranac;/*0...255*/
    wnrrc_plmn_id_t              plmn_id_list[MAX_NR_PLMN_NUM];
    u32                          tac;/*bit string 24 bits */
    u64                          cell_id;/*bit string 36bits*/
    bool                         cell_rsv_for_operator_use;
    u32                          tac_list_r17[MAX_NR_TAC_R17_NUM];
    u8                           g_nb_id_len_r17;/*22...32*/
    u8                           padding[3];
}wnrrc_plmn_id_info_t;

typedef struct{
    u8                        plmn_num;
    u8                        padding[3];
    wnrrc_plmn_id_info_t      plmn_id_info_list[MAX_NR_PLMN_NUM];
    bool                      cell_rsv_for_other;
    bool                      cell_rsv_for_future_r16;
}wnrrc_cell_access_info_t;

typedef enum{
    WNRRC_CONN_EST_FAIL_CTRL_CNT_N1    = 0,
    WNRRC_CONN_EST_FAIL_CTRL_CNT_N2,
    WNRRC_CONN_EST_FAIL_CTRL_CNT_N3,
    WNRRC_CONN_EST_FAIL_CTRL_CNT_N4
}wnrrc_conn_est_fail_ctrl_cnt_e;

typedef enum{
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S30     = 0,
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S60,
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S120,
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S240,
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S300,
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S420,
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S600,
    WNRRC_CONN_EST_FAIL_CTRL_OFFSET_VALIDITY_S900
}wnrrc_conn_est_fail_ctrl_offset_valid_e;

typedef struct{
    u8         fail_offset_valid:1;
    u8         rsv:7;
    u8         fail_count;/*enumerate refer to wnrrc_conn_est_fail_ctrl_cnt_e*/
    u8         fail_offset_validity;/*enumerate refer to wnrrc_conn_est_fail_ctrl_offset_valid_e*/
    u8         fail_offset;/*0...15*/
}wnrrc_conn_est_fail_ctrl_t;

typedef enum{
    WNRRC_SI_BROADCAST_STATUS_ING   = 0,
    WNRRC_SI_BROADCAST_STATUS_NOT_ING
}wnrrc_si_broadcast_status_e;

typedef enum{
    WNRRC_SI_PERIOD_RF8      = 0,
    WNRRC_SI_PERIOD_RF16,
    WNRRC_SI_PERIOD_RF32,
    WNRRC_SI_PERIOD_RF64,
    WNRRC_SI_PERIOD_RF128,
    WNRRC_SI_PERIOD_RF256,
    WNRRC_SI_PERIOD_RF512
}wnrrc_si_period_e;

typedef enum{
    WNRRC_SI_TYPE_2    = 0,
    WNRRC_SI_TYPE_3,
    WNRRC_SI_TYPE_4,
    WNRRC_SI_TYPE_5,
    WNRRC_SI_TYPE_6,
    WNRRC_SI_TYPE_7,
    WNRRC_SI_TYPE_8,
    WNRRC_SI_TYPE_9,
    WNRRC_SI_TYPE_10,
    WNRRC_SI_TYPE_11,
    WNRRC_SI_TYPE_12,
    WNRRC_SI_TYPE_13,
    WNRRC_SI_TYPE_14
}wnrrc_si_type_e;

typedef struct{
    u8          value_tag_valid:1;
    u8          area_scope_valid:1;
    u8          rsv:6;
    u8          type;/*enumerate refer to wnrrc_si_type_e*/
    u8          value_tag;
    u8          padding;
    bool        area_scope;
}wnrrc_sib_type_info_t;

typedef struct{
    u8                         sib_type_num;
    u8                         padding[3];
    wnrrc_sib_type_info_t      sib_type_info[MAX_NR_SI_MSG_NUM];
}wnrrc_sib_mapping_t;

typedef struct{
    u8                        si_broadcast_status;/*enumerate refer to wnrrc_si_broadcast_status_e*/
    u8                        si_period;/*enumerate refer to wnrrc_si_period_e*/
    u8                        padding[2];
    wnrrc_sib_mapping_t       sib_mapping;
}wnrrc_si_schdl_schdl_info_t;

typedef enum{
    WNRRC_SI_WIN_LEN_S5       = 0,
    WNRRC_SI_WIN_LEN_S10,
    WNRRC_SI_WIN_LEN_S20,
    WNRRC_SI_WIN_LEN_S40,
    WNRRC_SI_WIN_LEN_S80,
    WNRRC_SI_WIN_LEN_S160,
    WNRRC_SI_WIN_LEN_S320,
    WNRRC_SI_WIN_LEN_S640,
    WNRRC_SI_WIN_LEN_S1280,
    WNRRC_SI_WIN_LEN_S2560,
    WNRRC_SI_WIN_LEN_S5120
}wnrrc_si_win_len_e;

typedef struct{
    u8           prach_cfg_period_scaling_iab_r16_valid:1;
    u8           prach_cfg_frame_offset_iab_r16_valid:1;
    u8           prach_cfg_s_offset_iab_r16_valid:1;
    u8           ra_rsp_window_v1610_valid:1;
    u8           prach_cfg_idx_v1610_valid:1;
    u8           ra_rsp_window_v1700_valid:1;
    u8           rsv:2;
    u8           prach_cfg_idx;/*0...255*/
    u8           msg1_FDM;/*refer to nr_rach_generic_msg1_fdm_e*/
    u16          msg1_fre_start;/* 0...274*/
    u8           zero_zone_cfg;/*0...15*/
    s8            preamble_recv_target_pwr;/*-220...-60*/
    u8           preamble_trans_max;/*enumerate refer to nr_preamble_trans_max_e*/
    u8           pwr_ramping_step;/*enumerate refer to nr_ra_pwr_ramping_step_e*/
    u8           ra_rsp_window;/*enumerate refer to nr_ra_rsp_win_e*/
    u8           prach_cfg_period_scaling_iab_r16;/*enumerate refer to nr_ra_prach_cfg_period_scaling_iab_r16_e*/
    u8           prach_cfg_frame_offset_iab_r16;/*0...63 */
    u8           prach_cfg_s_offset_iab_r16;/*0...39*/
    u8           ra_rsp_window_v1610;/*enumerate refer to nr_ra_rsp_win_v1610_e*/
    u16          prach_cfg_idx_v1610;/*256...262*/
    u8           ra_rsp_window_v1700;/*enumrate refer to nr_ra_rsp_win_v1700_e*/
}nr_rach_generic_t;


typedef struct{
    nr_rach_generic_t    rach_generic;
    u8                   ssb_per_ro;/*enumerate refer to nr_ssb_per_ro_e*/
    u8                   padding[3];
}wnrrc_rach_occasion_si_t;

typedef enum
{
    WNRRC_SI_REQ_PERIOD_1   = 0,
    WNRRC_SI_REQ_PERIOD_2,
    WNRRC_SI_REQ_PERIOD_4,
    WNRRC_SI_REQ_PERIOD_6,
    WNRRC_SI_REQ_PERIOD_8,
    WNRRC_SI_REQ_PERIOD_10,
    WNRRC_SI_REQ_PERIOD_12,
    WNRRC_SI_REQ_PERIOD_16
}wnrrc_si_req_period_e;

typedef struct{
    u8                                 ra_assoc_period_idx_valid:1;
    u8                                 ra_ssb_ocn_mask_idx_valid:1;
    u8                                 rsv:6;
    u8                                 ra_preamble_start_idx;/*0...63*/
    u8                                 ra_assoc_period_idx;/*0...15*/
    u8                                 ra_ssb_ocn_mask_idx;/*0...15*/
}wnrrc_si_req_res_t;

typedef struct{
    u8                                 rach_occasion_valid:1;
    u8                                 si_req_period_valid:1;
    u8                                 rsv:6;
    u8                                 si_req_period;/*enumerate refer to wnrrc_si_req_period_e*/
    u8                                 padding;
    u8                                 si_res_num;
    wnrrc_rach_occasion_si_t           rach_occasion;
    wnrrc_si_req_res_t                 si_req_res[MAX_NR_SI_MSG_NUM];
}wnrrc_si_req_cfg_t;

typedef struct{
    u8                    pmax_valid:1;
    u8                    rsv:7;
    s8                    pmax;/*-30...33*/
    u8                    addition_spectrum_emission;/*0...7*/
    u8                    padding;
}nr_ns_pmax_val_t;

typedef struct{
    u8                    band_ind_valid:1;
    u8                    pmax_list_valid:1;
    u8                    rsv:6;
    u16                   band_ind;/*1...1024*/
    u8                    pmax_num;
    nr_ns_pmax_val_t      pmax_list[MAX_NR_NS_PMAX_NUM];
}wnrrc_multi_band_info_sib_t;

typedef enum{
    WNRRC_SCS_KHZ_15    = 0,
    WNRRC_SCS_KHZ_30,
    WNRRC_SCS_KHZ_60,
    WNRRC_SCS_KHZ_120,
    WNRRC_SCS_KHZ_240,
    WNRRC_SCS_KHZ_480_V1700,
    WNRRC_SCS_KHZ_960_V1700
}wnrrc_scs_e;

typedef struct{
    u16                   offset_to_carrier;/*0...2199*/
    u8                    scs;/*enumrate refer to wnrrc_scs_e*/
    u8                    padding;
    u16                   carrier_bw;/*1...275*/
    u16                   tx_direc_curr_location;/*0...4095*/
}wnrrc_scs_spec_carrier_t;


typedef struct{
    u8                                     multi_freq_band_num;
    u8                                     scs_spec_carrier_num;
    u16                                    offset_to_pointA;/*0...2199*/
    wnrrc_multi_band_info_sib_t            multi_freq_band_list[MAX_NR_MULTI_BAND_NUM];
    wnrrc_scs_spec_carrier_t               scs_spec_carrier_list[MAX_NR_SCS_NUM];
}wnrrc_freq_info_dl_sib_t;

typedef struct{
    u8                 cp_ext_valid:1;
    u8                 rsv:7;
    u16                loc_bw;/*location and bandwith , value range is 0...37949*/
    u8                 scs;/*enumerate refer to wnrrc_scs_e*/
    bool               cp_ext;/*cyclic prefix extended use*/
}wnrrc_bwp_t;

typedef enum{
    WNRRC_CCE_REG_INTERLEAVE_BUNDLE_SIZE_N2   = 0,
    WNRRC_CCE_REG_INTERLEAVE_BUNDLE_SIZE_N3,
    WNRRC_CCE_REG_INTERLEAVE_BUNDLE_SIZE_N6
}wnrrc_cce_reg_interleave_bundle_size_e;

typedef enum{
    WNRRC_CCE_REG_INTERLEAVE_SIZE_N2    = 0,
    WNRRC_CCE_REG_INTERLEAVE_SIZE_N3,
    WNRRC_CCE_REG_INTERLEAVE_SIZE_N6
}wnrrc_cce_reg_interleave_size_e;

typedef struct{
    u8         shift_idx_valid:1;
    u8         rsv:7;
    u8         reg_bundle_size;/*enumerate refer to wnrrc_cce_reg_interleave_bundle_size_e*/
    u8         interleave_size;/*enumerate refer to wnrrc_cce_reg_interleave_size_e*/
    u8         shift_idx;/*0...274*/
}wnrrc_cce_reg_interleave_info_t;

typedef enum{
    WNRRC_PRECODER_GRANULARITY_SAME_AS_REG_BUNDLE     = 0,
    WNRRC_PRECODER_GRANULARITY_ALL_CONTIGUOUS_RBS
}wnrrc_precoder_granularity_e;

typedef struct{
    u32                               cce_reg_interleave_valid:1;
    u32                               tci_present_in_dci_valid:1;
    u32                               pdcch_dmrs_scram_id_valid:1;
    u32                               rb_offset_r16_valid:1;
    u32                               tci_present_dci_1_2_valid:1;
    u32                               ctrl_res_set_id_v1610_valid:1;
    u32                               follow_unified_tci_r17_valid:1;
    u32                               rsv:25;
    u8                                ctrl_res_set_id;/*0...11*/
    u8                                precoder_granularity;/*enumerate refer to wnrrc_precoder_granularity_e*/
    u8                                tci_state_id_num;
    u8                                duration;/*1..3*/
    u64                               freq_res;/*bit string length is 45 bit*/
    wnrrc_cce_reg_interleave_info_t   cce_reg_interleave;
    u8                                tci_state_id_list[MAX_NR_TCI_STATE_PDCCH];/*0...127*/
    bool                              tci_present_in_dci;/*TRUE: enable, FALSE: disable*/
    u16                               pdcch_dmrs_scram_id;/*0...65535*/
    u8                                rb_offset_r16;/*0...5*/
    u8                                tci_present_dci_1_2;/*1...3*/
    u8                                coreset_pool_idx;/*0...1*/
    u8                                ctrl_res_set_id_v1610;/*12...15*/
    u8                                padding[2];
    bool                              follow_unified_tci_r17;/*TRUE: enable, FALSE: disable*/
}wnrrc_ctrl_res_set_t;

typedef enum{
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_1      = 0,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_2,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_4,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_5,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_8,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_10,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_16,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_20,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_40,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_80,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_160,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_320,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_640,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_1280,
    WNRRC_SEARCH_SPACE_MONITOR_SLOT_PERIOD_SL_2560
}wnrrc_search_space_monitor_slot_period_e;

typedef enum{
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_0     = 0,
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_1,
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_2,
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_3,
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_4,
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_5,
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_6,
    WNRRC_SEARCH_SPACE_AGGREGATION_NUM_8
}wnrrc_search_space_aggregation_num_e;

typedef struct{
    u8         aggre_level1;/*enumerate refer to wnrrc_search_space_aggregation_num_e*/
    u8         aggre_level2;/*enumerate refer to wnrrc_search_space_aggregation_num_e*/
    u8         aggre_level4;/*enumerate refer to wnrrc_search_space_aggregation_num_e*/
    u8         aggre_level8;/*enumerate refer to wnrrc_search_space_aggregation_num_e*/
    u8         aggre_level16;/*enumerate refer to wnrrc_search_space_aggregation_num_e*/
    u8         padding[3];
}wnrrc_search_space_candi_num_t;

typedef enum{
    WNRRC_SEARCH_SPACE_SFI_AGGREGATION_NUM_1   = 0,
    WNRRC_SEARCH_SPACE_SFI_AGGREGATION_NUM_2
}wnrrc_search_space_sfi_aggregation_num_e;

typedef struct{
    u8         sfi_aggre_level1_valid:1;
    u8         sfi_aggre_level2_valid:1;
    u8         sfi_aggre_level4_valid:1;
    u8         sfi_aggre_level8_valid:1;
    u8         sfi_aggre_level16_valid:1;
    u8         rsv:3;
    u8         sfi_aggre_level1;/*enumerate refer to wnrrc_search_space_sfi_aggregation_num_e*/
    u8         sfi_aggre_level2;/*enumerate refer to wnrrc_search_space_sfi_aggregation_num_e*/
    u8         sfi_aggre_level4;/*enumerate refer to wnrrc_search_space_sfi_aggregation_num_e*/
    u8         sfi_aggre_level8;/*enumerate refer to wnrrc_search_space_sfi_aggregation_num_e*/
    u8         sfi_aggre_level16;/*enumerate refer to wnrrc_search_space_sfi_aggregation_num_e*/
    u8         padding[2];
}wnrrc_search_space_candi_sfi_t;

typedef struct{
    wnrrc_search_space_candi_sfi_t    candi_sfi_num;
}wnrrc_search_space_type_dci_format_2_0_t;

typedef enum{
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_1     = 0,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_2,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_4,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_5,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_8,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_10,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_16,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY1_SL_20
}wnrrc_search_space_type_dci_2_3_dummy1_e;

typedef enum{
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY2_N_1     = 0,
    WNRRC_SEARCH_SPACE_TYPE_DCI_2_3_DUMMY2_N_2
}wnrrc_search_space_type_dci_2_3_dummy2_e;


typedef struct{
    u8         dummy1_valid:1;
    u8         rsv:7;
    u8         dummy1;/*enumerate refer to wnrrc_search_space_type_dci_2_3_dummy1_e*/
    u8         dummy2;/*enumerate refer to wnrrc_search_space_type_dci_2_3_dummy2_e*/
    u8         padding;
}wnrrc_search_space_type_dci_format_2_3_t;

typedef struct{
    u8                                           dci_2_3_valid:1;
    u8                                           rsv:7;
    u8                                           padding[3];
    wnrrc_search_space_type_dci_format_2_0_t     dci_2_0;
    wnrrc_search_space_type_dci_format_2_3_t     dci_2_3;
}wnrrc_search_space_common_t;

typedef enum{
    WNRRC_SEARCH_SPACE_UE_SPEC_DCI_FORMATS_0_0_AND_1_0   = 0,
    WNRRC_SEARCH_SPACE_UE_SPEC_DCI_FORMATS_0_1_AND_1_1
}wnrrc_search_space_ue_spec_dci_formats_e;

typedef enum{
    WNRRC_SEARCH_SPACE_UE_SPEC_DCI_FORMATS_MT_R16_2_5  = 0,
}wnrrc_search_space_ue_spec_dci_formats_mt_r16_e;

typedef enum{
    WNRRC_SEARCH_SPACE_UE_SPEC_DCI_FORMATS_EXT_R16_0_2_AND_1_2    = 0,
    WNRRC_SEARCH_SPACE_UE_SPEC_DCI_FORMATS_EXT_R16_0_1_AND_1_1_AND_0_2_AND_1_2
}wnrrc_search_space_ue_spec_dci_formats_ext_r16_e;

typedef struct{
    u8        dci_formats_mt_r16_valid:1;
    u8        dci_formats_ext_r16_valid:1;
    u8        rsv:6;
    u8        dci_formats;/*enumerate refer to wnrrc_search_space_ue_spec_dci_formats_e*/
    u8        dci_formats_mt_r16;/*enumerate refer to wnrrc_search_space_ue_spec_dci_formats_mt_r16_e*/
    u8        dci_formats_ext_r16;/*enumerate refer to wnrrc_search_space_ue_spec_dci_formats_ext_r16_e*/
}wnrrc_search_space_ue_spec_t;

typedef enum{
    WNRRC_SEARCH_SPACE_TYPE_COMMON  = 0,
    WNRRC_SEARCH_SPACE_TYPE_UE_SPEC,
}wnrrc_search_space_type_e;

typedef struct{
    u8                             type;/*0: common,  1:ue-specific*/
    u8                             padding[3];
    union{
        wnrrc_search_space_common_t    common;
        wnrrc_search_space_ue_spec_t   ue_spec;
    }u;
}wnrrc_search_space_type_t;

typedef struct{
    u8                                 ctrl_res_set_id_valid:1;
    u8                                 monitor_slot_period_offset_valid:1;
    u8                                 duration_valid:1;
    u8                                 nr_of_candidates_valid:1;
    u8                                 search_space_type_valid:1;
    u8                                 monitor_sym_within_slot_valid:1;
    u8                                 rsv:2;
    u8                                 search_space_id;/*0...39*/
    u8                                 ctrl_res_set_id;/*0...11*/
    u8                                 monitor_slot_period;/*enumerate refer to wnrrc_search_space_monitor_slot_period_e*/
    u16                                monitor_slot_offset;/*refer to period*/
    u16                                duration;/*2...2559*/
    u8                                 num_bits_monitor_sym_within_slot;
    u8                                 monitor_sym_within_slot[2];/*bit string 14*/
    u8                                 padding1;
    wnrrc_search_space_candi_num_t     nr_of_candidates;
    wnrrc_search_space_type_t          search_space_type;
}wnrrc_search_space_t;

typedef enum{
    WNRRC_SEARCH_SPACE_MONITOR_PERIOD_V1710_SL_32     = 0,
    WNRRC_SEARCH_SPACE_MONITOR_PERIOD_V1710_SL_64,
    WNRRC_SEARCH_SPACE_MONITOR_PERIOD_V1710_SL_128,
    WNRRC_SEARCH_SPACE_MONITOR_PERIOD_V1710_SL_5120,
    WNRRC_SEARCH_SPACE_MONITOR_PERIOD_V1710_SL_10240,
    WNRRC_SEARCH_SPACE_MONITOR_PERIOD_V1710_SL_20480
}wnrrc_search_space_monitor_period_v1710_e;

typedef enum{
    WNRRC_SEARCH_SPACE_AGGREGATION_R16_NUM_1   = 0,
    WNRRC_SEARCH_SPACE_AGGREGATION_R16_NUM_2
}wnrrc_search_space_aggre_level_r16_e;

typedef struct{
    u8         aggre_lev1_r16_valid:1;
    u8         aggre_lev2_r16_valid:1;
    u8         aggre_lev4_r16_valid:1;
    u8         aggre_lev8_r16_valid:1;
    u8         aggre_lev16_r16_valid:1;
    u8         rsv:3;
    u8         aggre_lev1_r16;/*enumerate refer to wnrrc_search_space_aggre_level_r16_e*/
    u8         aggre_lev2_r16;/*enumerate refer to wnrrc_search_space_aggre_level_r16_e*/
    u8         aggre_lev4_r16;/*enumerate refer to wnrrc_search_space_aggre_level_r16_e*/
    u8         aggre_lev8_r16;/*enumerate refer to wnrrc_search_space_aggre_level_r16_e*/
    u8         aggre_lev16_r16;/*enumerate refer to wnrrc_search_space_aggre_level_r16_e*/
    u8         padding[2];
}wnrrc_search_space_candi_ci_r16_t;

typedef struct{
    wnrrc_search_space_candi_ci_r16_t        candi_ci_r16;
}wnrrc_search_space_type_com_dci_2_4_r16_t;

typedef struct{
    u8                                             dci_2_4_r16_valid:1;
    u8                                             dci_2_5_r16_valid:1;
    u8                                             rsv:6;
    u8                                             padding[3];
    wnrrc_search_space_type_com_dci_2_4_r16_t      dci_2_4_r16;
//    wnrrc_search_space_type_com_dci_2_5_r16_t      dci_2_5_r16;
}wnrrc_search_space_type_common_r16_t;

typedef struct{
    wnrrc_search_space_type_common_r16_t  common_r16;
}wnrrc_search_space_type_r16_t;

typedef struct{
    u8                                   ctrl_res_set_id_r16_valid:1;
    u8                                   search_space_group_id_list_valid:1;
    u8                                   freq_moni_loc_r16_valid:1;
    u8                                   rsv:5;
    u8                                   ctrl_res_set_id_r16;/*0...15*/
    u8                                   padding[2];
    wnrrc_search_space_type_r16_t        type_r16;
    u8                                   search_space_group_id_r16_num;
    u8                                   search_space_group_id_list[2];/*array elem value rang is 0...1*/
    u8                                   freq_moni_loc_r16;/*bit string 5bits*/
}wnrrc_search_space_ext_r16_t;

typedef struct{
    bool                     new_search_space_exist;
    wnrrc_search_space_t     new_search_space;
    u8                       exist_search_space_id;/*0...39*/
    u8                       padding[3];
}wnrrc_search_space_sdt_r17_t;

typedef enum{
    WNRRC_SEARCH_SPACE_AGGREGATION_R17_NUM_0   = 0,
    WNRRC_SEARCH_SPACE_AGGREGATION_R17_NUM_1,
    WNRRC_SEARCH_SPACE_AGGREGATION_R17_NUM_2,
    WNRRC_SEARCH_SPACE_AGGREGATION_R17_NUM_3,
    WNRRC_SEARCH_SPACE_AGGREGATION_R17_NUM_4
}wnrrc_search_space_aggre_level_r17_e;

typedef struct{
    u8           aggre_lev4_r17_valid:1;
    u8           aggre_lev8_r17_valid:1;
    u8           aggre_lev16_r17_valid:1;
    u8           rsv:5;
    u8           aggre_lev4_r17;/*enumerate refer to wnrrc_search_space_aggre_level_r17_e*/
    u8           aggre_lev8_r17;/*enumerate refer to wnrrc_search_space_aggre_level_r17_e*/
    u8           aggre_lev16_r17;/*enumerate refer to wnrrc_search_space_aggre_level_r17_e*/
}wnrrc_search_space_candi_pei_r17_t;

typedef struct{
    wnrrc_search_space_candi_pei_r17_t       candi_pei_r17;
}wnrrc_search_space_type_com_dci_2_7_r17_t;

typedef struct{
    wnrrc_search_space_type_com_dci_2_7_r17_t  dci_2_7_r17;
}wnrrc_search_space_type_common_r17_t;

typedef struct{
    wnrrc_search_space_type_common_r17_t  common_r17;
}wnrrc_search_space_type_r17_t;

typedef enum{
    WNRRC_MONITOR_SLOTS_GROUP_R17_LEN_4   = 0,
    WNRRC_MONITOR_SLOTS_GROUP_R17_LEN_8
}wnrrc_monitor_slots_group_r17_len_e;

typedef struct{
    u8           monitor_slot_group_r17_valid:1;
    u8           duration_r17_valid:1;
    u8           search_space_type_r17_valid:1;
    u8           search_space_gp_id_list_r17_valid:1;
    u8           search_space_link_id_r17_valid:1;
    u8           rsv:3;
    u8           monitor_period;/*enumerate refer to wnrrc_search_space_monitor_period_v1710_e*/
    u16          monitor_offset;/*according to monitor period, offset is 0...(period-1)*/
    u8           monitor_slot_group_r17_len;/*enumerate refer to wnrrc_monitor_slots_group_r17_len_e*/
    u8           monitor_slots;/*slot group len is 4->bit string len is 4, 
                                 slot group len is 8->bit string len is 8*/
    u16          duration_r17;/*4...20476*/
    u8                                search_space_link_id_r17;/*0...39*/
    u8                                padding[3];
    wnrrc_search_space_type_r17_t     search_space_type_r17;
    u8                                search_space_gp_id_list_r17_num;
    u8                                search_space_gp_id_list_r17[3];/*array element value is 0..2*/
}wnrrc_search_space_ext2_r17_t;

typedef struct{
    u8           pei_search_id;/*0...39*/
    u8           first_po_pei_r17_type;/*0:scs15Khz zone T
                                         1:scs30khz zone T - scs15khz half T
                                         2:scs60khz zone T - scs30khz half zone T - 15khz quarter T
                                         3:scs120khz zone T - scs60khz half zone T - scs30khz quarter zone T - scs15khz eighthT
                                         4:scs120khz half T - scs60khz quater T -scs30 eighth T- scs15khz sixteenh T
                                         5:scs480khz zone T - scs120khz quarter T -scs60khz eight- scs30khz sixteenthT
                                         6:scs480khz half T - scs120khz eighthT - scs60khz sixteenthT
                                         7:scs480khz quarterT - scs120khz sixteenthT
                                         8:scs480khz eigthT
                                         9:scs480kzh sixteenthT*/
    u8           po_num;/*1...4*/
    u8           padding;
    union{
        u32      scs_15[4];/*array element value is 0...139*/
        u32      scs_30_15[4];/*array element value is 0...139*/
        u32      scs_60_30_15[4];/*array element value is 0...139*/
        u32      scs_120_60_30_15[4];/*array element value is 0...139*/
        u32      scs_120_half_60_30_15[4];/*array element value is 0...139*/
        u32      scs_480_120_60_30[4];/*array element value is 0...139*/
        u32      scs_480_half_120_60[4];/*array element value is 0...139*/
        u32      scs_480_quar_120[4];/*array element value is 0...139*/
        u32      scs_480_eighth[4];/*array element value is 0...139*/
        u32      scs_480_sixteenth[4];/*array element value is 0...139*/
    }first_pei_po;
}wnrrc_pei_cfg_bwp_r17_t;


typedef struct{
    u32                        ctrl_res_set_zero_valid:1;
    u32                        ctrl_res_set_valid:1;
    u32                        search_space_zero_valid:1;
    u32                        search_space_sib1_valid:1;
    u32                        search_space_other_si_valid:1;
    u32                        paging_search_space_valid:1;
    u32                        ra_search_space_valid:1;
    u32                        first_moni_po_choice_valid:1;
    u32                        search_space_ext_r16_list_valid:1;
    u32                        search_space_sdt_r17_valid:1;
    u32                        search_space_ext2_r17_valid:1;
    u32                        first_pmo_v1710_valid:1;
    u32                        pei_bwp_r17_valid:1;
    u32                        follow_unified_tci_1720_valid:1;
    u32                        rsv:18;
    u8                         ctrl_res_set_zero;/*0...15*/
    u8                         search_space_zero;/*0...15*/
    u8                         search_space_num;
    u8                         padding;
    wnrrc_ctrl_res_set_t       ctrl_res_set;
    wnrrc_search_space_t       search_space_list[4];
    u8                         search_space_sib1;/*0...39*/
    u8                         search_space_other_si;/*0...39*/
    u8                         paging_search_space;
    u8                         ra_search_space;
    u8                         first_pmo_choice;/*0: scs15khz zoneT 
                                                  1: scs30khz zoneT-scs15khz half T
                                                  2: scs60khz zoneT-scs30khz half T scs15khz quarter T
                                                  3: scs120khz zoneT-scs60khze half T-scs30khz quarter T -scs15khz zone eighthT
                                                  4: scs120khz half T- scs60khz quarter T - scs30khz zone eighthT -scs15khz zone sixteenthT
                                                  5: scs120khz quarter T - scs60khz zone eightT - scs30khz zone sixteenT
                                                  6: scs120khz zone eighthT-scs60khz zone sixteenthT
                                                  7: scs120khz zone sixteenthT*/
    u8                        pmo_num;/*1...4*/
    u8                        padding1[2];
    union{
        u16            scs15_T[4];/*0...139*/
        u16            scs30_15[4];/*0...279*/
        u16            scs60_30_15[4];/*0...559*/
        u16            scs120T_60_30_15[4];/*0...1119*/
        u16            scs120_half_T_60_30_15[4];/*0...2239*/
        u16            scs120_qua_T_60_30[4];/*0...4479*/
        u16            scs120_ei_T_60[4];/*0...8959*/
        u16            scs120_si_T[4];/*0...17919*/
    }first_pmo;
    u8                             search_space_ext_r16_num;
    u8                             search_space_ext2_r17_num;
    u8                             first_pmo_choice_v1710;/*0:scs480khz zone eigth T
                                                            1:scs480khz zone sixteenth T*/
    u8                             pmo_rv1710_num;/*1...4*/
    wnrrc_search_space_ext_r16_t   search_space_ext_r16_list[4];
    wnrrc_search_space_sdt_r17_t   search_space_sdt_r17;
    wnrrc_search_space_ext2_r17_t  search_space_ext2_r17_list[4];
    union{
        u32         scs480_eigthT[4];
        u32         scs480_sixteenthT[4];
    }first_pmo_v1710;
    wnrrc_pei_cfg_bwp_r17_t        pei_bwp_r17;
    bool                           follow_unified_tci_1720;/*TRUE: enable, FALSE: disable*/
}wnrrc_pdcch_cfg_common_t;

typedef enum{
    WNRRC_PDSCH_TD_RES_MAP_TYPE_A = 0,
    WNRRC_PDSCH_TD_RES_MAP_TYPE_B
}wnrrc_pdsch_td_res_map_type_e;

typedef struct{
    u8           k0;/*0...32*/
    u8           map_type;/*enumerate refer to wnrrc_pdsch_td_res_map_type_e*/
    u8           start_sym_len;/*0...127*/
    u8           padding;
}wnrrc_pdsch_td_res_alloc_t;

typedef struct{
    u8                                  pdsch_td_res_list_valid:1;
    u8                                  rsv:7;
    u8                                  pdsch_td_res_alloc_num;/*1...16*/
    u8                                  padding[2];
    wnrrc_pdsch_td_res_alloc_t          pdsch_td_res_list[MAX_NR_DL_ALLOC_NUM];
}wnrrc_pdsch_cfg_common_t;

typedef struct{
    wnrrc_bwp_t                 bwp;
    u8                          pdcch_cfg_valid:1;
    u8                          pdsch_cfg_valid:1;
    u8                          rsv:6;
    u8                          padding[3];
    wnrrc_pdcch_cfg_common_t    pdcch;
    wnrrc_pdsch_cfg_common_t    pdsch;
}wnrrc_bwp_dl_common_t;

typedef enum{
    WNRRC_BCCH_MODIFY_PERIOD_COEFF_N2    = 0,
    WNRRC_BCCH_MODIFY_PERIOD_COEFF_N4,
    WNRRC_BCCH_MODIFY_PERIOD_COEFF_N8,
    WNRRC_BCCH_MODIFY_PERIOD_COEFF_N16
}wnrrc_bcch_modify_period_coeff_e;

typedef struct{
    u8             modify_period_coeff;/*enumerate refer to */
    u8             padding[3];
}wnrrc_bcch_cfg_t;


typedef enum{
    WNRRC_PCCH_PAGING_CYCLE_RF_32   = 0,
    WNRRC_PCCH_PAGING_CYCLE_RF_64,
    WNRRC_PCCH_PAGING_CYCLE_RF_128,
    WNRRC_PCCH_PAGING_CYCLE_RF_256
}wnrrc_pcch_paging_cycle_e;

typedef enum{
    WNRRC_PCCH_PAGING_N_TYPE_ONE_T   = 0,
    WNRRC_PCCH_PAGING_N_TYPE_HALF_T,
    WNRRC_PCCH_PAGING_N_TYPE_QUARTER_T,
    WNRRC_PCCH_PAGING_N_TYPE_ONE_EIGHTH_T,
    WNRRC_PCCH_PAGING_N_TYPE_ONE_SIXTEENTH_T
}wnrrc_pcch_paging_n_type;

typedef enum{
    WNRRC_PCCH_PAGING_NS_FOUR   = 0,
    WNRRC_PCCH_PAGING_NS_TWO,
    WNRRC_PCCH_PAGING_NS_ONE
}wnrrc_pcch_paging_ns_e;

typedef struct{
    u8            first_pmo_valid:1;
    u8            pmo_per_ssb_r16_num_valid:1;
    u8            ran_paging_in_idle_r17_valid:1;
    u8            first_pmo_v1710_valid:1;
    u8            rsv:4;
    u8            paging_cycle;/*enumerate refer to wnrrc_pcch_paging_cycle_e*/
    u8            paging_n_type;/*enumerate refer to wnrrc_pcch_paging_n_type*/
    u8            frame_offset;
    u8            paging_ns;/*enumerate refer to wnrrc_pcch_paging_ns_e*/
    u8            first_pmo_choice;/*0: scs15khz zoneT 
                                     1: scs30khz zoneT-scs15khz half T
                                     2: scs60khz zoneT-scs30khz half T scs15khz quarter T
                                     3: scs120khz zoneT-scs60khze half T-scs30khz quarter T -scs15khz zone eighthT
                                     4: scs120khz half T- scs60khz quarter T - scs30khz zone eighthT -scs15khz zone sixteenthT
                                     5: scs120khz quarter T - scs60khz zone eightT - scs30khz zone sixteenT
                                     6: scs120khz zone eighthT-scs60khz zone sixteenthT
                                     7: scs120khz zone sixteenthT*/
    u8                 pmo_num;/*1...4*/
    u8                 padding;
    union{
        u16            scs15_T[4];/*0...139*/
        u16            scs30_15[4];/*0...279*/
        u16            scs60_30_15[4];/*0...559*/
        u16            scs120T_60_30_15[4];/*0...1119*/
        u16            scs120_half_T_60_30_15[4];/*0...2239*/
        u16            scs120_qua_T_60_30[4];/*0...4479*/
        u16            scs120_ei_T_60[4];/*0...8959*/
        u16            scs120_si_T[4];/*0...17919*/
    }first_pmo;
    u8                 pmo_per_ssb_r16_num;/*2...4*/
    u8                 first_pmo_choice_v1710;/*0:scs480khz zone eigth T
                                                1:scs480khz zone sixteenth T*/
    u8                 pmo_rv1710_num;/*1...4*/
    u8                 padding1;
    bool               ran_paging_in_idle_r17;/*true*/
    union{
        u32         scs480_eigthT[4];
        u32         scs480_sixteenthT[4];
    }first_pmo_v1710;    
}wnrrc_pcch_cfg_t;


typedef enum{
    WNRRC_PEI_R17_PO_NUM_PER_PEI_R17_PO1    = 0,
    WNRRC_PEI_R17_PO_NUM_PER_PEI_R17_PO2,
    WNRRC_PEI_R17_PO_NUM_PER_PEI_R17_PO4,
    WNRRC_PEI_R17_PO_NUM_PER_PEI_R17_PO8
}wnrrc_pei_r17_po_num_per_pei_r17_e;

typedef struct{
    u8           subgroup_num_ueid_r17_valid:1;
    u8           rsv:7;
    u8           subgroup_num_po_r17;/*1...8*/
    u8           subgroup_num_ueid_r17;/*1...8*/
    u8           padding;
}wnrrc_pei_subgroup_cfg_r17_t;

typedef struct{
    u8                              last_used_cell_only_r17_valid:1;
    u8                              rsv:7;
    u8                              po_num_per_pei;/*enumerate refer to wnrrc_pei_r17_po_num_per_pei_r17_e*/
    u8                              payload_size_dci_2_7_r17;/*1...43*/
    u8                              pei_frame_offset_r17;/*0...16*/
    wnrrc_pei_subgroup_cfg_r17_t    subgroup_cfg;
    bool                            last_used_cell_only_r17;
}wnrrc_pei_cfg_r17_t;

typedef struct{
    u8                              pei_cfg_r17_valid:1;
    u8                              init_dl_bwp_redcap_r17_valid:1;
    u8                              rsv:6;
    u8                              padding[3];
    wnrrc_freq_info_dl_sib_t        freq_dl_sib;
    wnrrc_bwp_dl_common_t           initial_dl_bwp;
    wnrrc_bcch_cfg_t                bcch_cfg;
    wnrrc_pcch_cfg_t                pcch_cfg;
    wnrrc_pei_cfg_r17_t             pei_cfg_r17;
    wnrrc_bwp_dl_common_t           init_dl_bwp_redcap_r17;
}wnrrc_dl_cfg_common_sib_t;

typedef struct{
    u8                                     multi_freq_band_list_valid:1;
    u8                                     arfcn_valid:1;
    u8                                     pmax_valid;
    u8                                     freq_shift_7p5_valid:1;
    u8                                     rsv:4;
    u8                                     multi_freq_band_num;
    u8                                     scs_spec_carrier_num;
    s8                                     pmax;/*-30...33*/
    wnrrc_multi_band_info_sib_t            multi_freq_band_list[MAX_NR_MULTI_BAND_NUM];
    u32                                    arfcn;/*0...3279165*/
    wnrrc_scs_spec_carrier_t               scs_spec_carrier_list[MAX_NR_SCS_NUM];
    bool                                   freq_shift_7p5;
}wnrrc_freq_info_ul_sib_t;

typedef enum{
    WNRRC_PUSCH_TD_RES_MAP_TYPE_A = 0,
    WNRRC_PUSCH_TD_RES_MAP_TYPE_B
}wnrrc_pusch_td_res_map_type_e;


typedef struct{
    u8                            k2_valid:1;
    u8                            rsv:7;
    u8                            k2;/*0...32*/
    u8                            map_type;/*enumerate refer to wnrrc_pusch_td_res_map_type_e*/
    u8                            start_sym_len;/*0...127*/
}nr_pusch_td_res_alloc_t;

typedef struct{
    u8                            group_hop_enable_valid:1;
    u8                            res_alloc_list_valid:1;
    u8                            msg3_delta_preamble_valid:1;
    u8                            p0_nominal_valid:1;
    u8                            rsv:4;
    s8                            msg3_delta_preamble;/*-1...6*/
    s8                            p0_nominal;/*-202...24*/
    u8                            pusch_td_res_alloc_num;/*1...16*/
    bool                          group_hop_enable;
    nr_pusch_td_res_alloc_t       res_alloc_list[MAX_NR_UL_ALLOC_NUM];
}nr_pusch_cfg_common_t;

typedef enum{
    NR_PUCCH_GROUP_HOP_NEITHER = 0,
    NR_PUCCH_GROUP_HOP_ENABLE,
    NR_PUCCH_GROUP_HOP_DISABLE
}nr_pucch_group_hop_e;

typedef enum{
    NR_PUCCH_INTRA_SLOT_FH_R17_FROM_LOWER_EDGE   = 0,
    NR_PUCCH_INTRA_SLOT_FH_R17_FROM_UPPER_EDGE,
}nr_pucch_intra_slot_fh_r17_e;

typedef enum{
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_2    = 0,
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_3,
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_4,
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_6,
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_8,
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_9,
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_10,
    NR_PUCCH_ADDITION_PRB_OFFSET_R17_N_12
}nr_pucch_addition_prb_offset_r17_e;

typedef struct{
    u8            res_com_valid:1;
    u8            hop_id_valid:1;
    u8            p0_nominal_valid:1;
    u8            prb_num_valid:1;
    u8            intra_slot_fh_r17_valid:1;
    u8            pucch_res_com_redcap_r17_valid:1;
    u8            addition_prb_offset_r17_valid:1;
    u8            rsv:1;
    u8            res_com;/*0...15*/
    u8            group_hop;/*enumerate refer to nr_pucch_group_hop_e*/
    s8            p0_nominal;/*-202...24*/
    u8            prb_num;/*1...16*/
    u8            intra_slot_fh_r17;/*enumerate refer to nr_pucch_intra_slot_fh_r17_e*/
    u8            pucch_res_com_redcap_r17;/*0...15*/
    u8            addition_prb_offset_r17;/*enumerate refer to nr_pucch_addition_prb_offset_r17_e*/
    u16           hop_id;
    u16           padding1;
}nr_pucch_cfg_common_t;

typedef enum{
    NR_RACH_CFG_COMMON_SSB_PER_RO_ONE_EIGHTH     = 0,
    NR_RACH_CFG_COMMON_SSB_PER_RO_ONE_FOURTH,
    NR_RACH_CFG_COMMON_SSB_PER_RO_ONE_HALF,
    NR_RACH_CFG_COMMON_SSB_PER_RO_ONE,
    NR_RACH_CFG_COMMON_SSB_PER_RO_TWO,
    NR_RACH_CFG_COMMON_SSB_PER_RO_FOUR,
    NR_RACH_CFG_COMMON_SSB_PER_RO_EIGHT,
    NR_RACH_CFG_COMMON_SSB_PER_RO_SIXTEEN
}nr_rach_cfg_common_ssb_per_ro_e;

typedef enum{
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N4      = 0,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N8,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N12,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N16,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N20,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N24,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N28,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N32,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N36,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N40,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N44,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N48,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N52,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N56,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N60,
    NR_RACH_CFG_COMMON_ONE_EIGHTH_SSB_PER_RO_PREAMBLES_PER_SSB_N64
}nr_rach_cfg_common_one_eighth_ssb_per_ro_preambles_per_ssb_e;

typedef enum{
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N4      = 0,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N8,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N12,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N16,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N20,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N24,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N28,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N32,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N36,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N40,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N44,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N48,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N52,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N56,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N60,
    NR_RACH_CFG_COMMON_ONE_FOURTH_SSB_PER_RO_PREAMBLES_PER_SSB_N64
}nr_rach_cfg_common_one_fourth_ssb_per_ro_preambles_per_ssb_e;


typedef enum{
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N4      = 0,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N8,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N12,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N16,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N20,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N24,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N28,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N32,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N36,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N40,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N44,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N48,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N52,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N56,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N60,
    NR_RACH_CFG_COMMON_ONE_HALF_SSB_PER_RO_PREAMBLES_PER_SSB_N64
}nr_rach_cfg_common_one_half_ssb_per_ro_preambles_per_ssb_e;

typedef enum{
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N4      = 0,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N8,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N12,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N16,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N20,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N24,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N28,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N32,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N36,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N40,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N44,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N48,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N52,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N56,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N60,
    NR_RACH_CFG_COMMON_ONE_SSB_PER_RO_PREAMBLES_PER_SSB_N64
}nr_rach_cfg_common_one_ssb_per_ro_preambles_per_ssb_e;


typedef enum{
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N4      = 0,
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N8,
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N12,
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N16,
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N20,
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N24,
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N28,
    NR_RACH_CFG_COMMON_TWO_SSB_PER_RO_PREAMBLES_PER_SSB_N32
}nr_rach_cfg_common_two_ssb_per_ro_preambles_per_ssb_e;

typedef enum{
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_MINUSINFINITY      = 0,
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_DB0,
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_DB5,
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_DB8,
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_DB10,
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_DB12,
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_DB15,
    NR_RA_CFG_MSG_PWR_OFFSET_GROUP_B_DB18
}nr_ra_cfg_msg_pwr_offset_groupB_e;

typedef enum{
    NR_RA_CFG_MSG3_SIZE_GROUPA_B56      = 0,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B144,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B208,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B256,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B282,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B480,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B640,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B800,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B1000,
    NR_RA_CFG_MSG3_SIZE_GROUPA_B72
}nr_ra_cfg_msg3_size_groupA_e;

typedef struct{
    u8           ra_msg3_size_groupA;/*enumerate refer to nr_ra_cfg_msg3_size_groupA_e*/
    u8           msg_power_offset_groupB;/*enumerate refer to nr_ra_cfg_msg_pwr_offset_groupB_e*/
    u8           preambles_groupA_num;/*1...64*/
    u8           padding;
}nr_groupB_cfg_t;

typedef enum{
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_8    = 0,
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_16,
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_24,
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_32,
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_40,
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_48,
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_56,
    NR_RA_CONTENTION_RESOLUTION_TIMER_SF_64
}nr_ra_cfg_contention_resolution_timer_e;

typedef struct{
    u8        scaling_factor_bi_valid:1;
    u8        rsv:7;
    u8        power_ramp_step_high;/*enumerate refer to nr_ra_pwr_ramp_step_high_pri_e*/
    u8        scaling_factor_bi;/*refer to nr_ra_scaling_factor_bi_e*/
    u8        padding;
}nr_ra_priority_t;

typedef enum{
    NR_RACH_CFG_COM_RESTRICT_SET_CFG_UNRESTRICT     = 0,
    NR_RACH_CFG_COM_RESTRICT_SET_CFG_RESTRICTED_SET_TYPEA,
    NR_RACH_CFG_COM_RESTRICT_SET_CFG_RESTRICTED_SET_TYPEB
}nr_rach_cfg_com_restrict_set_cfg_e;

typedef struct{
    nr_ra_priority_t        ra_priority_r16;
    u8                      ra_priority_for_ai_r16;/*bit string 2bits*/
    u8                      padding[3];
}nr_ra_priority_r16_t;

typedef enum{
    NR_PRACH_ROOT_SEQ_IDX_CHOICE_1839    = 0,
    NR_PRACH_ROOT_SEQ_IDX_CHOICE_1139
}nr_prach_root_seq_idx_choice_e;
  

typedef enum{
    NR_PRACH_ROOT_SEQ_IDX_R16_CHOICE_1571    = 0,
    NR_PRACH_ROOT_SEQ_IDX_R16_CHOICE_11151
}nr_prach_root_seq_idx_r16_choice_e;

typedef struct{
    u8          nsag_num;
    u8          padding[3];
#define MAX_NR_SLICE_INFO_R17        8
    u8          nsag_id_r17[MAX_NR_SLICE_INFO_R17];/*bit string 8bits*/
}nr_nsag_list_r17_t;

typedef struct{
    u8                 red_cap_r17_valid:1;
    u8                 small_data_r17_valid:1;
    u8                 msg3_repetitions_r17_valid:1;
    u8                 nsag_list_valid:1;
    u8                 rsv:4;
    u8                 padding[3];
    bool               red_cap_r17;
    bool               small_data_r17;
    bool               msg3_repetitions_r17;
    nr_nsag_list_r17_t nsag_list;
}nr_feature_comb_r17_t;

typedef enum{
    NR_RA_SIZE_GROUP_A_R17_B56     = 0,
    NR_RA_SIZE_GROUP_A_R17_B144,
    NR_RA_SIZE_GROUP_A_R17_B208,
    NR_RA_SIZE_GROUP_A_R17_B256,
    NR_RA_SIZE_GROUP_A_R17_B282,
    NR_RA_SIZE_GROUP_A_R17_B480,
    NR_RA_SIZE_GROUP_A_R17_B640,
    NR_RA_SIZE_GROUP_A_R17_B800,
    NR_RA_SIZE_GROUP_A_R17_B1000,
    NR_RA_SIZE_GROUP_A_R17_B72
}nr_ra_size_groupA_r17_e;

typedef enum{
    NR_MSG_PWR_OFFSET_GROUP_B_R17_MINUSINFINITY      = 0,
    NR_MSG_PWR_OFFSET_GROUP_B_R17_DB_0,
    NR_MSG_PWR_OFFSET_GROUP_B_R17_DB_5,
    NR_MSG_PWR_OFFSET_GROUP_B_R17_DB_8,
    NR_MSG_PWR_OFFSET_GROUP_B_R17_DB_10,
    NR_MSG_PWR_OFFSET_GROUP_B_R17_DB_12,
    NR_MSG_PWR_OFFSET_GROUP_B_R17_DB_15,
    NR_MSG_PWR_OFFSET_GROUP_B_R17_DB_18
}nr_msg_pwr_offset_group_B_r17_e;

typedef struct{
    u8                 ra_size_groupA_r17;/*enumerate refer to nr_ra_size_groupA_r17_e*/
    u8                 msg_pwr_offset_groupB_r17;/*enumerate refer to nr_msg_pwr_offset_group_B_r17_e*/
    u8                 num_preambles_groupA_r17;/*1...64*/
    u8                 padding;
}nr_groupB_cfg_r17_t;

typedef enum{
    NR_NUM_MSGA_PO_PER_SLOT_R16_ONE     = 0,
    NR_NUM_MSGA_PO_PER_SLOT_R16_TWO,
    NR_NUM_MSGA_PO_PER_SLOT_R16_THREE,
    NR_NUM_MSGA_PO_PER_SLOT_R16_SIX
}nr_num_msgA_po_per_slot_r16_e;

typedef enum{
    NR_NUM_OF_MSGA_PO_FDM_R16_1    = 0,
    NR_NUM_OF_MSGA_PO_FDM_R16_2,
    NR_NUM_OF_MSGA_PO_FDM_R16_4,
    NR_NUM_OF_MSGA_PO_FDM_R16_8
}nr_num_of_msga_po_fdm_r16_e;

typedef enum{
    NR_MSGA_DMRS_ADDI_POS_R16_POS0   = 0,
    NR_MSGA_DMRS_ADDI_POS_R16_POS1,
    NR_MSGA_DMRS_ADDI_POS_R16_POS3
}nr_msga_dmrs_addition_pos_r16_e;


typedef struct{
    u8           dmrs_addi_pos_r16_valid:1;
    u8           msga_max_len_valid:1;
    u8           dmrs_cdm_group_valid:1;
    u8           num_ports_valid:1;
    u8           scramb_id0_valid:1;
    u8           scramb_id1_valid:1;
    u8           rsv:2;
    u8           padding[3];
    u8           dmrs_addi_pos_r16;/*enumerate refer to nr_msga_dmrs_addition_pos_r16_e*/
    u8           msga_max_len;/*0:len2 */
    u8           dmrs_cdm_group;/*0,1*/
    u8           num_ports;/*0: one port per cdm group,1:two ports per cdm group*/
    u16          scramb_id0;/*0...65535*/
    u16          scramb_id1;/*0...65535*/
}msgA_dmrs_cfg_r16_t;


typedef enum{
    NR_MAPPING_TYPE_MSGA_PUSCH_R16_TYPEA     = 0,
    NR_MAPPING_TYPE_MSGA_PUSCH_R16_TYPEB
}nr_mapping_type_msgA_pusch_r16_e;

typedef enum{
    NR_MSGA_ALPHA_R16_ALPHA0     = 0,
    NR_MSGA_ALPHA_R16_ALPHA04,
    NR_MSGA_ALPHA_R16_ALPHA05,
    NR_MSGA_ALPHA_R16_ALPHA06,
    NR_MSGA_ALPHA_R16_ALPHA07,
    NR_MSGA_ALPHA_R16_ALPHA08,
    NR_MSGA_ALPHA_R16_ALPHA09,
    NR_MSGA_ALPHA_R16_ALPHA1
}nr_msga_alpha_r16_e;


typedef struct{
    u16               msgA_pusch_td_alloc_r16_valid:1;
    u16               start_sym_and_len_msgA_po_r16_valid:1;
    u16               maping_type_msgA_pusch_r16_valid:1;
    u16               guard_period_msgA_pusch_r16_valid:1;
    u16               msgA_intra_slot_freq_hop_r16_valid:1;
    u16               msgA_hop_bits_r16_valid:1;
    u16               msgA_alpha_r16_valid:1;
    u16               interlace_idx_first_po_msgA_pusch_r16_valid:1;
    u16               num_interlaces_per_msgA_po_r16_valid:1;
    u16               rsv:7;
    u8                msgA_mcs_r16;/*0...15*/
    u8                num_slot_msgA_pusch_r16;/*1...4*/
    u8                num_msgA_po_per_slot_r16;/*enumerate refer to nr_num_msgA_po_per_slot_r16_e*/
    u8                msgA_pusch_td_offset_r16;/*1...32*/
    u8                msgA_pusch_td_alloc_r16;/*1...16*/
    u8                start_sym_and_len_msgA_po_r16;/*0...127*/
    u8                maping_type_msgA_pusch_r16;/*enumerate refer to nr_mapping_type_msgA_pusch_r16_e*/
    u8                guard_period_msgA_pusch_r16;
    u8                guard_band_msgA_pusch_r16;
    u8                num_prb_per_msgA_po_r16;/*1...32*/
    u8                num_msgA_po_fdm_r16;/*nr_num_of_msga_po_fdm_r16_e*/
    u8                msgA_hop_bits_r16;
    u16               freq_start_msgA_pusch_r16;/*0...274*/
    bool              msgA_intra_slot_freq_hop_r16;
    msgA_dmrs_cfg_r16_t   msgA_dmrs_cfg_r16;
    u8                    num_dmrs_seq_r16;
    u8                    msgA_alpha_r16;/*enumerate refer to nr_msga_alpha_r16_e*/
    u8                    interlace_idx_first_po_msgA_pusch_r16;/*1...10*/
    u8                    num_interlaces_per_msgA_po_r16;/*1...10*/
}nr_msgA_pusch_res_r16_t;

typedef struct{
    u8                              msgA_pusch_groupA_res_valid:1;
    u8                              msgA_pusch_groupB_res_valid:1;
    u8                              msgA_transform_precoder_r16_valid:1;
    u8                              msgA_data_scramb_idx_r16_valid:1;
    u8                              msgA_delta_preambles_r16_valid:1;
    u8                              rsv:3;
    u8                              padding[3];
    nr_msgA_pusch_res_r16_t         msgA_pusch_groupA_res;
    nr_msgA_pusch_res_r16_t         msgA_pusch_groupB_res;
    bool                            msgA_transform_precoder_r16;
    u16                             msgA_data_scramb_idx_r16;/*0...1023*/
    s8                              msgA_delta_preambles_r16;
    u8                              padding1;
}nr_msgA_pusch_cfg_r16_t;

typedef struct{
    u8                              ssb_shared_ro_mask_idx_r17_valid:1;
    u8                              groupB_cfg_r17_valid:1;
    u8                              msgA_pusch_cfg_r17_valid:1;
    u8                              msgA_rsrp_thresh_r17_valid:1;
    u8                              rsrp_thresh_ssb_r17_valid:1;
    u8                              delta_preamble_r17_valid:1;
    u8                              rsv:2;
    u8                              start_preamble_for_this_part;/*0...63*/
    u8                              num_preambles_per_ssb;/*1...64*/
    u8                              ssb_shared_ro_mask_idx_r17;/*1...15*/
    nr_feature_comb_r17_t           feature_comb;
    nr_groupB_cfg_r17_t             groupB_cfg_r17;
    nr_msgA_pusch_cfg_r16_t         msgA_pusch_cfg_r17;
    u8                              msgA_rsrp_thresh_r17;
    u8                              rsrp_thresh_ssb_r17;
    s8                              delta_preamble_r17;/*-1...6*/
    u8                              padding1;
}nr_feature_comb_preambles_r17_t;

typedef struct{
    u16                                       feature_comb_num;
    u8                                        padding[2];
#define MAX_NR_FEATURE_COMB_PREAMBLES_PER_RACH_RES  256
    nr_feature_comb_preambles_r17_t           *feature_comb_list[MAX_NR_FEATURE_COMB_PREAMBLES_PER_RACH_RES];
}nr_rach_feature_combination_preamble_list_r17_t;


typedef struct{
    u8                        group_b_cfg_valid:1;
    u8                        rsrp_thresh_ssb_valid:1;
    u8                        rsrp_thresh_ssb_sul_valid:1;
    u8                        msg1_scs_valid:1;
    u8                        msg3_transform_precoder_valid:1;
    u8                        ra_priority_r16_valid:1;
    u8                        prach_root_seq_idx_r16_valid:1;
    u8                        feature_comb_list_valid:1;
    u8                        padding[3];
    nr_rach_generic_t         rach_generic;
    u8                        total_num_ra_preamble;/*integer(1...63)*/
    u8                        ssb_num_per_ro;/*enumerate refer to nr_rach_cfg_common_ssb_per_ro_e*/
    u8                        preambles_per_ssb;/*enumerate refer to 
                                                   nr_rach_cfg_common_one_eighth_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_one_fourth_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_one_half_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_one_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_two_ssb_per_ro_preambles_per_ssb_e,
                                                   four ssb per ro cfg preambles is 1...16
                                                   eight ssb per ro cfg preambles is 1...8
                                                   sixteen ssb per ro cfg preambles is 1...4*/
    u8                       restrict_set_cfg;/*enumerate refer to nr_rach_cfg_com_restrict_set_cfg_e*/
    nr_groupB_cfg_t          group_b_cfg;
    u8                       ra_cr_timer;/*enumerate refer to nr_ra_cfg_contention_resolution_timer_e*/
    u8                       rsrp_thresh_ssb;/*RSRP_Range 0...127*/
    u8                       rsrp_thresh_ssb_sul;/*RSRP_Range 0...127*/
    u8                       prach_root_seq_idx_choice;/*nr_prach_root_seq_idx_choice_e*/
    u16                      prach_root_seq_idx;
    u8                       msg1_scs;/*wnrrc_scs_e*/
    u8                       prach_root_seq_idx_r16_choice;/*nr_prach_root_seq_idx_r16_choice_e*/
    u16                      prach_root_seq_idx_r16;
    u8                       padding1[2];
    bool                     msg3_transform_precoder;
    nr_ra_priority_r16_t     ra_priority_r16;
    nr_rach_feature_combination_preamble_list_r17_t      feature_comb_list;
}nr_rach_cfg_common_t;

typedef enum{
    NR_MSGA_TRANS_MAX_R16_N1     = 0,
    NR_MSGA_TRANS_MAX_R16_N2,
    NR_MSGA_TRANS_MAX_R16_N4,
    NR_MSGA_TRANS_MAX_R16_N6,
    NR_MSGA_TRANS_MAX_R16_N8,
    NR_MSGA_TRANS_MAX_R16_N10,
    NR_MSGA_TRANS_MAX_R16_N20,
    NR_MSGA_TRANS_MAX_R16_N50,
    NR_MSGA_TRANS_MAX_R16_N100,
    NR_MSGA_TRANS_MAX_R16_N200
}nr_msgA_trans_max_r16_e;

typedef enum{
    NR_MSGA_RESTRICT_SET_CFG_R16_UNRESTRICT     = 0,
    NR_MSGA_RESTRICT_SET_CFG_R16_RESTRICTED_SET_TYPEA,
    NR_MSGA_RESTRICT_SET_CFG_R16_RESTRICTED_SET_TYPEB
}nr_msgA_restrict_set_cfg_r16_e;

typedef struct{
    u16     msgA_prach_cfg_idx_r16_valid:1;
    u16     msgA_ro_fdm_r16_valid:1;
    u16     msgA_ro_freq_start_r16_valid:1;
    u16     msgA_zc_zone_cfg_r16_valid:1;
    u16     pream_pwr_ramp_sp_r16_valid:1;
    u16     pream_recv_target_pwr_r16_valid:1;
    u16     msgB_rsp_window_r16_valid:1;
    u16     pream_trans_max_r16_valid:1;
    u16     msgB_rsp_win_v1700_valid:1;
    u16     rsv:7;
    u16     msgA_prach_cfg_idx_r16;/*0...262*/
    u8      msgA_ro_fdm_r16;/*enumerate refer to nr_ra_msga_ro_fdm_r16_e*/
    u16     msgA_ro_freq_start_r16;/*0...274*/
    u8      msgA_zc_zone_cfg_r16;/*0...15*/
    u8      pream_pwr_ramp_sp_r16;/*enumerate refer to nr_ra_pwr_ramping_step_e*/
    s8      pream_recv_target_pwr_r16;/*-220...-60*/
    u8      msgB_rsp_window_r16;/*enumerate refer to nr_ra_msgb_rsp_win_r16_e*/
    u8      pream_trans_max_r16;/*enumerate refer to nr_preamble_trans_max_e*/
    u8      msgB_rsp_win_v1700;/*enumerate refer to nr_ra_msgb_rsp_win_v1700_e*/
    u8      padding[3];
}ra_generic_twsp_r16_t;


typedef enum{
    NR_MSFA_PRACH_ROOT_SEQ_IDX_R16_CHOICE_1839    = 0,
    NR_MSFA_PRACH_ROOT_SEQ_IDX_R16_CHOICE_1139,
    NR_MSFA_PRACH_ROOT_SEQ_IDX_R16_CHOICE_1571,
    NR_MSFA_PRACH_ROOT_SEQ_IDX_R16_CHOICE_11151
}nr_msgA_prach_root_seq_idx_r16_choice_e;

typedef struct{
    nr_ra_priority_t               ra_priority_r16;
    u8                             ra_priority_for_ai_r16;/*bit string 2bits*/
    u8                             padding[3];
}nr_ra_priority_twsp_r16_t;

typedef enum{
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_8    = 0,
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_16,
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_24,
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_32,
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_40,
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_48,
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_56,
    NR_RA_CONTENTION_RESOLUTION_TIMER_R16_SF_64
}nr_ra_cfg_contention_resolution_timer_r16_e;

typedef enum{
    NR_RA_CFG_MSGA_SIZE_GROUPA_B56      = 0,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B144,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B208,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B256,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B282,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B480,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B640,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B800,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B1000,
    NR_RA_CFG_MSGA_SIZE_GROUPA_B72
}nr_ra_cfg_msgA_size_groupA_e;


typedef struct{
    u8                 ra_msgA_size_groupA;/*nr_ra_cfg_msgA_size_groupA_e*/
    u8                 msg_pwr_offset_groupB;/*nr_ra_cfg_msg_pwr_offset_groupB_e*/
    u8                 num_ra_preamble_groupA;/*1...64*/
    u8                 padding;
}nr_groupB_cfg_two_step_ra_r16_t;


typedef struct{
    u16                                          msgA_total_num_preambles_r16_valid:1;
    u16                                          ssb_per_ro_preambles_per_ssb_msgA_r16_valid:1;
    u16                                          msgA_cb_preambles_per_ssb_valid:1;
    u16                                          msgA_ssb_shared_ro_mask_idx_r16_valid:1;
    u16                                          groupB_cfg_r16_valid:1;
    u16                                          msgA_prach_root_seq_idx_r16_valid:1;
    u16                                          msgA_trans_max_r16_valid:1;
    u16                                          msgA_rsrp_thresh_r16_valid:1;
    u16                                          msgA_rsrp_thresh_ssb_r16_valid:1;
    u16                                          msgA_scs_valid:1;
    u16                                          msgA_restricted_set_cfg_r16_valid:1;
    u16                                          ra_priority_twsp_r16_valid:1;
    u16                                          ra_cr_timer_r16_valid:1;
    u16                                          feature_comb_r17_valid:1;
    u16                                          rsv:2;
    u16                                          padding;
    ra_generic_twsp_r16_t                        generic;
    u8                                           msgA_total_num_preambles_r16;
    u8                                           num_ssb_per_ro_msgA;/*enumerate refer to nr_rach_cfg_common_ssb_per_ro_e*/
    u8                                           cb_preambles_per_ssb_r16;/*enumerate refer to 
                                                   nr_rach_cfg_common_one_eighth_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_one_fourth_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_one_half_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_one_ssb_per_ro_preambles_per_ssb_e,
                                                   nr_rach_cfg_common_two_ssb_per_ro_preambles_per_ssb_e,
                                                   four ssb per ro cfg preambles is 1...16
                                                   eight ssb per ro cfg preambles is 1...8
                                                   sixteen ssb per ro cfg preambles is 1...4*/
    u8                                             msgA_cb_preambles_per_ssb;/*1...60*/
    u8                                             msgA_ssb_shared_ro_mask_idx_r16;/*1...15*/
    nr_groupB_cfg_two_step_ra_r16_t                groupB_cfg_r16;
    u8                                             msgA_prach_root_seq_idx_r16_choice;/*enumerate refer to nr_msgA_prach_root_seq_idx_r16_choice_e*/
    u16                                            msgA_prach_root_seq_idx_r16;
    u8                                             msgA_trans_max_r16;/*enumerate refer to nr_msgA_trans_max_r16_e*/
    u8                                             msgA_rsrp_thresh_r16;
    u8                                             msgA_rsrp_thresh_ssb_r16;
    u8                                             msgA_scs;/*wnrrc_scs_e*/
    u8                                             msgA_restricted_set_cfg_r16;/*nr_msgA_restrict_set_cfg_r16_e*/
    nr_ra_priority_twsp_r16_t                      ra_priority_twsp_r16;
    u8                                             ra_cr_timer_r16;/*nr_ra_cfg_contention_resolution_timer_r16_e*/
    nr_rach_feature_combination_preamble_list_r17_t  feature_comb_r17;
}nr_rach_cfg_common_two_step_r16_t;

typedef struct{
    u8                                     msgA_pusch_cfg_r16_valid:1;
    u8                                     rsv:7;
    u8                                     padding[3];
    nr_rach_cfg_common_two_step_r16_t      rach_cfg_two_step;
    nr_msgA_pusch_cfg_r16_t                msgA_pusch_cfg_r16;
}nr_msgA_cfg_common_r16_t;

typedef struct{
    u8                               rach_cfg_r17_valid:1;
    u8                               msgA_cfg_r17_valid:1;
    u8                               rsv:6;
    u8                               padding[3];
    nr_rach_cfg_common_t             rach_cfg_r17;
    nr_msgA_cfg_common_r16_t         msgA_cfg_r17;
}nr_addition_rach_cfg_r17_t;

typedef struct{
    u16                                 addition_rach_cfg_num;
    u16                                 padding;
#define MAX_ADDITIONAL_RACH_R17_NUM     256
    nr_addition_rach_cfg_r17_t*          addition_rach_list_r17[MAX_ADDITIONAL_RACH_R17_NUM];
}nr_addition_rach_cfg_list_r17_t;

typedef enum{
    nr_num_msg3_repetitions_r17_N_1      = 0,
    nr_num_msg3_repetitions_r17_N_2,
    nr_num_msg3_repetitions_r17_N_3,
    nr_num_msg3_repetitions_r17_N_4,
    nr_num_msg3_repetitions_r17_N_7,
    nr_num_msg3_repetitions_r17_N_8,
    nr_num_msg3_repetitions_r17_N_12,
    nr_num_msg3_repetitions_r17_N_16
}nr_num_msg3_repetitions_r17_e;

typedef struct{
    u16                                   rach_valid:1;
    u16                                   pusch_valid:1;
    u16                                   pucch_valid:1;
    u16                                   use_interlace_pucch_pusch_r16_valid:1;
    u16                                   msgA_cfg_com_r16_valid:1;
    u16                                   addition_rach_r17_valid:1;
    u16                                   rsrp_thresh_msg3_r17_valid:1;
    u16                                   msg3_repetitions_r17_valid:1;
    u16                                   mcs_msg3_repetitions_r17_valid:1;
    u16                                   rsv:7;
    u8                                    padding[2];
    wnrrc_bwp_t                           bwp;
    nr_rach_cfg_common_t                  *rach;
    nr_pusch_cfg_common_t                 pusch;
    nr_pucch_cfg_common_t                 pucch;
    bool                                  use_interlace_pucch_pusch_r16;
    nr_msgA_cfg_common_r16_t              *msgA_cfg_com_r16;
    nr_addition_rach_cfg_list_r17_t       *addition_rach_r17;
    u8                                    rsrp_thresh_msg3_r17;
    u8                                    padding1[3];
    u8                                    msg3_repetitions_r17[4];
    u8                                    mcs_msg3_repetitions_r17[8];/*element range is 0...31*/
}wnrrc_bwp_ul_common_t;

typedef struct{
    u16                                   rach_valid:1;
    u16                                   pusch_valid:1;
    u16                                   pucch_valid:1;
    u16                                   use_interlace_pucch_pusch_r16_valid:1;
    u16                                   msgA_cfg_com_r16_valid:1;
    u16                                   addition_rach_r17_valid:1;
    u16                                   rsrp_thresh_msg3_r17_valid:1;
    u16                                   msg3_repetitions_r17_valid:1;
    u16                                   mcs_msg3_repetitions_r17_valid:1;
    u16                                   rsv:7;
    u8                                    padding[2];
    wnrrc_bwp_t                           bwp;
    nr_rach_cfg_common_t                  rach;
    nr_pusch_cfg_common_t                 pusch;
    nr_pucch_cfg_common_t                 pucch;
    bool                                  use_interlace_pucch_pusch_r16;
    nr_msgA_cfg_common_r16_t              msgA_cfg_com_r16;
    nr_addition_rach_cfg_list_r17_t       addition_rach_r17;
    u8                                    rsrp_thresh_msg3_r17;
    u8                                    padding1[3];
    u8                                    msg3_repetitions_r17[4];
    u8                                    mcs_msg3_repetitions_r17[8];/*element range is 0...31*/
}wnrrc_bwp_ul_common_in_sib1_t;

typedef enum{
    NR_TA_TMR_MS_500       = 0,
    NR_TA_TMR_MS_750,
    NR_TA_TMR_MS_1280,
    NR_TA_TMR_MS_1920,
    NR_TA_TMR_MS_2560,
    NR_TA_TMR_MS_5120,
    NR_TA_TMR_MS_10240,
    NR_TA_TMR_MS_INFINITY
}nr_ta_timer_e;


typedef struct{
    wnrrc_freq_info_ul_sib_t             freq_ul;
    wnrrc_bwp_ul_common_t                bwp_ul;
    u8                                   ta_timer_com;/*enumerate refer to nr_ta_timer_e*/
    u8                                   padding[3];
}wnrrc_ul_cfg_common_sib_t;

typedef enum{
    NR_SERV_CELL_CFG_SIB_TA_OFFSET_N_0    = 0,
    NR_SERV_CELL_CFG_SIB_TA_OFFSET_N_25600,
    NR_SERV_CELL_CFG_SIB_TA_OFFSET_N_39936
}nr_serv_cell_cfg_sib_n_ta_offset_e;

typedef struct{
    u8       group_present_valid:1;
    u8       rsv:7;
    u8       in_one_group;/*bit string*/
    u8       group_present;/*bit string*/
    u8       padding;
}wnnr_ssb_pos_in_burst_t;

typedef enum{
    WNRRC_SERV_CELL_CFG_SIB_SSB_PERIOD_MS_5   = 0,
    WNRRC_SERV_CELL_CFG_SIB_SSB_PERIOD_MS_10,
    WNRRC_SERV_CELL_CFG_SIB_SSB_PERIOD_MS_20,
    WNRRC_SERV_CELL_CFG_SIB_SSB_PERIOD_MS_40,
    WNRRC_SERV_CELL_CFG_SIB_SSB_PERIOD_MS_80,
    WNRRC_SERV_CELL_CFG_SIB_SSB_PERIOD_MS_160
}wnrrc_serv_cell_cfg_sib_ssb_period_e;

typedef enum{
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_0_P_5     = 0,
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_0_P_625,
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_1,
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_1_P_25,
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_2,
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_2_P_5,
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_5,
    WNRRC_TD_DL_UL_TRANS_PERIOD_MS_10
}wnrrc_td_dl_ul_trans_period_e;

typedef enum{
    WNRRC_DL_UL_TRANS_PERIOD_V1530_MS_3    = 0,
    WNRRC_DL_UL_TRANS_PERIOD_V1530_MS_4
}wnrrc_dl_ul_trans_period_v1530_e;

typedef struct{
    u8                      dl_ul_trans_period_v1530_valid:1;
    u8                      rsv:7;
    u8                      padding[3];
    u8                      dl_ul_trans_period;/*enumerate refer to wnrrc_td_dl_ul_trans_period_e*/
    u16                     dl_slots;/*0...320*/
    u8                      dl_symbols;/*0...13*/
    u16                     ul_slots;/*0...320*/
    u8                      ul_symbols;/*0...13*/
    u8                      dl_ul_trans_period_v1530;/*enumerater refer to wnrrc_dl_ul_trans_period_v1530_e*/
}wnrrc_td_ul_dl_pattern_t;

typedef struct{
    u8                               pattern2_valid:1;
    u8                               rsv:7;
    u8                               scs;/*enumerate refer to wnrrc_scs_e referenceSubcarrierSpacing*/
    u8                               padding[2];
    wnrrc_td_ul_dl_pattern_t         pattern1;
    wnrrc_td_ul_dl_pattern_t         pattern2;
}wnrrc_td_ul_dl_cfg_common_t;

typedef enum{
    WNRRC_CHANNEL_ACCESS_MODE_R16_DYNAMIC   = 0,
    WNRRC_CHANNEL_ACCESS_MODE_R16_SEMI_STATIC
}wnrrc_channel_access_mode_r16_e;

typedef enum{
    WNRRC_SEMI_STATIC_ACCESS_R16_PERIOD_MS_1     = 0,
    WNRRC_SEMI_STATIC_ACCESS_R16_PERIOD_MS_2,
    WNRRC_SEMI_STATIC_ACCESS_R16_PERIOD_MS_2_DOT_5,
    WNRRC_SEMI_STATIC_ACCESS_R16_PERIOD_MS_4,
    WNRRC_SEMI_STATIC_ACCESS_R16_PERIOD_MS_5,
    WNRRC_SEMI_STATIC_ACCESS_R16_PERIOD_MS_10
}wnrrc_semi_static_access_r16_period_e;

typedef enum{
    WNRRC_DISCOVER_BURST_WIN_LEN_R16_MS_0_DOT_5     = 0,
    WNRRC_DISCOVER_BURST_WIN_LEN_R16_MS_1,
    WNRRC_DISCOVER_BURST_WIN_LEN_R16_MS_2,
    WNRRC_DISCOVER_BURST_WIN_LEN_R16_MS_3,
    WNRRC_DISCOVER_BURST_WIN_LEN_R16_MS_4,
    WNRRC_DISCOVER_BURST_WIN_LEN_R16_MS_5
}wnrrc_discover_burst_win_len_r16_e;


typedef struct{
    u8           meas_flag_r16_valid:1;
    u8           demo_flag_r16_valid:1;
    u8           rsv:6;
    u8           padding[3];
    bool         meas_flag_r16;
    bool         demo_flag_r16;
}wnrrc_high_speed_cfg_r16_t;


typedef enum{
    WNRRC_DISCOVER_BURST_WIN_LEN_V1700_MS_0_DOT_125     = 0,
    WNRRC_DISCOVER_BURST_WIN_LEN_V1700_MS_0_DOT_25,
    WNRRC_DISCOVER_BURST_WIN_LEN_V1700_MS_0_DOT_5,
    WNRRC_DISCOVER_BURST_WIN_LEN_V1700_MS_0_DOT_75,
    WNRRC_DISCOVER_BURST_WIN_LEN_V1700_MS_1,
    WNRRC_DISCOVER_BURST_WIN_LEN_V1700_MS_1_DOT_25
}wnrrc_discover_burst_win_len_v1700_e;

typedef enum{
    WNRRC_HIGH_SPEED_MEAS_FLAG_R17_SET1    = 0,
    WNRRC_HIGH_SPEED_MEAS_FLAG_R17_SET2
}wnrrc_high_speed_meas_flag_r17_e;

typedef enum{
    WNRRC_HIGH_SPEED_DEPLOY_TYPE_R17_UNIDIRECTIONAL  = 0,
    WNRRC_HIGH_SPEED_DEPLOY_TYPE_R17_BIDIRECTIONAL
}wnrrc_high_speed_deploy_type_r17_e;

typedef struct{
    u8           meas_flag_fr2_r17_valid:1;
    u8           deploy_type_r17_valid:1;
    u8           large_one_step_ul_timing_r17_valid:1;
    u8           rsv:5;
    u8           meas_flag_fr2_r17;/*enumerate refer to wnrrc_high_speed_meas_flag_r17_e*/
    u8           deploy_type_r17;/*enumerate refer to wnrrc_high_speed_deploy_type_r17_e*/
    u8           padding;
    bool         large_one_step_ul_timing_r17;
}wnrrc_high_speed_cfg_fr2_r17_t;

typedef struct{
    u8                          bwp_redcap_r17_valid:1;
    u8                          rsv:7;
    u8                          padding[3];
    wnrrc_bwp_ul_common_t       bwp_redcap_r17;
}wnrrc_ul_cfg_common_sib_v1700_t;

typedef enum{
    NR_T300_MS_100    = 0,
    NR_T300_MS_200,
    NR_T300_MS_300,
    NR_T300_MS_400,
    NR_T300_MS_600,
    NR_T300_MS_1000,
    NR_T300_MS_1500,
    NR_T300_MS_2000
}nr_t300_e;

typedef enum{
    NR_T301_MS_100    = 0,
    NR_T301_MS_200,
    NR_T301_MS_300,
    NR_T301_MS_400,
    NR_T301_MS_600,
    NR_T301_MS_1000,
    NR_T301_MS_1500,
    NR_T301_MS_2000
}nr_t301_e;


typedef enum{
    NR_T310_MS_0     = 0,
    NR_T310_MS_50,
    NR_T310_MS_100, 
    NR_T310_MS_200, 
    NR_T310_MS_500,
    NR_T310_MS_1000,
    NR_T310_MS_2000
}nr_t310_e;

typedef enum{
    NR_N310_N1    = 0,
    NR_N310_N2,
    NR_N310_N3,
    NR_N310_N4,
    NR_N310_N6,
    NR_N310_N8,
    NR_N310_N10,
    NR_N310_N20
}nr_n310_e;

typedef enum{
    NR_T311_MS_1000    = 0,
    NR_T311_MS_3000,
    NR_T311_MS_5000,
    NR_T311_MS_10000,
    NR_T311_MS_15000,
    NR_T311_MS_20000,
    NR_T311_MS_30000
}nr_t311_e;

typedef enum{
    NR_N311_N1    = 0,
    NR_N311_N2,
    NR_N311_N3,
    NR_N311_N4,
    NR_N311_N5,
    NR_N311_N6,
    NR_N311_N8,
    NR_N311_N10
}nr_n311_e;

typedef enum{
    NR_T319_MS_100    = 0,
    NR_T319_MS_200,
    NR_T319_MS_300,
    NR_T319_MS_400,
    NR_T319_MS_600,
    NR_T319_MS_1000,
    NR_T319_MS_1500,
    NR_T319_MS_2000
}nr_t319_e;


typedef struct{
    u8           t300;/*enumerate refer to nr_t300_e*/
    u8           t301;/*nr_t301_e*/
    u8           t310;/*nr_t310_e*/
    u8           n310;/*nr_n310_e*/
    u8           t311;/*nr_t311_e*/
    u8           n311;/*nr_n311_e*/
    u8           t319;/*nr_t319_e*/
    u8           padding;
}wnrrc_ue_tmr_and_cons_t;


typedef struct{
    u32                                ul_cfg_com_sib_valid:1;
    u32                                sul_cfg_sib_valid:1;
    u32                                n_ta_offset_valid:1;
    u32                                td_ul_dl_valid:1;
    u32                                channel_access_mode_r16_valid:1;
    u32                                dsc_burst_win_len_r16_valid:1;
    u32                                high_speed_r16_valid:1;
    u32                                chan_access_mode2_r17_valid:1;
    u32                                dsc_burst_win_len_v1700_valid:1;
    u32                                high_speed_r17_valid:1;
    u32                                ul_cfg_sib_v1700_valid:1;
    u32                                enhance_meas_LEO_r17_valid:1;
    u32                                rsv:21;
    wnrrc_dl_cfg_common_sib_t          dl_cfg_com_sib;
    wnrrc_ul_cfg_common_sib_t          ul_cfg_com_sib;
    wnrrc_ul_cfg_common_sib_t          sul_cfg_sib;
    u8                                 n_ta_offset;/*enumerate refer to nr_serv_cell_cfg_sib_n_ta_offset_e*/
    u8                                 padding[3];
    wnnr_ssb_pos_in_burst_t            ssb_pos_in_burst;
    u8                                 ssb_period_serv_cell;/*enumerate refer to wnrrc_serv_cell_cfg_sib_ssb_period_e*/
    u8                                 padding1[3];
    wnrrc_td_ul_dl_cfg_common_t        td_ul_dl;
    s8                                 ss_pbch_block_pwr;/*-60...50*/
    u8                                 channel_access_mode_r16;/*enumerate refer to wnrrc_channel_access_mode_r16_e*/
    u8                                 semi_static_period;/*enumerate refer to wnrrc_semi_static_access_r16_period_e*/
    u8                                 dsc_burst_win_len_r16;/*enumerate refer to wnrrc_discover_burst_win_len_r16_e*/
    wnrrc_high_speed_cfg_r16_t         high_speed_r16;
    bool                               chan_access_mode2_r17;/*TRUE: enable, FALSE:disable*/
    u8                                 dsc_burst_win_len_v1700;/*enumerate refer to wnrrc_discover_burst_win_len_v1700_e*/
    u8                                 padding2[3];
    wnrrc_high_speed_cfg_fr2_r17_t     high_speed_r17;
    wnrrc_ul_cfg_common_sib_v1700_t    ul_cfg_sib_v1700;
    bool                               enhance_meas_LEO_r17;
    bool                               ra_ch_access_r17;
}wnrrc_serv_cell_cfg_comm_sib_t;


typedef struct{
    u8                                 si_req_cfg_valid:1;
    u8                                 si_req_cfg_sul_valid:1;
    u8                                 sys_info_area_id_valid:1;
    u8                                 rsv:5;
    u8                                 si_win_len;/*enumerate refer to wnrrc_si_win_len_e*/
    u8                                 schdl_num;
    u8                                 padding[2];
    wnrrc_si_schdl_schdl_info_t        schdl_info_list[MAX_NR_SI_MSG_NUM];
    wnrrc_si_req_cfg_t                 si_req_cfg;
    wnrrc_si_req_cfg_t                 si_req_cfg_sul;
    u32                                sys_info_area_id;/*bit string*/
}wnrrc_si_schdl_info_t;

typedef struct{
    u8                            access_cat;/*1...63*/
    u8                            bar_info_set_idx;/*1...8*/
    u8                            padding[2];
}wnrrc_uac_bar_per_cat_t;

typedef enum{
    WNRRC_UAC_BAR_PER_PLMN_AC_BAR_TYPE_IMPLICIT   = 0,
    WNRRC_UAC_BAR_PER_PLMN_AC_BAR_TYPE_EXPLICIT
}wnrrc_uac_bar_per_plmn_ac_bar_type;

typedef struct{
    u8             uac_ACBarringListType_valid:1;
    u8             rsv:7;
    u8             plmn_id_idx;/*1...12*/
    u8             ac_bar_type;/*enumerate refer to wnrrc_uac_bar_per_plmn_ac_bar_type*/
    u8             bar_num;
    union{
        u8                            imp_bar_info_set_idx_list[MAX_NR_ACCESS_CAT];/*actual max array length is MAX_NR_ACCESS_CAT-1*/
        wnrrc_uac_bar_per_cat_t       exp_bar_per_cat_list[MAX_NR_ACCESS_CAT-1];
    }u;
}wnrrc_uac_bar_per_plmn_t;

typedef enum{
    WNRRC_BAR_FACTOR_P_00    = 0,
    WNRRC_BAR_FACTOR_P_05,
    WNRRC_BAR_FACTOR_P_10,
    WNRRC_BAR_FACTOR_P_15,
    WNRRC_BAR_FACTOR_P_20,
    WNRRC_BAR_FACTOR_P_25,
    WNRRC_BAR_FACTOR_P_30,
    WNRRC_BAR_FACTOR_P_40,
    WNRRC_BAR_FACTOR_P_50,
    WNRRC_BAR_FACTOR_P_60,
    WNRRC_BAR_FACTOR_P_70,
    WNRRC_BAR_FACTOR_P_75,
    WNRRC_BAR_FACTOR_P_80,
    WNRRC_BAR_FACTOR_P_85,
    WNRRC_BAR_FACTOR_P_90,
    WNRRC_BAR_FACTOR_P_95
}wnrrc_uac_bar_factor_e;

typedef enum{
    WNRRC_BAR_TIME_S4    = 0,
    WNRRC_BAR_TIME_S8,
    WNRRC_BAR_TIME_S16,
    WNRRC_BAR_TIME_S32,
    WNRRC_BAR_TIME_S64,
    WNRRC_BAR_TIME_S128,
    WNRRC_BAR_TIME_S256,
    WNRRC_BAR_TIME_S512
}wnrrc_uac_time_e;

typedef struct{
    u8         uac_bar_factor;/*enumerate refer to wnrrc_uac_bar_factor_e*/
    u8         uac_bar_time;/*enumerate refer to wnrrc_uac_time_e*/
    u8         bar_for_access_id;/*bit string*/
    u8         padding;
}wnrrc_uac_bar_info_set_t;

typedef enum{
    WNRRC_UAC_AC1_SEL_ASSIS_INFO_TYPE_A    = 0,
    WNRRC_UAC_AC1_SEL_ASSIS_INFO_TYPE_B,
    WNRRC_UAC_AC1_SEL_ASSIS_INFO_TYPE_C
}wnrrc_uac_ac1_sel_assis_info_type_e;

typedef struct{
    u8           type;/*enumerate refer to wnrrc_uac_ac1_sel_assis_info_type_e*/
    u8           padding[3];
}wnrrc_uac_ac1_sel_assis_info_t;

typedef struct{
    u8                                      bar_per_cat_list_valid:1;
    u8                                      bar_per_plmn_list_valid:1;
    u8                                      uac_ac1_sel_assis_info_valid:1;
    u8                                      rsv:6;
    u8                                      padding[3];
    u8                                      bar_num_per_cat;
    u8                                      bar_num_per_plmn;
    u8                                      bar_info_set_num;
    u8                                      uac_ac1_sel_assis_info_num;/*1: plmn common
                                                                         2~12:individual plmn list*/
    wnrrc_uac_bar_per_cat_t                 bar_per_cat_list[MAX_NR_ACCESS_CAT-1];
    wnrrc_uac_bar_per_plmn_t                bar_per_plmn_list[MAX_NR_PLMN_NUM];
    wnrrc_uac_bar_info_set_t                bar_info_set_list[MAX_NR_BAR_INFO_SET_NUM];
    wnrrc_uac_ac1_sel_assis_info_t          plmn_list[MAX_NR_PLMN_NUM];
}wnrrc_uac_bar_info_t;

typedef enum{
    WNRRC_POS_SCHDL_SI_PERIOD_R16_RF_8     = 0,
    WNRRC_POS_SCHDL_SI_PERIOD_R16_RF_16,
    WNRRC_POS_SCHDL_SI_PERIOD_R16_RF_32,
    WNRRC_POS_SCHDL_SI_PERIOD_R16_RF_64,
    WNRRC_POS_SCHDL_SI_PERIOD_R16_RF_128,
    WNRRC_POS_SCHDL_SI_PERIOD_R16_RF_256,
    WNRRC_POS_SCHDL_SI_PERIOD_R16_RF_512
}wnrrc_pos_schdl_si_period_r16_e;

typedef enum{
    WNRRC_POS_SCHDL_SI_BROADCAST_STATUS_R16_BRAODCASTING     = 0,
    WNRRC_POS_SCHDL_SI_BROADCAST_STATUS_R16_NOT_BRAODCASTING
}wnrrc_pos_schdl_si_broadcast_status_r16_e;

typedef enum{
    WNRRC_GNSS_ID_R16_GPS    = 0,
    WNRRC_GNSS_ID_R16_SBAS,
    WNRRC_GNSS_ID_R16_QZSS,
    WNRRC_GNSS_ID_R16_GALILEO,
    WNRRC_GNSS_ID_R16_GLONASS,
    WNRRC_GNSS_ID_R16_BDS
}wnrrc_gnss_id_r16_e;

typedef enum{
    WNRRC_SBAS_ID_R16_WAAS    = 0,
    WNRRC_SBAS_ID_R16_EQNOS,
    WNRRC_SBAS_ID_R16_MSAS,
    WNRRC_SBAS_ID_R16_GAGAN
}wnrrc_sbas_id_r16_e;

typedef enum{
    WNRRC_POS_SIB_TYPE_1_1     = 0,
    WNRRC_POS_SIB_TYPE_1_2,
    WNRRC_POS_SIB_TYPE_1_3,
    WNRRC_POS_SIB_TYPE_1_4,
    WNRRC_POS_SIB_TYPE_1_5,
    WNRRC_POS_SIB_TYPE_1_6,
    WNRRC_POS_SIB_TYPE_1_7,
    WNRRC_POS_SIB_TYPE_1_8,
    WNRRC_POS_SIB_TYPE_2_1,
    WNRRC_POS_SIB_TYPE_2_2,
    WNRRC_POS_SIB_TYPE_2_3,
    WNRRC_POS_SIB_TYPE_2_4,
    WNRRC_POS_SIB_TYPE_2_5,
    WNRRC_POS_SIB_TYPE_2_6,
    WNRRC_POS_SIB_TYPE_2_7,
    WNRRC_POS_SIB_TYPE_2_8,
    WNRRC_POS_SIB_TYPE_2_9,
    WNRRC_POS_SIB_TYPE_2_10,
    WNRRC_POS_SIB_TYPE_2_11,
    WNRRC_POS_SIB_TYPE_2_12,
    WNRRC_POS_SIB_TYPE_2_13,
    WNRRC_POS_SIB_TYPE_2_14,
    WNRRC_POS_SIB_TYPE_2_15,
    WNRRC_POS_SIB_TYPE_2_16,
    WNRRC_POS_SIB_TYPE_2_17,
    WNRRC_POS_SIB_TYPE_2_18,
    WNRRC_POS_SIB_TYPE_2_19,
    WNRRC_POS_SIB_TYPE_2_20,
    WNRRC_POS_SIB_TYPE_2_21,
    WNRRC_POS_SIB_TYPE_2_22,
    WNRRC_POS_SIB_TYPE_2_24,
    WNRRC_POS_SIB_TYPE_3_1,
    WNRRC_POS_SIB_TYPE_4_1,
    WNRRC_POS_SIB_TYPE_5_1,
    WNRRC_POS_SIB_TYPE_6_1,
    WNRRC_POS_SIB_TYPE_6_2,
    WNRRC_POS_SIB_TYPE_6_3
}wnrrc_pos_sib_type_r16_e;

typedef struct{
    u8                         encrypted_r16_valid:1;
    u8                         gnss_id_r16_valid:1;
    u8                         sbas_id_r16_valid:1;
    u8                         area_scope_r16_valid:1;
    u8                         rsv:4;
    u8                         gnss_id_r16;/*enumerate refer to wnrrc_gnss_id_r16_e*/
    u8                         sbas_id_r16;/*enumerate refer to wnrrc_sbas_id_r16_e*/
    u8                         pos_sib_type_r16;/*enumerate refer to wnrrc_pos_sib_type_r16_e*/
    bool                       encrypted_r16;
    bool                       area_scope_r16;
}wnrrc_pos_sib_type_r16;

typedef struct{
    u8                         pos_sib_num;/**/
    u8                         padding[3];
    wnrrc_pos_sib_type_r16     pos_sib_type[MAX_NR_SIB_NUM];
}wnrrc_pos_si_map_info_r16_t;

typedef struct{
    u8                              offset_to_si_used_r16_valid:1;
    u8                              rsv:7;
    u8                              si_period_r16;/*enumerate refer to wnrrc_pos_schdl_si_period_r16_e*/
    u8                              si_broadcast_status_r16;/*enumerate refer to wnrrc_pos_schdl_si_broadcast_status_r16_e*/
    u8                              padding;
    bool                            offset_to_si_used_r16;
    wnrrc_pos_si_map_info_r16_t     si_map_r16;
}wnrrc_pos_schdl_info_r16_t;

typedef struct{
    u8                                       pos_si_req_r16_valid:1;
    u8                                       pos_si_req_sul_r16_valid:1;
    u8                                       pos_si_req_redcap_r17_valid:1;
    u8                                       rsv:5;
    u8                                       pos_schdl_r16_num;
    u8                                       padding[2];
    wnrrc_pos_schdl_info_r16_t               pos_schdl_r16_list[MAX_NR_SI_MSG_NUM];
    wnrrc_si_req_cfg_t                       pos_si_req_r16;
    wnrrc_si_req_cfg_t                       pos_si_req_sul_r16;
    wnrrc_si_req_cfg_t                       pos_si_req_redcap_r17;
}wnrrc_pos_si_schdl_info_r16_t;

typedef enum{
    WNRRC_UAC_AC1_SEL_ASSIS_INFO_R16_A    = 0,
    WNRRC_UAC_AC1_SEL_ASSIS_INFO_R16_B,
    WNRRC_UAC_AC1_SEL_ASSIS_INFO_R16_C,
    WNRRC_UAC_AC1_SEL_ASSIS_INFO_R16_NOT_CONFIGURED
}wnrrc_uac_ac1_sel_assis_info_r16_e;


typedef struct{
    u8         uac_ac1_sel_assis_r16;/*enumerate refer to wnrrc_uac_ac1_sel_assis_info_r16_e*/
    u8         padding[3];
}wnrrc_uac_ac1_sel_assis_info_r16_t;

typedef struct{
    u8                                     ac1_sel_assis_r16_num;/*2...12*/
    u8                                     padding[3];
    wnrrc_uac_ac1_sel_assis_info_r16_t     ac1_sel_assis_r16_list[MAX_NR_PLMN_NUM];
}wnrrc_uac_bar_info_v1630_t;

typedef enum{
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_00      = 0,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_05,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_10,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_15,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_20,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_25,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_30,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_40,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_50,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_60,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_70,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_75,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_80,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_85,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_90,
    WNRRC_UAC_BAR_FACTOR_FOR_AI3_R17_P_95
}wnrrc_uac_bar_factor_for_ai3_r17_e;

typedef struct{
    u8          uac_bar_factor_ai3_r17_valid:1;
    u8          rsv:7;
    u8          uac_bar_factor_ai3_r17;/*enumerate refer to wnrrc_uac_bar_factor_for_ai3_r17_e*/
    u8          padding[2];
}wnrrc_uac_bar_info_set_v1700_t;

typedef struct{
    u8                                  bar_info_set_v1700_num;
    u8                                  padding[3];
    wnrrc_uac_bar_info_set_v1700_t      bar_info_v1700[MAX_NR_BAR_INFO_SET_NUM];
}wnrrc_uac_bar_info_v1700_t;

typedef enum{
    WNRRC_SDT_LCH_SR_DELAY_TMR_R17_SF_20     = 0,
    WNRRC_SDT_LCH_SR_DELAY_TMR_R17_SF_40,
    WNRRC_SDT_LCH_SR_DELAY_TMR_R17_SF_64,
    WNRRC_SDT_LCH_SR_DELAY_TMR_R17_SF_128,
    WNRRC_SDT_LCH_SR_DELAY_TMR_R17_SF_512,
    WNRRC_SDT_LCH_SR_DELAY_TMR_R17_SF_1024,
    WNRRC_SDT_LCH_SR_DELAY_TMR_R17_SF_2560
}wnrrc_sdt_lch_sr_delay_tmr_r17_e;

typedef enum{
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_32     = 0,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_100,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_200,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_400,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_600,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_800,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_1000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_2000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_4000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_8000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_9000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_10000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_12000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_24000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_48000,
    WNRRC_SDT_DATA_VOL_THRESHOLD_R17_BYTE_96000
}wnrrc_sdt_data_vol_threshold_r17_e;

typedef enum{
    WNRRC_T319_A_R17_MS_100     = 0,
    WNRRC_T319_A_R17_MS_200,
    WNRRC_T319_A_R17_MS_300,
    WNRRC_T319_A_R17_MS_400,
    WNRRC_T319_A_R17_MS_600,
    WNRRC_T319_A_R17_MS_1000,
    WNRRC_T319_A_R17_MS_2000,
    WNRRC_T319_A_R17_MS_3000,
    WNRRC_T319_A_R17_MS_4000
}wnrrc_t319_a_r17_e;

typedef struct{
    u8                  rsrp_threshold;/*rsrp range is 0...127*/
    u8                  lch_sr_delay_tmr_r17;/*enumerate refer to wnrrc_sdt_lch_sr_delay_tmr_r17_e*/
    u8                  data_vol_threshold_r17;/*enumerate refer to wnrrc_sdt_data_vol_threshold_r17_e*/
    u8                  t319_a_r17;/*enumerate refer to wnrrc_t319_a_r17_e*/
}wnrrc_sdt_cfg_common_sib_r17_t;

typedef struct{
    bool          cell_bar_redcap_1rx_r17;/*TRUE: barred, FALSE:not barred*/
    bool          cell_bar_redcap_2rx_r17;/*TRUE: barred，FALSE:not barred*/
}wnrrc_cell_bar_redcap_r17_t;

typedef struct{
    u8                              half_duplex_allow_r17_valid:1;
    u8                              cell_bar_redcap_r17_valid:1;
    u8                              rsv:6;
    u8                              padding[3];
    bool                            half_duplex_allow_r17;/*TRUE:allow, FALSE: not allow*/
    wnrrc_cell_bar_redcap_r17_t     cell_bar_redcap_r17;
}wnrrc_redcap_cfg_common_sib_r17_t;

typedef struct{
    u8        redcap_pri_r17_valid:1;
    u8        slicing_pri_r17_valid:1;
    u8        msg3_repeti_pri_r17_valid:1;
    u8        sdt_pri_r17_valid:1;
    u8        rsv:4;
    u8        padding[3];
    u8        redcap_pri_r17;/*feature priority r17, value range is 0...7*/
    u8        slicing_pri_r17;/*feature priority r17, value range is 0...7*/
    u8        msg3_repeti_pri_r17;/*feature priority r17, value range is 0...7*/
    u8        sdt_pri_r17;/*feature priority r17, value range is 0...7*/
}wnrrc_feature_priorit_r17_t;

typedef enum{
    WNRRC_SI_BROADCAST_STATUS_R17_BRAODCASTING     = 0,
    WNRRC_SI_BROADCAST_STATUS_R17_NOT_BRAODCASTING
}wnrrc_si_broadcast_status_r17_e;

typedef enum{
    WNRRC_SI_PERIOD_R17_RF_8     = 0,
    WNRRC_SI_PERIOD_R17_RF_16,
    WNRRC_SI_PERIOD_R17_RF_32,
    WNRRC_SI_PERIOD_R17_RF_64,
    WNRRC_SI_PERIOD_R17_RF_128,
    WNRRC_SI_PERIOD_R17_RF_256,
    WNRRC_SI_PERIOD_R17_RF_512
}wnrrc_si_period_r17_e;

typedef enum{
    WNRRC_SIB_TYPE1_R17_15      = 0,
    WNRRC_SIB_TYPE1_R17_16,
    WNRRC_SIB_TYPE1_R17_17,
    WNRRC_SIB_TYPE1_R17_18,
    WNRRC_SIB_TYPE1_R17_19,
    WNRRC_SIB_TYPE1_R17_20,
    WNRRC_SIB_TYPE1_R17_21
}wnrrc_sib_type1_r17_e;

typedef enum{
    WNRRC_POS_SIB_TYPE_R17_1_9     = 0,
    WNRRC_POS_SIB_TYPE_R17_1_10,
    WNRRC_POS_SIB_TYPE_R17_2_24,
    WNRRC_POS_SIB_TYPE_R17_2_25,
    WNRRC_POS_SIB_TYPE_R17_6_4,
    WNRRC_POS_SIB_TYPE_R17_6_5,
    WNRRC_POS_SIB_TYPE_R17_6_6
}wnrrc_pos_sib_type_r17_e;

typedef struct{
    u8         encrypted_r17_valid:1;
    u8         gnss_id_r17_valid:1;
    u8         sbas_id_r17_valid:1;
    u8         rsv:5;
    u8         pos_sib_type_r17;/*enumerate refer to wnrrc_pos_sib_type_r17_e*/
    u8         gnss_id_r17;/*refer to gnss_id_r16*/
    u8         sbas_id_r17;/*refer to sbas_id_r16*/
    bool       encrypted_r17;
}wnrrc_sib_type2_r17_t;

typedef struct{
    u8                           sib_type_r17;/*0: type1,  1:type2*/
    u8                           sib_type1_r17;/*enumerate refer to wnrrc_sib_type1_r17_e*/
    u8                           padding[2];
    wnrrc_sib_type2_r17_t        type2_r17;
}wnrrc_sib_type_r17_t;

typedef struct{
    u8                           value_tag_r17_valid:1;
    u8                           area_scope_r17_valid:1;
    u8                           rsv:6;
    u8                           value_tag_r17;/*0...31*/
    u8                           padding[2];
    wnrrc_sib_type_r17_t         sib_type_r17;
    bool                         area_scope_r17;
}wnrrc_sib_type_info_v1700_t;

typedef struct{
    u8                               sib_type_info_num;
    u8                               padding[3];
    wnrrc_sib_type_info_v1700_t      sib_type_v1700[MAX_NR_SIB_NUM];
}wnrrc_sib_map_v1700_t;


typedef struct{
    u8                         si_broadcast_status_r17;/*enumerate refer to wnrrc_si_broadcast_status_r17_e*/
    u16                        si_win_pos_r17;/*1...256*/
    u8                         si_period_r17;/*enumerate refer to wnrrc_si_period_r17_e*/
    wnrrc_sib_map_v1700_t      sib_map_v1700;
}wnrrc_si_schdl_info2_r17_t;

typedef struct{
    u8                             dummy_valid:1;
    u8                             rsv:7;
    u8                             schdl_info2_r17_num;
    u8                             padding[2];
    wnrrc_si_schdl_info2_r17_t     schdl_info_list[MAX_NR_SI_MSG_NUM];
    wnrrc_si_req_cfg_t             dummy;
}wnrrc_si_schdl_info_v1700_t;

typedef struct{
    u8                        si_req_cfg_redcap_r17_valid:1;
    u8                        rsv:7;
    u8                        padding[3];
    wnrrc_si_req_cfg_t        si_req_cfg_redcap_r17;
}wnrrc_si_schdl_info_v1740_t;

typedef struct{
    u8                                   si_schdl_info_v1740_valid:1;
    u8                                   rsv:7;
    u8                                   padding[3];
    wnrrc_si_schdl_info_v1740_t          si_schdl_info_v1740;
}wnrrc_sib1_v1740_t;

typedef struct{
    u16                                  hsdn_cell_r17_valid:1;
    u16                                  uac_bar_v1700_valid:1;
    u16                                  sdt_cfg_r17_valid:1;
    u16                                  redcap_r17_valid:1;
    u16                                  feature_pri_valid:1;
    u16                                  si_schdl_v1700_valid:1;
    u16                                  hyper_sfn_r17_valid:1;
    u16                                  edrx_allow_idle_r17_valid:1;
    u16                                  edrx_allow_inactive_r17_valid:1;
    u16                                  intra_freq_resel_redcap_r17_valid:1;
    u16                                  cell_bar_ntn_r17_valid:1;
    u16                                  sib1_v1740_valid:1;
    u16                                  rsv:4;
    u8                                   hyper_sfn_r17[2];/*bit string 10 bits*/
    bool                                 hsdn_cell_r17;
    wnrrc_uac_bar_info_v1700_t           uac_bar_v1700;
    wnrrc_sdt_cfg_common_sib_r17_t       sdt_cfg_r17;
    wnrrc_redcap_cfg_common_sib_r17_t    redcap_r17;
    wnrrc_feature_priorit_r17_t          feature_pri;
    wnrrc_si_schdl_info_v1700_t          si_schdl_v1700;
    bool                                 edrx_allow_idle_r17;
    bool                                 edrx_allow_inactive_r17;
    bool                                 intra_freq_resel_redcap_r17;
    bool                                 cell_bar_ntn_r17;
    wnrrc_sib1_v1740_t                   sib1_v1740;
}nr_sib1_v1700_t;

typedef struct{
    u8                                    uac_bar_1630_valid:1;
    u8                                    sib1_v1700_valid:1;
    u8                                    rsv:6;
    u8                                    padding[3];
    wnrrc_uac_bar_info_v1630_t            uac_bar_1630;
    nr_sib1_v1700_t                       sib1_v1700;
}wnrrc_sib1_v1630_t;

typedef struct{
    u8                                  idle_meas_eutra_r16_valid:1;
    u8                                  idle_meas_nr_r16_valid:1;
    u8                                  pos_si_valid:1;
    u8                                  sib1_v1630_valid:1;
    u8                                  rsv:4;
    u8                                  padding[3];
    bool                                idle_meas_eutra_r16;
    bool                                idle_meas_nr_r16;
    wnrrc_pos_si_schdl_info_r16_t       pos_si;
    wnrrc_sib1_v1630_t                  sib1_v1630;
}nr_sib1_v1610_t;

typedef struct{
    u32                                conn_est_fail_ctrl_valid:1;
    u32                                si_schdl_valid:1;
    u32                                serv_cell_cfg_com_valid:1;
    u32                                ims_emergency_support_valid:1;
    u32                                ecall_ims_support_valid:1;
    u32                                ue_tmr_val_valid:1;
    u32                                uac_bar_valid:1;
    u32                                use_full_resume_id_valid:1;
    u32                                late_non_critial_ext_valid:1;
    u32                                sib1_v1610_valid:1;
    u32                                rsv:22;
    wnrrc_cell_select_info_t           cell_select;
    wnrrc_cell_access_info_t           cell_access;
    wnrrc_conn_est_fail_ctrl_t         conn_est_fail_ctrl;
    wnrrc_si_schdl_info_t              si_schdl;
    wnrrc_serv_cell_cfg_comm_sib_t     serv_cell_cfg_common_sib;
    bool                               ims_emergency_support;
    bool                               ecall_ims_support;
    wnrrc_ue_tmr_and_cons_t            ue_tmr_val;
    wnrrc_uac_bar_info_t               uac_bar;
    bool                               use_full_resume_id;
    u8                                 late_non_critial_ext;/*octet string*/
    u8                                 padding[3];
    nr_sib1_v1610_t                    sib1_v1610;
}wnrrc_sib1_info_t;
/**********************sib1 parameters end**********************/
/**********************sib19 parameters start**********************/
typedef struct{
    u16         sfn_r17;/*0...1023*/
    u8          sub_frame_r17;/*0...9*/
    u8          padding;
}wnrrc_epoch_time_r17_t;

typedef enum{
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S5      = 0,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S10,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S15,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S20,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S25,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S30,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S35,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S40,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S45,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S50,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S55,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S60,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S120,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S180,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S240,
    WNRRC_NTN_UL_SYNC_VALID_DURA_R17_S900
}wnrrc_ntn_ul_sync_valid_dura_r17_e;

typedef struct{
    u8       ta_com_drift_r17_valid:1;
    u8       ta_com_drift_vari_r17_valid:1;
    u8       rsv:6;
    u16      ta_com_drift_vari_r17;/*0...28949*/
    u8       padding;
    u32      ta_common_r17;/*0...66485757*/
    s32      ta_com_drift_r17;/*-257303...257303*/
}wnrrc_ta_info_r17_t;

typedef enum{
    WNRRC_NTN_POLARIZATION_R17_RHCP     = 0,
    WNRRC_NTN_POLARIZATION_R17_LHCP,
    WNRRC_NTN_POLARIZATION_R17_LINEAR
}wnrrc_ntn_polarization_r17_e;


typedef struct{
    s32       pos_x;/*-33554432...33554431*/
    s32       pos_y;/*-33554432...33554431*/
    s32       pos_z;/*-33554432...33554431*/
    s32       pos_vx;/*-33554432...33554431*/
    s32       pos_vy;/*-33554432...33554431*/
    s32       pos_vz;/*-33554432...33554431*/
}wnrrc_pos_veloc_r17_t;

typedef struct{
    u64        semi_major_axis_r17;/*0...8589934591*/
    u32        eccentric_r17;/*0...1048575*/
    u32        periapsis_r17;/*0...268435455*/
    u32        longitude_r17;/*0...268435455*/
    s32        inclination_r17;/*-67108864...67108863*/
    u32        mean_anoma_r17;/*0...268435455*/
}wnrrc_orbital_r17_t;

typedef enum{
    WNRRC_EPHEME_INFO_R17_CHOICE_POSITION_VELOCITY_R17    = 0,
    WNRRC_EPHEME_INFO_R17_CHOICE_ORBITAL_R17
}wnrrc_epheme_info_r17_choice_e;

typedef struct{
    u8                                  epheme_choice;/*enumerate refer to wnrrc_epheme_info_r17_choice_e*/
    union{
        wnrrc_pos_veloc_r17_t           pos_veloc_r17;
        wnrrc_orbital_r17_t             orbital_r17;
    }u;
}wnrrc_epheme_info_r17_t;

typedef struct{
    u16                          epoch_time_valid:1;
    u16                          ntn_ul_sync_valid_dura_r17_valid:1;
    u16                          cell_spec_k_off_r17_valid:1;
    u16                          kmac_r17_valid:1;
    u16                          ta_info_r17_valid:1;
    u16                          ntn_pola_dl_r17_valid:1;
    u16                          ntn_pola_ul_r17_valid:1;
    u16                          ephem_r17_valid:1;
    u16                          ta_report_r17_valid:1;
    u16                          rsv:7;
    u8                           ntn_pola_dl_r17;/*enumerate refer to wnrrc_ntn_polarization_r17_e*/
    u8                           ntn_pola_ul_r17;/*enumerate refer to wnrrc_ntn_polarization_r17_e*/
    wnrrc_epoch_time_r17_t       epoch_time;
    u8                           ntn_ul_sync_valid_dura_r17;/*enumerate refer to wnrrc_ntn_ul_sync_valid_dura_r17_e*/
    u16                          cell_spec_k_off_r17;/*1...1023*/
    u8                           kmac_r17;/*1...512*/
    wnrrc_ta_info_r17_t          ta_info_r17;
    wnrrc_epheme_info_r17_t      ephem_r17;
    bool                         ta_report_r17;
}wnrrc_ntn_cfg_r17_t;

typedef struct{
    u8                         ntn_cfg_valid:1;
    u8                         carrier_freq_arfcn_valid:1;
    u8                         pci_valid:1;
    u8                         rsv:6;
    u16                        pci;
    u8                         padding;
    wnrrc_ntn_cfg_r17_t        ntn_cfg;
    u32                        carrier_freq_arfcn;
}wnrrc_ntn_neigh_cell_cfg_r17_t;


typedef struct{
    u8                                ntn_cfg_r17_valid:1;
    u8                                t_service_r17_valid:1;
    u8                                ref_loc_r17_valid:1;
    u8                                distance_thresh_r17_valid:1;
    u8                                ntn_nc_list_valid:1;
    u8                                late_non_critial_ext_valid:1;
    u8                                ntn_nc_list_ext_valid:1;
    u8                                rsv:1;
    u8                                ref_loc_r17;/*octet string*/
    u8                                ntn_nc_num;/*1...4*/
    u8                                ntn_nc_ext_num;/*1...4*/
    wnrrc_ntn_cfg_r17_t               ntn_cfg_r17;
    u64                               t_service_r17;/*0...549755813887*/
    u16                               distance_thresh_r17;/*0...65525*/
    wnrrc_ntn_neigh_cell_cfg_r17_t    ntn_nc_list[MAX_NR_CELL_NTN_R17_NUM];
    u8                                late_non_critial_ext;/*octet string*/
    u8                                padding[3];
    wnrrc_ntn_neigh_cell_cfg_r17_t    ntn_nc_list_ext[MAX_NR_CELL_NTN_R17_NUM];
}wnrrc_sib19_info_t;
/**********************sib19 parameters end**********************/
/**********************sib2 parameters start**********************/
typedef struct{
    u8          rsrp_thresh_valid:1;
    u8          rsrq_thresh_valid:1;
    u8          snr_thresh_valid:1;
    u8          rsv:5;
    u8          rsrp_thresh;/*0...127*/
    u8          rsrq_thresh;/*0...127*/
    u8          snr_thresh;/*0...127*/
}wnrrc_thresh_nr_t;

typedef enum{
    WNRRC_Q_OFFSET_RANGE_DB_NEG_24      = 0,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_22,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_20,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_18,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_16,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_14,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_12,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_10,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_8,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_6,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_5,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_4,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_3,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_2,
    WNRRC_Q_OFFSET_RANGE_DB_NEG_1,
    WNRRC_Q_OFFSET_RANGE_DB_0,
    WNRRC_Q_OFFSET_RANGE_DB_1,
    WNRRC_Q_OFFSET_RANGE_DB_2,
    WNRRC_Q_OFFSET_RANGE_DB_3,
    WNRRC_Q_OFFSET_RANGE_DB_4,
    WNRRC_Q_OFFSET_RANGE_DB_5,
    WNRRC_Q_OFFSET_RANGE_DB_6,
    WNRRC_Q_OFFSET_RANGE_DB_8,
    WNRRC_Q_OFFSET_RANGE_DB_10,
    WNRRC_Q_OFFSET_RANGE_DB_12,
    WNRRC_Q_OFFSET_RANGE_DB_14,
    WNRRC_Q_OFFSET_RANGE_DB_16,
    WNRRC_Q_OFFSET_RANGE_DB_18,
    WNRRC_Q_OFFSET_RANGE_DB_20,
    WNRRC_Q_OFFSET_RANGE_DB_22,
    WNRRC_Q_OFFSET_RANGE_DB_24
}wnrrc_q_offset_range_e;

typedef enum{
    WNRRC_SIB2_Q_HYST_DB_0      = 0,
    WNRRC_SIB2_Q_HYST_DB_1,
    WNRRC_SIB2_Q_HYST_DB_2,
    WNRRC_SIB2_Q_HYST_DB_3,
    WNRRC_SIB2_Q_HYST_DB_4,
    WNRRC_SIB2_Q_HYST_DB_5,
    WNRRC_SIB2_Q_HYST_DB_6,
    WNRRC_SIB2_Q_HYST_DB_8,
    WNRRC_SIB2_Q_HYST_DB_10,
    WNRRC_SIB2_Q_HYST_DB_12,
    WNRRC_SIB2_Q_HYST_DB_14,
    WNRRC_SIB2_Q_HYST_DB_16,
    WNRRC_SIB2_Q_HYST_DB_18,
    WNRRC_SIB2_Q_HYST_DB_20,
    WNRRC_SIB2_Q_HYST_DB_22,
    WNRRC_SIB2_Q_HYST_DB_24
}wnrrc_sib2_q_hyst_e;

typedef enum{
    WNRRC_MOBILITY_STATE_T_EVALUATION_S30       = 0,
    WNRRC_MOBILITY_STATE_T_EVALUATION_S60,
    WNRRC_MOBILITY_STATE_T_EVALUATION_S120,
    WNRRC_MOBILITY_STATE_T_EVALUATION_S180,
    WNRRC_MOBILITY_STATE_T_EVALUATION_S240
}wnrrc_mobility_state_t_evaluation_e;


typedef enum{
    WNRRC_MOBILITY_STATE_T_HYST_NORMAL_S30     = 0,
    WNRRC_MOBILITY_STATE_T_HYST_NORMAL_S60,
    WNRRC_MOBILITY_STATE_T_HYST_NORMAL_S120,
    WNRRC_MOBILITY_STATE_T_HYST_NORMAL_S180,
    WNRRC_MOBILITY_STATE_T_HYST_NORMAL_S240
}wnrrc_mobility_state_t_hysc_normal_e;

typedef struct{
    u8          t_evaluation;/*enumerate refer to wnrrc_mobility_state_t_evaluation_e*/
    u8          t_hyst_normal;/*enumrate refer to wnrrc_mobility_state_t_hysc_normal_e*/
    u8          n_cell_change_medium;/*1...16*/
    u8          n_cell_change_high;/*1...16*/
}wnrrc_mobility_state_param_t;

typedef struct{
    u8                                    sf_medium;/*0: db-6, 
                                                      1: db-4,
                                                      2: db-2,
                                                      3: db0*/
    u8                                    sf_high;/*0:db-6,
                                                    1:db-4,
                                                    2:db-2,
                                                    3:db0*/
    u8                                    padding[2];
}nr_q_hyst_sf_t;


typedef struct{
    wnrrc_mobility_state_param_t          mobility_state;
    nr_q_hyst_sf_t                        q_hyst_sf;
}wnrrc_sib2_speed_state_resel_pars_t;


typedef struct{
    u8                                     ssb_to_avg_num_valid:1;
    u8                                     thresh_nr_valid:1;
    u8                                     range_to_best_cell_valid:1;
    u8                                     speed_stat_resel_param_valid:1;
    u8                                     rsv:4;
    u8                                     ssb_to_avg_num;/*2...16*/
    u8                                     q_hyst;/*enumerate refer to wnrrc_sib2_q_hyst_e*/
    u8                                     range_to_best_cell;/*enumerate refer to wnrrc_q_offset_range_e*/
    wnrrc_thresh_nr_t                      thresh_nr;
    wnrrc_sib2_speed_state_resel_pars_t    speed_stat_resel_param;
}wnrrc_cell_resel_info_common_t;

typedef enum{
    WNRRC_CELL_RESEL_SUB_PRI_O_DOT_2    = 0,
    WNRRC_CELL_RESEL_SUB_PRI_O_DOT_4,
    WNRRC_CELL_RESEL_SUB_PRI_O_DOT_6,
    WNRRC_CELL_RESEL_SUB_PRI_O_DOT_8
}wnrrc_cell_resel_sub_pri_e;

typedef struct{
    u8                   thresh_serv_low_q_valid:1;
    u8                   cell_resel_sub_pri_valid:1;
    u8                   rsv:6;
    u8                   s_non_intra_search_p;/*0...31*/
    u8                   s_non_intra_search_q;/*0...31*/
    u8                   thresh_serv_low_p;/*0...31*/
    u8                   thresh_serv_low_q;/*0...31*/
    u8                   cell_resel_pri;/*0...7*/
    u8                   cell_resel_sub_pri;/*enumerate refer to wnrrc_cell_resel_sub_pri_e*/
    u8                   padding;
}wnrrc_cell_resel_serv_freq_info_t;

typedef struct{
    u16                   freq_band_ind;
    u8                    pmax_num;
    u8                    padding;
    nr_ns_pmax_val_t      pmax_list[MAX_NR_NS_PMAX_NUM];
}wnrrc_multi_band_info_t;

typedef enum{
    WNRRC_SSB_MTC_PERIOD_SF_5    = 0,
    WNRRC_SSB_MTC_PERIOD_SF_10,
    WNRRC_SSB_MTC_PERIOD_SF_20,
    WNRRC_SSB_MTC_PERIOD_SF_40,
    WNRRC_SSB_MTC_PERIOD_SF_80,
    WNRRC_SSB_MTC_PERIOD_SF_160
}wnrrc_ssb_mtc_period_e;

typedef enum{
    WNRRC_SSB_MTC_DURATION_SF_1     = 0,
    WNRRC_SSB_MTC_DURATION_SF_2,
    WNRRC_SSB_MTC_DURATION_SF_3,
    WNRRC_SSB_MTC_DURATION_SF_4,
    WNRRC_SSB_MTC_DURATION_SF_5
}wnrrc_ssb_mtc_duration_e;

typedef struct{
    u8          period;/*enumerate refer to wnrrc_ssb_mtc_period_e*/
    u8          offset;
    u8          duration;/*enumerate refer to wnrrc_ssb_mtc_duration_e*/
    u8          padding;
}wnrrc_ssb_mtc_t;

typedef struct{
    u8            meas_slots[10];/*bit string(size(1...80))*/
    u8            end_symbol;/*0...3*/
    u8            padding;
}wnrrc_ss_rssi_meas_t;

typedef struct{
    u8      bitmap_type;/*0: short bitmap 
                          1: media bitmap
                          2: long bitmap*/
    u8      padding[3];
    union{
        u8      short_bitmap;/*bit string size 4*/
        u8      meidum_bitmap;/*bit string size 8*/
        u8      long_bitmap[8];/*bit string size 64*/    
    }u;
}wnrrc_ssb_to_meas_t;

typedef enum{
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_MEDIUM_0_DOT_25     = 0,
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_MEDIUM_0_DOT_5,
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_MEDIUM_0_DOT_75,
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_MEDIUM_1_DOT_0
}wnrrc_speed_state_scale_factor_sf_medium_e;


typedef enum{
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_HIGH_0_DOT_25     = 0,
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_HIGH_0_DOT_5,
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_HIGH_0_DOT_75,
    WNRRC_SPEED_STATE_SCALE_FACTOR_SF_HIGH_1_DOT_0
}wnrrc_speed_state_scale_factor_sf_high_e;

typedef struct{
    u8     sf_media;/*enumerate refer to wnrrc_speed_state_scale_factor_sf_medium_e*/
    u8     sf_high;/*enumerate refer to wnrrc_speed_state_scale_factor_sf_high_e*/
    u8     padding[2];
}wnrrc_speed_state_scale_factor_t;

typedef enum{
    WNRRC_SMTC2_LP_R16_PERIOD_SF_10   = 0,
    WNRRC_SMTC2_LP_R16_PERIOD_SF_20,
    WNRRC_SMTC2_LP_R16_PERIOD_SF_40,
    WNRRC_SMTC2_LP_R16_PERIOD_SF_80,
    WNRRC_SMTC2_LP_R16_PERIOD_SF_160
}wnrrc_smtc2_lp_r16_period_e;

typedef struct{
    u8       pci_list_valid:1;
    u8       period;/*enumerate refer to wnrrc_smtc2_lp_r16_period_e*/
    u8       padding[2];
    u8       pci_num;
    u16      pci_list[MAX_NR_PCI_NUM_PER_SMTC];
}wnrrc_smtc2_lp_r16_t;

typedef enum{
    WNRRC_SSB_POS_QCL_RELATION_R16_N1    = 0,
    WNRRC_SSB_POS_QCL_RELATION_R16_N2,
    WNRRC_SSB_POS_QCL_RELATION_R16_N4,
    WNRRC_SSB_POS_QCL_RELATION_R16_N8
}wnrrc_ssb_pos_qcl_com_r16_e;

typedef enum{
    WNRRC_SSB_POS_QCL_RELATION_R17_N32    = 0,
    WNRRC_SSB_POS_QCL_RELATION_R17_N64
}wnrrc_ssb_pos_qcl_com_r17_e;

typedef struct{
    u8            offset_r17;/*0...167*/
    u8            pci_num;/*1...64*/
    u16           pci_list[MAX_NR_PCI_NUM_PER_SMTC];
}wnrrc_smtc4_r17_t;

typedef struct{
    u8                    smtc4_num;/*1...3*/
    u8                    padding[3];
    wnrrc_smtc4_r17_t     smtc4[3];
}wnrrc_smtc4_list_r17_t;


typedef struct{
    u16                                  q_rx_lev_min_sul_valid:1;
    u16                                  q_qual_min_valid:1;
    u16                                  s_intra_search_q_valid:1;
    u16                                  multi_band_list_valid:1;
    u16                                  multi_band_sul_list_valid:1;
    u16                                  p_max_valid:1;
    u16                                  smtc_valid:1;
    u16                                  ss_rssi_meas_valid:1;
    u16                                  ssb_to_meas_valid:1;
    u16                                  speed_factor_valid:1;
    u16                                  smtc2_lp_valid:1;
    u16                                  ssb_pos_qcl_relation_r16_valid:1;
    u16                                  ssb_pos_qcl_relation_r17_valid:1;
    u16                                  smtc4_list_r17_valid:1;
    u16                                  rsv:2;
    s8                                   p_max;/*-30...33*/
    s8                                   q_rx_lev_min;/*-70...-22*/
    s8                                   q_rx_lev_min_sul;/*-70...-22*/
    s8                                   q_qual_min;/*-43...-12*/
    u8                                   s_intra_search_p;/*0...31*/
    u8                                   s_intra_search_q;/*0...31*/
    u8                                   t_resel_nr;/*0...7*/
    u8                                   multi_band_num;/**/
    u8                                   multi_band_sul_num;/**/
    u8                                   padding;
    wnrrc_multi_band_info_sib_t          multi_band_list[MAX_NR_MULTI_BAND_NUM];
    wnrrc_multi_band_info_sib_t          multi_band_sul_list[MAX_NR_MULTI_BAND_NUM];    
    wnrrc_ssb_mtc_t                      smtc;
    wnrrc_ss_rssi_meas_t                 ss_rssi_meas;
    wnrrc_ssb_to_meas_t                  ssb_to_meas;
    bool                                 derive_ssb_idx_from_cell;
    wnrrc_speed_state_scale_factor_t     speed_factor;
    wnrrc_smtc2_lp_r16_t                 smtc2_lp;
    u8                                   ssb_pos_qcl_relation_r16;/*wnrrc_ssb_pos_qcl_com_r16_e*/
    u8                                   ssb_pos_qcl_relation_r17;/*wnrrc_ssb_pos_qcl_com_r17_e*/
    u8                                   padding1[2];
    wnrrc_smtc4_list_r17_t               smtc4_list_r17;
}wnrrc_intra_freq_cell_resel_info_t;

typedef enum{
    WNRRC_LOW_MOBILITY_S_SEARCH_DELTA_R16_DB_3     = 0,
    WNRRC_LOW_MOBILITY_S_SEARCH_DELTA_R16_DB_6,
    WNRRC_LOW_MOBILITY_S_SEARCH_DELTA_R16_DB_9,
    WNRRC_LOW_MOBILITY_S_SEARCH_DELTA_R16_DB_12,
    WNRRC_LOW_MOBILITY_S_SEARCH_DELTA_R16_DB_15
}wnrrc_low_mobility_s_search_delta_p_r16_e;

typedef enum{
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S5       = 0,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S10,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S20,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S30,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S60,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S120,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S180,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S240,
    WNRRC_LOW_MOBILITY_T_SEARCH_DELTA_R16_S300
}wnrrc_low_mobility_t_search_delta_p_r16_e;

typedef struct{
    u8      s_search_delta_p_r16;/*enumerate refer to wnrrc_low_mobility_s_search_delta_p_r16_e*/
    u8      t_search_delta_p_r16;/*enumerate refer to wnrrc_low_mobility_t_search_delta_p_r16_e*/
    u8      padding[2];
}wnrrc_low_mobility_eval_r16_t;

typedef struct{
    u8       s_search_thresh_q_r16_valid:1;
    u8       rsv:7;
    u8       s_search_thresh_p_r16;/*reselection threshold, 0..31*/
    u8       s_search_thresh_q_r16;/*reselection threshold Q,0...31*/
    u8       padding;
}wnrrc_cell_edge_eval_r16_t;

typedef struct{
    u8                                 low_mobility_valid:1;
    u8                                 cell_edge_eval_valid:1;
    u8                                 combin_relax_meas_cond_r16_valid:1;
    u8                                 high_pri_meas_relax_r16_valid:1;
    u8                                 rsv:4;
    u8                                 padding[3];
    wnrrc_low_mobility_eval_r16_t      low_mobility;
    wnrrc_cell_edge_eval_r16_t         cell_edge_eval;
    bool                               combin_relax_meas_cond_r16;
    bool                               high_pri_meas_relax_r16;
}wnrrc_relax_meas_r16_t;

typedef enum{
    WNRRC_STATION_MOBILITY_S_SEARCH_DELTA_R17_DB2       = 0,
    WNRRC_STATION_MOBILITY_S_SEARCH_DELTA_R17_DB3,
    WNRRC_STATION_MOBILITY_S_SEARCH_DELTA_R17_DB6,
    WNRRC_STATION_MOBILITY_S_SEARCH_DELTA_R17_DB9,
    WNRRC_STATION_MOBILITY_S_SEARCH_DELTA_R17_DB12,
    WNRRC_STATION_MOBILITY_S_SEARCH_DELTA_R17_DB15
}wnrrc_station_mobility_s_search_delta_r17_e;

typedef enum{
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S5     = 0,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S10,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S20,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S30,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S60,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S120,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S180,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S240,
    WNRRC_STATION_MOBILITY_T_SEARCH_DELTA_R17_S300
}wnrrc_station_mobility_t_search_delta_r17_e;

typedef struct{
    u8      s_search_delta_p_station_r17;/*enumerate refer to wnrrc_station_mobility_s_search_delta_r17_e*/
    u8      t_search_delta_p_station_r17;/*enumerate refer to wnrrc_station_mobility_t_search_delta_r17_e*/
    u8      padding[2];
}wnrrc_station_mobility_eval_r17_t;

typedef struct{
    u8    s_search_thresh_p2_r17;/*0...31*/
    u8    s_search_thresh_q2_r17;/*0...31*/
    u8    padding[2];
}wnrrc_cell_edge_eval_station_r17_t;

typedef struct{
    u8                                     cell_edge_r17_valid:1;
    u8                                     combin_relax_meas_r17_valid:1;
    u8                                     rsv:6;
    u8                                     padding[3];
    wnrrc_station_mobility_eval_r17_t      station_mobility;
    wnrrc_cell_edge_eval_station_r17_t     cell_edge_r17;
    bool                                   combin_relax_meas_r17;
}wnrrc_relax_meas_r17_t;

typedef struct{
    u8                                     relax_meas_r16_valid:1;
    u8                                     relax_meas_r17_valid:1;
    u8                                     cell_equival_size_r17_valid:1;
    u8                                     rsv:5;
    u8                                     cell_equival_size_r17;/*2...16*/
    u8                                     padding[2];
    wnrrc_cell_resel_info_common_t         cell_resel_com;
    wnrrc_cell_resel_serv_freq_info_t      cell_resel_serv_freq;
    wnrrc_intra_freq_cell_resel_info_t     intra_freq_resel;
    wnrrc_relax_meas_r16_t                 relax_meas_r16;
    wnrrc_relax_meas_r17_t                 relax_meas_r17;
}wnrrc_sib2_info_t;
/**********************sib2 parameters end**********************/

/**********************sib3 parameters start**********************/
typedef enum{
    NR_Q_OFFSET_RANGE_DB_NEG_24    = 0,
    NR_Q_OFFSET_RANGE_DB_NEG_22,
    NR_Q_OFFSET_RANGE_DB_NEG_20,
    NR_Q_OFFSET_RANGE_DB_NEG_18,
    NR_Q_OFFSET_RANGE_DB_NEG_16,
    NR_Q_OFFSET_RANGE_DB_NEG_14,
    NR_Q_OFFSET_RANGE_DB_NEG_12,
    NR_Q_OFFSET_RANGE_DB_NEG_10,
    NR_Q_OFFSET_RANGE_DB_NEG_8,
    NR_Q_OFFSET_RANGE_DB_NEG_6,
    NR_Q_OFFSET_RANGE_DB_NEG_5,
    NR_Q_OFFSET_RANGE_DB_NEG_4,
    NR_Q_OFFSET_RANGE_DB_NEG_3,
    NR_Q_OFFSET_RANGE_DB_NEG_2,
    NR_Q_OFFSET_RANGE_DB_NEG_1,
    NR_Q_OFFSET_RANGE_DB_0,
    NR_Q_OFFSET_RANGE_DB_1,
    NR_Q_OFFSET_RANGE_DB_2,
    NR_Q_OFFSET_RANGE_DB_3,
    NR_Q_OFFSET_RANGE_DB_4,
    NR_Q_OFFSET_RANGE_DB_5,
    NR_Q_OFFSET_RANGE_DB_6,
    NR_Q_OFFSET_RANGE_DB_8,
    NR_Q_OFFSET_RANGE_DB_10,
    NR_Q_OFFSET_RANGE_DB_12,
    NR_Q_OFFSET_RANGE_DB_14,
    NR_Q_OFFSET_RANGE_DB_16,
    NR_Q_OFFSET_RANGE_DB_18,
    NR_Q_OFFSET_RANGE_DB_20,
    NR_Q_OFFSET_RANGE_DB_22,
    NR_Q_OFFSET_RANGE_DB_24
}nr_q_offset_range_e;

typedef struct{
    u8                q_rx_lev_min_offset_cell_valid:1;
    u8                q_rx_lev_min_offset_cell_sul_valid:1;
    u8                q_qual_min_offset_cell_valid:1;
    u16               pci;/*0...1007*/
    u8                q_offset_range;/*enumerate refer to nr_q_offset_range_e */
    u8                q_rx_lev_min_offset_cell;/*1..8*/
    u8                q_rx_lev_min_offset_cell_sul;/*1...8*/
    u8                q_qual_min_offset_cell;
    u8                padding;
}nr_intra_freq_neigh_cell_t;

typedef struct{
    u8                               cell_num;/*1...16*/
    u8                               padding[3];
    nr_intra_freq_neigh_cell_t       intra_cell_list[MAX_NR_CELL_INTRA_NUM];
}nr_intra_freq_neigh_cell_list_t;

typedef enum{
    NR_PCI_RANGE_N_4    = 0,
    NR_PCI_RANGE_N_8,
    NR_PCI_RANGE_N_12,
    NR_PCI_RANGE_N_16,
    NR_PCI_RANGE_N_24,
    NR_PCI_RANGE_N_32,
    NR_PCI_RANGE_N_48,
    NR_PCI_RANGE_N_64,
    NR_PCI_RANGE_N_84,
    NR_PCI_RANGE_N_96,
    NR_PCI_RANGE_N_128,
    NR_PCI_RANGE_N_168,
    NR_PCI_RANGE_N_252,
    NR_PCI_RANGE_N_504,
    NR_PCI_RANGE_N_1008
}nr_pci_range_e;

typedef struct{
    u8                range_valid:1;
    u8                rsv:7;
    u8                start_pci;
    u8                range;/*enumerate refer to nr_pci_range_e*/
    u8                padding;
}nr_pci_range_t;

typedef struct{
    u8                     cell_num;/*1..16*/
    u8                     padding[3];
    nr_pci_range_t         exclude_cell_list[MAX_NR_CELL_EXCLUDE_NUM];
}nr_intra_freq_exclude_cell_list_t;

typedef struct{
    u8                ssb_pos_qcl_relation_r16_valid:1;
    u8                rsv:7;
    u8                ssb_pos_qcl_relation_r16;/*enumerate refer to wnrrc_ssb_pos_qcl_com_r16_e*/
    u8                padding[2];
}nr_intra_freq_cell_info_v1610_t;

typedef struct{
    u8                                     cell_num;
    u8                                     padding[3];
    nr_intra_freq_cell_info_v1610_t        cell_v1610_list[MAX_NR_CELL_INTRA_NUM];
}nr_intra_freq_neigh_cell_list_v1610_t;

typedef struct{
    u8                     cell_num;/*1..16*/
    u8                     padding[3];
    nr_pci_range_t         allow_cell_list[MAX_NR_CELL_ALLOW_NUM];
}nr_intra_freq_allow_cell_list_r16_t;

typedef struct{
    u8                   plmn_id_idx_r16;
    u8                   cell_num;
    u8                   padding[2];
    nr_pci_range_t       cell_list_r16[MAX_NR_CAG_CELL_R16_NUM];
}nr_intra_freq_cag_cell_list_r16_t;

typedef struct{
    u8                   cell_num;
    u8                   padding[3];
    nr_pci_range_t       cell_list[MAX_NR_CELL_INTRA_NUM];    
}nr_intra_freq_neigh_hsdn_cell_list_r17_t;

typedef struct{
    u8                ssb_pos_qcl_relation_r17_valid:1;
    u8                rsv:7;
    u8                ssb_pos_qcl_relation_r17;/*enumerate refer to wnrrc_ssb_pos_qcl_com_r17_e*/
    u8                padding[2];
}nr_intra_freq_cell_info_v1710_t;

typedef struct{
    u8                                  cell_num;
    u8                                  padding[3];
    nr_intra_freq_cell_info_v1710_t     cell_v1710_list[MAX_NR_CELL_INTRA_NUM];
}nr_intra_freq_neigh_cell_list_v1710_t;

typedef struct{
    u16                                       intra_cell_list_valid:1;
    u16                                       intra_exclude_cell_list_valid:1;
    u16                                       late_non_critical_ext_valid:1;
    u16                                       intra_cell_list_v1610_valid:1;
    u16                                       intra_allow_cell_list_r16_valid:1;
    u16                                       intra_cag_cell_list_r16_valid:1;
    u16                                       hsdn_cell_list_r17_valid:1;
    u16                                       intra_cell_list_v1710_valid:1;
    u16                                       channel_access_mode2_r17_valid:1;
    u16                                       rsv:7;
    u8                                        cag_cell_list_r16_num;/*1...12*/
    u8                                        late_non_critical_ext;/*oxtet string*/
    nr_intra_freq_neigh_cell_list_t           intra_cell_list;
    nr_intra_freq_exclude_cell_list_t         intra_exclude_cell_list;
    nr_intra_freq_neigh_cell_list_v1610_t     intra_cell_list_v1610;
    nr_intra_freq_allow_cell_list_r16_t       intra_allow_cell_list_r16;
    nr_intra_freq_cag_cell_list_r16_t         intra_cag_cell_list_r16[MAX_NR_PLMN_NUM];
    nr_intra_freq_neigh_hsdn_cell_list_r17_t  hsdn_cell_list_r17;
    nr_intra_freq_neigh_cell_list_v1710_t     intra_cell_list_v1710;
    bool                                      channel_access_mode2_r17;/*TRUE: enable, FALSE:disable */
}wnrrc_sib3_info_t;
/**********************sib3 parameters end**********************/

/**********************sib4 parameters start**********************/
typedef struct{
    u8                              band_num;
    u8                              padding[3];
    wnrrc_multi_band_info_sib_t     band_list[MAX_NR_MULTI_BAND_NUM];
}nr_multi_freq_band_list_sib_t;

typedef struct{
    u8                thresh_x_high_q;/*0...31*/
    u8                thresh_x_low_q;/*0...31*/
    u8                padding[2];
}nr_thresh_x_q_t;

typedef struct{
    u8                q_rx_lev_min_offset_cell_valid:1;
    u8                q_rx_lev_min_offset_cell_sul_valid:1;
    u8                q_qual_min_offset_cell_valid:1;
    u8                rsv:5;
    u16               pci;
    u8                q_offset_cell;/*enumerate refer to wnrrc_q_offset_range_e*/
    u8                q_rx_lev_min_offset_cell;/*1...8*/
    u8                q_rx_lev_min_offset_cell_sul;/*1...8*/
    u8                q_qual_min_offset_cell;/*1...8*/
    u8                padding;
}nr_inter_freq_neigh_cell_info_t;

typedef struct{
    u8                                  cell_num;
    u8                                  padding[3];
    nr_inter_freq_neigh_cell_info_t     inter_freq_cell_list[MAX_NR_CELL_INTER_NUM];
}nr_inter_freq_neigh_cell_list_t;

typedef struct{
    u8                   cell_num;
    u8                   padding[3];
    nr_pci_range_t       cell_list[MAX_NR_CELL_EXCLUDE_NUM];
}nr_inter_freq_exclude_cell_list_t;

typedef struct{
    u32                                       multi_freq_band_list_valid:1;
    u32                                       multi_freq_band_list_sul_valid:1;
    u32                                       ssb_to_average_num_valid:1;
    u32                                       abs_thresh_ssb_consolidation_valid:1;
    u32                                       smtc_valid:1;
    u32                                       ssb_to_meas_valid:1;
    u32                                       ss_rssi_meas_valid:1;
    u32                                       q_rx_lev_min_sul_valid:1;
    u32                                       q_qual_min_valid:1;
    u32                                       p_max_valid:1;
    u32                                       t_reselection_sf_valid:1;
    u32                                       thresh_x_q_valid:1;
    u32                                       cell_resel_priority_valid:1;
    u32                                       cell_resel_sub_priority_valid:1;
    u32                                       q_offset_range_valid:1;
    u32                                       inter_freq_cell_list_valid:1;
    u32                                       inter_exclude_cell_list_valid:1;
    u32                                       rsv:15;
    u32                                       dl_arfcn_nr;/*0...3279165*/
    nr_multi_freq_band_list_sib_t             multi_freq_band_list;
    nr_multi_freq_band_list_sib_t             multi_freq_band_list_sul;
    wnrrc_thresh_nr_t                         abs_thresh_ssb_consolidation;
    wnrrc_ssb_mtc_t                           smtc;
    wnrrc_ssb_to_meas_t                       ssb_to_meas;
    bool                                      derive_ssb_idx_from_cell;
    wnrrc_ss_rssi_meas_t                      ss_rssi_meas;
    u8                                        ssb_to_average_num;/*2...16*/
    u8                                        ssb_scs;/*wnrrc_scs_e */
    s8                                        q_rx_lev_min;/*-70...-22*/
    s8                                        q_rx_lev_min_sul;/*-70...-22*/
    s8                                        q_qual_min;
    s8                                        p_max;/*-30...33*/
    u8                                        t_reselection_nr;/*0...7*/
    u8                                        thresh_x_high_p;/*0...31*/
    u8                                        thresh_x_low_p;/*0...31*/
    u8                                        cell_resel_priority;/*0..7*/
    u8                                        cell_resel_sub_priority;/*enumerate refer to wnrrc_cell_resel_sub_pri_e*/
    u8                                        q_offset_range;/*enumerate refer to wnrrc_q_offset_range_e*/
    wnrrc_speed_state_scale_factor_t          t_reselection_sf;
    nr_thresh_x_q_t                           thresh_x_q;
    nr_inter_freq_neigh_cell_list_t           inter_freq_cell_list;
    nr_inter_freq_exclude_cell_list_t         inter_exclude_cell_list;
}nr_inter_freq_carrier_freq_info_t;

typedef struct{
    u8                                       freq_num;
    u8                                       padding[3];
    nr_inter_freq_carrier_freq_info_t        carrier_freq_list[MAX_NR_FREQ_NUM];
}nr_inter_freq_carrier_freq_list_t;

typedef struct{
    u8                      ssb_pos_qcl_r16_valid:1;
    u8                      rsv:7;
    u8                      ssb_pos_qcl_r16;/*enumerate refer to wnrrc_ssb_pos_qcl_com_r16_e*/
    u8                      padding[2];
}nr_inter_freq_neigh_cell_info_v1610_t;

typedef struct{
    u8                   plmn_id_idx_r16;
    u8                   cell_num;
    u8                   padding[2];
    nr_pci_range_t       cell_list_r16[MAX_NR_CAG_CELL_R16_NUM];
}nr_inter_freq_cag_cell_list_per_plmn_r16_t;

typedef struct{
    u8                                              plmn_num;
    u8                                              padding[3];
    nr_inter_freq_cag_cell_list_per_plmn_r16_t      cell_list[MAX_NR_PLMN_NUM];
}nr_inter_freq_cag_cell_list_r16_t;

typedef struct{
    u8                  cell_num;
    u8                  padding[3];
    nr_pci_range_t      pci_range_list[MAX_NR_CELL_ALLOW_NUM];
}nr_inter_freq_allow_cell_info_r16_list_t;

typedef struct{
    u8                                        inter_neigh_cell_list_v1610_valid:1;
    u8                                        smtc2_lp_r16_valid:1;
    u8                                        allow_cell_list_valid:1;
    u8                                        ssb_pos_qcl_com_r16_valid:1;
    u8                                        cag_cell_list_valid:1;
    u8                                        rsv:3;
    u8                                        ssb_pos_qcl_com_r16;/*wnrrc_ssb_pos_qcl_com_r16_e*/
    u8                                        inter_neigh_cell_list_num;
    u8                                        padding;
    nr_inter_freq_neigh_cell_info_v1610_t     inter_neigh_cell_list_v1610[MAX_NR_CELL_INTER_NUM];
    wnrrc_smtc2_lp_r16_t                      smtc2_lp_r16;
    nr_inter_freq_allow_cell_info_r16_list_t  allow_cell_list;
    nr_inter_freq_cag_cell_list_r16_t         cag_cell_list;
}nr_inter_freq_carrier_freq_info_v1610_t;

typedef struct{
    u8                                         freq_num;
    u8                                         padding[3];
    nr_inter_freq_carrier_freq_info_v1610_t    carrier_freq_list_v1610[MAX_NR_FREQ_NUM];
}nr_inter_freq_carrier_freq_list_v1610_t;

typedef struct{
    u8                                     cell_num;
    u8                                     padding[3];
    nr_pci_range_t                         cell_list_r17[MAX_NR_CELL_INTER_NUM];
}nr_inter_neigh_hsdn_cell_list_r17_t;

typedef struct{
    u8                        ssb_pos_qcl_r17_valid:1;
    u8                        rsv:7;
    u8                        ssb_pos_qcl_r17;/*enumerate refer to wnrrc_ssb_pos_qcl_com_r17_e*/
    u8                        padding[2];
}nr_inter_freq_neigh_cell_info_v1710_t;

typedef struct{
    u8                                       cell_num;
    u8                                       padding[3];
    nr_inter_freq_neigh_cell_info_v1710_t    cell_list[MAX_NR_CELL_INTER_NUM];
}nr_inter_freq_neigh_cell_list_v1710_t;

typedef struct{
    u8                                             inter_hsdn_cell_list_r17_valid:1;
    u8                                             high_speed_meas_inter_freq_r17_valid:1;
    u8                                             red_cap_access_allow_r17_valid:1;
    u8                                             ssb_pos_qcl_com_r17_valid:1;
    u8                                             inter_freq_neigh_cell_list_v1710_valid:1;
    u8                                             rsv:3;
    u8                                             ssb_pos_qcl_com_r17;/*enumerate refer to wnrrc_ssb_pos_qcl_com_r17_e*/
    u8                                             padding[2];
    nr_inter_neigh_hsdn_cell_list_r17_t            inter_hsdn_cell_list_r17;
    bool                                           high_speed_meas_inter_freq_r17;
    bool                                           red_cap_access_allow_r17;
    nr_inter_freq_neigh_cell_list_v1710_t          inter_freq_neigh_cell_list_v1710;
}nr_inter_freq_carrier_freq_info_v1700_t;

typedef struct{
    u8                                         freq_num;
    u8                                         padding[3];
    nr_inter_freq_carrier_freq_info_v1700_t    carrier_freq_list_v1700[MAX_NR_FREQ_NUM];
}nr_inter_freq_carrier_freq_list_v1700_t;

typedef struct{
    u8                                 smtc4_list_r17_valid:1;
    u8                                 rsv:7;
    u8                                 padding[3];
    wnrrc_smtc4_list_r17_t             smtc4_list_r17;
}nr_inter_freq_carrier_freq_info_v1720_t;

typedef struct{
    u8                                         freq_num;
    u8                                         padding[3];
    nr_inter_freq_carrier_freq_info_v1720_t    carrier_freq_list_v1720[MAX_NR_FREQ_NUM];
}nr_inter_freq_carrier_freq_list_v1720_t;

typedef struct{
    u8                       channel_access_mode2_r17_valid:1;
    u8                       rsv:7;
    u8                       padding[3];
    bool                     channel_access_mode2_r17;
}nr_inter_freq_carrier_freq_info_v1730_t;

typedef struct{
    u8                                         freq_num;
    u8                                         padding[3];
    nr_inter_freq_carrier_freq_info_v1730_t    carrier_freq_list_v1730[MAX_NR_FREQ_NUM];
}nr_inter_freq_carrier_freq_list_v1730_t;

typedef struct{
    u8                                           late_non_critical_ext_valid:1;
    u8                                           inter_carrier_freq_list_v1610_valid:1;
    u8                                           inter_carrier_freq_list_v1700_valid:1;
    u8                                           inter_carrier_freq_list_v1720_valid:1;
    u8                                           inter_carrier_freq_list_v1730_valid:1;
    u8                                           rsv:3;
    u8                                           late_non_critical_ext;/*octet string*/
    u8                                           padding[2];
    nr_inter_freq_carrier_freq_list_t            inter_carrier_freq_list;
    nr_inter_freq_carrier_freq_list_v1610_t      inter_carrier_freq_list_v1610;
    nr_inter_freq_carrier_freq_list_v1700_t      inter_carrier_freq_list_v1700;
    nr_inter_freq_carrier_freq_list_v1720_t      inter_carrier_freq_list_v1720;
    nr_inter_freq_carrier_freq_list_v1730_t      inter_carrier_freq_list_v1730;
}wnrrc_sib4_info_t;
/**********************sib4 parameters end**********************/

/**********************pos parameters start**********************/
typedef enum{
    NR_POS_SIB_TYPE_1_1     = 0,
    NR_POS_SIB_TYPE_1_2,
    NR_POS_SIB_TYPE_1_3,
    NR_POS_SIB_TYPE_1_4,
    NR_POS_SIB_TYPE_1_5,
    NR_POS_SIB_TYPE_1_6,
    NR_POS_SIB_TYPE_1_7,
    NR_POS_SIB_TYPE_1_8,
    NR_POS_SIB_TYPE_2_1,
    NR_POS_SIB_TYPE_2_2,
    NR_POS_SIB_TYPE_2_3,
    NR_POS_SIB_TYPE_2_4,
    NR_POS_SIB_TYPE_2_5,
    NR_POS_SIB_TYPE_2_6,
    NR_POS_SIB_TYPE_2_7,
    NR_POS_SIB_TYPE_2_8,
    NR_POS_SIB_TYPE_2_9,
    NR_POS_SIB_TYPE_2_10,
    NR_POS_SIB_TYPE_2_11,
    NR_POS_SIB_TYPE_2_12,
    NR_POS_SIB_TYPE_2_13,
    NR_POS_SIB_TYPE_2_14,
    NR_POS_SIB_TYPE_2_15,
    NR_POS_SIB_TYPE_2_16,
    NR_POS_SIB_TYPE_2_17,
    NR_POS_SIB_TYPE_2_18,
    NR_POS_SIB_TYPE_2_19,
    NR_POS_SIB_TYPE_2_20,
    NR_POS_SIB_TYPE_2_21,
    NR_POS_SIB_TYPE_2_22,
    NR_POS_SIB_TYPE_2_24,
    NR_POS_SIB_TYPE_3_1,
    NR_POS_SIB_TYPE_4_1,
    NR_POS_SIB_TYPE_5_1,
    NR_POS_SIB_TYPE_6_1,
    NR_POS_SIB_TYPE_6_2,
    NR_POS_SIB_TYPE_6_3,
    NR_POS_SIB_TYPE_R17_1_9,
    NR_POS_SIB_TYPE_R17_1_10,
    NR_POS_SIB_TYPE_R17_2_24,
    NR_POS_SIB_TYPE_R17_2_25,
    NR_POS_SIB_TYPE_R17_6_4,
    NR_POS_SIB_TYPE_R17_6_5,
    NR_POS_SIB_TYPE_R17_6_6
}nr_pos_sib_type_r16_r17_e;

typedef struct{
    u8           late_non_critial_ext_valid:1;
    u8           rsv:7;
    u8           assistance_data_sib_element_r16;/*octet string*/
    u8           late_non_critial_ext;/*octet string*/
    u8           padding;
}nr_sib_pos_r16_t;

typedef struct{
    u8                      pos_sib_type_r16_and_r17;/*enumerate refer to nr_pos_sib_type_r16_r17_e*/
    u8                      padding[3];
    nr_sib_pos_r16_t        sib_pos_r16;
}nr_pos_sib_type_and_info_r16_t;

typedef struct{
    u8                                    late_non_critial_ext_valid:1;
    u8                                    rsv:7;
    u8                                    late_non_critial_ext;/*octet string*/
    u8                                    pos_sib_num;
    u8                                    padding;
    nr_pos_sib_type_and_info_r16_t        pos_sib_info[MAX_NR_SIB_NUM];
}wnrrc_pos_sib_r16_info_t;
/**********************pos parameters end**********************/

typedef struct {
    /* number of bits */
    unsigned int length;
    char*  bytes;
} BITS;

typedef struct {
	/* number of bytes */
    unsigned int length;
    char*  bytes;
} OCTETS;




typedef struct
{
   u32 nrofDownlinkSymbols;	/* OPTIONAL */
   u32 nrofUplinkSymbols;	/* OPTIONAL */
}Explicit_t;


typedef struct
{
   int choice;
#define	Symbols_allDownlink_chosen	0
#define	Symbols_allUplink_chosen	1
#define	Symbols__explicit_chosen	2

   union 
   {
      s8 allDownlink;
      s8 allUplink;
      Explicit_t _explicit;
   } value;
}Symbols_t;


typedef struct
{
   u32 slotIndex;
   Symbols_t symbols;
}TDD_UL_DL_SlotConfig_t;


typedef struct
{
    u16                    num_slot_spec_cfg;
    u16                    num_slot_spec_release;
	TDD_UL_DL_SlotConfig_t slotSpecificConfigurationsToAddModList[320]; /* OPTIONAL */
	u32 slotSpecificConfigurationsToReleaseList[320];  /* OPTIONAL */
}TDD_UL_DL_ConfigDedicated_t;


typedef enum{
    NRRC_PHY_CELL_SEARCH_TYPE_ALL_BAND   = 0,
    NRRC_PHY_CELL_SEARCH_TYPE_BAND_LIST,
    NRRC_PHY_CELL_SEARCH_TYPE_STORE_LIST_CELL,
    NRRC_PHY_CELL_SEARCH_TYPE_STORE_LIST_ARFCN,
    NRRC_PHY_CELL_SEARCH_TYPE_STORE_LIST_GSCN
}nrrc_phy_search_type_e;

typedef enum{
	WNRRC_CELL_SORT_PRIORITY_RSRP   = 0,
	WNRRC_CELL_SORT_PRIORITY_SNR
}wnrrc_cell_sort_priority_e;


typedef struct{
    u32       arfcn;
    u16       band_id;
    u16       pci;
    u8        rsrp;/*0xff invalid*/
    s8        snr;/*0xff invalid*/
    u8        padding[2];
}nrrc_phy_cell_info_t;


typedef enum{
    NRRC_PHY_RESULT_IND_SUCCESS = 0,
    NRRC_PHY_RESULT_IND_FAILURE
}nrrc_phy_result_ind_e;

typedef enum{
    NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_SCAN_FAIL     = 0,
    NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_PSS_DETECT_FAIL,
    NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_SSS_DETECT_FAIL,
    NRRC_PHY_CELL_SEARCH_FAIL_CAUSE_OTHER
}nrrc_phy_cell_search_fail_cause_e;

typedef enum{
    NRRC_PHY_CELL_SEARCH_STATUS_IS_NOT_END   = 0,
    NRRC_PHY_CELL_SEARCH_STATUS_IS_END
}nrrc_phy_cell_search_status_e;


typedef enum{
    NRRC_PHY_MIBSIB1_READ_TYPE_MIB     = 0,
    NRRC_PHY_MIBSIB1_READ_TYPE_SIB1,
    NRRC_PHY_MIBSIB1_READ_TYPE_MIBSIB1
}nrrc_phy_mibsib1_read_type_e;



typedef enum{
    NRRC_PHY_MIB_SCS_COMMON_SCS15_OR_SCS60   = 0,
    NRRC_PHY_MIB_SCS_COMMON_SCS30_OR_SCS120
}nrrc_phy_mib_scs_common_e;

typedef enum{
    NRRC_PHY_MIB_DMRS_TYPEA_POS_2   = 0,
    NRRC_PHY_MIB_DMRS_TYPEA_POS_3
}nrrc_phy_mib_dmrs_typea_pos_e;

typedef struct{
    u8             ctrl_resource_zero;/*0...15*/
    u8             search_space_zero;/*0...15*/
}nrrc_phy_pdcch_cfg_sib1_t;

typedef struct{
    u8                           sfn;/*system frame number*/
    u8                           scs_com;/*enumerate refer to nrrc_phy_mib_scs_common_e*/
    u8                           ssb_subcarrier_offset;/*0...15*/
    u8                           dmrs_typeA_pos;/*enumerate refer to nrrc_phy_mib_dmrs_typea_pos_e*/
    nrrc_phy_pdcch_cfg_sib1_t    sib1_cfg;
    bool                         cell_barred;
    bool                         intra_freq_reselect_allow;/*TRUE: allow intra frequency select
    	                                                     FALSE: not allow intra frequency select*/
}nr_mib_info_t;


typedef struct{
    u16     data_len;
    u8      padding[2];
    u8      data[MAX_NR_SI_SIZE];
}nr_si_buffer_t;



/*report_uplink_tx_direct_current_more_carrier_t start*/

typedef struct
{
    u8 deactivated_r17;
    u8 active_BWP_r17;/*maxNrofBWPs = 4 0xFF invalid*/
    u8 padding[2];
}carrier_state_r17_t;


typedef struct
{

    u8 dl_carrier_state_valid:1;
    u8 ul_carrier_state_valid:1;
    u8 :6;
    u8 padding[3];

    carrier_state_r17_t  dl_carrier_state;
    carrier_state_r17_t  ul_carrier_state;
}cc_state_r17_t;


typedef struct
{
    u8 cc_state_num;
    cc_state_r17_t cc_state_list[MAX_NR_OF_SERVING_CELLS];
}intra_band_CC_combination_r17_t;

typedef struct
{
    u8 serv_cell_index_num;
    u8 serv_cell_index_list[MAX_NR_OF_SERVING_CELLS];
    u8 combination_num;
    intra_band_CC_combination_r17_t intra_band_CC_combination_r17[MAX_NR_OF_REQ_COM_DC_LOCATION_R17];
}intra_band_CC_combinationreq_list_t;


typedef struct
{
    u8 combinationreq_list_num;
    intra_band_CC_combinationreq_list_t   combinationreq_list[MAX_SIMULTANEOUS_BANDS];
}report_uplink_tx_direct_current_more_carrier_t;

/*report_uplink_tx_direct_current_more_carrier_t end*/


/*physical_cell_group_config_ start*/


typedef enum 
{
    dB0 = 0,
    dB6
}xscale_e;

typedef enum 
{
    SETUP = 0,
    RELEASE
}cfg_type_e;

typedef enum 
{
    ENABLE = 0,
    DISABLE
}cfg_able_e;

typedef struct
{
    cfg_type_e cfg_type; /*0 setup, 1 release*/
    u8 padding;
    u16 rnti;
}cs_rnti_t;

typedef struct
{
    cfg_type_e cfg_type; /*0 setup, 1 release*/
    u8 pdcch_blind_detection;
}pdcch_blind_detection_t;

typedef struct
{
    cfg_type_e cfg_type; /*0 setup, 1 release*/
    u16 ps_rnti_r16;
    u8 ps_offset_r16;/*1~120*/
    u8 sizeDCI_2_6_r16;/*0-140*/
    u8 ps_positionDci_2_6_r16;/*0-139*/
    bool ps_wakeup_r16;
    bool ps_transmit_periodicL1_RSRP_r16;
    bool ps_transmit_other_periodicCSI_RSRP_r16;
}dcp_config_r16_t;


typedef struct
{
    cfg_type_e cfg_type; /*0 setup, 1 release*/
    u8 pdcch_blind_detection_CA1_r16;
    u8 pdcch_blind_detection_CA2_r16;
    u8 padding;
}pdcch_blind_detectionCA_comb_indicator_r16_t;


typedef struct {
    unsigned int length; /* number of bits */
    u16  bytes_u16;
} bits_u16_t;




typedef struct
{
   u8 per_cc_num;
   u8 per_harq_num;
   u8 per_cc[MAX_NR_OF_SERVING_CELLS];/*percc :0,1*/
   bits_u16_t per_harq[MAX_NR_OF_SERVING_CELLS];/*per_harq:BIT STRING (SIZE (16)*/
}applicable_r17_t;

typedef struct
{
    u8 pdsch_harq_ack_enh_type3_index_r17; /*0~7*/
    bool pdsch_harq_ack_enh_type3_ndi_r17;
    bool pdsch_harq_ack_enh_type3_cbg_r17;/*FALSE not config*/
    u8 padding;
    applicable_r17_t applicable_r17;
}pdsch_harq_ack_enh_type3_r17_t;

typedef struct
{
    cfg_type_e cfg_type; /*0 setup, 1 release*/
    bool codebook_list_flag;
    u8 pdsch_harq_ack_codebook_list_r17[3];/**/
    u8 type1_codebook_generation_mode_r17;/*ENUMERATED { mode1, mode2}*/
    u8 padding;
}multicast_config_r17_t;

typedef struct
{
    cfg_type_e cfg_type; /*0 setup, 1 release*/
    u8 pdcch_blind_detection_CA1_r17;/*0xFF invalid*/
    u8 pdcch_blind_detection_CA2_r17;/*0xFF invalid*/
    u8 pdcch_blind_detection_CA3_r17;
}pdcch_blind_detectionCA_combIndicator_r17_t;

typedef struct
{
    bool harq_ack_spatial_bundling_pucch;
    bool harq_ack_spatial_bundling_pusch;
    s8 p_nr_fr1;/*P-Max INTEGER (-30..33) 0xFF is invalid*/
    u8 pdsch_harq_ack_codebook;/*SEMISTASTIC/DYNAMIC*/
    u16 tpc_srs_rnti;/*0xFFFF is invalid*/
    u16 tpc_pucch_rnti;/*0xFFFF is invalid*/
    u16 tpc_pusch_rnti;/*0xFFFF is invalid*/
    u16 sp_csi_rnti;/*0xFFFF is invalid*/
    cs_rnti_t cs_rnti;
    u16 mcs_c_rnti;/*0xFFFF is invalid*/
    s8 p_ue_fr1;/*P-Max*/
    xscale_e xscale;
    pdcch_blind_detection_t pdcch_blind_detection;
    /*******************r16**********************/
    dcp_config_r16_t dcp_config;
    cfg_able_e harq_ack_spatial_bundling_pucch_secondary_pucch_group_r16;
    cfg_able_e harq_ack_spatial_bundling_pusch_secondary_pucch_group_r16;
    u8 pdsch_HARQ_ACK_codebook_secondary_PUCCH_group_r16;/*semiStatic = 0,dynamic = 1*/
    s8 p_nr_fr2_r16;/*P-Max*/
    s8 p_ue_fr2_r16;/*P-Max*/
    //nrdc-PCmode-FR1-r16
    //nrdc-PCmode-FR2-r16
    bool pdsch_harq_ack_codebook_enhanced_dynamic_r16;/*enhancedDynamic 1 0 FALSE*/
    bool nfi_total_dai_included_r16;/*TRUE,FALSE*/
    bool ul_total_dai_included_r16;/*TRUE,FALSE*/
    bool pdsch_harq_ack_one_shot_feedback_r16;
    bool pdsch_harq_ack_one_shot_feedback_ndi_r16;
    bool pdsch_harq_ack_one_shotFeedback_cbg_r16;
    bool downlink_assignment_index_dci_0_2_enable_r16;
    u8 downlink_assignment_index_dci_1_2_r16;/*0 = n1,1=n2,2=n4 0xFF is invalid*/
    bool pdsch_harq_ack_codebook_list_r16_valid;
    u8 pdsch_harq_ack_codebook_list_r16[3];/*SEMISTASTIC/DYNAMIC*/
    u8 ack_nack_feedback_mode_r16;/*joint, separate:0,1,0xFF*/
    pdcch_blind_detectionCA_comb_indicator_r16_t pdcch_blind_detectionCA_comb_indicator_r16;
    u8 pdcch_blind_detection2_r16;/*INTEGER (1..15) 0xFF id set release*/
    u8 pdcch_blind_detection3_r16;/*INTEGER (1..15) 0xFF id set release*/
    u8 bdFactorR_r16;/*0 is n1;0xff invalid release*/
    /*******************r17**********************/
    /*********start of enhanced Type3 feedback****************/
    u8 pdsch_harq_ack_enh_type3_to_add_mode_list_r17_num;
    pdsch_harq_ack_enh_type3_r17_t pdsch_harq_ack_enh_type3_to_add_mode_list_r17[MAX_NR_OF_ENH_TYPE3_HARQ_ACK_R17];
    u8 pdsch_harq_ack_enh_type3_to_release_list_r17_num;
    u8 pdsch_harq_ack_enh_type3_to_release_list_r17[MAX_NR_OF_ENH_TYPE3_HARQ_ACK_R17];
    u8 pdsch_harq_ack_enh_type3_secondary_to_add_mode_list_r17_num;
    pdsch_harq_ack_enh_type3_r17_t pdsch_harq_ack_enh_type3_secondary_to_add_mode_list_r17[MAX_NR_OF_ENH_TYPE3_HARQ_ACK_R17];
    u8 pdsch_harq_ack_enh_type3_secondary_to_release_list_r17_num;
    u8 pdsch_harq_ack_enh_type3_secondary_to_release_list_r17[MAX_NR_OF_ENH_TYPE3_HARQ_ACK_R17];
    cfg_able_e pdsch_harq_ack_enh_type3_dci_field_secondary_pucch_group_r17;
    cfg_able_e pdsch_harq_ack_enh_type3_dci_field_r17;
    /*********end of enhanced Type3 feedback****************/
    cfg_able_e pdsch_harq_ack_retx_r17;
    cfg_able_e pdsch_harq_ack_retx_secondary_pucch_group_r17;
    /**start of PUCCH Cell switching*/
    u8 pucch_sSCell_r17;/*SCellIndex*/
    u8 pucch_sSCell_Secondary_pucch_group_r17;/*SCellIndex 1-31  0xFF*/
    cfg_able_e pucch_sSCell_dyn_r17;
    cfg_able_e pucch_sSCell_dyn_secondary_pucch_group_r17;
    u8 pucch_sSCell_pattern_r17_num;
    u8 pucch_sSCell_pattern_r17[MAX_NR_OF_SLOTS];
    u8 pucch_sSCell_pattern_secondary_pucch_group_r17_num;
    u8 pucch_sSCell_pattern_secondary_pucch_group_r17[MAX_NR_OF_SLOTS];
    /**end of PUCCH Cell switching*/
    cfg_able_e uci_mux_with_diff_prio_r17;
    cfg_able_e uci_mux_with_diff_prio_secondary_pucch_group_r17;
    cfg_able_e simultaneous_pucch_pusch_r17;
    cfg_able_e simultaneous_pucch_pusch_Secondary_pucch_group_r17;
    cfg_able_e prioLow_dg_high_cg_r17;
    cfg_able_e prio_High_dg_low_cg_r17;
    cfg_able_e two_QCL_typeDfor_PDCCH_repetition_r17;
    multicast_config_r17_t multicast_config;/*MBS not surpport*/
    pdcch_blind_detectionCA_combIndicator_r17_t  pdcch_blind_detectionCA_combIndicator_r17;
    cfg_able_e simultaneous_sr_pusch_diff_pucch_groups_r17;
    cfg_able_e intra_band_nc_prach_simul_tx_r17;  
}physical_cell_group_config_t;
/*physical_cell_group_config_t end*/

/*spcell_config_t start*/
typedef enum{
     N0 = 0,
     N25600, 
     N39936
}nr_ta_offset_e;

typedef struct{
#define	ServingCellConfigCommon_Ssb_PositionsInBurst_shortBitmap_chosen	0
#define	ServingCellConfigCommon_Ssb_PositionsInBurst_mediumBitmap_chosen	1
#define	ServingCellConfigCommon_Ssb_PositionsInBurst_longBitmap_chosen	2
    u8 bitmap_type;
    u8 bitmap_len;/*bits num*/
    union
    {
        u8 short_bitmap;
        u8 medium_bitmap;
        u64 long_bitmap;
    }u;
}ssb_positions_inburst_t;

typedef enum 
{
    SSB_MS5 = 0,
    SSB_MS10,
    SSB_MS20,
    SSB_MS40,
    SSB_MS80,
    SSB_MS160     
}ssb_periodicity_serving_cell_e;


typedef struct 
{
    u8 periodicity_type;/*0:n2,1:n4,2:n5,3:n8,4:n10,5:n20,6:n40*/
    u8 padding[3];
    u64 pattern;
}periodicity_and_pattern_t;

typedef struct 
{
    u8 symbols_type;/*0:one slot, number of bits is 14
                      1:two slots, number of bits is 28*/
    u8 padding[3];
    u32 resource_block;
}symbols_in_resource_block_t;



typedef struct
{
    u8 periodicity_and_pattern_valid:1;
    u8 rsv:7;
    u8 resource_blocks[35]; 
    u16 num_bits_of_resource_blocks;
    symbols_in_resource_block_t symbols_in_resource_block;
    periodicity_and_pattern_t periodicity_and_pattern;
}bitmaps_t;

typedef struct
{
#define	PatternType_bitmaps_chosen	0
#define	PatternType_controlResourceSet_chosen	1
    u8 pattern_type;
    u8 control_resource_set_id;
    u8 padding[2];
    bitmaps_t bitmap_pattern_type;
}pattern_type_t;


typedef struct
{
    u8 SubcarrierSpacing_valid:1;
    u8 controlResourceSet_r16_valid:1;
    u8                         :6;

    
    u8 rate_match_pattern_id;
    pattern_type_t pattern_type;
    wnrrc_scs_e SubcarrierSpacing;
    u8 dummy;/*ENUMERATED { dynamic, semiStatic }*/
    u8 controlResourceSet_r16;
}rate_match_pattern_t;


typedef enum{
    MS0DOT125 = 0,
    MS0DOT25,
    MS0DOT5,
    MS0DOT75,
    MS1,
    MS1DOT25     
}discovery_burst_window_length_r17_e;

typedef struct
{
    u8 carrier_bandwidth;
    u8 padding[2];
    u16 offsetToCarrier;
    u16 tx_direct_current_location;
    wnrrc_scs_e  SubcarrierSpacing;
}scs_specific_carrier_t;


typedef struct
{
    u8 absolute_frequency_SSB_valid:1;
    u8 absolute_frequency_point_a_valid:1;
    u8                           :6;
    u32 absolute_frequency_SSB;
    u8 frequencyBandList_num;
    u16 frequencyBandList[MAX_NR_OF_MULTI_BANDS];
    u32 absolute_frequency_point_a;
    u8 scs_specific_carrier_list_num;
    scs_specific_carrier_t  scs_specific_carrier_list[MAX_SCSS];
}frequency_info_dl_t;


typedef struct
{
    u8 bwp_valid:1;
    u8 pdcch_cfg_common_valid:1;
    u8 pdsch_cfg_valid:1;
    u8                :5;
    u8 padding[3];
    wnrrc_bwp_t bwp;
    wnrrc_pdcch_cfg_common_t pdcch_cfg_common;
    wnrrc_pdsch_cfg_common_t pdsch_cfg_common;
}bwp_downlink_common_t;

typedef enum {
    SPS_MS10 = 0,
    SPS_MS20,
    SPS_MS32,
    SPS_MS64,
    SPS_MS80,
    SPS_MS128, 
    SPS_MS160,
    SPS_MS320,
    SPS_MS640
}sps_periodicity_e;

typedef struct
{
    sps_periodicity_e  periodicity;
    u8 nr_of_harq_processes;
    u8 n1_pucch_an;
    bool mcs_table_qam64_lowse;/*ENUMERATED {qam64LowSE}*/
    u8 sps_config_index_r16;
    u8 harq_proc_id_offset_r16;
    u8 periodicity_ext_r16;/*INTEGER (1..5120)*/
    u8 harq_codebook_id_r16;/*INTEGER (1..2)*/
    u8 pdsch_aggregation_factor_r16;/*ENUMERATED {n1, n2, n4, n8 }*/
    /*******R17*********/
    u8 sps_harq_Deferral_r17;
    u8 n1_pucch_an_pucch_sSell_r17;
    u16 periodicity_ext_r17;/*INTEGER (1..40960)*/
    u8 nr_of_harq_processes_v1710;/*INTEGER(9..32)*/
    u8 harq_proc_id_offset_v1700;/*INTEGER (16..31)*/
}sps_config_t;


typedef enum {
   nr_Reg_BundleSize_n2 = 0,
   nr_Reg_BundleSize_n3 = 1,
   nr_Reg_BundleSize_n6 = 2
}reg_bundle_size_e;

typedef enum  {
   nr_InterleaverSize_n2 = 0,
   nr_InterleaverSize_n3 = 1,
   nr_InterleaverSize_n6 = 2
}inter_leaver_size_e;


typedef struct
{
    reg_bundle_size_e reg_bundle_size;
    inter_leaver_size_e inter_leaver_size;
    u8 shift_index;
    u8 padding[3];
}inter_leaved_t;


typedef struct  
{
    u8 inter_leaved_exist_flag;
    u8 non_inter_leaved_exist_flag;
    u8 non_inter_leaved;
    u8 padding;
    inter_leaved_t inter_leaved;
}cce_reg_mapping_type_t;



typedef struct
{
    u8 control_resource_set_id;
    u8 frequency_domain_resources[6];
    u8 duration;
    cce_reg_mapping_type_t cce_reg_mapping_type;
    u8 precoder_granularity;/*ENUMERATED {sameAsREG-bundle, allContiguousRBs}*/
    u8 tci_states_pdcch_to_add_list[MAX_NR_OF_TCI_STATES_PDCCH];
    u8 tci_states_pdcch_to_rel_list[MAX_NR_OF_TCI_STATES_PDCCH];
    bool tci_present_in_dci;
    u16 pdcch_DMRS_scramblingID;   /* OPTIONAL */
    u16 rb_Offset_r16; /* OPTIONAL */
    u16 tci_PresentDCI_1_2_r16;    /* OPTIONAL */
    u16 coresetPoolIndex_r16;  /* OPTIONAL */
    u16 controlResourceSetId_v1610;    /* OPTIONAL */
    bool followUnifiedTCI_State_r17; /* OPTIONAL */
}control_resource_set_t;


typedef struct  {
   u32 servingCellId;
   u32 positionInDCI;
}INT_ConfigurationPerServingCell_t;


typedef struct  {
   u32 int_RNTI;
   s32 timeFrequencySet; /* enum TimeFrequencySet_set0 = 0,
   									TimeFrequencySet_set1 = 1*/
   u32 dci_PayloadSize;

   u32 num_of_int_ConfigurationPerServingCell;//1..32
   INT_ConfigurationPerServingCell_t int_ConfigurationPerServingCell[32];
}DownlinkPreemption_t;


typedef struct  {
//   int choice;
//#define	PDCCH_Config_DownlinkPreemption_release_chosen	0
//#define	PDCCH_Config_DownlinkPreemption_setup_chosen	1

//   union {
//      s8 release;
      DownlinkPreemption_t setup;
//   } value;
}PDCCH_Config_DownlinkPreemption_t;


#define	Tpc_PUSCH_release_chosen	0
#define	Tpc_PUSCH_setup_chosen	1

typedef struct  {
   u8  tpc_Index_valid:1;
   u8  tpc_IndexSUL_valid:1;
   u8  targetCell_valid:1;
   u8  rsv:5;
   u8  padding[3];
   u32 tpc_Index;	/* OPTIONAL */
   u32 tpc_IndexSUL;	/* OPTIONAL */
   u32 targetCell;	/* OPTIONAL */
}PUSCH_TPC_CommandConfig_t;

typedef struct  {
//   int choice;
//   union {
//      char release;
      PUSCH_TPC_CommandConfig_t setup;
//   } value;
}Tpc_PUSCH_t;

typedef struct  {
   u8 tpc_IndexPCell_valid:1;
   u8 tpc_IndexPUCCH_SCell_valid:1;
   u8 tpc_IndexPUCCH_sSCell_r17_valid:1;
   u8 tpc_IndexPUCCH_sScellSecondaryPUCCHgroup_r17_valid:1;
   u8 rsv:4;
   u8 padding[3];
   u32 tpc_IndexPCell;	/* OPTIONAL */
   u32 tpc_IndexPUCCH_SCell;	/* OPTIONAL */
   u32 tpc_IndexPUCCH_sSCell_r17;	/* OPTIONAL */
   u32 tpc_IndexPUCCH_sScellSecondaryPUCCHgroup_r17;	/* OPTIONAL */
}PUCCH_TPC_CommandConfig_t;


typedef struct  {
//   s32 choice;
//#define	Tpc_PUCCH_release_chosen	0
//#define	Tpc_PUCCH_setup_chosen	1

//   union {
//      s8 release;
      PUCCH_TPC_CommandConfig_t setup;
//   } value;
}Tpc_PUCCH_t;


typedef struct  {
    u8 startingBitOfFormat2_3_valid:1;
    u8 fieldTypeFormat2_3_valid:1;
    u8 startingBitOfFormat2_3SUL_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u32 startingBitOfFormat2_3;	/* OPTIONAL */
   u32 fieldTypeFormat2_3;	/* OPTIONAL */
   u32 startingBitOfFormat2_3SUL;	/* OPTIONAL */
}SRS_TPC_CommandConfig_t;



typedef struct  {
//   s32 choice;
//#define	Tpc_SRS_release_chosen	0
//#define	Tpc_SRS_setup_chosen	1

//   union {
//      s8 release;
      SRS_TPC_CommandConfig_t setup;
//   } value;
}Tpc_SRS_t;

typedef struct  {
    u8 shiftIndex_valid:1;
    u8 rsv:7;
    u8 padding[3];
   s32 reg_BundleSize; /*enum Reg_BundleSize_n2 = 0,
							   Reg_BundleSize_n3 = 1,
							   Reg_BundleSize_n6 = 2*/
   s32 interleaverSize; /*enum    InterleaverSize_n2 = 0,
												   InterleaverSize_n3 = 1,
												   InterleaverSize_n6 = 2*/
   u32 shiftIndex;	/* OPTIONAL */
}Interleaved_t;



typedef struct  {
   s32 choice;
#define	Cce_REG_MappingType_interleaved_chosen	0
#define	Cce_REG_MappingType_nonInterleaved_chosen	1

   union {
      Interleaved_t interleaved;
      s8 nonInterleaved;
   } value;
}Cce_REG_MappingType_t;




typedef struct  {
    u8 tci_PresentInDCI_valid:1;
    u8 pdcch_DMRS_ScramblingID_valid:1;
    u8 rb_Offset_r16_valid:1;
    u8 tci_PresentDCI_1_2_r16_valid:1;
    u8 coresetPoolIndex_r16_valid:1;
    u8 controlResourceSetId_v1610_valid:1;
    u8 followUnifiedTCI_State_r17_valid:1;
    u8 rsv:1;
    u8 padding[3];
   u32 controlResourceSetId;
   u8             num_bits_frequencyDomainResources;
   u8             padding1;
   u8/*SIZE(45)*/ frequencyDomainResources[6];
   u32 duration;
   Cce_REG_MappingType_t cce_REG_MappingType;
   s32 precoderGranularity;/*enum PrecoderGranularity_sameAsREG_bundle = 0,
   									PrecoderGranularity_allContiguousRBs = 1*/

   u32 num_of_tci_StatesPDCCH_ToAddList;//0..64
   u32 tci_StatesPDCCH_ToAddList[64];	/* OPTIONAL */

   u32 num_of_tci_StatesPDCCH_ToReleaseList;//0..64
   u32 tci_StatesPDCCH_ToReleaseList[64];	/* OPTIONAL */
   u32 tci_PresentInDCI;	/* OPTIONAL enum Tci_PresentInDCI_enabled = 0 */
   u32 pdcch_DMRS_ScramblingID;	/* OPTIONAL */
   u32 rb_Offset_r16;	/* OPTIONAL */
   u32 tci_PresentDCI_1_2_r16;	/* OPTIONAL */
   u32 coresetPoolIndex_r16;	/* OPTIONAL */
   u32 controlResourceSetId_v1610;	/* OPTIONAL */
   s32 followUnifiedTCI_State_r17;	/* OPTIONAL enum FollowUnifiedTCI_State_r17_enabled = 0*/
}ControlResourceSet_t;


typedef struct  {
    u8 aggregationLevel1_r16_valid:1;
    u8 aggregationLevel2_r16_valid:1;
    u8 aggregationLevel4_r16_valid:1;
    u8 aggregationLevel8_r16_valid:1;
    u8 aggregationLevel16_r16_valid:1;
    u8 rsv:3;
    u8 padding[3];
   s32 aggregationLevel1_r16;	/* OPTIONAL enum AggregationLevel1_r16_n1 = 0,
   												AggregationLevel1_r16_n2 = 1*/
   s32 aggregationLevel2_r16;	/* OPTIONAL enum AggregationLevel2_r16_n1 = 0,
   													AggregationLevel2_r16_n2 = 1*/
   s32 aggregationLevel4_r16;	/* OPTIONAL enum AggregationLevel4_r16_n1 = 0,
   													AggregationLevel4_r16_n2 = 1*/
   s32 aggregationLevel8_r16;	/* OPTIONAL enum  AggregationLevel8_r16_n1 = 0,
   													AggregationLevel8_r16_n2 = 1*/
   s32 aggregationLevel16_r16;	/* OPTIONAL enum AggregationLevel16_r16_n1 = 0,
   													AggregationLevel16_r16_n2 = 1*/
}NrofCandidates_CI_r16_t;

typedef struct  {
   s32 aggregationLevel1_r16;	/* OPTIONAL enum  NrofCandidates_IAB_r16_AggregationLevel1_r16_n1 = 0,
  												  NrofCandidates_IAB_r16_AggregationLevel1_r16_n2 = 1*/
   s32 aggregationLevel2_r16;	/* OPTIONAL enum NrofCandidates_IAB_r16_AggregationLevel2_r16_n1 = 0,
   												 NrofCandidates_IAB_r16_AggregationLevel2_r16_n2 = 1 */
   s32 aggregationLevel4_r16;	/* OPTIONAL enum  NrofCandidates_IAB_r16_AggregationLevel4_r16_n1 = 0,
   													NrofCandidates_IAB_r16_AggregationLevel4_r16_n2 = 1 */
   s32 aggregationLevel8_r16;	/* OPTIONAL enum NrofCandidates_IAB_r16_AggregationLevel8_r16_n1 = 0,
   													NrofCandidates_IAB_r16_AggregationLevel8_r16_n2 = 1 */
   s32  aggregationLevel16_r16;	/* OPTIONAL enum NrofCandidates_IAB_r16_AggregationLevel16_r16_n1 = 0,
   														NrofCandidates_IAB_r16_AggregationLevel16_r16_n2 = 1*/
}NrofCandidates_IAB_r16_t;


typedef struct  {
   s8 foo;	/* DUMMY */
}Dci_Format2_6_r16_t;



typedef struct  {
   NrofCandidates_IAB_r16_t nrofCandidates_IAB_r16;
}Dci_Format2_5_r16_t;



typedef struct  {
   NrofCandidates_CI_r16_t nrofCandidates_CI_r16;
}Dci_Format2_4_r16_t;



typedef struct  {
    u8      dci_Format2_4_r16_valid:1;
    u8      dci_Format2_5_r16_valid:1;
    u8      dci_Format2_6_r16_valid:1;
    u8      rsv:5;
    u8      padding[3];
   Dci_Format2_4_r16_t dci_Format2_4_r16;	/* OPTIONAL */
   Dci_Format2_5_r16_t dci_Format2_5_r16;	/* OPTIONAL */
   Dci_Format2_6_r16_t dci_Format2_6_r16;	/* OPTIONAL */
}Common_r16_t;



typedef struct  {
   Common_r16_t common_r16;
}SearchSpaceType_r16_t;


typedef struct  {
    u8 controlResourceSetId_r16_valid:1;
    u8 searchSpaceType_r16_valid:1;
    u8 searchSpaceGroupIdList_r16_valid:1;
    u8 freqMonitorLocations_r16_valid:1;
    u8 rsv:4;
    u8 padding[3];
   u32 controlResourceSetId_r16;	/* OPTIONAL */
   SearchSpaceType_r16_t searchSpaceType_r16;	/* OPTIONAL */

   u32 num_of_searchSpaceGroupIdList_r16;//0..2
   u32 searchSpaceGroupIdList_r16[2];	/* OPTIONAL */
   u8  num_bits_freqMonitorLocations_r16;
   u8/*SIZE(5)*/ freqMonitorLocations_r16;	/* OPTIONAL */
   u8   padding1[2];
}SearchSpaceExt_r16_t;


typedef struct  {
    u8 timeDurationForCI_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   s32 timeDurationForCI_r16;	/* OPTIONAL enum TimeDurationForCI_r16_n2 = 0,
											   TimeDurationForCI_r16_n4 = 1,
											   TimeDurationForCI_r16_n7 = 2,
											   TimeDurationForCI_r16_n14 = 3*/
   s32 timeGranularityForCI_r16; /*enum  TimeGranularityForCI_r16_n1 = 0,
									   TimeGranularityForCI_r16_n2 = 1,
									   TimeGranularityForCI_r16_n4 = 2,
									   TimeGranularityForCI_r16_n7 = 3,
									   TimeGranularityForCI_r16_n14 = 4,
									   TimeGranularityForCI_r16_n28 = 5*/
   u32 frequencyRegionForCI_r16;
   u32 deltaOffset_r16;
}TimeFrequencyRegion_r16_t;


typedef struct  {
    u8 positionInDCI_ForSUL_r16_valid:1;
    u8 uplinkCancellationPriority_v1610_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 servingCellId;
   u32 positionInDCI_r16;
   u32 positionInDCI_ForSUL_r16;	/* OPTIONAL */
   s32 ci_PayloadSize_r16; /*enum Ci_PayloadSize_r16_n1 = 0,
								   Ci_PayloadSize_r16_n2 = 1,
								   Ci_PayloadSize_r16_n4 = 2,
								   Ci_PayloadSize_r16_n5 = 3,
								   Ci_PayloadSize_r16_n7 = 4,
								   Ci_PayloadSize_r16_n8 = 5,
								   Ci_PayloadSize_r16_n10 = 6,
								   Ci_PayloadSize_r16_n14 = 7,
								   Ci_PayloadSize_r16_n16 = 8,
								   Ci_PayloadSize_r16_n20 = 9,
								   Ci_PayloadSize_r16_n28 = 10,
								   Ci_PayloadSize_r16_n32 = 11,
								   Ci_PayloadSize_r16_n35 = 12,
								   Ci_PayloadSize_r16_n42 = 13,
								   Ci_PayloadSize_r16_n56 = 14,
								   Ci_PayloadSize_r16_n112 = 15*/
   TimeFrequencyRegion_r16_t timeFrequencyRegion_r16;
   bool uplinkCancellationPriority_v1610;	/* OPTIONAL enum */
}CI_ConfigurationPerServingCell_r16_t;




typedef struct  {
   u32 ci_RNTI_r16;
   u32 dci_PayloadSizeForCI_r16;

   u32 num_of_ci_ConfigurationPerServingCell_r16;//1..32
   CI_ConfigurationPerServingCell_r16_t ci_ConfigurationPerServingCell_r16[32];
}UplinkCancellation_r16_t;



typedef struct  {
//   s32 choice;
//#define	PDCCH_Config_UplinkCancellation_r16_release_chosen	0
//#define	PDCCH_Config_UplinkCancellation_r16_setup_chosen	1

//   union {
//      s8 release;
      UplinkCancellation_r16_t setup;
//   } value;
}PDCCH_Config_UplinkCancellation_r16_t;

typedef struct{
    u8  num_of_serv_cell_idx;
    u16 serv_cell_idx[16];
    u8  padding;
}nr_cell_group_for_switch_r16_t;

typedef struct  {
    u8 cellGroupsForSwitchList_r16_valid:1;
    u8 searchSpaceSwitchDelay_r16_valid:1;
    u8 rsv:6;
    u8 padding[2];
    u8 num_of_cellGroupsForSwitchList_r16;/*1...4*/
    nr_cell_group_for_switch_r16_t cellGroupsForSwitchList_r16[4];	/* OPTIONAL */
    u32 searchSpaceSwitchDelay_r16;	/* OPTIONAL */
}SearchSpaceSwitchConfig_r16_t;



typedef struct  {
   int choice;
#define	MonitoringSlotPeriodicityAndOffset_v1710_sl32_chosen	0
#define	MonitoringSlotPeriodicityAndOffset_v1710_sl64_chosen	1
#define	MonitoringSlotPeriodicityAndOffset_v1710_sl128_chosen	2
#define	MonitoringSlotPeriodicityAndOffset_v1710_sl5120_chosen	3
#define	MonitoringSlotPeriodicityAndOffset_v1710_sl10240_chosen	4
#define	MonitoringSlotPeriodicityAndOffset_v1710_sl20480_chosen	5

   union {
      u32  sl32;
      u32  sl64;
      u32  sl128;
      u32  sl5120;
      u32  sl10240;
      u32 sl20480;
   } value;
}MonitoringSlotPeriodicityAndOffset_v1710_t;

typedef struct  {
   s32 choice;
#define	MonitoringSlotsWithinSlotGroup_r17_slotGroupLength4_r17_chosen	0
#define	MonitoringSlotsWithinSlotGroup_r17_slotGroupLength8_r17_chosen	1
    u8  num_bits_of_slot_group_length4_or_8;
    u8  padding[3];
   union {
      u8/*SIZE(4)*/ slotGroupLength4_r17;
      u8/*SIZE(8)*/ slotGroupLength8_r17;
   } value;
}MonitoringSlotsWithinSlotGroup_r17_t;


typedef struct  {
   s8 foo;	/* DUMMY */
}Dci_Format4_0_r17_t;

typedef struct  {
   s8 foo;	/* DUMMY */
}Dci_Format4_1_r17_t;

typedef struct  {
   char foo;	/* DUMMY */
}Dci_Format4_2_r17_t;

typedef struct  {
   char foo;	/* DUMMY */
}Dci_Format4_1_AndFormat4_2_r17_t;

typedef  struct{
    u8 aggregationLevel4_r17_valid:1;
    u8 aggregationLevel8_r17_valid:1;
    u8 aggregationLevel16_r17_valid:1;
    u8 rsv:5;
    u8 padding[3];
   s32 aggregationLevel4_r17;	/* OPTIONAL enum AggregationLevel4_r17_n0 = 0,
												   AggregationLevel4_r17_n1 = 1,
												   AggregationLevel4_r17_n2 = 2,
												   AggregationLevel4_r17_n3 = 3,
												   AggregationLevel4_r17_n4 = 4 */
   s32 aggregationLevel8_r17;	/* OPTIONAL enum  AggregationLevel8_r17_n0 = 0,
																		   AggregationLevel8_r17_n1 = 1,
																		   AggregationLevel8_r17_n2 = 2 */
   s32 aggregationLevel16_r17;	/* OPTIONAL enum AggregationLevel16_r17_n0 = 0,
   												AggregationLevel16_r17_n1 = 1*/
}NrofCandidates_PEI_r17_t;


typedef struct  {
   NrofCandidates_PEI_r17_t nrofCandidates_PEI_r17;
}Dci_Format2_7_r17_t;


typedef struct  {
    u8 dci_Format4_0_r17_valid:1;
    u8 dci_Format4_1_r17_valid:1;
    u8 dci_Format4_2_r17_valid:1;
    u8 dci_Format4_1_AndFormat4_2_r17_valid:1;
    u8 dci_Format2_7_r17_valid:1;
    u8 rsv:3;
    u8 padding[3];
   Dci_Format4_0_r17_t dci_Format4_0_r17;	/* OPTIONAL */
   Dci_Format4_1_r17_t dci_Format4_1_r17;	/* OPTIONAL */
   Dci_Format4_2_r17_t dci_Format4_2_r17;	/* OPTIONAL */
   Dci_Format4_1_AndFormat4_2_r17_t dci_Format4_1_AndFormat4_2_r17;	/* OPTIONAL */
   Dci_Format2_7_r17_t dci_Format2_7_r17;	/* OPTIONAL */
}Common_r17_t;



typedef struct  {
   Common_r17_t common_r17;
}SearchSpaceType_r17_t;



typedef struct  {
    u8 monitoringSlotPeriodicityAndOffset_v1710_valid:1;
    u8 monitoringSlotsWithinSlotGroup_r17_valid:1;
    u8 duration_r17_valid:1;
    u8 searchSpaceType_r17_valid:1;
    u8 searchSpaceGroupIdList_r17_valid:1;
    u8 searchSpaceLinkingId_r17_valid:1;
    u8 rsv:2;
    u8 padding[3];
   MonitoringSlotPeriodicityAndOffset_v1710_t monitoringSlotPeriodicityAndOffset_v1710;	/* OPTIONAL */
   MonitoringSlotsWithinSlotGroup_r17_t monitoringSlotsWithinSlotGroup_r17;	/* OPTIONAL */
   u32 duration_r17;	/* OPTIONAL */
   SearchSpaceType_r17_t searchSpaceType_r17;	/* OPTIONAL */

   u32 num_of_searchSpaceGroupIdList_r17;//0..3
   u32 searchSpaceGroupIdList_r17[3];	/* OPTIONAL */
   u32 searchSpaceLinkingId_r17;	/* OPTIONAL */
}SearchSpaceExt_v1700_t;

typedef struct  {
    u8 searchSpaceSwitchTimer_r17_valid:1;
    u8 searchSpaceSwitchDelay_r17_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 searchSpaceSwitchTimer_r17;	/* OPTIONAL */
   u32 searchSpaceSwitchDelay_r17;	/* OPTIONAL */
}SearchSpaceSwitchConfig_r17_t;



typedef struct  {
   u16     downlinkPreemption_valid:1;
   u16     tpc_PUSCH_valid:1;
   u16     tpc_PUCCH_valid:1;
   u16     tpc_SRS_valid:1;
   u16     uplinkCancellation_r16_valid:1;
   u16     monitoringCapabilityConfig_r16_valid:1;
   u16     searchSpaceSwitchConfig_r16_valid:1;
   u16     monitoringCapabilityConfig_v1710_valid:1;
   u16     searchSpaceSwitchConfig_r17_valid:1;
   u8      pdcch_SkippingDurationList_r17_valid:1;
   u16     rsv:6;
   u16     padding;
   u32 num_of_controlResourceSetToAddModList;//0..3
   ControlResourceSet_t controlResourceSetToAddModList[3];	/* OPTIONAL */

   u32 num_of_controlResourceSetToReleaseList;//0..3
   u32 controlResourceSetToReleaseList[3];	/* OPTIONAL */

   u32 num_of_searchSpacesToAddModList;//0..10
   wnrrc_search_space_t searchSpacesToAddModList[10];	/* OPTIONAL */

   u32 num_of_searchSpacesToReleaseList;//0..10
   u32 searchSpacesToReleaseList[10];	/* OPTIONAL */
   
   PDCCH_Config_DownlinkPreemption_t downlinkPreemption;	/* OPTIONAL */
   Tpc_PUSCH_t tpc_PUSCH;	/* OPTIONAL */
   Tpc_PUCCH_t tpc_PUCCH;	/* OPTIONAL */
   Tpc_SRS_t tpc_SRS;	/* OPTIONAL */

   u32 num_of_controlResourceSetToAddModListSizeExt_v1610;//0..2
   ControlResourceSet_t controlResourceSetToAddModListSizeExt_v1610[2];	/* OPTIONAL */

   u32 num_of_controlResourceSetToReleaseListSizeExt_r16;//0..5
   u32 controlResourceSetToReleaseListSizeExt_r16[5];	/* OPTIONAL */

   u32 num_of_searchSpacesToAddModListExt_r16;//0..10
   SearchSpaceExt_r16_t searchSpacesToAddModListExt_r16[10];	/* OPTIONAL */
   PDCCH_Config_UplinkCancellation_r16_t uplinkCancellation_r16;	/* OPTIONAL */
   s32 monitoringCapabilityConfig_r16;	/* OPTIONAL enum MonitoringCapabilityConfig_r16_r15monitoringcapability = 0,
   															MonitoringCapabilityConfig_r16_r16monitoringcapability = 1*/
   SearchSpaceSwitchConfig_r16_t searchSpaceSwitchConfig_r16;	/* OPTIONAL */

   u32 num_of_searchSpacesToAddModListExt_v1700;//0..10
   SearchSpaceExt_v1700_t searchSpacesToAddModListExt_v1700[10];	/* OPTIONAL */
   s32 monitoringCapabilityConfig_v1710;	/* OPTIONAL enum MonitoringCapabilityConfig_v1710_r17monitoringcapability = 0*/
   SearchSpaceSwitchConfig_r17_t searchSpaceSwitchConfig_r17;	/* OPTIONAL */

   u32 num_of_pdcch_SkippingDurationList_r17;//0..3
   u32 pdcch_SkippingDurationList_r17[3];	/* OPTIONAL */
}PDCCH_Config_t;



//typedef struct
//{
//    control_resource_set_t add_mod_List[3];/*ControlResourceSet*/
//    u8 control_resource_set_to_release_list[3];/*ControlResourceSetId*/
//    wnrrc_search_space_t search_space;
//}pdcch_config_t;


typedef struct {
   u8  frequencyDensity_valid:1;
   u8  timeDensity_valid:1;
   u8  epre_Ratio_valid:1;
   u8  resourceElementOffset_valid:1;
   u8  maxNrofPorts_r16_valid:1;
   u8  rsv:3;
   u8  padding;
   u8 resourceElementOffset;/*ENUMERATED { offset01, offset10, offset11 }*/
   u8 maxNrofPorts_r16;/*ENUMERATED {n1, n2}*/
   u16 frequencyDensity[2];
   u16 timeDensity[3];
   u16 epre_Ratio;
}PTRS_DownlinkConfig_t;

typedef struct  {
//   cfg_type_e cfg_type;
   PTRS_DownlinkConfig_t setup;
}PhaseTrackingRS_t;

typedef struct  {
    u8 dmrs_Type_valid:1;
    u8 dmrs_AdditionalPosition_valid:1;
    u8 maxLength_valid:1;
    u8 scramblingID0_valid:1;
    u8 scramblingID1_valid:1;
    u8 dmrs_Downlink_r16_valid:1;
    u8 phaseTrackingRS_valid:1;
    u8 rsv:1;
   u8 dmrs_Type;/* OPTIONAL ENUMERATED {type2}*/
   u8 dmrs_AdditionalPosition;/*OPTIONAL ENUMERATED {pos0, pos1, pos3}*/
   u8 maxLength;/*ENUMERATED {len2}*/
   u16 scramblingID0;/* OPTIONAL */
   u16 scramblingID1;/* OPTIONAL */
   PhaseTrackingRS_t phaseTrackingRS;	/* OPTIONAL */
   bool dmrs_Downlink_r16;	/* TRUEOPTIONAL ENUMERATED {enabled}*/
}DMRS_DownlinkConfig_t;


typedef struct  {
//   cfg_type_e cfg_type;
   DMRS_DownlinkConfig_t setup;
} Dmrs_DownlinkForPDSCH_MappingTypeA_t;

typedef struct {
//    cfg_type_e cfg_type;
    DMRS_DownlinkConfig_t setup;
}Dmrs_DownlinkForPDSCH_MappingTypeB_t;

typedef struct  
{
    bool csi_rs_is_exist_flag;
    u8 csi_rs;
    u8 ssb;
    u8 padding[2];
}ReferenceSignal_t;

typedef struct {
    u8 cell_valid:1;
    u8 bwp_Id_valid:1;
    u8 rsv:6;
    u8 qcl_Type;/*ENUMERATED {typeA, typeB, typeC, typeD},*/
    u8 padding[2];
   u16 cell;	/* OPTIONAL */
   u16 bwp_Id;	/* OPTIONAL */
   ReferenceSignal_t referenceSignal;
}QCL_Info_t;


typedef struct  {
   u8 qcl_Type2_valid:1;
   u8 additionalPCI_r17_valid:1;
   u8 pathlossReferenceRS_Id_r17_valid:1;
   u8 ul_powerControl_r17_valid:1;
   u8 rsv:4;
   u16 additionalPCI_r17;	/* OPTIONAL */
   u8 tci_StateId;
   QCL_Info_t qcl_Type1;
   QCL_Info_t qcl_Type2;	/* OPTIONAL */
   u16 pathlossReferenceRS_Id_r17;	/* OPTIONAL */
   u16 ul_powerControl_r17;	/* OPTIONAL */
}TCI_State_t;

typedef enum{
   nr_pdsch_time_domain_res_alloc_MappingType_typeA = 0,
   nr_pdsch_time_domain_res_alloc_MappingType_typeB = 1
}nr_pdsch_time_domain_res_alloc_MappingType_e;

typedef struct  {
   u8  k0;	/* OPTIONAL */
   u8 mappingType;  /*enum MappingType_typeA = 0,
                            MappingType_typeB = 1, refer to nr_pdsch_time_domain_res_alloc_MappingType_e*/
   u8 startSymbolAndLength;
   u8 padding;
} PDSCH_TimeDomainResourceAllocation_t;


typedef struct  {
//    cfg_type_e cfg_type;
    u8 num_of_PDSCH_TimeDomainResourceAllocationlist;
    u8 padding[3];
    PDSCH_TimeDomainResourceAllocation_t PDSCH_TimeDomainResourceAllocationlist[MAX_NR_OF_DL_ALLOCATIONS];
}Pdsch_TimeDomainAllocationList_t;

typedef struct  {
    bool cellLevel_is_exist_flag;
    u8 padding[2];
    u8 cellLevel;
    u8 bwpLevel;
}RateMatchPatternGroup_t;

typedef enum{
      nr_BundleSizeSet1_n4 = 0,
      nr_BundleSizeSet1_wideband = 1,
      nr_BundleSizeSet1_n2_wideband = 2,
      nr_BundleSizeSet1_n4_wideband = 3
}nr_dynamic_BundleSizeSet1_e;

typedef enum{
   nr_BundleSizeSet2_n4 = 0,
   nr_BundleSizeSet2_wideband = 1
}nr_dynamic_BundleSizeSet2_e;

typedef struct  {
   u8 bundleSizeSet1_valid:1;
   u8 bundleSizeSet2_valid:1;
   u8 rsv:6;
   u8 padding;
   u8 bundleSizeSet1;	/* enumerate refer to nr_dynamic_BundleSizeSet1_e*/
   u8 bundleSizeSet2;	/* enumerate refer to nr_dynamic_BundleSizeSet2_e*/
} DynamicBundling_t;

typedef enum{
   nr_BundleSize_n4 = 0,
   nr_BundleSize_wideband = 1
}nr_static_BundleSize_e;

typedef struct{
   u8 bundlesize_valid:1;
   u8 rsv:7;
   u8 padding[2];
   u8 bundleSize;	/*nr_static_BundleSize_e*/
}nr_StaticBundling_t;

typedef struct {
   bool staticBundling_is_exist_flag;
   nr_StaticBundling_t staticBundling;
   DynamicBundling_t dynamicBundling;
}Prb_BundlingType_t;

typedef struct  {
   int choice;/*0~3*/
   union {
      u8 dot5;/*ENUMERATED {evenPRBs, oddPRBs}*/
      u8 one;
      u8 three;
      u8 spare;
   } value;
}Density_t;

typedef struct  {
   u32 startingRB;
   u32 nrofRBs;
}CSI_FrequencyOccupation_t;




typedef struct  {
   u8 FrequencyDomain;/*0:row1,1:row2,3:row4,4:other*/
   u8 num_bits;
   u16 value;
} FrequencyDomainAllocation_t;

typedef struct  {
    u8 firstOFDMSymbolInTimeDomain2_valid:1;
    u8 rsv:7;
    u8 padding[3];
   FrequencyDomainAllocation_t frequencyDomainAllocation;
   s32 nrofPorts;/*enum NrofPorts_p1 = 0,
					   NrofPorts_p2 = 1,
					   NrofPorts_p4 = 2,
					   NrofPorts_p8 = 3,
					   NrofPorts_p12 = 4,
					   NrofPorts_p16 = 5,
					   NrofPorts_p24 = 6,
					   NrofPorts_p32 = 7*/
   u32 firstOFDMSymbolInTimeDomain;
   u32 firstOFDMSymbolInTimeDomain2;	/* OPTIONAL */
   s32 cdm_Type;/*enum Cdm_Type_noCDM = 0,
							   Cdm_Type_fd_CDM2 = 1,
							   Cdm_Type_cdm4_FD2_TD2 = 2,
							   Cdm_Type_cdm8_FD2_TD4 = 3*/
   Density_t density;
   CSI_FrequencyOccupation_t freqBand;
}CSI_RS_ResourceMapping_t;


typedef struct  {
   s32 choice;
#define	CSI_ResourcePeriodicityAndOffset_slots4_chosen	0
#define	CSI_ResourcePeriodicityAndOffset_slots5_chosen	1
#define	CSI_ResourcePeriodicityAndOffset_slots8_chosen	2
#define	CSI_ResourcePeriodicityAndOffset_slots10_chosen	3
#define	CSI_ResourcePeriodicityAndOffset_slots16_chosen	4
#define	CSI_ResourcePeriodicityAndOffset_slots20_chosen	5
#define	CSI_ResourcePeriodicityAndOffset_slots32_chosen	6
#define	CSI_ResourcePeriodicityAndOffset_slots40_chosen	7
#define	CSI_ResourcePeriodicityAndOffset_slots64_chosen	8
#define	CSI_ResourcePeriodicityAndOffset_slots80_chosen	9
#define	CSI_ResourcePeriodicityAndOffset_slots160_chosen	10
#define	CSI_ResourcePeriodicityAndOffset_slots320_chosen	11
#define	CSI_ResourcePeriodicityAndOffset_slots640_chosen	12

   union {
      u32 slots4;
      u32 slots5;
      u32 slots8;
      u32 slots10;
      u32 slots16;
      u32 slots20;
      u32 slots32;
      u32 slots40;
      u32 slots64;
      u32 slots80;
      u32 slots160;
      u32 slots320;
      u32 slots640;
   } value;
}CSI_ResourcePeriodicityAndOffset_t;


typedef struct  {
    u8 periodicityAndOffset_valid:1;
    u8 rsv:7;
    u8 padding[2];
   u8 zp_CSI_RS_ResourceId;
   CSI_RS_ResourceMapping_t resourceMapping;
   CSI_ResourcePeriodicityAndOffset_t periodicityAndOffset;	/* OPTIONAL */
}ZP_CSI_RS_Resource_t;

typedef struct  {
    u8 zp_CSI_RS_ResourceSetId;
    u8 num_of_zp_CSI_RS_ResourceIdList;
    u8 padding[2];
    u8 zp_CSI_RS_ResourceIdList [16];
 } ZP_CSI_RS_ResourceSet_t;
 

 
typedef struct  {
//#define	P_ZP_CSI_RS_ResourceSet_release_chosen	0
//#define	P_ZP_CSI_RS_ResourceSet_setup_chosen	1
//    int choice;
//    union {
//       char release;
       ZP_CSI_RS_ResourceSet_t setup;
//    } value;
 } P_ZP_CSI_RS_ResourceSet_t;


typedef struct {
//#define	MaxMIMO_Layers_r16_release_chosen	0
//#define	MaxMIMO_Layers_r16_setup_chosen	1
//   int choice;
//   union {
//      u8 release;
    u8 setup;
    u8 padding[3];
//   } value;
} MaxMIMO_Layers_r16_t;


typedef struct  {
//#define	MinimumSchedulingOffsetK0_r16_release_chosen	0
//#define	MinimumSchedulingOffsetK0_r16_setup_chosen	1
//   int choice;
//   union {
//      char release;
    u8 num_of_setup;
    u8 setup[2];
    u8 padding;
//   } value;
} MinimumSchedulingOffsetK0_r16_t;


typedef struct  {
//#define	Dmrs_DownlinkForPDSCH_MappingTypeA_DCI_1_2_r16_release_chosen	0
//#define	Dmrs_DownlinkForPDSCH_MappingTypeA_DCI_1_2_r16_setup_chosen	1

//   int choice;
//   union {
//      u8 release;
      DMRS_DownlinkConfig_t setup;
//   } value;
} Dmrs_DownlinkForPDSCH_MappingTypeA_DCI_1_2_r16_t;




typedef struct  {
//#define	Dmrs_DownlinkForPDSCH_MappingTypeB_DCI_1_2_r16_release_chosen	0
//#define	Dmrs_DownlinkForPDSCH_MappingTypeB_DCI_1_2_r16_setup_chosen	1
//   int choice;
//   union {
//      u8 release;
      DMRS_DownlinkConfig_t setup;
//   } value;

} Dmrs_DownlinkForPDSCH_MappingTypeB_DCI_1_2_r16_t;

typedef enum{
   nr_MappingType_r16_typeA = 0,
   nr_MappingType_r16_typeB = 1
}nr_MappingType_r16_e;

typedef enum{
   nr_RepetitionNumber_r16_n2 = 0,
   nr_RepetitionNumber_r16_n3 = 1,
   nr_RepetitionNumber_r16_n4 = 2,
   nr_RepetitionNumber_r16_n5 = 3,
   nr_RepetitionNumber_r16_n6 = 4,
   nr_RepetitionNumber_r16_n7 = 5,
   nr_RepetitionNumber_r16_n8 = 6,
   nr_RepetitionNumber_r16_n16 = 7
}nr_RepetitionNumber_r16_e;

typedef enum{
   nr_RepetitionNumber_v1730_n2 = 0,
   nr_RepetitionNumber_v1730_n3 = 1,
   nr_RepetitionNumber_v1730_n4 = 2,
   nr_RepetitionNumber_v1730_n5 = 3,
   nr_RepetitionNumber_v1730_n6 = 4,
   nr_RepetitionNumber_v1730_n7 = 5,
   nr_RepetitionNumber_v1730_n8 = 6,
   nr_RepetitionNumber_v1730_n16 = 7
}nr_RepetitionNumber_v1730_e;

typedef struct  {
    u8 k0_r16_valid:1;
    u8 repetitionNumber_r16_valid:1;
    u8 k0_v1710_valid:1;
    u8 repetitionNumber_v1730_valid:1;
    u8 rsv:4;
   u16 k0_r16;	/* OPTIONAL */
   u8 mappingType_r16;/*enumerate refer to nr_MappingType_r16_e*/
   u8 startSymbolAndLength_r16;
   u8 repetitionNumber_r16;	/*nr_RepetitionNumber_r16_e */
   u16 k0_v1710;	/* OPTIONAL */
   u8 repetitionNumber_v1730;	/* nr_RepetitionNumber_v1730_e*/
   u8 padding[3];
} PDSCH_TimeDomainResourceAllocation_r16_t;



typedef struct  {
//#define	Pdsch_TimeDomainAllocationListDCI_1_2_r16_release_chosen	0
//#define	Pdsch_TimeDomainAllocationListDCI_1_2_r16_setup_chosen	1
//   int choice;
//   union {
//      u8 release;
      u8 num_of_PDSCH_TimeDomainResourceAllocation_r16;
      PDSCH_TimeDomainResourceAllocation_r16_t setup[16];
//   } value;
} Pdsch_TimeDomainAllocationListDCI_1_2_r16_t;

typedef struct  {
   u8  bundleSize_r16_valid:1;
   u8  rsv:7;
   u8  padding[3];
   s32 bundleSize_r16;	/* OPTIONAL enum BundleSize_r16_n4 = 0,
  														 BundleSize_r16_wideband = 1*/
}StaticBundling_r16_t;


typedef struct  {
    u8 bundleSizeSet1_r16_valid:1;
    u8 bundleSizeSet2_r16_valid:1;
    u8 rsv:6;
    u8 padding[3];
   s32 bundleSizeSet1_r16;	/* OPTIONAL enum  BundleSizeSet1_r16_n4 = 0,
											   BundleSizeSet1_r16_wideband = 1,
											   BundleSizeSet1_r16_n2_wideband = 2,
											   BundleSizeSet1_r16_n4_wideband = 3 */
   s32 bundleSizeSet2_r16;	/* OPTIONAL enum  BundleSizeSet2_r16_n4 = 0,
   											BundleSizeSet2_r16_wideband = 1 */
}DynamicBundling_r16_t;



typedef struct  {
#define	Prb_BundlingTypeDCI_1_2_r16_staticBundling_r16_chosen	0
#define	Prb_BundlingTypeDCI_1_2_r16_dynamicBundling_r16_chosen	1
   int choice;
   union {
      StaticBundling_r16_t staticBundling_r16;
      DynamicBundling_r16_t dynamicBundling_r16;
   } value;
} Prb_BundlingTypeDCI_1_2_r16_t;

typedef struct  {
//#define	Pdsch_TimeDomainAllocationList_r16_release_chosen	0
//#define	Pdsch_TimeDomainAllocationList_r16_setup_chosen	1
//   int choice;
//   union {
//      char release;
    u8 num_of_setup;
    u8 padding[3];
    PDSCH_TimeDomainResourceAllocation_r16_t setup[16];
//   } value;
} Pdsch_TimeDomainAllocationList_r16_t;


typedef struct  {
   u8 startingSymbolOffsetK_r16_valid:1;
   u8 rsv:7;
   u8 repetitionScheme_r16;
   u16 startingSymbolOffsetK_r16;	/* OPTIONAL */
}FDM_TDM_r16_t;



typedef struct  {
#define	RepetitionSchemeConfig_r16_Fdm_TDM_r16_release_chosen	0
#define	RepetitionSchemeConfig_r16_Fdm_TDM_r16_setup_chosen	1

   int choice;
   union {
      char release;
      FDM_TDM_r16_t setup;
   } value;
} RepetitionSchemeConfig_r16_Fdm_TDM_r16_t;

typedef struct  {
   s32 tciMapping_r16; /*enum TciMapping_r16_cyclicMapping = 0,
   							TciMapping_r16_sequentialMapping = 1*/
   u32 sequenceOffsetForRV_r16;
}SlotBased_r16_t;



typedef struct {
#define	RepetitionSchemeConfig_r16_SlotBased_r16_release_chosen	0
#define	RepetitionSchemeConfig_r16_SlotBased_r16_setup_chosen	1
   int choice;
   union {
      char release;
      SlotBased_r16_t setup;
   } value;
} RepetitionSchemeConfig_r16_SlotBased_r16_t;



typedef struct  {
#define	RepetitionSchemeConfig_r16_fdm_TDM_r16_chosen	0
#define	RepetitionSchemeConfig_r16_slotBased_r16_chosen	1
   int choice;
   union {
      RepetitionSchemeConfig_r16_Fdm_TDM_r16_t fdm_TDM_r16;
      RepetitionSchemeConfig_r16_SlotBased_r16_t slotBased_r16;
   } value;
} RepetitionSchemeConfig_r16_t;



typedef struct  {
   u8 tciMapping_r16;
   u8 sequenceOffsetForRV_r16;
}SlotBased_v1630_t;



typedef struct  {
//#define	PDSCH_Config_RepetitionSchemeConfig_r16_release_chosen	0
//#define	PDSCH_Config_RepetitionSchemeConfig_r16_setup_chosen	1

//   u8 choice;
//   union {
//      u8 release;
      RepetitionSchemeConfig_r16_t setup;
//   } value;
} PDSCH_Config_RepetitionSchemeConfig_r16_t;





typedef struct  {
#define	RepetitionSchemeConfig_v1630_SlotBased_v1630_release_chosen	0
#define	RepetitionSchemeConfig_v1630_SlotBased_v1630_setup_chosen	1
   u8 choice;
   union {
      char release;
      SlotBased_v1630_t setup;
   } value;
} RepetitionSchemeConfig_v1630_SlotBased_v1630_t,RepetitionSchemeConfig_v1630_t;

//typedef struct{
//    RepetitionSchemeConfig_v1630_SlotBased_v1630_t repetition_scheme_v1630;
//}RepetitionSchemeConfig_v1630_t;


typedef struct  {
//#define	PDSCH_Config_RepetitionSchemeConfig_v1630_release_chosen	0
//#define	PDSCH_Config_RepetitionSchemeConfig_v1630_setup_chosen	1
//   u8 choice;
//   union {
//      u8 release;
      RepetitionSchemeConfig_v1630_t setup;
//   } value;
}PDSCH_Config_RepetitionSchemeConfig_v1630_t;



typedef struct  {
   u8 num_of_dl_OrJointTCI_StateToAddModList_r17;
   u8 num_of_dl_OrJointTCI_StateToReleaseList_r17;
   u8 padding[2];
   TCI_State_t dl_OrJointTCI_StateToAddModList_r17[128];
   u8 dl_OrJointTCI_StateToReleaseList_r17[128];
}Explicitlist_t;


typedef struct  {
   u8 servingcell_r17;
   u8 bwp_r17;
   u8 padding[2];
}ServingCellAndBWP_Id_r17_t;


typedef struct  {
#define	Dl_OrJointTCI_StateList_r17_explicitlist_chosen	0
#define	Dl_OrJointTCI_StateList_r17_unifiedTCI_StateRef_r17_chosen	1

   u8 choice;
   union {
      Explicitlist_t explicitlist;
      ServingCellAndBWP_Id_r17_t unifiedTCI_StateRef_r17;
   } value;
} Dl_OrJointTCI_StateList_r17_t;


typedef struct  {
    u8 num_of_pdsch_TDRA_List_r17;
    u8 padding[3];
   PDSCH_TimeDomainResourceAllocation_r16_t pdsch_TDRA_List_r17[8];
} MultiPDSCH_TDRA_r17_t;



typedef struct {
//#define	PDSCH_Config_Dummy_release_chosen	0
//#define	PDSCH_Config_Dummy_setup_chosen	    1
//   u8 choice;
//   union {
//      u8 release;
    u8 num_of_setup;
    u8 padding[3];
    MultiPDSCH_TDRA_r17_t setup[16];
//   } value;
} PDSCH_Config_Dummy_t;


typedef struct {
//#define	MinimumSchedulingOffsetK0_r17_release_chosen	0
//#define	MinimumSchedulingOffsetK0_r17_setup_chosen	1
//   int choice;
//   union {
//      u8 release;
    u8 num_of_setup;
    u8 setup[2];
//   } value;
}MinimumSchedulingOffsetK0_r17_t;


typedef struct  {
//#define	Pdsch_TimeDomainAllocationListForMultiPDSCH_r17_release_chosen	0
//#define	Pdsch_TimeDomainAllocationListForMultiPDSCH_r17_setup_chosen	1
//   int choice;
//   union {
//      u8 release;
    u8 num_of_setup;
    u8 padding[3];
    MultiPDSCH_TDRA_r17_t setup[64];
//   } value;
} Pdsch_TimeDomainAllocationListForMultiPDSCH_r17_t;


typedef enum{
   nr_Pdsch_AggregationFactor_n2 = 0,
   nr_Pdsch_AggregationFactor_n4 = 1,
   nr_Pdsch_AggregationFactor_n8 = 2
}nr_Pdsch_AggregationFactor_e;

typedef enum{
   nr_Mcs_Table_qam256 = 0,
   nr_Mcs_Table_qam64LowSE = 1
}nr_mcs_table_e;

typedef enum{
   nr_MaxNrofCodeWordsScheduledByDCI_n1 = 0,
   nr_MaxNrofCodeWordsScheduledByDCI_n2 = 1
}nr_MaxNrofCodeWordsScheduledByDCI_e;

typedef enum{
   nr_ResourceAllocationType1GranularityDCI_1_2_r16_n2 = 0,
   nr_ResourceAllocationType1GranularityDCI_1_2_r16_n4 = 1,
   nr_ResourceAllocationType1GranularityDCI_1_2_r16_n8 = 2,
   nr_ResourceAllocationType1GranularityDCI_1_2_r16_n16 = 3
}nr_ResourceAllocationType1GranularityDCI_1_2_r16_e;

typedef enum{
   nr_Vrb_ToPRB_InterleaverDCI_1_2_r16_n2 = 0,
   nr_Vrb_ToPRB_InterleaverDCI_1_2_r16_n4 = 1
}nr_Vrb_ToPRB_InterleaverDCI_1_2_r16_e;

typedef enum{
   nr_ResourceAllocationDCI_1_2_r16_resourceAllocationType0 = 0,
   nr_ResourceAllocationDCI_1_2_r16_resourceAllocationType1 = 1,
   nr_ResourceAllocationDCI_1_2_r16_dynamicSwitch = 2
}nr_ResourceAllocationDCI_1_2_r16_e;

typedef enum{
   nr_BeamAppTime_r17_n1 = 0,
   nr_BeamAppTime_r17_n2 = 1,
   nr_BeamAppTime_r17_n4 = 2,
   nr_BeamAppTime_r17_n7 = 3,
   nr_BeamAppTime_r17_n14 = 4,
   nr_BeamAppTime_r17_n28 = 5,
   nr_BeamAppTime_r17_n42 = 6,
   nr_BeamAppTime_r17_n56 = 7,
   nr_BeamAppTime_r17_n70 = 8,
   nr_BeamAppTime_r17_n84 = 9,
   nr_BeamAppTime_r17_n98 = 10,
   nr_BeamAppTime_r17_n112 = 11,
   nr_BeamAppTime_r17_n224 = 12,
   nr_BeamAppTime_r17_n336 = 13,
   nr_BeamAppTime_r17_spare2 = 14,
   nr_BeamAppTime_r17_spare1 = 15
}nr_BeamAppTime_r17_e;

typedef enum{
   nr_PDSCH_Config_Mcs_Table_r17_qam1024 = 0
}nr_PDSCH_Config_Mcs_Table_r17_e;

typedef enum{
   nr_Mcs_TableDCI_1_2_r17_qam1024 = 0
}nr_Mcs_TableDCI_1_2_r17_e;



typedef struct {
    u64  dataScramblingIdentityPDSCH_valid:1;
    u64  dmrs_DownlinkForPDSCH_MappingTypeA_valid:1;
    u64  dmrs_DownlinkForPDSCH_MappingTypeB_valid:1;
    u64  vrb_ToPRB_Interleaver_valid:1;
    u64  pdsch_TimeDomainAllocationList_valid:1;
    u64  pdsch_AggregationFactor_valid:1;
    u64  rateMatchPatternGroup1_valid:1;
    u64  rateMatchPatternGroup2_valid:1;
    u64  mcs_Table_valid:1;
    u64  maxNrofCodeWordsScheduledByDCI_valid:1;
    u64  p_ZP_CSI_RS_ResourceSet_valid:1;
    u64  maxMIMO_Layers_r16_valid:1;
    u64  minimumSchedulingOffsetK0_r16_valid:1;
    u64  antennaPortsFieldPresenceDCI_1_2_r16_valid:1;
    u64  dmrs_DownlinkForPDSCH_MappingTypeA_DCI_1_2_r16_valid:1;
    u64  dmrs_DownlinkForPDSCH_MappingTypeB_DCI_1_2_r16_valid:1;
    u64  dmrs_SequenceInitializationDCI_1_2_r16_valid:1;
    u64  harq_ProcessNumberSizeDCI_1_2_r16_valid:1;
    u64  mcs_TableDCI_1_2_r16_valid:1;
    u64  numberOfBitsForRV_DCI_1_2_r16_valid:1;
    u64  pdsch_TimeDomainAllocationListDCI_1_2_r16_valid:1;
    u64  prb_BundlingTypeDCI_1_2_r16_valid:1;
    u64  priorityIndicatorDCI_1_2_r16_valid:1;
    u64  rateMatchPatternGroup1DCI_1_2_r16_valid:1;
    u64  rateMatchPatternGroup2DCI_1_2_r16_valid:1;
    u64  resourceAllocationType1GranularityDCI_1_2_r16_valid:1;
    u64  vrb_ToPRB_InterleaverDCI_1_2_r16_valid:1;
    u64  referenceOfSLIVDCI_1_2_r16_valid:1;
    u64  resourceAllocationDCI_1_2_r16_valid:1;
    u64  priorityIndicatorDCI_1_1_r16_valid:1;
    u64  dataScramblingIdentityPDSCH2_r16_valid:1;
    u64  pdsch_TimeDomainAllocationList_r16_valid:1;
    u64  repetitionSchemeConfig_r16_valid:1;
    u64  repetitionSchemeConfig_v1630_valid:1;
    u64  pdsch_HARQ_ACK_OneShotFeedbackDCI_1_2_r17_valid:1;
    u64  pdsch_HARQ_ACK_EnhType3DCI_1_2_r17_valid:1;
    u64  pdsch_HARQ_ACK_EnhType3DCI_Field_1_2_r17_valid:1;
    u64  pdsch_HARQ_ACK_RetxDCI_1_2_r17_valid:1;
    u64  pucch_sSCellDynDCI_1_2_r17_valid:1;
    u64  dl_OrJointTCI_StateList_r17_valid:1;
    u64  beamAppTime_r17_valid:1;
    u64  dummy_valid:1;
    u64  dmrs_FD_OCC_DisabledForRank1_PDSCH_r17_valid:1;
    u64  minimumSchedulingOffsetK0_r17_valid:1;
    u64  harq_ProcessNumberSizeDCI_1_2_v1700_valid:1;
    u64  harq_ProcessNumberSizeDCI_1_1_r17_valid:1;
    u64 mcs_Table_r17_valid:1;    /* OPTIONAL */
    u64 mcs_TableDCI_1_2_r17_valid:1; /* OPTIONAL */
    u64 xOverheadMulticast_r17_valid:1;   /* OPTIONAL */
    u64 priorityIndicatorDCI_4_2_r17_valid:1; /* OPTIONAL */
    u64 sizeDCI_4_2_r17_valid:1; /* OPTIONAL */
    u64 pdsch_TimeDomainAllocationListForMultiPDSCH_r17_valid:1;
    u64  rsv:12;
   u32 dataScramblingIdentityPDSCH;	/* OPTIONAL */
   Dmrs_DownlinkForPDSCH_MappingTypeA_t dmrs_DownlinkForPDSCH_MappingTypeA;	/* OPTIONAL */
   Dmrs_DownlinkForPDSCH_MappingTypeB_t dmrs_DownlinkForPDSCH_MappingTypeB;	/* OPTIONAL */
   u32 num_of_tci_StatesToAddModList;
   TCI_State_t tci_StatesToAddModList[MAX_NR_OF_TCI_STATES];
   u8  num_of_tci_StatesToReleaseList;
   u16 tci_StatesToReleaseList[MAX_NR_OF_TCI_STATES];
   u32 vrb_ToPRB_Interleaver;	/* OPTIONAL ENUMERATED {n2, n4}*/
   u32 resourceAllocation;/*ENUMERATED { resourceAllocationType0, resourceAllocationType1, dynamicSwitch}*/

   Pdsch_TimeDomainAllocationList_t pdsch_TimeDomainAllocationList;	/* OPTIONAL */
   u32 pdsch_AggregationFactor;	/* enumerate refer to nr_Pdsch_AggregationFactor_e*/
   u32 num_of_rateMatchPatternToAddModList;
   rate_match_pattern_t rateMatchPatternToAddModList[MAX_NR_OF_RATE_MATCH_PATTERNS];
   u32 num_of_rateMatchPatternToReleaseList;
   u8 rateMatchPatternToReleaseList[MAX_NR_OF_RATE_MATCH_PATTERNS];
   u32 num_of_rateMatchPatternGroup1;
   u32 num_of_rateMatchPatternGroup2;
   RateMatchPatternGroup_t rateMatchPatternGroup1[MAX_NR_OF_RATE_MATCH_PATTERNS_PERGROUP];
   RateMatchPatternGroup_t rateMatchPatternGroup2[MAX_NR_OF_RATE_MATCH_PATTERNS_PERGROUP];
   u32 rbg_Size;
   u32 mcs_Table;	/* enumerate refer to nr_mcs_table_e */
   u32 maxNrofCodeWordsScheduledByDCI;	/*enumerate refer to nr_MaxNrofCodeWordsScheduledByDCI_e*/
   Prb_BundlingType_t prb_BundlingType;
   u32 num_of_zp_CSI_RS_ResourceToAddModList;
   u32 num_of_zp_CSI_RS_ResourceToReleaseList;
   ZP_CSI_RS_Resource_t zp_CSI_RS_ResourceToAddModList[MAX_NR_OF_ZP_CSI_RS_RESOURCES];
   u8 zp_CSI_RS_ResourceToReleaseList[MAX_NR_OF_ZP_CSI_RS_RESOURCES];
   u32 num_of_aperiodic_ZP_CSI_RS_ResourceSetsToAddModList;
   u32 num_of_aperiodic_ZP_CSI_RS_ResourceSetsToReleaseList;
   ZP_CSI_RS_ResourceSet_t aperiodic_ZP_CSI_RS_ResourceSetsToAddModList[16];
   u8 aperiodic_ZP_CSI_RS_ResourceSetsToReleaseList[16];
   u32 num_of_sp_ZP_CSI_RS_ResourceSetsToAddModList;
   u32 num_of_sp_ZP_CSI_RS_ResourceSetsToReleaseList;
   ZP_CSI_RS_ResourceSet_t sp_ZP_CSI_RS_ResourceSetsToAddModList[16];
   u32 sp_ZP_CSI_RS_ResourceSetsToReleaseList[16];
   P_ZP_CSI_RS_ResourceSet_t p_ZP_CSI_RS_ResourceSet;/* OPTIONAL */
   MaxMIMO_Layers_r16_t maxMIMO_Layers_r16;	/* OPTIONAL */
   MinimumSchedulingOffsetK0_r16_t minimumSchedulingOffsetK0_r16;	/* OPTIONAL */
   bool antennaPortsFieldPresenceDCI_1_2_r16;	/* OPTIONAL */
   u32 num_of_aperiodicZP_CSI_RS_ResourceSetsToAddModListDCI_1_2_r16;
   u32 num_of_aperiodicZP_CSI_RS_ResourceSetsToReleaseListDCI_1_2_r16;
   ZP_CSI_RS_ResourceSet_t aperiodicZP_CSI_RS_ResourceSetsToAddModListDCI_1_2_r16[16];
   u32 aperiodicZP_CSI_RS_ResourceSetsToReleaseListDCI_1_2_r16[16];
   Dmrs_DownlinkForPDSCH_MappingTypeA_DCI_1_2_r16_t dmrs_DownlinkForPDSCH_MappingTypeA_DCI_1_2_r16;
   Dmrs_DownlinkForPDSCH_MappingTypeB_DCI_1_2_r16_t dmrs_DownlinkForPDSCH_MappingTypeB_DCI_1_2_r16;	/* OPTIONAL */
   bool dmrs_SequenceInitializationDCI_1_2_r16;	/* OPTIONAL */
   u32 harq_ProcessNumberSizeDCI_1_2_r16;	/* OPTIONAL */
   u32 mcs_TableDCI_1_2_r16;	/* OPTIONAL */
   u32 numberOfBitsForRV_DCI_1_2_r16;	/* OPTIONAL */
   Pdsch_TimeDomainAllocationListDCI_1_2_r16_t pdsch_TimeDomainAllocationListDCI_1_2_r16;	/* OPTIONAL */
   Prb_BundlingTypeDCI_1_2_r16_t prb_BundlingTypeDCI_1_2_r16;	/* OPTIONAL */
   bool priorityIndicatorDCI_1_2_r16;	/* OPTIONAL */
   u32 num_of_rateMatchPatternGroup1DCI_1_2_r16;
   u32 num_of_rateMatchPatternGroup2DCI_1_2_r16;
   RateMatchPatternGroup_t rateMatchPatternGroup1DCI_1_2_r16[8];
   RateMatchPatternGroup_t rateMatchPatternGroup2DCI_1_2_r16[8];
   u32 resourceAllocationType1GranularityDCI_1_2_r16;	/* enumerate refer to nr_ResourceAllocationType1GranularityDCI_1_2_r16_e */
   u32 vrb_ToPRB_InterleaverDCI_1_2_r16;	/* nr_Vrb_ToPRB_InterleaverDCI_1_2_r16_e */
   bool referenceOfSLIVDCI_1_2_r16;	/* OPTIONAL */
   u32 resourceAllocationDCI_1_2_r16;	/*nr_ResourceAllocationDCI_1_2_r16_e*/
   bool priorityIndicatorDCI_1_1_r16;	/* OPTIONAL */
   u32 dataScramblingIdentityPDSCH2_r16;	/* OPTIONAL */
   Pdsch_TimeDomainAllocationList_r16_t pdsch_TimeDomainAllocationList_r16;	/* OPTIONAL */
   PDSCH_Config_RepetitionSchemeConfig_r16_t repetitionSchemeConfig_r16;	/* OPTIONAL */
   PDSCH_Config_RepetitionSchemeConfig_v1630_t repetitionSchemeConfig_v1630;	/* OPTIONAL */
   bool pdsch_HARQ_ACK_OneShotFeedbackDCI_1_2_r17;	/* OPTIONAL */
   bool pdsch_HARQ_ACK_EnhType3DCI_1_2_r17;	/* OPTIONAL */
   bool pdsch_HARQ_ACK_EnhType3DCI_Field_1_2_r17;	/* OPTIONAL */
   bool pdsch_HARQ_ACK_RetxDCI_1_2_r17;	/* OPTIONAL */
   bool pucch_sSCellDynDCI_1_2_r17;	/* OPTIONAL */
   Dl_OrJointTCI_StateList_r17_t dl_OrJointTCI_StateList_r17;	/* OPTIONAL */
   u32 beamAppTime_r17;	/*enumerate refer to nr_BeamAppTime_r17_e*/
   PDSCH_Config_Dummy_t dummy;	/* OPTIONAL */
   bool dmrs_FD_OCC_DisabledForRank1_PDSCH_r17;	/* OPTIONAL */
   MinimumSchedulingOffsetK0_r17_t minimumSchedulingOffsetK0_r17;	/* OPTIONAL */
   u32 harq_ProcessNumberSizeDCI_1_2_v1700;	/* OPTIONAL */
   u32 harq_ProcessNumberSizeDCI_1_1_r17;	/* OPTIONAL */
   u32 mcs_Table_r17;	/* nr_PDSCH_Config_Mcs_Table_r17_e */
   u32 mcs_TableDCI_1_2_r17;	/* OPTIONAL */
   u32 xOverheadMulticast_r17;	/* OPTIONAL */
   bool priorityIndicatorDCI_4_2_r17;	/* OPTIONAL */
   u32 sizeDCI_4_2_r17;	/* OPTIONAL */
   Pdsch_TimeDomainAllocationListForMultiPDSCH_r17_t pdsch_TimeDomainAllocationListForMultiPDSCH_r17;	/* OPTIONAL */
}pdsch_config_t;





typedef struct  {
    
#define	DetectionResource_ssb_Index_chosen	0
#define	DetectionResource_csi_RS_Index_chosen	1

   int choice;
   union {
      u8 ssb_Index;
      u8 csi_RS_Index;
   } value;
} DetectionResource_t;



typedef struct  {
   u8 radioLinkMonitoringRS_Id;
   u8 purpose;
   u8 padding[2];
   DetectionResource_t detectionResource;
}RadioLinkMonitoringRS_t;


typedef struct  {
#define	DetectionResource_r17_ssb_Index_chosen	0
#define	DetectionResource_r17_csi_RS_Index_chosen	1

   int choice;
   union {
      u8 ssb_Index;
      u8 csi_RS_Index;
   } value;
}DetectionResource_r17_t;


typedef struct  {
   u8 beamLinkMonitoringRS_Id_r17;
   DetectionResource_r17_t detectionResource_r17;
}BeamLinkMonitoringRS_r17_t;



typedef struct  {
   BeamLinkMonitoringRS_r17_t bfdResourcesToAddModList_r17[64];	/* OPTIONAL */
   u8 bfdResourcesToReleaseList_r17[64];	/* OPTIONAL */
   u8 beamFailureInstanceMaxCount_r17;	/* OPTIONAL */
   u8 beamFailureDetectionTimer_r17;	/* OPTIONAL */
}BeamFailureDetectionSet_r17_t;




typedef struct  {
    BeamFailureDetectionSet_r17_t failureDetectionSet1_r17;	/* OPTIONAL */
    BeamFailureDetectionSet_r17_t failureDetectionSet2_r17;	/* OPTIONAL */
    u16 additionalPCI_r17;	/* OPTIONAL */
} BeamFailureDetection_r17_t;





typedef struct  {
   u8 num_of_failureDetectionResourcesToAddModList;
   u8 num_of_failureDetectionResourcesToReleaseList;
   u8 beamFailureInstanceMaxCount;	/* OPTIONAL */
   u8 beamFailureDetectionTimer;	/* OPTIONAL */
   RadioLinkMonitoringRS_t failureDetectionResourcesToAddModList[10];	/* OPTIONAL */
   u8 failureDetectionResourcesToReleaseList[10];
   u8 padding[2];
   BeamFailureDetection_r17_t beamFailure_r17;	/* OPTIONAL */
} RadioLinkMonitoringConfig_t;

typedef struct  {
  u8 StateList[8];
} sps_ConfigDeactivationStateList_r16_t;

typedef struct  {
   int choice;
   union {
      unsigned int ssb_r16;
      unsigned int csi_RS_r16;
   } value;
}CandidateBeamConfig_r16_t;


typedef struct  {
    u8 servingCellId_valid:1;
    u8 rsv:7;
    u8 padding[3];
   CandidateBeamConfig_r16_t candidateBeamConfig_r16;
   u32 servingCellId;	/* OPTIONAL */
} CandidateBeamRS_r16_t;



typedef struct  {
    u8 rsrp_ThresholdBFR_r16_valid:1;
    u8 candidateBeamRS_List_r16_valid:1;
    u8 candidateBeamRS_List2_r17_valid:1;
    u8 rsv:5;
   u16 rsrp_ThresholdBFR_r16;	/* OPTIONAL */
   u8 num_of_candidateBeamRS_List_r16;
   u8 num_of_candidateBeamRS_List2_r17;
   u8 padding[3];
   CandidateBeamRS_r16_t candidateBeamRS_List_r16[64];	/* OPTIONAL */
   CandidateBeamRS_r16_t candidateBeamRS_List2_r17[64];	/* OPTIONAL */
}BeamFailureRecoveryRSConfig_r16_t;


typedef struct  {
//#define	BeamFailureRecoverySCellConfig_r16_release_chosen	0
//#define	BeamFailureRecoverySCellConfig_r16_setup_chosen	1
//   int choice;
//   union {
//      u8 release;
      BeamFailureRecoveryRSConfig_r16_t setup;
//   } value;
} BeamFailureRecoverySCellConfig_r16_t;





typedef struct  {
#define	Sl_PDCCH_Config_r16_release_chosen	0
#define	Sl_PDCCH_Config_r16_setup_chosen	1

   int choice;
   union {
      u8 release;
      PDCCH_Config_t setup;
   } value;
}Sl_PDCCH_Config_r16_t;




typedef struct  {
//#define	BeamFailureRecoverySpCellConfig_r17_release_chosen	0
//#define	BeamFailureRecoverySpCellConfig_r17_setup_chosen	1

//   u8 choice;
//   union {
//      u8 release;
      BeamFailureRecoveryRSConfig_r16_t setup;
//   } value;
}BeamFailureRecoverySpCellConfig_r17_t;


typedef struct  {
   u16 locationAndBandwidthMulticast_r17;	/* OPTIONAL */
   PDCCH_Config_t pdcch_ConfigMulticast_r17;	/* OPTIONAL */
   PDCCH_Config_t pdsch_ConfigMulticast_r17;	/* OPTIONAL */
   sps_config_t sps_ConfigMulticastToAddModList_r17[8];
   u8 sps_ConfigMulticastToReleaseList_r17[8];
} CFR_ConfigMulticast_r17_t;



typedef struct  {
#define	BWP_DownlinkDedicated_Cfr_ConfigMulticast_r17_release_chosen	0
#define	BWP_DownlinkDedicated_Cfr_ConfigMulticast_r17_setup_chosen	1

   int choice;
   union {
      u8 release;
      CFR_ConfigMulticast_r17_t  setup;
   } value;
}BWP_DownlinkDedicated_Cfr_ConfigMulticast_r17_t;

typedef struct{
#define	ppw_Scs15_n4_chosen	0
#define	ppw_Scs15_n5_chosen	1
#define	ppw_Scs15_n8_chosen	2
#define	ppw_Scs15_n10_chosen	3
#define	ppw_Scs15_n16_chosen	4
#define	ppw_Scs15_n20_chosen	5
#define	ppw_Scs15_n32_chosen	6
#define	ppw_Scs15_n40_chosen	7
#define	ppw_Scs15_n64_chosen	8
#define	ppw_Scs15_n80_chosen	9
#define	ppw_Scs15_n160_chosen	10
#define	ppw_Scs15_n320_chosen	11
#define	ppw_Scs15_n640_chosen	12
#define	ppw_Scs15_n1280_chosen	13
#define	ppw_Scs15_n2560_chosen	14
#define	ppw_Scs15_n5120_chosen	15
#define	ppw_Scs15_n10240_chosen	16
    int choice;
    union {
        unsigned int n4;
        unsigned int n5;
        unsigned int n8;
        unsigned int n10;
        unsigned int n16;
        unsigned int n20;
        unsigned int n32;
        unsigned int n40;
        unsigned int n64;
        unsigned int n80;
        unsigned int n160;
        unsigned int n320;
        unsigned int n640;
        unsigned int n1280;
        unsigned int n2560;
        unsigned int n5120;
        unsigned int n10240;
   } value;
}nr_ppw_period_offset_scs15_t;

typedef struct{
#define	ppw_Scs30_n8_chosen	0
#define	ppw_Scs30_n10_chosen	1
#define	ppw_Scs30_n16_chosen	2
#define	ppw_Scs30_n20_chosen	3
#define	ppw_Scs30_n32_chosen	4
#define	ppw_Scs30_n40_chosen	5
#define	ppw_Scs30_n64_chosen	6
#define	ppw_Scs30_n80_chosen	7
#define	ppw_Scs30_n128_chosen	8
#define	ppw_Scs30_n160_chosen	9
#define	ppw_Scs30_n320_chosen	10
#define	ppw_Scs30_n640_chosen	11
#define	ppw_Scs30_n1280_chosen	12
#define	ppw_Scs30_n2560_chosen	13
#define	ppw_Scs30_n5120_chosen	14
#define	ppw_Scs30_n10240_chosen	15
#define	ppw_Scs30_n20480_chosen	16
   int choice;
   union {
      unsigned int n8;
      unsigned int n10;
      unsigned int n16;
      unsigned int n20;
      unsigned int n32;
      unsigned int n40;
      unsigned int n64;
      unsigned int n80;
      unsigned int n128;
      unsigned int n160;
      unsigned int n320;
      unsigned int n640;
      unsigned int n1280;
      unsigned int n2560;
      unsigned int n5120;
      unsigned int n10240;
      unsigned int n20480;
   } value;
}nr_ppw_period_offset_scs30_t;


typedef struct{
#define	ppw_Scs60_n16_chosen	0
#define	ppw_Scs60_n20_chosen	1
#define	ppw_Scs60_n32_chosen	2
#define	ppw_Scs60_n40_chosen	3
#define	ppw_Scs60_n64_chosen	4
#define	ppw_Scs60_n80_chosen	5
#define	ppw_Scs60_n128_chosen	6
#define	ppw_Scs60_n160_chosen	7
#define	ppw_Scs60_n256_chosen	8
#define	ppw_Scs60_n320_chosen	9
#define	ppw_Scs60_n640_chosen	10
#define	ppw_Scs60_n1280_chosen	11
#define	ppw_Scs60_n2560_chosen	12
#define	ppw_Scs60_n5120_chosen	13
#define	ppw_Scs60_n10240_chosen	14
#define	ppw_Scs60_n20480_chosen	15
#define	ppw_Scs60_n40960_chosen	16
   int choice;
   union {
      unsigned int n16;
      unsigned int n20;
      unsigned int n32;
      unsigned int n40;
      unsigned int n64;
      unsigned int n80;
      unsigned int n128;
      unsigned int n160;
      unsigned int n256;
      unsigned int n320;
      unsigned int n640;
      unsigned int n1280;
      unsigned int n2560;
      unsigned int n5120;
      unsigned int n10240;
      unsigned int n20480;
      unsigned int n40960;
   } value;
}nr_ppw_period_offset_scs60_t;

typedef struct{
#define	ppw_Scs120_n32_chosen	0
#define	ppw_Scs120_n40_chosen	1
#define	ppw_Scs120_n64_chosen	2
#define	ppw_Scs120_n80_chosen	3
#define	ppw_Scs120_n128_chosen	4
#define	ppw_Scs120_n160_chosen	5
#define	ppw_Scs120_n256_chosen	6
#define	ppw_Scs120_n320_chosen	7
#define	ppw_Scs120_n512_chosen	8
#define	ppw_Scs120_n640_chosen	9
#define	ppw_Scs120_n1280_chosen	10
#define	ppw_Scs120_n2560_chosen	11
#define	ppw_Scs120_n5120_chosen	12
#define	ppw_Scs120_n10240_chosen	13
#define	ppw_Scs120_n20480_chosen	14
#define	ppw_Scs120_n40960_chosen	15
#define	ppw_Scs120_n81920_chosen	16
   int choice;
   union {
      unsigned int n32;
      unsigned int n40;
      unsigned int n64;
      unsigned int n80;
      unsigned int n128;
      unsigned int n160;
      unsigned int n256;
      unsigned int n320;
      unsigned int n512;
      unsigned int n640;
      unsigned int n1280;
      unsigned int n2560;
      unsigned int n5120;
      unsigned int n10240;
      unsigned int n20480;
      unsigned int n40960;
      unsigned int n81920;
   } value;
}nr_ppw_period_offset_scs120_t;


typedef struct{
#define	DL_PPW_PeriodicityAndStartSlot_r17_scs15_chosen	0
#define	DL_PPW_PeriodicityAndStartSlot_r17_scs30_chosen	1
#define	DL_PPW_PeriodicityAndStartSlot_r17_scs60_chosen	2
#define	DL_PPW_PeriodicityAndStartSlot_r17_scs120_chosen	3

   int choice;
   union {
      nr_ppw_period_offset_scs15_t scs15;
      nr_ppw_period_offset_scs30_t scs30;
      nr_ppw_period_offset_scs60_t scs60;
      nr_ppw_period_offset_scs120_t scs120;
   } value;
} DL_PPW_PeriodicityAndStartSlot_r17_t;



typedef struct  {
    u8 type_r17_valid:1;
    u8 priority_r17_valid:1;
    u8 rsv:6;
   u8 dl_PPW_ID_r17;
   u8 length_r17;
   u8 type_r17;	/* OPTIONAL */
   u8 priority_r17;	/* OPTIONAL */
   u8 padding[3];
   DL_PPW_PeriodicityAndStartSlot_r17_t dl_PPW_PeriodicityAndStartSlot_r17;
}DL_PPW_PreConfig_r17_t;


typedef struct  {
    u8 ssb_Periodicity_r17_valid:1;
    u8 ssb_TimeOffset_r17_valid:1;
    u8 rsv:7;
    u8 padding;
    u8 ssb_Periodicity_r17;  /* OPTIONAL */
    u8 ssb_TimeOffset_r17;   /* OPTIONAL */
   u64 absoluteFrequencySSB_r17;
} NonCellDefiningSSB_r17_t;

typedef struct  {
    u32                        pdcch_Config_valid:1;
    u32                        pdsch_Config_valid:1;
    u32                        radio_link_monitoring_config_valid:1;
    u32                        beamFailureRecoverySCellConfig_r16_valid:1;
    u32                        preConfGapStatus_r17_valid:1;
    u32                        beamFailureRecoverySpCellConfig_r17_valid:1;
    u32                        harq_FeedbackEnablingforSPSactive_r17_valid:1;
    u32                        nonCellDefiningSSB_r17_valid:1;
    u32                        servingCellMO_r17_valid:1;
    u32                        rsv:23;
    PDCCH_Config_t pdcch_Config;
    pdsch_config_t pdsch_Config;
    sps_config_t sps_config;
    RadioLinkMonitoringConfig_t radio_link_monitoring_config;
    sps_config_t sps_ConfigToAddModList_r16[8];
    u8 sps_ConfigToReleaseList_r16[8];
    sps_ConfigDeactivationStateList_r16_t sps_ConfigDeactivationStateList_r16[16];
    BeamFailureRecoverySCellConfig_r16_t beamFailureRecoverySCellConfig_r16;	/* OPTIONAL */
    Sl_PDCCH_Config_r16_t sl_PDCCH_Config_r16;	/* OPTIONAL */
    u8 preConfGapStatus_r17;
    BeamFailureRecoverySpCellConfig_r17_t beamFailureRecoverySpCellConfig_r17;	/* OPTIONAL */
    bool harq_FeedbackEnablingforSPSactive_r17;	/* OPTIONAL */
    BWP_DownlinkDedicated_Cfr_ConfigMulticast_r17_t cfr_ConfigMulticast_r17;	/* OPTIONAL */
    u8 num_of_dl_PPW_PreConfigToAddModList_r17;
    u8 num_dl_PPW_PreConfigToReleaseList_r17;
    DL_PPW_PreConfig_r17_t dl_PPW_PreConfigToAddModList_r17[4];
    u8 dl_PPW_PreConfigToReleaseList_r17[4];
    NonCellDefiningSSB_r17_t nonCellDefiningSSB_r17;	/* OPTIONAL */
    u16  servingCellMO_r17;	/* OPTIONAL */
}BWP_DownlinkDedicated_t;


typedef struct
{
    u8 bwp_downlink_common_valid:1;
    u8 bwp_downlink_dedicated_valid:1;
    u8 rsv:6;
    u8 bwp_id;
    u8 padding[2];
    wnrrc_bwp_dl_common_t bwp_downlink_common;
    BWP_DownlinkDedicated_t bwp_downlink_dedicated;
}bwp_downlink_t;


typedef struct
{
    u8 frequency_info_dl_valid:1;
    u8 initialDownlinkBWP_valid:1;
    u8                         :6;
    frequency_info_dl_t frequency_info_dl;
    wnrrc_bwp_dl_common_t initialDownlinkBWP;
    /*initialDownlinkBWP-RedCap-r17 not surpport*/
}downlink_config_common_t;


typedef struct {

   u8                                     absoluteFrequencyPointA_valid:1;
   u8                                     pmax_valid;
   u8                                     freq_shift_7p5_valid:1;
   u8                                     :5;
   u8                                     frequencyBandList_num;
   u8                                     scs_specific_carrier_list_num;
   u8 frequencyBandList[MAX_NR_MULTI_BAND_NUM];	/* OPTIONAL */
   u64 absoluteFrequencyPointA;	/* OPTIONAL */
   scs_specific_carrier_t scs_specific_carrier_list[MAX_NR_SCS_NUM];
   u16 additionalSpectrumEmission;	/* OPTIONAL */
   s16 p_Max;	/* OPTIONAL */
   u8 frequencyShift7p5khz;	/* OPTIONAL */
}FrequencyInfoUL_t;


typedef struct  {
   u8 locationAndBandwidth;
   u8 subcarrierSpacing;
   u8 cyclicPrefix;	/* OPTIONAL */
   u8 padding;
} BWP_t;

typedef struct  {
   u32 prach_ConfigurationIndex;
   s32 msg1_FDM; /*enum Msg1_FDM_one = 0,
						   Msg1_FDM_two = 1,
						   Msg1_FDM_four = 2,
						   Msg1_FDM_eight = 3*/
   u32 msg1_FrequencyStart;
   u32 zeroCorrelationZoneConfig;
   s32 preambleReceivedTargetPower;
   s32 preambleTransMax; /*enum PreambleTransMax_n3 = 0,
							   PreambleTransMax_n4 = 1,
							   PreambleTransMax_n5 = 2,
							   PreambleTransMax_n6 = 3,
							   PreambleTransMax_n7 = 4,
							   PreambleTransMax_n8 = 5,
							   PreambleTransMax_n10 = 6,
							   PreambleTransMax_n20 = 7,
							   PreambleTransMax_n50 = 8,
							   PreambleTransMax_n100 = 9,
							   PreambleTransMax_n200 = 10*/
   s32 powerRampingStep; /*PowerRampingStep_dB0 = 0,
							   PowerRampingStep_dB2 = 1,
							   PowerRampingStep_dB4 = 2,
							   PowerRampingStep_dB6 = 3*/
   s32 ra_ResponseWindow; /*enum Ra_ResponseWindow_sl1 = 0,
													   Ra_ResponseWindow_sl2 = 1,
													   Ra_ResponseWindow_sl4 = 2,
													   Ra_ResponseWindow_sl8 = 3,
													   Ra_ResponseWindow_sl10 = 4,
													   Ra_ResponseWindow_sl20 = 5,
													   Ra_ResponseWindow_sl40 = 6,
													   Ra_ResponseWindow_sl80 = 7*/

   u8 prach_ConfigurationPeriodScaling_IAB_r16_valid:1;
   u8 prach_ConfigurationFrameOffset_IAB_r16_valid:1;
   u8 prach_ConfigurationSOffset_IAB_r16_valid:1;
   u8 ra_ResponseWindow_v1610_valid:1;
   u8 prach_ConfigurationIndex_v1610_valid:1;
   u8 ra_ResponseWindow_v1700_valid:1;
   u8 :2;
                                                       
   s32 prach_ConfigurationPeriodScaling_IAB_r16;	/* OPTIONAL enum  Prach_ConfigurationPeriodScaling_IAB_r16_scf1 = 0,
																	   Prach_ConfigurationPeriodScaling_IAB_r16_scf2 = 1,
																	   Prach_ConfigurationPeriodScaling_IAB_r16_scf4 = 2,
																	   Prach_ConfigurationPeriodScaling_IAB_r16_scf8 = 3,
																	   Prach_ConfigurationPeriodScaling_IAB_r16_scf16 = 4,
																	   Prach_ConfigurationPeriodScaling_IAB_r16_scf32 = 5,
																	   Prach_ConfigurationPeriodScaling_IAB_r16_scf64 = 6 */
   u32 prach_ConfigurationFrameOffset_IAB_r16;	/* OPTIONAL */
   u32 prach_ConfigurationSOffset_IAB_r16;	/* OPTIONAL */
   s32 ra_ResponseWindow_v1610;	/* OPTIONAL enum   Ra_ResponseWindow_v1610_sl60 = 0,
   																				Ra_ResponseWindow_v1610_sl160 = 1 */
   u32 prach_ConfigurationIndex_v1610;	/* OPTIONAL */
   s32 ra_ResponseWindow_v1700;	/* OPTIONAL enum Ra_ResponseWindow_v1700_sl240 = 0,
												   Ra_ResponseWindow_v1700_sl320 = 1,
												   Ra_ResponseWindow_v1700_sl640 = 2,
												   Ra_ResponseWindow_v1700_sl960 = 3,
												   Ra_ResponseWindow_v1700_sl1280 = 4,
												   Ra_ResponseWindow_v1700_sl1920 = 5,
												   Ra_ResponseWindow_v1700_sl2560 = 6*/
}RACH_ConfigGeneric_t;


typedef struct  {
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_oneEighth_chosen	0
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_oneFourth_chosen	1
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_oneHalf_chosen	2
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_one_chosen	3
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_two_chosen	4
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_four_chosen	5
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_eight_chosen	6
#define	Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_sixteen_chosen	7

   int choice;
   union {
      u8 oneEighth;
      u8 oneFourth;
      u8 oneHalf;
      u8 one;
      u8 two;
      u16 four;
      u16 eight;
      u16 sixteen;
   } value;
}Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_t;

typedef struct  {
   u8 ra_Msg3SizeGroupA;
   u8 messagePowerOffsetGroupB;
   u8 numberOfRA_PreamblesGroupA;
   u8 padding;
}GroupBconfigured_t;

typedef struct  {
#define	Prach_RootSequenceIndex_l839_chosen	0
#define	Prach_RootSequenceIndex_l139_chosen	1

   int choice;
   union {
      unsigned int l839;
      unsigned int l139;
   } value;
} Prach_RootSequenceIndex_t;

typedef struct  {
   s32 powerRampingStepHighPriority;/* enum  PowerRampingStepHighPriority_dB0 = 0,
                                    PowerRampingStepHighPriority_dB2 = 1,
                                    PowerRampingStepHighPriority_dB4 = 2,
                                    PowerRampingStepHighPriority_dB6 = 3*/
   u8 scalingFactorBI_valid; 
   s32 scalingFactorBI; /* OPTIONAL enum  ScalingFactorBI_zero = 0,
                        ScalingFactorBI_dot25 = 1,
                        ScalingFactorBI_dot5 = 2,
                        ScalingFactorBI_dot75 = 3*/
}RA_Prioritization_t;


typedef struct  {
#define	Prach_RootSequenceIndex_r16_l571_chosen	0
#define	Prach_RootSequenceIndex_r16_l1151_chosen	1
   int choice;
   union {
      u16 l571;
      u16 l1151;
   } value;
} Prach_RootSequenceIndex_r16_t;



typedef struct {
   RA_Prioritization_t ra_Prioritization_r16;
   u8 ra_PrioritizationForAI_r16;
} Ra_PrioritizationForAccessIdentity_r16_t;

typedef struct  {
   u8 nsag_ID_List_r17[8];
   RA_Prioritization_t ra_Prioritization_r17;
}RA_PrioritizationSliceInfo_r17_t;


typedef struct  {
   RA_PrioritizationSliceInfo_r17_t ra_PrioritizationSliceInfoList_r17[8];
} RA_PrioritizationForSlicing_r17_t;


typedef struct  {
   u8 redCap_r17;	/* OPTIONAL */
   u8 smallData_r17;	/* OPTIONAL */
   u8 nsag_r17[8];
   u8 msg3_Repetitions_r17;	/* OPTIONAL */
   u8 spare4;	/* OPTIONAL */
   u8 spare3;	/* OPTIONAL */
   u8 spare2;	/* OPTIONAL */
   u8 spare1;	/* OPTIONAL */
}FeatureCombination_r17_t;


typedef struct  {
   u8 ra_SizeGroupA_r17;
   u8 messagePowerOffsetGroupB_r17;
   u8 numberOfRA_PreamblesGroupA_r17;
   u8 padding;
}GroupBconfigured_r17_t;

 typedef struct  {

    u8 msgA_DMRS_AdditionalPosition_r16_valid:1;
    u8 msgA_MaxLength_r16_valid:1;
    u8 msgA_PUSCH_DMRS_CDM_Group_r16_valid:1;
    u8 msgA_PUSCH_NrofPorts_r16_valid:1;
    u8 msgA_ScramblingID0_r16_valid:1;
    u8 msgA_ScramblingID1_r16_valid:1;
    u8                             :2;
    u8 padding[3];
    s32 msgA_DMRS_AdditionalPosition_r16;	 /* OPTIONAL enum MsgA_DMRS_AdditionalPosition_r16_pos0 = 0,
    										MsgA_DMRS_AdditionalPosition_r16_pos1 = 1,
    										MsgA_DMRS_AdditionalPosition_r16_pos3 = 2*/
    s32 msgA_MaxLength_r16;  /* OPTIONAL enum  MsgA_MaxLength_r16_len2 = 0*/
    u32 msgA_PUSCH_DMRS_CDM_Group_r16;	 /* OPTIONAL */
    u32 msgA_PUSCH_NrofPorts_r16;	 /* OPTIONAL */
    u32 msgA_ScramblingID0_r16;  /* OPTIONAL */
    u32 msgA_ScramblingID1_r16;  /* OPTIONAL */
 }MsgA_DMRS_Config_r16_t;


 typedef struct  {
    u8 startSymbolAndLengthMsgA_PO_r16_valid:1;
    u8 msgA_PUSCH_TimeDomainAllocation_r16_valid:1;
    u8 mappingTypeMsgA_PUSCH_r16_valid:1;
    u8 guardPeriodMsgA_PUSCH_r16_valid:1;
    
    u8 msgA_IntraSlotFrequencyHopping_r16_valid:1;
    u8 msgA_HoppingBits_r16_valid:1;
    u8 msgA_Alpha_r16_valid:1;
    u8 interlaceIndexFirstPO_MsgA_PUSCH_r16_valid:1;
    
    u8 nrofInterlacesPerMsgA_PO_r16_valid:1;
    u8                                   :7;

    
    u32 msgA_MCS_r16;
    u32 nrofSlotsMsgA_PUSCH_r16;
    s32 nrofMsgA_PO_PerSlot_r16;/*enum NrofMsgA_PO_PerSlot_r16_one = 0,
    								   NrofMsgA_PO_PerSlot_r16_two = 1,
    								   NrofMsgA_PO_PerSlot_r16_three = 2,
    								   NrofMsgA_PO_PerSlot_r16_six = 3*/
    u32 msgA_PUSCH_TimeDomainOffset_r16;
    u32 msgA_PUSCH_TimeDomainAllocation_r16;	/* OPTIONAL */
    u32 startSymbolAndLengthMsgA_PO_r16;	/* OPTIONAL */
    s32 mappingTypeMsgA_PUSCH_r16;	/* OPTIONAL enum  MappingTypeMsgA_PUSCH_r16_typeA = 0,
    														MappingTypeMsgA_PUSCH_r16_typeB = 1*/
    u32 guardPeriodMsgA_PUSCH_r16;	/* OPTIONAL */
    u32 guardBandMsgA_PUSCH_r16;
    u32 frequencyStartMsgA_PUSCH_r16;
    u32 nrofPRBs_PerMsgA_PO_r16;
    s32 nrofMsgA_PO_FDM_r16; /*enum NrofMsgA_PO_FDM_r16_one = 0,
    							   NrofMsgA_PO_FDM_r16_two = 1,
    							   NrofMsgA_PO_FDM_r16_four = 2,
    							   NrofMsgA_PO_FDM_r16_eight = 3*/
    s32 msgA_IntraSlotFrequencyHopping_r16;	/* OPTIONAL enum MsgA_IntraSlotFrequencyHopping_r16_enabled = 0*/
    u8/*SIZE(2)*/ msgA_HoppingBits_r16;	/* OPTIONAL */
    MsgA_DMRS_Config_r16_t msgA_DMRS_Config_r16;
    u32 nrofDMRS_Sequences_r16;
    s32 msgA_Alpha_r16;	/* OPTIONAL enum MsgA_Alpha_r16_alpha0 = 0,
    									   MsgA_Alpha_r16_alpha04 = 1,
    									   MsgA_Alpha_r16_alpha05 = 2,
    									   MsgA_Alpha_r16_alpha06 = 3,
    									   MsgA_Alpha_r16_alpha07 = 4,
    									   MsgA_Alpha_r16_alpha08 = 5,
    									   MsgA_Alpha_r16_alpha09 = 6,
    									   MsgA_Alpha_r16_alpha1 = 7*/
    u32 interlaceIndexFirstPO_MsgA_PUSCH_r16;	/* OPTIONAL */
    u32 nrofInterlacesPerMsgA_PO_r16;	/* OPTIONAL */
}MsgA_PUSCH_Resource_r16_t;


typedef struct  {
   MsgA_PUSCH_Resource_r16_t msgA_PUSCH_ResourceGroupA_r16;	/* OPTIONAL */
   MsgA_PUSCH_Resource_r16_t msgA_PUSCH_ResourceGroupB_r16;	/* OPTIONAL */
   u8 msgA_TransformPrecoder_r16;	/* OPTIONAL */
   u8 msgA_DataScramblingIndex_r16;	/* OPTIONAL */
   s8 msgA_DeltaPreamble_r16;	/* OPTIONAL */
}MsgA_PUSCH_Config_r16_t;


typedef struct  {

   FeatureCombination_r17_t featureCombination_r17;
   u8 startPreambleForThisPartition_r17;
   u8 numberOfPreamblesPerSSB_ForThisPartition_r17;
   u8 ssb_SharedRO_MaskIndex_r17;	/* OPTIONAL */
   GroupBconfigured_r17_t groupBconfigured_r17;	/* OPTIONAL */
   MsgA_PUSCH_Config_r16_t separateMsgA_PUSCH_Config_r17;	/* OPTIONAL */
  u16 msgA_RSRP_Threshold_r17;	/* OPTIONAL */
   u16 rsrp_ThresholdSSB_r17;	/* OPTIONAL */
   s8 deltaPreamble_r17;	/* OPTIONAL */
}FeatureCombinationPreambles_r17_t;


typedef struct  {
   RACH_ConfigGeneric_t rach_ConfigGeneric;
   u16 totalNumberOfRA_Preambles;	/* OPTIONAL */
   Ssb_perRACH_OccasionAndCB_PreamblesPerSSB_t ssb_perRACH_OccasionAndCB_PreamblesPerSSB;	/* OPTIONAL */
   GroupBconfigured_t groupBconfigured;	/* OPTIONAL */
   u8 ra_ContentionResolutionTimer;
   u16 rsrp_ThresholdSSB;	/* OPTIONAL */
   u16 rsrp_ThresholdSSB_SUL;	/* OPTIONAL */
   Prach_RootSequenceIndex_t prach_RootSequenceIndex;
   u8 msg1_SubcarrierSpacing;	/* OPTIONAL */
   u8 restrictedSetConfig;
   u8 msg3_transformPrecoder;	/* OPTIONAL */
   Ra_PrioritizationForAccessIdentity_r16_t ra_PrioritizationForAccessIdentity_r16;	/* OPTIONAL */
   Prach_RootSequenceIndex_r16_t prach_RootSequenceIndex_r16;	/* OPTIONAL */
   RA_PrioritizationForSlicing_r17_t ra_PrioritizationForSlicing_r17;	/* OPTIONAL */
   FeatureCombinationPreambles_r17_t featureCombinationPreamblesList_r17[256];	/* OPTIONAL */
}RACH_ConfigCommon_t;


typedef struct  {
    
#define	BWP_UplinkCommon_Rach_ConfigCommon_release_chosen	0
#define	BWP_UplinkCommon_Rach_ConfigCommon_setup_chosen	1
   int choice;
   union {
      u8 release;
      RACH_ConfigCommon_t setup;
   } value;
}BWP_UplinkCommon_Rach_ConfigCommon_t;

typedef struct{
    u8 k2_valid:1;
    u8 rsv:7;
    u8 k2;    /* OPTIONAL */
    u8 mappingType;/*enumerate 0:typeA, 1:typeB*/
    u8 startSymbolAndLength;/*0...127*/
}PUSCH_TimeDomainResourceAllocation_t;

typedef struct  {
   u8 groupHoppingEnabledTransformPrecoding;	/* OPTIONAL */
   PUSCH_TimeDomainResourceAllocation_t pusch_TimeDomainAllocationList[16];
   s8 msg3_DeltaPreamble;	/* OPTIONAL */
   s8 p0_NominalWithGrant;	/* OPTIONAL */
}PUSCH_ConfigCommon_t;


typedef struct  {
    
#define	BWP_UplinkCommon_Pusch_ConfigCommon_release_chosen	0
#define	BWP_UplinkCommon_Pusch_ConfigCommon_setup_chosen	1

   int choice;
   union {
      char release;
      PUSCH_ConfigCommon_t setup;
   }value;
}BWP_UplinkCommon_Pusch_ConfigCommon_t;


typedef struct  {
   u16 pucch_ResourceCommon;	/* OPTIONAL */
   u8 pucch_GroupHopping;
   u16 hoppingId;	/* OPTIONAL */
   s8 p0_nominal;	/* OPTIONAL */
   u16 nrofPRBs;	/* OPTIONAL */
   u8 intra_SlotFH_r17;	/* OPTIONAL */
   u16 pucch_ResourceCommonRedCap_r17;	/* OPTIONAL */
   u8 additionalPRBOffset_r17;	/* OPTIONAL */
}PUCCH_ConfigCommon_t;




typedef struct {
#define	BWP_UplinkCommon_Pucch_ConfigCommon_release_chosen	0
#define	BWP_UplinkCommon_Pucch_ConfigCommon_setup_chosen	1

   int choice;
   union {
      u8 release;
      PUCCH_ConfigCommon_t setup;
   } value;
}BWP_UplinkCommon_Pucch_ConfigCommon_t;

typedef struct{
    u8 maxPayloadSize_valid:1;
    u8 rsv:7;
    u8 num_of_resourceList;
   u32 pucch_ResourceSetId;
   u32 resourceList[32];
   u32 maxPayloadSize;	/* OPTIONAL */
}PUCCH_ResourceSet_t;

typedef struct
{
   unsigned int initialCyclicShift;
   unsigned int nrofSymbols;
   unsigned int startingSymbolIndex;
}PUCCH_format0_t;

typedef struct{
   u32 initialCyclicShift;
   u32 nrofSymbols;
   u32 startingSymbolIndex;
   u32 timeDomainOCC;
}PUCCH_format1_t;

typedef struct
{
   u32 nrofPRBs;
   u32 nrofSymbols;
   u32 startingSymbolIndex;
}PUCCH_format2_t;

typedef struct
{
   u32 nrofPRBs;
   u32 nrofSymbols;
   u32 startingSymbolIndex;
}PUCCH_format3_t;

typedef struct
{
   u32 nrofSymbols;
   u32 occ_Length; /* enum Occ_Length_n2 = 0, Occ_Length_n4 = 1 */
   u32 occ_Index;  /*enum Occ_Index_n0 = 0, Occ_Index_n1 = 1, Occ_Index_n2 = 2, Occ_Index_n3 = 3*/
   u32 startingSymbolIndex;
}PUCCH_format4_t;

typedef struct
{
    u8 interslotFrequencyHopping_valid:1;
    u8 additionalDMRS_valid:1;
    u8 maxCodeRate_valid:1;
    u8 nrofSlots_valid:1;
    u8 pi2BPSK_valid:1;
    u8 simultaneousHARQ_ACK_CSI_valid:1;
    u8 rsv:2;
    u8 padding[3];
   u32 interslotFrequencyHopping;	/* OPTIONAL enum InterslotFrequencyHopping_enabled = 0 */
   u32 additionalDMRS;	/* OPTIONAL enum  AdditionalDMRS_true = 0*/
   u32 maxCodeRate;	/* OPTIONAL enum PUCCH_MaxCodeRate_zeroDot08 = 0,
										   PUCCH_MaxCodeRate_zeroDot15 = 1,
										   PUCCH_MaxCodeRate_zeroDot25 = 2,
										   PUCCH_MaxCodeRate_zeroDot35 = 3,
										   PUCCH_MaxCodeRate_zeroDot45 = 4,
										   PUCCH_MaxCodeRate_zeroDot60 = 5,
										   PUCCH_MaxCodeRate_zeroDot80 = 6*/
   u32 nrofSlots;	/* OPTIONAL enum NrofSlots_n2 = 0,
												 NrofSlots_n4 = 1,
												 NrofSlots_n8 = 2*/
   u32 pi2BPSK;	/* OPTIONAL enum Pi2BPSK_enabled = 0*/
   u32 simultaneousHARQ_ACK_CSI;	/* OPTIONAL enum SimultaneousHARQ_ACK_CSI_true = 0 */
}PUCCH_FormatConfig_t;


typedef struct
{
//   s32 choice;
//#define	Format1_release_chosen	0
//#define	Format1_setup_chosen	1

//   union {
//      s8 release;
      PUCCH_FormatConfig_t setup;
//   } value;
}Format1_t;

typedef struct
{
//   s32 choice;
//#define	Format2_release_chosen	0
//#define	Format2_setup_chosen	1

 //  union {
//      s8 release;
      PUCCH_FormatConfig_t setup;
 //  } value;
}Format2_t;

typedef struct
{
//   s32 choice;
//#define	Format3_release_chosen	0
//#define	Format3_setup_chosen	1

//   union {
//      s8 release;
      PUCCH_FormatConfig_t setup;
//   } value;
}Format3_t;

typedef struct
{
//   s32 choice;
//#define	Format4_release_chosen	0
//#define	Format4_setup_chosen	1

//   union {
//      s8 release;
      PUCCH_FormatConfig_t setup;
//   } value;
}Format4_t;




typedef struct
{
   int choice;
#define	Format_format0_chosen	0
#define	Format_format1_chosen	1
#define	Format_format2_chosen	2
#define	Format_format3_chosen	3
#define	Format_format4_chosen	4

   union {
      PUCCH_format0_t format0;
      PUCCH_format1_t format1;
      PUCCH_format2_t format2;
      PUCCH_format3_t format3;
      PUCCH_format4_t format4;
   } value;
}Format_t;


typedef struct
{
    u8 intraSlotFrequencyHopping_valid:1;
    u8 startingPRB_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 pucch_ResourceId;
   u32 startingPRB;
   bool intraSlotFrequencyHopping;	/* OPTIONAL */ /*enum IntraSlotFrequencyHopping_enabled = 0*/
   u32 secondHopPRB;	/* OPTIONAL */
   Format_t format;
}PUCCH_Resource_t;


typedef struct  {
   s32 choice;
   union {
      s8 sym2;
      s8 sym6or7;
      s8 sl1;
      u32 sl2;
      u32 sl4;
      u32 sl5;
      u32 sl8;
      u32 sl10;
      u32 sl16;
      u32 sl20;
      u32 sl40;
      u32 sl80;
      u32 sl160;
      u32 sl320;
      u32 sl640;
   } value;
}SchedulingRequestResourceConfig_PeriodicityAndOffset_t;


typedef struct
{
    u8 periodicityAndOffset_valid:1;
    u8 resource_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 schedulingRequestResourceId;
   u32 schedulingRequestID;
   SchedulingRequestResourceConfig_PeriodicityAndOffset_t periodicityAndOffset;	/* OPTIONAL */
   u32 resource;	/* OPTIONAL */
}SchedulingRequestResourceConfig_t;

typedef struct
{
   u32 resource;
   u32 uplinkBWP;
}PUCCH_SRS_t;



typedef struct
{
#define	nr_PUCCH_SpatialRelationInfo_ReferenceSignal_ssb_Index_chosen	0
#define	nr_PUCCH_SpatialRelationInfo_ReferenceSignal_csi_RS_Index_chosen	1
#define	nr_PUCCH_SpatialRelationInfo_ReferenceSignal_srs_chosen	2
   s32 choice;
   union {
      u32 ssb_Index;
      u32 csi_RS_Index;
      PUCCH_SRS_t srs;
   } value;
}PUCCH_SpatialRelationInfo_ReferenceSignal_t;


typedef struct
{
    u8 servingCellId_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 pucch_SpatialRelationInfoId;
   u32 servingCellId;	/* OPTIONAL */
   PUCCH_SpatialRelationInfo_ReferenceSignal_t referenceSignal;
   u32 pucch_PathlossReferenceRS_Id;
   u32 p0_PUCCH_Id;
   s32 closedLoopIndex; /* enum  ClosedLoopIndex_i0 = 0,ClosedLoopIndex_i1 = 1*/
}PUCCH_SpatialRelationInfo_t;

typedef struct
{
   s32 choice;
   union {
      u32 ssb_Index;
      u32 csi_RS_Index;
   } value;
}PUCCH_PathlossReferenceRS_ReferenceSignal_t;



typedef struct
{
   u32 p0_PUCCH_Id;
   s32 p0_PUCCH_Value;
}P0_PUCCH_t;

typedef struct
{
   u32 pucch_PathlossReferenceRS_Id;
   PUCCH_PathlossReferenceRS_ReferenceSignal_t referenceSignal;
}PUCCH_PathlossReferenceRS_t;

typedef struct
{
   s32 choice;
   union {
      u32 ssb_Index_r16;
      u32 csi_RS_Index_r16;
   } value;
}ReferenceSignal_r16_t;


typedef struct
{
   u32 pucch_PathlossReferenceRS_Id_r16;
   ReferenceSignal_r16_t referenceSignal_r16;
}PUCCH_PathlossReferenceRS_r16_t;



typedef struct
{
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    PUCCH_PathlossReferenceRS_r16_t setup[60];
//   } value;
}PUCCH_PowerControl_PathlossReferenceRSs_v1610_t;

typedef struct  {
   s32 choice;
   union {
      u32 scs15;
      u32 scs30;
   } value;
}Interlace0_r16_t;

typedef struct  {
   u8 occ_Length_v1610_valid:1;
   u8 occ_Index_v1610_valid:1;
   u8 rsv:6;
   u8 padding[3];
   s32 occ_Length_v1610;	/* OPTIONAL enum Occ_Length_v1610_n2 = 0, Occ_Length_v1610_n4 = 1*/
   s32 occ_Index_v1610;	/* OPTIONAL enum Occ_Index_v1610_n0 = 0,
																   Occ_Index_v1610_n1 = 1,
																   Occ_Index_v1610_n2 = 2,
																   Occ_Index_v1610_n3 = 3 */
}Occ_v1610_t;


typedef struct  {
   s32 choice;
   union {
      u32 interlace1_v1610;
      Occ_v1610_t occ_v1610;
   } value;
}Format_v1610_t;



typedef struct
{
    u8 deltaF_PUCCH_f0_valid:1;
    u8 deltaF_PUCCH_f1_valid:1;
    u8 deltaF_PUCCH_f2_valid:1;
    u8 deltaF_PUCCH_f3_valid:1;
    u8 deltaF_PUCCH_f4_valid:1;
    u8 twoPUCCH_PC_AdjustmentStates_valid:1;
    u8 pathlossReferenceRSs_v1610_valid:1;
    u8 rsv:1;
    u8 padding[2];
    u8 num_of_p0_Set;
    u8 num_of_pathlossReferenceRSs;
   s32  deltaF_PUCCH_f0;	/* OPTIONAL */
   s32  deltaF_PUCCH_f1;	/* OPTIONAL */
   s32  deltaF_PUCCH_f2;	/* OPTIONAL */
   s32  deltaF_PUCCH_f3;	/* OPTIONAL */
   s32  deltaF_PUCCH_f4;	/* OPTIONAL */
   P0_PUCCH_t p0_Set[8];	/* OPTIONAL */
   PUCCH_PathlossReferenceRS_t pathlossReferenceRSs[4];	/* OPTIONAL */
   s32 twoPUCCH_PC_AdjustmentStates;	/* OPTIONAL enum TwoPUCCH_PC_AdjustmentStates_twoStates = 0*/
   PUCCH_PowerControl_PathlossReferenceRSs_v1610_t pathlossReferenceRSs_v1610;	/* OPTIONAL */
}PUCCH_PowerControl_t;

typedef struct  {
   u32 rb_SetIndex_r16;
   Interlace0_r16_t interlace0_r16;
}InterlaceAllocation_r16_t;

typedef struct  {
   u32 nrofPRBs_r17;
}Format_v1700_t;


typedef struct
{
    u8 interlaceAllocation_r16_valid:1;
    u8 format_v1610_valid:1;
    u8 format_v1700_valid:1;
    u8 pucch_RepetitionNrofSlots_r17_valid:1;
    u8 rsv:4;
    u8 padding[3];
   InterlaceAllocation_r16_t interlaceAllocation_r16;	/* OPTIONAL */
   Format_v1610_t format_v1610;	/* OPTIONAL */
   Format_v1700_t format_v1700;	/* OPTIONAL */
   s32 pucch_RepetitionNrofSlots_r17;	/* OPTIONAL enum  Pucch_RepetitionNrofSlots_r17_n1 = 0,
													   Pucch_RepetitionNrofSlots_r17_n2 = 1,
													   Pucch_RepetitionNrofSlots_r17_n4 = 2,
													   Pucch_RepetitionNrofSlots_r17_n8 = 3 */
}PUCCH_ResourceExt_v1610_t;

typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    int setup[8];
//   } value;
}PUCCH_Config_Dl_DataToUL_ACK_r16_t;

typedef struct  {
   s32 choice;
   union {
      s8 release;
      u8 setup[16];
   } value;
}PUCCH_Config_Ul_AccessConfigListDCI_1_1_r16_t;

typedef struct  {
   s8 choice;
   union {
      s32 normalCP_r16;  /*enum NormalCP_r16_n2 = 0, NormalCP_r16_n7 = 1*/
      s32 extendedCP_r16; /*enum ExtendedCP_r16_n2 = 0, ExtendedCP_r16_n6 = 1*/
   } value;
}SubslotLengthForPUCCH_r16_t;

typedef struct  {
//   s8 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[8];
//   } value;
}PUCCH_Config_Dl_DataToUL_ACK_DCI_1_2_r16_t;

typedef struct  {
    u8 pucch_SpatialRelationInfoId_v1610_valid:1;
    u8 pucch_PathlossReferenceRS_Id_v1610_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 pucch_SpatialRelationInfoId_v1610;	/* OPTIONAL */
   u32 pucch_PathlossReferenceRS_Id_v1610;	/* OPTIONAL */
}PUCCH_SpatialRelationInfoExt_r16;

typedef struct  {
   u32 pucch_ResourceGroupId_r16;
   u8 num_of_resourcePerGroupList_r16;
   u8 padding[3];
   u32 resourcePerGroupList_r16[128];
}PUCCH_ResourceGroup_r16_t;

typedef struct  {
    u8 maxPayloadSize_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 sps_PUCCH_AN_ResourceID_r16;
   u32 maxPayloadSize_r16;	/* OPTIONAL */
}SPS_PUCCH_AN_r16_t;



typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    SPS_PUCCH_AN_r16_t setup[4];
//   } value;
}PUCCH_Config_Sps_PUCCH_AN_List_r16_t;

typedef struct  {
    u8 phy_PriorityIndex_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   s32 phy_PriorityIndex_r16;	/* OPTIONAL enum Phy_PriorityIndex_r16_p0 = 0, Phy_PriorityIndex_r16_p1 = 1 */
}SchedulingRequestResourceConfigExt_v1610_t;

typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
      PUCCH_FormatConfig_t setup;
//   } value;
}Format0_r17_t;

typedef struct  {
    u8 maxCodeRateLP_r17_valid:1;
    u8 rsv:7;
    u8 padding[3];
   s32 maxCodeRateLP_r17;	/* OPTIONAL enum  PUCCH_MaxCodeRate_zeroDot08 = 0,
																   PUCCH_MaxCodeRate_zeroDot15 = 1,
																   PUCCH_MaxCodeRate_zeroDot25 = 2,
																   PUCCH_MaxCodeRate_zeroDot35 = 3,
																   PUCCH_MaxCodeRate_zeroDot45 = 4,
																   PUCCH_MaxCodeRate_zeroDot60 = 5,
																   PUCCH_MaxCodeRate_zeroDot80 = 6*/
}PUCCH_FormatConfigExt_r17_t;


typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
      PUCCH_FormatConfigExt_r17_t setup;
//   } value;
}Format2Ext_r17_t;

typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
      PUCCH_FormatConfigExt_r17_t setup;
//   } value;
}Format3Ext_r17_t;

typedef struct  {
//   s32 choice;
//   union {
//      s8  release;
      PUCCH_FormatConfigExt_r17_t setup;
//   } value;
}Format4Ext_r17_t;


typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[16];
//   } value;
}PUCCH_Config_Ul_AccessConfigListDCI_1_2_r17_t;

typedef struct  {
   u32 pucch_PowerControlSetInfoId_r17;
   u32 p0_PUCCH_Id_r17;
   s32 pucch_ClosedLoopIndex_r17; /*enum Pucch_ClosedLoopIndex_r17_i0 = 0,Pucch_ClosedLoopIndex_r17_i1 = 1*/
   u32 pucch_PathlossReferenceRS_Id_r17;
}PUCCH_PowerControlSetInfo_r17_t;

typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    s32 setup[8];
//   } value;
}PUCCH_Config_Dl_DataToUL_ACK_r17_t;



typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
      u32 setup[8];
//   } value;
}PUCCH_Config_Dl_DataToUL_ACK_DCI_1_2_r17_t;


typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[3];
//   } value;
}PUCCH_Config_Ul_AccessConfigListDCI_1_1_r17_t;


typedef struct  {
    u8 pucch_DMRS_Bundling_r17_valid:1;
    u8 pucch_TimeDomainWindowLength_r17_valid:1;
    u8 pucch_WindowRestart_r17_valid:1;
    u8 pucch_FrequencyHoppingInterval_r17_valid:1;
    u8 rsv:4;
    u8 padding[3];
   s32 pucch_DMRS_Bundling_r17;	/* OPTIONAL enum Pucch_DMRS_Bundling_r17_enabled = 0 */
   u32 pucch_TimeDomainWindowLength_r17;	/* OPTIONAL */
   s32 pucch_WindowRestart_r17;	/* OPTIONAL enum Pucch_WindowRestart_r17_enabled = 0*/
   s32 pucch_FrequencyHoppingInterval_r17;	/* OPTIONAL enum Pucch_FrequencyHoppingInterval_r17_s2 = 0,
																								   Pucch_FrequencyHoppingInterval_r17_s4 = 1,
																								   Pucch_FrequencyHoppingInterval_r17_s5 = 2,
																								   Pucch_FrequencyHoppingInterval_r17_s10 = 3 */
}DMRS_BundlingPUCCH_Config_r17_t;



typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
      DMRS_BundlingPUCCH_Config_r17_t setup;
//   } value;
}PUCCH_Config_Dmrs_BundlingPUCCH_Config_r17_t;

typedef struct  {
   s32 choice;
   union {
      u32 sl1280;
      u32 sl2560;
      u32 sl5120;
   } value;
}PeriodicityAndOffset_r17_t;

typedef struct  {
    u8 periodicityAndOffset_r17_valid:1;
    u8 rsv:7;
    u8 padding[3];
   PeriodicityAndOffset_r17_t periodicityAndOffset_r17;	/* OPTIONAL */
}SchedulingRequestResourceConfigExt_v1700_t;

typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[8];
//   } value;
}PUCCH_Config_Dl_DataToUL_ACK_v1700_t;

typedef struct  {
   s32 choice;
   union {
      s8 release;
      u32 setup[8];
   } value;
}PUCCH_Config_Dl_DataToUL_ACK_MulticastDCI_Format4_1_r17_t;


typedef struct  {
   s32 choice;
   union {
      s8 release;
      SPS_PUCCH_AN_r16_t setup[4];
   } value;
}Sps_PUCCH_AN_ListMulticast_r17_t;



typedef struct 
{
    u32 format1_valid:1;
    u32 format2_valid:1;
    u32 format3_valid:1;
    u32 format4_valid:1;
    u32 pucch_PowerControl_valid:1;
    u32 dl_DataToUL_ACK_r16_valid:1;
    u32 ul_AccessConfigListDCI_1_1_r16_valid:1;
    u32 subslotLengthForPUCCH_r16_valid:1;
    u32 dl_DataToUL_ACK_DCI_1_2_r16_valid:1;
    u32 numberOfBitsForPUCCH_ResourceIndicatorDCI_1_2_r16_valid:1;
    u32 dmrs_UplinkTransformPrecodingPUCCH_r16_valid:1;
    u32 sps_PUCCH_AN_List_r16_valid:1;
    u32 format0_r17_valid:1;
    u32 format2Ext_r17_valid:1;
    u32 format3Ext_r17_valid:1;
    u32 format4Ext_r17_valid:1;
    u32 ul_AccessConfigListDCI_1_2_r17_valid:1;
    u32 mappingPattern_r17_valid:1;
    u32 secondTPCFieldDCI_1_1_r17_valid;
    u32 secondTPCFieldDCI_1_2_r17_valid;
    u32 dl_DataToUL_ACK_r17_valid:1;
    u32 dl_DataToUL_ACK_DCI_1_2_r17_valid:1;
    u32 ul_AccessConfigListDCI_1_1_r17_valid:1;
    u32 dmrs_BundlingPUCCH_Config_r17_valid;  /* OPTIONAL */
    u32 dl_DataToUL_ACK_v1700_valid;  /* OPTIONAL */
    u32 dl_DataToUL_ACK_MulticastDCI_Format4_1_r17_valid;    /* OPTIONAL */
    u32 sps_PUCCH_AN_ListMulticast_r17_valid; /* OPTIONAL */
    u32 rsv:5;
    u8 num_of_resourceSetToReleaseList;
    u8 num_of_resourceSetToAddModList;
    u8 num_of_resourceToReleaseList;
    u8 num_of_resourceToAddModList;
    u8 num_of_schedulingRequestResourceToReleaseList;
    u8 num_of_schedulingRequestResourceToAddModList;
    u8 num_of_dl_DataToUL_ACK;
    u8 num_of_spatialRelationInfoToReleaseList;
    u8 num_of_spatialRelationInfoToAddModList;
    u8 num_of_resourceToAddModListExt_v1610;
    u8 num_of_multi_CSI_PUCCH_ResourceList;
    u8 num_of_spatialRelationInfoToAddModListSizeExt_v1610;
    u8 num_of_spatialRelationInfoToReleaseListSizeExt_v1610;
    u8 num_of_spatialRelationInfoToAddModListExt_v1610;
    u8 num_of_spatialRelationInfoToReleaseListExt_v1610;
    u8 num_of_resourceGroupToAddModList_r16;
    u8 num_of_resourceGroupToReleaseList_r16;
    u8 num_of_schedulingRequestResourceToAddModListExt_v1610;
    u8 num_of_powerControlSetInfoToReleaseList_r17;
    u8 num_of_powerControlSetInfoToAddModList_r17;
    u8 num_of_schedulingRequestResourceToAddModListExt_v1700;
    u8 padding[3];
   PUCCH_ResourceSet_t resourceSetToAddModList[4];	/* OPTIONAL */
   u32 resourceSetToReleaseList[4];	/* OPTIONAL */
   PUCCH_Resource_t resourceToAddModList[128];	/* OPTIONAL */
   u32 resourceToReleaseList[128];	/* OPTIONAL */
   Format1_t format1;	/* OPTIONAL */
   Format2_t format2;	/* OPTIONAL */
   Format3_t format3;	/* OPTIONAL */
   Format4_t format4;	/* OPTIONAL */
   SchedulingRequestResourceConfig_t schedulingRequestResourceToAddModList[8];	/* OPTIONAL */
   u32 schedulingRequestResourceToReleaseList[8];	/* OPTIONAL */
   u32 multi_CSI_PUCCH_ResourceList[2];	/* OPTIONAL */
   u32 dl_DataToUL_ACK[8];	/* OPTIONAL */
   PUCCH_SpatialRelationInfo_t spatialRelationInfoToAddModList[8];	/* OPTIONAL */
   u32 spatialRelationInfoToReleaseList[8];	/* OPTIONAL */
   PUCCH_PowerControl_t pucch_PowerControl;	/* OPTIONAL */
   PUCCH_ResourceExt_v1610_t resourceToAddModListExt_v1610[128];	/* OPTIONAL */
   PUCCH_Config_Dl_DataToUL_ACK_r16_t dl_DataToUL_ACK_r16;	/* OPTIONAL */
   PUCCH_Config_Ul_AccessConfigListDCI_1_1_r16_t ul_AccessConfigListDCI_1_1_r16;	/* OPTIONAL */
   SubslotLengthForPUCCH_r16_t subslotLengthForPUCCH_r16;	/* OPTIONAL */
   PUCCH_Config_Dl_DataToUL_ACK_DCI_1_2_r16_t dl_DataToUL_ACK_DCI_1_2_r16;	/* OPTIONAL */
   u32 numberOfBitsForPUCCH_ResourceIndicatorDCI_1_2_r16;	/* OPTIONAL */
   bool dmrs_UplinkTransformPrecodingPUCCH_r16;	/* */
   PUCCH_SpatialRelationInfo_t spatialRelationInfoToAddModListSizeExt_v1610[56];	/* OPTIONAL */
   u32 spatialRelationInfoToReleaseListSizeExt_v1610[56];	/* OPTIONAL */
   PUCCH_SpatialRelationInfoExt_r16 spatialRelationInfoToAddModListExt_v1610[64];	/* OPTIONAL */
   u32 spatialRelationInfoToReleaseListExt_v1610[64];	/* OPTIONAL */
   PUCCH_ResourceGroup_r16_t resourceGroupToAddModList_r16[4];	/* OPTIONAL */
   u32 resourceGroupToReleaseList_r16[4];	/* OPTIONAL */
   PUCCH_Config_Sps_PUCCH_AN_List_r16_t sps_PUCCH_AN_List_r16;	/* OPTIONAL */
   SchedulingRequestResourceConfigExt_v1610_t schedulingRequestResourceToAddModListExt_v1610[8];	/* OPTIONAL */
   Format0_r17_t format0_r17;	/* OPTIONAL */
   Format2Ext_r17_t	format2Ext_r17; /* OPTIONAL */
   Format3Ext_r17_t format3Ext_r17;	/* OPTIONAL */
   Format4Ext_r17_t format4Ext_r17;	/* OPTIONAL */
   PUCCH_Config_Ul_AccessConfigListDCI_1_2_r17_t ul_AccessConfigListDCI_1_2_r17;	/* OPTIONAL */
   s32  mappingPattern_r17;	/* OPTIONAL enum  MappingPattern_r17_cyclicMapping = 0, MappingPattern_r17_sequentialMapping = 1*/
   PUCCH_PowerControlSetInfo_r17_t powerControlSetInfoToAddModList_r17[8];	/* OPTIONAL */
   u32 powerControlSetInfoToReleaseList_r17[8];	/* OPTIONAL */
   s32 secondTPCFieldDCI_1_1_r17;	/* OPTIONAL enum  SecondTPCFieldDCI_1_1_r17_enabled = 0 */
   s32 secondTPCFieldDCI_1_2_r17;	/* OPTIONAL enum SecondTPCFieldDCI_1_2_r17_enabled = 0*/
   PUCCH_Config_Dl_DataToUL_ACK_r17_t dl_DataToUL_ACK_r17;	/* OPTIONAL */
   PUCCH_Config_Dl_DataToUL_ACK_DCI_1_2_r17_t dl_DataToUL_ACK_DCI_1_2_r17;	/* OPTIONAL */
   PUCCH_Config_Ul_AccessConfigListDCI_1_1_r17_t ul_AccessConfigListDCI_1_1_r17;	/* OPTIONAL */
   SchedulingRequestResourceConfigExt_v1700_t schedulingRequestResourceToAddModListExt_v1700[8];	/* OPTIONAL */
   PUCCH_Config_Dmrs_BundlingPUCCH_Config_r17_t dmrs_BundlingPUCCH_Config_r17;	/* OPTIONAL */
   PUCCH_Config_Dl_DataToUL_ACK_v1700_t dl_DataToUL_ACK_v1700;	/* OPTIONAL */
   PUCCH_Config_Dl_DataToUL_ACK_MulticastDCI_Format4_1_r17_t dl_DataToUL_ACK_MulticastDCI_Format4_1_r17;	/* OPTIONAL */
   Sps_PUCCH_AN_ListMulticast_r17_t sps_PUCCH_AN_ListMulticast_r17;	/* OPTIONAL */
}PUCCH_Config_t;

typedef struct{
	u32 num_of_PUCCH_Config_list;//0..2
	PUCCH_Config_t pucch_config_list[2];
}PUCCH_Config_list_t;

typedef struct{
//   s32 choice;
//#define	BWP_UplinkDedicated_Pucch_Config_release_chosen	0
//#define	BWP_UplinkDedicated_Pucch_Config_setup_chosen	1

//   union {
//      s8 release;
      PUCCH_Config_t setup;
//   } value;
}BWP_UplinkDedicated_Pucch_Config_t;


typedef struct  {
#define	Rach_ConfigCommonIAB_r16_release_chosen	0
#define	Rach_ConfigCommonIAB_r16_setup_chosen	1

   int choice;
   union {
      u8 release;
      RACH_ConfigCommon_t setup;
   } value;
}Rach_ConfigCommonIAB_r16_t;


typedef struct  {

   u8 msgA_PRACH_ConfigurationIndex_r16_valid:1;
   u8 msgA_RO_FDM_r16_valid:1;
   u8 msgA_RO_FrequencyStart_r16_valid:1;
   u8 msgA_ZeroCorrelationZoneConfig_r16_valid:1;
   
   u8 msgA_PreamblePowerRampingStep_r16_valid:1;
   u8 msgA_PreambleReceivedTargetPower_r16_valid:1;
   u8 msgB_ResponseWindow_r16_valid:1;
   u8 preambleTransMax_r16_valid:1;
   
   u8 msgB_ResponseWindow_v1700_valid:1;
   u8  :7;

   u32 msgA_PRACH_ConfigurationIndex_r16;	/* OPTIONAL */
   s32 msgA_RO_FDM_r16;	/* OPTIONAL enum  MsgA_RO_FDM_r16_one = 0,
										   MsgA_RO_FDM_r16_two = 1,
										   MsgA_RO_FDM_r16_four = 2,
										   MsgA_RO_FDM_r16_eight = 3*/
   u32 msgA_RO_FrequencyStart_r16;	/* OPTIONAL */
   u32 msgA_ZeroCorrelationZoneConfig_r16;	/* OPTIONAL */
   s32 msgA_PreamblePowerRampingStep_r16;	/* OPTIONAL enum MsgA_PreamblePowerRampingStep_r16_dB0 = 0,
															   MsgA_PreamblePowerRampingStep_r16_dB2 = 1,
															   MsgA_PreamblePowerRampingStep_r16_dB4 = 2,
															   MsgA_PreamblePowerRampingStep_r16_dB6 = 3*/
   s32 msgA_PreambleReceivedTargetPower_r16;	/* OPTIONAL */
   s32 msgB_ResponseWindow_r16;	/* OPTIONAL enum  MsgB_ResponseWindow_r16_sl1 = 0,
												   MsgB_ResponseWindow_r16_sl2 = 1,
												   MsgB_ResponseWindow_r16_sl4 = 2,
												   MsgB_ResponseWindow_r16_sl8 = 3,
												   MsgB_ResponseWindow_r16_sl10 = 4,
												   MsgB_ResponseWindow_r16_sl20 = 5,
												   MsgB_ResponseWindow_r16_sl40 = 6,
												   MsgB_ResponseWindow_r16_sl80 = 7,
												   MsgB_ResponseWindow_r16_sl160 = 8,
												   MsgB_ResponseWindow_r16_sl320 = 9*/
   s32 preambleTransMax_r16;	/* OPTIONAL enum   PreambleTransMax_r16_n3 = 0,
												   PreambleTransMax_r16_n4 = 1,
												   PreambleTransMax_r16_n5 = 2,
												   PreambleTransMax_r16_n6 = 3,
												   PreambleTransMax_r16_n7 = 4,
												   PreambleTransMax_r16_n8 = 5,
												   PreambleTransMax_r16_n10 = 6,
												   PreambleTransMax_r16_n20 = 7,
												   PreambleTransMax_r16_n50 = 8,
												   PreambleTransMax_r16_n100 = 9,
												   PreambleTransMax_r16_n200 = 10 */
   s32 msgB_ResponseWindow_v1700;	/* OPTIONAL enum MsgB_ResponseWindow_v1700_sl240 = 0,
													   MsgB_ResponseWindow_v1700_sl640 = 1,
													   MsgB_ResponseWindow_v1700_sl960 = 2,
													   MsgB_ResponseWindow_v1700_sl1280 = 3,
													   MsgB_ResponseWindow_v1700_sl1920 = 4,
													   MsgB_ResponseWindow_v1700_sl2560 = 5 */
}RACH_ConfigGenericTwoStepRA_r16_t;



typedef struct  {
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_oneEighth_chosen	0
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_oneFourth_chosen	1
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_oneHalf_chosen	2
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_one_chosen	3
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_two_chosen	4
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_four_chosen	5
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_eight_chosen	6
#define	MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_sixteen_chosen	7

   u8 choice;
   union {
      u8 oneEighth;
      u8 oneFourth;
      u8 oneHalf;
      u8 one;
      u8 two;
      u8 four;
      u8 eight;
      u8 sixteen;
   } value;
}MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_t;

typedef struct  {
#define	MsgA_PRACH_RootSequenceIndex_r16_l839_chosen	0
#define	MsgA_PRACH_RootSequenceIndex_r16_l139_chosen	1
#define	MsgA_PRACH_RootSequenceIndex_r16_l571_chosen	2
#define	MsgA_PRACH_RootSequenceIndex_r16_l1151_chosen	3

   int choice;
   union {
      unsigned int l839;
      unsigned int l139;
      unsigned int l571;
      unsigned int l1151;
   } value;
}MsgA_PRACH_RootSequenceIndex_r16_t;


typedef struct  {
   u8 ra_MsgA_SizeGroupA;
   u8 messagePowerOffsetGroupB;
   u8 numberOfRA_PreamblesGroupA;
   u8 padding;
}GroupB_ConfiguredTwoStepRA_r16_t;

typedef struct  {
   RA_Prioritization_t ra_Prioritization_r16;
   u8 ra_PrioritizationForAI_r16;
}Ra_PrioritizationForAccessIdentityTwoStep_r16_t;


typedef struct {

   RACH_ConfigGenericTwoStepRA_r16_t rach_ConfigGenericTwoStepRA_r16;
   u16 msgA_TotalNumberOfRA_Preambles_r16;	/* OPTIONAL */
   MsgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16_t msgA_SSB_PerRACH_OccasionAndCB_PreamblesPerSSB_r16;
   u16 msgA_CB_PreamblesPerSSB_PerSharedRO_r16;	/* OPTIONAL */
   u16 msgA_SSB_SharedRO_MaskIndex_r16;	/* OPTIONAL */
   GroupB_ConfiguredTwoStepRA_r16_t groupB_ConfiguredTwoStepRA_r16;
   MsgA_PRACH_RootSequenceIndex_r16_t msgA_PRACH_RootSequenceIndex_r16;	/* OPTIONAL */
   u8 msgA_TransMax_r16;	/* OPTIONAL */
   u16 msgA_RSRP_Threshold_r16;	/* OPTIONAL */
   u16 msgA_RSRP_ThresholdSSB_r16;	/* OPTIONAL */
   u8 msgA_SubcarrierSpacing_r16;
   u8 msgA_RestrictedSetConfig_r16;	/* OPTIONAL */
   Ra_PrioritizationForAccessIdentityTwoStep_r16_t ra_PrioritizationForAccessIdentityTwoStep_r16;	/* OPTIONAL */
   u8 ra_ContentionResolutionTimer_r16;	/* OPTIONAL */
   RA_PrioritizationForSlicing_r17_t ra_PrioritizationForSlicingTwoStep_r17;
   u16 featureCombinationPreamblesList_num;
   FeatureCombinationPreambles_r17_t featureCombinationPreamblesList_r17[256];
}RACH_ConfigCommonTwoStepRA_r16_t;


typedef struct  {
   RACH_ConfigCommonTwoStepRA_r16_t rach_ConfigCommonTwoStepRA_r16;
   MsgA_PUSCH_Config_r16_t msgA_PUSCH_Config_r16;	/* OPTIONAL */
}MsgA_ConfigCommon_r16_t;



typedef struct  {
#define	BWP_UplinkCommon_MsgA_ConfigCommon_r16_release_chosen	0
#define	BWP_UplinkCommon_MsgA_ConfigCommon_r16_setup_chosen	1
   u8 choice;
   union {
      char release;
      MsgA_ConfigCommon_r16_t setup;
   } value;
}BWP_UplinkCommon_MsgA_ConfigCommon_r16_t;


typedef struct  {
    RACH_ConfigCommon_t rach_ConfigCommon_r17;
   MsgA_ConfigCommon_r16_t msgA_ConfigCommon_r17;	/* OPTIONAL */
}AdditionalRACH_Config_r17_t;


typedef struct  {

#define	BWP_UplinkCommon_AdditionalRACH_ConfigList_r17_release_chosen	0
#define	BWP_UplinkCommon_AdditionalRACH_ConfigList_r17_setup_chosen	1
   u8 choice;
   u8 release;
   u16 setup_num;
   AdditionalRACH_Config_r17_t setup[256];
}BWP_UplinkCommon_AdditionalRACH_ConfigList_r17_t;


typedef struct  {
    
   BWP_t genericParameters;
   BWP_UplinkCommon_Rach_ConfigCommon_t rach_ConfigCommon;	/* OPTIONAL */
   BWP_UplinkCommon_Pusch_ConfigCommon_t pusch_ConfigCommon;	/* OPTIONAL */
   BWP_UplinkCommon_Pucch_ConfigCommon_t pucch_ConfigCommon;
   Rach_ConfigCommonIAB_r16_t rach_ConfigCommonIAB_r16;
   u8 useInterlacePUCCH_PUSCH_r16;	/* OPTIONAL */
   BWP_UplinkCommon_MsgA_ConfigCommon_r16_t msgA_ConfigCommon_r16;
   bool enableRA_PrioritizationForSlicing_r17;	/* OPTIONAL */




   BWP_UplinkCommon_AdditionalRACH_ConfigList_r17_t additionalRACH_ConfigList_r17;	/* OPTIONAL */
   unsigned int* rsrp_ThresholdMsg3_r17;	/* OPTIONAL */
   u32 numberOfMsg3_RepetitionsList_r17[4];	/* OPTIONAL enum NumberOfMsg3_Repetitions_r17_n1 = 0,
															   NumberOfMsg3_Repetitions_r17_n2 = 1,
															   NumberOfMsg3_Repetitions_r17_n3 = 2,
															   NumberOfMsg3_Repetitions_r17_n4 = 3,
															   NumberOfMsg3_Repetitions_r17_n7 = 4,
															   NumberOfMsg3_Repetitions_r17_n8 = 5,
															   NumberOfMsg3_Repetitions_r17_n12 = 6,
															   NumberOfMsg3_Repetitions_r17_n16 = 7 */
   u32 mcs_Msg3_Repetitions_r17[8];	/* OPTIONAL */
} BWP_UplinkCommon_t;


typedef struct  {
   FrequencyInfoUL_t frequencyInfoUL;
   wnrrc_bwp_ul_common_t initialUplinkBWP;
   u8 dummy;
} UplinkConfigCommon_t;

typedef struct  {
#define	ServingCellConfigCommon_ChannelAccessMode_r16_dynamic_chosen	0
#define	ServingCellConfigCommon_ChannelAccessMode_r16_semiStatic_chosen	1
   u8 type_cfg;
   u8 value;
   u8 padding[2];
}wnrrc_channel_access_mode_r16_t;

typedef struct  {
bool highSpeedMeasCA_Scell_r17;
bool highSpeedMeasInterFreq_r17;
bool highSpeedDemodCA_Scell_r17;
u8 padding;
}HighSpeedConfig_v1700_t;

typedef struct {
    u8 redCapPriority_r17_valid:1;
    u8 slicingPriority_r17_valid:1;
    u8 msg3_Repetitions_Priority_valid:1;
    u8 sdt_Priority_valid:1;
    u8                    :4;
    u8 redCapPriority_r17;   /* OPTIONAL */
    u8 slicingPriority_r17;  /* OPTIONAL */
    u8 msg3_Repetitions_Priority_r17;    /* OPTIONAL */
    u8 sdt_Priority_r17; /* OPTIONAL */
}FeaturePriorities_r17_t;


typedef struct
{
    u8 phys_cellId_valid:1;
    u8 downlink_config_common_valid:1;
    u8 uplink_config_common_valid:1;
    u8 supplementary_uplink_config_valid:1;
    
    u8 n_timing_advance_offset_valid:1;
    u8 ssb_positions_inburst_valid:1;
    u8 ssb_periodicity_valid:1;
    u8 dmrs_typeA_position_valid:1;
    
    u8 SubcarrierSpacing_valid:1;
    u8 tdd_ul_dl_cfg_commom_valid:1;
    u8 ss_pbch_block_pwr_valid:1;
    u8 channel_access_mode_r16_valid:1;
    
    u8 dsc_burst_win_len_r16_valid:1;
    u8 ssb_position_QCL_r16_valid:1;
    u8 high_speed_r16_valid:1;
    u8 discovery_burst_window_length_valid:1;
    
    u8 high_speed_config_v1700_valid:1;
    u8 ssb_position_QCL_r17_valid:1;
    u8 high_speed_fr2_r17_valid:1;
    u8 ntn_cfg_valid:1;
    
    u8 feature_priorities_r17_valid:1;
    u8  :3;

    u16 phys_cellId;
    downlink_config_common_t downlink_config_common;
    UplinkConfigCommon_t   *uplink_config_common;
    UplinkConfigCommon_t   *supplementary_uplink_config;
    nr_ta_offset_e n_timing_advance_offset;
    ssb_positions_inburst_t ssb_positions_inburst;
    ssb_periodicity_serving_cell_e ssb_periodicity;
#define POS2 0
#define POS3 1
    u8 dmrs_typeA_position;
    u8 rate_match_pattern_to_add_mod_list_num;
    rate_match_pattern_t rate_match_pattern_to_add_mod_list[MAX_NR_OF_RATE_MATCH_PATTERNS];
    u8 rate_match_pattern_to_release_list_num;
    u8 rate_match_pattern_to_release_list[MAX_NR_OF_RATE_MATCH_PATTERNS];
    wnrrc_scs_e  SubcarrierSpacing;
    wnrrc_td_ul_dl_cfg_common_t tdd_ul_dl_cfg_commom;
    s8 ss_pbch_block_pwr;/*-60...50*/
    wnrrc_channel_access_mode_r16_t channel_access_mode_r16;/*enumerate refer to wnrrc_channel_access_mode_r16_e*/
    u8 dsc_burst_win_len_r16;/*enumerate refer to wnrrc_discover_burst_win_len_r16_e*/
    u8 ssb_position_QCL_r16;/*ENUMERATED {n1,n2,n4,n8}*/
    wnrrc_high_speed_cfg_r16_t high_speed_r16;
    /******************************R17*****************************/
    HighSpeedConfig_v1700_t high_speed_config_v1700;
    bool channel_access_mode2_r17;/*TRUE: enable, FALSE:disable*/
    u8 dsc_burst_win_len_v1700;/*enumerate refer to wnrrc_discover_burst_win_len_v1700_e*/
    discovery_burst_window_length_r17_e discovery_burst_window_length;
    u8 ssb_position_QCL_r17;/*ENUMERATED {n32,n64}*/
    wnrrc_high_speed_cfg_fr2_r17_t     high_speed_fr2_r17;
    //uplinkConfigCommon_v1700 /*RedCap*/
    wnrrc_ntn_cfg_r17_t        ntn_cfg;
    FeaturePriorities_r17_t feature_priorities_r17;
    bool ra_channel_access_r17;
}serving_cell_config_common_t;


typedef struct  {
    u8 timeDensityTransformPrecoding_valid:1;
    u8 rsv:7;
    u8 num_of_sampleDensity;
    u8 padding[2];
   u32 sampleDensity[5];
   s32 timeDensityTransformPrecoding;	/* OPTIONAL enum TimeDensityTransformPrecoding_d2 = 0 */
}TransformPrecoderEnabled_t;



typedef struct  {
    u8 frequencyDensity_valid:1;
    u8 timeDensity_valid:1;
    u8 resourceElementOffset_valid:1;
    u8 rsv:5;
    u8 num_of_frequencyDensity;
    u8 num_of_timeDensity;
   u32 frequencyDensity[2];	/* OPTIONAL */
   u32 timeDensity[3];	/* OPTIONAL */
   s32 maxNrofPorts; /*enum MaxNrofPorts_n1 = 0, MaxNrofPorts_n2 = 1*/
   s32 resourceElementOffset;	/* OPTIONAL enum TransformPrecoderDisabled_ResourceElementOffset_offset01 = 0,
																							   TransformPrecoderDisabled_ResourceElementOffset_offset10 = 1,
																							   TransformPrecoderDisabled_ResourceElementOffset_offset11 = 2 */
   s32 ptrs_Power;  /*enum Ptrs_Power_p00 = 0,
									   Ptrs_Power_p01 = 1,
									   Ptrs_Power_p10 = 2,
									   Ptrs_Power_p11 = 3*/
}TransformPrecoderDisabled_t;


typedef struct  {
    u8 transformPrecoderDisabled_valid:1;
    u8 transformPrecoderEnabled_valid:1;
    u8 rsv:6;
    u8 padding[3];
   TransformPrecoderDisabled_t transformPrecoderDisabled;	/* OPTIONAL */
   TransformPrecoderEnabled_t transformPrecoderEnabled;	/* OPTIONAL */
}PTRS_UplinkConfig_t;



typedef struct  {
//   s32 choice;
//#define	DMRS_UplinkConfig_PhaseTrackingRS_release_chosen	0
//#define	DMRS_UplinkConfig_PhaseTrackingRS_setup_chosen	1

//   union {
//      s8 release;
      PTRS_UplinkConfig_t setup;
//   } value;
}DMRS_UplinkConfig_PhaseTrackingRS_t;

typedef struct  {
    u8 scramblingID0_valid:1;
    u8 scramblingID1_valid:1;
    u8 dmrs_Uplink_r16_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u32 scramblingID0;	/* OPTIONAL */
   u32 scramblingID1;	/* OPTIONAL */
   s32 dmrs_Uplink_r16;	/* OPTIONAL enum Dmrs_Uplink_r16_enabled = 0*/
}TransformPrecodingDisabled_t;

typedef struct  {
    u8 pi2BPSK_ScramblingID0_valid:1;
    u8 pi2BPSK_ScramblingID1_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 pi2BPSK_ScramblingID0;	/* OPTIONAL */
   u32 pi2BPSK_ScramblingID1;	/* OPTIONAL */
}DMRS_UplinkTransformPrecoding_r16_t;


typedef struct  {
//   s32 choice;
//#define	TransformPrecodingEnabled_Dmrs_UplinkTransformPrecoding_r16_release_chosen	0
//#define	TransformPrecodingEnabled_Dmrs_UplinkTransformPrecoding_r16_setup_chosen	1

//   union {
//      s8 release;
      DMRS_UplinkTransformPrecoding_r16_t setup;
//   } value;
}TransformPrecodingEnabled_Dmrs_UplinkTransformPrecoding_r16_t;


typedef struct  {
    u8 nPUSCH_Identity_valid:1;
    u8 sequenceGroupHopping_valid:1;
    u8 sequenceHopping_valid:1;
    u8 dmrs_UplinkTransformPrecoding_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 nPUSCH_Identity;	/* OPTIONAL */
   s32 sequenceGroupHopping;	/* OPTIONAL enum SequenceGroupHopping_disabled = 0 */
   s32 sequenceHopping;	/* OPTIONAL enum SequenceHopping_enabled = 0*/
   TransformPrecodingEnabled_Dmrs_UplinkTransformPrecoding_r16_t dmrs_UplinkTransformPrecoding_r16;	/* OPTIONAL */
}TransformPrecodingEnabled_t;



typedef struct  {
    u8 dmrs_Type_valid:1;
    u8 dmrs_AdditionalPosition_valid:1;
    u8 phaseTrackingRS_valid:1;
    u8 maxLength_valid:1;
    u8 transformPrecodingDisabled_valid:1;
    u8 transformPrecodingEnabled_valid:1;
    u8 rsv:2;
    u8 padding[3];
   s32 dmrs_Type;	/* OPTIONAL enum DMRS_UplinkConfig_Dmrs_Type_type2 = 0*/
   s32 dmrs_AdditionalPosition;	/* OPTIONAL enum DMRS_UplinkConfig_Dmrs_AdditionalPosition_pos0 = 0,
																						   DMRS_UplinkConfig_Dmrs_AdditionalPosition_pos1 = 1,
																						   DMRS_UplinkConfig_Dmrs_AdditionalPosition_pos3 = 2 */
   DMRS_UplinkConfig_PhaseTrackingRS_t phaseTrackingRS;	/* OPTIONAL */
   s32 maxLength;	/* OPTIONAL enum DMRS_UplinkConfig_MaxLength_len2 = 0*/
   TransformPrecodingDisabled_t transformPrecodingDisabled;	/* OPTIONAL */
   TransformPrecodingEnabled_t transformPrecodingEnabled;	/* OPTIONAL */
}DMRS_UplinkConfig_t;





typedef struct  {
//   s32 choice;
//#define	Dmrs_UplinkForPUSCH_MappingTypeA_release_chosen	0
//#define	Dmrs_UplinkForPUSCH_MappingTypeA_setup_chosen	1

//   union {
//      s8 release;
      DMRS_UplinkConfig_t setup;
//   } value;
}Dmrs_UplinkForPUSCH_MappingTypeA_t;


typedef struct  {
//   s32 choice;
//#define	Dmrs_UplinkForPUSCH_MappingTypeB_release_chosen	0
//#define	Dmrs_UplinkForPUSCH_MappingTypeB_setup_chosen	1

//   union {
//      s8 release;
      DMRS_UplinkConfig_t setup;
//   } value;
}Dmrs_UplinkForPUSCH_MappingTypeB_t;

typedef struct  {
    u8 p0_valid:1;
    u8 alpha_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 p0_PUSCH_AlphaSetId;
   s32 p0;	/* OPTIONAL */
   s32 alpha;	/* OPTIONAL enum Alpha_alpha0 = 0,
										   Alpha_alpha04 = 1,
										   Alpha_alpha05 = 2,
										   Alpha_alpha06 = 3,
										   Alpha_alpha07 = 4,
										   Alpha_alpha08 = 5,
										   Alpha_alpha09 = 6,
										   Alpha_alpha1 = 7 */
}P0_PUSCH_AlphaSet_t;

typedef struct  {
   s32 choice;
#define	PUSCH_PathlossReferenceRS_ReferenceSignal_ssb_Index_chosen	0
#define	PUSCH_PathlossReferenceRS_ReferenceSignal_csi_RS_Index_chosen	1

   union {
      u32 ssb_Index;
      u32 csi_RS_Index;
   } value;
}PUSCH_PathlossReferenceRS_ReferenceSignal_t;



typedef struct {
   u32 pusch_PathlossReferenceRS_Id;
   PUSCH_PathlossReferenceRS_ReferenceSignal_t referenceSignal;
}PUSCH_PathlossReferenceRS_t;


typedef struct  {
   u32 sri_PUSCH_PowerControlId;
   u32 sri_PUSCH_PathlossReferenceRS_Id;
   u32 sri_P0_PUSCH_AlphaSetId;
   u32 sri_PUSCH_ClosedLoopIndex; /*enum Sri_PUSCH_ClosedLoopIndex_i0 = 0, Sri_PUSCH_ClosedLoopIndex_i1 = 1*/
}SRI_PUSCH_PowerControl_t;




typedef struct  {
    u16 tpc_Accumulation_valid:1;
    u16 msg3_Alpha_valid:1;
    u16 p0_NominalWithoutGrant_valid:1;
    u16 p0_AlphaSets_valid:1;
    u16 twoPUSCH_PC_AdjustmentStates_valid:1;
    u16 deltaMCS_valid:1;
    u16 rsv:11;
    u8 num_of_p0_AlphaSets;
    u8 num_of_pathlossReferenceRSToReleaseList;
    u8 num_of_pathlossReferenceRSToAddModList;
    u8 num_of_sri_PUSCH_MappingToAddModList;
    u8 num_of_sri_PUSCH_MappingToReleaseList;
    u8 padding;
   s32 tpc_Accumulation;	/* OPTIONAL enum Tpc_Accumulation_disabled = 0 */
   s32 msg3_Alpha;	/* OPTIONAL enum Alpha_alpha0 = 0,
										   Alpha_alpha04 = 1,
										   Alpha_alpha05 = 2,
										   Alpha_alpha06 = 3,
										   Alpha_alpha07 = 4,
										   Alpha_alpha08 = 5,
										   Alpha_alpha09 = 6,
										   Alpha_alpha1 = 7*/
   s32 p0_NominalWithoutGrant;	/* OPTIONAL */
   P0_PUSCH_AlphaSet_t p0_AlphaSets[30];	/* OPTIONAL */
   PUSCH_PathlossReferenceRS_t pathlossReferenceRSToAddModList[4];	/* OPTIONAL */
   u32 pathlossReferenceRSToReleaseList[4];	/* OPTIONAL */
   s32 twoPUSCH_PC_AdjustmentStates;	/* OPTIONAL enum  TwoPUSCH_PC_AdjustmentStates_twoStates = 0 */
   s32 deltaMCS;	/* OPTIONAL enum  DeltaMCS_enabled = 0*/
   SRI_PUSCH_PowerControl_t sri_PUSCH_MappingToAddModList[16];	/* OPTIONAL */
   u32 sri_PUSCH_MappingToReleaseList[16];	/* OPTIONAL */
}PUSCH_PowerControl_t;

typedef struct  {
   u32 num_of_PUSCH_TimeDomainResourceAllocation_list;//0..16
   PUSCH_TimeDomainResourceAllocation_t PUSCH_TimeDomainResourceAllocation_list[16];
}PUSCH_TimeDomainResourceAllocation_list_t;

typedef struct {
//   s32 choice;
//#define	Pusch_TimeDomainAllocationList_release_chosen	0
//#define	Pusch_TimeDomainAllocationList_setup_chosen	1

//   union {
//      s8 release;
      u32 num_of_PUSCH_TimeDomainResourceAllocation_list;//0..16
      PUSCH_TimeDomainResourceAllocation_t setup[16];
//   } value;
}Pusch_TimeDomainAllocationList_t;

typedef struct  {
    u8 betaOffsetACK_Index1_valid:1;
    u8 betaOffsetACK_Index2_valid:1;
    u8 betaOffsetACK_Index3_valid:1;
    u8 betaOffsetCSI_Part1_Index1_valid:1;
    u8 betaOffsetCSI_Part1_Index2_valid:1;
    u8 betaOffsetCSI_Part2_Index1_valid:1;
    u8 betaOffsetCSI_Part2_Index2_valid:1;
    u8 rsv:1;
    u8 padding[3];
   u32 betaOffsetACK_Index1;	/* OPTIONAL */
   u32 betaOffsetACK_Index2;	/* OPTIONAL */
   u32 betaOffsetACK_Index3;	/* OPTIONAL */
   u32 betaOffsetCSI_Part1_Index1;	/* OPTIONAL */
   u32 betaOffsetCSI_Part1_Index2;	/* OPTIONAL */
   u32 betaOffsetCSI_Part2_Index1;	/* OPTIONAL */
   u32 betaOffsetCSI_Part2_Index2;	/* OPTIONAL */
}BetaOffsets_t;



typedef struct  {
   s32 choice;
#define	UCI_OnPUSCH_BetaOffsets_dynamic_chosen	0
#define	UCI_OnPUSCH_BetaOffsets_semiStatic_chosen	1
    u8 num_of_dynamic;
    u8 padding[3];
   union {
      BetaOffsets_t dynamic[4];
      BetaOffsets_t semiStatic;
   } value;
}UCI_OnPUSCH_BetaOffsets_t;




typedef struct  {
    u8 betaOffsets_valid:1;
    u8 rsv:7;
    u8 padding[3];
   UCI_OnPUSCH_BetaOffsets_t betaOffsets;	/* OPTIONAL */
   s32 scaling; /*enum Scaling_f0p5 = 0,
						   Scaling_f0p65 = 1,
						   Scaling_f0p8 = 2,
						   Scaling_f1 = 3*/
}UCI_OnPUSCH_t;


typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_Uci_OnPUSCH_release_chosen	0
//#define	PUSCH_Config_Uci_OnPUSCH_setup_chosen	1

//   union {
//      s8 release;
      UCI_OnPUSCH_t setup;
//   } value;
}PUSCH_Config_Uci_OnPUSCH_t;


typedef struct  {
//   s32 choice;
//#define	MinimumSchedulingOffsetK2_r16_release_chosen	0
//#define	MinimumSchedulingOffsetK2_r16_setup_chosen	1

//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[2];
//   } value;
}MinimumSchedulingOffsetK2_r16_t;

typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_Ul_AccessConfigListDCI_0_1_r16_release_chosen	0
//#define	PUSCH_Config_Ul_AccessConfigListDCI_0_1_r16_setup_chosen	1

//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[64];
//   } value;
}PUSCH_Config_Ul_AccessConfigListDCI_0_1_r16_t;

typedef struct  {
//   s32 choice;
//#define	Dmrs_UplinkForPUSCH_MappingTypeA_DCI_0_2_r16_release_chosen	0
//#define	Dmrs_UplinkForPUSCH_MappingTypeA_DCI_0_2_r16_setup_chosen	1

//   union {
//      s8 release;
      DMRS_UplinkConfig_t setup;
//   } value;
}Dmrs_UplinkForPUSCH_MappingTypeA_DCI_0_2_r16_t;

typedef struct  {
//   s32 choice;
//#define	Dmrs_UplinkForPUSCH_MappingTypeB_DCI_0_2_r16_release_chosen	0
//#define	Dmrs_UplinkForPUSCH_MappingTypeB_DCI_0_2_r16_setup_chosen	1

//   union {
//      s8 release;
      DMRS_UplinkConfig_t setup;
//   } value;
}Dmrs_UplinkForPUSCH_MappingTypeB_DCI_0_2_r16_t;

typedef struct  {
   s32 choice;
#define	FrequencyHoppingDCI_0_2_r16_pusch_RepTypeA_chosen	0
#define	FrequencyHoppingDCI_0_2_r16_pusch_RepTypeB_chosen	1

   union {
      s32 pusch_RepTypeA;  /*enum  Pusch_RepTypeA_intraSlot = 0, Pusch_RepTypeA_interSlot = 1*/
      s32 pusch_RepTypeB; /*enum Pusch_RepTypeB_interRepetition = 0, Pusch_RepTypeB_interSlot = 1*/
   } value;
}FrequencyHoppingDCI_0_2_r16_t;

typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_FrequencyHoppingOffsetListsDCI_0_2_r16_release_chosen	0
//#define	PUSCH_Config_FrequencyHoppingOffsetListsDCI_0_2_r16_setup_chosen	1

//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[4];
//   } value;
}PUSCH_Config_FrequencyHoppingOffsetListsDCI_0_2_r16_t;


typedef struct  {
   s32 choice;
#define	DynamicDCI_0_2_r16_oneBit_r16_chosen	0
#define	DynamicDCI_0_2_r16_twoBits_r16_chosen	1
    u8 num_of_betaOffset;
    u8 padding[3];
   union {
      BetaOffsets_t oneBit_r16[2];
      BetaOffsets_t twoBits_r16[4];
   } value;
}DynamicDCI_0_2_r16_t;

typedef struct  {
   s32 choice;
#define	PUSCH_Config_Uci_OnPUSCH_ListDCI_0_2_r16_release_chosen	0
#define	PUSCH_Config_Uci_OnPUSCH_ListDCI_0_2_r16_setup_chosen	1

   union {
      DynamicDCI_0_2_r16_t dynamicDCI_0_2_r16;
      BetaOffsets_t semiStaticDCI_0_2_r16;
   } value;
}BetaOffsetsDCI_0_2_r16_t;



typedef struct  {
    u8 betaOffsetsDCI_0_2_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   BetaOffsetsDCI_0_2_r16_t betaOffsetsDCI_0_2_r16;	/* OPTIONAL */
   s32 scalingDCI_0_2_r16; /*enum ScalingDCI_0_2_r16_f0p5 = 0,
								   ScalingDCI_0_2_r16_f0p65 = 1,
								   ScalingDCI_0_2_r16_f0p8 = 2,
								   ScalingDCI_0_2_r16_f1 = 3*/
}UCI_OnPUSCH_DCI_0_2_r16_t;


typedef struct  {
   u32 num_of_UCI_OnPUSCH_DCI_0_2_r16_list;	//1..2
   UCI_OnPUSCH_DCI_0_2_r16_t UCI_OnPUSCH_DCI_0_2_r16_list[2];
}UCI_OnPUSCH_DCI_0_2_r16_list_t;




typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_Uci_OnPUSCH_ListDCI_0_2_r16_release_chosen	0
//#define	PUSCH_Config_Uci_OnPUSCH_ListDCI_0_2_r16_setup_chosen	1

 //  union {
 //     s8 release;
      UCI_OnPUSCH_DCI_0_2_r16_list_t setup;
//   } value;
}PUSCH_Config_Uci_OnPUSCH_ListDCI_0_2_r16_t;

typedef struct  {
    u8 mappingType_r16_valid:1;
    u8 startSymbolAndLength_r16_valid:1;
    u8 startSymbol_r16_valid:1;
    u8 length_r16_valid:1;
    u8 numberOfRepetitions_r16_valid:1;
    u8 numberOfRepetitionsExt_r17_valid:1;
    u8 numberOfSlotsTBoMS_r17_valid:1;
    u8 extendedK2_r17_valid:1;
    u8 padding[3];
   s32 mappingType_r16;	/* OPTIONAL enum PUSCH_Allocation_r16_MappingType_r16_typeA = 0, PUSCH_Allocation_r16_MappingType_r16_typeB = 1 */
   u32 startSymbolAndLength_r16;	/* OPTIONAL */
   u32 startSymbol_r16;	/* OPTIONAL */
   u32 length_r16;	/* OPTIONAL */
   s32 numberOfRepetitions_r16;	/* OPTIONAL enum 
							   NumberOfRepetitions_r16_n1 = 0,
							   NumberOfRepetitions_r16_n2 = 1,
							   NumberOfRepetitions_r16_n3 = 2,
							   NumberOfRepetitions_r16_n4 = 3,
							   NumberOfRepetitions_r16_n7 = 4,
							   NumberOfRepetitions_r16_n8 = 5,
							   NumberOfRepetitions_r16_n12 = 6,
							   NumberOfRepetitions_r16_n16 = 7*/
   s32 numberOfRepetitionsExt_r17;	/* OPTIONAL enum 
							   NumberOfRepetitionsExt_r17_n1 = 0,
							   NumberOfRepetitionsExt_r17_n2 = 1,
							   NumberOfRepetitionsExt_r17_n3 = 2,
							   NumberOfRepetitionsExt_r17_n4 = 3,
							   NumberOfRepetitionsExt_r17_n7 = 4,
							   NumberOfRepetitionsExt_r17_n8 = 5,
							   NumberOfRepetitionsExt_r17_n12 = 6,
							   NumberOfRepetitionsExt_r17_n16 = 7,
							   NumberOfRepetitionsExt_r17_n20 = 8,
							   NumberOfRepetitionsExt_r17_n24 = 9,
							   NumberOfRepetitionsExt_r17_n28 = 10,
							   NumberOfRepetitionsExt_r17_n32 = 11,
							   NumberOfRepetitionsExt_r17_spare4 = 12,
							   NumberOfRepetitionsExt_r17_spare3 = 13,
							   NumberOfRepetitionsExt_r17_spare2 = 14,
							   NumberOfRepetitionsExt_r17_spare1 = 15*/
   s32 numberOfSlotsTBoMS_r17;	/* OPTIONAL enum 
                               NumberOfSlotsTBoMS_r17_n1 = 0,
							   NumberOfSlotsTBoMS_r17_n2 = 1,
							   NumberOfSlotsTBoMS_r17_n4 = 2,
							   NumberOfSlotsTBoMS_r17_n8 = 3,
							   NumberOfSlotsTBoMS_r17_spare4 = 4,
							   NumberOfSlotsTBoMS_r17_spare3 = 5,
							   NumberOfSlotsTBoMS_r17_spare2 = 6,
							   NumberOfSlotsTBoMS_r17_spare1 = 7
							   */
   u32 extendedK2_r17;	/* OPTIONAL */
}PUSCH_Allocation_r16_t;




typedef struct  {
    u8 k2_r16_valid:1;
    u8 rsv:7;
    u8 padding[2];
    u8 num_of_puschAllocationList_r16;
   u32 k2_r16;	/* OPTIONAL */
   PUSCH_Allocation_r16_t puschAllocationList_r16[8];
}PUSCH_TimeDomainResourceAllocation_r16_t;


typedef struct  {
//   s32 choice;
//#define	Pusch_TimeDomainAllocationListDCI_0_2_r16_release_chosen	0
//#define	Pusch_TimeDomainAllocationListDCI_0_2_r16_setup_chosen	1

//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    PUSCH_TimeDomainResourceAllocation_r16_t setup[64];
//   } value;
}Pusch_TimeDomainAllocationListDCI_0_2_r16_t;


typedef struct  {
//   s32 choice;
//#define	Pusch_TimeDomainAllocationListDCI_0_1_r16_release_chosen	0
//#define	Pusch_TimeDomainAllocationListDCI_0_1_r16_setup_chosen	1
//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    PUSCH_TimeDomainResourceAllocation_r16_t setup[64];
//   } value;
}Pusch_TimeDomainAllocationListDCI_0_1_r16_t;


typedef struct  {
//   s32 choice;
//#define	Symbols_r16_oneSlot_chosen	0
//#define	Symbols_r16_twoSlots_chosen	1
//  union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
      UCI_OnPUSCH_t setup[2];
//   } value;
}PUSCH_Config_Uci_OnPUSCH_ListDCI_0_1_r16_t;


typedef struct  {
   s32 choice;
   u8 num_bits;
   u8 padding[3];
   union {
      u8 oneSlot[2];
      u8/*SIZE(28)*/ twoSlots[4];
   } value;
}Symbols_r16_t;


typedef struct  {
   s32 choice;
   u8 num_of_bits;
   u8 padding[3];
   union {
      u8/*SIZE(2)*/ n2;
      u8/*SIZE(4)*/ n4;
      u8/*SIZE(5)*/ n5;
      u8/*SIZE(8)*/ n8;
      u8/*SIZE(10)*/ n10[2];
      u8/*SIZE(20)*/ n20[3];
      u8/*SIZE(40)*/ n40[5];
   } value;
}PeriodicityAndPattern_r16_t;



typedef struct  {
   u8 periodicityAndPattern_r16_valid:1;
   u8 rsv:7;
   u8 padding[3];
   Symbols_r16_t symbols_r16;
   PeriodicityAndPattern_r16_t periodicityAndPattern_r16;	/* OPTIONAL */
}InvalidSymbolPattern_r16_t;


typedef struct  {
   s32 choice;
#define	PUSCH_PathlossReferenceRS_r16_ReferenceSignal_r16_ssb_Index_r16_chosen	0
#define	PUSCH_PathlossReferenceRS_r16_ReferenceSignal_r16_csi_RS_Index_r16_chosen	1

   union {
      u32 ssb_Index_r16;
      u32 csi_RS_Index_r16;
   } value;
}PUSCH_PathlossReferenceRS_r16_ReferenceSignal_r16_t;


typedef struct  {
   u32 pusch_PathlossReferenceRS_Id_r16;
   PUSCH_PathlossReferenceRS_r16_ReferenceSignal_r16_t referenceSignal_r16;
}PUSCH_PathlossReferenceRS_r16_t;

typedef struct  {
    u8 olpc_ParameterSetDCI_0_1_r16_valid:1;
    u8 olpc_ParameterSetDCI_0_2_r16_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 olpc_ParameterSetDCI_0_1_r16;	/* OPTIONAL */
   u32 olpc_ParameterSetDCI_0_2_r16;	/* OPTIONAL */
}Olpc_ParameterSet_t;


typedef struct  {
    u8 p0_List_r16_valid:1;
    u8 rsv:7;
    u8 num_of_p0_List_r16;
    u8 padding[2];
   u32 p0_PUSCH_SetId_r16;
   s32 p0_List_r16[2];	/* OPTIONAL */
}P0_PUSCH_Set_r16_t;


typedef struct  {
    u8 additionalPCI_r17_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 pusch_PathlossReferenceRS_Id_r17;
   u32 additionalPCI_r17;	/* OPTIONAL */
}DummyPathlossReferenceRS_v1710_t;



typedef struct  {
    u8 p0_PUSCH_SetList_r16_valid:1;
    u8 olpc_ParameterSet_valid:1;
    u8 p0_PUSCH_SetList2_r17_valid:1;
    u8 rsv:5;
    u8 num_of_pathlossReferenceRSToAddModListSizeExt_v1610;
    u8 num_of_pathlossReferenceRSToReleaseListSizeExt_v1610;
    u8 num_of_sri_PUSCH_MappingToAddModList2_r17;
    u8 num_of_sri_PUSCH_MappingToReleaseList2_r17;
    u8 num_of_p0_PUSCH_SetList_r16;
    u8 num_of_p0_PUSCH_SetList2_r17;
    u8 num_of_dummy;
   PUSCH_PathlossReferenceRS_r16_t pathlossReferenceRSToAddModListSizeExt_v1610[60];	/* OPTIONAL */
   u32 pathlossReferenceRSToReleaseListSizeExt_v1610[60];	/* OPTIONAL */
   P0_PUSCH_Set_r16_t p0_PUSCH_SetList_r16[16];	/* OPTIONAL */
   Olpc_ParameterSet_t olpc_ParameterSet;	/* OPTIONAL */
   SRI_PUSCH_PowerControl_t sri_PUSCH_MappingToAddModList2_r17[16];	/* OPTIONAL */
   u32 sri_PUSCH_MappingToReleaseList2_r17[16];	/* OPTIONAL */
   P0_PUSCH_Set_r16_t p0_PUSCH_SetList2_r17[16];	/* OPTIONAL */
   DummyPathlossReferenceRS_v1710_t dummy[64];	/* OPTIONAL */
}PUSCH_PowerControl_v1610_t;






typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_Pusch_PowerControl_v1610_release_chosen	0
//#define	PUSCH_Config_Pusch_PowerControl_v1610_setup_chosen	1

//   union {
//      s8 release;
      PUSCH_PowerControl_v1610_t setup;
//   } value;
}PUSCH_Config_Pusch_PowerControl_v1610_t;



typedef struct  {
//   s32 choice;
//#define	Pusch_TimeDomainAllocationListForMultiPUSCH_r16_release_chosen	0
//#define	Pusch_TimeDomainAllocationListForMultiPUSCH_r16_setup_chosen	1

//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    PUSCH_TimeDomainResourceAllocation_r16_t setup[64];
//   } value;
}Pusch_TimeDomainAllocationListForMultiPUSCH_r16_t;



typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_Ul_AccessConfigListDCI_0_2_r17_release_chosen	0
//#define	PUSCH_Config_Ul_AccessConfigListDCI_0_2_r17_setup_chosen	1

//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
      u32 setup[64];
//   } value;
}PUSCH_Config_Ul_AccessConfigListDCI_0_2_r17_t;

typedef struct{
    u8 num_of_value;
    u8 value[3];
}nr_betaOffsetCrossPri_r17_t;


typedef struct  {
   s32 choice;
#define	BetaOffsetsCrossPriSel_r17_dynamic_r17_chosen	0
#define	BetaOffsetsCrossPriSel_r17_semiStatic_r17_chosen	1
    u8 num_of_dynamic_r17;
    u8 padding[3];
   union {
      nr_betaOffsetCrossPri_r17_t dynamic_r17[4];
      nr_betaOffsetCrossPri_r17_t semiStatic_r17;
   } value;
}BetaOffsetsCrossPriSel_r17_t;


typedef struct  {
//   s32 choice;
//   union {
//      s8 release;
      BetaOffsetsCrossPriSel_r17_t setup;
//   } value;
}BetaOffsetsCrossPri0_r17_t;

typedef struct  {
//   s32 choice;
//#define	BetaOffsetsCrossPri1_r17_release_chosen	0
//#define	BetaOffsetsCrossPri1_r17_setup_chosen	1

//   union {
//      s8 release;
      BetaOffsetsCrossPriSel_r17_t setup;
//   } value;
}BetaOffsetsCrossPri1_r17_t;

typedef struct  {
   s32 choice;
#define	DynamicDCI_0_2_r17_oneBit_r17_chosen	0
#define	DynamicDCI_0_2_r17_twoBits_r17_chosen	1
    u8 num_of_betaOffset;
    u8 padding[3];
   union {
      nr_betaOffsetCrossPri_r17_t oneBit_r17[2];
      nr_betaOffsetCrossPri_r17_t twoBits_r17[4];
   } value;
}DynamicDCI_0_2_r17_t;


typedef struct  {
   s32 choice;
#define	BetaOffsetsCrossPriSelDCI_0_2_r17_dynamicDCI_0_2_r17_chosen	0
#define	BetaOffsetsCrossPriSelDCI_0_2_r17_semiStaticDCI_0_2_r17_chosen	1

   union {
      DynamicDCI_0_2_r17_t dynamicDCI_0_2_r17;
      nr_betaOffsetCrossPri_r17_t semiStaticDCI_0_2_r17;
   } value;
}BetaOffsetsCrossPriSelDCI_0_2_r17_t;



typedef struct  {
//   s32 choice;
//#define	BetaOffsetsCrossPri0DCI_0_2_r17_release_chosen	0
//#define	BetaOffsetsCrossPri0DCI_0_2_r17_setup_chosen	1

//   union {
//      s8 release;
      BetaOffsetsCrossPriSelDCI_0_2_r17_t setup;
//   } value;
}BetaOffsetsCrossPri0DCI_0_2_r17_t;


typedef struct  {
//   s32 choice;
//#define	BetaOffsetsCrossPri1DCI_0_2_r17_release_chosen	0
//#define	BetaOffsetsCrossPri1DCI_0_2_r17_setup_chosen	1

//   union {
//      s8 release;
      BetaOffsetsCrossPriSelDCI_0_2_r17_t setup;
//   } value;
}BetaOffsetsCrossPri1DCI_0_2_r17_t;


typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_Ul_AccessConfigListDCI_0_1_r17_release_chosen	0
//#define	PUSCH_Config_Ul_AccessConfigListDCI_0_1_r17_setup_chosen	1

//   union {
//      s8 release;

	  u32 num_of_setup;//1..3
      u32 setup[3];
//   } value;
}PUSCH_Config_Ul_AccessConfigListDCI_0_1_r17_t;

typedef struct  {
//   s32 choice;
//#define	MinimumSchedulingOffsetK2_r17_release_chosen	0
//#define	MinimumSchedulingOffsetK2_r17_setup_chosen	1

//   union {
//      s8 release;
    u8 num_of_setup;
    u8 padding[3];
    u32 setup[2];
//   } value;
}MinimumSchedulingOffsetK2_r17_t;

typedef struct  {
    u8 pusch_DMRS_Bundling_r17_valid:1;
    u8 pusch_TimeDomainWindowLength_r17_valid:1;
    u8 pusch_WindowRestart_r17_valid:1;
    u8 pusch_FrequencyHoppingInterval_r17_valid:1;
    u8 rsv:4;
    u8 padding[3];
   s32 pusch_DMRS_Bundling_r17;	/* OPTIONAL enum Pusch_DMRS_Bundling_r17_enabled = 0 */
   u32 pusch_TimeDomainWindowLength_r17;	/* OPTIONAL */
   s32 pusch_WindowRestart_r17;	/* OPTIONAL enum Pusch_WindowRestart_r17_enabled = 0*/
   s32 pusch_FrequencyHoppingInterval_r17;	/* OPTIONAL enum Pusch_FrequencyHoppingInterval_r17_s2 = 0,
														   Pusch_FrequencyHoppingInterval_r17_s4 = 1,
														   Pusch_FrequencyHoppingInterval_r17_s5 = 2,
														   Pusch_FrequencyHoppingInterval_r17_s6 = 3,
														   Pusch_FrequencyHoppingInterval_r17_s8 = 4,
														   Pusch_FrequencyHoppingInterval_r17_s10 = 5,
														   Pusch_FrequencyHoppingInterval_r17_s12 = 6,
														   Pusch_FrequencyHoppingInterval_r17_s14 = 7,
														   Pusch_FrequencyHoppingInterval_r17_s16 = 8,
														   Pusch_FrequencyHoppingInterval_r17_s20 = 9 */
}DMRS_BundlingPUSCH_Config_r17_t;




typedef struct  {
//   s32 choice;
//#define	PUSCH_Config_Dmrs_BundlingPUSCH_Config_r17_release_chosen	0
//#define	PUSCH_Config_Dmrs_BundlingPUSCH_Config_r17_setup_chosen	1

//   union {
//      s8 release;
      DMRS_BundlingPUSCH_Config_r17_t setup;
//   } value;
}PUSCH_Config_Dmrs_BundlingPUSCH_Config_r17_t;

typedef struct  {
   s32 choice;
#define	Mpe_ReferenceSignal_r17_csi_RS_Resource_r17_chosen	0
#define	Mpe_ReferenceSignal_r17_ssb_Resource_r17_chosen	1

   union {
      u32 csi_RS_Resource_r17;
      u32 ssb_Resource_r17;
   } value;
}Mpe_ReferenceSignal_r17_t;


typedef struct  {
    u8 cell_r17_valid:1;
    u8 additionalPCI_r17_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 mpe_ResourceId_r17;
   u32 cell_r17;	/* OPTIONAL */
   u32 additionalPCI_r17;	/* OPTIONAL */
   Mpe_ReferenceSignal_r17_t mpe_ReferenceSignal_r17;
}MPE_Resource_r17_t;


typedef struct  {
   u64 dataScramblingIdentityPUSCH_valid:1;
   u64 txConfig_valid:1;
   u64 dmrs_UplinkForPUSCH_MappingTypeA_valid:1;
   u64 dmrs_UplinkForPUSCH_MappingTypeB_valid:1;
   u64 pusch_PowerControl_valid:1;
   u64 frequencyHopping_valid:1;
   u64 frequencyHoppingOffsetLists_valid:1;
   u64 pusch_TimeDomainAllocationList_valid:1;
   u64 pusch_AggregationFactor_valid:1;
   u64 mcs_Table_valid:1;
   u64 mcs_TableTransformPrecoder_valid:1;
   u64 transformPrecoder_valid:1;
   u64 codebookSubset_valid:1;
   u64 maxRank_valid:1;
   u64 rbg_Size_valid:1;
   u64 uci_OnPUSCH_valid:1;
   u64 tp_pi2BPSK_valid:1;
   u64 minimumSchedulingOffsetK2_r16_valid:1;
   u64 ul_AccessConfigListDCI_0_1_r16_valid:1;
   u64 harq_ProcessNumberSizeDCI_0_2_r16_valid:1;
   u64 dmrs_SequenceInitializationDCI_0_2_r16_valid:1;
   u64 numberOfBitsForRV_DCI_0_2_r16_valid:1;
   u64 antennaPortsFieldPresenceDCI_0_2_r16_valid:1;
   u64 dmrs_UplinkForPUSCH_MappingTypeA_DCI_0_2_r16_valid:1;
   u64 dmrs_UplinkForPUSCH_MappingTypeB_DCI_0_2_r16_valid:1;
   u64 frequencyHoppingDCI_0_2_r16_valid:1;
   u64 frequencyHoppingOffsetListsDCI_0_2_r16_valid:1;
   u64 codebookSubsetDCI_0_2_r16_valid:1;
   u64 invalidSymbolPatternIndicatorDCI_0_2_r16_valid:1;
   u64 maxRankDCI_0_2_r16_valid:1;
   u64 mcs_TableDCI_0_2_r16_valid:1;
   u64 mcs_TableTransformPrecoderDCI_0_2_r16_valid:1;
   u64 priorityIndicatorDCI_0_2_r16_valid:1;
   u64 pusch_RepTypeIndicatorDCI_0_2_r16_valid:1;
   u64 resourceAllocationDCI_0_2_r16_valid:1;
   u64 resourceAllocationType1GranularityDCI_0_2_r16_valid:1;
   u64 uci_OnPUSCH_ListDCI_0_2_r16_valid:1;
   u64 pusch_TimeDomainAllocationListDCI_0_2_r16_valid:1;
   u64 pusch_TimeDomainAllocationListDCI_0_1_r16_valid:1;
   u64 invalidSymbolPatternIndicatorDCI_0_1_r16_valid:1;
   u64 priorityIndicatorDCI_0_1_r16_valid:1;
   u64 pusch_RepTypeIndicatorDCI_0_1_r16_valid:1;
   u64 frequencyHoppingDCI_0_1_r16_valid:1;
   u64 uci_OnPUSCH_ListDCI_0_1_r16_valid:1;
   u64 invalidSymbolPattern_r16_valid:1;
   u64 pusch_PowerControl_v1610_valid:1;
   u64 ul_FullPowerTransmission_r16_valid:1;
   u64 pusch_TimeDomainAllocationListForMultiPUSCH_r16_valid:1;
   u64 numberOfInvalidSymbolsForDL_UL_Switching_r16_valid:1;
   u64 ul_AccessConfigListDCI_0_2_r17_valid:1;
   u64 betaOffsetsCrossPri0_r17_valid:1;
   u64 betaOffsetsCrossPri1_r17_valid:1;
   u64 betaOffsetsCrossPri0DCI_0_2_r17_valid:1;
   u64 betaOffsetsCrossPri1DCI_0_2_r17_valid:1;
   u64 mappingPattern_r17_valid:1;
   u64 secondTPCFieldDCI_0_1_r17_valid:1;
   u64 secondTPCFieldDCI_0_2_r17_valid:1;
   u64 sequenceOffsetForRV_r17_valid:1;
   u64 ul_AccessConfigListDCI_0_1_r17_valid:1;
   u64 minimumSchedulingOffsetK2_r17_valid:1;
   u64 availableSlotCounting_r17_valid:1;
   u64 dmrs_BundlingPUSCH_Config_r17_valid:1;
   u64 harq_ProcessNumberSizeDCI_0_2_v1700_valid:1;
   u64 harq_ProcessNumberSizeDCI_0_1_r17_valid:1;
   u64 rsv:1;
   u8 num_of_frequencyHoppingOffsetLists;
   u8 num_of_mpe_ResourcePoolToAddModList_r17;
   u8 num_of_mpe_ResourcePoolToReleaseList_r17;
   u8 padding;
   u32 dataScramblingIdentityPUSCH;	/* OPTIONAL */
   s32 txConfig;	/* OPTIONAL enum TxConfig_codebook = 0, TxConfig_nonCodebook = 1*/
   Dmrs_UplinkForPUSCH_MappingTypeA_t dmrs_UplinkForPUSCH_MappingTypeA;	/* OPTIONAL */
   Dmrs_UplinkForPUSCH_MappingTypeB_t dmrs_UplinkForPUSCH_MappingTypeB;	/* OPTIONAL */
   PUSCH_PowerControl_t pusch_PowerControl;	/* OPTIONAL */
   s32 frequencyHopping;	/* OPTIONAL enum FrequencyHopping_intraSlot = 0, FrequencyHopping_interSlot = 1 */
   u32 frequencyHoppingOffsetLists[4];	/* OPTIONAL */
   s32 resourceAllocation;  /* enum PUSCH_Config_ResourceAllocation_resourceAllocationType0 = 0,
									   PUSCH_Config_ResourceAllocation_resourceAllocationType1 = 1,
									   PUSCH_Config_ResourceAllocation_dynamicSwitch = 2*/
   Pusch_TimeDomainAllocationList_t pusch_TimeDomainAllocationList;	/* OPTIONAL */
   s32 pusch_AggregationFactor;	/* OPTIONAL enum Pusch_AggregationFactor_n2 = 0,
											   Pusch_AggregationFactor_n4 = 1,
											   Pusch_AggregationFactor_n8 = 2 */
   s32 mcs_Table;	/* OPTIONAL  enum PUSCH_Config_Mcs_Table_qam256 = 0, PUSCH_Config_Mcs_Table_qam64LowSE = 1*/
   s32 mcs_TableTransformPrecoder;	/* OPTIONAL enum Mcs_TableTransformPrecoder_qam256 = 0, Mcs_TableTransformPrecoder_qam64LowSE = 1 */
   s32 transformPrecoder;	/* OPTIONAL enum TransformPrecoder_enabled = 0, TransformPrecoder_disabled = 1 */
   s32 codebookSubset;	/* OPTIONAL enum CodebookSubset_fullyAndPartialAndNonCoherent = 0,
										   CodebookSubset_partialAndNonCoherent = 1,
										   CodebookSubset_nonCoherent = 2 */
   u32 maxRank;	/* OPTIONAL */
   s32 rbg_Size;	/* OPTIONAL enum  PUSCH_Config_Rbg_Size_config2 = 0 */
   PUSCH_Config_Uci_OnPUSCH_t uci_OnPUSCH;	/* OPTIONAL */
   s32 tp_pi2BPSK;	/* OPTIONAL enum Tp_pi2BPSK_enabled = 0*/
   MinimumSchedulingOffsetK2_r16_t minimumSchedulingOffsetK2_r16;	/* OPTIONAL */
   PUSCH_Config_Ul_AccessConfigListDCI_0_1_r16_t ul_AccessConfigListDCI_0_1_r16;	/* OPTIONAL */
   u32 harq_ProcessNumberSizeDCI_0_2_r16;	/* OPTIONAL */
   s32 dmrs_SequenceInitializationDCI_0_2_r16;	/* OPTIONAL enum  Dmrs_SequenceInitializationDCI_0_2_r16_enabled = 0 */
   u32 numberOfBitsForRV_DCI_0_2_r16;	/* OPTIONAL */
   s32 antennaPortsFieldPresenceDCI_0_2_r16;	/* OPTIONAL enum AntennaPortsFieldPresenceDCI_0_2_r16_enabled = 0 */
   Dmrs_UplinkForPUSCH_MappingTypeA_DCI_0_2_r16_t dmrs_UplinkForPUSCH_MappingTypeA_DCI_0_2_r16;	/* OPTIONAL */
   Dmrs_UplinkForPUSCH_MappingTypeB_DCI_0_2_r16_t dmrs_UplinkForPUSCH_MappingTypeB_DCI_0_2_r16;	/* OPTIONAL */
   FrequencyHoppingDCI_0_2_r16_t frequencyHoppingDCI_0_2_r16;	/* OPTIONAL */
   PUSCH_Config_FrequencyHoppingOffsetListsDCI_0_2_r16_t frequencyHoppingOffsetListsDCI_0_2_r16;	/* OPTIONAL */
   s32 codebookSubsetDCI_0_2_r16;	/* OPTIONAL enum CodebookSubsetDCI_0_2_r16_fullyAndPartialAndNonCoherent = 0,
											   CodebookSubsetDCI_0_2_r16_partialAndNonCoherent = 1,
											   CodebookSubsetDCI_0_2_r16_nonCoherent = 2 */
   s32 invalidSymbolPatternIndicatorDCI_0_2_r16;	/* OPTIONAL enum  InvalidSymbolPatternIndicatorDCI_0_2_r16_enabled = 0 */
   u32 maxRankDCI_0_2_r16;	/* OPTIONAL */
   s32 mcs_TableDCI_0_2_r16;	/* OPTIONAL  enum  Mcs_TableDCI_0_2_r16_qam256 = 0, Mcs_TableDCI_0_2_r16_qam64LowSE = 1*/
   s32 mcs_TableTransformPrecoderDCI_0_2_r16;	/* OPTIONAL  enum Mcs_TableTransformPrecoderDCI_0_2_r16_qam256 = 0, Mcs_TableTransformPrecoderDCI_0_2_r16_qam64LowSE = 1*/
   s32 priorityIndicatorDCI_0_2_r16;	/* OPTIONAL enum PriorityIndicatorDCI_0_2_r16_enabled = 0 */
   s32 pusch_RepTypeIndicatorDCI_0_2_r16;	/* OPTIONAL enum Pusch_RepTypeIndicatorDCI_0_2_r16_pusch_RepTypeA = 0, Pusch_RepTypeIndicatorDCI_0_2_r16_pusch_RepTypeB = 1*/
   s32 resourceAllocationDCI_0_2_r16;	/* OPTIONAL enum  ResourceAllocationDCI_0_2_r16_resourceAllocationType0 = 0,
														   ResourceAllocationDCI_0_2_r16_resourceAllocationType1 = 1,
														   ResourceAllocationDCI_0_2_r16_dynamicSwitch = 2*/
   s32 resourceAllocationType1GranularityDCI_0_2_r16;	/* OPTIONAL enum  
																	   ResourceAllocationType1GranularityDCI_0_2_r16_n2 = 0,
																	   ResourceAllocationType1GranularityDCI_0_2_r16_n4 = 1,
																	   ResourceAllocationType1GranularityDCI_0_2_r16_n8 = 2,
																	   ResourceAllocationType1GranularityDCI_0_2_r16_n16 = 3 */
   PUSCH_Config_Uci_OnPUSCH_ListDCI_0_2_r16_t uci_OnPUSCH_ListDCI_0_2_r16;	/* OPTIONAL */
   Pusch_TimeDomainAllocationListDCI_0_2_r16_t pusch_TimeDomainAllocationListDCI_0_2_r16;	/* OPTIONAL */
   Pusch_TimeDomainAllocationListDCI_0_1_r16_t pusch_TimeDomainAllocationListDCI_0_1_r16;	/* OPTIONAL */
   s32 invalidSymbolPatternIndicatorDCI_0_1_r16;	/* OPTIONAL enum InvalidSymbolPatternIndicatorDCI_0_1_r16_enabled = 0 */
   s32 priorityIndicatorDCI_0_1_r16;	/* OPTIONAL enum PriorityIndicatorDCI_0_1_r16_enabled = 0 */
   s32 pusch_RepTypeIndicatorDCI_0_1_r16;	/* OPTIONAL enum 
											   Pusch_RepTypeIndicatorDCI_0_1_r16_pusch_RepTypeA = 0,
											   Pusch_RepTypeIndicatorDCI_0_1_r16_pusch_RepTypeB = 1*/
   s32 frequencyHoppingDCI_0_1_r16;	/* OPTIONAL enum 
											   FrequencyHoppingDCI_0_1_r16_interRepetition = 0,
   											   FrequencyHoppingDCI_0_1_r16_interSlot = 1*/
   PUSCH_Config_Uci_OnPUSCH_ListDCI_0_1_r16_t uci_OnPUSCH_ListDCI_0_1_r16;	/* OPTIONAL */
   InvalidSymbolPattern_r16_t invalidSymbolPattern_r16;	/* OPTIONAL */
   PUSCH_Config_Pusch_PowerControl_v1610_t pusch_PowerControl_v1610;	/* OPTIONAL */
   s32 ul_FullPowerTransmission_r16;	/* OPTIONAL enum  Ul_FullPowerTransmission_r16_fullpower = 0,
														   Ul_FullPowerTransmission_r16_fullpowerMode1 = 1,
														   Ul_FullPowerTransmission_r16_fullpowerMode2 = 2 */
   Pusch_TimeDomainAllocationListForMultiPUSCH_r16_t pusch_TimeDomainAllocationListForMultiPUSCH_r16;	/* OPTIONAL */
   u32 numberOfInvalidSymbolsForDL_UL_Switching_r16;	/* OPTIONAL */
   PUSCH_Config_Ul_AccessConfigListDCI_0_2_r17_t ul_AccessConfigListDCI_0_2_r17;	/* OPTIONAL */
   BetaOffsetsCrossPri0_r17_t betaOffsetsCrossPri0_r17;	/* OPTIONAL */
   BetaOffsetsCrossPri1_r17_t betaOffsetsCrossPri1_r17;	/* OPTIONAL */
   BetaOffsetsCrossPri0DCI_0_2_r17_t betaOffsetsCrossPri0DCI_0_2_r17;	/* OPTIONAL */
   BetaOffsetsCrossPri1DCI_0_2_r17_t betaOffsetsCrossPri1DCI_0_2_r17;	/* OPTIONAL */
   s32 mappingPattern_r17;	/* OPTIONAL enum PUSCH_Config_MappingPattern_r17_cyclicMapping = 0,
   											PUSCH_Config_MappingPattern_r17_sequentialMapping = 1*/
   s32 secondTPCFieldDCI_0_1_r17;	/* OPTIONAL enum SecondTPCFieldDCI_0_1_r17_enabled = 0 */
   s32 secondTPCFieldDCI_0_2_r17;	/* OPTIONAL enum SecondTPCFieldDCI_0_2_r17_enabled = 0*/
   u32 sequenceOffsetForRV_r17;	/* OPTIONAL */
   PUSCH_Config_Ul_AccessConfigListDCI_0_1_r17_t ul_AccessConfigListDCI_0_1_r17;	/* OPTIONAL */
   MinimumSchedulingOffsetK2_r17_t minimumSchedulingOffsetK2_r17;	/* OPTIONAL */
   s32 availableSlotCounting_r17;	/* OPTIONALenum AvailableSlotCounting_r17_enabled = 0 */
   PUSCH_Config_Dmrs_BundlingPUSCH_Config_r17_t dmrs_BundlingPUSCH_Config_r17;	/* OPTIONAL */
   u32 harq_ProcessNumberSizeDCI_0_2_v1700;	/* OPTIONAL */
   u32 harq_ProcessNumberSizeDCI_0_1_r17;	/* OPTIONAL */
   MPE_Resource_r17_t mpe_ResourcePoolToAddModList_r17[64];	/* OPTIONAL */
   u32 mpe_ResourcePoolToReleaseList_r17[64];	/* OPTIONAL */
}PUSCH_Config_t;



typedef struct  {
//   s32 choice;
//#define	BWP_UplinkDedicated_Pusch_Config_release_chosen	0
//#define	BWP_UplinkDedicated_Pusch_Config_setup_chosen	1

//   union {
//      s8 release;
      PUSCH_Config_t setup;
//   } value;
}BWP_UplinkDedicated_Pusch_Config_t;


typedef struct  {
   s32 choice;
#define	CG_UCI_OnPUSCH_dynamic_chosen	0
#define	CG_UCI_OnPUSCH_semiStatic_chosen	1
    u8 num_of_dynamic;
    u8 padding[3];
   union {
      BetaOffsets_t dynamic[4];
      BetaOffsets_t semiStatic;
   } value;
}CG_UCI_OnPUSCH_t;


typedef struct  {
//   s32 choice;
//#define	ConfiguredGrantConfig_Uci_OnPUSCH_release_chosen	0
//#define	ConfiguredGrantConfig_Uci_OnPUSCH_setup_chosen	1

//   union {
 //     s8 release;
      CG_UCI_OnPUSCH_t setup;
//   } value;
}ConfiguredGrantConfig_Uci_OnPUSCH_t;

typedef struct  {
   s32 choice;
#define	Sdt_SSB_Subset_r17_shortBitmap_r17_chosen	0
#define	Sdt_SSB_Subset_r17_mediumBitmap_r17_chosen	1
#define	Sdt_SSB_Subset_r17_longBitmap_r17_chosen	2

   union {
      BITS/*SIZE(4)*/ shortBitmap_r17;
      BITS/*SIZE(8)*/ mediumBitmap_r17;
      BITS/*SIZE(64)*/ longBitmap_r17;
   } value;
}Sdt_SSB_Subset_r17_t;

typedef struct  {
   s32 choice;
   union {
      BITS/*SIZE(8)*/ dmrsType1_r17;
      BITS/*SIZE(12)*/ dmrsType2_r17;
   } value;
}Sdt_DMRS_Ports_r17_t;



typedef struct  {
   u32 cg_SDT_RetransmissionTimer;	/* OPTIONAL */
   Sdt_SSB_Subset_r17_t sdt_SSB_Subset_r17;	/* OPTIONAL */
   s32 sdt_SSB_PerCG_PUSCH_r17;	/* OPTIONAL enum  Sdt_SSB_PerCG_PUSCH_r17_oneEighth = 0,
												   Sdt_SSB_PerCG_PUSCH_r17_oneFourth = 1,
												   Sdt_SSB_PerCG_PUSCH_r17_half = 2,
												   Sdt_SSB_PerCG_PUSCH_r17_one = 3,
												   Sdt_SSB_PerCG_PUSCH_r17_two = 4,
												   Sdt_SSB_PerCG_PUSCH_r17_four = 5,
												   Sdt_SSB_PerCG_PUSCH_r17_eight = 6,
												   Sdt_SSB_PerCG_PUSCH_r17_sixteen = 7 */
   s32 sdt_P0_PUSCH_r17;	/* OPTIONAL */
   s32 sdt_Alpha_r17;	/* OPTIONAL enum  Sdt_Alpha_r17_alpha0 = 0,
										   Sdt_Alpha_r17_alpha04 = 1,
										   Sdt_Alpha_r17_alpha05 = 2,
										   Sdt_Alpha_r17_alpha06 = 3,
										   Sdt_Alpha_r17_alpha07 = 4,
										   Sdt_Alpha_r17_alpha08 = 5,
										   Sdt_Alpha_r17_alpha09 = 6,
										   Sdt_Alpha_r17_alpha1 = 7*/
   Sdt_DMRS_Ports_r17_t sdt_DMRS_Ports_r17;	/* OPTIONAL */
   u32 sdt_NrofDMRS_Sequences_r17;	/* OPTIONAL */
}CG_SDT_Configuration_r17_ut;


typedef struct  {
   u16 dmrs_SeqInitialization_valid:1;
   u16 srs_ResourceIndicator_valid:1;
   u16 frequencyHoppingOffset_valid:1;
   u16 pusch_RepTypeIndicator_r16_valid:1;
   u16 frequencyHoppingPUSCH_RepTypeB_r16_valid:1;
   u16 timeReferenceSFN_r16_valid:1;
   u16 pathlossReferenceIndex2_r17_valid:1;
   u16 srs_ResourceIndicator2_r17_valid:1;
   u16 precodingAndNumberOfLayers2_r17_valid:1;
   u16 timeDomainAllocation_v1710_valid:1;
   u16 timeDomainOffset_r17_valid:1;
   u16 cg_SDT_Configuration_r17_valid:1;
   u16 rsv:4;
   u16 padding;
   u32 timeDomainOffset;
   u32 timeDomainAllocation;
   u8 num_bits_of_frequencyDomainAllocation;
   u8/*SIZE(18)*/ frequencyDomainAllocation[3];
   u32 antennaPort;
   u32 dmrs_SeqInitialization;	/* OPTIONAL */
   u32 precodingAndNumberOfLayers;
   u32 srs_ResourceIndicator;	/* OPTIONAL */
   u32 mcsAndTBS;
   u32 frequencyHoppingOffset;	/* OPTIONAL */
   u32 pathlossReferenceIndex;
   s32 pusch_RepTypeIndicator_r16;	/* OPTIONAL enum Pusch_RepTypeIndicator_r16_pusch_RepTypeA = 0,
  													 Pusch_RepTypeIndicator_r16_pusch_RepTypeB = 1*/
   s32 frequencyHoppingPUSCH_RepTypeB_r16;	/* OPTIONAL enum FrequencyHoppingPUSCH_RepTypeB_r16_interRepetition = 0,
  															 FrequencyHoppingPUSCH_RepTypeB_r16_interSlot = 1 */
   s32 timeReferenceSFN_r16;	/* OPTIONAL enum TimeReferenceSFN_r16_sfn512 = 0 */
   u32 pathlossReferenceIndex2_r17;	/* OPTIONAL */
   u32 srs_ResourceIndicator2_r17;	/* OPTIONAL */
   u32 precodingAndNumberOfLayers2_r17;	/* OPTIONAL */
   u32 timeDomainAllocation_v1710;	/* OPTIONAL */
   u32 timeDomainOffset_r17;	/* OPTIONAL */
   CG_SDT_Configuration_r17_ut cg_SDT_Configuration_r17;	/* OPTIONAL */
}Rrc_ConfiguredUplinkGrant_t;

typedef struct  {
    u8 cg_StartingFullBW_InsideCOT_r16_valid:1;
    u8 cg_StartingFullBW_OutsideCOT_r16_valid:1;
    u8 cg_StartingPartialBW_InsideCOT_r16_valid:1;
    u8 cg_StartingPartialBW_OutsideCOT_r16_valid:1;
    u8 rsv:4;
    u8 num_of_cg_StartingFullBW_InsideCOT_r16;
    u8 num_of_cg_StartingFullBW_OutsideCOT_r16;
    u8 padding;
   u32 cg_StartingFullBW_InsideCOT_r16[7];	/* OPTIONAL */
   u32 cg_StartingFullBW_OutsideCOT_r16[7];	/* OPTIONAL */
   u32 cg_StartingPartialBW_InsideCOT_r16;	/* OPTIONAL */
   u32 cg_StartingPartialBW_OutsideCOT_r16;	/* OPTIONAL */
}CG_StartingOffsets_r16_t;

typedef struct  {
   u32 duration_r16;
   u32 offset_r16;
   u32 channelAccessPriority_r16;
}Cot_Sharing_r16_t;


typedef struct  {
   s32 choice;
#define	CG_COT_Sharing_r16_noCOT_Sharing_r16_chosen	0
#define	CG_COT_Sharing_r16_cot_Sharing_r16_chosen	1

   union {
      s8 noCOT_Sharing_r16;
      Cot_Sharing_r16_t cot_Sharing_r16;
   } value;
}CG_COT_Sharing_r16_t;


typedef struct  {
   s32 choice;
#define	BetaOffsetsCrossPriSelCG_r17_dynamic_r17_chosen	0
#define	BetaOffsetsCrossPriSelCG_r17_semiStatic_r17_chosen	1
    u8 num_of_dynamic_r17;
    u8 padding[3];
   union {
      nr_betaOffsetCrossPri_r17_t dynamic_r17[4];
      nr_betaOffsetCrossPri_r17_t semiStatic_r17;
   } value;
}BetaOffsetsCrossPriSelCG_r17_t;



typedef struct  {
//   s32 choice;
//#define	Cg_betaOffsetsCrossPri0_r17_release_chosen	0
//#define	Cg_betaOffsetsCrossPri0_r17_setup_chosen	1

//   union {
//      s8 release;
      BetaOffsetsCrossPriSelCG_r17_t setup;
//   } value;
}Cg_betaOffsetsCrossPri0_r17_t;


typedef struct  {
   u32 duration_r17;
   u32 offset_r17;
}Cot_Sharing_r17_t;


typedef struct  {
//   s32 choice;
//#define	Cg_betaOffsetsCrossPri1_r17_release_chosen	0
//#define	Cg_betaOffsetsCrossPri1_r17_setup_chosen	1

//   union {
//      s8 release;
      BetaOffsetsCrossPriSelCG_r17_t setup;
//   } value;
}Cg_betaOffsetsCrossPri1_r17_t;


typedef struct  {
   s32 choice;
#define	CG_COT_Sharing_r17_noCOT_Sharing_r17_chosen	0
#define	CG_COT_Sharing_r17_cot_Sharing_r17_chosen	1

   union {
      s8 noCOT_Sharing_r17;
      Cot_Sharing_r17_t cot_Sharing_r17;
   } value;
}CG_COT_Sharing_r17_t;


 typedef struct  {
    u64 frequencyHopping_valid:1;
    u64 mcs_Table_valid:1;
    u64 mcs_TableTransformPrecoder_valid:1;
    u64 uci_OnPUSCH_valid:1;
    u64 rbg_Size_valid:1;
    u64 transformPrecoder_valid:1;
    u64 repK_RV_valid:1;
    u64 configuredGrantTimer_valid:1;
    u64 rrc_ConfiguredUplinkGrant_valid:1;
    u64 cg_RetransmissionTimer_r16_valid:1;
    u64 cg_minDFI_Delay_r16_valid:1;
    u64 cg_nrofPUSCH_InSlot_r16_valid:1;
    u64 cg_nrofSlots_r16_valid:1;
    u64 cg_StartingOffsets_r16_valid:1;
    u64 cg_UCI_Multiplexing_r16_valid:1;
    u64 cg_COT_SharingOffset_r16_valid:1;
    u64 betaOffsetCG_UCI_r16_valid:1;
    u64 harq_ProcID_Offset_r16_valid:1;
    u64 harq_ProcID_Offset2_r16_valid:1;
    u64 configuredGrantConfigIndex_r16_valid:1;
    u64 configuredGrantConfigIndexMAC_r16_valid:1;
    u64 periodicityExt_r16_valid:1;
    u64 startingFromRV0_r16_valid:1;
    u64 phy_PriorityIndex_r16_valid:1;
    u64 autonomousTx_r16_valid:1;
    u64 cg_betaOffsetsCrossPri0_r17_valid:1;
    u64 cg_betaOffsetsCrossPri1_r17_valid:1;
    u64 mappingPattern_r17_valid:1;
    u64 sequenceOffsetForRV_r17_valid:1;
    u64 p0_PUSCH_Alpha2_r17_valid:1;
    u64 powerControlLoopToUse2_r17_valid:1;
    u64 periodicityExt_r17_valid:1;
    u64 repK_v1710_valid:1;
    u64 nrofHARQ_Processes_v1700_valid:1;
    u64 harq_ProcID_Offset2_v1700_valid:1;
    u64 configuredGrantTimer_v1700_valid:1;
    u64 cg_minDFI_Delay_v1710_valid:1;
    u64 harq_ProcID_Offset_v1730_valid:1;
    u64 cg_nrofSlots_r17_valid:1;
    u64 rsv:25;
   s32 frequencyHopping;	/* OPTIONAL enum ConfiguredGrantConfig_FrequencyHopping_intraSlot = 0,
   											ConfiguredGrantConfig_FrequencyHopping_interSlot = 1 */
   DMRS_UplinkConfig_t cg_DMRS_Configuration;
   s32 mcs_Table;	/* OPTIONAL enum ConfiguredGrantConfig_Mcs_Table_qam256 = 0,
   									ConfiguredGrantConfig_Mcs_Table_qam64LowSE = 1 */
   s32 mcs_TableTransformPrecoder;	/* OPTIONAL enum ConfiguredGrantConfig_Mcs_TableTransformPrecoder_qam256 = 0,
   													ConfiguredGrantConfig_Mcs_TableTransformPrecoder_qam64LowSE = 1 */
   ConfiguredGrantConfig_Uci_OnPUSCH_t uci_OnPUSCH;	/* OPTIONAL */
   s32 resourceAllocation; /*enum ConfiguredGrantConfig_ResourceAllocation_resourceAllocationType0 = 0,
							   ConfiguredGrantConfig_ResourceAllocation_resourceAllocationType1 = 1,
							   ConfiguredGrantConfig_ResourceAllocation_dynamicSwitch = 2*/
   s32 rbg_Size;	/* OPTIONAL enum ConfiguredGrantConfig_Rbg_Size_config2 = 0*/
   s32 powerControlLoopToUse; /* PowerControlLoopToUse_n0 = 0,
   								PowerControlLoopToUse_n1 = 1 */
   u32 p0_PUSCH_Alpha;
   s32 transformPrecoder;	/* OPTIONAL enum ConfiguredGrantConfig_TransformPrecoder_enabled = 0,
   												ConfiguredGrantConfig_TransformPrecoder_disabled = 1*/
   u32 nrofHARQ_Processes;
   s32 repK; /*enum  RepK_n1 = 0,
					   RepK_n2 = 1,
					   RepK_n4 = 2,
					   RepK_n8 = 3*/
   s32 repK_RV;	/* OPTIONAL enum RepK_RV_s1_0231 = 0,
							   RepK_RV_s2_0303 = 1,
							   RepK_RV_s3_0000 = 2*/
   s32 periodicity; /*ConfiguredGrantConfig_Periodicity_sym2 = 0,
						   ConfiguredGrantConfig_Periodicity_sym7 = 1,
						   ConfiguredGrantConfig_Periodicity_sym1x14 = 2,
						   ConfiguredGrantConfig_Periodicity_sym2x14 = 3,
						   ConfiguredGrantConfig_Periodicity_sym4x14 = 4,
						   ConfiguredGrantConfig_Periodicity_sym5x14 = 5,
						   ConfiguredGrantConfig_Periodicity_sym8x14 = 6,
						   ConfiguredGrantConfig_Periodicity_sym10x14 = 7,
						   ConfiguredGrantConfig_Periodicity_sym16x14 = 8,
						   ConfiguredGrantConfig_Periodicity_sym20x14 = 9,
						   ConfiguredGrantConfig_Periodicity_sym32x14 = 10,
						   ConfiguredGrantConfig_Periodicity_sym40x14 = 11,
						   ConfiguredGrantConfig_Periodicity_sym64x14 = 12,
						   ConfiguredGrantConfig_Periodicity_sym80x14 = 13,
						   ConfiguredGrantConfig_Periodicity_sym128x14 = 14,
						   ConfiguredGrantConfig_Periodicity_sym160x14 = 15,
						   ConfiguredGrantConfig_Periodicity_sym256x14 = 16,
						   ConfiguredGrantConfig_Periodicity_sym320x14 = 17,
						   ConfiguredGrantConfig_Periodicity_sym512x14 = 18,
						   ConfiguredGrantConfig_Periodicity_sym640x14 = 19,
						   ConfiguredGrantConfig_Periodicity_sym1024x14 = 20,
						   ConfiguredGrantConfig_Periodicity_sym1280x14 = 21,
						   ConfiguredGrantConfig_Periodicity_sym2560x14 = 22,
						   ConfiguredGrantConfig_Periodicity_sym5120x14 = 23,
						   ConfiguredGrantConfig_Periodicity_sym6 = 24,
						   ConfiguredGrantConfig_Periodicity_sym1x12 = 25,
						   ConfiguredGrantConfig_Periodicity_sym2x12 = 26,
						   ConfiguredGrantConfig_Periodicity_sym4x12 = 27,
						   ConfiguredGrantConfig_Periodicity_sym5x12 = 28,
						   ConfiguredGrantConfig_Periodicity_sym8x12 = 29,
						   ConfiguredGrantConfig_Periodicity_sym10x12 = 30,
						   ConfiguredGrantConfig_Periodicity_sym16x12 = 31,
						   ConfiguredGrantConfig_Periodicity_sym20x12 = 32,
						   ConfiguredGrantConfig_Periodicity_sym32x12 = 33,
						   ConfiguredGrantConfig_Periodicity_sym40x12 = 34,
						   ConfiguredGrantConfig_Periodicity_sym64x12 = 35,
						   ConfiguredGrantConfig_Periodicity_sym80x12 = 36,
						   ConfiguredGrantConfig_Periodicity_sym128x12 = 37,
						   ConfiguredGrantConfig_Periodicity_sym160x12 = 38,
						   ConfiguredGrantConfig_Periodicity_sym256x12 = 39,
						   ConfiguredGrantConfig_Periodicity_sym320x12 = 40,
						   ConfiguredGrantConfig_Periodicity_sym512x12 = 41,
						   ConfiguredGrantConfig_Periodicity_sym640x12 = 42,
						   ConfiguredGrantConfig_Periodicity_sym1280x12 = 43,
						   ConfiguredGrantConfig_Periodicity_sym2560x12 = 44*/
   u32 configuredGrantTimer;	/* OPTIONAL */
   Rrc_ConfiguredUplinkGrant_t rrc_ConfiguredUplinkGrant;	/* OPTIONAL */
   u32 cg_RetransmissionTimer_r16;	/* OPTIONAL */
   s32 cg_minDFI_Delay_r16;	/* OPTIONAL enum Cg_minDFI_Delay_r16_sym7 = 0,
										   Cg_minDFI_Delay_r16_sym1x14 = 1,
										   Cg_minDFI_Delay_r16_sym2x14 = 2,
										   Cg_minDFI_Delay_r16_sym3x14 = 3,
										   Cg_minDFI_Delay_r16_sym4x14 = 4,
										   Cg_minDFI_Delay_r16_sym5x14 = 5,
										   Cg_minDFI_Delay_r16_sym6x14 = 6,
										   Cg_minDFI_Delay_r16_sym7x14 = 7,
										   Cg_minDFI_Delay_r16_sym8x14 = 8,
										   Cg_minDFI_Delay_r16_sym9x14 = 9,
										   Cg_minDFI_Delay_r16_sym10x14 = 10,
										   Cg_minDFI_Delay_r16_sym11x14 = 11,
										   Cg_minDFI_Delay_r16_sym12x14 = 12,
										   Cg_minDFI_Delay_r16_sym13x14 = 13,
										   Cg_minDFI_Delay_r16_sym14x14 = 14,
										   Cg_minDFI_Delay_r16_sym15x14 = 15,
										   Cg_minDFI_Delay_r16_sym16x14 = 16*/
   u32 cg_nrofPUSCH_InSlot_r16;	/* OPTIONAL */
   u32 cg_nrofSlots_r16;	/* OPTIONAL */
   CG_StartingOffsets_r16_t cg_StartingOffsets_r16;	/* OPTIONAL */
   s32 cg_UCI_Multiplexing_r16;	/* OPTIONAL enum Cg_UCI_Multiplexing_r16_enabled = 0 */
   u32 cg_COT_SharingOffset_r16;	/* OPTIONAL */
   u32 betaOffsetCG_UCI_r16;	/* OPTIONAL */
   //CG_COT_Sharing_r16_t cg_COT_SharingList_r16[1709];	/* OPTIONAL */ /* COT is used for unlicensed band*/
   u32 harq_ProcID_Offset_r16;	/* OPTIONAL */
   u32 harq_ProcID_Offset2_r16;	/* OPTIONAL */
   u32 configuredGrantConfigIndex_r16;	/* OPTIONAL */
   u32 configuredGrantConfigIndexMAC_r16;	/* OPTIONAL */
   u32 periodicityExt_r16;	/* OPTIONAL */
   s32 startingFromRV0_r16;	/* OPTIONAL enum  StartingFromRV0_r16_on = 0,
   												StartingFromRV0_r16_off = 1 */
   s32 phy_PriorityIndex_r16;	/* OPTIONAL enum  ConfiguredGrantConfig_Phy_PriorityIndex_r16_p0 = 0,
   													ConfiguredGrantConfig_Phy_PriorityIndex_r16_p1 = 1 */
   s32 autonomousTx_r16;	/* OPTIONAL enum   AutonomousTx_r16_enabled = 0 */
   Cg_betaOffsetsCrossPri0_r17_t cg_betaOffsetsCrossPri0_r17;	/* OPTIONAL */
   Cg_betaOffsetsCrossPri1_r17_t cg_betaOffsetsCrossPri1_r17;	/* OPTIONAL */
   s32 mappingPattern_r17;	/* OPTIONAL eunm ConfiguredGrantConfig_MappingPattern_r17_cyclicMapping = 0,
   												ConfiguredGrantConfig_MappingPattern_r17_sequentialMapping = 1 */
   u32 sequenceOffsetForRV_r17;	/* OPTIONAL */
   u32 p0_PUSCH_Alpha2_r17;	/* OPTIONAL */
   s32 powerControlLoopToUse2_r17;	/* OPTIONAL enum  PowerControlLoopToUse2_r17_n0 = 0,
   													PowerControlLoopToUse2_r17_n1 = 1 */
   //CG_COT_Sharing_r17_t cg_COT_SharingList_r17[50722];	/* OPTIONAL */ /*COT is used for unlicensed band*/
   u32 periodicityExt_r17;	/* OPTIONAL */
   s32 repK_v1710;	/* OPTIONAL enum RepK_v1710_n12 = 0,
									   RepK_v1710_n16 = 1,
									   RepK_v1710_n24 = 2,
									   RepK_v1710_n32 = 3 */
   u32 nrofHARQ_Processes_v1700;	/* OPTIONAL */
   u32 harq_ProcID_Offset2_v1700;	/* OPTIONAL */
   u32 configuredGrantTimer_v1700;	/* OPTIONAL */
   u32 cg_minDFI_Delay_v1710;	/* OPTIONAL */
   u32 harq_ProcID_Offset_v1730;	/* OPTIONAL */
   u32 cg_nrofSlots_r17;	/* OPTIONAL */
}ConfiguredGrantConfig_t;


typedef struct  {
//   s32 choice;
//#define	BWP_UplinkDedicated_ConfiguredGrantConfig_release_chosen	0
//#define	BWP_UplinkDedicated_ConfiguredGrantConfig_setup_chosen	1

//   union {
//      s8 release;
      ConfiguredGrantConfig_t setup;
//   } value;
}BWP_UplinkDedicated_ConfiguredGrantConfig_t;

typedef struct  {
    u8 csi_RS_valid:1;
    u8 slotOffset_valid:1;
    u8 aperiodicSRS_ResourceTriggerList_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u32 aperiodicSRS_ResourceTrigger;
   u32 csi_RS;	/* OPTIONAL */
   u32 slotOffset;	/* OPTIONAL */
   u32 num_of_aperiodicSRS_ResourceTriggerList;// 0..2 , 0 means NW does not configure this setup
   u32 aperiodicSRS_ResourceTriggerList[2];	/* OPTIONAL */
}Aperiodic_t;

typedef struct  {
   u8 associatedCSI_RS_valid:1;
   u8 rsv:7;
   u8 padding[3];
   u32 associatedCSI_RS;	/* OPTIONAL */
}Semi_persistent_t;

typedef struct  {
    u8 associatedCSI_RS_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 associatedCSI_RS;	/* OPTIONAL */
}Periodic_t;


typedef struct  {
   s32 choice;
#define	ResourceType_aperiodic_chosen	0
#define	ResourceType_semi_persistent_chosen	1
#define	ResourceType_periodic_chosen	2

   union {
      Aperiodic_t aperiodic;
      Semi_persistent_t semi_persistent;
      Periodic_t periodic;
   } value;
}ResourceType_t;


typedef struct  {
   s32 choice;
#define	PathlossReferenceRS_Config_ssb_Index_chosen	0
#define	PathlossReferenceRS_Config_csi_RS_Index_chosen	1

   union {
      u32 ssb_Index;
      u32 csi_RS_Index;
   } value;
}PathlossReferenceRS_Config_t;


typedef struct  {
   u32 srs_PathlossReferenceRS_Id_r16;
   PathlossReferenceRS_Config_t pathlossReferenceRS_r16;
}PathlossReferenceRS_r16_t;

typedef struct  {
	u32 num_of_PathlossReferenceRS_r16; //0..64,Inform phy the number of items in setup list
	PathlossReferenceRS_r16_t PathlossReferenceRS_r16_list[64];
}PathlossReferenceRS_r16_list_t;

typedef struct  {
//   s32 choice;
//#define	SRS_ResourceSet_PathlossReferenceRSList_r16_release_chosen	0
//#define	SRS_ResourceSet_PathlossReferenceRSList_r16_setup_chosen	1

//   union {
//      s8 release;
      PathlossReferenceRS_r16_list_t setup;
//   } value;
}SRS_ResourceSet_PathlossReferenceRSList_r16_t;



typedef struct  {
    u16 srs_ResourceIdList_valid:1;
    u16 alpha_valid:1;
    u16 p0_valid:1;
    u16 pathlossReferenceRS_valid:1;
    u16 srs_PowerControlAdjustmentStates_valid:1;
    u16 pathlossReferenceRSList_r16_valid:1;
    u16 usagePDC_r17_valid:1;
    u16 availableSlotOffsetList_r17_valid:1;
    u16 followUnifiedTCI_StateSRS_r17_valid:1;
    u16 rsv:7;
    u16 padding;
   u32 srs_ResourceSetId;
   u32 num_of_srs_ResourceIdList; //0..16, 0 means NW does not configure this setup
   u32 srs_ResourceIdList[16];	/* OPTIONAL */

   ResourceType_t resourceType;
   s32 usage; /*enum  Usage_beamManagement = 0,
					   Usage_codebook = 1,
					   Usage_nonCodebook = 2,
					   Usage_antennaSwitching = 3*/
   s32 alpha;	/* OPTIONAL enum Alpha_alpha0 = 0,
							   Alpha_alpha04 = 1,
							   Alpha_alpha05 = 2,
							   Alpha_alpha06 = 3,
							   Alpha_alpha07 = 4,
							   Alpha_alpha08 = 5,
							   Alpha_alpha09 = 6,
							   Alpha_alpha1 = 7 */
   s32 p0;	/* OPTIONAL */
   PathlossReferenceRS_Config_t pathlossReferenceRS;	/* OPTIONAL */
   s32 srs_PowerControlAdjustmentStates;	/* OPTIONAL enum Srs_PowerControlAdjustmentStates_sameAsFci2 = 0,
   															Srs_PowerControlAdjustmentStates_separateClosedLoop = 1*/
   SRS_ResourceSet_PathlossReferenceRSList_r16_t pathlossReferenceRSList_r16;	/* OPTIONAL */
   s32 usagePDC_r17;	/* OPTIONAL enum UsagePDC_r17_true = 0 */
   u32 num_of_availableSlotOffsetList_r17; //0..4
   u32 availableSlotOffsetList_r17[4];	/* OPTIONAL */
   s32 followUnifiedTCI_StateSRS_r17;	/* OPTIONAL enum FollowUnifiedTCI_StateSRS_r17_enabled = 0*/
}SRS_ResourceSet_t;


typedef struct  {
   u32 combOffset_n2;
   u32 cyclicShift_n2;
}N2_t;

typedef struct  {
   u32 combOffset_n4;
   u32 cyclicShift_n4;
}N4_t;


typedef struct  {
   s32 choice;
#define	TransmissionComb_n2_chosen	0
#define	TransmissionComb_n4_chosen	1

   union {
      N2_t n2;
      N4_t n4;
   } value;
}TransmissionComb_t;

typedef struct  {
   u32 startPosition;
   s32 nrofSymbols; /* NrofSymbols_n1 = 0,
					   NrofSymbols_n2 = 1,
					   NrofSymbols_n4 = 2 */
   s32 repetitionFactor; /* RepetitionFactor_n1 = 0,
							   RepetitionFactor_n2 = 1,
							   RepetitionFactor_n4 = 2*/
}ResourceMapping_t;

typedef struct  {
   u32 c_SRS;
   u32 b_SRS;
   u32 b_hop;
}FreqHopping_t;


typedef struct  {
   s8 foo;	/* DUMMY */
}SRS_Resource_ResourceType_Aperiodic_t;


typedef struct  {
   int choice;
#define	SRS_PeriodicityAndOffset_sl1_chosen	0
#define	SRS_PeriodicityAndOffset_sl2_chosen	1
#define	SRS_PeriodicityAndOffset_sl4_chosen	2
#define	SRS_PeriodicityAndOffset_sl5_chosen	3
#define	SRS_PeriodicityAndOffset_sl8_chosen	4
#define	SRS_PeriodicityAndOffset_sl10_chosen	5
#define	SRS_PeriodicityAndOffset_sl16_chosen	6
#define	SRS_PeriodicityAndOffset_sl20_chosen	7
#define	SRS_PeriodicityAndOffset_sl32_chosen	8
#define	SRS_PeriodicityAndOffset_sl40_chosen	9
#define	SRS_PeriodicityAndOffset_sl64_chosen	10
#define	SRS_PeriodicityAndOffset_sl80_chosen	11
#define	SRS_PeriodicityAndOffset_sl160_chosen	12
#define	SRS_PeriodicityAndOffset_sl320_chosen	13
#define	SRS_PeriodicityAndOffset_sl640_chosen	14
#define	SRS_PeriodicityAndOffset_sl1280_chosen	15
#define	SRS_PeriodicityAndOffset_sl2560_chosen	16

   union {
      s8 sl1;
      u32 sl2;
      u32 sl4;
      u32 sl5;
      u32 sl8;
      u32 sl10;
      u32 sl16;
      u32 sl20;
      u32 sl32;
      u32 sl40;
      u32 sl64;
      u32 sl80;
      u32 sl160;
      u32 sl320;
      u32 sl640;
      u32 sl1280;
      u32 sl2560;
   } value;
}SRS_PeriodicityAndOffset_t;


typedef struct  {
   SRS_PeriodicityAndOffset_t periodicityAndOffset_sp;
}SRS_Resource_ResourceType_Semi_persistent_t;


typedef struct  {
   SRS_PeriodicityAndOffset_t periodicityAndOffset_p;
}SRS_Resource_ResourceType_Periodic_t;



typedef struct  {
   s32 choice;
#define	SRS_Resource_ResourceType_aperiodic_chosen	0
#define	SRS_Resource_ResourceType_semi_persistent_chosen	1
#define	SRS_Resource_ResourceType_periodic_chosen	2

   union {
      SRS_Resource_ResourceType_Aperiodic_t aperiodic;
      SRS_Resource_ResourceType_Semi_persistent_t semi_persistent;
      SRS_Resource_ResourceType_Periodic_t periodic;
   } value;
}SRS_Resource_ResourceType_t;


typedef struct  {
   u32 resourceId;
   u32 uplinkBWP;
}Srs_t;


typedef struct  {
   s32 choice;
#define	SRS_SpatialRelationInfo_ReferenceSignal_ssb_Index_chosen	0
#define	SRS_SpatialRelationInfo_ReferenceSignal_csi_RS_Index_chosen	1
#define	SRS_SpatialRelationInfo_ReferenceSignal_srs_chosen	2

   union {
      u32 ssb_Index;
      u32 csi_RS_Index;
      Srs_t srs;
   } value;
}SRS_SpatialRelationInfo_ReferenceSignal_t;


typedef struct  {
    u8 servingCellId_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 servingCellId;	/* OPTIONAL */
   SRS_SpatialRelationInfo_ReferenceSignal_t referenceSignal;
}SRS_SpatialRelationInfo_t;


typedef struct  {
   u32 startPosition_r16;
   s32 nrofSymbols_r16; /*enum NrofSymbols_r16_n1 = 0,
							   NrofSymbols_r16_n2 = 1,
							   NrofSymbols_r16_n4 = 2*/
   s32 repetitionFactor_r16; /* RepetitionFactor_r16_n1 = 0,
								   RepetitionFactor_r16_n2 = 1,
								   RepetitionFactor_r16_n4 = 2*/
}ResourceMapping_r16_t;


typedef struct  {
   u32 resourceId;
   u32 uplinkBWP;
}SpatialRelationInfo_PDC_r17_ReferenceSignal_Srs_t;


typedef struct  {
   s32 choice;
#define	SpatialRelationInfo_PDC_r17_ReferenceSignal_ssb_Index_chosen	0
#define	SpatialRelationInfo_PDC_r17_ReferenceSignal_csi_RS_Index_chosen	1
#define	SpatialRelationInfo_PDC_r17_ReferenceSignal_dl_PRS_PDC_chosen	2
#define	SpatialRelationInfo_PDC_r17_ReferenceSignal_srs_chosen	3

   union {
      u32 ssb_Index;
      u32 csi_RS_Index;
      u32 dl_PRS_PDC;
      SpatialRelationInfo_PDC_r17_ReferenceSignal_Srs_t srs;
   } value;
}SpatialRelationInfo_PDC_r17_ReferenceSignal_t;



typedef struct  {
   SpatialRelationInfo_PDC_r17_ReferenceSignal_t referenceSignal;
}SpatialRelationInfo_PDC_r17_t;




typedef struct  {
//   s32 choice;
//#define	SRS_Resource_SpatialRelationInfo_PDC_r17_release_chosen	0
//#define	SRS_Resource_SpatialRelationInfo_PDC_r17_setup_chosen	1

//   union {
//      s8 release;
      SpatialRelationInfo_PDC_r17_t setup;
//   } value;
}SRS_Resource_SpatialRelationInfo_PDC_r17_t;

typedef struct  {
   u32 startPosition_r17;
   s32 nrofSymbols_r17; /*  NrofSymbols_r17_n1 = 0,
							   NrofSymbols_r17_n2 = 1,
							   NrofSymbols_r17_n4 = 2,
							   NrofSymbols_r17_n8 = 3,
							   NrofSymbols_r17_n10 = 4,
							   NrofSymbols_r17_n12 = 5,
							   NrofSymbols_r17_n14 = 6 */
   s32 repetitionFactor_r17; /* RepetitionFactor_r17_n1 = 0,
							   RepetitionFactor_r17_n2 = 1,
							   RepetitionFactor_r17_n4 = 2,
							   RepetitionFactor_r17_n5 = 3,
							   RepetitionFactor_r17_n6 = 4,
							   RepetitionFactor_r17_n7 = 5,
							   RepetitionFactor_r17_n8 = 6,
							   RepetitionFactor_r17_n10 = 7,
							   RepetitionFactor_r17_n12 = 8,
							   RepetitionFactor_r17_n14 = 9*/
}ResourceMapping_r17_t;


typedef struct  {
   s32 choice;
#define	StartRBIndexFScaling_r17_startRBIndexAndFreqScalingFactor2_r17_chosen	0
#define	StartRBIndexFScaling_r17_startRBIndexAndFreqScalingFactor4_r17_chosen	1

   union {
      u32 startRBIndexAndFreqScalingFactor2_r17;
      u32 startRBIndexAndFreqScalingFactor4_r17;
   } value;
}StartRBIndexFScaling_r17_t;


typedef struct  {
    u8 enableStartRBHopping_r17_valid:1;
    u8 rsv:7;
    u8 padding[3];
   StartRBIndexFScaling_r17_t startRBIndexFScaling_r17;
   s32 enableStartRBHopping_r17;	/* OPTIONAL enum EnableStartRBHopping_r17_enable = 0*/
}PartialFreqSounding_r17_t;

typedef struct  {
   u32 combOffset_n8_r17;
   u32 cyclicShift_n8_r17;
}TransmissionComb_n8_r17_t;


typedef struct  {
   s32 choice;
#define	Srs_TCI_State_r17_srs_UL_TCI_State_chosen	0
#define	Srs_TCI_State_r17_srs_DLorJointTCI_State_chosen	1

   union {
      u32 srs_UL_TCI_State;
      u32 srs_DLorJointTCI_State;
   } value;
}Srs_TCI_State_r17_t;

typedef struct  {
   ServingCellAndBWP_Id_r17_t cellAndBWP_r17;
}Srs_DLorJointTCI_State_v1730_t;



typedef struct  {
   u16 ptrs_PortIndex_valid:1;
   u16 spatialRelationInfo_valid:1;
   u16 resourceMapping_r16_valid:1;
   u16 spatialRelationInfo_PDC_r17_valid:1;
   u16 resourceMapping_r17_valid:1;
   u16 partialFreqSounding_r17_valid:1;
   u16 transmissionComb_n8_r17_valid:1;
   u16 srs_TCI_State_r17_valid:1;
   u16 repetitionFactor_v1730_valid:1;
   u16 srs_DLorJointTCI_State_v1730_valid:1;
   u16 rsv:7;
   u16 padding;
   u32 srs_ResourceId;
   s32 nrofSRS_Ports; /*enum NrofSRS_Ports_port1 = 0,
										   NrofSRS_Ports_ports2 = 1,
										   NrofSRS_Ports_ports4 = 2*/
   s32 ptrs_PortIndex;	/* OPTIONAL enum  Ptrs_PortIndex_n0 = 0,
   											Ptrs_PortIndex_n1 = 1*/
   TransmissionComb_t transmissionComb;
   ResourceMapping_t resourceMapping;
   u32 freqDomainPosition;
   u32 freqDomainShift;
   FreqHopping_t freqHopping;
   s32 groupOrSequenceHopping; /* enum GroupOrSequenceHopping_neither = 0,
									   GroupOrSequenceHopping_groupHopping = 1,
									   GroupOrSequenceHopping_sequenceHopping = 2*/
   SRS_Resource_ResourceType_t resourceType;
   u32 sequenceId;
   SRS_SpatialRelationInfo_t spatialRelationInfo;	/* OPTIONAL */
   ResourceMapping_r16_t resourceMapping_r16;	/* OPTIONAL */
   SRS_Resource_SpatialRelationInfo_PDC_r17_t spatialRelationInfo_PDC_r17;	/* OPTIONAL */
   ResourceMapping_r17_t resourceMapping_r17;	/* OPTIONAL */
   PartialFreqSounding_r17_t partialFreqSounding_r17;	/* OPTIONAL */
   TransmissionComb_n8_r17_t transmissionComb_n8_r17;	/* OPTIONAL */
   Srs_TCI_State_r17_t srs_TCI_State_r17;	/* OPTIONAL */
   s32 repetitionFactor_v1730;	/* OPTIONAL enum  RepetitionFactor_v1730_n3 = 0 */
   Srs_DLorJointTCI_State_v1730_t srs_DLorJointTCI_State_v1730;	/* OPTIONAL */
}SRS_Resource_t;

typedef struct  {
   s8 foo;	/* DUMMY */
}Semi_persistent_r16_t;

typedef struct  {
   s8 foo;	/* DUMMY */
}Periodic_r16_t;


typedef struct  {
    u8 aperiodicSRS_ResourceTriggerList_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
	u32 num_of_aperiodicSRS_ResourceTriggerList_r16;
   u32 aperiodicSRS_ResourceTriggerList_r16[3];	/* OPTIONAL */
}Aperiodic_r16_t;


typedef struct  {
   s32 choice;
#define	ResourceType_r16_aperiodic_r16_chosen	0
#define	ResourceType_r16_semi_persistent_r16_chosen	1
#define	ResourceType_r16_periodic_r16_chosen	2

   union {
      Aperiodic_r16_t aperiodic_r16;
      Semi_persistent_r16_t semi_persistent_r16;
      Periodic_r16_t periodic_r16;
   } value;
}ResourceType_r16_t;

typedef struct  {
    u8 integerSubframeOffset_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 sfn_Offset_r16;
   u32 integerSubframeOffset_r16;	/* OPTIONAL */
}Sfn0_Offset_r16_t;



typedef struct  {
    u8 ssb_Periodicity_r16_valid:1;
    u8 sfn0_Offset_r16_valid:1;
    u8 ss_PBCH_BlockPower_r16_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u64 ssb_Freq_r16;
   s32 halfFrameIndex_r16; /*enum HalfFrameIndex_r16_zero = 0,
   								  HalfFrameIndex_r16_one = 1*/
   s32 ssbSubcarrierSpacing_r16; /*enum  SubcarrierSpacing_kHz15 = 0,
										   SubcarrierSpacing_kHz30 = 1,
										   SubcarrierSpacing_kHz60 = 2,
										   SubcarrierSpacing_kHz120 = 3,
										   SubcarrierSpacing_kHz240 = 4,
										   SubcarrierSpacing_kHz480_v1700 = 5,
										   SubcarrierSpacing_kHz960_v1700 = 6,
										   SubcarrierSpacing_spare1 = 7*/
   s32 ssb_Periodicity_r16;	/* OPTIONAL enum Ssb_Periodicity_r16_ms5 = 0,
										   Ssb_Periodicity_r16_ms10 = 1,
										   Ssb_Periodicity_r16_ms20 = 2,
										   Ssb_Periodicity_r16_ms40 = 3,
										   Ssb_Periodicity_r16_ms80 = 4,
										   Ssb_Periodicity_r16_ms160 = 5,
										   Ssb_Periodicity_r16_spare2 = 6,
										   Ssb_Periodicity_r16_spare1 = 7*/
   Sfn0_Offset_r16_t sfn0_Offset_r16;	/* OPTIONAL */
   u32 sfn_SSB_Offset_r16;
   s32 ss_PBCH_BlockPower_r16;	/* OPTIONAL */
}SSB_Configuration_r16_t;


typedef struct  {
    u8 ssb_IndexNcell_r16_valid:1;
    u8 ssb_Configuration_r16_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 physicalCellId_r16;
   u32 ssb_IndexNcell_r16;	/* OPTIONAL */
   SSB_Configuration_r16_t ssb_Configuration_r16;	/* OPTIONAL */
}SSB_InfoNcell_r16_t;


typedef struct  {
    u8 dl_PRS_ResourceId_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 dl_PRS_ID_r16;
   u32 dl_PRS_ResourceSetId_r16;
   u32 dl_PRS_ResourceId_r16;	/* OPTIONAL */
}DL_PRS_Info_r16_t;


typedef struct  {
   s32 choice;
#define	PathlossReferenceRS_Pos_r16_ssb_IndexServing_r16_chosen	0
#define	PathlossReferenceRS_Pos_r16_ssb_Ncell_r16_chosen	1
#define	PathlossReferenceRS_Pos_r16_dl_PRS_r16_chosen	2

   union {
      u32 ssb_IndexServing_r16;
      SSB_InfoNcell_r16_t ssb_Ncell_r16;
      DL_PRS_Info_r16_t dl_PRS_r16;
   } value;
}PathlossReferenceRS_Pos_r16_t;



typedef struct  {
    u8 srs_PosResourceIdList_r16_valid:1;
    u8 alpha_r16_valid:1;
    u8 p0_r16_valid:1;
    u8 pathlossReferenceRS_Pos_r16_valid:1;
    u8 rsv:4;
    u8 padding[3];
   u32 srs_PosResourceSetId_r16;
   u32 num_of_srs_PosResourceIdList_r16;
   u32 srs_PosResourceIdList_r16[16];	/* OPTIONAL */
   ResourceType_r16_t resourceType_r16;
   s32 alpha_r16;	/* OPTIONAL enum  Alpha_alpha0 = 0,
									   Alpha_alpha04 = 1,
									   Alpha_alpha05 = 2,
									   Alpha_alpha06 = 3,
									   Alpha_alpha07 = 4,
									   Alpha_alpha08 = 5,
									   Alpha_alpha09 = 6,
									   Alpha_alpha1 = 7*/
   s32 p0_r16;	/* OPTIONAL */
   PathlossReferenceRS_Pos_r16_t pathlossReferenceRS_Pos_r16;	/* OPTIONAL */
}SRS_PosResourceSet_r16_t;

typedef struct  {
   u32 combOffset_n2_r16;
   u32 cyclicShift_n2_r16;
}N2_r16_t;

typedef struct  {
   u32 combOffset_n4_r16;
   u32 cyclicShift_n4_r16;
}N4_r16_t;

typedef struct  {
   u32 combOffset_n8_r16;
   u32 cyclicShift_n8_r16;
}N8_r16_t;


typedef struct  {
   s32 choice;
#define	TransmissionComb_r16_n2_r16_chosen	0
#define	TransmissionComb_r16_n4_r16_chosen	1
#define	TransmissionComb_r16_n8_r16_chosen	2

   union {
      N2_r16_t n2_r16;
      N4_r16_t n4_r16;
      N8_r16_t n8_r16;
   } value;
}TransmissionComb_r16_t;


typedef struct   {
   u32 startPosition_r16;
   s32 nrofSymbols_r16; /*enum SRS_PosResource_r16_ResourceMapping_r16_NrofSymbols_r16_n1 = 0,
								   SRS_PosResource_r16_ResourceMapping_r16_NrofSymbols_r16_n2 = 1,
								   SRS_PosResource_r16_ResourceMapping_r16_NrofSymbols_r16_n4 = 2,
								   SRS_PosResource_r16_ResourceMapping_r16_NrofSymbols_r16_n8 = 3,
								   SRS_PosResource_r16_ResourceMapping_r16_NrofSymbols_r16_n12 = 4*/
}SRS_PosResource_r16_ResourceMapping_r16_t;

typedef struct  {
   u32 c_SRS_r16;
}FreqHopping_r16_t;

typedef struct  {
   u8 slotOffset_r16_valid:1;
   u8 rsv:7;
   u8 padding[3];
   u32 slotOffset_r16;	/* OPTIONAL */
}SRS_PosResource_r16_ResourceType_r16_Aperiodic_r16_t;


typedef struct  {
   s32 choice;
#define	SRS_PeriodicityAndOffset_r16_sl1_chosen	0
#define	SRS_PeriodicityAndOffset_r16_sl2_chosen	1
#define	SRS_PeriodicityAndOffset_r16_sl4_chosen	2
#define	SRS_PeriodicityAndOffset_r16_sl5_chosen	3
#define	SRS_PeriodicityAndOffset_r16_sl8_chosen	4
#define	SRS_PeriodicityAndOffset_r16_sl10_chosen	5
#define	SRS_PeriodicityAndOffset_r16_sl16_chosen	6
#define	SRS_PeriodicityAndOffset_r16_sl20_chosen	7
#define	SRS_PeriodicityAndOffset_r16_sl32_chosen	8
#define	SRS_PeriodicityAndOffset_r16_sl40_chosen	9
#define	SRS_PeriodicityAndOffset_r16_sl64_chosen	10
#define	SRS_PeriodicityAndOffset_r16_sl80_chosen	11
#define	SRS_PeriodicityAndOffset_r16_sl160_chosen	12
#define	SRS_PeriodicityAndOffset_r16_sl320_chosen	13
#define	SRS_PeriodicityAndOffset_r16_sl640_chosen	14
#define	SRS_PeriodicityAndOffset_r16_sl1280_chosen	15
#define	SRS_PeriodicityAndOffset_r16_sl2560_chosen	16
#define	SRS_PeriodicityAndOffset_r16_sl5120_chosen	17
#define	SRS_PeriodicityAndOffset_r16_sl10240_chosen	18
#define	SRS_PeriodicityAndOffset_r16_sl40960_chosen	19
#define	SRS_PeriodicityAndOffset_r16_sl81920_chosen	20

   union {
      s8 sl1;
      u32 sl2;
      u32 sl4;
      u32 sl5;
      u32 sl8;
      u32 sl10;
      u32 sl16;
      u32 sl20;
      u32 sl32;
      u32 sl40;
      u32 sl64;
      u32 sl80;
      u32 sl160;
      u32 sl320;
      u32 sl640;
      u32 sl1280;
      u32 sl2560;
      u32 sl5120;
      u32 sl10240;
      u32 sl40960;
      u64 sl81920;
   } value;
}SRS_PeriodicityAndOffset_r16_t;


typedef struct  {
   s32 choice;
#define	SRS_PeriodicityAndOffsetExt_r16_sl128_chosen	0
#define	SRS_PeriodicityAndOffsetExt_r16_sl256_chosen	1
#define	SRS_PeriodicityAndOffsetExt_r16_sl512_chosen	2
#define	SRS_PeriodicityAndOffsetExt_r16_sl20480_chosen	3

   union {
      u32 sl128;
      u32 sl256;
      u32 sl512;
      u32 sl20480;
   } value;
}SRS_PeriodicityAndOffsetExt_r16_t;


typedef struct  {
   u8 periodicityAndOffset_sp_Ext_r16_valid:1;
   u8 rsv:7;
   u8 padding[3];
   SRS_PeriodicityAndOffset_r16_t periodicityAndOffset_sp_r16;
   SRS_PeriodicityAndOffsetExt_r16_t periodicityAndOffset_sp_Ext_r16;	/* OPTIONAL */
}SRS_PosResource_r16_ResourceType_r16_Semi_persistent_r16_t;


typedef struct  {
    u8 periodicityAndOffset_p_Ext_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   SRS_PeriodicityAndOffset_r16_t periodicityAndOffset_p_r16;
   SRS_PeriodicityAndOffsetExt_r16_t periodicityAndOffset_p_Ext_r16;	/* OPTIONAL */
}SRS_PosResource_r16_ResourceType_r16_Periodic_r16_t;



typedef struct  {
   s32 choice;
#define	SRS_PosResource_r16_ResourceType_r16_aperiodic_r16_chosen	0
#define	SRS_PosResource_r16_ResourceType_r16_semi_persistent_r16_chosen	1
#define	SRS_PosResource_r16_ResourceType_r16_periodic_r16_chosen	2

   union {
      SRS_PosResource_r16_ResourceType_r16_Aperiodic_r16_t aperiodic_r16;
      SRS_PosResource_r16_ResourceType_r16_Semi_persistent_r16_t semi_persistent_r16;
      SRS_PosResource_r16_ResourceType_r16_Periodic_r16_t periodic_r16;
   } value;
}SRS_PosResource_r16_ResourceType_r16_t;


typedef struct  {
   s32 choice;
#define	ResourceSelection_r16_srs_ResourceId_r16_chosen	0
#define	ResourceSelection_r16_srs_PosResourceId_r16_chosen	1

   union {
      u32 srs_ResourceId_r16;
      u32 srs_PosResourceId_r16;
   } value;
}ResourceSelection_r16_t;


typedef struct  {
   ResourceSelection_r16_t resourceSelection_r16;
   u32 uplinkBWP_r16;
}Srs_SpatialRelation_r16_t;



typedef struct  {
   s32 choice;
#define	ServingRS_r16_ReferenceSignal_r16_ssb_IndexServing_r16_chosen	0
#define	ServingRS_r16_ReferenceSignal_r16_csi_RS_IndexServing_r16_chosen	1
#define	ServingRS_r16_ReferenceSignal_r16_srs_SpatialRelation_r16_chosen	2

   union {
      u32 ssb_IndexServing_r16;
      u32 csi_RS_IndexServing_r16;
      Srs_SpatialRelation_r16_t srs_SpatialRelation_r16;
   } value;
}ServingRS_r16_ReferenceSignal_r16_t;



typedef struct  {
    u8 servingCellId_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 servingCellId;	/* OPTIONAL */
   ServingRS_r16_ReferenceSignal_r16_t referenceSignal_r16;
}ServingRS_r16_t;

typedef struct  {
   s32 choice;
#define	SRS_SpatialRelationInfoPos_r16_servingRS_r16_chosen	0
#define	SRS_SpatialRelationInfoPos_r16_ssb_Ncell_r16_chosen	1
#define	SRS_SpatialRelationInfoPos_r16_dl_PRS_r16_chosen	2

   union {
      ServingRS_r16_t servingRS_r16;
      SSB_InfoNcell_r16_t ssb_Ncell_r16;
      DL_PRS_Info_r16_t dl_PRS_r16;
   } value;
}SRS_SpatialRelationInfoPos_r16_t;



typedef struct  {
    u8 spatialRelationInfoPos_r16_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 srs_PosResourceId_r16;
   TransmissionComb_r16_t transmissionComb_r16;
   SRS_PosResource_r16_ResourceMapping_r16_t resourceMapping_r16;
   u32 freqDomainShift_r16;
   FreqHopping_r16_t freqHopping_r16;
   s32 groupOrSequenceHopping_r16;/*GroupOrSequenceHopping_r16_neither = 0,
								   GroupOrSequenceHopping_r16_groupHopping = 1,
								   GroupOrSequenceHopping_r16_sequenceHopping = 2*/
   SRS_PosResource_r16_ResourceType_r16_t resourceType_r16;
   u32 sequenceId_r16;
   SRS_SpatialRelationInfoPos_r16_t spatialRelationInfoPos_r16;	/* OPTIONAL */
}SRS_PosResource_r16_t;




typedef struct  {
    u16 tpc_Accumulation_valid:1;
    u16 srs_RequestDCI_1_2_r16_valid:1;
    u16 srs_RequestDCI_0_2_r16_valid:1;
    u16 rsv:13;
    u16 padding;
   u32 num_of_srs_ResourceSetToReleaseList; //0..16, 0 means NW does not configure this setup
   u32 srs_ResourceSetToReleaseList[16];	/* OPTIONAL */

   u32 num_of_srs_ResourceSetToAddModList; ////0..16, 0 means NW does not configure this setup
   SRS_ResourceSet_t srs_ResourceSetToAddModList[16];	/* OPTIONAL */

   u32 num_of_srs_ResourceToReleaseList; //0.. 64
   u32 srs_ResourceToReleaseList[64];	/* OPTIONAL */

   u32 num_of_srs_ResourceToAddModList;//0..64
   SRS_Resource_t srs_ResourceToAddModList[64];	/* OPTIONAL */
   
   s32 tpc_Accumulation;	/* OPTIONAL enum SRS_Config_Tpc_Accumulation_disabled = 0 */
   u32 srs_RequestDCI_1_2_r16;	/* OPTIONAL */
   u32 srs_RequestDCI_0_2_r16;	/* OPTIONAL */

   u32 num_of_srs_ResourceSetToAddModListDCI_0_2_r16; //0..16
   SRS_ResourceSet_t srs_ResourceSetToAddModListDCI_0_2_r16[16];	/* OPTIONAL */

   u32 num_of_srs_ResourceSetToReleaseListDCI_0_2_r16;
   u32 srs_ResourceSetToReleaseListDCI_0_2_r16[16];	/* OPTIONAL */

   u32 num_of_srs_PosResourceSetToReleaseList_r16;
   u32 srs_PosResourceSetToReleaseList_r16[16];	/* OPTIONAL */

   u32 num_of_srs_PosResourceSetToAddModList_r16;//0..16
   SRS_PosResourceSet_r16_t srs_PosResourceSetToAddModList_r16[16];	/* OPTIONAL */

   u32 num_of_srs_PosResourceToReleaseList_r16;//0..64
   u32 srs_PosResourceToReleaseList_r16[64];	/* OPTIONAL */

   u32 num_of_srs_PosResourceToAddModList_r16;//0..64
   SRS_PosResource_r16_t srs_PosResourceToAddModList_r16[64];	/* OPTIONAL */
}SRS_Config_t;



typedef struct  {
//   s32 choice;
//#define	BWP_UplinkDedicated_Srs_Config_release_chosen	0
//#define	BWP_UplinkDedicated_Srs_Config_setup_chosen	1

 //  union {
 //     s8 release;
      SRS_Config_t setup;
//   } value;
}BWP_UplinkDedicated_Srs_Config_t;


typedef struct  {
   u32 ssb;
   u32 ra_PreambleIndex;
}BFR_SSB_Resource_t;

typedef struct  {
    u8 ra_OccasionList_valid:1;
    u8 ra_PreambleIndex_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 csi_RS;
   u32 num_of_ra_OccasionList;
   u32 ra_OccasionList[64];	/* OPTIONAL */
   u32 ra_PreambleIndex;	/* OPTIONAL */
}BFR_CSIRS_Resource_t;



typedef struct  {
   s32 choice;
#define	PRACH_ResourceDedicatedBFR_ssb_chosen	0
#define	PRACH_ResourceDedicatedBFR_csi_RS_chosen	1

   union {
      BFR_SSB_Resource_t ssb;
      BFR_CSIRS_Resource_t csi_RS;
   } value;
}PRACH_ResourceDedicatedBFR_t;

typedef struct  {
    u32 num_of_PRACH_ResourceDedicatedBFR_list; //1..48
	PRACH_ResourceDedicatedBFR_t PRACH_ResourceDedicatedBFR_list[48];
}PRACH_ResourceDedicatedBFR_list_t;


typedef struct  {
//   s32 choice;
//#define	CandidateBeamRSListExt_v1610_release_chosen	0
//#define	CandidateBeamRSListExt_v1610_setup_chosen	1
//   union {
//      s8 release;
      PRACH_ResourceDedicatedBFR_list_t setup;
//   } value;
}CandidateBeamRSListExt_v1610_t;

typedef struct  {
    u32 rootSequenceIndex_BFR_valid:1;
    u32 rach_ConfigBFR_valid:1;
    u32 rsrp_ThresholdSSB_valid:1;
    u32 candidateBeamRSList_valid:1;
    u32 ssb_perRACH_Occasion_valid:1;
    u32 ra_ssb_OccasionMaskIndex_valid:1;
    u32 recoverySearchSpaceId_valid:1;
    u32 ra_Prioritization_valid:1;
    u32 beamFailureRecoveryTimer_valid:1;
    u32 msg1_SubcarrierSpacing_valid:1;
    u32 ra_PrioritizationTwoStep_r16_valid:1;
    u32 candidateBeamRSListExt_v1610_valid:1;
    u32 spCell_BFR_CBRA_r16_valid:1;
    u32 rsv:19;
   u32 rootSequenceIndex_BFR;	/* OPTIONAL */
   nr_rach_generic_t rach_ConfigBFR;	/* OPTIONAL */
   u32 rsrp_ThresholdSSB;	/* OPTIONAL */

   u32 num_of_candidateBeamRSList; //0..16
   PRACH_ResourceDedicatedBFR_t candidateBeamRSList[16];	/* OPTIONAL */
   s32 ssb_perRACH_Occasion;	/* OPTIONAL enum  BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_oneEighth = 0,
												   BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_oneFourth = 1,
												   BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_oneHalf = 2,
												   BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_one = 3,
												   BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_two = 4,
												   BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_four = 5,
												   BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_eight = 6,
												   BeamFailureRecoveryConfig_Ssb_perRACH_Occasion_sixteen = 7 */
   u32 ra_ssb_OccasionMaskIndex;	/* OPTIONAL */
   u32 recoverySearchSpaceId;	/* OPTIONAL */
   nr_ra_priority_t ra_Prioritization;	/* OPTIONAL */
   s32 beamFailureRecoveryTimer;	/* OPTIONAL enum BeamFailureRecoveryTimer_ms10 = 0,
													   BeamFailureRecoveryTimer_ms20 = 1,
													   BeamFailureRecoveryTimer_ms40 = 2,
													   BeamFailureRecoveryTimer_ms60 = 3,
													   BeamFailureRecoveryTimer_ms80 = 4,
													   BeamFailureRecoveryTimer_ms100 = 5,
													   BeamFailureRecoveryTimer_ms150 = 6,
													   BeamFailureRecoveryTimer_ms200 = 7*/
   s32 msg1_SubcarrierSpacing;	/* OPTIONAL enum SubcarrierSpacing_kHz15 = 0,
												   SubcarrierSpacing_kHz30 = 1,
												   SubcarrierSpacing_kHz60 = 2,
												   SubcarrierSpacing_kHz120 = 3,
												   SubcarrierSpacing_kHz240 = 4,
												   SubcarrierSpacing_kHz480_v1700 = 5,
												   SubcarrierSpacing_kHz960_v1700 = 6,
												   SubcarrierSpacing_spare1 = 7*/
   nr_ra_priority_t ra_PrioritizationTwoStep_r16;	/* OPTIONAL */
   CandidateBeamRSListExt_v1610_t candidateBeamRSListExt_v1610;	/* OPTIONAL */
   s32 spCell_BFR_CBRA_r16;	/* OPTIONAL enum SpCell_BFR_CBRA_r16_true = 0*/
}BeamFailureRecoveryConfig_t;



typedef struct  {
//   s32 choice;
//#define	BWP_UplinkDedicated_BeamFailureRecoveryConfig_release_chosen	0
//#define	BWP_UplinkDedicated_BeamFailureRecoveryConfig_setup_chosen	1

//   union {
//      s8 release;
      BeamFailureRecoveryConfig_t setup;
//   } value;
}BWP_UplinkDedicated_BeamFailureRecoveryConfig_t;


typedef struct  {
   s32 choice;
#define	Sl_PUCCH_Config_r16_release_chosen	0
#define	Sl_PUCCH_Config_r16_setup_chosen	1

   union {
      s8 release;
      PUCCH_Config_t setup;
   } value;
}Sl_PUCCH_Config_r16_t;





typedef struct  {
//   s32 choice;
//#define	BWP_UplinkDedicated_Pucch_ConfigurationList_r16_release_chosen	0
//#define	BWP_UplinkDedicated_Pucch_ConfigurationList_r16_setup_chosen	1

//   union {
//      s8 release;
      PUCCH_Config_list_t setup;
//   } value;
}BWP_UplinkDedicated_Pucch_ConfigurationList_r16_t;

typedef struct  {
   s32 lbt_FailureInstanceMaxCount_r16; /*enum Lbt_FailureInstanceMaxCount_r16_n4 = 0,
												   Lbt_FailureInstanceMaxCount_r16_n8 = 1,
												   Lbt_FailureInstanceMaxCount_r16_n16 = 2,
												   Lbt_FailureInstanceMaxCount_r16_n32 = 3,
												   Lbt_FailureInstanceMaxCount_r16_n64 = 4,
												   Lbt_FailureInstanceMaxCount_r16_n128 = 5*/
   s32 lbt_FailureDetectionTimer_r16;/*enum  Lbt_FailureDetectionTimer_r16_ms10 = 0,
											   Lbt_FailureDetectionTimer_r16_ms20 = 1,
											   Lbt_FailureDetectionTimer_r16_ms40 = 2,
											   Lbt_FailureDetectionTimer_r16_ms80 = 3,
											   Lbt_FailureDetectionTimer_r16_ms160 = 4,
											   Lbt_FailureDetectionTimer_r16_ms320 = 5*/
}LBT_FailureRecoveryConfig_r16_t;



typedef struct  {
//   s32 choice;
//#define	BWP_UplinkDedicated_Lbt_FailureRecoveryConfig_r16_release_chosen	0
//#define	BWP_UplinkDedicated_Lbt_FailureRecoveryConfig_r16_setup_chosen	1

 //  union {
 //     s8 release;
      LBT_FailureRecoveryConfig_r16_t setup;
 //  } value;
}BWP_UplinkDedicated_Lbt_FailureRecoveryConfig_r16_t;


typedef struct  {
   s32 choice;
#define	ReferenceSignal_r17_ssb_Index_r17_chosen	0
#define	ReferenceSignal_r17_csi_RS_Index_r17_chosen	1
#define	ReferenceSignal_r17_srs_r17_chosen	2

   union {
      u32 ssb_Index_r17;
      u32 csi_RS_Index_r17;
      u32 srs_r17;
   } value;
}ReferenceSignal_r17_t;


typedef struct  {
    u8 servingCellId_r17_valid:1;
    u8 bwp_Id_r17_valid:1;
    u8 additionalPCI_r17_valid:1;
    u8 ul_powerControl_r17_valid:1;
    u8 pathlossReferenceRS_Id_r17_valid:1;
    u8 rsv:3;
    u8 padding[3];
   u32 tci_UL_StateId_r17;
   u32 servingCellId_r17;	/* OPTIONAL */
   u32 bwp_Id_r17;	/* OPTIONAL */
   ReferenceSignal_r17_t referenceSignal_r17;
   u32 additionalPCI_r17;	/* OPTIONAL */
   u32 ul_powerControl_r17;	/* OPTIONAL */
   u32 pathlossReferenceRS_Id_r17;	/* OPTIONAL */
}TCI_UL_State_r17_t;


typedef struct  {

   u32 num_of_ul_TCI_ToAddModList_r17; //0..64
   TCI_UL_State_r17_t ul_TCI_ToAddModList_r17[64];	/* OPTIONAL */

   u32 num_of_ul_TCI_ToReleaseList_r17;//0..64
   u32 ul_TCI_ToReleaseList_r17[64];	/* OPTIONAL */
}Ul_TCI_StateList_r17_Explicitlist_t;

typedef struct  {
   s32 choice;
#define	Ul_TCI_StateList_r17_explicitlist_chosen	0
#define	Ul_TCI_StateList_r17_unifiedTCI_StateRef_r17_chosen	1
   union {
      Ul_TCI_StateList_r17_Explicitlist_t explicitlist;
      ServingCellAndBWP_Id_r17_t unifiedTCI_StateRef_r17;
   } value;
}Ul_TCI_StateList_r17_t;


typedef struct  {
   s32 choice;
#define	Pucch_ConfigurationListMulticast1_r17_release_chosen	0
#define	Pucch_ConfigurationListMulticast1_r17_setup_chosen	1

   union {
      s8 release;
      PUCCH_Config_list_t setup;
   } value;
}Pucch_ConfigurationListMulticast1_r17_t;


typedef struct  {
   s32 choice;
#define	Pucch_ConfigurationListMulticast2_r17_release_chosen	0
#define	Pucch_ConfigurationListMulticast2_r17_setup_chosen	1

   union {
      s8 release;
      PUCCH_Config_list_t setup;
   } value;
}Pucch_ConfigurationListMulticast2_r17_t;




typedef struct  {
   s32 choice;
#define	Pucch_ConfigMulticast1_r17_release_chosen	0
#define	Pucch_ConfigMulticast1_r17_setup_chosen	1

   union {
      s8 release;
      PUCCH_Config_t setup;
   } value;
}Pucch_ConfigMulticast1_r17_t;



typedef struct  {
   s32 choice;
#define	PathlossReferenceRS_r17_ReferenceSignal_r17_ssb_Index_chosen	0
#define	PathlossReferenceRS_r17_ReferenceSignal_r17_csi_RS_Index_chosen	1

   union {
      u32 ssb_Index;
      u32 csi_RS_Index;
   } value;
}PathlossReferenceRS_r17_ReferenceSignal_r17_t;



typedef struct  {
   s32 choice;
#define	Pucch_ConfigMulticast2_r17_release_chosen	0
#define	Pucch_ConfigMulticast2_r17_setup_chosen	1

   union {
      s8 release;
      PUCCH_Config_t setup;
   } value;
}Pucch_ConfigMulticast2_r17_t;

typedef struct  {
    u8 additionalPCI_r17_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 pathlossReferenceRS_Id_r17;
   PathlossReferenceRS_r17_ReferenceSignal_r17_t referenceSignal_r17;
   u32 additionalPCI_r17;	/* OPTIONAL */
}PathlossReferenceRS_r17_t;

typedef struct{
    u8 num_of_configuredGrantConfigIndex_r16;
    u8 padding[3];
    u8 configuredGrantConfigIndex_r16[12];
}nr_configuredGrant_cfgType2DeactiveState_r16_t;

typedef struct  
{
    u32 pucch_Config_valid:1;
    u32 pusch_Config_valid:1;
    u32 configuredGrantConfig_valid:1;
    u32 srs_Config_valid:1;
    u32 beamFailureRecoveryConfig_valid:1;
    u32 cp_ExtensionC2_r16_valid:1;
    u32 cp_ExtensionC3_r16_valid:1;
    u32 useInterlacePUCCH_PUSCH_r16_valid:1;
    u32 pucch_ConfigurationList_r16_valid:1;
    u32 lbt_FailureRecoveryConfig_r16_valid:1;
    u32 configuredGrantConfigType2DeactivationStateList_r16_valid:1;
    u32 ul_TCI_StateList_r17_valid:1;
    u32 ul_powerControl_r17_valid:1;
    u32 rsv:19;
   BWP_UplinkDedicated_Pucch_Config_t *pucch_Config;	/* OPTIONAL */
   BWP_UplinkDedicated_Pusch_Config_t *pusch_Config;	/* OPTIONAL */
   BWP_UplinkDedicated_ConfiguredGrantConfig_t configuredGrantConfig;	/* OPTIONAL */
   BWP_UplinkDedicated_Srs_Config_t *srs_Config;	/* OPTIONAL */
   BWP_UplinkDedicated_BeamFailureRecoveryConfig_t *beamFailureRecoveryConfig;	/* OPTIONAL */
   //Sl_PUCCH_Config_r16_t sl_PUCCH_Config_r16;	/* OPTIONAL */
   u32 cp_ExtensionC2_r16;	/* OPTIONAL */
   u32 cp_ExtensionC3_r16;	/* OPTIONAL */
   s32 useInterlacePUCCH_PUSCH_r16;	/* OPTIONAL enum BWP_UplinkDedicated_UseInterlacePUCCH_PUSCH_r16_enabled = 0 */
   BWP_UplinkDedicated_Pucch_ConfigurationList_r16_t *pucch_ConfigurationList_r16;	/* OPTIONAL */
   BWP_UplinkDedicated_Lbt_FailureRecoveryConfig_r16_t lbt_FailureRecoveryConfig_r16;	/* OPTIONAL */

   u32 num_of_configuredGrantConfigToAddModList_r16;//0..12
   ConfiguredGrantConfig_t* configuredGrantConfigToAddModList_r16[12];	/* OPTIONAL */

   u32 num_of_configuredGrantConfigToReleaseList_r16;//0..12
   u32 configuredGrantConfigToReleaseList_r16[12];	/* OPTIONAL */

   u32 num_of_first_dimension; //0..16
   u32 num_of_second_dimension;//0..12
   u32 num_of_configuredGrantConfigType2DeactivationStateList_r16;
   nr_configuredGrant_cfgType2DeactiveState_r16_t configuredGrantConfigType2DeactivationStateList_r16[16];	/* OPTIONAL */

   
   Ul_TCI_StateList_r17_t *ul_TCI_StateList_r17;	/* OPTIONAL */
   u32 ul_powerControl_r17;	/* OPTIONAL */
   Pucch_ConfigurationListMulticast1_r17_t *pucch_ConfigurationListMulticast1_r17;	/* OPTIONAL */
   Pucch_ConfigurationListMulticast2_r17_t *pucch_ConfigurationListMulticast2_r17;	/* OPTIONAL */
   Pucch_ConfigMulticast1_r17_t *pucch_ConfigMulticast1_r17;	/* OPTIONAL */
   Pucch_ConfigMulticast2_r17_t *pucch_ConfigMulticast2_r17;	/* OPTIONAL */

   u32 num_of_pathlossReferenceRSToAddModList_r17;//0..64
   PathlossReferenceRS_r17_t pathlossReferenceRSToAddModList_r17[64];	/* OPTIONAL */

   u32 num_of_pathlossReferenceRSToReleaseList_r17;
   u32 pathlossReferenceRSToReleaseList_r17[64];	/* OPTIONAL */
}BWP_UplinkDedicated_t;

typedef struct  {
    u8 bwp_Common_valid:1;
    u8 bwp_Dedicated_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 bwp_Id;
   wnrrc_bwp_ul_common_t *bwp_Common;	/* OPTIONAL */
   BWP_UplinkDedicated_t *bwp_Dedicated;	/* OPTIONAL */
}BWP_Uplink_t;

typedef struct  {
   s32 maxCodeBlockGroupsPerTransportBlock;/* MaxCodeBlockGroupsPerTransportBlock_n2 = 0,
											   MaxCodeBlockGroupsPerTransportBlock_n4 = 1,
											   MaxCodeBlockGroupsPerTransportBlock_n6 = 2,
											   MaxCodeBlockGroupsPerTransportBlock_n8 = 3*/
}PUSCH_CodeBlockGroupTransmission_t;



typedef struct  {
//   s32 choice;
//#define	CodeBlockGroupTransmission_release_chosen	0
//#define	CodeBlockGroupTransmission_setup_chosen	1

//   union {
//      s8 release;
      PUSCH_CodeBlockGroupTransmission_t setup;
//   } value;
}CodeBlockGroupTransmission_t;




typedef struct  {
//   s32 choice;
//#define	PUSCH_ServingCellConfig_MaxMIMO_LayersDCI_0_2_r16_release_chosen	0
//#define	PUSCH_ServingCellConfig_MaxMIMO_LayersDCI_0_2_r16_setup_chosen	1

//   union {
//      s8 release;
      u32 setup;
//   } value;
}PUSCH_ServingCellConfig_MaxMIMO_LayersDCI_0_2_r16_t;




typedef struct  {
//   s32 choice;
//#define	PUSCH_ServingCellConfig_UplinkHARQ_mode_r17_release_chosen	0
//#define	PUSCH_ServingCellConfig_UplinkHARQ_mode_r17_setup_chosen	1

//   union {
//      s8 release;
      u8 num_bits_of_setup;
      u8 padding[3];
      u8/*SIZE(32)*/ setup[4];
//   } value;
}PUSCH_ServingCellConfig_UplinkHARQ_mode_r17_t;



typedef struct  {
    u16 codeBlockGroupTransmission_valid:1;
    u16 rateMatching_valid:1;
    u16 xOverhead_valid:1;
    u16 maxMIMO_Layers_valid:1;
    u16 processingType2Enabled_valid:1;
    u16 maxMIMO_LayersDCI_0_2_r16_valid:1;
    u16 nrofHARQ_ProcessesForPUSCH_r17_valid:1;
    u16 uplinkHARQ_mode_r17_valid:1;
    u16 rsv:8;
    u16 padding;
   CodeBlockGroupTransmission_t codeBlockGroupTransmission;	/* OPTIONAL */
   s32 rateMatching;	/* OPTIONAL enum RateMatching_limitedBufferRM = 0 */
   s32 xOverhead;	/* OPTIONAL  enum XOverhead_xoh6 = 0,
								   XOverhead_xoh12 = 1,
								   XOverhead_xoh18 = 2*/
   u32 maxMIMO_Layers;	/* OPTIONAL */
   bool processingType2Enabled;	/* OPTIONAL */
   PUSCH_ServingCellConfig_MaxMIMO_LayersDCI_0_2_r16_t maxMIMO_LayersDCI_0_2_r16;	/* OPTIONAL */
   s32 nrofHARQ_ProcessesForPUSCH_r17;	/* OPTIONAL enum NrofHARQ_ProcessesForPUSCH_r17_n32 = 0 */
   PUSCH_ServingCellConfig_UplinkHARQ_mode_r17_t uplinkHARQ_mode_r17;	/* OPTIONAL */
}PUSCH_ServingCellConfig_t;


typedef struct  {
//   s32 choice;
//#define	UplinkConfig_Pusch_ServingCellConfig_release_chosen	0
//#define	UplinkConfig_Pusch_ServingCellConfig_setup_chosen	1

//   union {
//      s8 release;
      PUSCH_ServingCellConfig_t setup;
//   } value;
}UplinkConfig_Pusch_ServingCellConfig_t;


typedef struct  {
    u8 cc_SetIndex_valid:1;
    u8 cc_IndexInOneCC_Set_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 cc_SetIndex;	/* OPTIONAL */
   u32 cc_IndexInOneCC_Set;	/* OPTIONAL */
}SRS_CC_SetIndex_t;


typedef struct  {
    u8 srs_CC_SetIndexlist_valid:1;
    u8 rsv:7;
    u8 padding[3];
	u32 num_of_srs_CC_SetIndexlist;//0..4
   SRS_CC_SetIndex_t srs_CC_SetIndexlist[4];	/* OPTIONAL */
}SRS_TPC_PDCCH_Config_t;


typedef struct  {
	u32 num_of_SRS_TPC_PDCCH_Config_list;//0..32
   SRS_TPC_PDCCH_Config_t SRS_TPC_PDCCH_Config_list[32];	/* OPTIONAL */
}SRS_TPC_PDCCH_Config_list_t;





typedef struct  {
   s32 choice;
#define	Srs_TPC_PDCCH_Group_typeA_chosen	0
#define	Srs_TPC_PDCCH_Group_typeB_chosen	1

   union {
      SRS_TPC_PDCCH_Config_list_t typeA;
      SRS_TPC_PDCCH_Config_t typeB;
   } value;
}Srs_TPC_PDCCH_Group_t;


typedef struct  {
    u8 srs_SwitchFromServCellIndex_valid:1;
    u8 srs_TPC_PDCCH_Group_valid:1;
    u8 monitoringCells_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u32 srs_SwitchFromServCellIndex;	/* OPTIONAL */
   s32 srs_SwitchFromCarrier;/*enum Srs_SwitchFromCarrier_sUL = 0,
   										Srs_SwitchFromCarrier_nUL = 1*/
   Srs_TPC_PDCCH_Group_t srs_TPC_PDCCH_Group;	/* OPTIONAL */

   u32 num_of_monitoringCells;//0..32
   u32 monitoringCells[32];	/* OPTIONAL */
}SRS_CarrierSwitching_t;


typedef struct  {
//   s32 choice;
//#define	CarrierSwitching_release_chosen	0
//#define	CarrierSwitching_setup_chosen	1

//   union {
//      s8 release;
      SRS_CarrierSwitching_t setup;
//   } value;
}CarrierSwitching_t;



typedef struct  {
   BOOL uplinkTxSwitchingPeriodLocation_r16;
   s32 uplinkTxSwitchingCarrier_r16; /*UplinkTxSwitchingCarrier_r16_carrier1 = 0,
   										UplinkTxSwitchingCarrier_r16_carrier2 = 1*/
}UplinkTxSwitching_r16_t;



typedef struct  {
//   s32 choice;
//#define	UplinkConfig_UplinkTxSwitching_r16_release_chosen	0
//#define	UplinkConfig_UplinkTxSwitching_r16_setup_chosen	1

//   union {
//      s8 release;
      UplinkTxSwitching_r16_t setup;
//   } value;
}UplinkConfig_UplinkTxSwitching_r16_t;



typedef struct
{
    u16 initialUplinkBWP_valid:1;
    u16 firstActiveUplinkBWP_Id_valid:1;
    u16 pusch_ServingCellConfig_valid:1;
    u16 carrierSwitching_valid:1;
    u16 powerBoostPi2BPSK_valid:1;
    u16 uplinkChannelBW_PerSCS_List_valid:1;
    u16 enablePL_RS_UpdateForPUSCH_SRS_r16_valid:1;
    u16 enableDefaultBeamPL_ForPUSCH0_0_r16_valid:1;
    u16 enableDefaultBeamPL_ForPUCCH_r16_valid:1;
    u16 enableDefaultBeamPL_ForSRS_r16_valid:1;
    u16 uplinkTxSwitching_r16_valid:1;
    u16 mpr_PowerBoost_FR2_r16_valid:1;
    u16 rsv:4;
    u16 padding;
   BWP_UplinkDedicated_t *initialUplinkBWP;	/* OPTIONAL */

   u32 num_of_uplinkBWP_ToReleaseList;//0..4
   u32 uplinkBWP_ToReleaseList[4];	/* OPTIONAL */

   u32 num_of_uplinkBWP_ToAddModList;//0..4
   BWP_Uplink_t* uplinkBWP_ToAddModList[4];	/* OPTIONAL */
   
   u32 firstActiveUplinkBWP_Id;	/* OPTIONAL */
   UplinkConfig_Pusch_ServingCellConfig_t pusch_ServingCellConfig;	/* OPTIONAL */
   CarrierSwitching_t carrierSwitching;	/* OPTIONAL */
   BOOL powerBoostPi2BPSK;	/* OPTIONAL */

   u32 num_of_uplinkChannelBW_PerSCS_List;//0..5
   scs_specific_carrier_t uplinkChannelBW_PerSCS_List[5];	/* OPTIONAL */
   s32 enablePL_RS_UpdateForPUSCH_SRS_r16;	/* OPTIONAL enum EnablePL_RS_UpdateForPUSCH_SRS_r16_enabled = 0 */
   s32 enableDefaultBeamPL_ForPUSCH0_0_r16;	/* OPTIONAL enum EnableDefaultBeamPL_ForPUSCH0_0_r16_enabled = 0*/
   s32 enableDefaultBeamPL_ForPUCCH_r16;	/* OPTIONAL enum EnableDefaultBeamPL_ForPUCCH_r16_enabled = 0 */
   s32 enableDefaultBeamPL_ForSRS_r16;	/* OPTIONAL enum EnableDefaultBeamPL_ForSRS_r16_enabled = 0*/
   UplinkConfig_UplinkTxSwitching_r16_t uplinkTxSwitching_r16;	/* OPTIONAL */
   s32 mpr_PowerBoost_FR2_r16;	/* OPTIONAL enum Mpr_PowerBoost_FR2_r16_true = 0 */
}UplinkConfig_t;


typedef struct  {
   u32 slotFormatCombinationId;

   u32 num_of_slotFormats;
   u32 slotFormats[256];
}SlotFormatCombination_t;


typedef struct  {
    u8 subcarrierSpacing2_valid:1;
    u8 slotFormatCombinations_valid:1;
    u8 positionInDCI_valid:1;
    u8 enableConfiguredUL_r16_valid:1;
    u8 rsv:4;
    u8 padding[3];
   u32 servingCellId;
   s32 subcarrierSpacing; /*SubcarrierSpacing_kHz15 = 0,
						   SubcarrierSpacing_kHz30 = 1,
						   SubcarrierSpacing_kHz60 = 2,
						   SubcarrierSpacing_kHz120 = 3,
						   SubcarrierSpacing_kHz240 = 4,
						   SubcarrierSpacing_kHz480_v1700 = 5,
						   SubcarrierSpacing_kHz960_v1700 = 6,
						   SubcarrierSpacing_spare1 = 7*/
   s32 subcarrierSpacing2;	/* OPTIONAL enum SubcarrierSpacing_kHz15 = 0,
											   SubcarrierSpacing_kHz30 = 1,
											   SubcarrierSpacing_kHz60 = 2,
											   SubcarrierSpacing_kHz120 = 3,
											   SubcarrierSpacing_kHz240 = 4,
											   SubcarrierSpacing_kHz480_v1700 = 5,
											   SubcarrierSpacing_kHz960_v1700 = 6,
											   SubcarrierSpacing_spare1 = 7*/
   u32 num_of_slotFormatCombinations;//0..512
   SlotFormatCombination_t *slotFormatCombinations[512];	/* OPTIONAL */
   u32 positionInDCI;	/* OPTIONAL */
   s32 enableConfiguredUL_r16;	/* OPTIONAL enum  EnableConfiguredUL_r16_enabled = 0*/
}SlotFormatCombinationsPerCell_t;

typedef struct  {
   u32 servingCellId_r16;
   u32 positionInDCI_r16;
}AvailableRB_SetsPerCell_r16_t;

typedef struct  {
   u32 servingCellId_r16;
   u32 positionInDCI_r16;
   s32 subcarrierSpacing_r16; /* SubcarrierSpacing_kHz15 = 0,
													   SubcarrierSpacing_kHz30 = 1,
													   SubcarrierSpacing_kHz60 = 2,
													   SubcarrierSpacing_kHz120 = 3,
													   SubcarrierSpacing_kHz240 = 4,
													   SubcarrierSpacing_kHz480_v1700 = 5,
													   SubcarrierSpacing_kHz960_v1700 = 6,
													   SubcarrierSpacing_spare1 = 7*/
   u32 num_of_co_DurationList_r16;//0..64
   u32 co_DurationList_r16[64];
}CO_DurationsPerCell_r16_t;

typedef struct  {
   u32 servingCellId_r16;
   u32 positionInDCI_r16;
}SearchSpaceSwitchTrigger_r16_t;


typedef struct  {
   u32 servingCellId_r17;
   u32 positionInDCI_r17;
   s32 subcarrierSpacing_r17; /*SubcarrierSpacing_kHz15 = 0,
								   SubcarrierSpacing_kHz30 = 1,
								   SubcarrierSpacing_kHz60 = 2,
								   SubcarrierSpacing_kHz120 = 3,
								   SubcarrierSpacing_kHz240 = 4,
								   SubcarrierSpacing_kHz480_v1700 = 5,
								   SubcarrierSpacing_kHz960_v1700 = 6,
								   SubcarrierSpacing_spare1 = 7*/
   u32 num_of_co_DurationList_r17;//0..64
   u32 co_DurationList_r17[64];
}CO_DurationsPerCell_r17_t;


typedef struct  {
   u32 availabilityCombinationId_r16;

   u32 num_of_resourceAvailability_r16;//0..256
   u32 resourceAvailability_r16[256];
}AvailabilityCombination_r16_t;

typedef struct  {
    u8 rb_Sets_r17_valid:1;
    u8 resourceAvailability_r17_valid:1;
    u8 rsv:6;
    u8 padding[3];
	u32 num_of_resourceAvailability_r17; //0..256
   u32 resourceAvailability_r17[256];	/* OPTIONAL */

   u32 num_of_rb_Sets_r17;//0..8
   u32 rb_Sets_r17[8];	/* OPTIONAL */
}RB_SetGroup_r17_t;


typedef struct  {
    u8 rb_SetGroups_r17_valid:1;
    u8 resourceAvailability_r17_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 availabilityCombinationId_r17;

   u32 num_of_rb_SetGroups_r17;//0..8
   RB_SetGroup_r17_t rb_SetGroups_r17[8];	/* OPTIONAL */

   u32 num_of_resourceAvailability_r17;//0..256
   u32 resourceAvailability_r17[256];	/* OPTIONAL */
}AvailabilityCombinationRB_Groups_r17_t;



typedef struct  {
    u8 positionInDCI_AI_r16_valid:1;
    u8 availabilityCombinationsRB_Groups_r17_valid:1;
    u8 positionInDCI_AI_RBGroups_v1720_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u32 availabilityCombinationsPerCellIndex_r16;
   u8 num_bits_iab_DU_CellIdentity_r16;
   u8/*SIZE(36)*/ iab_DU_CellIdentity_r16[5];
   u8 padding1[2];
   u32 positionInDCI_AI_r16;	/* OPTIONAL */

   u32 num_of_availabilityCombinations_r16;//0..512
   AvailabilityCombination_r16_t availabilityCombinations_r16[512];

   u32 num_of_availabilityCombinationsRB_Groups_r17;//0..512
   AvailabilityCombinationRB_Groups_r17_t *availabilityCombinationsRB_Groups_r17[512];	/* OPTIONAL */
   u32 positionInDCI_AI_RBGroups_v1720;	/* OPTIONAL */
}AvailabilityCombinationsPerCell_r16_t;



typedef struct  {
   u32 sfi_RNTI;
   u32 dci_PayloadSize;

   u32 num_of_slotFormatCombToAddModList;//0..16
   SlotFormatCombinationsPerCell_t *slotFormatCombToAddModList[16];	/* OPTIONAL */


   u32 num_of_slotFormatCombToReleaseList;
   u32 slotFormatCombToReleaseList[16];	/* OPTIONAL */

   u32 num_of_availableRB_SetsToAddModList_r16;//0..16
   AvailableRB_SetsPerCell_r16_t availableRB_SetsToAddModList_r16[16];	/* OPTIONAL */

   u32 num_of_availableRB_SetsToReleaseList_r16;//0..16
   u32 availableRB_SetsToReleaseList_r16[16];	/* OPTIONAL */

   u32 num_of_switchTriggerToAddModList_r16;//0..4
   SearchSpaceSwitchTrigger_r16_t switchTriggerToAddModList_r16[4];	/* OPTIONAL */

   u32 num_of_switchTriggerToReleaseList_r16;//0..4
   u32 switchTriggerToReleaseList_r16[4];	/* OPTIONAL */

   u32 num_of_co_DurationsPerCellToAddModList_r16;//0..16
   CO_DurationsPerCell_r16_t *co_DurationsPerCellToAddModList_r16[16];	/* OPTIONAL */

   u32 num_of_co_DurationsPerCellToReleaseList_r16;//0..16
   u32 co_DurationsPerCellToReleaseList_r16[16];	/* OPTIONAL */

   u32 num_of_switchTriggerToAddModListSizeExt_r16;//0..12
   SearchSpaceSwitchTrigger_r16_t switchTriggerToAddModListSizeExt_r16[12];	/* OPTIONAL */

   u32 num_of_switchTriggerToReleaseListSizeExt_r16;//0..12
   u32 switchTriggerToReleaseListSizeExt_r16[12];	/* OPTIONAL */

   u32 num_of_co_DurationsPerCellToAddModList_r17;//0..16
   CO_DurationsPerCell_r17_t *co_DurationsPerCellToAddModList_r17[16];	/* OPTIONAL */
}SlotFormatIndicator_t;

typedef struct  {
   u32 ai_RNTI_r16;
   u32 dci_PayloadSizeAI_r16;

   u32 num_of_availableCombToAddModList_r16;//0..512
   AvailabilityCombinationsPerCell_r16_t *availableCombToAddModList_r16[512];	/* OPTIONAL */

   u32 num_of_availableCombToReleaseList_r16;//0..512
   u32 availableCombToReleaseList_r16[512];	/* OPTIONAL */
}AvailabilityIndicator_r16_t;


typedef struct  {
//   s32 choice;
//#define	PDCCH_ServingCellConfig_SlotFormatIndicator_release_chosen	0
//#define	PDCCH_ServingCellConfig_SlotFormatIndicator_setup_chosen	1

//   union {
//      s8 release;
      SlotFormatIndicator_t setup;
//   } value;
}PDCCH_ServingCellConfig_SlotFormatIndicator_t;




typedef struct  {
//   s32 choice;
//#define	PDCCH_ServingCellConfig_AvailabilityIndicator_r16_release_chosen	0
//#define	PDCCH_ServingCellConfig_AvailabilityIndicator_r16_setup_chosen	1

//   union {
//      s8 release;
      AvailabilityIndicator_r16_t setup;
//   } value;
}PDCCH_ServingCellConfig_AvailabilityIndicator_r16_t;


typedef struct  {
    u8 slotFormatIndicator_valid:1;
    u8 availabilityIndicator_r16_valid:1;
    u8 searchSpaceSwitchTimer_r16_valid:1;
    u8 searchSpaceSwitchTimer_v1710_valid:1;
    u8 rsv:7;
    u8 padding[3];
   PDCCH_ServingCellConfig_SlotFormatIndicator_t *slotFormatIndicator;	/* OPTIONAL */
   PDCCH_ServingCellConfig_AvailabilityIndicator_r16_t *availabilityIndicator_r16;	/* OPTIONAL */
   u32 searchSpaceSwitchTimer_r16;	/* OPTIONAL */
   u32 searchSpaceSwitchTimer_v1710;	/* OPTIONAL */
}PDCCH_ServingCellConfig_t;



typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_Pdcch_ServingCellConfig_release_chosen	0
//#define	ServingCellConfig_Pdcch_ServingCellConfig_setup_chosen	1

//   union {
//      s8 release;
      PDCCH_ServingCellConfig_t setup;
//   } value;
}ServingCellConfig_Pdcch_ServingCellConfig_t;

typedef struct  {
   s32 maxCodeBlockGroupsPerTransportBlock; /*PDSCH_CodeBlockGroupTransmission_MaxCodeBlockGroupsPerTransportBlock_n2 = 0,
											   PDSCH_CodeBlockGroupTransmission_MaxCodeBlockGroupsPerTransportBlock_n4 = 1,
											   PDSCH_CodeBlockGroupTransmission_MaxCodeBlockGroupsPerTransportBlock_n6 = 2,
											   PDSCH_CodeBlockGroupTransmission_MaxCodeBlockGroupsPerTransportBlock_n8 = 3*/
   BOOL codeBlockGroupFlushIndicator;
}PDSCH_CodeBlockGroupTransmission_t;




typedef struct  {
//   s32 choice;
//#define	PDSCH_ServingCellConfig_CodeBlockGroupTransmission_release_chosen	0
//#define	PDSCH_ServingCellConfig_CodeBlockGroupTransmission_setup_chosen	1

//   union {
//      s8 release;
      PDSCH_CodeBlockGroupTransmission_t setup;
//   } value;
}PDSCH_ServingCellConfig_CodeBlockGroupTransmission_t;


typedef struct  {
   u32 num_of_PDSCH_CodeBlockGroupTransmission;//0..2
   PDSCH_CodeBlockGroupTransmission_t PDSCH_CodeBlockGroupTransmission_list[2];
}PDSCH_CodeBlockGroupTransmission_list_t;







typedef struct  {
//   s32 choice;
//#define	PDSCH_ServingCellConfig_Pdsch_CodeBlockGroupTransmissionList_r16_release_chosen	0
//#define	PDSCH_ServingCellConfig_Pdsch_CodeBlockGroupTransmissionList_r16_setup_chosen	1

//   union {
//      s8 release;
      PDSCH_CodeBlockGroupTransmission_list_t setup;
//   } value;
}PDSCH_ServingCellConfig_Pdsch_CodeBlockGroupTransmissionList_r16_t;





typedef struct  {
//   s32 choice;
//#define	PDSCH_ServingCellConfig_DownlinkHARQ_FeedbackDisabled_r17_release_chosen	0
//#define	PDSCH_ServingCellConfig_DownlinkHARQ_FeedbackDisabled_r17_setup_chosen	1

//   union {
//      s8 release;
    u8 num_bits_of_setup;
    u8 padding[3];
    u8/*SIZE(32)*/ setup[4];
//   } value;
}PDSCH_ServingCellConfig_DownlinkHARQ_FeedbackDisabled_r17_t;




typedef struct  {
    u16 codeBlockGroupTransmission_valid:1;
    u16 xOverhead_valid:1;
    u16 nrofHARQ_ProcessesForPDSCH_valid:1;
    u16 pucch_Cell_valie:1;
    u16 pucch_Cell_valid:1;
    u16 maxMIMO_Layers_valid:1;
    u16 processingType2Enabled_valid:1;
    u16 pdsch_CodeBlockGroupTransmissionList_r16_valid:1;
    u16 downlinkHARQ_FeedbackDisabled_r17_valid:1;
    u16 nrofHARQ_ProcessesForPDSCH_v1700_valid:1;
    u16 rsv:6;
    u16 padding;
   PDSCH_ServingCellConfig_CodeBlockGroupTransmission_t codeBlockGroupTransmission;	/* OPTIONAL */
   s32 xOverhead;	/* OPTIONAL ENUM PDSCH_ServingCellConfig_XOverhead_xOh6 = 0,
									   PDSCH_ServingCellConfig_XOverhead_xOh12 = 1,
									   PDSCH_ServingCellConfig_XOverhead_xOh18 = 2 */
   s32 nrofHARQ_ProcessesForPDSCH;	/* OPTIONAL enum  NrofHARQ_ProcessesForPDSCH_n2 = 0,
													   NrofHARQ_ProcessesForPDSCH_n4 = 1,
													   NrofHARQ_ProcessesForPDSCH_n6 = 2,
													   NrofHARQ_ProcessesForPDSCH_n10 = 3,
													   NrofHARQ_ProcessesForPDSCH_n12 = 4,
													   NrofHARQ_ProcessesForPDSCH_n16 = 5*/
   u32 pucch_Cell;	/* OPTIONAL */
   u32 maxMIMO_Layers;	/* OPTIONAL */
   BOOL processingType2Enabled;	/* OPTIONAL */
   PDSCH_ServingCellConfig_Pdsch_CodeBlockGroupTransmissionList_r16_t pdsch_CodeBlockGroupTransmissionList_r16;	/* OPTIONAL */
   PDSCH_ServingCellConfig_DownlinkHARQ_FeedbackDisabled_r17_t downlinkHARQ_FeedbackDisabled_r17;	/* OPTIONAL */
   s32 nrofHARQ_ProcessesForPDSCH_v1700;	/* OPTIONAL enum NrofHARQ_ProcessesForPDSCH_v1700_n32 = 0 */
}PDSCH_ServingCellConfig_t;



typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_Pdsch_ServingCellConfig_release_chosen	0
//#define	ServingCellConfig_Pdsch_ServingCellConfig_setup_chosen	1

//   union {
//      s8 release;
      PDSCH_ServingCellConfig_t setup;
//   } value;
}ServingCellConfig_Pdsch_ServingCellConfig_t;

typedef struct  {
    u8 powerControlOffsetSS_valid:1;
    u8 periodicityAndOffset_valid:1;
    u8 qcl_InfoPeriodicCSI_RS_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u32 nzp_CSI_RS_ResourceId;
   CSI_RS_ResourceMapping_t resourceMapping;
   s32 powerControlOffset;
   s32 powerControlOffsetSS;	/* OPTIONAL enum  PowerControlOffsetSS_db_3 = 0,
												   PowerControlOffsetSS_db0 = 1,
												   PowerControlOffsetSS_db3 = 2,
												   PowerControlOffsetSS_db6 = 3*/
   u32 scramblingID;
   CSI_ResourcePeriodicityAndOffset_t periodicityAndOffset;	/* OPTIONAL */
   u32 qcl_InfoPeriodicCSI_RS;	/* OPTIONAL */
}NZP_CSI_RS_Resource_t;

typedef struct  {
   u32 nzp_CSI_RS_ResourceId1_r17;
   u32 nzp_CSI_RS_ResourceId2_r17;
}NZP_CSI_RS_Pairing_r17_t;



typedef struct  {
    u8 pair1OfNZP_CSI_RS_r17_valid:1;
    u8 pair2OfNZP_CSI_RS_r17_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 nrofResourcesGroup1_r17;
   NZP_CSI_RS_Pairing_r17_t pair1OfNZP_CSI_RS_r17;	/* OPTIONAL */
   NZP_CSI_RS_Pairing_r17_t pair2OfNZP_CSI_RS_r17;	/* OPTIONAL */
}CMRGroupingAndPairing_r17_t;



typedef struct  {
    u16 repetition_valid:1;
    u16 aperiodicTriggeringOffset_valid:1;
    u16 trs_Info_valid:1;
    u16 aperiodicTriggeringOffset_r16_valid:1;
    u16 pdc_Info_r17_valid:1;
    u16 cmrGroupingAndPairing_r17_valid:1;
    u16 aperiodicTriggeringOffset_r17_valid:1;
    u16 aperiodicTriggeringOffsetL2_r17_valid:1;
    u16 rsv:8;
    u16 padding;
   u32 nzp_CSI_ResourceSetId;

   u32 num_of_nzp_CSI_RS_Resources;//0..64
   u32 nzp_CSI_RS_Resources[64];
   
   s32 repetition;	/* OPTIONAL enum  Repetition_on = 0,
   									Repetition_off = 1 */
   u32 aperiodicTriggeringOffset;	/* OPTIONAL */
   s32 trs_Info;	/* OPTIONAL enum Trs_Info_true = 0*/
   u32 aperiodicTriggeringOffset_r16;	/* OPTIONAL */
   s32 pdc_Info_r17;	/* OPTIONAL enum  Pdc_Info_r17_true = 0*/
   CMRGroupingAndPairing_r17_t cmrGroupingAndPairing_r17;	/* OPTIONAL */
   u32 aperiodicTriggeringOffset_r17;	/* OPTIONAL */
   u32 aperiodicTriggeringOffsetL2_r17;	/* OPTIONAL */
}NZP_CSI_RS_ResourceSet_t;


typedef struct  {
   s32 subcarrierLocation_p0;/*enum SubcarrierLocation_p0_s0 = 0,
									   SubcarrierLocation_p0_s2 = 1,
									   SubcarrierLocation_p0_s4 = 2,
									   SubcarrierLocation_p0_s6 = 3,
									   SubcarrierLocation_p0_s8 = 4,
									   SubcarrierLocation_p0_s10 = 5*/
   u32 symbolLocation_p0;
}Pattern0_t;


typedef struct  {
   s32 subcarrierLocation_p1; /*enum  SubcarrierLocation_p1_s0 = 0,
									   SubcarrierLocation_p1_s4 = 1,
									   SubcarrierLocation_p1_s8 = 2*/
   u32 symbolLocation_p1;
}Pattern1_t;



typedef struct  {
   s32 choice;
#define	Csi_IM_ResourceElementPattern_pattern0_chosen	0
#define	Csi_IM_ResourceElementPattern_pattern1_chosen	1

   union {
      Pattern0_t pattern0;
      Pattern1_t pattern1;
   } value;
}Csi_IM_ResourceElementPattern_t;

typedef struct  {
    u8 csi_IM_ResourceElementPattern_valid:1;
    u8 freqBand_valid:1;
    u8 periodicityAndOffset_valid:1;
    u8 rsv:5;
    u8 padding[3];
   u32 csi_IM_ResourceId;
   Csi_IM_ResourceElementPattern_t csi_IM_ResourceElementPattern;	/* OPTIONAL */
   CSI_FrequencyOccupation_t freqBand;	/* OPTIONAL */
   CSI_ResourcePeriodicityAndOffset_t periodicityAndOffset;	/* OPTIONAL */
}CSI_IM_Resource_t;

typedef struct  {
    u8 servingAdditionalPCIList_r17_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 csi_SSB_ResourceSetId;

   u32 num_of_csi_SSB_ResourceList;//0..64
   u32 csi_SSB_ResourceList[64];

   u32 num_of_servingAdditionalPCIList_r17;//0..64
   u32 servingAdditionalPCIList_r17[64];	/* OPTIONAL */
}CSI_SSB_ResourceSet_t;

typedef struct  {
   u32 csi_IM_ResourceSetId;

   u32 num_of_csi_IM_Resources;//0..8
   u32 csi_IM_Resources[8];
}CSI_IM_ResourceSet_t;


typedef struct  {
    u8 nzp_CSI_RS_ResourceSetList_valid:1;
    u8 csi_SSB_ResourceSetList_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 num_of_nzp_CSI_RS_ResourceSetList;//0..16
   u32 nzp_CSI_RS_ResourceSetList[16];	/* OPTIONAL */

   u32 num_of_csi_SSB_ResourceSetList; //0..1
   u32 csi_SSB_ResourceSetList[1];	/* OPTIONAL */
}Nzp_CSI_RS_SSB_t;


typedef struct  {
   s32 choice;
   u32 num_of_csi_IM_ResourceSetList;//0..16
   union {
      Nzp_CSI_RS_SSB_t nzp_CSI_RS_SSB;
      u32 csi_IM_ResourceSetList[16];
   } value;
}Csi_RS_ResourceSetList_t;



typedef struct  {
    u8 csi_SSB_ResourceSetListExt_r17_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 csi_ResourceConfigId;
   Csi_RS_ResourceSetList_t csi_RS_ResourceSetList;
   u32 bwp_Id;
   u32 resourceType; /* CSI_ResourceConfig_ResourceType_aperiodic = 0,
						   CSI_ResourceConfig_ResourceType_semiPersistent = 1,
						   CSI_ResourceConfig_ResourceType_periodic = 2*/
   u32 csi_SSB_ResourceSetListExt_r17;	/* OPTIONAL */
}CSI_ResourceConfig_t;



typedef struct  {
   s32 choice;
#define	CSI_ReportPeriodicityAndOffset_slots4_chosen	0
#define	CSI_ReportPeriodicityAndOffset_slots5_chosen	1
#define	CSI_ReportPeriodicityAndOffset_slots8_chosen	2
#define	CSI_ReportPeriodicityAndOffset_slots10_chosen	3
#define	CSI_ReportPeriodicityAndOffset_slots16_chosen	4
#define	CSI_ReportPeriodicityAndOffset_slots20_chosen	5
#define	CSI_ReportPeriodicityAndOffset_slots40_chosen	6
#define	CSI_ReportPeriodicityAndOffset_slots80_chosen	7
#define	CSI_ReportPeriodicityAndOffset_slots160_chosen	8
#define	CSI_ReportPeriodicityAndOffset_slots320_chosen	9

   union {
      u32 slots4;
      u32 slots5;
      u32 slots8;
      u32 slots10;
      u32 slots16;
      u32 slots20;
      u32 slots40;
      u32 slots80;
      u32 slots160;
      u32 slots320;
   } value;
}CSI_ReportPeriodicityAndOffset_t;

typedef struct  {
   u32 uplinkBandwidthPartId;
   u32 pucch_Resource;
}PUCCH_CSI_Resource_t;

typedef struct  {
   CSI_ReportPeriodicityAndOffset_t reportSlotConfig;

   u32 num_of_pucch_CSI_ResourceList;//0..4
   PUCCH_CSI_Resource_t pucch_CSI_ResourceList[4];
}SemiPersistentOnPUCCH_t;



typedef struct  {
   CSI_ReportPeriodicityAndOffset_t reportSlotConfig;

   u32 num_of_pucch_CSI_ResourceList;//0..4
   PUCCH_CSI_Resource_t pucch_CSI_ResourceList[4];
}ReportConfigType_Periodic_t;


typedef struct  {
	u32 num_of_reportSlotOffsetList;//0..16
   u32 reportSlotOffsetList[16];
}ReportConfigType_Aperiodic_t;

typedef enum{
   nr_ReportSlotConfig_sl5 = 0,
   nr_ReportSlotConfig_sl10 = 1,
   nr_ReportSlotConfig_sl20 = 2,
   nr_ReportSlotConfig_sl40 = 3,
   nr_ReportSlotConfig_sl80 = 4,
   nr_ReportSlotConfig_sl160 = 5,
   nr_ReportSlotConfig_sl320 = 6
}nr_ReportSlotConfig_e;

typedef struct {
   u8 reportSlotConfig;/*enumerate refer to nr_ReportSlotConfig_e*/
   u8 num_of_reportSlotOffsetList;
   u32 reportSlotOffsetList[16];
   u32 p0alpha;
}SemiPersistentOnPUSCH_t;

typedef struct  {
   s32 choice;
   union {
      ReportConfigType_Periodic_t periodic;
      SemiPersistentOnPUCCH_t semiPersistentOnPUCCH;
      SemiPersistentOnPUSCH_t semiPersistentOnPUSCH;
      ReportConfigType_Aperiodic_t aperiodic;
   } value;
}ReportConfigType_t;

typedef struct  {
    u8 pdsch_BundleSizeForCSI_valid:1;
    u8 rsv:7;
    u8 padding[3];
   s32 pdsch_BundleSizeForCSI;	/* OPTIONAL enum Pdsch_BundleSizeForCSI_n2 = 0,
   												Pdsch_BundleSizeForCSI_n4 = 1*/
}Cri_RI_i1_CQI_t;




typedef struct  {
   s32 choice;
#define	ReportQuantity_none_chosen	0
#define	ReportQuantity_cri_RI_PMI_CQI_chosen	1
#define	ReportQuantity_cri_RI_i1_chosen	2
#define	ReportQuantity_cri_RI_i1_CQI_chosen	3
#define	ReportQuantity_cri_RI_CQI_chosen	4
#define	ReportQuantity_cri_RSRP_chosen	5
#define	ReportQuantity_ssb_Index_RSRP_chosen	6
#define	ReportQuantity_cri_RI_LI_PMI_CQI_chosen	7

   union {
      s8 none;
      s8 cri_RI_PMI_CQI;
      s8 cri_RI_i1;
      Cri_RI_i1_CQI_t cri_RI_i1_CQI;
      s8 cri_RI_CQI;
      s8 cri_RSRP;
      s8 ssb_Index_RSRP;
      s8 cri_RI_LI_PMI_CQI;
   } value;
}ReportQuantity_t;


typedef struct  {
   s32 choice;
   u32 num_bits;
   union {
      u32/*SIZE(3)*/ subbands3;
      u32/*SIZE(4)*/ subbands4;
      u32/*SIZE(5)*/ subbands5;
      u32/*SIZE(6)*/ subbands6;
      u32/*SIZE(7)*/ subbands7;
      u32/*SIZE(8)*/ subbands8;
      u32/*SIZE(9)*/ subbands9;
      u32/*SIZE(10)*/ subbands10;
      u32/*SIZE(11)*/ subbands11;
      u32/*SIZE(12)*/ subbands12;
      u32/*SIZE(13)*/ subbands13;
      u32/*SIZE(14)*/ subbands14;
      u32/*SIZE(15)*/ subbands15;
      u32/*SIZE(16)*/ subbands16;
      u32/*SIZE(17)*/ subbands17;
      u32/*SIZE(18)*/ subbands18;
      u32/*SIZE(19)*/ subbands19_v1530;
   } value;
}Csi_ReportingBand_t;


typedef struct  {
    u32 cqi_FormatIndicator_valid:1;
    u32 pmi_FormatIndicator_valid:1;
    u32 csi_ReportingBand_valid:1;
    u32 rsv:29;
   s32 cqi_FormatIndicator;	/* OPTIONAL enum Cqi_FormatIndicator_widebandCQI = 0,
   												Cqi_FormatIndicator_subbandCQI = 1 */
   s32 pmi_FormatIndicator;	/* OPTIONAL enum Pmi_FormatIndicator_widebandPMI = 0,
   											Pmi_FormatIndicator_subbandPMI = 1*/
   Csi_ReportingBand_t csi_ReportingBand;	/* OPTIONAL */
}ReportFreqConfiguration_t;


typedef struct  {
   u8 num_bits_twoTX_CodebookSubsetRestriction;
   u8/*SIZE(6)*/ twoTX_CodebookSubsetRestriction;
   u16 padding;
}NrOfAntennaPorts_Two_t;



typedef struct  {
   s16 choice;
#define	N1_n2_two_one_TypeI_SinglePanel_Restriction_chosen	0
#define	N1_n2_two_two_TypeI_SinglePanel_Restriction_chosen	1
#define	N1_n2_four_one_TypeI_SinglePanel_Restriction_chosen	2
#define	N1_n2_three_two_TypeI_SinglePanel_Restriction_chosen	3
#define	N1_n2_six_one_TypeI_SinglePanel_Restriction_chosen	4
#define	N1_n2_four_two_TypeI_SinglePanel_Restriction_chosen	5
#define	N1_n2_eight_one_TypeI_SinglePanel_Restriction_chosen	6
#define	N1_n2_four_three_TypeI_SinglePanel_Restriction_chosen	7
#define	N1_n2_six_two_TypeI_SinglePanel_Restriction_chosen	8
#define	N1_n2_twelve_one_TypeI_SinglePanel_Restriction_chosen	9
#define	N1_n2_four_four_TypeI_SinglePanel_Restriction_chosen	10
#define	N1_n2_eight_two_TypeI_SinglePanel_Restriction_chosen	11
#define	N1_n2_sixteen_one_TypeI_SinglePanel_Restriction_chosen	12
    u16 num_bits_value;
   union {
      u8/*SIZE(8)*/ two_one_TypeI_SinglePanel_Restriction;
      u8/*SIZE(64)*/ two_two_TypeI_SinglePanel_Restriction[8];
      u8/*SIZE(16)*/ four_one_TypeI_SinglePanel_Restriction[2];
      u8/*SIZE(96)*/ three_two_TypeI_SinglePanel_Restriction[12];
      u8/*SIZE(24)*/ six_one_TypeI_SinglePanel_Restriction[3];
      u8/*SIZE(128)*/ four_two_TypeI_SinglePanel_Restriction[16];
      u8/*SIZE(32)*/ eight_one_TypeI_SinglePanel_Restriction[4];
      u8/*SIZE(192)*/ four_three_TypeI_SinglePanel_Restriction[24];
      u8/*SIZE(192)*/ six_two_TypeI_SinglePanel_Restriction[24];
      u8/*SIZE(48)*/ twelve_one_TypeI_SinglePanel_Restriction[6];
      u8/*SIZE(256)*/ four_four_TypeI_SinglePanel_Restriction[32];
      u8/*SIZE(256)*/ eight_two_TypeI_SinglePanel_Restriction[32];
      u8/*SIZE(64)*/ sixteen_one_TypeI_SinglePanel_Restriction[8];
   } value;
}N1_n2_t;


typedef struct  {
    u8 typeI_SinglePanel_codebookSubsetRestriction_i2_valid:1;
    u8 rsv:7;
    u8 num_bits_typeI_SinglePanel_codebookSubsetRestriction_i2;
    u8/*SIZE(16)*/ typeI_SinglePanel_codebookSubsetRestriction_i2[2];   /* OPTIONAL */
   N1_n2_t n1_n2;
}MoreThanTwo_t;


typedef struct  {
   s32 choice;
#define	NrOfAntennaPorts_two_chosen	0
#define	NrOfAntennaPorts_moreThanTwo_chosen	1

   union {
      NrOfAntennaPorts_Two_t two;
      MoreThanTwo_t moreThanTwo;
   } value;
}NrOfAntennaPorts_t;



typedef struct  {
   s16 choice;
#define	Ng_n1_n2_two_two_one_TypeI_MultiPanel_Restriction_chosen	0
#define	Ng_n1_n2_two_four_one_TypeI_MultiPanel_Restriction_chosen	1
#define	Ng_n1_n2_four_two_one_TypeI_MultiPanel_Restriction_chosen	2
#define	Ng_n1_n2_two_two_two_TypeI_MultiPanel_Restriction_chosen	3
#define	Ng_n1_n2_two_eight_one_TypeI_MultiPanel_Restriction_chosen	4
#define	Ng_n1_n2_four_four_one_TypeI_MultiPanel_Restriction_chosen	5
#define	Ng_n1_n2_two_four_two_TypeI_MultiPanel_Restriction_chosen	6
#define	Ng_n1_n2_four_two_two_TypeI_MultiPanel_Restriction_chosen	7
   u16 num_bits_value;
   union {
      u8/*SIZE(8)*/ two_two_one_TypeI_MultiPanel_Restriction[1];
      u8/*SIZE(16)*/ two_four_one_TypeI_MultiPanel_Restriction[2];
      u8/*SIZE(8)*/ four_two_one_TypeI_MultiPanel_Restriction[1];
      u8/*SIZE(64)*/ two_two_two_TypeI_MultiPanel_Restriction[8];
      u8/*SIZE(32)*/ two_eight_one_TypeI_MultiPanel_Restriction[4];
      u8/*SIZE(16)*/ four_four_one_TypeI_MultiPanel_Restriction[2];
      u8/*SIZE(128)*/ two_four_two_TypeI_MultiPanel_Restriction[16];
      u8/*SIZE(64)*/ four_two_two_TypeI_MultiPanel_Restriction[8];
   } value;
}Ng_n1_n2_t;



typedef struct  {
   NrOfAntennaPorts_t nrOfAntennaPorts;
   u8 num_bits_typeI_SinglePanel_ri_Restriction;
   u8/*SIZE(8)*/ typeI_SinglePanel_ri_Restriction;
   u16 padding;
}TypeI_SinglePanel_t;

typedef struct  {
   Ng_n1_n2_t ng_n1_n2;
   u8 num_bits_ri_Restriction;
   u8/*SIZE(4)*/ ri_Restriction;
   u16 padding;
}TypeI_MultiPanel_t;




typedef struct  {
   s32 choice;
   union {
      TypeI_SinglePanel_t typeI_SinglePanel;
      TypeI_MultiPanel_t  typeI_MultiPanel;
   } value;
}SubType_t;


typedef struct  {
   SubType_t subType;
   u32 codebookMode;
}Type1_t;



typedef struct  {
   s16 choice;
#define	N1_n2_codebookSubsetRestriction_two_one_chosen	0
#define	N1_n2_codebookSubsetRestriction_two_two_chosen	1
#define	N1_n2_codebookSubsetRestriction_four_one_chosen	2
#define	N1_n2_codebookSubsetRestriction_three_two_chosen	3
#define	N1_n2_codebookSubsetRestriction_six_one_chosen	4
#define	N1_n2_codebookSubsetRestriction_four_two_chosen	5
#define	N1_n2_codebookSubsetRestriction_eight_one_chosen	6
#define	N1_n2_codebookSubsetRestriction_four_three_chosen	7
#define	N1_n2_codebookSubsetRestriction_six_two_chosen	8
#define	N1_n2_codebookSubsetRestriction_twelve_one_chosen	9
#define	N1_n2_codebookSubsetRestriction_four_four_chosen	10
#define	N1_n2_codebookSubsetRestriction_eight_two_chosen	11
#define	N1_n2_codebookSubsetRestriction_sixteen_one_chosen	12
    u16 num_bits_value;
   union {
      u8/*SIZE(16)*/ two_one[2];
      u8/*SIZE(43)*/ two_two[6];
      u8/*SIZE(32)*/ four_one[4];
      u8/*SIZE(59)*/ three_two[8];
      u8/*SIZE(48)*/ six_one[6];
      u8/*SIZE(75)*/ four_two[10];
      u8/*SIZE(64)*/ eight_one[8];
      u8/*SIZE(107)*/ four_three[14];
      u8/*SIZE(107)*/ six_two[14];
      u8/*SIZE(96)*/ twelve_one[12];
      u8/*SIZE(139)*/ four_four[18];
      u8/*SIZE(139)*/ eight_two[18];
      u8/*SIZE(128)*/ sixteen_one[16];
   } value;
}N1_n2_codebookSubsetRestriction_t;




typedef struct {
   N1_n2_codebookSubsetRestriction_t n1_n2_codebookSubsetRestriction;
   u8 num_bits_typeII_RI_Restriction;
   u8/*SIZE(2)*/ typeII_RI_Restriction;
   u16 padding;
}TypeII_t;

typedef struct  {
    u16 portSelectionSamplingSize_valid:1;
    u16 rsv:15;
    u8 num_bits_typeII_PortSelectionRI_Restriction;
    u8/*SIZE(2)*/ typeII_PortSelectionRI_Restriction;
   s32 portSelectionSamplingSize;	/* OPTIONAL enum PortSelectionSamplingSize_n1 = 0,
												   PortSelectionSamplingSize_n2 = 1,
												   PortSelectionSamplingSize_n3 = 2,
												   PortSelectionSamplingSize_n4 = 3*/
}TypeII_PortSelection_t;



typedef struct  {
   s32 choice;
#define	Type2_SubType_typeII_chosen	0
#define	Type2_SubType_typeII_PortSelection_chosen	1

   union {
      TypeII_t typeII;
      TypeII_PortSelection_t typeII_PortSelection;
   } value;
}Type2_SubType_t;


typedef struct  {
   Type2_SubType_t subType;
   s32 phaseAlphabetSize;/*enum PhaseAlphabetSize_n4 = 0,
  												    PhaseAlphabetSize_n8 = 1*/
   BOOL subbandAmplitude;
   s32 numberOfBeams; /*NumberOfBeams_two = 0,
					   NumberOfBeams_three = 1,
					   NumberOfBeams_four = 2*/
}Type2_T;



typedef struct  {
   s32 choice;
#define	CodebookType_type1_chosen	0
#define	CodebookType_type2_chosen	1

   union {
      Type1_t type1;
      Type2_T type2;
   } value;
}CodebookType_t;




typedef struct  {
   CodebookType_t codebookType;
}CodebookConfig_t;

typedef struct  {
    u8 nrofReportedRS_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 nrofReportedRS;	/* OPTIONAL enum  NrofReportedRS_n1 = 0,
						   NrofReportedRS_n2 = 1,
						   NrofReportedRS_n3 = 2,
						   NrofReportedRS_n4 = 3 */
}Disabled_t;



typedef struct  {
   s32 choice;
#define	GroupBasedBeamReporting_enabled_chosen	0
#define	GroupBasedBeamReporting_disabled_chosen	1

   union {
      s8 enabled;
      Disabled_t disabled;
   } value;
}GroupBasedBeamReporting_t;

typedef struct  {
   u16 rank1_8_valid:1;
   u16 rank2_8_valid:1;
   u16 rank3_8_valid:1;
   u16 rank4_8_valid:1;
   u16 rank5_8_valid:1;
   u16 rank6_8_valid:1;
   u16 rank7_8_valid:1;
   u16 rank8_8_valid:1;
   u16 rsv:8;
   u16 padding;
   u32 rank1_8;	/* OPTIONAL */
   u32 rank2_8[2];	/* OPTIONAL */
   u32 rank3_8[3];	/* OPTIONAL */
   u32 rank4_8[4];	/* OPTIONAL */
   u32 rank5_8[5];	/* OPTIONAL */
   u32 rank6_8[6];	/* OPTIONAL */
   u32 rank7_8[7];	/* OPTIONAL */
   u32 rank8_8[8];	/* OPTIONAL */
}PortIndexFor8Ranks_PortIndex8_t;

typedef struct  {
    u8 rank1_4_valid:1;
    u8 rank2_4_valid:1;
    u8 rank3_4_valid:1;
    u8 rank4_4_valid:1;
    u8 rsv:4;
    u8 padding[3];
   u32 rank1_4;	/* OPTIONAL */
   u32 rank2_4[2];	/* OPTIONAL */
   u32 rank3_4[3];	/* OPTIONAL */
   u32 rank4_4[4];	/* OPTIONAL */
}PortIndexFor8Ranks_PortIndex4_t;


typedef struct  {
    u8 rank1_2_valid:1;
    u8 rank2_2_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 rank1_2;	/* OPTIONAL */
   u32 rank2_2[2];	/* OPTIONAL */
}PortIndexFor8Ranks_PortIndex2_t;




typedef struct  {
   s32 choice;
#define	PortIndexFor8Ranks_portIndex8_chosen	0
#define	PortIndexFor8Ranks_portIndex4_chosen	1
#define	PortIndexFor8Ranks_portIndex2_chosen	2
#define	PortIndexFor8Ranks_portIndex1_chosen	3

   union {
      PortIndexFor8Ranks_PortIndex8_t portIndex8;
      PortIndexFor8Ranks_PortIndex4_t portIndex4;
      PortIndexFor8Ranks_PortIndex2_t portIndex2;
      s8 portIndex1;
   } value;
}PortIndexFor8Ranks_t;


typedef struct  {
   s32 reportSlotConfig_v1530; /*enum ReportSlotConfig_v1530_sl4 = 0,
								   ReportSlotConfig_v1530_sl8 = 1,
								   ReportSlotConfig_v1530_sl16 = 2*/
}SemiPersistentOnPUSCH_v1530_t;

typedef struct  {
    u8 reportSlotOffsetListDCI_0_2_r16_valid:1;
    u8 reportSlotOffsetListDCI_0_1_r16_valid:1;
    u8 rsv:6;
    u8 padding[3];
   u32 num_of_reportSlotOffsetListDCI_0_2_r16;//0..64
   u32  reportSlotOffsetListDCI_0_2_r16[64];	/* OPTIONAL */

   u32 num_of_reportSlotOffsetListDCI_0_1_r16;
   u32 reportSlotOffsetListDCI_0_1_r16[64];	/* OPTIONAL */
}SemiPersistentOnPUSCH_v1610_t;

typedef struct  {
    u8 reportSlotOffsetListDCI_0_2_r16_valid:1;
    u8 reportSlotOffsetListDCI_0_1_r16_valid:1;
    u8 rsv:6;
    u8 padding[3];
	u32 num_of_reportSlotOffsetListDCI_0_2_r16;//0..64
   u32 reportSlotOffsetListDCI_0_2_r16[64];	/* OPTIONAL */

   u32 num_of_reportSlotOffsetListDCI_0_1_r16;//0..64
   u32 reportSlotOffsetListDCI_0_1_r16[64];	/* OPTIONAL */
}Aperiodic_v1610_t;


typedef struct  {
   s32 choice;
#define	ReportQuantity_r16_cri_SINR_r16_chosen	0
#define	ReportQuantity_r16_ssb_Index_SINR_r16_chosen	1

   union {
      s8 cri_SINR_r16;
      s8 ssb_Index_SINR_r16;
   } value;
}ReportQuantity_r16_t;


typedef struct  {
   s16 choice;
#define	N1_n2_codebookSubsetRestriction_r16_two_one_chosen	0
#define	N1_n2_codebookSubsetRestriction_r16_two_two_chosen	1
#define	N1_n2_codebookSubsetRestriction_r16_four_one_chosen	2
#define	N1_n2_codebookSubsetRestriction_r16_three_two_chosen	3
#define	N1_n2_codebookSubsetRestriction_r16_six_one_chosen	4
#define	N1_n2_codebookSubsetRestriction_r16_four_two_chosen	5
#define	N1_n2_codebookSubsetRestriction_r16_eight_one_chosen	6
#define	N1_n2_codebookSubsetRestriction_r16_four_three_chosen	7
#define	N1_n2_codebookSubsetRestriction_r16_six_two_chosen	8
#define	N1_n2_codebookSubsetRestriction_r16_twelve_one_chosen	9
#define	N1_n2_codebookSubsetRestriction_r16_four_four_chosen	10
#define	N1_n2_codebookSubsetRestriction_r16_eight_two_chosen	11
#define	N1_n2_codebookSubsetRestriction_r16_sixteen_one_chosen	12
    u16 num_bits_value;
   union {
      u8/*SIZE(16)*/ two_one[2];
      u8/*SIZE(43)*/ two_two[6];
      u8/*SIZE(32)*/ four_one[4];
      u8/*SIZE(59)*/ three_two[8];
      u8/*SIZE(48)*/ six_one[6];
      u8/*SIZE(75)*/ four_two[10];
      u8/*SIZE(64)*/ eight_one[8];
      u8/*SIZE(107)*/ four_three[14];
      u8/*SIZE(107)*/ six_two[14];
      u8/*SIZE(96)*/ twelve_one[12];
      u8/*SIZE(139)*/ four_four[18];
      u8/*SIZE(139)*/ eight_two[18];
      u8/*SIZE(128)*/ sixteen_one[16];
   } value;
}N1_n2_codebookSubsetRestriction_r16_t;



typedef struct  {
   N1_n2_codebookSubsetRestriction_r16_t n1_n2_codebookSubsetRestriction_r16;
   u8 num_bits_typeII_RI_Restriction_r16;
   u8/*SIZE(4)*/ typeII_RI_Restriction_r16;
   u8 padding[2];
}TypeII_r16_t;

typedef struct  {
   s32 portSelectionSamplingSize_r16;/*enum PortSelectionSamplingSize_r16_n1 = 0,
											   PortSelectionSamplingSize_r16_n2 = 1,
											   PortSelectionSamplingSize_r16_n3 = 2,
											   PortSelectionSamplingSize_r16_n4 = 3*/
   u8 num_bits_typeII_PortSelectionRI_Restriction_r16;
   u8/*SIZE(4)*/ typeII_PortSelectionRI_Restriction_r16;
   u8 padding[2];
}TypeII_PortSelection_r16_t;




typedef struct  {
   s32 choice;
#define	CodebookConfig_r16_CodebookType_Type2_SubType_typeII_r16_chosen	0
#define	CodebookConfig_r16_CodebookType_Type2_SubType_typeII_PortSelection_r16_chosen	1

   union {
      TypeII_r16_t typeII_r16;
      TypeII_PortSelection_r16_t typeII_PortSelection_r16;
   } value;
}CodebookConfig_r16_CodebookType_Type2_SubType_t;



typedef struct  {
   CodebookConfig_r16_CodebookType_Type2_SubType_t subType;
   u32 numberOfPMI_SubbandsPerCQI_Subband_r16;
   u32 paramCombination_r16;
}CodebookConfig_r16_CodebookType_Type2_t;


typedef struct  {
   s32 choice;
#define	CodebookConfig_r16_CodebookType_type2_chosen	0

   union {
      CodebookConfig_r16_CodebookType_Type2_t type2;
   } value;
}CodebookConfig_r16_CodebookType_t;


typedef struct  {
   CodebookConfig_r16_CodebookType_t codebookType;
}CodebookConfig_r16_t;

typedef  struct{
   s32 nrofReportedGroups_r17;/*enum NrofReportedGroups_r17_n1 = 0,
															   NrofReportedGroups_r17_n2 = 1,
															   NrofReportedGroups_r17_n3 = 2,
															   NrofReportedGroups_r17_n4 = 3*/
}GroupBasedBeamReporting_v1710_t;


typedef struct  {
   s16 choice;
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_two_one_TypeI_SinglePanel_Restriction1_r17_chosen	0
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_two_two_TypeI_SinglePanel_Restriction1_r17_chosen	1
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_one_TypeI_SinglePanel_Restriction1_r17_chosen	2
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_three_two_TypeI_SinglePanel_Restriction1_r17_chosen	3
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_six_one_TypeI_SinglePanel_Restriction1_r17_chosen	4
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_two_TypeI_SinglePanel_Restriction1_r17_chosen	5
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_eight_one_TypeI_SinglePanel_Restriction1_r17_chosen	6
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_three_TypeI_SinglePanel_Restriction1_r17_chosen	7
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_six_two_TypeI_SinglePanel_Restriction1_r17_chosen	8
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_twelve_one_TypeI_SinglePanel_Restriction1_r17_chosen	9
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_four_TypeI_SinglePanel_Restriction1_r17_chosen	10
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_eight_two_TypeI_SinglePanel_Restriction1_r17_chosen	11
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_sixteen_one_TypeI_SinglePanel_Restriction1_r17_chosen	12
    u16 num_bits_value;
   union {
      u8/*SIZE(8)*/ two_one_TypeI_SinglePanel_Restriction1_r17[1];
      u8/*SIZE(64)*/ two_two_TypeI_SinglePanel_Restriction1_r17[8];
      u8/*SIZE(16)*/ four_one_TypeI_SinglePanel_Restriction1_r17[2];
      u8/*SIZE(96)*/ three_two_TypeI_SinglePanel_Restriction1_r17[12];
      u8/*SIZE(24)*/ six_one_TypeI_SinglePanel_Restriction1_r17[3];
      u8/*SIZE(128)*/ four_two_TypeI_SinglePanel_Restriction1_r17[16];
      u8/*SIZE(32)*/ eight_one_TypeI_SinglePanel_Restriction1_r17[4];
      u8/*SIZE(192)*/ four_three_TypeI_SinglePanel_Restriction1_r17[24];
      u8/*SIZE(192)*/ six_two_TypeI_SinglePanel_Restriction1_r17[24];
      u8/*SIZE(48)*/ twelve_one_TypeI_SinglePanel_Restriction1_r17[6];
      u8/*SIZE(256)*/ four_four_TypeI_SinglePanel_Restriction1_r17[32];
      u8/*SIZE(256)*/ eight_two_TypeI_SinglePanel_Restriction1_r17[32];
      u8/*SIZE(64)*/ sixteen_one_TypeI_SinglePanel_Restriction1_r17[8];
   } value;
}TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_t;



typedef struct  {
    u8 num_bits_twoTX_CodebookSubsetRestriction1_r17;
    u8/*SIZE(6)*/ twoTX_CodebookSubsetRestriction1_r17;
    u16 padding;
}TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_Two_t;

typedef struct  {
   TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_t n1_n2;
}TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_t;



typedef struct  {
   s32 choice;
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_two_chosen	0
#define	TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_moreThanTwo_chosen	1

   union {
      TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_Two_t two;
      TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_MoreThanTwo_t moreThanTwo;
   } value;
}TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_t;


typedef struct  {
   TypeI_SinglePanel_Group1_r17_NrOfAntennaPorts_t nrOfAntennaPorts;
}TypeI_SinglePanel_Group1_r17_t;

typedef struct  {
   u8 num_bits_twoTX_CodebookSubsetRestriction2_r17;
   u8/*SIZE(6)*/ twoTX_CodebookSubsetRestriction2_r17;
   u8 padding[2];
}TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_Two_t;



typedef struct  {
   s16 choice;
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_two_one_TypeI_SinglePanel_Restriction2_r17_chosen	0
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_two_two_TypeI_SinglePanel_Restriction2_r17_chosen	1
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_one_TypeI_SinglePanel_Restriction2_r17_chosen	2
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_three_two_TypeI_SinglePanel_Restriction2_r17_chosen	3
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_six_one_TypeI_SinglePanel_Restriction2_r17_chosen	4
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_two_TypeI_SinglePanel_Restriction2_r17_chosen	5
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_eight_one_TypeI_SinglePanel_Restriction2_r17_chosen	6
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_three_TypeI_SinglePanel_Restriction2_r17_chosen	7
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_six_two_TypeI_SinglePanel_Restriction2_r17_chosen	8
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_twelve_one_TypeI_SinglePanel_Restriction2_r17_chosen	9
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_four_four_TypeI_SinglePanel_Restriction2_r17_chosen	10
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_eight_two_TypeI_SinglePanel_Restriction2_r17_chosen	11
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_sixteen_one_TypeI_SinglePanel_Restriction2_r17_chosen	12
    u16 num_bits_value;
   union {
      u8/*SIZE(8)*/ two_one_TypeI_SinglePanel_Restriction2_r17[1];
      u8/*SIZE(64)*/ two_two_TypeI_SinglePanel_Restriction2_r17[8];
      u8/*SIZE(16)*/ four_one_TypeI_SinglePanel_Restriction2_r17[2];
      u8/*SIZE(96)*/ three_two_TypeI_SinglePanel_Restriction2_r17[12];
      u8/*SIZE(24)*/ six_one_TypeI_SinglePanel_Restriction2_r17[3];
      u8/*SIZE(128)*/ four_two_TypeI_SinglePanel_Restriction2_r17[16];
      u8/*SIZE(32)*/ eight_one_TypeI_SinglePanel_Restriction2_r17[4];
      u8/*SIZE(192)*/ four_three_TypeI_SinglePanel_Restriction2_r17[24];
      u8/*SIZE(192)*/ six_two_TypeI_SinglePanel_Restriction2_r17[24];
      u8/*SIZE(48)*/ twelve_one_TypeI_SinglePanel_Restriction2_r17[6];
      u8/*SIZE(256)*/ four_four_TypeI_SinglePanel_Restriction2_r17[32];
      u8/*SIZE(256)*/ eight_two_TypeI_SinglePanel_Restriction2_r17[32];
      u8/*SIZE(64)*/ sixteen_one_TypeI_SinglePanel_Restriction2_r17[8];
   } value;
}TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_t;


typedef struct  {
   TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_N1_n2_t n1_n2;
}TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_t;



typedef struct  {
   s32 choice;
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_two_chosen	0
#define	TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_moreThanTwo_chosen	1

   union {
      TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_Two_t two;
      TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_MoreThanTwo_t moreThanTwo;
   } value;
}TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_t;



typedef struct  {
   TypeI_SinglePanel_Group2_r17_NrOfAntennaPorts_t nrOfAntennaPorts;
}TypeI_SinglePanel_Group2_r17_t;




typedef struct  {
    u16 typeI_SinglePanel_Group1_r17_valid:1;
    u16 typeI_SinglePanel_Group2_r17_valid:1;
    u16 typeI_SinglePanel_ri_RestrictionSTRP_r17_valid:1;
    u16 typeI_SinglePanel_ri_RestrictionSDM_r17_valid:1;
    u16 rsv:12;
    u16 padding;
   TypeI_SinglePanel_Group1_r17_t typeI_SinglePanel_Group1_r17;	/* OPTIONAL */
   TypeI_SinglePanel_Group2_r17_t typeI_SinglePanel_Group2_r17;	/* OPTIONAL */
   u8 num_bits_typeI_SinglePanel_ri_RestrictionSTRP_r17;
   u8 num_bits_typeI_SinglePanel_ri_RestrictionSDM_r17;
   u8/*SIZE(8)*/* typeI_SinglePanel_ri_RestrictionSTRP_r17;	/* OPTIONAL */
   u8/*SIZE(4)*/* typeI_SinglePanel_ri_RestrictionSDM_r17;	/* OPTIONAL */
}CodebookConfig_r17_CodebookType_Type1_t;


typedef struct  {
    u8 valueOfN_r17_valid:1;
    u8 numberOfPMI_SubbandsPerCQI_Subband_r17_valid:1;
    u8 rsv:6;
    u8 num_bits_typeII_PortSelectionRI_Restriction_r17;
    u8/*SIZE(4)*/ typeII_PortSelectionRI_Restriction_r17;
    u8 padding;
   u32 paramCombination_r17;
   s32 valueOfN_r17;	/* OPTIONAL enum ValueOfN_r17_n2 = 0,
   										 ValueOfN_r17_n4 = 1*/
   u32 numberOfPMI_SubbandsPerCQI_Subband_r17;	/* OPTIONAL */
}TypeII_PortSelection_r17_t;



typedef struct  {
   TypeII_PortSelection_r17_t typeII_PortSelection_r17;
}CodebookConfig_r17_CodebookType_Type2_t;



typedef struct  {
   s32 choice;
#define	CodebookConfig_r17_CodebookType_type1_chosen	0
#define	CodebookConfig_r17_CodebookType_type2_chosen	1

   union {
      CodebookConfig_r17_CodebookType_Type1_t type1;
      CodebookConfig_r17_CodebookType_Type2_t type2;
   } value;
}CodebookConfig_r17_CodebookType_t;



typedef struct  {
   CodebookConfig_r17_CodebookType_t codebookType;
}CodebookConfig_r17_t;




typedef struct  {
   s32 choice;
#define	ReportQuantity_r17_cri_RSRP_Index_r17_chosen	0
#define	ReportQuantity_r17_ssb_Index_RSRP_Index_r17_chosen	1
#define	ReportQuantity_r17_cri_SINR_Index_r17_chosen	2
#define	ReportQuantity_r17_ssb_Index_SINR_Index_r17_chosen	3
   union {
      s32 cri_RSRP_Index_r17;
      s32 ssb_Index_RSRP_Index_r17;
      s32 cri_SINR_Index_r17;
      s32 ssb_Index_SINR_Index_r17;
   } value;
}ReportQuantity_r17_t;

typedef struct  {
    u16 reportSlotOffsetList_r17_valid:1;
    u16 reportSlotOffsetListDCI_0_2_r17_valid:1;
    u16 reportSlotOffsetListDCI_0_1_r17_valid:1;
    u16 rsv:13;
    u16 padding;
   u32 num_of_reportSlotOffsetList_r17;//0..64
   u32 reportSlotOffsetList_r17[64];	/* OPTIONAL */

   u32 num_of_reportSlotOffsetListDCI_0_2_r17;//0..64
   u32 reportSlotOffsetListDCI_0_2_r17[64];	/* OPTIONAL */

   u32 num_of_reportSlotOffsetListDCI_0_1_r17; //0..64
   u32 reportSlotOffsetListDCI_0_1_r17[64];	/* OPTIONAL */
}SemiPersistentOnPUSCH_v1720_t;


typedef struct  {
    u16 reportSlotOffsetList_r17_valid:1;
    u16 reportSlotOffsetListDCI_0_2_r17_valid:1;
    u16 reportSlotOffsetListDCI_0_1_r17_valid:1;
    u16 rsv:13;
    u16 padding;
   u32 num_of_reportSlotOffsetList_r17;//0..64
   u32 reportSlotOffsetList_r17[64];	/* OPTIONAL */

   u32 num_of_reportSlotOffsetListDCI_0_2_r17;//0..64
   u32 reportSlotOffsetListDCI_0_2_r17[64];	/* OPTIONAL */

   u32 num_of_reportSlotOffsetListDCI_0_1_r17;//0..64
   u32 reportSlotOffsetListDCI_0_1_r17[64];	/* OPTIONAL */
}Aperiodic_v1720_t;

typedef struct  {
    u8 codebookMode_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 codebookMode;	/* OPTIONAL */
}CodebookConfig_v1730_CodebookType_Type1_t;




typedef struct  {
   s32 choice;
#define	CodebookConfig_v1730_CodebookType_type1_chosen	0

   union {
      CodebookConfig_v1730_CodebookType_Type1_t type1;
   } value;
}CodebookConfig_v1730_CodebookType_t;


typedef struct  {
   CodebookConfig_v1730_CodebookType_t codebookType;
}CodebookConfig_v1730_t;


typedef struct  {
   u32 carrier_valid:1;
   u32 csi_IM_ResourcesForInterference_valid:1;
   u32 nzp_CSI_RS_ResourcesForInterference_valid:1;
   u32 reportFreqConfiguration_valid:1;
   u32 codebookConfig_valid:1;
   u32 dummy_valid:1;
   u32 cqi_Table_valid:1;
   u32 non_PMI_PortIndication_valid:1;
   u32 semiPersistentOnPUSCH_v1530_valid:1;
   u32 semiPersistentOnPUSCH_v1610_valid:1;
   u32 aperiodic_v1610_valid:1;
   u32 reportQuantity_r16_valid:1;
   u32 codebookConfig_r16_valid:1;
   u32 cqi_BitsPerSubband_r17_valid:1;
   u32 groupBasedBeamReporting_v1710_valid:1;
   u32 codebookConfig_r17_valid:1;
   u32 sharedCMR_r17_valid:1;
   u32 csi_ReportMode_r17_valid:1;
   u32 numberOfSingleTRP_CSI_Mode1_r17_valid:1;
   u32 reportQuantity_r17_valid:1;
   u32 semiPersistentOnPUSCH_v1720_valid:1;
   u32 aperiodic_v1720_valid:1;
   u32 codebookConfig_v1730_valid:1;
   u32 rsv:9;
   u32 reportConfigId;
   u32 carrier;	/* OPTIONAL */
   u32 resourcesForChannelMeasurement;
   u32 csi_IM_ResourcesForInterference;	/* OPTIONAL */
   u32 nzp_CSI_RS_ResourcesForInterference;	/* OPTIONAL */
   ReportConfigType_t reportConfigType;
   ReportQuantity_t reportQuantity;
   ReportFreqConfiguration_t reportFreqConfiguration;	/* OPTIONAL */
   s32 timeRestrictionForChannelMeasurements; /*enum  TimeRestrictionForChannelMeasurements_configured = 0,
   																TimeRestrictionForChannelMeasurements_notConfigured = 1*/
   s32 timeRestrictionForInterferenceMeasurements; /*enum TimeRestrictionForInterferenceMeasurements_configured = 0,
   															TimeRestrictionForInterferenceMeasurements_notConfigured = 1*/
   CodebookConfig_t codebookConfig;	/* OPTIONAL */
   s32 dummy;	/* OPTIONAL enum CSI_ReportConfig_Dummy_n1 = 0,
   								CSI_ReportConfig_Dummy_n2 = 1*/
   GroupBasedBeamReporting_t groupBasedBeamReporting;
   s8 cqi_Table;	/* OPTIONAL enum Cqi_Table_table1 = 0,
								   Cqi_Table_table2 = 1,
								   Cqi_Table_table3 = 2,
								   Cqi_Table_table4_r17 = 3*/
   s8 subbandSize; /*enum SubbandSize_value1 = 0,
  							 SubbandSize_value2 = 1*/

   u32 num_of_non_PMI_PortIndication;//0..128
   PortIndexFor8Ranks_t *non_PMI_PortIndication[128];	/* OPTIONAL */
   SemiPersistentOnPUSCH_v1530_t semiPersistentOnPUSCH_v1530;	/* OPTIONAL */
   SemiPersistentOnPUSCH_v1610_t semiPersistentOnPUSCH_v1610;	/* OPTIONAL */
   Aperiodic_v1610_t aperiodic_v1610;	/* OPTIONAL */
   ReportQuantity_r16_t reportQuantity_r16;	/* OPTIONAL */
   CodebookConfig_r16_t codebookConfig_r16;	/* OPTIONAL */
   s32 cqi_BitsPerSubband_r17;	/* OPTIONAL enum Cqi_BitsPerSubband_r17_bits4 = 0 */
   GroupBasedBeamReporting_v1710_t groupBasedBeamReporting_v1710;	/* OPTIONAL */
   CodebookConfig_r17_t codebookConfig_r17;	/* OPTIONAL */
   s32 sharedCMR_r17;	/* OPTIONAL enum SharedCMR_r17_enable = 0*/
   s32 csi_ReportMode_r17;	/* OPTIONAL enum Csi_ReportMode_r17_mode1 = 0,
   																	Csi_ReportMode_r17_mode2 = 1 */
   s32 numberOfSingleTRP_CSI_Mode1_r17;	/* OPTIONAL enum NumberOfSingleTRP_CSI_Mode1_r17_n0 = 0,
													   NumberOfSingleTRP_CSI_Mode1_r17_n1 = 1,
													   NumberOfSingleTRP_CSI_Mode1_r17_n2 = 2 */
   ReportQuantity_r17_t reportQuantity_r17;	/* OPTIONAL */
   SemiPersistentOnPUSCH_v1720_t semiPersistentOnPUSCH_v1720;	/* OPTIONAL */
   Aperiodic_v1720_t aperiodic_v1720;	/* OPTIONAL */
   CodebookConfig_v1730_t codebookConfig_v1730;	/* OPTIONAL */
}CSI_ReportConfig_t;


typedef struct  {
    u8 qcl_info_valid:1;
    u8 rsv:7;
    u8 padding[3];
   u32 resourceSet;

   u32 num_of_qcl_info;//0..16
   u32 qcl_info[16];	/* OPTIONAL */
}Nzp_CSI_RS_t;



typedef struct  {
   s32 choice;
#define	ResourcesForChannel_nzp_CSI_RS_chosen	0
#define	ResourcesForChannel_csi_SSB_ResourceSet_chosen	1

   union {
      Nzp_CSI_RS_t nzp_CSI_RS;
      u32 csi_SSB_ResourceSet;
   } value;
}ResourcesForChannel_t;

typedef struct  {
    u32 qcl_info2_r17_valid:1;
    u32 rsv:31;
   u32 resourceSet2_r17;

   u32 num_of_qcl_info2_r17;//0..16
   u32 qcl_info2_r17[16];	/* OPTIONAL */
}Nzp_CSI_RS2_r17_t;




typedef struct  {
   s32 choice;
#define	ResourcesForChannel2_r17_nzp_CSI_RS2_r17_chosen	0
#define	ResourcesForChannel2_r17_csi_SSB_ResourceSet2_r17_chosen	1

   union {
      Nzp_CSI_RS2_r17_t nzp_CSI_RS2_r17;
      u32 csi_SSB_ResourceSet2_r17;
   } value;
}ResourcesForChannel2_r17_t;



typedef struct  {
    u32 csi_IM_ResourcesForInterference_valid:1;
    u32 nzp_CSI_RS_ResourcesForInterference_valid:1;
    u32 resourcesForChannel2_r17_valid:1;
    u32 csi_SSB_ResourceSetExt_valid:1;
    u32 rsv:28;
   u32 reportConfigId;
   ResourcesForChannel_t resourcesForChannel;
   u32 csi_IM_ResourcesForInterference;	/* OPTIONAL */
   u32 nzp_CSI_RS_ResourcesForInterference;	/* OPTIONAL */
   ResourcesForChannel2_r17_t resourcesForChannel2_r17;	/* OPTIONAL */
   u32 csi_SSB_ResourceSetExt;	/* OPTIONAL */
}CSI_AssociatedReportConfigInfo_t;


typedef struct  {
   u32 num_of_CSI_AssociatedReportConfigInfoList;//0..16
   CSI_AssociatedReportConfigInfo_t CSI_AssociatedReportConfigInfoList[16];
}CSI_AssociatedReportConfigInfo_list_t;


typedef struct  {
    u32 ap_CSI_MultiplexingMode_r17_valid:1;
    u32 rsv:31;
   CSI_AssociatedReportConfigInfo_list_t associatedReportConfigInfoList;
   s32 ap_CSI_MultiplexingMode_r17;	/* OPTIONAL enum  Ap_CSI_MultiplexingMode_r17_enabled = 0*/
}CSI_AperiodicTriggerState_t;


typedef struct  {
   u32 num_of_CSI_AperiodicTriggerStateList;//0..128
   CSI_AperiodicTriggerState_t CSI_AperiodicTriggerStateList[128];
}CSI_AperiodicTriggerStateList_t;



typedef struct  {
//   s32 choice;
//#define	AperiodicTriggerStateList_release_chosen	0
//#define	AperiodicTriggerStateList_setup_chosen	1

//   union {
//      s8 release;
      CSI_AperiodicTriggerStateList_t setup;
//   } value;
}AperiodicTriggerStateList_t;


typedef struct  {
    u32 sp_CSI_MultiplexingMode_r17_valid:1;
    u32 rsv:31;
   u32 associatedReportConfigInfo;
   s32 sp_CSI_MultiplexingMode_r17;	/* OPTIONAL enum Sp_CSI_MultiplexingMode_r17_enabled = 0 */
}CSI_SemiPersistentOnPUSCH_TriggerState_t;

typedef struct  {
	u32 num_of_CSI_SemiPersistentOnPUSCH_TriggerStateList;//0..64
    CSI_SemiPersistentOnPUSCH_TriggerState_t  CSI_SemiPersistentOnPUSCH_TriggerStateList[64];
}CSI_SemiPersistentOnPUSCH_TriggerStateList_t;




typedef struct  {
//   s32 choice;
//#define	SemiPersistentOnPUSCH_TriggerStateList_release_chosen	0
//#define	SemiPersistentOnPUSCH_TriggerStateList_setup_chosen	1

//   union {
//      s8 release;
      CSI_SemiPersistentOnPUSCH_TriggerStateList_t setup;
//   } value;
}SemiPersistentOnPUSCH_TriggerStateList_t;


typedef struct  {
    u32 gapBetweenBursts_r17_valid:1;
    u32 rsv:31;
   u32 scellActivationRS_Id_r17;
   u32 resourceSet_r17;
   u32 gapBetweenBursts_r17;	/* OPTIONAL */
   u32 qcl_Info_r17;
}SCellActivationRS_Config_r17_t;





typedef struct  {
    u32 reportTriggerSize_valid:1;
    u32 aperiodicTriggerStateList_valid:1;
    u32 semiPersistentOnPUSCH_TriggerStateList_valid:1;
    u32 reportTriggerSizeDCI_0_2_r16_valid:1;
    u32 rsv:28;
   u32 num_of_nzp_CSI_RS_ResourceToAddModList;//0..192
   NZP_CSI_RS_Resource_t *nzp_CSI_RS_ResourceToAddModList[192];	/* OPTIONAL */


   u32 num_of_nzp_CSI_RS_ResourceToReleaseList;//0..192
   u32 nzp_CSI_RS_ResourceToReleaseList[192];	/* OPTIONAL */

   u32 num_of_nzp_CSI_RS_ResourceSetToAddModList;//0..64
   NZP_CSI_RS_ResourceSet_t nzp_CSI_RS_ResourceSetToAddModList[64];	/* OPTIONAL */

   u32 num_of_nzp_CSI_RS_ResourceSetToReleaseList;//0..64
   u32 nzp_CSI_RS_ResourceSetToReleaseList[64];	/* OPTIONAL */

   u32 num_of_csi_IM_ResourceToAddModList;//0..32
   CSI_IM_Resource_t *csi_IM_ResourceToAddModList[32];	/* OPTIONAL */

   u32 num_of_csi_IM_ResourceToReleaseList;//0..32
   u32 csi_IM_ResourceToReleaseList[32];	/* OPTIONAL */

   u32 num_of_csi_IM_ResourceSetToAddModList;//0..64
   CSI_IM_ResourceSet_t *csi_IM_ResourceSetToAddModList[64];	/* OPTIONAL */

   u32 num_of_csi_IM_ResourceSetToReleaseList;//0..64
   u32 csi_IM_ResourceSetToReleaseList[64];	/* OPTIONAL */

   u32 num_of_csi_SSB_ResourceSetToAddModList;//0..64
   CSI_SSB_ResourceSet_t *csi_SSB_ResourceSetToAddModList[64];	/* OPTIONAL */

   u32 num_of_csi_SSB_ResourceSetToReleaseList;//0..64
   u32 csi_SSB_ResourceSetToReleaseList[64];	/* OPTIONAL */

   u32 num_of_csi_ResourceConfigToAddModList;//0.112
   CSI_ResourceConfig_t *csi_ResourceConfigToAddModList[112];	/* OPTIONAL */

   u32 num_of_csi_ResourceConfigToReleaseList;//0..112
   u32 csi_ResourceConfigToReleaseList[112];	/* OPTIONAL */

   u32 num_of_csi_ReportConfigToAddModList;//0..48
   CSI_ReportConfig_t *csi_ReportConfigToAddModList[48];	/* OPTIONAL */

   u32 num_of_csi_ReportConfigToReleaseList;//0..48
   u32 csi_ReportConfigToReleaseList[48];	/* OPTIONAL */

   u32 reportTriggerSize;	/* OPTIONAL */
   AperiodicTriggerStateList_t *aperiodicTriggerStateList;	/* OPTIONAL */
   SemiPersistentOnPUSCH_TriggerStateList_t *semiPersistentOnPUSCH_TriggerStateList;	/* OPTIONAL */
   u32 reportTriggerSizeDCI_0_2_r16;	/* OPTIONAL */

   u32 num_of_sCellActivationRS_ConfigToAddModList_r17;//0..255
   SCellActivationRS_Config_r17_t *sCellActivationRS_ConfigToAddModList_r17[255];	/* OPTIONAL */

   u32 num_of_sCellActivationRS_ConfigToReleaseList_r17;//0..255
   u32  sCellActivationRS_ConfigToReleaseList_r17[255];	/* OPTIONAL */
}CSI_MeasConfig_t;



typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_Csi_MeasConfig_release_chosen	0
//#define	ServingCellConfig_Csi_MeasConfig_setup_chosen	1

//   union {
//      s8 release;
      CSI_MeasConfig_t setup;
//   } value;
}ServingCellConfig_Csi_MeasConfig_t;


typedef struct  {
   BOOL cif_Presence;
}Own_t;

typedef struct  {
   u32 schedulingCellId;
   u32 cif_InSchedulingCell;
}Other_t;




typedef struct  {
   s32 choice;
#define	SchedulingCellInfo_own_chosen	0
#define	SchedulingCellInfo_other_chosen	1

   union {
      Own_t own;
      Other_t other;
   } value;
}SchedulingCellInfo_t;

typedef struct  {
   u32 carrierIndicatorSizeDCI_1_2_r16;
   u32 carrierIndicatorSizeDCI_0_2_r16;
}CarrierIndicatorSize_r16_t;




typedef struct  {
    u32 carrierIndicatorSize_r16_valid:1;
    u32 enableDefaultBeamForCCS_r16_valid:1;
    u32 ccs_BlindDetectionSplit_r17_valid:1;
    u32 rsv:29;
   SchedulingCellInfo_t schedulingCellInfo;
   CarrierIndicatorSize_r16_t carrierIndicatorSize_r16;	/* OPTIONAL */
   s32 enableDefaultBeamForCCS_r16;	/* OPTIONAL enum EnableDefaultBeamForCCS_r16_enabled = 0 */
   s32 ccs_BlindDetectionSplit_r17;	/* OPTIONAL enum  Ccs_BlindDetectionSplit_r17_oneSeventh = 0,
													   Ccs_BlindDetectionSplit_r17_threeFourteenth = 1,
													   Ccs_BlindDetectionSplit_r17_twoSeventh = 2,
													   Ccs_BlindDetectionSplit_r17_threeSeventh = 3,
													   Ccs_BlindDetectionSplit_r17_oneHalf = 4,
													   Ccs_BlindDetectionSplit_r17_fourSeventh = 5,
													   Ccs_BlindDetectionSplit_r17_fiveSeventh = 6,
													   Ccs_BlindDetectionSplit_r17_spare1 = 7 */
}CrossCarrierSchedulingConfig_t;




typedef struct  {
   s32 choice;
   
#define	SubframeAllocation1_oneFrame_chosen	0
#define	SubframeAllocation1_fourFrames_chosen	1

   union {
      BITS/*SIZE(6)*/ oneFrame;
      BITS/*SIZE(24)*/ fourFrames;
   } value;
}SubframeAllocation1_t;


typedef struct  {
   s32 choice;
#define	SubframeAllocation2_oneFrame_chosen	0
#define	SubframeAllocation2_fourFrames_chosen	1

   union {
      BITS/*SIZE(2)*/ oneFrame;
      BITS/*SIZE(8)*/ fourFrames;
   } value;
}SubframeAllocation2_t;



typedef struct  {
   s32 radioframeAllocationPeriod; /*enum  RadioframeAllocationPeriod_n1 = 0,
										   RadioframeAllocationPeriod_n2 = 1,
										   RadioframeAllocationPeriod_n4 = 2,
										   RadioframeAllocationPeriod_n8 = 3,
										   RadioframeAllocationPeriod_n16 = 4,
										   RadioframeAllocationPeriod_n32 = 5*/
   u32 radioframeAllocationOffset;
   SubframeAllocation1_t subframeAllocation1;
   SubframeAllocation2_t subframeAllocation2;	/* OPTIONAL */
}EUTRA_MBSFN_SubframeConfig_t;




typedef struct  {
   u32 carrierFreqDL;
   s32 carrierBandwidthDL; /*enum CarrierBandwidthDL_n6 = 0,
								   CarrierBandwidthDL_n15 = 1,
								   CarrierBandwidthDL_n25 = 2,
								   CarrierBandwidthDL_n50 = 3,
								   CarrierBandwidthDL_n75 = 4,
								   CarrierBandwidthDL_n100 = 5,
								   CarrierBandwidthDL_spare2 = 6,
								   CarrierBandwidthDL_spare1 = 7*/
   u32 num_of_mbsfn_SubframeConfigList;//0..8
   EUTRA_MBSFN_SubframeConfig_t mbsfn_SubframeConfigList[8];	/* OPTIONAL */
   s32 nrofCRS_Ports; /*enum  NrofCRS_Ports_n1 = 0,
								   NrofCRS_Ports_n2 = 1,
								   NrofCRS_Ports_n4 = 2*/
   s32 v_Shift;  /*enum    V_Shift_n0 = 0,
						   V_Shift_n1 = 1,
						   V_Shift_n2 = 2,
						   V_Shift_n3 = 3,
						   V_Shift_n4 = 4,
						   V_Shift_n5 = 5*/
}RateMatchPatternLTE_CRS_t;



typedef struct  {
   s32 choice;
#define	ServingCellConfig_Lte_CRS_ToMatchAround_release_chosen	0
#define	ServingCellConfig_Lte_CRS_ToMatchAround_setup_chosen	1

   union {
      s8 release;
      RateMatchPatternLTE_CRS_t setup;
   } value;
}ServingCellConfig_Lte_CRS_ToMatchAround_t;




typedef struct  {
   s32 choice;
#define	PeriodicityAndPattern_n2_chosen	0
#define	PeriodicityAndPattern_n4_chosen	1
#define	PeriodicityAndPattern_n5_chosen	2
#define	PeriodicityAndPattern_n8_chosen	3
#define	PeriodicityAndPattern_n10_chosen	4
#define	PeriodicityAndPattern_n20_chosen	5
#define	PeriodicityAndPattern_n40_chosen	6

   union {
      BITS/*SIZE(2)*/ n2;
      BITS/*SIZE(4)*/ n4;
      BITS/*SIZE(5)*/ n5;
      BITS/*SIZE(8)*/ n8;
      BITS/*SIZE(10)*/ n10;
      BITS/*SIZE(20)*/ n20;
      BITS/*SIZE(40)*/ n40;
   } value;
}PeriodicityAndPattern_t;




typedef struct  {
   s32 choice;
#define	SymbolsInResourceBlock_oneSlot_chosen	0
#define	SymbolsInResourceBlock_twoSlots_chosen	1

   union {
      BITS/*SIZE(14)*/ oneSlot;
      BITS/*SIZE(28)*/ twoSlots;
   } value;
}SymbolsInResourceBlock_t;



typedef struct  {
   BITS/*SIZE(275)*/ resourceBlocks;
   SymbolsInResourceBlock_t symbolsInResourceBlock;
   PeriodicityAndPattern_t periodicityAndPattern;	/* OPTIONAL */
}Bitmaps_t;



typedef struct  {
   s32 choice;
#define	PatternType_bitmaps_chosen	0
#define	PatternType_controlResourceSet_chosen	1

   union {
      Bitmaps_t bitmaps;
      u32 controlResourceSet;
   } value;
}PatternType_t;





typedef struct  {
   u32 rateMatchPatternId;
   PatternType_t patternType;
   s32 subcarrierSpacing;	/* OPTIONAL enum  SubcarrierSpacing_kHz15 = 0,
											   SubcarrierSpacing_kHz30 = 1,
											   SubcarrierSpacing_kHz60 = 2,
											   SubcarrierSpacing_kHz120 = 3,
											   SubcarrierSpacing_kHz240 = 4,
											   SubcarrierSpacing_kHz480_v1700 = 5,
											   SubcarrierSpacing_kHz960_v1700 = 6,
											   SubcarrierSpacing_spare1 = 7*/
   s32 dummy; /*enum Dummy_dynamic = 0,
  					 Dummy_semiStatic = 1*/
   u32  controlResourceSet_r16;	/* OPTIONAL */
}RateMatchPattern_t;

typedef struct  {
   u32 nrofDownlinkSymbols_r16;	/* OPTIONAL */
   u32 nrofUplinkSymbols_r16;	/* OPTIONAL */
}Explicit_r16_t;


typedef struct  {
   u32 nrofDownlinkSymbols_r16;	/* OPTIONAL */
   u32 nrofUplinkSymbols_r16;	/* OPTIONAL */
}Explicit_IAB_MT_r16_t;



typedef struct  {
   s32 choice;
#define	Symbols_IAB_MT_r16_allDownlink_r16_chosen	0
#define	Symbols_IAB_MT_r16_allUplink_r16_chosen	1
#define	Symbols_IAB_MT_r16_explicit_r16_chosen	2
#define	Symbols_IAB_MT_r16_explicit_IAB_MT_r16_chosen	3

   union {
      s8 allDownlink_r16;
      s8 allUplink_r16;
      Explicit_r16_t explicit_r16;
      Explicit_IAB_MT_r16_t explicit_IAB_MT_r16;
   } value;
}Symbols_IAB_MT_r16_t;


typedef struct  {
   u32 slotIndex_r16;
   Symbols_IAB_MT_r16_t symbols_IAB_MT_r16;
}TDD_UL_DL_SlotConfig_IAB_MT_r16_t;



typedef struct  {
	u32 num_of_slotSpecificConfigurationsToAddModList_IAB_MT_r16;//0..320
   TDD_UL_DL_SlotConfig_IAB_MT_r16_t slotSpecificConfigurationsToAddModList_IAB_MT_r16[320];	/* OPTIONAL */

   u32 num_of_slotSpecificConfigurationsToReleaseList_IAB_MT_r16;//0..320
   u32 slotSpecificConfigurationsToReleaseList_IAB_MT_r16[320];	/* OPTIONAL */
}TDD_UL_DL_ConfigDedicated_IAB_MT_r16_t;


typedef struct  {
   u32 firstWithinActiveTimeBWP_Id_r16_valid:1;
   u32 dormancyGroupWithinActiveTime_r16_valid:1;
   u32 rsv:30;
   u32 firstWithinActiveTimeBWP_Id_r16;	/* OPTIONAL */
   u32 dormancyGroupWithinActiveTime_r16;	/* OPTIONAL */
}WithinActiveTimeConfig_r16_t;




typedef struct  {
//   s32 choice;
//#define	DormantBWP_Config_r16_WithinActiveTimeConfig_r16_release_chosen	0
//#define	DormantBWP_Config_r16_WithinActiveTimeConfig_r16_setup_chosen	1

//   union {
//      s8 release;
      WithinActiveTimeConfig_r16_t setup;
//   } value;
}DormantBWP_Config_r16_WithinActiveTimeConfig_r16_t;


typedef struct  {
   u32 firstOutsideActiveTimeBWP_Id_r16_valid:1;
   u32 dormancyGroupOutsideActiveTime_r16_valid:1;
   u32 rsv:30;
   u32 firstOutsideActiveTimeBWP_Id_r16;	/* OPTIONAL */
   u32 dormancyGroupOutsideActiveTime_r16;	/* OPTIONAL */
}OutsideActiveTimeConfig_r16_t;



typedef struct  {
//   s32 choice;
//#define	DormantBWP_Config_r16_OutsideActiveTimeConfig_r16_release_chosen	0
//#define	DormantBWP_Config_r16_OutsideActiveTimeConfig_r16_setup_chosen	1

//   union {
//      s8 release;
      OutsideActiveTimeConfig_r16_t setup;
//   } value;
}DormantBWP_Config_r16_OutsideActiveTimeConfig_r16_t;





typedef struct  {
   u32 dormantBWP_Id_r16_valid:1;
   u32 withinActiveTimeConfig_r16_valid:1;
   u32 outsideActiveTimeConfig_r16_valid:1;
   u32 rsv:29;
   u32 dormantBWP_Id_r16;	/* OPTIONAL */
   DormantBWP_Config_r16_WithinActiveTimeConfig_r16_t withinActiveTimeConfig_r16;	/* OPTIONAL */
   DormantBWP_Config_r16_OutsideActiveTimeConfig_r16_t outsideActiveTimeConfig_r16;	/* OPTIONAL */
}DormantBWP_Config_r16_t;



typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_DormantBWP_Config_r16_release_chosen	0
//#define	ServingCellConfig_DormantBWP_Config_r16_setup_chosen	1

//   union {
//      s8 release;
      DormantBWP_Config_r16_t setup;
//   } value;
}ServingCellConfig_DormantBWP_Config_r16_t;




typedef struct  {
   s32 choice;
#define	Ca_SlotOffset_r16_refSCS15kHz_chosen	0
#define	Ca_SlotOffset_r16_refSCS30KHz_chosen	1
#define	Ca_SlotOffset_r16_refSCS60KHz_chosen	2
#define	Ca_SlotOffset_r16_refSCS120KHz_chosen	3

   union {
      s32 refSCS15kHz;
      s32 refSCS30KHz;
      s32 refSCS60KHz;
      s32 refSCS120KHz;
   } value;
}Ca_SlotOffset_r16_t;

typedef struct  {
    u32 ul_toDL_COT_SharingED_Threshold_r16_valid:1;
    u32 absenceOfAnyOtherTechnology_r16_valid:1;
    u32 rsv:30;
   s32 maxEnergyDetectionThreshold_r16;
   s32 energyDetectionThresholdOffset_r16;
   s32 ul_toDL_COT_SharingED_Threshold_r16;	/* OPTIONAL */
   s32 absenceOfAnyOtherTechnology_r16;	/* OPTIONAL enum AbsenceOfAnyOtherTechnology_r16_true = 0 */
}DummyJ_t;




typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_Dummy2_release_chosen	0
//#define	ServingCellConfig_Dummy2_setup_chosen	1

//   union {
//      s8 release;
      DummyJ_t setup;
//   } value;
}ServingCellConfig_Dummy2_t;

typedef struct  {
   u32 startCRB_r16;
   u32 nrofCRBs_r16;
}GuardBand_r16_t;




typedef struct  {
   s32 guardBandSCS_r16; /*SubcarrierSpacing_kHz15 = 0,
						   SubcarrierSpacing_kHz30 = 1,
						   SubcarrierSpacing_kHz60 = 2,
						   SubcarrierSpacing_kHz120 = 3,
						   SubcarrierSpacing_kHz240 = 4,
						   SubcarrierSpacing_kHz480_v1700 = 5,
						   SubcarrierSpacing_kHz960_v1700 = 6,
						   SubcarrierSpacing_spare1 = 7*/

   u32 num_of_intraCellGuardBands_r16;//0..4
   GuardBand_r16_t intraCellGuardBands_r16[4];
}IntraCellGuardBandsPerSCS_r16_t;


typedef struct  {
   u32 num_of_RateMatchPatternLTE_CRS_list;//0..3
   RateMatchPatternLTE_CRS_t RateMatchPatternLTE_CRS_list[3];
}RateMatchPatternLTE_CRS_list_t;



typedef struct  {
   s32 choice;
#define	Lte_CRS_PatternList1_r16_release_chosen	0
#define	Lte_CRS_PatternList1_r16_setup_chosen	1

   union {
      s8 release;
      RateMatchPatternLTE_CRS_list_t setup;
   } value;
}Lte_CRS_PatternList1_r16_t;






typedef struct  {
   s32 choice;
#define	Lte_CRS_PatternList2_r16_release_chosen	0
#define	Lte_CRS_PatternList2_r16_setup_chosen	1

   union {
      s8 release;
      RateMatchPatternLTE_CRS_list_t setup;
   } value;
}Lte_CRS_PatternList2_r16_t;

typedef struct  {
   s32 choice;
   union {
      s32 maxEnergyDetectionThreshold_r16;
      s32 energyDetectionThresholdOffset_r16;
   } value;
}EnergyDetectionConfig_r16_t;




typedef struct  {
   u32 energyDetectionConfig_r16_valid:1;
   u32 ul_toDL_COT_SharingED_Threshold_r16_valid:1;
   u32 absenceOfAnyOtherTechnology_r16_valid:1;
   u32 rsv:29;
   EnergyDetectionConfig_r16_t energyDetectionConfig_r16;	/* OPTIONAL */
   s32 ul_toDL_COT_SharingED_Threshold_r16;	/* OPTIONAL */
   s32 absenceOfAnyOtherTechnology_r16;	/* OPTIONAL enum ChannelAccessConfig_r16_AbsenceOfAnyOtherTechnology_r16_true = 0 */
}ChannelAccessConfig_r16_t;



typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_ChannelAccessConfig_r16_release_chosen	0
//#define	ServingCellConfig_ChannelAccessConfig_r16_setup_chosen	1

//   union {
//      s8 release;
      ChannelAccessConfig_r16_t setup;
//   } value;
}ServingCellConfig_ChannelAccessConfig_r16_t;




typedef struct  {
   int choice;
#define	Scs15_r17_n4_r17_chosen	0
#define	Scs15_r17_n5_r17_chosen	1
#define	Scs15_r17_n8_r17_chosen	2
#define	Scs15_r17_n10_r17_chosen	3
#define	Scs15_r17_n16_r17_chosen	4
#define	Scs15_r17_n20_r17_chosen	5
#define	Scs15_r17_n32_r17_chosen	6
#define	Scs15_r17_n40_r17_chosen	7
#define	Scs15_r17_n64_r17_chosen	8
#define	Scs15_r17_n80_r17_chosen	9
#define	Scs15_r17_n160_r17_chosen	10
#define	Scs15_r17_n320_r17_chosen	11
#define	Scs15_r17_n640_r17_chosen	12
#define	Scs15_r17_n1280_r17_chosen	13
#define	Scs15_r17_n2560_r17_chosen	14
#define	Scs15_r17_n5120_r17_chosen	15
#define	Scs15_r17_n10240_r17_chosen	16

   union {
      u32 n4_r17;
      u32 n5_r17;
      u32 n8_r17;
      u32 n10_r17;
      u32 n16_r17;
      u32 n20_r17;
      u32 n32_r17;
      u32 n40_r17;
      u32 n64_r17;
      u32 n80_r17;
      u32 n160_r17;
      u32 n320_r17;
      u32 n640_r17;
      u32 n1280_r17;
      u32 n2560_r17;
      u32 n5120_r17;
      u32 n10240_r17;
   } value;
}Scs15_r17_t;




typedef struct  {
   s32 choice;
#define	Scs30_r17_n8_r17_chosen	0
#define	Scs30_r17_n10_r17_chosen	1
#define	Scs30_r17_n16_r17_chosen	2
#define	Scs30_r17_n20_r17_chosen	3
#define	Scs30_r17_n32_r17_chosen	4
#define	Scs30_r17_n40_r17_chosen	5
#define	Scs30_r17_n64_r17_chosen	6
#define	Scs30_r17_n80_r17_chosen	7
#define	Scs30_r17_n128_r17_chosen	8
#define	Scs30_r17_n160_r17_chosen	9
#define	Scs30_r17_n320_r17_chosen	10
#define	Scs30_r17_n640_r17_chosen	11
#define	Scs30_r17_n1280_r17_chosen	12
#define	Scs30_r17_n2560_r17_chosen	13
#define	Scs30_r17_n5120_r17_chosen	14
#define	Scs30_r17_n10240_r17_chosen	15
#define	Scs30_r17_n20480_r17_chosen	16

   union {
      u32 n8_r17;
      u32 n10_r17;
      u32 n16_r17;
      u32 n20_r17;
      u32 n32_r17;
      u32 n40_r17;
      u32 n64_r17;
      u32 n80_r17;
      u32 n128_r17;
      u32 n160_r17;
      u32 n320_r17;
      u32 n640_r17;
      u32 n1280_r17;
      u32 n2560_r17;
      u32 n5120_r17;
      u32 n10240_r17;
      u32 n20480_r17;
   } value;
}Scs30_r17_t;




typedef struct  {
   s32 choice;
#define	Scs60_r17_n16_r17_chosen	0
#define	Scs60_r17_n20_r17_chosen	1
#define	Scs60_r17_n32_r17_chosen	2
#define	Scs60_r17_n40_r17_chosen	3
#define	Scs60_r17_n64_r17_chosen	4
#define	Scs60_r17_n80_r17_chosen	5
#define	Scs60_r17_n128_r17_chosen	6
#define	Scs60_r17_n160_r17_chosen	7
#define	Scs60_r17_n256_r17_chosen	8
#define	Scs60_r17_n320_r17_chosen	9
#define	Scs60_r17_n640_r17_chosen	10
#define	Scs60_r17_n1280_r17_chosen	11
#define	Scs60_r17_n2560_r17_chosen	12
#define	Scs60_r17_n5120_r17_chosen	13
#define	Scs60_r17_n10240_r17_chosen	14
#define	Scs60_r17_n20480_r17_chosen	15
#define	Scs60_r17_n40960_r17_chosen	16

   union {
      u32 n16_r17;
      u32 n20_r17;
      u32 n32_r17;
      u32 n40_r17;
      u32 n64_r17;
      u32 n80_r17;
      u32 n128_r17;
      u32 n160_r17;
      u32 n256_r17;
      u32 n320_r17;
      u32 n640_r17;
      u32 n1280_r17;
      u32 n2560_r17;
      u32 n5120_r17;
      u32 n10240_r17;
      u32 n20480_r17;
      u32 n40960_r17;
   } value;
}Scs60_r17_t;





typedef struct  {
   s32 choice;
#define	Scs120_r17_n32_r17_chosen	0
#define	Scs120_r17_n40_r17_chosen	1
#define	Scs120_r17_n64_r17_chosen	2
#define	Scs120_r17_n80_r17_chosen	3
#define	Scs120_r17_n128_r17_chosen	4
#define	Scs120_r17_n160_r17_chosen	5
#define	Scs120_r17_n256_r17_chosen	6
#define	Scs120_r17_n320_r17_chosen	7
#define	Scs120_r17_n512_r17_chosen	8
#define	Scs120_r17_n640_r17_chosen	9
#define	Scs120_r17_n1280_r17_chosen	10
#define	Scs120_r17_n2560_r17_chosen	11
#define	Scs120_r17_n5120_r17_chosen	12
#define	Scs120_r17_n10240_r17_chosen	13
#define	Scs120_r17_n20480_r17_chosen	14
#define	Scs120_r17_n40960_r17_chosen	15
#define	Scs120_r17_n81920_r17_chosen	16

   union {
      u32 n32_r17;
      u32 n40_r17;
      u32 n64_r17;
      u32 n80_r17;
      u32 n128_r17;
      u32 n160_r17;
      u32 n256_r17;
      u32 n320_r17;
      u32 n512_r17;
      u32 n640_r17;
      u32 n1280_r17;
      u32 n2560_r17;
      u32 n5120_r17;
      u32 n10240_r17;
      u32 n20480_r17;
      u32 n40960_r17;
      u64 n81920_r17;
   } value;
}Scs120_r17_t;



typedef struct  {
   s32 choice;
#define	NR_DL_PRS_Periodicity_and_ResourceSetSlotOffset_r17_scs15_r17_chosen	0
#define	NR_DL_PRS_Periodicity_and_ResourceSetSlotOffset_r17_scs30_r17_chosen	1
#define	NR_DL_PRS_Periodicity_and_ResourceSetSlotOffset_r17_scs60_r17_chosen	2
#define	NR_DL_PRS_Periodicity_and_ResourceSetSlotOffset_r17_scs120_r17_chosen	3

   union {
      Scs15_r17_t scs15_r17;
      Scs30_r17_t scs30_r17;
      Scs60_r17_t scs60_r17;
      Scs120_r17_t scs120_r17;
   } value;
}NR_DL_PRS_Periodicity_and_ResourceSetSlotOffset_r17_t;


typedef struct  {
   u32 ssb_Index_r17;
   s32 rs_Type_r17; /*enum Rs_Type_r17_typeC = 0,
						   Rs_Type_r17_typeD = 1,
						   Rs_Type_r17_typeC_plus_typeD = 2*/
}Ssb_r17_t;

typedef struct  {
   u32 qcl_DL_PRS_ResourceID_r17;
}Dl_PRS_r17_t;




typedef struct  {
   s32 choice;
#define	DL_PRS_QCL_Info_r17_ssb_r17_chosen	0
#define	DL_PRS_QCL_Info_r17_dl_PRS_r17_chosen	1

   union {
      Ssb_r17_t ssb_r17;
      Dl_PRS_r17_t dl_PRS_r17;
   } value;
}DL_PRS_QCL_Info_r17_t;



typedef struct  {
   s32 choice;
#define	Dl_PRS_CombSizeN_AndReOffset_r17_n2_r17_chosen	0
#define	Dl_PRS_CombSizeN_AndReOffset_r17_n4_r17_chosen	1
#define	Dl_PRS_CombSizeN_AndReOffset_r17_n6_r17_chosen	2
#define	Dl_PRS_CombSizeN_AndReOffset_r17_n12_r17_chosen	3

   union {
      u32 n2_r17;
      u32 n4_r17;
      u32 n6_r17;
      u32 n12_r17;
   } value;
}Dl_PRS_CombSizeN_AndReOffset_r17_t;




typedef struct  {
    u32 dl_PRS_QCL_Info_r17_valid:1;
    u32 rsv:31;
   u32 nr_DL_PRS_ResourceID_r17;
   u32 dl_PRS_SequenceID_r17;
   Dl_PRS_CombSizeN_AndReOffset_r17_t dl_PRS_CombSizeN_AndReOffset_r17;
   u32 dl_PRS_ResourceSlotOffset_r17;
   u32 dl_PRS_ResourceSymbolOffset_r17;
   DL_PRS_QCL_Info_r17_t dl_PRS_QCL_Info_r17;	/* OPTIONAL */
}NR_DL_PRS_Resource_r17_t;



typedef struct  {
   s32 repetitionFactor_r17; /*enum    RepFactorAndTimeGap_r17_RepetitionFactor_r17_n2 = 0,
															   RepFactorAndTimeGap_r17_RepetitionFactor_r17_n4 = 1,
															   RepFactorAndTimeGap_r17_RepetitionFactor_r17_n6 = 2,
															   RepFactorAndTimeGap_r17_RepetitionFactor_r17_n8 = 3,
															   RepFactorAndTimeGap_r17_RepetitionFactor_r17_n16 = 4,
															   RepFactorAndTimeGap_r17_RepetitionFactor_r17_n32 = 5,
															   RepFactorAndTimeGap_r17_RepetitionFactor_r17_spare2 = 6,
															   RepFactorAndTimeGap_r17_RepetitionFactor_r17_spare1 = 7*/
   s32 timeGap_r17;/*enum TimeGap_r17_s1 = 0,
						   TimeGap_r17_s2 = 1,
						   TimeGap_r17_s4 = 2,
						   TimeGap_r17_s8 = 3,
						   TimeGap_r17_s16 = 4,
						   TimeGap_r17_s32 = 5,
						   TimeGap_r17_spare2 = 6,
						   TimeGap_r17_spare1 = 7*/
}RepFactorAndTimeGap_r17_t;




typedef struct  {
   u32 repFactorAndTimeGap_r17_valid:1;
   u32 rsv:31;
   NR_DL_PRS_Periodicity_and_ResourceSetSlotOffset_r17_t periodicityAndOffset_r17;
   s32 numSymbols_r17; /*enum  NumSymbols_r17_n2 = 0,
											   NumSymbols_r17_n4 = 1,
											   NumSymbols_r17_n6 = 2,
											   NumSymbols_r17_n12 = 3,
											   NumSymbols_r17_spare4 = 4,
											   NumSymbols_r17_spare3 = 5,
											   NumSymbols_r17_spare2 = 6,
											   NumSymbols_r17_spare1 = 7*/
   u32 dl_PRS_ResourceBandwidth_r17;
   u32 dl_PRS_StartPRB_r17;

   u32 num_of_resourceList_r17;//0..64
   NR_DL_PRS_Resource_r17_t resourceList_r17[64];
   RepFactorAndTimeGap_r17_t repFactorAndTimeGap_r17;	/* OPTIONAL */
}NR_DL_PRS_PDC_ResourceSet_r17_t;



typedef struct  {
    u32 nr_DL_PRS_PDC_ResourceSet_r17_valid:1;
    u32 rsv:31;
   NR_DL_PRS_PDC_ResourceSet_r17_t nr_DL_PRS_PDC_ResourceSet_r17;	/* OPTIONAL */
}NR_DL_PRS_PDC_Info_r17_t;




typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_Nr_dl_PRS_PDC_Info_r17_release_chosen	0
//#define	ServingCellConfig_Nr_dl_PRS_PDC_Info_r17_setup_chosen	1

//   union {
//      s8 release;
      NR_DL_PRS_PDC_Info_r17_t setup;
//   } value;
}ServingCellConfig_Nr_dl_PRS_PDC_Info_r17_t;

typedef struct  {
   s32 periodUE_r17; /*enum PeriodUE_r17_ms1 = 0,
										   PeriodUE_r17_ms2 = 1,
										   PeriodUE_r17_ms2dot5 = 2,
										   PeriodUE_r17_ms4 = 3,
										   PeriodUE_r17_ms5 = 4,
										   PeriodUE_r17_ms10 = 5,
										   PeriodUE_r17_spare2 = 6,
										   PeriodUE_r17_spare1 = 7*/
   u32 offsetUE_r17;
}SemiStaticChannelAccessConfigUE_r17_t;



typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_SemiStaticChannelAccessConfigUE_r17_release_chosen	0
//#define	ServingCellConfig_SemiStaticChannelAccessConfigUE_r17_setup_chosen	1

//   union {
//      s8 release;
      SemiStaticChannelAccessConfigUE_r17_t setup;
//   } value;
}ServingCellConfig_SemiStaticChannelAccessConfigUE_r17_t;



typedef struct  {
   s16 choice;
   u16 num_bits_value;
   union {
      u8/*SIZE(4)*/ shortBitmap;
      u8/*SIZE(8)*/ mediumBitmap;
      u8/*SIZE(64)*/ longBitmap[8];
   } value;
}Ssb_PositionsInBurst_r17_t;



typedef struct  {
   u32 additionalPCIIndex_r17;
   u32 additionalPCI_r17;
   s32 periodicity_r17; /*enum  Periodicity_r17_ms5 = 0,
								   Periodicity_r17_ms10 = 1,
								   Periodicity_r17_ms20 = 2,
								   Periodicity_r17_ms40 = 3,
								   Periodicity_r17_ms80 = 4,
								   Periodicity_r17_ms160 = 5,
								   Periodicity_r17_spare2 = 6,
								   Periodicity_r17_spare1 = 7*/
   Ssb_PositionsInBurst_r17_t ssb_PositionsInBurst_r17;
   s32 ss_PBCH_BlockPower_r17;
}SSB_MTC_AdditionalPCI_r17_t;



typedef struct  {
   u32 p0_r17_valid:1;
   u32 alpha_r17_valid:1;
   u32 rsv:30;
   s32 p0_r17;	/* OPTIONAL */
   s32 alpha_r17;	/* OPTIONAL enum Alpha_alpha0 = 0,
									   Alpha_alpha04 = 1,
									   Alpha_alpha05 = 2,
									   Alpha_alpha06 = 3,
									   Alpha_alpha07 = 4,
									   Alpha_alpha08 = 5,
									   Alpha_alpha09 = 6,
									   Alpha_alpha1 = 7*/
   s32 closedLoopIndex_r17; /*enum   ClosedLoopIndex_r17_i0 = 0,
  										 ClosedLoopIndex_r17_i1 = 1*/ 
}P0AlphaSet_r17_t;


typedef struct  {
   u32 p0AlphaSetforPUSCH_r17_valid:1;
   u32 p0AlphaSetforPUCCH_r17_valid:1;
   u32 p0AlphaSetforSRS_r17_valid:1;
   u32 rsv:29;
   u32 ul_powercontrolId_r17;
   P0AlphaSet_r17_t p0AlphaSetforPUSCH_r17;	/* OPTIONAL */
   P0AlphaSet_r17_t p0AlphaSetforPUCCH_r17;	/* OPTIONAL */
   P0AlphaSet_r17_t p0AlphaSetforSRS_r17;	/* OPTIONAL */
}Uplink_powerControl_r17_t;



typedef struct  {
    u32 unifiedTCI_StateType_r17_valid:1;
    u32 sfnSchemePDCCH_r17_valid:1;
    u32 sfnSchemePDSCH_r17_valid:1;
    u32 rsv:29;
   u32 num_of_additionalPCI_ToAddModList_r17;//0..7
   SSB_MTC_AdditionalPCI_r17_t additionalPCI_ToAddModList_r17[7];	/* OPTIONAL */

   u32 num_of_additionalPCI_ToReleaseList_r17;//0..7
   u32 additionalPCI_ToReleaseList_r17[7];	/* OPTIONAL */
   s32 unifiedTCI_StateType_r17;	/* OPTIONAL enum UnifiedTCI_StateType_r17_separate = 0,
   													UnifiedTCI_StateType_r17_joint = 1 */
   u32 num_of_uplink_PowerControlToAddModList_r17;//0..64
   Uplink_powerControl_r17_t uplink_PowerControlToAddModList_r17[64];	/* OPTIONAL */

   u32 num_of_uplink_PowerControlToReleaseList_r17;//0..64
   u32 uplink_PowerControlToReleaseList_r17[64];	/* OPTIONAL */
   s32 sfnSchemePDCCH_r17;	/* OPTIONAL enum SfnSchemePDCCH_r17_sfnSchemeA = 0,
   											SfnSchemePDCCH_r17_sfnSchemeB = 1 */
   s32 sfnSchemePDSCH_r17;	/* OPTIONAL enum SfnSchemePDSCH_r17_sfnSchemeA = 0,
   										     SfnSchemePDSCH_r17_sfnSchemeB = 1 */
}MIMOParam_r17_t;



typedef struct  {
//   s32 choice;
//#define	ServingCellConfig_MimoParam_r17_release_chosen	0
//#define	ServingCellConfig_MimoParam_r17_setup_chosen	1

//   union {
//      s8 release;
      MIMOParam_r17_t setup;
//   } value;
}ServingCellConfig_MimoParam_r17_t;

typedef struct  {
   u32 num_of_pdcch_TCI_r17;//0..5
   u32 pdcch_TCI_r17[5];
   u32 num_bits_pdsch_TCI_r17;
   u8/*SIZE(1..128)*/ pdsch_TCI_r17[16];
}TCI_ActivatedConfig_r17_t;




typedef struct  {
   s32 neighCarrierBandwidthDL_r17;	/* OPTIONAL enum NeighCarrierBandwidthDL_r17_n6 = 0,
													   NeighCarrierBandwidthDL_r17_n15 = 1,
													   NeighCarrierBandwidthDL_r17_n25 = 2,
													   NeighCarrierBandwidthDL_r17_n50 = 3,
													   NeighCarrierBandwidthDL_r17_n75 = 4,
													   NeighCarrierBandwidthDL_r17_n100 = 5,
													   NeighCarrierBandwidthDL_r17_spare2 = 6,
													   NeighCarrierBandwidthDL_r17_spare1 = 7*/
   u32 neighCarrierFreqDL_r17;	/* OPTIONAL */
   u32 neighCellId_r17;	/* OPTIONAL */
   s32 neighCRS_muting_r17;	/* OPTIONAL enum NeighCRS_muting_r17_enabled = 0*/
   u32 num_of_neighMBSFN_SubframeConfigList_r17;//0..8
   EUTRA_MBSFN_SubframeConfig_t neighMBSFN_SubframeConfigList_r17[8];	/* OPTIONAL */
   s32 neighNrofCRS_Ports_r17;	/* OPTIONAL enum  NeighNrofCRS_Ports_r17_n1 = 0,
												   NeighNrofCRS_Ports_r17_n2 = 1,
												   NeighNrofCRS_Ports_r17_n4 = 2 */
   s32 neighV_Shift_r17;	/* OPTIONAL enum NeighV_Shift_r17_n0 = 0,
											   NeighV_Shift_r17_n1 = 1,
											   NeighV_Shift_r17_n2 = 2,
											   NeighV_Shift_r17_n3 = 3,
											   NeighV_Shift_r17_n4 = 4,
											   NeighV_Shift_r17_n5 = 5 */
}LTE_NeighCellsCRS_AssistInfo_r17_t;

typedef struct  {
   u32 num_of_LTE_NeighCellsCRS_AssistInfo_r17_list;
   LTE_NeighCellsCRS_AssistInfo_r17_t LTE_NeighCellsCRS_AssistInfo_r17_list[8];
}LTE_NeighCellsCRS_AssistInfo_r17_list_t;





typedef struct  {
   s32 choice;
#define	ServingCellConfig_Lte_NeighCellsCRS_AssistInfoList_r17_release_chosen	0
#define	ServingCellConfig_Lte_NeighCellsCRS_AssistInfoList_r17_setup_chosen	1

   union {
      s8 release;
      LTE_NeighCellsCRS_AssistInfo_r17_list_t setup;
   } value;
}ServingCellConfig_Lte_NeighCellsCRS_AssistInfoList_r17_t;




typedef struct  
{
   u64  tdd_UL_DL_ConfigurationDedicated_valid:1;
   u64  initialDownlinkBWP_valid:1;
   u64  firstActiveDownlinkBWP_Id_valid:1;
   u64  bwp_InactivityTimer_valid:1;
   u64  defaultDownlinkBWP_Id_valid:1;
   u64  uplinkConfig_valid:1;
   u64  supplementaryUplink_valid:1;
   u64  pdcch_ServingCellConfig_valid:1;
   u64  pdsch_ServingCellConfig_valid:1;
   u64  csi_MeasConfig_valid:1;
   u64  sCellDeactivationTimer_valid:1;
   u64 crossCarrierSchedulingConfig_valid:1;
   u64 dummy1_valid:1;
   u64 pathlossReferenceLinking_valid:1;
   u64 servingCellMO_valid:1;
   u64 downlinkChannelBW_PerSCS_List_valid:1;
   u64 supplementaryUplinkRelease_r16_valid:1;
   u64 dormantBWP_Config_r16_valid:1;
   u64 ca_SlotOffset_r16_valid:1;
   u64 dummy2_valid:1;
   u64 intraCellGuardBandsDL_List_r16_valid:1;
   u64 intraCellGuardBandsUL_List_r16_valid:1;
   u64 csi_RS_ValidationWithDCI_r16_valid:1;
   u64 crs_RateMatch_PerCORESETPoolIndex_r16_valid:1;
   u64 enableTwoDefaultTCI_States_r16_valid:1;
   u64 enableDefaultTCI_StatePerCoresetPoolIndex_r16_valid:1;
   u64 enableBeamSwitchTiming_r16_valid:1;
   u64 cbg_TxDiffTBsProcessingType1_r16_valid:1;
   u64 cbg_TxDiffTBsProcessingType2_r16_valid:1;
   u64 directionalCollisionHandling_r16_valid:1;
   u64 channelAccessConfig_r16_valid:1;
   u64 nr_dl_PRS_PDC_Info_r17_valid:1;
   u64 semiStaticChannelAccessConfigUE_r17_valid:1;
   u64 mimoParam_r17_valid:1;
   u64 channelAccessMode2_r17_valid:1;
   u64 timeDomainHARQ_BundlingType1_r17_valid:1;
   u64 nrofHARQ_BundlingGroups_r17_valid:1;
   u64 fdmed_ReceptionMulticast_r17_valid:1;
   u64 moreThanOneNackOnlyMode_r17_valid:1;
   u64 tci_ActivatedConfig_r17_valid:1;
   u64 directionalCollisionHandling_DC_r17_valid:1;
   u64 crossCarrierSchedulingConfigRelease_r17_valid:1;
   u64 rsv:22;
   TDD_UL_DL_ConfigDedicated_t *tdd_UL_DL_ConfigurationDedicated;	/* OPTIONAL */
   BWP_DownlinkDedicated_t *initialDownlinkBWP;	/* OPTIONAL */
   u8 num_of_downlinkBWP_ToReleaseList;
   u8 num_of_downlinkBWP_ToAddModList;
   u32 downlinkBWP_ToReleaseList[4];	/* OPTIONAL */
   bwp_downlink_t *downlinkBWP_ToAddModList[4];	/* OPTIONAL */
   u32 firstActiveDownlinkBWP_Id;	/* OPTIONAL */
   u32 bwp_InactivityTimer;	/* OPTIONAL */ /* Refer to  enum Bwp_InactivityTimer  */
   u32 defaultDownlinkBWP_Id;	/* OPTIONAL */
   UplinkConfig_t *uplinkConfig;	/* OPTIONAL */
   UplinkConfig_t *supplementaryUplink;	/* OPTIONAL */
   ServingCellConfig_Pdcch_ServingCellConfig_t *pdcch_ServingCellConfig;	/* OPTIONAL */
   ServingCellConfig_Pdsch_ServingCellConfig_t pdsch_ServingCellConfig;	/* OPTIONAL */
   ServingCellConfig_Csi_MeasConfig_t *csi_MeasConfig;	/* OPTIONAL */
   s32 sCellDeactivationTimer;	/* OPTIONAL enum SCellDeactivationTimer_ms20 = 0,
												   SCellDeactivationTimer_ms40 = 1,
												   SCellDeactivationTimer_ms80 = 2,
												   SCellDeactivationTimer_ms160 = 3,
												   SCellDeactivationTimer_ms200 = 4,
												   SCellDeactivationTimer_ms240 = 5,
												   SCellDeactivationTimer_ms320 = 6,
												   SCellDeactivationTimer_ms400 = 7,
												   SCellDeactivationTimer_ms480 = 8,
												   SCellDeactivationTimer_ms520 = 9,
												   SCellDeactivationTimer_ms640 = 10,
												   SCellDeactivationTimer_ms720 = 11,
												   SCellDeactivationTimer_ms840 = 12,
												   SCellDeactivationTimer_ms1280 = 13,
												   SCellDeactivationTimer_spare2 = 14,
												   SCellDeactivationTimer_spare1 = 15*/
   CrossCarrierSchedulingConfig_t crossCarrierSchedulingConfig;	/* OPTIONAL */
   u32 tag_Id;
   u32 dummy1;	/* OPTIONAL enum ServingCellConfig_Dummy1_enabled = 0 */
   s32 pathlossReferenceLinking;	/* OPTIONAL enum PathlossReferenceLinking_spCell = 0,
   												PathlossReferenceLinking_sCell = 1 */
   u32 servingCellMO;	/* OPTIONAL */
   ServingCellConfig_Lte_CRS_ToMatchAround_t lte_CRS_ToMatchAround;	/* OPTIONAL */

   u32 num_of_rateMatchPatternToAddModList;//0..4
   rate_match_pattern_t rateMatchPatternToAddModList[4];	/* OPTIONAL */

   u32 num_of_rateMatchPatternToReleaseList;//0..4
   u32 rateMatchPatternToReleaseList[4];	/* OPTIONAL */

   u32 num_of_downlinkChannelBW_PerSCS_List;//0..5
   scs_specific_carrier_t downlinkChannelBW_PerSCS_List[5];	/* OPTIONAL */

   s32 supplementaryUplinkRelease_r16;	/* OPTIONAL enum SupplementaryUplinkRelease_r16_true = 0*/
   TDD_UL_DL_ConfigDedicated_IAB_MT_r16_t *tdd_UL_DL_ConfigurationDedicated_IAB_MT_r16;	/* OPTIONAL */
   ServingCellConfig_DormantBWP_Config_r16_t *dormantBWP_Config_r16;	/* OPTIONAL */
   Ca_SlotOffset_r16_t ca_SlotOffset_r16;	/* OPTIONAL */
   ServingCellConfig_Dummy2_t dummy2;	/* OPTIONAL */

   u32 num_of_intraCellGuardBandsDL_List_r16;//0..5
   IntraCellGuardBandsPerSCS_r16_t intraCellGuardBandsDL_List_r16[5];	/* OPTIONAL */

   u32 num_of_intraCellGuardBandsUL_List_r16;//0..5
   IntraCellGuardBandsPerSCS_r16_t intraCellGuardBandsUL_List_r16[5];	/* OPTIONAL */
   s32 csi_RS_ValidationWithDCI_r16;	/* OPTIONAL enum Csi_RS_ValidationWithDCI_r16_enabled = 0 */

   
   //Lte_CRS_PatternList1_r16_t lte_CRS_PatternList1_r16;	/* OPTIONAL */
   //Lte_CRS_PatternList2_r16_t lte_CRS_PatternList2_r16;	/* OPTIONAL */
   s32 crs_RateMatch_PerCORESETPoolIndex_r16;	/* OPTIONAL enum  Crs_RateMatch_PerCORESETPoolIndex_r16_enabled = 0 */
   s32 enableTwoDefaultTCI_States_r16;	/* OPTIONAL enum  EnableTwoDefaultTCI_States_r16_enabled = 0*/
   s32 enableDefaultTCI_StatePerCoresetPoolIndex_r16;	/* OPTIONAL enum EnableDefaultTCI_StatePerCoresetPoolIndex_r16_enabled = 0 */
   s32 enableBeamSwitchTiming_r16;	/* OPTIONAL enum EnableBeamSwitchTiming_r16_true = 0*/
   s32 cbg_TxDiffTBsProcessingType1_r16;	/* OPTIONAL enum Cbg_TxDiffTBsProcessingType1_r16_enabled = 0*/
   s32 cbg_TxDiffTBsProcessingType2_r16;	/* OPTIONAL  enum Cbg_TxDiffTBsProcessingType2_r16_enabled = 0*/
   s32 directionalCollisionHandling_r16;	/* OPTIONAL enum  DirectionalCollisionHandling_r16_enabled = 0*/
   ServingCellConfig_ChannelAccessConfig_r16_t channelAccessConfig_r16;	/* OPTIONAL */
   ServingCellConfig_Nr_dl_PRS_PDC_Info_r17_t *nr_dl_PRS_PDC_Info_r17;	/* OPTIONAL */
   ServingCellConfig_SemiStaticChannelAccessConfigUE_r17_t semiStaticChannelAccessConfigUE_r17;	/* OPTIONAL */
   ServingCellConfig_MimoParam_r17_t *mimoParam_r17;	/* OPTIONAL */
   s32 channelAccessMode2_r17;	/* OPTIONAL enum ServingCellConfig_ChannelAccessMode2_r17_enabled = 0*/
   s32 timeDomainHARQ_BundlingType1_r17;	/* OPTIONAL enum TimeDomainHARQ_BundlingType1_r17_enabled = 0*/
   s32 nrofHARQ_BundlingGroups_r17;	/* OPTIONAL enum NrofHARQ_BundlingGroups_r17_n1 = 0,
													   NrofHARQ_BundlingGroups_r17_n2 = 1,
													   NrofHARQ_BundlingGroups_r17_n4 = 2*/
   s32 fdmed_ReceptionMulticast_r17;	/* OPTIONAL enum Fdmed_ReceptionMulticast_r17_true = 0 */
   s32 moreThanOneNackOnlyMode_r17;	/* OPTIONAL enum MoreThanOneNackOnlyMode_r17_mode2 = 0 */
   TCI_ActivatedConfig_r17_t tci_ActivatedConfig_r17;	/* OPTIONAL */
   s32 directionalCollisionHandling_DC_r17;	/* OPTIONAL ENUM DirectionalCollisionHandling_DC_r17_enabled = 0*/
   //ServingCellConfig_Lte_NeighCellsCRS_AssistInfoList_r17_t lte_NeighCellsCRS_AssistInfoList_r17;	/* OPTIONAL */
   s32 lte_NeighCellsCRS_Assumptions_r17;	/* OPTIONAL enum Lte_NeighCellsCRS_Assumptions_r17_false = 0*/
   s32 crossCarrierSchedulingConfigRelease_r17;	/* OPTIONAL enum  CrossCarrierSchedulingConfigRelease_r17_true = 0 */
}ServingCellConfig_t;


typedef struct  {
   RACH_ConfigGeneric_t rach_ConfigGeneric;
   s32 ssb_perRACH_Occasion;	/* OPTIONAL enumOccasions_Ssb_perRACH_Occasion_oneEighth = 0,
												   Occasions_Ssb_perRACH_Occasion_oneFourth = 1,
												   Occasions_Ssb_perRACH_Occasion_oneHalf = 2,
												   Occasions_Ssb_perRACH_Occasion_one = 3,
												   Occasions_Ssb_perRACH_Occasion_two = 4,
												   Occasions_Ssb_perRACH_Occasion_four = 5,
												   Occasions_Ssb_perRACH_Occasion_eight = 6,
												   Occasions_Ssb_perRACH_Occasion_sixteen = 7 */
}Occasions_t;


typedef struct  {
   u32 msgA_PUSCH_Resource_Index_r16_valid:1;
   u32 rsv:31;
   u32 ssb;
   u32 ra_PreambleIndex;
   u32 msgA_PUSCH_Resource_Index_r16;	/* OPTIONAL */
}CFRA_SSB_Resource_t;

typedef struct  {
   u32 csi_RS;

   u32 num_of_ra_OccasionList;//1..64
   u32 ra_OccasionList[64];

   u32 ra_PreambleIndex;
}CFRA_CSIRS_Resource_t;


typedef struct  {
   u32 num_of_csirs_ResourceList;//1..96
   CFRA_CSIRS_Resource_t csirs_ResourceList[96];
   u32 rsrp_ThresholdCSI_RS;
}Csirs_t;



typedef struct  {
   u32 num_of_ssb_ResourceList;//1..63
   CFRA_SSB_Resource_t ssb_ResourceList[64];
   u32 ra_ssb_OccasionMaskIndex;
}Ssb_t;



typedef struct  {
   s32 choice;
#define	Resources_ssb_chosen	0
#define	Resources_csirs_chosen	1

   union {
      Ssb_t ssb;
      Csirs_t csirs;
   } value;
}Resources_t;


typedef struct  {
   u8 occasions_valid:1;
   u8 totalNumberOfRA_Preambles_valid:1;
   u8 :6;

   Occasions_t occasions;	/* OPTIONAL */
   Resources_t resources;
   u32 totalNumberOfRA_Preambles;	/* OPTIONAL */
}CFRA_t;


typedef struct  {
   RACH_ConfigGenericTwoStepRA_r16_t rach_ConfigGenericTwoStepRA_r16;
   s32 ssb_PerRACH_OccasionTwoStepRA_r16;/*enum Ssb_PerRACH_OccasionTwoStepRA_r16_oneEighth = 0,
													   Ssb_PerRACH_OccasionTwoStepRA_r16_oneFourth = 1,
													   Ssb_PerRACH_OccasionTwoStepRA_r16_oneHalf = 2,
													   Ssb_PerRACH_OccasionTwoStepRA_r16_one = 3,
													   Ssb_PerRACH_OccasionTwoStepRA_r16_two = 4,
													   Ssb_PerRACH_OccasionTwoStepRA_r16_four = 5,
													   Ssb_PerRACH_OccasionTwoStepRA_r16_eight = 6,
													   Ssb_PerRACH_OccasionTwoStepRA_r16_sixteen = 7*/
}OccasionsTwoStepRA_r16_t;

typedef struct  {
   u32 num_of_ssb_ResourceList;//1..64
   CFRA_SSB_Resource_t ssb_ResourceList[64];
   u32 ra_ssb_OccasionMaskIndex;
}ResourcesTwoStep_r16_t;





typedef struct  {

   u8 occasionsTwoStepRA_r16_valid:1;
   u8 msgA_TransMax_r16_valid:1;
   u8 :6;

   OccasionsTwoStepRA_r16_t occasionsTwoStepRA_r16;	/* OPTIONAL */
   s32 msgA_TransMax_r16;   /* OPTIONAL enum CFRA_TwoStep_r16_MsgA_TransMax_r16_n1 = 0,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n2 = 1,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n4 = 2,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n6 = 3,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n8 = 4,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n10 = 5,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n20 = 6,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n50 = 7,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n100 = 8,
                            CFRA_TwoStep_r16_MsgA_TransMax_r16_n200 = 9 */
   MsgA_PUSCH_Resource_r16_t msgA_CFRA_PUSCH_r16;
   ResourcesTwoStep_r16_t resourcesTwoStep_r16;
}CFRA_TwoStep_r16_t;


typedef struct  {
   u8 cfra_valid:1;
   u8 ra_Prioritization_valid:1;
   u8 ra_PrioritizationTwoStep_r16_valid:1;
   u8 cfra_TwoStep_r16_valid:1;
   u8                           :4;

   CFRA_t cfra;	/* OPTIONAL */
   RA_Prioritization_t ra_Prioritization;	/* OPTIONAL */
   RA_Prioritization_t ra_PrioritizationTwoStep_r16;	/* OPTIONAL */
   CFRA_TwoStep_r16_t cfra_TwoStep_r16;	/* OPTIONAL */
}RACH_ConfigDedicated_t;



typedef struct  {
   s32 choice;
#define	ReconfigurationWithSync_Rach_ConfigDedicated_uplink_chosen	0
#define	ReconfigurationWithSync_Rach_ConfigDedicated_supplementaryUplink_chosen	1

   union {
      RACH_ConfigDedicated_t uplink;
      RACH_ConfigDedicated_t supplementaryUplink;
   } value;
}ReconfigurationWithSync_Rach_ConfigDedicated_t;


typedef struct
{
    u8 serving_cell_config_common_valid:1;
    u8 rach_config_dedicated_valid:1;
    u8 new_rnti_valid:1;
    u8 ssb_mtc_valid:1;
    u8                            :4;

    serving_cell_config_common_t *serving_cell_config_common;
    /*newUE_Identity*/
    u16 new_rnti;  
    ReconfigurationWithSync_Rach_ConfigDedicated_t  *rach_config_dedicated;
    wnrrc_ssb_mtc_t ssb_mtc;
}reconfiguration_with_sync_t;

typedef struct  {
   u8 s_SearchDeltaP_Connected_r17;
   u8 t_SearchDeltaP_Connected_r17;
   u8 padding[2];
}LowMobilityEvaluationConnected_r17_t;



typedef struct  {
   s32 choice;
#define	PeriodicityAndOffset_sf5_chosen	0
#define	PeriodicityAndOffset_sf10_chosen	1
#define	PeriodicityAndOffset_sf20_chosen	2
#define	PeriodicityAndOffset_sf40_chosen	3
#define	PeriodicityAndOffset_sf80_chosen	4
#define	PeriodicityAndOffset_sf160_chosen	5

   union {
      u32 sf5;
      u32 sf10;
      u32 sf20;
      u32 sf40;
      u32 sf80;
      u32 sf160;
   } value;
}PeriodicityAndOffset_t;


typedef struct  {
   PeriodicityAndOffset_t periodicityAndOffset;
   s32 duration; /*enum Duration_sf1 = 0,
					   Duration_sf2 = 1,
					   Duration_sf3 = 2,
					   Duration_sf4 = 3,
					   Duration_sf5 = 4*/
}SSB_MTC_t;



typedef struct  {
   s32 offset_r17;	/* OPTIONAL enum Offset_r17_db2 = 0,
								   Offset_r17_db4 = 1,
								   Offset_r17_db6 = 2,
								   Offset_r17_db8 = 3*/
}GoodServingCellEvaluation_r17_t;


typedef struct  {
   s32 choice;
#define	SCellConfig_SCellSIB20_r17_release_chosen	0
#define	SCellConfig_SCellSIB20_r17_setup_chosen	1

   union {
      s8 release;
      OCTETS setup;
   } value;
}SCellConfig_SCellSIB20_r17_t;

typedef struct
{
    u32 sCellIndex;
    u8 sCellConfigCommon_valid:1;
    u8 sCellConfigDedicated_valid:1;
    u8 smtc_valid:1;
    u8 sCellState_r16_valid:1;

    u8 secondaryDRX_GroupConfig_r16_valid:1;
    u8 preConfGapStatus_r17_valid:1;
    u8 goodServingCellEvaluationBFD_r17_valid:1;
    u8 sCellSIB20_r17_valid:1;
    u8 padding[3];

    serving_cell_config_common_t sCellConfigCommon;	/* OPTIONAL */
    ServingCellConfig_t *sCellConfigDedicated;	/* OPTIONAL */
    wnrrc_ssb_mtc_t smtc;	/* OPTIONAL */
    s32 sCellState_r16;	/* OPTIONAL enum SCellState_r16_activated = 0*/
    s32 secondaryDRX_GroupConfig_r16;	/* OPTIONAL enum SecondaryDRX_GroupConfig_r16_true = 0 */
    u8/*SIZE(8)*/ preConfGapStatus_r17;	/* OPTIONAL */
    u8 goodServingCellEvaluationBFD_r17;	/* OPTIONAL */
    //SCellConfig_SCellSIB20_r17_t sCellSIB20_r17;	/* OPTIONAL */
    //struct Plmn_IdentityInfoList_r17* plmn_IdentityInfoList_r17;	/* OPTIONAL */
    //struct Npn_IdentityInfoList_r17* npn_IdentityInfoList_r17;	/* OPTIONAL */
}scell_config_t;


typedef struct
{
    u8 serv_cell_index_valid:1;
    u8 reconfiguration_with_sync_valid:1;
    u8 rlm_insync_outOfsync_threshold_valid:1;
    u8 spcell_config_dedicated_valid:1;
    
    u8 lowMobilityEvaluationConnected_r17_valid:1;
    u8 good_servingcell_evaluation_RLM_offset_r17_valid:1;
    u8 good_servingcell_evaluation_BFD_offset_r17_valid:1;
    u8 Deactivated_SCG_config_bfd_and_RLM_r1_valid:1;

    u8 serv_cell_index;/*0-32,0XFF is INVALID*/
    reconfiguration_with_sync_t *reconfiguration_with_sync;/*HO*/
    u8 rlm_insync_outOfsync_threshold;/*0:n1,0xFF is invalid*/
    ServingCellConfig_t *spcell_config_dedicated;
    LowMobilityEvaluationConnected_r17_t lowMobilityEvaluationConnected_r17;
    u8 good_servingcell_evaluation_RLM_offset_r17;/*ENUMERATED {db2, db4, db6, db8}*/
    u8 good_servingcell_evaluation_BFD_offset_r17;/*ENUMERATED {db2, db4, db6, db8}*/
    bool Deactivated_SCG_config_bfd_and_RLM_r17;
}spcell_config_t;
/*spcell_config_t end*/

typedef struct
{
   u8 cell_group_id;
   physical_cell_group_config_t *phy_cell_group_config;


   u16             spcell_config_valid:1;
   spcell_config_t *spcell_config;
   u8 scell_add_mod_num;
   scell_config_t *scell_add_mod_list[MAX_NR_OF_SCCELLS];
   u8 scell_rel_num;
   u8 scell_rel_list[MAX_NR_OF_SCCELLS];
   bool report_uplink_tx_direct_current;/*Cond BWP-Reconfig*/

   /****************R16*******************************/
    u8 simultaneous_TCI_list1_num;
    u8 simultaneous_TCI_update_list1_r16[MAX_NR_OF_SERVING_CELLS_TCI_R16];

    u8 simultaneous_TCI_list2_num;
    u8 simultaneous_TCI_update_list2_r16[MAX_NR_OF_SERVING_CELLS_TCI_R16];

    u8 simultaneous_patial_TCI_list1_num;
    u8 simultaneous_Spatial_TCI_update_list1_r16[MAX_NR_OF_SERVING_CELLS_TCI_R16];

    u8 simultaneous_Spatial_TCI_list2_num;
    u8 simultaneous_Spatial_TCI_update_list2_r16[MAX_NR_OF_SERVING_CELLS_TCI_R16];


    u8 uplink_tx_switching_option_r16_valid;
#define     SWITCHED_UL 0
#define     DUAL_UL     1
    u8 uplink_tx_switching_option_r16;
    bool uplink_tx_switching_power_boosting_r16;
    bool report_uplink_tx_direct_current_two_carrier_r16;
   /****************R17*******************************/
    bool uplink_tx_switching_2T_mode;/*Indicates 2Tx-2Tx switching mode is configured for inter-band UL CA or SUL*/


     u8 uplink_tx_switching_dualUL_tx_state_valid;
#define ONE_T     0
#define TWO_T     1
    u8 uplink_tx_switching_dualUL_tx_state;/*Indicates the state of Tx chains if the state of Tx chains after the UL Tx switching 
                                    is not unique (as specified in TS 38.214 [19]) in case of 2Tx-2Tx switching is configured and
                                    uplinkTxSwitchingOption is set to dualUL. Value oneT indicates 1Tx is assumed to be supported 
                                    on the carriers on each band, value twoT indicates 2Tx is assumed to be supported on that carrier.*/
    u8 simultaneousU_TCI_list1_num;
    u8 simultaneousU_TCI_update_list1_r17[MAX_NR_OF_SERVING_CELLS_TCI_R16];
    
    u8 simultaneousU_TCI_list2_num;
    u8 simultaneousU_TCI_update_list2_r17[MAX_NR_OF_SERVING_CELLS_TCI_R16];
    
    u8 simultaneousU_TCI_list3_num;
    u8 simultaneousU_TCI_update_list3_r17[MAX_NR_OF_SERVING_CELLS_TCI_R16];
    
    u8 simultaneousU_TCI_list4_num;
    u8 simultaneousU_TCI_update_list4_r17[MAX_NR_OF_SERVING_CELLS_TCI_R16];

    report_uplink_tx_direct_current_more_carrier_t  *report_uplink_tx_direct_current_more_carrier_r17;
}cell_group_config_t;



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

