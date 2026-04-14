tempi_bubble = [2.41e-07 3.81e-07 1.185e-06 3.42e-06 1.2352e-05 5.7423e-05 0.000165356 0.00064577 0.00240041 0.0101458 0.0419603 0.189799 ];
tempi_insertion = [1.86e-07 2.26e-07 5.34e-07 1.288e-06 3.829e-06 1.6376e-05 4.9107e-05 0.000178425 0.000744324 0.00291842 0.011275 0.0457877 ];
tempi_selection = [1.73e-07 3.97e-07 9.07e-07 2.901e-06 8.359e-06 5.7458e-05 0.000101277 0.000383806 0.00144543 0.00555889 0.0224191 0.0922509 ];
tempi_stdsort = [5.02e-07 4.33e-07 9.32e-07 2.167e-06 5.601e-06 1.3576e-05 2.2723e-05 4.8383e-05 0.000119315 0.00024193 0.000575195 0.00116658 ];

n = 2.^(2:13);

figure;
plot(n, tempi_bubble, '-o', n, tempi_insertion, '-x', n, tempi_selection, '-s', n, tempi_stdsort, '-*');
grid on;
xlabel('Dimensione del vettore');
ylabel('Tempo');
legend('Bubble Sort', 'Insertion Sort', 'Selection Sort', 'std::sort');