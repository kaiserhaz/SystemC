/**
 * PCIX main
 */

/**
 * Includes
 */
#include "pcix_master.h"
#include "pcix_rtl_slave.h"
#include "tlm2rtl_bus.h"

int sc_main(int argc, char* argv[]) {

	sc_set_time_resolution(1, SC_NS);

	pcix_master* pcix_m_0 = new pcix_master("pcix_m_0");
	pcix_rtl_slave* pcix_s_0 = new pcix_rtl_slave("pcix_s_0");
	pcix_bus* pcix_b_0 = new pcix_bus("pcix_b_0");
	tlm2rtl_bus* tlm2rtl_b_0 = new tlm2rtl_bus("tlm2rtl_b_0");
	my_interrupt* tlm2rtl_irq = new my_interrupt("tlm2rtl_irq");
	my_interrupt* rtl2tlm_irq = new my_interrupt("rtl2tlm_irq");

	sc_signal<int> _devnum("devnum"), _addr("addr"), _attr1("attr1"), _attr2("attr2"), _cmnd("cmnd");
	sc_signal<int> _datain[8], _dataout[8];

	sc_trace_file* tfp = sc_create_vcd_trace_file("pcix_trans_adaptor");
	tfp->set_time_unit(1.0, SC_NS);
	tfp->write_comment("PCIX Adaptor/Transactor Trace");

	pcix_m_0->p_slave(*pcix_b_0);
	tlm2rtl_b_0->p_master(*pcix_b_0);

	tlm2rtl_b_0->p_devnum(_devnum);
	tlm2rtl_b_0->p_addr(_addr);
	tlm2rtl_b_0->p_attr1(_attr1);
	tlm2rtl_b_0->p_attr2(_attr2);
	tlm2rtl_b_0->p_cmnd(_cmnd);
	for(int i=0; i<8; i++) {

		tlm2rtl_b_0->p_datain(_datain[i]);
		tlm2rtl_b_0->p_dataout(_dataout[i]);

	}
	tlm2rtl_b_0->p_tlm2rtl(*tlm2rtl_irq);
	tlm2rtl_b_0->p_rtl2tlm(*rtl2tlm_irq);

	pcix_s_0->p_devnum(_devnum);
	pcix_s_0->p_addr(_addr);
	pcix_s_0->p_attr1(_attr1);
	pcix_s_0->p_attr2(_attr2);
	pcix_s_0->p_cmnd(_cmnd);
	for(int i=0; i<8; i++) {

		pcix_s_0->p_datain(_dataout[i]);
		pcix_s_0->p_dataout(_datain[i]);

	}
	pcix_s_0->p_tlm2rtl(*tlm2rtl_irq);
	pcix_s_0->p_rtl2tlm(*rtl2tlm_irq);

	sc_trace(tfp, _devnum, "devnum");
	sc_trace(tfp, _addr, "addr");
	sc_trace(tfp, _attr1, "attr1");
	sc_trace(tfp, _attr2, "attr2");
	sc_trace(tfp, _cmnd, "cmnd");
	for(int i=0; i<8; i++) {

		sc_trace(tfp, _datain[i], "datain");
		sc_trace(tfp, _dataout[i], "dataout");

	}
	
	sc_start();

	sc_close_vcd_trace_file(tfp);

	system("pause");

	return 0;

}
