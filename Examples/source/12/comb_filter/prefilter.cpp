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
#include "prefilter.h"

prefilter::prefilter(sc_core::sc_module_name nm)
{
  fc = 1e3;
}

void prefilter::initialize()
{
  num(0) = 1.0;
  den(0) = 1.0;
  den(1) = 1.0 / (2.0 * M_PI * fc);
}

void prefilter::processing()
{
  out = ltf1(num, den, in);
}

void prefilter::ac_processing()
{
  sca_ac(out) = sca_ac_ltf_nd(num, den, sca_ac(in));
}
