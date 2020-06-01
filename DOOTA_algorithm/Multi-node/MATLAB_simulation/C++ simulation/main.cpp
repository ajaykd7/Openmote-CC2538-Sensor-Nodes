#include <QCoreApplication>
#include <iostream>>
using namespace std;
int main()
{for(int ia=1;ia<2;ia++)
    {
        /*initialization*/
        // static float Pre_m[12]={1.4740,43.3548,14.7246,0.0159,0.0085,0.2356,0.2517,6.3789,0.7198,0.5236,0.7642,0.3619};
        // static float Pre_s[12]={1.5230,44.7949,15.2137,0.0164,0.0088,0.2435,0.2600,6.5908,0.7437,0.5410,0.7896,0.3739};
        //static float Edm[12]={-4.534,2.2675,2.1169,-0.0089,0.0709,-2.2586,-2.1877,0,0,0,2.2675,2.2675};
        //static float Eds[12]={ 1.4444,-0.7222,-0.6742,0.0028,-0.0226,0.7194,0.6968,0,0,0,-0.7222,-0.7222};
        //float Pre_m[12]={2.1009,61.7919,20.9864,0.0226,0.0122,0.3358,0.3587,9.0916,1.0259,0.7463,1.0892,0.5158};
       float Pre_m[12]={0.46227456,18.81,6.384,0.00077862,0.00011514,0.0099978,0.014136,2.622,0.13016064,0.043776,0.05603328,0.06595584};
        //float Pre_s[12]={2.1009,61.7919,20.9864,0.0226,0.0122,0.3358,0.3587,9.0916,1.0259,0.7463,1.0892,0.5158};
        float Pre_s[12]={0.46227456,18.81,6.384,0.00077862,0.00011514,0.0099978,0.014136,2.622,0.13016064,0.043776,0.05603328,0.06595584};
       //float Edm[12]={-1.5843,0.7922,0.7396,-0.0031,0.0248,-0.7891,-0.7643,0,0,0,0.7922,0.7922};
        float Edm[12]={-0.0849,0.04247,0.03965,-0.00016,0.00133,-0.0423,-0.0409,0,0,0,0.04247,0.04247};
       //float Eds[12]={1.6432,-0.8216,-0.7670,0.0032,-0.0257,0.8184,0.7927,0,0,0,-0.8216,-0.8216};
       float Eds[12]={0.4737,-0.2368,-0.2211,0.00092,-0.0074,0.2359,0.2285,0,0,0,-0.2368,-0.2368};
       float X[3][12]={{0,0,0,0,0,0,0,0,0,0,0,1},{0,0,0,1,0,1,1,1,1,1,1,1},{0,1,1,1,1,1,1,1,1,1,1,1}};
        float NoS=1;
        float bat_s=20000;
        float bat_m=19999;
        float Te=20 ;
        float Es[12];
        float Em[12];
        float Esi_c=0;
        float Esi_b=0;
        float Esi_a=0;
        float Em_c=0;
        float Em_b=0;
        float Em_a=0;
        //float Kei[k];
        int yy;
        // float Ees[k];
        // float Eem[k];
        float A0;
        float A1;
        float B0;
        float B1;
        int Conf=0;
        int exit=0;
        float Eemt;
        float Eest;
        float T;
        float test1;
        float test2;
        int num=0;
        float Ees[3]={0,0,0};
        float Eem[3]={0,0,0};
        float Kei[3]={0,0,0};
        //float Wxx[2][3]={{0,0,0},{0,0,0}};

        // test1=bat_m/(ia*7);
        //test2=bat_s/(ia*7);
        //  bat_m=test1;
        //  bat_s=test2;
        while(exit!=1)
        {num++;
            for (int k=0;k<1;k++)
            {
                if(Conf!=1)
                {

                    Esi_c=0;
                    Esi_b=0;
                    Esi_a=0;
                    Em_c=0;
                    Em_b=0;
                    Em_a=0;
                    for(int i=0;i<12;i++)
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
                    Ees[k]=bat_s/Te;
                    //calculation limit of Ees[k] value
                    if(Ees[k]<Esi_a)
                        Ees[k]=Esi_a;
                    else if (Ees[k]>Esi_c)
                        Ees[k]=Esi_c;

                    //calculation which optimal line use
                    if(Esi_a<=Ees[k] && Ees[k]<Esi_b)
                    { Eem[k]=A0*Ees[k]+B0;
                        Kei[k]=(Em_a-Eem[k])/(Esi_a-Ees[k]);
                        yy=0;}
                    else if(Esi_b<=Ees[k] && Ees[k]<=Esi_c)
                    { Eem[k]=A1*Ees[k]+B1;
                        Kei[k]=(Em_b-Eem[k])/(Esi_b-Ees[k]);
                        yy=1;}

                }
                // }

                //part 2
                else        //when master node send confirm massage
                {
                    Ees[k]=bat_s/Te;
                    if(Ees[k]<Esi_a)
                        Ees[k]=Esi_a;
                    else if(Ees[k]>Esi_c)
                        Ees[k]=Esi_c;


                    // calculate weght
                    float Wa=0;
                    float Wb=0;
                    float Wc=0;
                    //float Wxxa=[];
                    float Wbc=0;
                    float Wab=0;
                    //float Wxx;
                    if(yy==0)
                    {
                        Wa=(Esi_b-Ees[k])/(Esi_b-Esi_a);
                        Wb=(Esi_a-Ees[k])/(Esi_a-Esi_b);
                        Wab=Wa+Wb;
                        cout<<"ncjacn"<<Wa<<'\n';
                        cout<<"ncjacn"<<Wb<<'\n';
                        // float Wxx[2][3]={{1,((Wa*Te)/Wab),X[2][1]},{1,((Wb*Te)/Wab),X[1][1]}};
                        // Wxxa=[Wxxa;Wxx];
                    }
                    else if(yy==1 )
                    {     Wb=(Esi_c-Ees[k])/(Esi_c-Esi_b);
                        Wc=(Esi_b-Ees[k])/(Esi_b-Esi_c);
                        Wbc=Wc+Wb;
                        // Wxx=[ay ((Wb*Te)/Wbc) ip(2,:);ay ((Wc*Te)/Wbc) ip(1,:)];
                        // float Wxx[2][3]={{1,((Wb*Te)/Wbc),X[2][1]},{1,((Wc*Te)/Wbc),X[1][1]}};
                        //                  Wxxa=[Wxxa;Wxx];
                    }
                    exit=1;
                }
               // cout<<Eem[k]<<'\n';
            }
            //master node algorithm
            // Recive Ees[k],Eem[k],Kei[k] from slave
            if(Conf!=1)
            {
                Eest=0;
                Eemt=0;
                for (int k=0;k<3;k++)
                {
                    Eest+=(Ees[k]*Kei[k]);
                    Eemt+=(Eem[k]-(Ees[k]*Kei[k]));
                }
                T=(bat_m-(Te*Eest))/Eemt;  //calculation T;

                int as,ass;
                as=Te*1000;
                ass=T*1000;
                if (as==ass)
                    Conf=1;
                else
                    Te=T;
                // cout<<Kei[k]<<'\n';
                // cout<<Ees[k]<<'\n';
                // cout<<Eem[k]<<'\n';
                //cout<<Te<<'\n';
            }
        }

        /* float fg=7.244;
    cout<<X[2]<<'\n';
    cout<<A1<<'\n';
    cout<<round(fg)<<'\n';
    cout<<B1<<'\n';
    cout<<Eemt<<'\n';
    cout<<Eest<<'\n'; */
        cout<<num<<'\n';
        cout<<Te<<'\n';

    }
    return 0;
}
