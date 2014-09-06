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

#ifndef _PREFILTER_H
#define _PREFILTER_H

#include <systemc-ams.h>

SCA_TDF_MODULE(prefilter)
{
  sca_tdf::sca_in<double> in;
  sca_tdf::sca_out<double> out;

  void initialize();
  void processing();
  void ac_processing();

  SCA_CTOR(prefilter);

 private:
  sca_vector<double> num, den;
  sca_tdf::sca_ltf_nd ltf1;
  double fc;
};

#endif /* _PREFILTER_H */

