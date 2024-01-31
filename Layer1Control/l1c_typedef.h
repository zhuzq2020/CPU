/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   l1c_typedef.h
 * Author: sat01
 *
 * Created on November 10, 2023, 10:17 AM
 */

#ifndef L1C_TYPEDEF_H
#define L1C_TYPEDEF_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
    
/*******************************************************************************
*  MACRO DEFINITION
*******************************************************************************/
#define RLOGE(fmt,args...) {printf("\033[0;31mERROR %s ",LOG_TAG);\
printf(fmt,##args);printf(" \033[0m\n");}
#define RLOGD(fmt,args...) {printf("\033[0;34mDEBUG %s ",LOG_TAG);\
printf(fmt,##args);printf(" \033[0m\n");}
#define RLOGI(fmt,args...) {printf("\033[0;32mINFO  %s ",LOG_TAG);\
printf(fmt,##args);printf(" \033[0m\n");}

#define TRUE   (1)
#define FALSE  (0)
#define OK     (0)

#define U8_INVALID_VALUE  (0xFF)
#define U16_INVALID_VALUE (0xFFFF)
#define U32_INVALID_VALUE (0xFFFFFFFF)
#define U64_INVALID_VALUE (0xFFFFFFFFFFFFFFFF)

/*******************************************************************************
*  TYPE DEFINITION
*******************************************************************************/
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef uint32_t BOOL;

#ifdef __cplusplus
}
#endif

#endif /* L1C_TYPEDEF_H */

