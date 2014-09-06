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

#include "adc_sd.h"

adc_sd::adc_sd(sc_core::sc_module_name nm)
{
  integ1 = 0.0;
  integ2 = 0.0;
}

void adc_sd::processing()
{
  double a = 0.5;
  double b = 0.5;
  double c = 1.0;

  double feedback = (integ2 >= 0.0) ? 1.0 : -1.0;

  bool output = (integ2 >= 0.0) ? true : false;
  out.write(output);

  double s1 = in.read() - feedback;

  double k1 = a * s1;
  double s2 = k1 + integ1;

  double k3 = c * feedback;
  double s3 = integ1 - k3;

  double k2 = b * s3;

  double s4 = k2 + integ2;

  integ2 = s2;
  integ1 = s4;
}

void adc_sd::ac_processing()
{
  sca_ac(out) = 0.25 / (sca_ac_z(2) - 1.5 * sca_ac_z() + 0.75) * sca_ac(in);
}
