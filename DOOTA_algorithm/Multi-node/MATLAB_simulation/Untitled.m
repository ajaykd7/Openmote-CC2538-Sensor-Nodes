c = categorical({'B1','B2','B3','B4','B5','B6','B7'});
 data=[126.6121	217.7824	217.7824;126.6121	313.7294	313.7294;253.2241	339.598	339.598;253.2241	435.5147	435.5147;253.2241	627.5347	627.5347;506.4483	679.1316	679.1316;506.4483	871.1645	871.1645];
 data3=[1 217.7824/126.6121;1	313.7294/126.6121;1	339.598/253.2241;1 435.5147/253.2241;1 627.5347/253.2241;1	679.1316/506.4483;1	871.1645/506.4483];
 data4=[253.2241 435.4455 435.4455;506.4483 871.1501 871.1501;0.7597e+03 1.3063e+03 1.3063e+03;1.0129e+03 1.7423e+03 1.7423e+03;506.4483 679.2313 679.2313;759.6724 922.8941 922.8941;1.0129e+03 1.1663e+03 1.1663e+03;253.2241 627.4914 627.4914;253.2241 819.4179 819.4179;0.2532e+03 1.0114e+03 1.0114e+03];
data5=[1 435.4455/253.2241;1 871.1501/506.4483;1 1.3063e+03/0.7597e+03;1 1.7423e+03/1.0129e+03;1 679.2313/506.4483;1 922.8941/759.6724;1 1.1663e+03/1.0129e+03;1 627.4914/253.2241;1 819.4179/253.2241;1 1.0114e+03/0.2532e+03];
 c1 = categorical({'B0','B1','B2','B3','B4','B5','B6','B7','B8','B9'});
 bar(c1,data5);
% plot(c1,data5);
 ylabel('Cluster Lifetime');
 xlabel('Battery Energy');