#include "contiki.h"
#include "net/rime/rime.h"
#include "dev/leds.h"
#include <stdio.h>
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
    leds_on(LEDS_GREEN);
    proc+=1;
    xx=1;
    con+=1;
    //printf("Received counter %d:",con);
    packetbuf_copyto(rec);
    if(from->u8[0] == 155 && from->u8[1]==128)
    {
        Ees[0]=rec[0];
        //ax=Ees[0]*1000;
        //printf("Received from Slave Ees_2 %d.%u\n : ",ax / 1000,ax % 1000);
        Eem[0]=rec[2];
        //bx=Eem[0]*1000;
        //printf("Received from Slave Eem_2 %d.%u\n : ",bx / 1000,bx % 1000);
        Kei[0]=-rec[1];
       // cx=Kei[0]*1000;
        //printf("Received from Slave Kei_2 %d.%u\n : ",cx / 1000,cx % 1000);
        la=1;
    }
    else if(from->u8[0] ==155  && from->u8[1]==124)
    {
        Ees[1]=rec[0];
        //ax=Ees[1]*1000;
       // printf("Received from Slave Ees_3 %d.%u\n : ",ax / 1000,ax % 1000);
        Eem[1]=rec[2];
       // bx=Eem[1]*1000;
       // printf("Received from Slave Eem_3 %d.%u\n : ",bx / 1000,bx % 1000);
        Kei[1]=-rec[1];
       // cx=Kei[1]*1000;
       //printf("Received from Slave Kei_3 %d.%u\n : ",cx / 1000,cx % 1000);
        lb=1;
    }
    else if(from->u8[0] ==154  && from->u8[1]==224)
    {
        Ees[2]=rec[0];
        //ax=Ees[2]*1000;
        //printf("Received from Slave Ees_3 %d.%u\n : ",ax / 1000,ax % 1000);
        Eem[2]=rec[2];
        //bx=Eem[2]*1000;
       //printf("Received from Slave Eem_3 %d.%u\n : ",bx / 1000,bx % 1000);
        Kei[2]=-rec[1];
       // cx=Kei[2]*1000;
       // printf("Received from Slave Kei_3 %d.%u\n : ",cx / 1000,cx % 1000);
        lc=1;
    }
    leds_off(LEDS_GREEN);
//clock_delay_usec((2000));

    //process
   // printf("check my value %d:%d:%d\n : ",la,lb,lc);

    if(la==1 && lb==1 && lc==1)
    {
        leds_on(LEDS_YELLOW);
        Tx=Te*100;
        if(Conf!=1)
        {
            Eest=0;
            Eemt=0;
            for(i=0;i<3;i++)
            {
                Eest+=(Ees[i]*Kei[i]);
                Eemt+=(Eem[i]-(Ees[i]*Kei[i]));
            }
            T=(bat_m-(Te*Eest))/Eemt;  //calculation T;
            xT=T*100;
            if (Tx==xT)
                Conf=1;
            else
                Te=T;
        }
        leds_off(LEDS_YELLOW);
        lb=0;
        la=0;
        lc=0;
        con1+=1;
       // printf("process counter %d:",con1);
        proc=0;
    }
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
    while(Conf!=1) {
        // static struct etimer et;
        linkaddr_t addr;
        leds_on(LEDS_RED);
        send[0]=Conf;
        send[1]=Te;
        static int ia;
        //ia=Te*1000;
        leds_off(LEDS_RED);
        packetbuf_copyfrom(send,sizeof(send));
        addr.u8[0] = 0x9b;
        addr.u8[1] = 0x80;
        if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
            unicast_send(&uc, &addr);
           // printf("broadcast confirm sent to Slave %d\n",Conf);
           // printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
//clock_delay_usec((2000));        
}
        packetbuf_copyfrom(send,sizeof(send));
        addr.u8[0] = 0x9b;
        addr.u8[1] = 0x7c;
        if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
            unicast_send(&uc, &addr);
           // printf("broadcast confirm sent to Slave %d\n",Conf);
           // printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);

//clock_delay_usec((2000));
        }
        etimer_set(&et, 1*CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        packetbuf_copyfrom(send,sizeof(send));
        addr.u8[0] = 0x9a;
        addr.u8[1] = 0xe0;
        if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
            unicast_send(&uc, &addr);
           // printf("broadcast confirm sent to Slave %d\n",Conf);
           //printf("broadcast Te sent to Slave %d.%d\n",(ia)/1000,(ia)%1000);
        }


        leds_off(LEDS_RED);
        counter+=1;
        z+=1;
      // clock_delay_usec((2000));
        //printf("send counter %d:",z);
        etimer_set(&et, 1*CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        etimer_set(&et, 1*CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    }
//clock_wait(0.000001);
clock_delay_usec((78.2));
static int ll=0;
for (ll=0;ll>10;ll++)
{
}
etimer_set(&et, 1*CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
//clock_wait(1);
//clock_delay((1));
etimer_set(&et, 1*CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
//clock_delay_usec((2000));
//CLOCK_SECOND;
//clock_wait(2);
//clock_delay_usec((2000));
//clock_wait(2);
//clock_delay_usec((2000));
//clock_wait(2);
    PROCESS_END();
}
/*---------------------------------------------------------------------------*/

