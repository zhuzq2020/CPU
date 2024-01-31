/*******************************************************************************
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 ******************************************************************************/
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "l1c_init.h"
#include "../l1c_typedef.h"
#include "../l1c_para.h"

/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define LOG_TAG "INIT : "

/*******************************************************************************
 * GLOBAL VARIABLES DECLARATION
 ******************************************************************************/
s_l1c_para g_l1c_syspara;

/*******************************************************************************
* FUNCTION PROTOTYPE DECLARATION
*******************************************************************************/

/*******************************************************************************
 * @funtion:
 * @description:
 * @param:
 * @return:
 ******************************************************************************/
void init_l1c(void)
{
    int i;
    
    g_l1c_syspara.ue_state = RRC_STATE_REEST;
    memset(&g_l1c_syspara.s_tmsi, 0, 6);
    g_l1c_syspara.sort_priority = WNRRC_CELL_SORT_PRIORITY_RSRP;
    g_l1c_syspara.local_cell_pci = 0;
    g_l1c_syspara.l1c_cell_num = 0;
    for (i = 0; i < MAX_NR_CELL_SEARCH_CELL_NUM; i++) {
        g_l1c_syspara.l1c_cell_list[i] = NULL;
    }
    g_l1c_syspara.ue_camp_on_info = NULL;
}
