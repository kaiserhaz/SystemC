/**
 * @file surface_ecg_test.cpp
 *
 * @brief ECG simulator bench.
 * 
 * -- Versioning Info --
 *
 * v1.0 : 26/02/2025 : Initial working config write-up.
 *
 * @copyright
 * Copyright 2025 British Malaysian Institute, Universiti Kuala Lumpur.
 * 
 * Written by Muhammad Haziq Kamarul Azman a.k.a. Kaiser Haz.
 *******************************************************************************************
 */
 
// Libs
#include <stdio.h>
#include "gen_ecg.h"

int main()
{
  printf("> surface_ecg_test : Generating ECG.\r\n");

  int status = gen_ecg();
  
  return status;
}
