/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   l1c_para.h
 * Author: sat01
 *
 * Created on December 28, 2023, 5:30 PM
 */

#ifndef L1C_PARA_H
#define L1C_PARA_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "ctrlplane/rrc_phy_ifc/rrc_phy_ifc.h"
    
/*******************************************************************************
*  COMMON TYPE DEFINITION
*******************************************************************************/
typedef struct
{
    u8 ue_state;
    u8 s_tmsi[6];
    u8 sort_priority;
    u16 local_cell_pci;
    u8 l1c_cell_num;
    s_l1c_cell_info_t *l1c_cell_list[MAX_NR_CELL_SEARCH_CELL_NUM];
    s_l1c_ue_camp_on_info_t *ue_camp_on_info;
} s_l1c_para;

#ifdef __cplusplus
}
#endif

#endif /* L1C_PARA_H */

