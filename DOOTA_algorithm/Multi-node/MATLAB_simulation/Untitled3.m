c = categorical({'B1','B2','B3','B4','B5','B6','B7'});
 data=[126.6121	217.7824	217.7824;126.6121	313.7294	313.7294;253.2241	339.598	339.598;253.2241	435.5147	435.5147;253.2241	627.5347	627.5347;506.4483	679.1316	679.1316;506.4483	871.1645	871.1645];
 data3=[1 217.7824/126.6121;1	313.7294/126.6121;1	339.598/253.2241;1 435.5147/253.2241;1 627.5347/253.2241;1	679.1316/506.4483;1	871.1645/506.4483];
 data4=[253.2241 435.4455 435.4455;506.4483 871.1501 871.1501;0.7597e+03 1.3063e+03 1.3063e+03;1.0129e+03 1.7423e+03 1.7423e+03;506.4483 679.2313 679.2313;759.6724 922.8941 922.8941;1.0129e+03 1.1663e+03 1.1663e+03;253.2241 627.4914 627.4914;253.2241 819.4179 819.4179;0.2532e+03 1.0114e+03 1.0114e+03];
data5=[1 435.4455/253.2241;1 871.1501/506.4483;1 1.3063e+03/0.7597e+03;1 1.7423e+03/1.0129e+03;1 679.2313/506.4483;1 922.8941/759.6724;1 1.1663e+03/1.0129e+03;1 627.4914/253.2241;1 819.4179/253.2241;1 1.0114e+03/0.2532e+03];
 c1 = categorical({'B0','B1','B2','B3','B4','B5','B6','B7','B8','B9'});
 data6=[1;1.261684937;1.561412597;1.711455695;1.961096794;2.460715577;3.959506071;6.956977304;9.89765811;12.82955116;15.75942763;74.59130707;74.59130707];
 c3=[0.0125;0.1;0.2;0.25;0.333333333;0.5;1;2;3;4;5;26;30];
 data7=[1;1.012198959;1.036977363;1.111515987;1.261684937;1.961096794;1.711455695;2.460715577;3.959506071;6.956977304;12.82955116;15.75942763;30.41983677;45.0787825;59.73333802;74.37472287;74.59130707;74.59130707];
 c4=[0.0125;0.016666667;0.025;0.05;0.1;0.333333333;0.25;0.5;1;2;4;5;10;15;20;25;26;30];
 data8=[68.3337;69.1673;70.8605;75.954;86.2156;134.009;116.9501;168.1498;270.5677;475.396;876.6907;1076.9;2078.7;3080.4;4081.8;5082.3;5097.1;5097.1];
 data9=[68.3337 68.3337 68.3337;68.3337 69.1673 69.1673;68.3337 69.1673 70.8605;68.3337 69.1673 75.954;68.3337 86.2156 86.2156;68.3337 134.009 134.009;68.3337 116.9501 116.9501;68.3337 168.1498 168.1498;68.3337 270.5677 270.5677;68.3337 475.396 475.396;68.3337 876.6907 876.6907;68.3337 1076.9 1076.9;68.3337 2078.7 2078.7;68.3337 3080.4 3080.4;68.3337 4081.8 4081.8;68.3337 5082.3 5082.3;68.3337 5097.1 5097.1;68.3337 5097.1 5097.1] 
 c5=  categorical({'B1','B2','B3','B4','B5','B6','B7','B8','B9','B910','B911','B912','B913','B914','B915','B916','B917','B918'});
 c6=1:1:18;
 bar(c5,data9);

% hold
%plot(c4,data7,'-o','Linewidth',4);
%hold
%plot(c4,data7,':','Linewidth',4);
ylabel('Cluster Lifetime');
 xlabel('Battery Energy Combination');
 %ylabel('Ratio Between DOOTA and No Scheduling Lifetimes');
 %ylabel('Ratio Value');
 %xlabel('Ratio Between Slave and Master Battery Energys');
 %Ratio Between Offline dynamic and No Scheduling Lifetimes