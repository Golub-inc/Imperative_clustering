#include "clustering.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    FILE* inp = fopen("data.csv", "r");
    if (!inp) {
        perror("Не удалось открыть data.csv");
        return 1;
    }
    P* data = calloc(300, sizeof(P));
    char trash;
    fscanf(inp, "%c,%c", &trash, &trash);
    for (size_t i = 0; i < 300; i++) {
        fscanf(inp, "%lf,%lf", &data[i].x, &data[i].y);
    }
    int cl_num_dbscan = dbscan(data, 300, 5, 5);
    P* cents_dbscan = centroid(data, 300, cl_num_dbscan);
    FILE* gp1 = popen("gnuplot -persist", "w");
    fprintf(gp1, "set title 'DBSCAN: Точки и Центроиды'\n");
    fprintf(gp1, "set xlabel 'x'\n");
    fprintf(gp1, "set ylabel 'y'\n");
    fprintf(gp1, "set grid\n");
    fprintf(gp1, "set pointsize 1.5\n");
    fprintf(gp1, "plot '-' using 1:2:3 with points pt 7 ps 1.2 palette title 'Data Points', \\\n");
    fprintf(gp1, "     '-' using 1:2 with points pt 4 ps 3.0 lc rgb 'red' lw 2 title 'Centroids'\n");
    for (int i = 0; i < 300; i++) {
        fprintf(gp1, "%.4f %.4f %d\n", data[i].x, data[i].y, data[i].cluster);
    }
    fprintf(gp1, "e\n");
    for (int i = 0; i < cl_num_dbscan; i++) {
        if (cents_dbscan[i].cluster > 0) {
            fprintf(gp1, "%.4f %.4f\n", cents_dbscan[i].x, cents_dbscan[i].y);
        }
    }
    fprintf(gp1, "e\n");
    fflush(gp1);
    pclose(gp1);
    free(cents_dbscan);

    P* data_kmeans = malloc(300 * sizeof(P));
    memcpy(data_kmeans, data, 300 * sizeof(P));
    for (int i = 0; i < 300; i++) data_kmeans[i].cluster = 0;
    int k_clusters = 3;
    P* cents_kmeans = kmeans(data_kmeans, 300, k_clusters);
    FILE* gp2 = popen("gnuplot -persist", "w");
    fprintf(gp2, "set title 'K-Means: Точки и Центроиды'\n");
    fprintf(gp2, "set xlabel 'x'\n");
    fprintf(gp2, "set ylabel 'y'\n");
    fprintf(gp2, "set grid\n");
    fprintf(gp2, "set pointsize 1.5\n");
    fprintf(gp2, "plot '-' using 1:2:3 with points pt 7 ps 1.2 palette title 'Data Points', \\\n");
    fprintf(gp2, "     '-' using 1:2 with points pt 4 ps 3.0 lc rgb 'blue' lw 2 title 'Centroids'\n");
    for (int i = 0; i < 300; i++) {
        fprintf(gp2, "%.4f %.4f %d\n", data_kmeans[i].x, data_kmeans[i].y, data_kmeans[i].cluster);
    }
    fprintf(gp2, "e\n");
    for (int i = 0; i < k_clusters; i++) {
        fprintf(gp2, "%.4f %.4f\n", cents_kmeans[i].x, cents_kmeans[i].y);
    }
    fprintf(gp2, "e\n");
    fflush(gp2);
    pclose(gp2);
    fclose(inp);
    free(data);
    free(data_kmeans);
    free(cents_kmeans);
    return 0;
}