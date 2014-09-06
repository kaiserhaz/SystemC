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
#include "prefilter.h"
#include "adc_sd.h"

int sc_main(int argn,char* argc[])
{
  sca_tdf::sca_signal<double> sig_1, sig_2;
  sca_tdf::sca_signal<bool> sig_3;

  sin_source_with_noise sin1("sin1");
  sin1.out(sig_1);

  prefilter prefi1("lp1");
  prefi1.in(sig_1);
  prefi1.out(sig_2);

  adc_sd adc1("adc1");
  adc1.in(sig_2);
  adc1.out(sig_3);

  sca_trace_file* tfp =
    sca_create_tabular_trace_file("tb_lab2c.dat");

  sca_trace(tfp, sig_1, "sig_1");
  sca_trace(tfp, sig_2, "sig_2");
  sca_trace(tfp, sig_3, "sig_3");

  sc_start(5.0, SC_MS);

  tfp->reopen("tb_ac_lab2c.dat");
  tfp->set_mode(sca_ac_format(sca_util::SCA_AC_DB_DEG));

  sca_ac_start(1.0, 1e6, 1000, SCA_LOG);

  return 0;
}
