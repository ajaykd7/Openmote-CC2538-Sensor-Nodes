% comparison of the distributed optimal on-line task allocation, DOOTA,
% algorithm with the no-scheduling and weighted approaches
% Created by Wanli Yu, University of Bremen, 18-10-2017
% wyu@item.uni-bremen.de
% ***********************************************************************
clear,clc

%% The WSN application modeled as a sdf graph
% % modeling the workload as a SDF graph, for example, MEPS computation.
% % DASR application (distributed automatic speech recognization) and spectrum application.
% % load xxx_app.mat file (meps_, dasr_ and spectrum_app.mat) which contains 1) NoV, the number of the vectors of
% % the SDF graph; 2) c0, the matix of the connection relationship of the vectors; 3) c1,
% % the matix of the number of generated tokens of each vectors; 4) Tv, the
% % execution time of the node for executing each vector; and 5) qv, the
% % number of execution times of each vector. 6) X, the partition that
% % no-scheduling used

load('meps_app.mat');

% net consuming tockens of each actor, used to formulate the ILP or LP problem
Kv  = kvdata (c1); 

X   = [0,ones(1,NoV-1)]; % the partition solution for no-scheduling approach
%% parameters of the networks
ns  = 2; % number of slave nodes changes from 5 to 40
ns1  = 1:1:4;
%% parameters of the WSN node
% the HW parameters, for example, node CC2430
Psv = 36.9; Pmv = 36.9;          % unit mw,  Psv,Pmv represent the power consumed when actor executes task in the slave and master graph respectively.
Pse = 36.9; Pme = 36.9;          % unit mw,  Pse Pme represent the power consumption for local communication in the slave and master graph respectively. 
% transmitting and receiving power, note that the transmission power consumption : function of the distance and the path loss 
Pre      = 59.8;   % recieving power cost: get by the matlab FIT function, unit: mw
tc       = 4e-6;   % unit s, the speed of transmiting one bit data, bit rate= 250kbps,  1 bit = 4us,microsecond
ts_inter = 4e-6;   % unit s,  speed of fetch and store 1 bit in the edge of salve
tm_inter = 4e-6;   % unit s,  operation 1 bit speed in the edge of master

rp =1; % repeat the simulation rp times

life    = cell(1,length(ns)); % network lifetime by using task allocation apptoaches
bat_s   = cell(1,length(ns));
bat_m   = zeros(rp,length(ns));
runtime = cell(1,length(ns));

% the loop for changing the number of slave nodes
for k = 1:length(ns)
    NoS = ns(k);
    %% parameters of the WSN node
    d   = 100*rand(1,NoS); % the distance of each slave node
    % transmission power consumption : function of the distance and the path loss 
    Ptr = tansmitting_power(d);% transmitting power cost, unit:mw, different for each slave 
    
    %% energy cost: processing and communication per actor
    [Prc_m, Prc_s, Edm, Eds]= eng_prc_cmn(Ptr, Pre, tc, Pme, tm_inter, Pse, ts_inter, Kv, qv, Pmv, Psv, Tv, c1);

    %% calculate the important partition cuts
    ip= important_partition(NoV, Prc_m, Prc_s, Edm, Eds, c0);%important partitions
    
    % initialize the lifetime and the algorithm runtime
    life{k}    = zeros(rp,3); % the columns in order represent the lifetime of using no-scheduling, weighted and doota algorithms
    runtime{k} = zeros(rp,2); % the columns in order represent the algorithm runtime of weighted and doota algorithms
    
    %% battery energy of the slave and master nodes
     bat_s{k}   = 2.00e4;
    bat_m(:,k) = 2.00e4;
    for i =1:rp
        %% no-scheduling
        net_life_no = no_scheduling_scheme(Prc_m, Prc_s, Edm, Eds, X, NoS, bat_s{k}(i,:), bat_m(i,k));
        life{k}(i,1) = net_life_no;

        % using the weighted scheme to calculate the maximum network lifetime
        tic;
        [x_wet, net_life_wet]= hete_weighted_scheme_01(Prc_m, Prc_s, Edm, Eds, c0, NoS, NoV, bat_s{k}(i,:), bat_m(i,k));
        runtime{k}(i,1) = toc;
        life{k}(i,2) = net_life_wet;

        %% using distributed algorithm to calculate the optimal partitions and the corresponding weights
        L0    = net_life_no; % given one initial network lifetime
        tic;
        [net_life_dist,par_num] = distributed_algorithm (Prc_m, Prc_s, Edm, Eds, ip, NoS, bat_s{k}(i,:), bat_m(i,k), L0);
        runtime{k}(i,2) = toc;
        life{k}(i,3) = net_life_dist;
    end

end
% life{k}(i,1)
% life{k}(i,3)
% L0
% Tv
% Kv
% tc
%  Prc_m
%  Prc_s
%  Edm
%  Eds
%  ip
% % NoS
% % bat_s{k}(i,:)
% % bat_m(i,k)
  life{k}(:)
 %c = categorical({'c1','c2','c3','c4','c5','c6'});
% data=[life{1}(i,1) life{1}(i,2) life{1}(i,3);life{2}(i,1) life{2}(i,2) life{2}(i,3);life{3}(i,1) life{3}(i,2) life{3}(i,3);life{4}(i,1) life{4}(i,2) life{4}(i,3);life{5}(i,1) life{5}(i,2) life{5}(i,3);life{6}(i,1) life{6}(i,2) life{6}(i,3)];
%data=[life{1}(i,1) life{1}(i,2) life{1}(i,3);life{2}(i,1) life{2}(i,2) life{2}(i,3);life{3}(i,1) life{3}(i,2) life{3}(i,3);life{4}(i,1) life{4}(i,2) life{4}(i,3)];  
%bar(c,data);
 % ylabel('Cluster Lifetime');
 % xlabel('Clusters');
%life{k}(i,3)
par_num