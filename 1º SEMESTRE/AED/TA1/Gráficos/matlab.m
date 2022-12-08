%% Solução Fornecida %%%%%%%%%%%%%%%%%%

%% Gráfico %%
% 107708 %
f = fopen('speedrun_original_107708.txt','r'); % abrir ficheiro para leitura
mydata1 = textscan(f,'%f%f'); % separar as duas colunas por tab
md2 = mydata1{1,2}; % coluna cpu-time
fclose(f);
% 107961 %
f = fopen('speedrun_original_107961.txt','r'); % abrir ficheiro para leitura
mydata2 = textscan(f,'%f%f'); % separar as duas colunas por tab
md3 = mydata2{1,2}; % coluna cpu-time
fclose(f);
% 108352 %
f = fopen('speedrun_original_108352.txt','r'); % abrir ficheiro para leitura
mydata3 = textscan(f,'%f%f'); % separar as duas colunas por tab
md4 = mydata3{1,2}; % coluna cpu-time
fclose(f);
% fazer grafico %
figure(1);
n = 1:1:50;
plot(n,md2,n,md3,n,md4,'Marker','.');
legend('107708','107961','108352','FontSize',10);
xlabel('n','FontSize',10); % legendar eixo dos x
ylabel('cpu-time','FontSize',10); % legendar eixo dos y
title('Solução Fornecida'); % dar título
xlim([0 50]);
ylim([0 1200]);

%% Gráfico Equações %%
p08 = polyfit(n,md2,1);
p61 = polyfit(n,md3,1);
p52 = polyfit(n,md4,1);
n = 0:1:800;
y08 = exp(0.507888709677419).^n * exp(-18.357330645161290);
y61 = exp(0.496723387096774).^n * exp(-18.571576612903222);
y52 = exp(0.497231209677419).^n * exp(-18.494779435483870);
figure(2);
plot(n,y08,n,y61,n,y52,'Marker','.');
legend('107708','107961','108352','FontSize',10);
xlabel('n','FontSize',10); % legendar eixo dos x
ylabel('cpu-time','FontSize',10); % legendar eixo dos y
title('Equações Obtidas'); % dar título
xlim([0 50]);
ylim([0 1200]);

%% Solução 1 %%%%%%%%%%%%%%%%%%

%% Gráfico %%
% 107708 %
f = fopen('speedrun_sol1_107708.txt','r'); % abrir ficheiro para leitura
mydata1 = textscan(f,'%f%f'); % separar as duas colunas por tab
md1 = mydata1{1,1}; % coluna n
md2 = mydata1{1,2}; % coluna cpu-time
fclose(f);
% 107961 %
f = fopen('speedrun_sol1_107961.txt','r'); % abrir ficheiro para leitura
mydata2 = textscan(f,'%f%f'); % separar as duas colunas por tab
md3 = mydata2{1,2}; % coluna cpu-time
fclose(f);
% 108352 %
f = fopen('speedrun_sol1_108352.txt','r'); % abrir ficheiro para leitura
mydata3 = textscan(f,'%f%f'); % separar as duas colunas por tab
md4 = mydata3{1,2}; % coluna cpu-time
fclose(f);
% fazer grafico %
figure(3);
plot(md1,md2,md1,md3,md1,md4,'Marker','.');
legend('107708','107961','108352','FontSize',10);
xlabel('n','FontSize',10); % legendar eixo dos x
ylabel('cpu-time','FontSize',10); % legendar eixo dos y
title('Solução 1'); % dar título
