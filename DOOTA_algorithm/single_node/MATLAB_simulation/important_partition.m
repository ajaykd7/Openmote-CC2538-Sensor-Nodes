% get the important partitions for a given SDF graph
function ip= important_partition(NoV, Prc_m, Prc_s, Edm, Eds, c0)
ap = dec2bin(0:2^(NoV-2)-1)-'0'; % all partition cuts
ap = [zeros(size(ap,1),1), ap, ones(size(ap,1),1)];
nf = feedback(c0); % no feedback matrix
i = 1;
done = 1;
while done
    if sum((ap(i,2:end))) == NoV-1
        break;
    end
    f = ap(i,:)*nf';
    if any(f>0)
        ap(i,:) = [];
        i = i-1;
    end
    i = i+1; 
end

Es = Prc_s + Eds(1,:);
Em = Prc_m + Edm;
E  = [Es*(1-ap)';Em*ap'];

i = 1;
done = 1;
fp(1,:) = ap(1,:);
fe(:,1)   = E(:,1);
while done
    np = zeros(1,size(ap,1));
    for j = 1: size(ap,1)
        if j == 1
            np(j) = -inf;
        end
        a = E(:,1);
        b = E(:,j);
        np(j) = (a(2)-b(2))/(a(1)-b(1));
    end
    [~, id] = max(np); 
    fp(i+1,:) = ap(id,:);
    fe(:,i+1)   = E(:,id);
    no = find (E(1,:) > E(1,id));
    ap(no,:) = [];
    E(:,no) = [];
%     i = i-1;
    if size(ap,1)==1
        break;
    end
    i = i+1;
end
ip = fp;