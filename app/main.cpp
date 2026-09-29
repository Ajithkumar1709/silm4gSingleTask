
#ifndef MBTK_SIMCOM_SUPPORT

extern "C" {

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mbtk_api.h"
#include "mbtk_comm_api.h"
#include <locale.h>
}

#include <string.h>

 
class People{
    public:
        People(int n, int m, char *x, int y){
            age = n;
            weight = m;
            strcpy(name, x);
            height = y;
        }
        //成员变量
        char name[20];
        int height;
        void people_display(){
            op_uart_printf("age %d", age);
            op_uart_printf("weight %d", weight);
            op_uart_printf("height %d", height);
			op_uart_printf("name %s", name);
        }
    private:
        int age;
        int weight;

};


class CException
{
	public:
	    char msg[50];
	    CException(char *s) { strcpy(msg,s);}
};



class BlackPeople : public People{
	public:
        BlackPeople(int n, int m, char *x, int y):People(n,m,x,y)
		{
			a = 100;
			b = 1000;
			
        }

		void people_display(){
            op_uart_printf("a %d", a);
            op_uart_printf("b %d", b);

			People::people_display();
		}

	private :
	   int a;
	   int b;
	
};


double Devide(double x, double y)
{
    if (y == 0)
        throw CException("devided by zero");

    op_uart_printf("in Devide."); 
    return x / y;
}
int CountTax(int salary)
{

	op_uart_printf("CountTax");
    try {
        if (salary < 0)
            throw  -1;
        op_uart_printf("counting tax");
    }
    catch (int) {
        op_uart_printf("salary < 0");
    }
    op_uart_printf("tax counted");
    return salary * 0.15;
}


void exception_test()
{

    double f = 1.2;

	op_uart_printf("exception_test");
    try {
        CountTax(-1);
        f = Devide(3, 0);
        op_uart_printf("end of try block");
    }

	catch (int) {
        op_uart_printf("salary11 < 0");
    }
    catch (CException e) {
        op_uart_printf("exception %s", e.msg);
    }
	
    op_uart_printf("f = %f", f);
    op_uart_printf("finished");
}


extern "C" {

	mbtk_taskref mbtk_test_task_ref;
	mbtk_taskref my_task_ref = NULL;
	extern void my_demo(void *arg);

	mbtk_taskref mqtt_demo_task_ref = NULL;
	extern void mqtt_demo(void);

	static void mqtt_demo_task(void *arg)
	{
		(void)arg;
		mqtt_demo();
		/* mqtt_demo() returns after its 5 publishes; don't return from the task */
		while (1)
		{
			ol_os_task_sleep(6000);
		}
	}


	void nitz_ind_callback(void)
	{
	    op_uart_printf("updateTimeFromNitz finish");
	}

	void test_reject_callback(ol_NW_REJECT_CAUSE *param)
	{
		ol_NW_REJECT_CAUSE *cause = (ol_NW_REJECT_CAUSE *)param;
		
		op_uart_printf("a reject event report\r\n");
		op_uart_printf("mcc = %d,mnc = %d,cause = %d,time = %s",cause->mcc,
			cause->mnc,cause->rejectcause,cause->timestamp);
	}


	void app_open_task(void *argv)
	{
		char *btime;
		People testp(10,30,"nihao", 120);
		ol_set_nitz_ind_cb(nitz_ind_callback);
		ol_nw_set_reject_callback(test_reject_callback);
		ol_os_task_sleep(5*200);
		btime = ol_get_buildtime();
		op_uart_printf("ol_dev_get_build time build time:%s \n",btime);
		op_uart_printf("powerup reason: %d\n", ol_powerup_get_reason());

		testp.people_display();

		People *aaaa;
		aaaa = new People(10,330,"n222222ihao", 120);
		aaaa->people_display();

		//exception_test();

		delete aaaa;

		BlackPeople black(20,10,"black", 200);
		black.people_display();

        cdc_uart_printf("my demo start\r\n");
		//demo_menu_test();
		/* bumped from 8192: my_demo() + payLoadAutoUpload()/dataStore.c calls
		 * stack several hundred-byte structs deep, and a stack overflow
		 * crashes silently (no log line) straight into a watchdog reset. */
		ol_os_task_creat(&my_task_ref, NULL, 12288, 220,
                 "my_task", my_demo, NULL);

		/* TLS MQTT test: run mqtt_demo instead of my_demo (both use the IMEI
		 * as client ID, so the broker would kick one off if both ran). */
		// ol_os_task_creat(&mqtt_demo_task_ref, NULL, 16384, 220,
        //          "mqtt_demo_task", mqtt_demo_task, NULL);


	}


static void pwrkey_test_callback(void)
{
	ol_pwrkey_intc_enable(0);	//disable pwrkey intc
	op_uart_printf("pwrkey_test_callback! %d\r\n",ol_get_pwrkey_status());

	

	ol_pwrkey_intc_enable(1);	//enable pwrkey intc
}

	void user_app_init(open_api_table *api_table)
	{
	  //setlocale(LC_ALL, "C");
	  mbtk_api_init(api_table);
	  init_cdc_uart();
	  
	 
		op_uart_printf("app hello, world\r\n");
		
		ol_pwrkey_register_irq(pwrkey_test_callback);
		ol_pwrkey_intc_enable(1);	//enable pwrkey intc
		ol_set_syssleep_status(MBTK_SLEEP_DISABLE);
		ol_os_task_creat(&mbtk_test_task_ref,NULL, 50*1024, 220, "app_at_task", app_open_task, NULL);

		
		while(1)
		{
			/* 30s, matching my_demo's cycle so the idle loop gets a real
			 * chance to enter low power instead of waking every ~1s. */
			ol_os_task_sleep(6000);
			op_uart_printf("app hello, 1   %d\r\n", ol_get_pwrkey_status());
			op_uart_printf("adc, %d,%d,%d\r\n", ol_adc_get_vol(mbtk_adc_index_0),ol_adc_get_vol(mbtk_adc_index_1),ol_adc_get_vol(mbtk_adc_index_2));

			mbtk_task_info_struct_ex info;
			if (my_task_ref && ol_os_get_task_info_ex(my_task_ref, &info) == mbtk_os_success) {
				op_uart_printf("stack my_task: inuse=%lu peak=%lu size=%lu\r\n",
					info.pStackInuse, info.pStackPeak, info.task_stack_size);
			}
		}
		
	}
}

extern "C" {

	void *__wrap_malloc(size_t num)
	{
		//op_uart_printf("call ol_malloc\r\n");
		return ol_malloc(num);
	}

	void __wrap_free(void *free)
	{
		//op_uart_printf("call ol_free\r\n");
		return ol_free(free);
	}

	void *__wrap_calloc(size_t ptr , size_t size)
	{
		//op_uart_printf("call ol_calloc\r\n");
		return ol_calloc(ptr,size);
	}

	void *__wrap_realloc(void * ptr, size_t size)
	{
		//op_uart_printf("call ol_realloc\r\n");
		return ol_realloc(ptr,size);
	}

}

void *operator new(size_t size)
{
 
    op_uart_printf("new mem: %d", size);
 
    return ol_malloc(size);
}
 
void operator delete(void* ptr)
{
    op_uart_printf("delete mem: %u", ptr);
 
    ol_free(ptr);
}


#else
extern "C" {

    #include "mbtk_api_init.h"

    extern void sAPP_SimcomUIDemo(void);

    void user_app_init(open_api_table *api_table)
    {
        mbtk_api_init(api_table);
        sAPP_SimcomUIDemo();
    }
}
#endif
