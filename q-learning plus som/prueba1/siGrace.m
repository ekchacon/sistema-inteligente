%%Extract boundary image

close all;
clc;
 
fileID = fopen('Mpasos.txt','r');
formatSpec = '%f %f';
sizeA = [1000 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
columns = 300

TA = A';
SUBTA = TA(:,1:columns);

TA = SUBTA;

epis = [1:columns];

stdA = [std(TA(:,1))];

for i=2:columns
    
    if mod(i,50) == 0
        
        stdA(end + 1) = std(TA(:,i));
        
    else
        
        stdA(end + 1) = 0;
    end
    
end


meanA = mean(TA);
dataset = [epis;meanA;stdA]';
mean(TA(:,1))
std(TA(:,1))
fileID = fopen('dataGraceIntra.dat','w');
fprintf(fileID,'%2.2f %2.2f %2.2f \n',dataset');
fclose(fileID);