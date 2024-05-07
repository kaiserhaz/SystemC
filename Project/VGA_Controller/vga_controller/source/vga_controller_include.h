/**
 * @file vga_controller_include.h
 *
 * @brief Header for `vga_controller`.
 * 
 * -- Versioning Info --
 *
 * v0.0 : Before 07/05/2024 : Initial working config write-up.
 * v1.0 : 07/05/2024 : Edited for clarity.
 *
 * @copyright
 * Copyright 2024 British Malaysian Institute, Universiti Kuala Lumpur.
 * 
 * Written by Muhammad Haziq Kamarul Azman a.k.a. Kaiser Haz.
 *******************************************************************************************
 */

// Def guard
#ifndef VGA_CONTROLLER_INCLUDE_H
#define VGA_CONTROLLER_INCLUDE_H

// Defs
#define _X_SCREEN_ 800                                      /**< Maximum horizontal screen size in pixels      */
#define _Y_SCREEN_ 524                                      /**< Maximum vertical screen size in lines         */

#define _X_MAX_ 640                                         /**< Maximum horizontal image size in pixels       */
#define _X_ORIGIN_ 0                                        /**< Image horizontal origin                       */
#define _X_BPOR_ 48                                         /**< Horizontal back porch duration in pixels      */
#define _X_SYNC_ 96                                         /**< Horizontal synchronization duration in pixels */
#define _X_FPOR_ 16                                         /**< Horizontal front porch duration in pixels     */

#define _Y_MAX_ 480                                         /**< Maximum vertical image size in lines          */
#define _Y_ORIGIN_ 0                                        /**< Image vertical origin                         */
#define _Y_BPOR_ 31                                         /**< Vertical back porch duration in lines         */
#define _Y_SYNC_ 2                                          /**< Vertical synchronization duration in lines    */
#define _Y_FPOR_ 11                                         /**< Vertical front porch duration in lines        */

#endif
