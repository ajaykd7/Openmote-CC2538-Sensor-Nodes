#include "contiki.h"
#include "net/rime/rime.h"
#include "dev/leds.h"
#include <stdio.h>
//Start coding
//Initialization 
static int z=0;
static float Pre_m[12]={2.1009,61.7919,20.9864,0.0226,0.0122,0.3358,0.3587,9.0916,1.0259,0.7463,1.0892,0.5158};
static float Pre_s[12]={2.1009,61.7919,20.9864,0.0226,0.0122,0.3358,0.3587,9.0916,1.0259,0.7463,1.0892,0.5158};
static float Edm[12]={-1.5843,0.7922,0.7396,-0.0031,0.0248,-0.7891,-0.7643,0,0,0,0.7922,0.7922};
static float Eds[12]={1.6432,-0.8216,-0.7670,0.0032,-0.0257,0.8184,0.7927,0,0,0,-0.8216,-0.8216};
static float X[3][12]={{0,0,0,0,0,0,0,0,0,0,0,1},{0,0,0,1,0,1,1,1,1,1,1,1},{0,1,1,1,1,1,1,1,1,1,1,1}};
static float bat_s=18742;
static float Te=20 ;
static float Es[12];
static float Em[12];
static float Esi_c=0;
static float Esi_b=0;
static float Esi_a=0;
static float Em_c=0;
static float Em_b=0;
static float Em_a=0;
static float Kei=0;
static int Conf=0;
static int exit=0;
static int ax=0;
static int on=0;
static float send[3]={0,0,0};
static float rec[2]={0,0};
static int con=0;
static int con1=0;
static float Ees,Eem,A0, A1,B0,B1;
static int i,yy;
/*---------------------------------------------------------------------------*/
PROCESS(example_unicast_process, "Example unicast");
AUTOSTART_PROCESSES(&example_unicast_process);
/*---------------------------------------------------------------------------*/
static void
recv_uc(struct unicast_conn *c, const linkaddr_t *from)
{
    //Recive from master
    leds_on(LEDS_GREEN);
    on=1;
    packetbuf_copyto(rec);
    Conf=rec[0];
   // printf("Received Confarmation %d\n:",Conf);
    Te=rec[1];
    ax=Te*1000;
   // printf("Received Te %d.%d\n:",ax/1000,ax%1000);
    con+=1;
    //printf("Received counter %d:",con);
    leds_off(LEDS_GREEN);

    //process work
    if(Conf!=1)
    {
        Esi_c=0;
        Esi_b=0;
        Esi_a=0;
        Em_c=0;
        Em_b=0;
        Em_a=0;
        for(i=0;i<12;i++)
        {
            Es[i]=Eds[i]+Pre_s[i];
            Em[i]=Edm[i]+Pre_m[i];
            //the energy cost of the slave
            Esi_c += Es[i]*(1-X[0][i]) ;//+ calculat Esi(xci)
            Esi_b += Es[i]*(1-X[1][i]) ;//+ calculat Esi(xbi)
            Esi_a += Es[i]*(1-X[2][i]) ;//+ calculat Esi(xai)
            Em_c += Em[i]*X[0][i];//+ calculat Emi(xci); % master has to manege all of the slave nodes
            Em_b += Em[i]*X[1][i];//+ calculat Emi(xbi); % master has to manege all of the slave nodes
            Em_a += Em[i]*X[2][i];//+ calculat Emi(xai); % master has to manege all of the slave nodes
        }
        //Calculation A0,A1,B0,B1
        A0=(Em_a-Em_b)/(Esi_a-Esi_b);
        A1=(Em_b-Em_c)/(Esi_b-Esi_c);
        B0=((Esi_a*Em_b)-(Em_a*Esi_b))/(Esi_a-Esi_b);
        B1=((Esi_b*Em_c)-(Em_b*Esi_c))/(Esi_b-Esi_c);
        Ees=bat_s/Te;
        //calculation limit of Ees value
        if(Ees<Esi_a)
            Ees=Esi_a;
        else if (Ees>Esi_c)
            Ees=Esi_c;
        //calculation which optimal line use
        if(Esi_a<=Ees && Ees<=Esi_b)
        { Eem=A0*Ees+B0;
            Kei=(Em_a-Eem)/(Esi_a-Ees);
            yy=0;}
        else if(Esi_b<=Ees && Ees<=Esi_c)
        { Eem=A1*Ees+B1;
            Kei=(Em_b-Eem)/(Esi_b-Ees);
            yy=1;
        }
    }
    //part 2
    else        //when master node send confirm massage
    {       Ees=bat_s/Te;
        if(Ees<Esi_a)
            Ees=Esi_a;
        else if(Ees>Esi_c)
            Ees=Esi_c;
        // calculate weght
        static float Wa=0;
        static float Wb=0;
        static float Wc=0;
        //float Wxxa=[];
        static float Wbc=0;
        static float Wab=0;
        //static float Wxx;
        if(yy==0)
        {
            Wa=(Esi_b-Ees)/(Esi_b-Esi_a);
            Wb=(Esi_a-Ees)/(Esi_a-Esi_b);
            Wab=Wa+Wb;
            // Wxx={{1,((Wa*Te)/Wab),X[2][1]},{1,((Wb*Te)/Wab),X[1][1]}};
            // Wxxa=[Wxxa;Wxx];
        }
        else if(yy==1 )
        {     Wb=(Esi_c-Ees)/(Esi_c-Esi_b);
            Wc=(Esi_b-Ees)/(Esi_b-Esi_c);
            Wbc=Wc+Wb;
            // Wxx=[ay ((Wb*Te)/Wbc) ip(2,:);ay ((Wc*Te)/Wbc) ip(1,:)];
            //                Wxx={{1,((Wb*Te)/Wbc),X[2][]},{1,((Wc*Te)/Wbc),X[1][]}};
            //                  Wxxa=[Wxxa;Wxx];
        }
        exit=1;
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
       

   
 while(exit!=1) {
         static struct etimer et;
etimer_set(&et, 1*CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

       linkaddr_t addr;    
  CLOCK_SECOND;
clock_wait(80); 
 
PROCESS_PAUSE();
clock_wait(80);
packetbuf_copyfrom(send, sizeof(send));
            addr.u8[0] = 0x9a;
            addr.u8[1] = 0xc7;
            if(!linkaddr_cmp(&addr, &linkaddr_node_addr)) {
                unicast_send(&uc, &addr);
                
            }  


  
 
}
   

    PROCESS_END();
}
/*---------------------------------------------------------------------------*/

