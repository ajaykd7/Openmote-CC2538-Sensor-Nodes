% transmitting power cost, unit:mw
function Ptr= tansmitting_power(d)
    fq=2437; % the frequency of the radio
    P_rs=-85; % the reveiving sensetivity, unit:dB
    alfa=2;  % path loss 
    L= 20*log10(fq)+10*alfa*log10(d)-27.55;
    P_out =10.^((L+P_rs)/10);
    Ptr = 59.8  + P_out./(0.0642 - 0.0290*P_out); % transmitting power cost, unit:mw
end