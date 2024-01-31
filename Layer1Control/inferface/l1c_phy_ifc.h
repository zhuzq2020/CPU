/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * File:   l1c_phy_ifc.h
 * Author: sat01
 *
 * Created on December 12, 2023, 4:36 PM
 ******************************************************************************/

#ifndef L1C_PHY_IFC_H
#define L1C_PHY_IFC_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "../l1c_typedef.h"

/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
/**************************** CELL SEARCH *************************************/
#define CELL_SEARCH_BASE_ADDR             (0x0100)
#define PSS_SYNC_START_REG                (CELL_SEARCH_BASE_ADDR + 0x31)
#define PSS_SYNC_FINISH_REG               (CELL_SEARCH_BASE_ADDR + 0x34)
#define PEAK_ABS_0_REG                    (CELL_SEARCH_BASE_ADDR + 0x03)
#define PEAK_LOCATION_0_REG               (CELL_SEARCH_BASE_ADDR + 0x0F)
#define PEAK_ANGLE_0_REG                  (CELL_SEARCH_BASE_ADDR + 0x1B)
#define NID2_REG                          (CELL_SEARCH_BASE_ADDR + 0x27)
#define PSS_LOCATION_REG                  (CELL_SEARCH_BASE_ADDR + 0x28)
#define PSS_ANGLE_REG                     (CELL_SEARCH_BASE_ADDR + 0x29)
#define PSS_SYNC_FINISH_CLR_REG           (CELL_SEARCH_BASE_ADDR + 0x35)
    
#define SSS_SYNC_START_REG                (CELL_SEARCH_BASE_ADDR + 0x51)
#define SSS_SYNC_FINISH_REG               (CELL_SEARCH_BASE_ADDR + 0x52)
#define SSS_RSRP_REG                      (CELL_SEARCH_BASE_ADDR + 0x53)
#define SSS_SNR_REG                       (CELL_SEARCH_BASE_ADDR + 0x54)
#define PCI_REG                           (CELL_SEARCH_BASE_ADDR + 0x55)
#define SSS_SYNC_FINISH_CLR_REG           (CELL_SEARCH_BASE_ADDR + 0x56)
    
#define PBCH_DETECTION_START_REG          (CELL_SEARCH_BASE_ADDR + 0x61)
#define PBCH_DETECTION_FINISH_REG         (CELL_SEARCH_BASE_ADDR + 0x62)
#define PBCH_PCI_REG                      (CELL_SEARCH_BASE_ADDR + 0x63)
#define PBCH_MIB_PAYLOAD_REG              (CELL_SEARCH_BASE_ADDR + 0x64)
#define SSB_LOW3_REG                      (CELL_SEARCH_BASE_ADDR + 0x65)
    
/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/
int l1c_phy_write(u32 reg_addr, u32 src_data);
u32 l1c_phy_read(u32 reg_addr);

#ifdef __cplusplus
}
#endif

#endif /* L1C_PHY_IFC_H */

