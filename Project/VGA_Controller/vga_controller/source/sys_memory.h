/**
 * @file sys_memory.h
 *
 * @brief System memory module.
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
#ifndef SYS_MEMORY_H
#define SYS_MEMORY_H

// Libs
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

/**
 * TLM2 Memory Module
 */
// From tlm2_example1, with modifications
// Added OpenCV2 headers for frame grabbing
struct Memory: sc_module
{
  
  // Attributes: port
  tlm_utils::simple_target_socket<Memory> socket;           /**< TLM2 memory socket */

  // Constructor
  SC_CTOR(Memory) : socket("socket")
  {
    // Register callback for incoming b_transport interface method call
    socket.register_b_transport(this, &Memory::b_transport);

	// Open video file before running simulation
	cap = cv::VideoCapture("resource/test-mpeg.mpg");

	if (!cap.isOpened())
	    SC_REPORT_ERROR("OpenCV", "Video import error");

	// Pre-load a frame
	if(!cap.read(curr_frame))
		SC_REPORT_ERROR("OpenCV", "Video read error");

	cout << "MEMORY: Preloaded video has the following frame size: " << cap.get(cv::CAP_PROP_FRAME_WIDTH)
	                                                                 << "x" << cap.get(cv::CAP_PROP_FRAME_HEIGHT)
	                                                                 << endl;

	cout << "MEMORY: This file has " << cap.get(cv::CAP_PROP_FRAME_COUNT) << " frames" << endl;
#ifdef _PRINT_DBG_
	cout << "MEMORY: Image depth is " << curr_frame.depth() << " with " << curr_frame.channels() << " channels" << endl;
#endif
  }

  // Destructor 
  ~Memory() { cap.release(); curr_frame.release(); }

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    //tlm::tlm_command cmd = trans.get_command();
    unsigned int     adr = trans.get_address();
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    if (byt != 0 || len > 32 || wid < len)
      SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

	// Check for address mismatch
	if(adr != (cap.get(cv::CAP_PROP_POS_FRAMES)-1)) {
#ifdef _PRINT_DBG_
	  cout << "MEMORY: Requested read addr is :" << adr-1 << " and current frame points to "
		                                         << cap.get(cv::CAP_PROP_POS_FRAMES) << endl;
#endif
	  SC_REPORT_ERROR("TLM-2", "Mismatched address");

	}
#ifdef _PRINT_DBG_
	cout << "MEMORY: Frame #" << adr+1 << " requested" << endl; // Debug purpose
#endif
	if(!cap.read(curr_frame))
	  SC_REPORT_ERROR("OpenCV", "Video read error");

	memcpy(ptr, &curr_frame, sizeof(curr_frame)); // Deep copy

    trans.set_response_status( tlm::TLM_OK_RESPONSE );

	wait(delay);

  }

  private:

  // Attributes
  cv::VideoCapture cap;
  cv::Mat curr_frame;

};

#endif
