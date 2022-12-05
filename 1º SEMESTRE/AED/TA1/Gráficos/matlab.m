%%%%%% solucao fornecida

fileID = fopen('speedrun_3600_original.txt');
mydata = textscan(fileID,'%f%f'); % separar as duas colunas por tab
md1 = mydata{1,1}; % coluna n
md2 = mydata{1,2}; % coluna cpu-time
fclose(fileID);
figure(1);
plot(md1,md2); % criar plot
xlabel('n','FontSize',10); % legendar eixo dos x
ylabel('cpu-time','FontSize',10); % legendar eixo dos y
title('Solução Fornecida - Nº Mec. 107708'); % dar título
xlim([38 50]); % limitar eixo dos x
ylim([0 1200]); % limitar eixo dos y
p1 = polyfit(md1,md2,4); % encontrar fórmula com 4 coeficientes
val1 = polyval(p1,800); % calcular valor para 800

%%%%%% prova formula

n = 38:1:50;
p1 = 0.179683515012509*n.^4 - 29.874161695810340*n.^3 + (1.862710731929421e+03)*n.^2 - (5.161081233702307e+04)*n + 5.360544850625902e+05;
figure(2);
plot(n,p1)
xlabel('n','FontSize',10);
ylabel('cpu-time','FontSize',10);
ylim([0 1200])
title('Prova da Equação')

%%%%%% solucao 1

fileID = fopen('speedrun_our.txt');
mydata = textscan(fileID,'%f%f'); % separar as duas colunas por tab
md1 = mydata{1,1}; % coluna n
md2 = mydata{1,2}; % coluna cpu-time
fclose(fileID);
figure(3);
plot(md1,md2); % criar plot
xlabel('n','FontSize',10); % legendar eixo dos x
ylabel('cpu-time','FontSize',10); % legendar eixo dos y
title('Valores obtidos - Nº Mec. 107708');