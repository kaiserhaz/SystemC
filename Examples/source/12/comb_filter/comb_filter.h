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

#ifndef COMB_FILTER_H
#define COMB_FILTER_H

#include<systemc-ams>

SCA_TDF_MODULE(comb_filter)
{
  static const int WL=19;

  sca_tdf::sca_in<bool>                in;
  sca_tdf::sca_out<sc_dt::sc_int<WL> > out;

  void set_attributes()
  {
    in.set_rate(64);
    out.set_rate(1);
  }

  void processing();
  void ac_processing();

  SCA_CTOR(comb_filter);

private:
  sc_dt::sc_int<WL> 	z1;
  sc_dt::sc_int<WL> 	z2;
  sc_dt::sc_int<WL> 	z3;
  sc_dt::sc_int<WL> 	z4;
  sc_dt::sc_int<WL> 	z5;
  sc_dt::sc_int<WL> 	z6;
};

#endif /* COMB_FILTER_H */
