% This function is called by functions partition_r and partition_s to make sure there is no feedback in the SDF graph, namely, m(v_source) - m(v_sink) <=0;
% From the conjunction matrix, obtain a new matrix I and asign the related elements which satify I(i, :)* m(v) <= 0;
function I = feedback(A)
       
         I = zeros(size(A)) ;
         [row, col] = find (A == 1);
         for i = 1:length(row)
             I(i, row(i)) =  1;
             I(i, col(i)) = -1;
         end
       
end
 