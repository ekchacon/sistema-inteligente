clear ; close all; clc

dataset = zeros(1,2);

for i=0:12
    
    for j=0:12

        mu = [(j + 0.5),(i + 0.5)]; %Media de los datos

        %% Sigma 1,2 y 3 es la matriz de varianza-covarianza, 
        %% y es la misma para todos los estados
        sigma = [0.0,0;0,0.0]; %representa una desv estd grande
        sigma2 = [0.0,0;0,0.0]; %representa una desv estd mediana
        sigma3 = [0.0,0;0,0.0]; %representa una desv estd pequeña

        rng shuffle  % For reproducibility

        casos = 200;    %Hacer exp con 200 casos
        %% Genera n casos para una desv estandar determinada
        r = mvnrnd(mu,sigma,casos); %% r Genera n casos para una desv estandar grande

        r2 = mvnrnd(mu,sigma2,casos); %% r Genera n casos para una desv estandar mediana

        r3 = mvnrnd(mu,sigma3,casos); %% r Genera n casos para una desv estandar pequeña
        
        dataset = [dataset; r; r2; r3];
        
%         plot(r(:,1),r(:,2),'+',r2(:,1),r2(:,2),'+',r3(:,1),r3(:,2),'+');
        
%         hold on;
%         axis([0 13 0 13])
        
        
    end
end

dataset;

dataset(1,:) = []; %Para eliminar una fila

length(dataset)

% shuffledDataset = dataset(randperm(size(dataset,1)),:); %Revuelve las filas de la matriz X

% shuffledDataset ;

    fileID = fopen('dataset.txt','w');
    fprintf(fileID,'%2.4f %2.4f\n',dataset'); %La ' es para escribir bien la matriz dataset al archivo .txt
    fclose(fileID);