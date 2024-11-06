%%Extract boundary image

close all;
clc;

fileID = fopen('MswitchOption.txt','r');
formatSpec = '%f %f';
sizeA = [1000 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
A';
TA = A';
 
fileID = fopen('Mpasos.txt','r');
formatSpec = '%f %f';
sizeA = [1000 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
A';
TB = A';

columns = 1000

% SUBTA = TA(:,1:columns);

% TA = SUBTA;


SUBTB = TB(:,1:columns);

TB = SUBTB;

epis = [1:columns];

% promA = mean(TA);
mean(TB(:,1))
promB = mean(TB);

% for i=1:1

%     descrip = [TA(i,1:50); TA(i,51:100); TA(i,101:150); TA(i,151:200)];
%     rFSDs = descrip;
%     outln = rEfourier( rFSDs, 50,1000);
    
% %     figure;

%     plot(outln(:,2), outln(:,1), 'r', 'LineWidth', 2);
    
    plot(epis', promB','k','LineWidth',4);
%     plot(epis', promA','--k', epis', promB', 'k','LineWidth',4);
    title('Aprendizaje Intra-options vs Sistema inteligente', 'FontSize', 30);
    xlabel('Episodios','FontSize',30);
    ylabel('Pasos por episodio','FontSize',30);

    h_legend=legend('Intra-O + SOM');
    
    set(h_legend,'FontSize',30);
    set(gca,'fontsize',30)

    %legend('Intra-options','Sistema inteligente','FontSize',40)
%     hold on;
    
% %     pause;
% %  length(dataset(1,:));

% % fileID = fopen('dataset.txt','w');
% % fprintf(fileID,'%2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f \n',dataset');
% % fclose(fileID);
% end