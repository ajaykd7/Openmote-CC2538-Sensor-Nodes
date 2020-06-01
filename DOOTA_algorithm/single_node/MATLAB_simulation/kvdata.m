function Kv = kvdata(c1)
    Kv  = zeros(1,size(c1,2));
    for i = 1:size(c1,2)
        % kv(i) = k(v_consumes) - k(v_generates);net consumed tokens of each actor
        if  i == 1
            Kv(i) = -sum(c1(1, 2:size(c1,2)));
        elseif i == size(c1,2)
            Kv(i) = sum(c1(1:size(c1,2)-1, size(c1,2)));
        else
            Kv(i) = sum(c1(1:i-1, i))-sum(c1(i, i+1:size(c1,2))); 
        end
    end
end