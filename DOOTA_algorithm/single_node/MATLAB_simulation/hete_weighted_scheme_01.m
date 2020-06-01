% static scheduling for heterogeneous networks
function [x, net_life]= hete_weighted_scheme_01(Prc_m, Prc_s, Edm, Eds, c0, NoS, NoV, bat_s, bat_m)
        Prc_m = kron(ones(1,NoS),Prc_m);
        Prc_s = kron(eye(NoS),Prc_s);
        Edm = kron(ones(1,NoS),Edm);
        ts    = num2cell(Eds,2);
        Eds   = blkdiag(ts{:});
        Es  = Prc_s + Eds;
        Em  = Prc_m + Edm;
        bat_s = repmat(bat_s',[1,NoV*NoS+1]);
        
        GA = [ones(1,size(c0,2));  -ones(1,size(c0,2));    feedback(c0)];
        Gb = [size(c0,2)-1;  -1;    zeros(size(feedback(c0),2),1)];
        GA = kron(eye(NoS),GA);
        Gb = kron(ones(NoS,1),Gb);
        f     = [1 zeros(1,NoV*NoS)];
        
        
        A1 = -[zeros(NoS,1),Es]./bat_s - kron(ones(NoS,1),f);  b1   = -sum([zeros(NoS,1),Es]./bat_s,2);
        A2 = [0,Em]/bat_m - f;  b2  = 0;
%         intcon = 2:(NoV*NoS +1);
        AA  = [zeros(size(GA,1),1),GA;A1;A2];
        bb  = [Gb;b1;b2];

        Aeq    = [];
        beq    = [];
        
        lb     = [0; repmat([zeros(NoV-1,1);1],NoS,1)];
        ub     = [Inf; repmat([0; ones(NoV-1,1)],NoS,1)];
%         lb     = zeros(NoV*NoS+1, 1);
%         ub     = [Inf; ones(NoV*NoS, 1)];

%         options = optimoptions('intlinprog','TolGapRel',1e-9,'TolCon',1e-9,'TolInteger',1e-6);

        [x, fval]   = linprog(f', AA, bb, Aeq, beq, lb, ub); % optimal objective value
        net_life = 1/fval;
end