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

#define _USE_MATH_DEFINES
#include "sin_source_with_noise.h"

#include <cstdlib> // for std::rand
#include <cmath>   // for M_PI, std::sin, std::sqrt, and std::log

double gauss_rand(double variance)
{
  double rnd1, rnd2, Q, Q1, Q2;

  do
  {
    rnd1 = static_cast<double>(std::rand()) / RAND_MAX;
    rnd2 = static_cast<double>(std::rand()) / RAND_MAX;

    Q1 = 2.0 * rnd1 - 1.0;
    Q2 = 2.0 * rnd2 - 1.0;
    Q = Q1 * Q1 + Q2 * Q2;
  }
  while (Q > 1.0);

  return ( std::sqrt(variance) * ( std::sqrt( - 2.0 * std::log(Q) / Q) * Q1) );
}

void sin_source_with_noise::set_attributes()    // Set TDF attributes
{
  out.set_timestep(1.0, SC_US);                 // Set time step of output port
}

void sin_source_with_noise::processing()
{
  double t = out.get_time().to_seconds();       // Get current time of the sample
  double n = gauss_rand(variance);
  double x = ampl * sin(2.0 * M_PI * freq * t) + n; // Calculate sine wave
  out.write(x);                                     // Write sample to the output
}
