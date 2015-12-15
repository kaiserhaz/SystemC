/**
 * Datatypes
 */

/** Include guard **/
#ifndef VNC_DT_H
#define VNC_DT_H

/** Includes **/
#include <systemc.h>

/** Constants **/
#define MEM_SIZE 1024

#define MEM_ADDR_WORD_LEN 16
#define MEM_DATA_WORD_LEN 16

/** Typedefs **/
typedef sc_lv<MEM_ADDR_WORD_LEN> a_word_t;
typedef sc_lv<MEM_DATA_WORD_LEN> d_word_t;

#endif
