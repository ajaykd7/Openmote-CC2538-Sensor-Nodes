% mastr and slave life time
function[net_life_dist,par_num] = distributed_algorithm (Prc_m, Prc_s, Edm, Eds, ip, NoS, bat_s, bat_m, L0)
Te=20; %initialize Te and send to slave
Tj=0;  %First send Te to slave
%T=0;
X=ip;  %partition cutting point for optimal curave
Conf=0;    % for confirm message(if X=1 than confirm it )
done=1;  % start for while loop
num=0;    % number for sending massage for master to slave
while done
    if(Tj~=0)
        %% master node algorithm
        %% Recive Ees,Eem,Kei from slave
        num=num+1;
        %% for loop use
        Eemt=0;
        Eest=0;
        for aa=1:NoS
            Eest=Eest+(Ees(aa)*Kei(aa));
            Eemt=Eemt+(Eem(aa)-(Ees(aa)*Kei(aa)));
        end
        T=(bat_m-(Te*Eest))/Eemt;  %%calculation T;
        %if (ceil(Te)==ceil(T))
        if (Te==T)
            Conf=1;
        else
            Te=T;
        end
    end
    %% slave node algorithon
    if(Conf~=1)      %%when master send not confirm massage to slave
        %%calculation Ee_si,Ee_mi,Ke_i
        
        %% Calculation n namber of slave nodes and master node
        for ax=1:NoS
            Ees(ax)=bat_s/Te; %Ees=bat_s/Te
            %%Calculation Esi_a,Esi_b,Esi_c,Emi_a,Emi_b,Emi_c
            Es = Prc_s + Eds(ax,:);
            Em = Prc_m + Edm;
            % since the slave always does the first task, it can be expressed as the
            % slave always uses the partition cut [0 1,...,1]
            % the energy cost of the slave
            Esi_c(ax) = Es*(1-X(1,:)') ;%+ calculat Esi(xci)
            Esi_b(ax) = Es*(1-X(2,:)') ;%+ calculat Esi(xbi)
            Esi_a(ax) = Es*(1-X(3,:)') ;%+ calculat Esi(xai)
            Em_c(ax) = Em*X(1,:)';%+ calculat Emi(xci); % master has to manege all of the slave nodes
            Em_b(ax) = Em*X(2,:)';%+ calculat Emi(xbi); % master has to manege all of the slave nodes
            Em_a(ax) = Em*X(3,:)';%+ calculat Emi(xai); % master has to manege all of the slave nodes
            %%Calculation A0,A1,B0,B1
            A0=(Em_a(ax)-Em_b(ax))/(Esi_a(ax)-Esi_b(ax));
            A1=(Em_b(ax)-Em_c(ax))/(Esi_b(ax)-Esi_c(ax));
            B0=((Esi_a(ax)*Em_b(ax))-(Em_a(ax)*Esi_b(ax)))/(Esi_a(ax)-Esi_b(ax));
            B1=((Esi_b(ax)*Em_c(ax))-(Em_b(ax)*Esi_c(ax)))/(Esi_b(ax)-Esi_c(ax));
            %%calculation limit of Ees value
            if(Ees(ax)<Esi_a(ax))
                Ees(ax)=Esi_a(ax);
            elseif(Ees(ax)>Esi_c(ax))
                Ees(ax)=Esi_c(ax);
            end
            %%calculation which optimal line use
            if(Esi_a(ax)<=Ees(ax) && Ees(ax)<=Esi_b(ax))
                Eem(ax)=A0*Ees(ax)+B0;
                Kei(ax)=(Em_a(ax)-Eem(ax))/(Esi_a(ax)-Ees(ax));
                yy=0;
            elseif(Esi_b(ax)<=Ees(ax) && Ees(ax)<=Esi_c(ax))
                Eem(ax)=A1*Ees(ax)+B1;
                Kei(ax)=(Em_b(ax)-Eem(ax))/(Esi_b(ax)-Ees(ax));
                yy=1;
            end
            asss=0;
        end
        Tj=1;
    else        %%when master node send confirm massage
        
        for ax=1:NoS
            Ees(ax)=bat_s/Te;
            if(Ees(ax)<Esi_a(ax))
                Ees(ax)=Esi_a(ax);
            elseif(Ees(ax)>Esi_c(ax))
                Ees(ax)=Esi_c(ax);
            end
        end
        %% calculate weght
        Wax=0;
        Wbx=0;
        Wcx=0;
        Wxxa=[];
        for ay=1:NoS
            if(yy==0)
                Wa=(Esi_b(ay)-Ees(ay))/(Esi_b(ay)-Esi_a(ay));
                Wb=(Esi_a(ay)-Ees(ay))/(Esi_a(ay)-Esi_b(ay));
                Wab=Wa+Wb;
                Wxx=[ay ((Wa)/Wab) ip(3,:);ay ((Wb)/Wab) ip(2,:)];
                %Wxx=[ay Wa ip(3,:);ay Wb ip(2,:)];
                Wxxa=[Wxxa;Wxx];
            elseif(yy==1 )
                Wb=(Esi_c(ay)-Ees(ay))/(Esi_c(ay)-Esi_b(ay));
                Wc=(Esi_b(ay)-Ees(ay))/(Esi_b(ay)-Esi_c(ay));
                Wbc=Wc+Wb;
                Wxx=[ay ((Wb)/Wbc) ip(2,:);ay ((Wc)/Wbc) ip(1,:)];
                %Wxx=[ay Wb ip(2,:);ay Wc ip(1,:)];
                Wxxa=[Wxxa;Wxx];
            end
        end
        break
    end
end
net_life_dist=Te;
par_num=Wxxa;
num
end