#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"
#include "dev/button-sensor.h"
#include "contiki.h"
#include "cpu.h"
#include "sys/etimer.h"
#include "dev/leds.h"
#include "dev/uart.h"
#include "dev/button-sensor.h"
#include "dev/serial-line.h"
#include "dev/sys-ctrl.h"
#include "net/rime/broadcast.h"
#include "net/ip/uipopt.h"
#include "dev/adxl346.h"
#include "dev/max44009.h"
#include "dev/sht21.h"
#include "dev/leds.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
//#include "powertrace.h"
#include "random.h"
//Start coding
//Initialization 
static int z=0;
static int Conf=0;
static float Ees=0;
static float Eem=0;
static float Kei=0;
static float Te=20;
static float bat_m=74114;
static int Tee;
static int xx=0;
static int xT=0;
static int Tx=0;
static int counter=0;
static int proc=1;
static float send[2]={0,0};
static float rec[3]={0,0,0};
static int con=0;
static int con1=0;
static int ax,bx,cx;
static int on=1;
/*---------------------------------------------------------------------------*/
#define UNICAST_CHANNEL   146
PROCESS(example_unicast_process, "Example unicast");
AUTOSTART_PROCESSES(&example_unicast_process);
/*---------------------------------------------------------------------------*/
	
// for Reciving
static void
recv_uc(struct unicast_conn *c, const linkaddr_t *from)
{
  
    leds_on(LEDS_GREEN);
   proc=1;
    xx=1;
con+=1;
printf("Received counter %d:",con); 
 packetbuf_copyto(rec); 
on=1;
Ees=rec[0];  
        ax=Ees*1000;       
  printf("Received from Slave Ees %d.%u\n : ",ax / 1000,ax % 1000);
        Eem=rec[2];       
        bx=Eem*1000;
  printf("Received from Slave Eem %d.%u\n : ",bx / 1000,bx % 1000);
     Kei=-rec[1];
        cx=Kei*1000;       
  printf("Received from Slave Kei %d.%u\n : ",cx / 1000,cx % 1000);
//
printf("process: %d",proc );

        //ax=Ees*1000;       
  //printf("Received from Slave Ees_org %d.%u\n : ",ax / 1000,ax % 1000);
      //  Eem=rec[2];       
      //  bx=Eem*1000;
 // printf("Received from Slave Eem_org %d.%u\n : ",bx / 1000,bx % 1000);
    // Kei=-rec[1];
      //  cx=rec[1]*1000;       
 // printf("Received from Slave Kei_org %d.%u\n : ",cx / 1000,cx % 1000);//rintf("process: %d",proc ); 
   
       //printf("broadcast message received from Master%d.%d: %d.%u\n, %d.%u\n, %d.%u\n",from->u8[0], from->u8[1] ,ax / 1000,bx / 1000,cx / 1000,ax % 1000,bx % 1000,cx % 1000);
    leds_off(LEDS_GREEN);

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
// processing part
static const struct unicast_callbacks unicast_callbacks = {recv_uc, sent_uc};
static struct unicast_conn uc;
//static float powertrace_start powertrace_start;
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(example_unicast_process, ev, data)
{
    static struct etimer et;
    static float T,Eest,Eemt;
     linkaddr_t addr;
    PROCESS_EXITHANDLER(unicast_close(&uc);)
    
  PROCESS_BEGIN();
unicast_open(&uc, 146, &unicast_callbacks) ;
			

    while(Conf!=1)
    {

 
        if(xx>0)
        {
 leds_on(LEDS_YELLOW);
    
if(proc==1)
{
       
            Tx=Te*1000;
            if(Conf!=1)
            {
Eest=0;
Eemt=0;
T=0;
                Eest=(Ees*Kei);
                Eemt=(Eem-(Ees*Kei));
                T=(bat_m-(Te*Eest))/Eemt;  //calculation T;
                xT=T*1000;
                if (Tx==xT)
                    Conf=1;
                else
                    Te=T;
            }           
        }
        leds_off(LEDS_YELLOW);
con1+=1;
printf("process counter %d:",con1); 
proc=0;        
} 
       Tee=Te*1000;
        //printf("broadcast Te:%d.%u\n",Tee/1000,Tee%1000);
        //printf("confirm:%d\n",Conf);
        /* Start powertracing, once every two seconds. */
  
        // sending part
    
         
	//powertrace_start(CLOCK_SECOND * 1);                
        leds_on(LEDS_RED);
send[0]=Conf;
send[1]=Te;
static int ia;
ia=Te*1000;
        packetbuf_copyfrom(send,sizeof(send));
        addr.u8[0] = 0x9a;
	addr.u8[1] = 0xc7; 
 leds_off(LEDS_RED);
        if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
      unicast_send(&uc, &addr);
 printf("broadcast confirm sent to Slave\n");
printf("broadcast confirm sent to Slave %d\n",Conf);
        printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
       
      counter+=1;  
  z+=1;
printf("send counter %d:",z);

    } 
etimer_set(&et, 3 * CLOCK_SECOND);  // timer use(etimer)      
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));              
 
    } 
    printf("counter:%d\n",counter);    
    printf("broadcast Te:%d.%u\n",Tee/1000,Tee%1000);  
    //powertrace_stop(); 
/* Delay 2-4 seconds */
 etimer_set(&et, 4 * CLOCK_SECOND);  // timer use(etimer)      
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));       
    PROCESS_END();
 
}

/*---------------------------------------------------------------------------*/
