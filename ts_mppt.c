#include <stdio.h>
#include <stdlib.h>
#include <modbus/modbus.h>

#define MODBUS_ADD    0x01	/* MODBUS Address of the TS_MPPT */

int main(void)
{
	modbus_t* mb_param;
	int ret;
	int errno;
	/* 
 	* 	Setup the serial port parameters 
 	* 	need to create symbolic link e.g: ln -s /dev/ttyUSB0 /dev/ts_mppt
 	*/
	#ifdef TS_MPPT_45
	mb_param = modbus_new_rtu("/dev/ts_mppt_45", 9600, 'N', 8, 2);
	#else
	mb_param = modbus_new_rtu("/dev/ts_45", 9600, 'N', 8, 2);
	#endif
	if (mb_param == NULL) {
	    fprintf(stderr, "Unable to create the libmodbus context\n");
	    return -1;
	}	
	/* Open the MODBUS connection */
	if (modbus_connect(mb_param) == -1) {
	    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
	    modbus_free(mb_param);
	    return -1;
	}
	if(modbus_set_slave(mb_param,MODBUS_ADD)==-1){
	    fprintf(stderr, "set_slave failed: %s\n", modbus_strerror(errno));
	    modbus_free(mb_param);
	    return -1;
	}
	#ifdef TS_MPPT_45
	int n_register=0x5b;
	#else 
	int n_register=0x1e;
	#endif
	uint16_t data[n_register];
	/*
	 Read the RAM Registers from 0x0 to n
 	*/ 
	int rc=modbus_read_registers(mb_param,0x0,n_register,data);
	if(rc==-1){
	    fprintf(stderr, "read_input_register failed: %s\n", modbus_strerror(errno));
	    modbus_free(mb_param);
	    return -1;
	}
	//for debugging
	/* 
	for(int i=0;i<rc;++i)
		printf("%X\t%X\n",i,data[i]);
	printf("\n");
	*/
	#ifdef TS_MPPT_45
	float V_PU=data[0x0];
	/* Filtered ADC */
	float adc_vb_f_med=data[0x18]*V_PU/32768;printf("adc_vb_f_med\t%.2f V\n",adc_vb_f_med);
	float adc_vbterm_f=data[0x19]*V_PU/32768;printf("adc_vbterm_f\t%.2f V\n",adc_vbterm_f);
	float adc_vbs_f=data[0x1A]*V_PU/32768;printf("adc_vbs_f\t%.2f V\n",adc_vbs_f);
	float I_PU=data[0x2];
	float adc_va_f=data[0x1b]*V_PU/32768;printf("adc_va_f\t%.2f V\n",adc_va_f);
	float adc_ib_f_shadow=data[0x1c]*I_PU/32768;printf("adc_ib_f_shadow\t%.2f A\n",adc_ib_f_shadow);
	float adc_ia_f_shadow=data[0x1d]*I_PU/32768;printf("adc_ia_f_shadow\t%.2f A\n",adc_ia_f_shadow);
	float adc_p12_f=data[0x1e]*18.612/32768;printf("adc_p12_f\t%.2f V\n",adc_p12_f);
	float adc_p3_f=data[0x1f]*6.6/32768;printf("adc_p3_f\t%.2f V\n",adc_p3_f);
	float adc_pmeter_f=data[0x20]*18.612/32768;printf("adc_pmeter_f\t%.2f V\n",adc_pmeter_f);
	float adc_p18_f=data[0x21]*3.0/32768;printf("adc_p18_f\t%.2f V\n",adc_p18_f);
	float adc_v_ref=data[0x22]*3.0/32768;printf("adc_v_ref\t%.2f V\n",adc_v_ref);
	/* Temperatures */
	float T_hs=data[0x23];printf("T_hs\t%.2f C\n",T_hs);
	float T_rts=data[0x24];printf("T_rts\t%.2f C\n",T_rts);
	float T_batt=data[0x23];printf("T_batt\t%.2f C\n",T_batt);
	/* Status */
	float adc_vb_f_1m=data[0x26]*V_PU/32768;printf("adc_vb_f_1m\t%.2f V\n",adc_vb_f_1m);
	float adc_ib_f_1m=data[0x27]*I_PU/32768;printf("adc_ib_f_1m\t%.2f A\n",adc_ib_f_1m);
	float vb_min=data[0x28]*V_PU/32768;printf("vb_min\t%.2f V\n",vb_min);
	float vb_max=data[0x29]*V_PU/32768;printf("vb_max\t%.2f V\n",vb_max);
	//...
	/* Charger */
	char* charge_states[]={"START","NIGHT_CHECK","DISCONNECT","NIGHT","FAULT","MPPT","ABSORPTION","FLOAT","EQUALIZE","SLAVE"};
	printf("Charge_state\t%s\n",charge_states[data[0x32]]);
	/* MPPT */
	float power_out_shadow=data[0x3a]*V_PU*I_PU/(1L<<17);printf("power_out_shadow\t%.2f W\n",power_out_shadow);
	float power_in_shadow=data[0x3b]*V_PU*I_PU/(1L<<17);printf("power_in_shadow\t%.2f W\n",power_in_shadow);
	float sweep_Pin_max=data[0x3c]*V_PU*I_PU/(1L<<17);printf("sweep_Pin_max\t%.2f W\n",sweep_Pin_max);
	float Ahc_daily=data[0x43]*0.1;printf("Ahc_daily\t%.2f Ah\n",Ahc_daily);
	float Whc_daily=data[0x44]*0.1; printf("Whc_daily\t%.2f Wh\n",Whc_daily);
	float Pout_max_daily=data[0x46]*V_PU*I_PU/(1L<<17);printf("Pout_max_daily\t%.2f W\n",Pout_max_daily);
	float Tb_max_daily=data[0x48]; printf("Tb_max_daily\t%.2f C\n",Tb_max_daily);
	float time_ab_daily=data[0x4d]; printf("time_ab_daily\t%.2f s\n",time_ab_daily);
	#else
	printf("adc_vb_f\t%.2f V\n",data[0x8]*96.666/(1<<15));
	printf("adc_vs_f\t%.2f V\n",data[0x9]*96.666/(1<<15));
	printf("adc_vx_f\t%.2f V\n",data[0xa]*139.15/(1<<15));
	printf("adc_ipv_f\t%.2f A\n",data[0xb]*66.667/(1<<15));
	printf("adc_iload_f\t%.2f A\n",data[0xc]*316.67/(1<<15));
	printf("vb_f\t%.2f V\n",data[0xd]*96.666/(1<<15));
	printf("t_hs\t%i C\n",data[0xe]);
	printf("t_batt\t%i C\n",data[0xf]);
	printf("v_ref\t%.2f V\n",data[0x10]*96.666/(1<<15));
	//data is 2 bytes
	int Ah_r=((int)data[0x11]<<16)+data[0x12];
	printf("Ah_r\t%.2f Ah\n",Ah_r*0.1);
	int Ah_t=((int)data[0x13]<<16)+data[0x14];
	printf("Ah_t\t%i Ah\n",Ah_t);
	int hourmeter=((int)data[0x15]<<16)+data[0x16];
	printf("hourmeter\t%i h\n",hourmeter);
	int alarm=((int)data[0x1d]<<16)+data[0x17];
	printf("alarm\t%x\n",alarm);
	printf("fault\t%x\n",data[0x18]);
	printf("dip_switch\t%x\n",data[0x19]);
	printf("control_mode\t%x\n",data[0x1a]);
	printf("control_state\t%x\n",data[0x1b]);
	printf("d_filt\t%i\n",data[0x1c]);
	#endif
	exit(0);
}
