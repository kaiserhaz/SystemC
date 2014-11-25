//----------------------------------------------------------------------
//   Copyright 2010-2014 Fraunhofer IIS/EAS
//   Copyright 2014 NXP B.V.
//   Copyright 2014 Université Pierre et Marie Curie
//   All Rights Reserved
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//----------------------------------------------------------------------
//
//   Original Author: Karsten Einwich Fraunhofer IIS/EAS Dresden
//
//   Created on: 16.02.2010
//
//----------------------------------------------------------------------

#include "sin_source_with_noise.h"
#include "sink.h"

int sc_main(int argn, char* argc[])          // SystemC main program
{
  sca_tdf::sca_signal<double> sig_1;         // Signal to connect source w sink

  sin_source_with_noise src_1("src_1");      // Instantiate source
    src_1.out(sig_1);                        // Connect (bind) with signal

  sink sink_1("sink_1");                     // Instantiate sink
    sink_1.in(sig_1);                        // Connect (bind) with signal

  sca_trace_file* tfp =                      // Open trace file
    sca_create_vcd_trace_file("testbench");
    sca_trace(tfp, sig_1, "sig_1");          // Define which signal to trace

  sc_start(10.0, SC_MS);                     // Start simulation for 10 ms

  sca_close_vcd_trace_file(tfp);             // Close trace file

  return 0;                                  // Exit with return code 0
}
