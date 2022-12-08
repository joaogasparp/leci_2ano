
%%%%%% solucao fornecida

fileID = fopen('speedrun_original_107708.txt');
mydata = textscan(fileID,'%f%f'); % separar as duas colunas por tab
md1 = mydata{1,1}; % coluna n
md2 = mydata{1,2}; % coluna cpu-time
fclose(fileID);
figure(1);
plot(md1,md2,'Marker','.','LineStyle','none','Color','b'); % criar plot
h1 = lsline; % reta de ajuste
h1.Color = 'r';
xlabel('n','FontSize',10); % legendar eixo dos x
ylabel('cpu-time','FontSize',10); % legendar eixo dos y
title('Solução Fornecida - Nº Mec. 107708'); % dar título
xlim([0 50]); % limitar eixo dos x
ylim([0 1200]); % limitar eixo dos y

%%%%%% solucao fornecida - ln

fileID = fopen('speedrun_original_107708_ln.txt');
mydata = textscan(fileID,'%f%f'); % separar as duas colunas por tab
md3 = mydata{1,2}; % coluna cpu-time
fclose(fileID);
figure(2);
plot(md1,md3,'Marker','.','LineStyle','none','Color','b'); % criar plot
p1 = polyfit(md1,md3,1);
xlabel('n','FontSize',10); % legendar eixo dos x
ylabel('cpu-time','FontSize',10); % legendar eixo dos y
title('? - Nº Mec. 107708'); % dar título
