#include "contiki.h"
#include "net/rime/rime.h"
#include "dev/leds.h"
#include "cpu.h"
#include "sys/etimer.h"
#include "dev/uart.h"
#include "dev/button-sensor.h"
#include "dev/serial-line.h"
#include "dev/sys-ctrl.h"
#include "net/rime/unicast.h"

#include "dev/adxl346.h"
#include "dev/max44009.h"
#include "dev/sht21.h"
#include <stdio.h>
#include "dev/gpio.h"

static int z=0;
static int Conf=0;
static float Te=20;
static float bat_m=74114;
static int xx=0;
static int xT=0;
static int Tx=0;
static int counter=0;
static int proc=0;
static float send[2]={0,0};
static float rec[3]={0,0,0};
static int con=0;
static int con1=0;
static int ax,bx,cx;
static float T,Eest,Eemt;
static float Ees[3]={0,0,0};
static float Eem[3]={0,0,0};
static float Kei[3]={0,0,0};
static int i;
static int la=0;
static int lb=0;
static int lc=0;

/*---------------------------------------------------------------------------*/
PROCESS(example_unicast_process, "Example unicast");
AUTOSTART_PROCESSES(&example_unicast_process);
/*---------------------------------------------------------------------------*/
static void
recv_uc(struct unicast_conn *c, const linkaddr_t *from)
{   
    
}
/*---------------------------------------------------------------------------*/
static void
sent_uc(struct unicast_conn *c, int status, int num_tx)
{
    const linkaddr_t *dest = packetbuf_addr(PACKETBUF_ADDR_RECEIVER);
    if(linkaddr_cmp(dest, &linkaddr_null)) {
        return;
    }
    // printf("unicast message sent to %d.%d: status %d num_tx %d\n",
    //   dest->u8[0], dest->u8[1], status, num_tx);
}
/*---------------------------------------------------------------------------*/
static const struct unicast_callbacks unicast_callbacks = {recv_uc, sent_uc};
static struct unicast_conn uc;

PROCESS_THREAD(example_unicast_process, ev, data)
{
    PROCESS_EXITHANDLER(unicast_close(&uc);)
            PROCESS_BEGIN();
    static struct etimer et;
    unicast_open(&uc, 146, &unicast_callbacks);
adc_init();
GPIO_SET_OUTPUT(GPIO_B_BASE,0x02);   // Set DC-DC converter pin as output
//GPIO_SET_PIN(GPIO_B_BASE,0x2);      // Set DC-DC converter pin as  1
GPIO_CLR_PIN(GPIO_B_BASE,0x2);
 linkaddr_t addr;
    while(1) 
{
        
etimer_set(&et, 10*CLOCK_SECOND);
PROCESS_YIELD();
      //  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
//clock_wait(2);
//clock_delay_usec(10000);
//clock_delay(1000);
static int lll=0;
static int lll1=0;
static int lll2=0;

/*for(lll=0;lll<100000;lll++)
{
while(lll1<100000)
{
lll1+=1;
while(lll2<10000)
{
lll2+=1;
}
}*/
/*
for(lll=0;lll<600000;lll++)
{
for(lll1=0;lll1<100000;lll1++)
{
for(lll2=0;lll2<100000;lll2++)
{
}
}
}
*/

//clock_wait(100000);
//CLOCK_SECOND;

/*clock_delay(100000000);
printf("broadcast Te sent to Slave");
clock_delay(100000000);
printf("broadcast Te sent to Slave");
clock_delay(100000000);
printf("broadcast Te sent to Slave");
printf("broadcast Te sent to Slave");
clock_delay(100000000);
printf("broadcast Te sent to Slave");
clock_delay(100000000);
//clock_delay(100000000);
//clock_delay(10000000);
clock_delay(10000000);
clock_delay(10000000);
clock_delay(10000000);
clock_delay(10000000);
clock_delay(10000000);*/
for(lll=0;lll<1000;lll++)
{
clock_delay(400);
}
for(lll1=0;lll1<1000;lll1++)
{
clock_delay(400);
}
packetbuf_copyfrom(send,sizeof(send));
        addr.u8[0] = 0x9b;
        addr.u8[1] = 0x80;
        if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
            unicast_send(&uc, &addr);
            //printf("broadcast confirm sent to Slave %d\n",Conf);
            //printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
        }

}
    PROCESS_END();
}
/*---------------------------------------------------------------------------*/

