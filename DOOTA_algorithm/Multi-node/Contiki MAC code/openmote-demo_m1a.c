#include "contiki.h"
#include "dev/leds.h"
#include "net/rime/rime.h"
#include <stdio.h>
static int z=0;
static int Conf=0;
static float Ees=0;
static float Eem=0;
static float Kei=0;
static float Te=20;
static float bat_m=74114;
//static int Tee;
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
PROCESS(example_broadcast_process, "Broadcast example");
AUTOSTART_PROCESSES(&example_broadcast_process);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
	
  leds_on(LEDS_GREEN);
   proc+=1;
    xx=1;
con+=1;
printf("Received counter %d:",con); 
//printf("Name adress %d.%d: \n",from->u8[0], from->u8[1]);
 packetbuf_copyto(rec);
Ees=rec[0];  
        ax=Ees*1000;       
  printf("Received from Slave Ees_org %d.%u\n : ",ax / 1000,ax % 1000);
        Eem=rec[2];       
        bx=Eem*1000;
  printf("Received from Slave Eem_org %d.%u\n : ",bx / 1000,bx % 1000);
     Kei=-rec[1];
        cx=rec[1]*1000;       
  printf("Received from Slave Kei_org %d.%u\n : ",cx / 1000,cx % 1000);
 leds_off(LEDS_GREEN);
//process
leds_on(LEDS_YELLOW);
       
//if(Eem==0 || Ees==0 || Kei==0 )
{
       
            Tx=Te*10;
            if(Conf!=1)
            {
                Eest=(Ees*Kei);
                Eemt=(Eem-(Ees*Kei));
                T=(bat_m-(Te*Eest))/Eemt;  //calculation T;
                xT=T*10;
                if (Tx==xT)
                    Conf=1;
                else
                    Te=T;
//return 0;
            }           
        }
        leds_off(LEDS_YELLOW);
con1+=1;
printf("process counter %d:",con1); 
proc=0;        
     
     
}
/*---------------------------------------------------------------------------*/
/*static void
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
/*---------------------------------------------------------------------------*/
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  broadcast_open(&broadcast, 146, &broadcast_call);

    
   // etimer_set(&et, 1*CLOCK_SECOND);
    
   // PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));




  while(Conf!=1) {
   // static struct etimer et;
    //linkaddr_t addr;
    
    etimer_set(&et, 1*CLOCK_SECOND);
    
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
etimer_set(&et, 1*CLOCK_SECOND);
    
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
//if(lb==1 || lb==1)
//{
//PROCESS_WAIT_EVENT_UNTIL(lb==1 && la==1);
//}
    leds_on(LEDS_RED);
send[0]=Conf;
send[1]=Te;
static int ia;
ia=Te*1000;
      /*  packetbuf_copyfrom(send,sizeof(send));
        addr.u8[0] = 0x9b;
	addr.u8[1] = 0x80; 

        if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
      unicast_send(&uc, &addr);
printf("broadcast confirm sent to Slave %d\n",Conf);
        printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
}
//packetbuf_copyfrom(send,sizeof(send));
  //      addr.u8[0] = 0x9b;
	//addr.u8[1] = 0x7c; 

        //if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
      //unicast_send(&uc, &addr);
//printf("broadcast confirm sent to Slave %d\n",Conf);
  //      printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
//}
packetbuf_copyfrom(send,sizeof(send));
        addr.u8[0] = 0x9a;
	addr.u8[1] = 0xe0; 

        if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
      unicast_send(&uc, &addr);
printf("broadcast confirm sent to Slave %d\n",Conf);
        printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
}*/
packetbuf_copyfrom(send,sizeof(send));
          broadcast_send(&broadcast);
printf("broadcast confirm sent to Slave %d\n",Conf);
        printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
        leds_off(LEDS_RED);
      counter+=1;  
  z+=1;
printf("send counter %d:",z);
       

  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

