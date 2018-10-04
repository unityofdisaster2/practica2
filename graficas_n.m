function graficas_n()
y = importdata('promedios_n.txt');
x = [100, 1000, 5000, 10000, 50000, 100000, 200000, 400000, 600000,...
800000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000,...
7000000, 8000000, 9000000,10000000];
nombres = {'busqueda lineal','busqueda binaria','busqueda con arbol',...
    'busqueda lineal con hilos','busqueda binaria con hilos'};

%graficas individuales
for i = 1:size(y,2)
    figure;
    plot(x,y(:,i));
    title(nombres{i});
    xlabel('n');
    ylabel('tiempo');
    set(gca, 'XTickLabel', num2cell(get(gca, 'XTick')))
    set(gca, 'YTickLabel', num2cell(get(gca, 'YTick')))
end


%comparativa de graficas
%arreglo de referencia a graficas
p = cell(1,5);
figure;
for i = 1:size(y,2)
    p{i}= plot(x,y(:,i));
    hold on;
end
ylim([0 0.5]);
legend([p{:}],nombres{:});
xlabel('n');
ylabel('tiempo');
title('comparativa de algoritmos');
end