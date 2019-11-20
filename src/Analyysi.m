close all
clearvars
clc
matriisi = readmatrix("harjoitustyo_tulokset.csv");
x = matriisi(:,1);
y = matriisi(:,2);
complexity_index_x = 1:100:1000000;
complexity_index_y = log(complexity_index_x) / 20;
hold on
plot(x,y, ".")
plot(complexity_index_x,complexity_index_y)
xlabel('Lis‰tt‰vien alkioiden m‰‰r‰') 
ylabel('Aika') 
title("AVL-puu algoritmin nopeus.")
hold off