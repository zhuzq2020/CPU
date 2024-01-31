/***********************************************************************************************************************
*
*  COPYRIGHT GuangZhou HaiGe TongXin
*
***********************************************************************************************************************/

/***********************************************************************************************************************
*
* FILE
*
*    ps_phy_msg_id.h
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
#ifndef PS_PHY_MSG_ID_H
#define PS_PHY_MSG_ID_H

/***********************************************************************************************************************
*  INCLUDE FILES
***********************************************************************************************************************/





/***********************************************************************************************************************
*  MACRO DEFINITION
***********************************************************************************************************************/



/********************************** MESSAGE ID DEFINITION *******************************************************
*
*  MSG ID =  ((TASK ID << 16) | MSG No.)
*
*********************************** MESSAGE ID DEFINITION ******************************************************/
#define MSG_PS_WNRRC_BASE                                  ((uint32_t)4 << 16)   /* WRRC message base value */
#define MSG_PS_PHY_BASE                                    ((uint32_t)8 << 16)   /* PHY message base value define ps_phy_msg_id*/


/********************************** PS->PHY START**********************************************************************/
/**************************************WNRRC->PHY**********************************************************************/

#define MSG_PS_PHY_BEGIN                                   (MSG_PS_PHY_BASE + (uint32_t)0)
#define MSG_WNRRC_PHY_DEDICATED_CONFIG_REQ                 (MSG_PS_PHY_BEGIN + (uint32_t)1)
#define MSG_WNRRC_PHY_HO_REQ                               (MSG_PS_PHY_BEGIN + (uint32_t)2)
#define MSG_WNRRC_PHY_DEDICATED_RELEASE_REQ                (MSG_PS_PHY_BEGIN + (uint32_t)3)
#define MSG_WNRRC_PHY_STATECHG_IND                         (MSG_PS_PHY_BEGIN + (uint32_t)4)
#define MSG_WNRRC_PHY_MEAS_CONTROL_REQ                     (MSG_PS_PHY_BEGIN + (uint32_t)5)
#define MSG_WNRRC_PHY_CAMP_ON_REQ                          (MSG_PS_PHY_BEGIN + (uint32_t)6)
#define MSG_WNRRC_PHY_CELL_SEARCH_REQ                      (MSG_PS_PHY_BEGIN + (uint32_t)7)
#define MSG_WNRRC_PHY_SEARCH_NEXT_REQ                      (MSG_PS_PHY_BEGIN + (uint32_t)8)
#define MSG_WNRRC_PHY_STOP_SEARCH_IND                      (MSG_PS_PHY_BEGIN + (uint32_t)9)
#define MSG_WNRRC_PHY_STOP_READ_SI_IND                     (MSG_PS_PHY_BEGIN + (uint32_t)10)
#define MSG_WNRRC_PHY_READ_MIBSIB1_REQ                     (MSG_PS_PHY_BEGIN + (uint32_t)11)
#define MSG_WNRRC_PHY_READ_SI_REQ                          (MSG_PS_PHY_BEGIN + (uint32_t)12)
#define MSG_WNRRC_PHY_BG_CELL_SEARCH_REQ                   (MSG_PS_PHY_BEGIN + (uint32_t)13)
#define MSG_WNRRC_PHY_BG_SEARCH_NEXT_REQ                   (MSG_PS_PHY_BEGIN + (uint32_t)14)
#define MSG_WNRRC_PHY_BG_READ_MSI_REQ                       (MSG_PS_PHY_BEGIN + (uint32_t)15)
#define MSG_WNRRC_PHY_STOP_BG_SEARCH_IND                   (MSG_PS_PHY_BEGIN + (uint32_t)16)
#define MSG_WNRRC_PHY_STOP_BG_READ_MSI_IND                  (MSG_PS_PHY_BEGIN + (uint32_t)17)
#define MSG_WNRRC_PHY_READ_CGI_SI_REQ                      (MSG_PS_PHY_BEGIN + (uint32_t)18)
#define MSG_WNRRC_PHY_UEID_INFO_IND                        (MSG_PS_PHY_BEGIN + (uint32_t)19)
#define MSG_WNRRC_PHY_CONN_DEFAULT_CONFIG_REQ              (MSG_PS_PHY_BEGIN + (uint32_t)20)
#define MSG_WNRRC_PHY_IDLE_MEAS_CFG_IND                    (MSG_PS_PHY_BEGIN + (uint32_t)21)
#define MSG_WNRRC_PHY_IDLE_STOP_MEAS_IND                   (MSG_PS_PHY_BEGIN + (uint32_t)22)
#define MSG_WNRRC_PHY_IDLE_START_MEAS_IND                  (MSG_PS_PHY_BEGIN + (uint32_t)23)




/**************************************WNRRC->WNL2**********************************************************************/
/********************************** PS->PHY END**********************************************************************/


/***********************************PHY->WNRRC START****************************************************************/
/***********************************PHY->WNDCFE*********************************************************************/
#define MSG_PHY_WNDCFE_BEGIN                               (MSG_PS_WNRRC_BASE + (uint32_t)1000)
#define MSG_WNRRC_PHY_DEDICATED_CONFIG_CNF                 (MSG_PHY_WNDCFE_BEGIN + (uint32_t)1)
#define MSG_WNRRC_PHY_HO_CNF                               (MSG_PHY_WNDCFE_BEGIN + (uint32_t)2)
#define MSG_WNRRC_PHY_DEDICATED_RELEASE_CNF                (MSG_PHY_WNDCFE_BEGIN + (uint32_t)3)
#define MSG_PHY_WNRRC_DL_OUTOFSYNC_IND                     (MSG_PHY_WNDCFE_BEGIN + (uint32_t)4)
#define MSG_PHY_WNRRC_DL_INSYNC_IND                        (MSG_PHY_WNDCFE_BEGIN + (uint32_t)5)
#define MSG_WNRRC_PHY_CONN_DEFAULT_CONFIG_CNF              (MSG_PHY_WNDCFE_BEGIN + (uint32_t)6)
#define MSG_PHY_WNRRC_PAGING_IND                           (MSG_PHY_WNDCFE_BEGIN + (uint32_t)7)
#define MSG_WNRRC_PHY_MEAS_CONTROL_CNF                     (MSG_PHY_WNDCFE_BEGIN + (uint32_t)8)
#define MSG_WNRRC_PHY_RELEASE_CNF                          (MSG_PHY_WNDCFE_BEGIN + (uint32_t)9)
#define MSG_PHY_WNDCFE_END                                 (MSG_PHY_WNDCFE_BEGIN + (uint32_t)10)

/***********************************PHY->WNGCFE*********************************************************************/
#define MSG_PHY_WNGCFE_BEGIN                               (MSG_PHY_WNDCFE_END +  (uint32_t)0)
#define MSG_PHY_WNRRC_S_IND                                (MSG_PHY_WNGCFE_BEGIN + (uint32_t)1)
#define MSG_PHY_WNRRC_IDLE_MEASEVA_IND                     (MSG_PHY_WNGCFE_BEGIN + (uint32_t)2)
#define MSG_WNRRC_PHY_CELL_SEARCH_CNF                      (MSG_PHY_WNGCFE_BEGIN + (uint32_t)3)
#define MSG_WNRRC_PHY_SEARCH_NEXT_CNF                      (MSG_PHY_WNGCFE_BEGIN + (uint32_t)4)
#define MSG_PHY_WNRRC_MIB_IND                              (MSG_PHY_WNGCFE_BEGIN + (uint32_t)5)
#define MSG_PHY_WNRRC_SIB1_IND                             (MSG_PHY_WNGCFE_BEGIN + (uint32_t)6)
#define MSG_PHY_WHRRC_SI_DATA_IND                          (MSG_PHY_WNGCFE_BEGIN + (uint32_t)7)
#define MSG_WNRRC_PHY_BG_CELL_SEARCH_CNF                   (MSG_PHY_WNGCFE_BEGIN + (uint32_t)8)
#define MSG_WNRRC_PHY_BG_SEARCH_NEXT_CNF                   (MSG_PHY_WNGCFE_BEGIN + (uint32_t)9)
#define MSG_WNRRC_PHY_CAMP_ON_CNF                          (MSG_PHY_WNDCFE_BEGIN + (uint32_t)10)
#define MSG_PHY_WNRRC_SIB1BIS_IND                          (MSG_PHY_WNGCFE_BEGIN + (uint32_t)11)
#define MSG_PHY_WNGCFE_END                                 (MSG_PHY_WNGCFE_BEGIN + (uint32_t)11)



/***********************************PHY->WNGCFE*********************************************************************/
#define MSG_PHY_WNMCFE_BEGIN                               (MSG_PHY_WNGCFE_END +  (uint32_t)0)
#define MSG_PHY_WNRRC_INTERF_MEAS_REPORT_IND               (MSG_PHY_WNMCFE_BEGIN + (uint32_t)1)
#define MSG_PHY_WNRRC_INTRAF_MEAS_REPORT_IND               (MSG_PHY_WNMCFE_BEGIN + (uint32_t)2)
#define MSG_PHY_WNMCFE_END                                 (MSG_PHY_WNMCFE_BEGIN + (uint32_t)2)

/***********************************PHY->WNRRC END****************************************************************/




/***********************************PHY->WNL2 START****************************************************************/



/***********************************PHY->WNL2 END****************************************************************/

#endif 

/********************************* END OF FILE ************************************************************************/

