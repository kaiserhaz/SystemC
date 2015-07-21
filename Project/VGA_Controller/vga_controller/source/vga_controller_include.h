#ifndef VGA_CONTROLLER_INCLUDE_H
#define VGA_CONTROLLER_INCLUDE_H

/** VGA Controller Includes **/

//Constants

#define _X_SCREEN_ 800    // Maximum horizontal screen size in pixels
#define _Y_SCREEN_ 524    // Maximum vertical screen size in lines

#define _X_MAX_ 640       // Maximum horizontal image size in pixels
#define _X_ORIGIN_ 0      // Image horizontal origin
#define _X_BPOR_ 48       // Horizontal back porch duration in pixels
#define _X_SYNC_ 96       // Horizontal synchronization duration in pixels
#define _X_FPOR_ 16       // Horizontal front porch duration in pixels

#define _Y_MAX_ 480       // Maximum vertical image size in lines
#define _Y_ORIGIN_ 0      // Image vertical origin
#define _Y_BPOR_ 31       // Vertical back porch duration in lines
#define _Y_SYNC_ 2        // Vertical synchronization duration in lines
#define _Y_FPOR_ 11       // Vertical front porch duration in lines

#endif
