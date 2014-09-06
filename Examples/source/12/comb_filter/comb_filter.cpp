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

#include <systemc-ams.h>
#include "comb_filter.h"

comb_filter::comb_filter(sc_core::sc_module_name nm)
{
  z1 = 0;
  z2 = 0;
  z3 = 0;
  z4 = 0;
  z5 = 0;
  z6 = 0;
}


void comb_filter::processing()
{
  sc_int<WL> y, y1, y2, y3, y4, y5;

  // Integrators
  for (int i = 0; i < 64; i++)
  {
    y1 = in.read(i) ? z1 + 1 : z1 - 1;
    z1 = y1;

    y2 = y1 + z2;
    z2 = y2;

    y3 = y2 + z3;
    z3 = y3;
  }

  //Differentiators
  y4 = y3 - z4;
  z4 = y3;

  y5 = y4 - z5;
  z5 = y4;

  y = y5 - z6;
  z6 = y5;

  out.write(y);
}


void comb_filter::ac_processing()
{
	double k = 64.0;
	double n = 3.0;

	sca_complex z = sca_ac_z(1, in.get_timestep());
	sca_complex h;

	h = pow((1.0 - pow(z, -k)) / (1.0 - 1.0 / z), n); // comb

	sca_ac(out) = h * sca_ac(in);

}



