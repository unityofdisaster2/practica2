function coef = AjusteMinimosCuadrados(num_alg,grado)

%%VALORES DE X

x = [100, 1000, 5000, 10000, 50000, 100000, 200000, 400000, 600000,...
800000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000,...
7000000, 8000000, 9000000, 10000000];
    xi=linspace(0,10000000,1000);	%%ESPACIO DE PUNTOS PARA Xi

algoritmos = {' busqueda lineal',' busqueda binaria',' busqueda con arbol',...
    ' busqueda lineal con hilos',' busqueda binaria con hilos'};
titulo = strcat('Ajuste de minimos cuadrados',' ',algoritmos{num_alg});
%%VALORES DE Y = F(x)
y = importdata('promedios_n.txt');
y = y(:,num_alg);


p = cell(1,5);
n = grado;
%n = [1,2,3,4,8]; %%GRADO DEL POLINOMIO DE AJUSTE

figure;
plot(x,y,'o');
ylabel('F(Y)');
xlabel('X');
title(titulo);
grid;
hold on;
graficas = cell(1,5);
for i = 1:1
    %%OBTENER UN POLINOMIO QUE SE AJUSTE A LOS PUNTOS X Y Y    
    %p{i}=polyfit(x,y',n(i));	%%FUNCION QUE REALIZA EL AJUSTE POLINOMIAL
    p=polyfit(x,y',n(i));	%%FUNCION QUE REALIZA EL AJUSTE POLINOMIAL
    %%SE CREA UN ESPACIO PARA REALIZAR UNA GRAFICA EN 
    %%DONDE SE COMPARA LA CURVA AJUSTADA CONTRA LOS 
    %%VALORES EXPERIMENTALES
    %z=polyval(p{i},xi);				%%EVALUACION DEL POLINOMIO P EN EL ESPACIO Xi
    z=polyval(p,xi);				%%EVALUACION DEL POLINOMIO P EN EL ESPACIO Xi
    graficas{i} = plot(xi,z,'-');
    hold on;
end


%legend([graficas{:}],'grado 1', 'grado 2', 'grado 3', 'grado 4', 'grado 8');


coef = p;





end