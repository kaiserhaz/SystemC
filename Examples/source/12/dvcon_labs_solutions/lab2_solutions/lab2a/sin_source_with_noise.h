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

#ifndef SIN_SOURCE_WITH_NOISE_H
#define SIN_SOURCE_WITH_NOISE_H

#include <systemc-ams.h>                   // SystemC AMS header

SCA_TDF_MODULE(sin_source_with_noise)      // Declare a TDF module
{
  sca_tdf::sca_out<double> out;            // TDF output port

  void set_attributes();                   // Set TDF attributes

  void processing();                       // Describe time-domain behaviour

  void ac_processing();                    // Describe freq-domain behaviour

  SCA_CTOR(sin_source_with_noise)          // Constructor of the TDF module
  : out("out"),                            // Name the port(s)
    ampl(1.0), freq(1e3),variance(0.1) {}  // Initial values for ampl and freq

 private:                                  // Private variables
  double ampl;                             //   amplitude
  double freq;                             //   frequency
  double variance;                         //   variance for noise
};

#endif /* SIN_SOURCE_WITH_NOISE_H */
