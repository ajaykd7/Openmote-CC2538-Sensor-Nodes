% weighted scheduling for homegeneous networks
function net_life= no_scheduling_scheme(Prc_m, Prc_s, Edm, Eds, X, NoS, bat_s, bat_m)

Es = Prc_s + Eds(1,:);
Em = Prc_m + Edm;

% since the slave always does the first task, it can be expressed as the
% slave always uses the partition cut [0 1,...,1]

% Eo = 0.004; % overhead energy, unit:mJ
% the energy cost of the slave
s = Es*(1-X') ;%+ Eo;
m = Em*X'*NoS ;%+ Eo; % master has to manege all of the slave nodes
net_life = min([bat_s/s, bat_m/m]);
end