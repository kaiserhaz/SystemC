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

#include "sin_source.h"
#include <cmath>                                      // for M_PI and std::sin

void sin_source::set_attributes()                     // Set TDF attributes
{
  out.set_timestep(1.0, SC_US);                       // Set time step of output port
}

void sin_source::processing()                         // Describe time-domain behaviour
{
  double t = out.get_time().to_seconds();             // Get current time of the sample
  double x = ampl * std::sin(2.0 * M_PI * freq * t);  // Calculate sine wave
  out.write(x);                                       // Write sample to the output
}
