#ifndef SYS_MEMORY_H
#define SYS_MEMORY_H

#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

/**
 * TLM2 Memory Module
 * From tlm2_example1, with modifications
 * Added OpenCV2 headers for frame grabbing
 */

struct Memory: sc_module
{
  
  /** Memor port **/
  tlm_utils::simple_target_socket<Memory> socket;

  /** Memory constructor & destructor **/

  SC_CTOR(Memory)
  : socket("socket")
  {
    // Register callback for incoming b_transport interface method call
    socket.register_b_transport(this, &Memory::b_transport);

	// Open video file before running simulation
	cap = cv::VideoCapture("C:\\test-mpeg\\test-mpeg.mpg");
	  
	if (!cap.isOpened())
	    SC_REPORT_ERROR("OpenCV", "Video import error");

	// Pre-load a frame
	if(!cap.read(curr_frame))
		SC_REPORT_ERROR("OpenCV", "Video read error");

	cout << "MEMORY: Preloaded video has the following frame size: " << cap.get(CV_CAP_PROP_FRAME_WIDTH)
	                                                                 << "x" << cap.get(CV_CAP_PROP_FRAME_HEIGHT)
	                                                                 << endl;

	cout << "MEMORY: This file has " << cap.get(CV_CAP_PROP_FRAME_COUNT) << " frames" << endl;

	//cout << "MEMORY: Image depth is " << curr_frame.depth() << " with " << curr_frame.channels() << " channels" << endl;

  }

  ~Memory() { cap.release(); curr_frame.release(); }

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    tlm::tlm_command cmd = trans.get_command();
    unsigned int     adr = trans.get_address();
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    if (byt != 0 || len > 32 || wid < len)
      SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

	// Check for address mismatch
	if(adr != (cap.get(CV_CAP_PROP_POS_FRAMES)-1)) {

	  /*cout << "MEMORY: Requested read addr is :" << adr-1 << " and current frame points to "
		                                         << cap.get(CV_CAP_PROP_POS_FRAMES) << endl;*/

	  SC_REPORT_ERROR("TLM-2", "Mismatched address");

	}

	//cout << "MEMORY: Frame #" << adr+1 << " requested" << endl; // Debug purpose

	if(!cap.read(curr_frame))
	  SC_REPORT_ERROR("OpenCV", "Video read error");

	memcpy(ptr, &curr_frame, sizeof(curr_frame));

    trans.set_response_status( tlm::TLM_OK_RESPONSE );

	wait(delay);

  }

  private:

  /** Memory attributes **/

  cv::VideoCapture cap;
  cv::Mat curr_frame;

};

#endif
