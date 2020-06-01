% processing and communication energy cost, Prc_m, Prc_s and Edm, Eds
function [Prc_m, Prc_s, Edm, Eds]= eng_prc_cmn(Ptr, Pre, tc, Pme, tm_inter, Pse, ts_inter, Kv, qv, Pmv, Psv, Tv, c1)
    %% processing energy cost per actor    
    Prc_m = zeros(1, size(c1,2));
    Prc_s = zeros(1, size(c1,2));
    for i = 1:size(c1,2)
        Prc_m(i) = qv(i)*Pmv*Tv(i) + sum(sum(c1(1:size(c1,2), i)))*Pme*tm_inter*8 + sum(sum(c1(i, 1:size(c1,2))))*Pme*tm_inter*8;
        Prc_s(i) = qv(i)*Psv*Tv(i) + sum(sum(c1(1:size(c1,2), i)))*Pse*ts_inter*8 + sum(sum(c1(i, 1:size(c1,2))))*Pse*ts_inter*8;
    end    
    %% communication energy cost per actor
    etx      = Ptr * tc;             % unit mJ, tx 1 bit energy consumption
    erx      = Pre * tc;             % unit mJ, rx 1 bit energy consumption
    erm      = (erx  + Pme*tm_inter);% unit mJ, the energy cost of master receiving 1 bit and putting it in the edge
    ets      = -(etx + Pse*ts_inter);% unit mJ, the energy cost of slave transmitting 1 bit and putting it in the edge

    % the net data communication energy cost of each actor; the real data communication erngy cost is a function of m(v) 
    Edm   = erm*Kv*8; 
    Eds   = kron(ets',Kv)*8;

end