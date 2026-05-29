#include "clustering.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    int point_num,cl_num,dim;
    printf("input number of points\n");
    scanf("%d",&point_num);
    printf("input number of clusters\n");
    scanf("%d",&cl_num);
    printf("input number of dimetions\n");
    scanf("%d",&dim);
    P*data;
    if(dim==2){
        FILE* inp = fopen("data.csv", "r");
        data = calloc(point_num, sizeof(P));
        char trash;
        fscanf(inp, "%c,%c", &trash, &trash);
        for (size_t i = 0; i < point_num; i++) {
            fscanf(inp, "%lf,%lf", &data[i].x, &data[i].y);
        }
    }
    else if(dim==3){
        FILE* inp = fopen("data_3d.csv", "r");
        P3D* dat = calloc(point_num, sizeof(P));
        char trash;
        fscanf(inp, "%c,%c,%c", &trash, &trash, &trash);
        for (size_t i = 0; i < point_num; i++) {
            fscanf(inp, "%lf,%lf,%lf", &dat[i].x, &dat[i].y,&dat[i].z);
        }
        data=pca(dat,point_num);
    }
    else{
        printf("unsupported");
        exit(0);
    }
    int cl_num_dbscan = dbscan(data, point_num, 5, 2);
    double score_dbscan = silhouette(data, point_num, cl_num_dbscan);
    printf("DBSCAN Silhouette Score: %.4f\n", score_dbscan);
    P* cents_dbscan = centroid(data, point_num, cl_num_dbscan);
    FILE* gp1 = popen("gnuplot -persist", "w");
    fprintf(gp1, "set title 'DBSCAN'\n");
    fprintf(gp1, "set xlabel 'x'\n");
    fprintf(gp1, "set ylabel 'y'\n");
    fprintf(gp1, "set grid\n");
    fprintf(gp1, "set pointsize 1.5\n");
    fprintf(gp1, "plot '-' using 1:2:3 with points pt 7 ps 1.2 palette title 'Data Points', \\\n");
    fprintf(gp1, "     '-' using 1:2 with points pt 4 ps 3.0 lc rgb 'green' lw 2 title 'Centroids'\n");
    for (int i = 0; i < point_num; i++) {
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

    P* data_kmeans = malloc(point_num * sizeof(P));
    memcpy(data_kmeans, data, point_num * sizeof(P));
    for (int i = 0; i < point_num; i++) data_kmeans[i].cluster = 0; 
    P* cents_kmeans = kmeans(data_kmeans, point_num, cl_num);
    double score_kmeans = silhouette(data_kmeans, point_num, cl_num);
    printf("K-Means (k=%d) Silhouette Score: %.4f\n", cl_num, score_kmeans);
    FILE* gp2 = popen("gnuplot -persist", "w");
    fprintf(gp2, "set title 'K-Means'\n");
    fprintf(gp2, "set xlabel 'x'\n");
    fprintf(gp2, "set ylabel 'y'\n");
    fprintf(gp2, "set grid\n");
    fprintf(gp2, "set pointsize 1.5\n");
    fprintf(gp2, "plot '-' using 1:2:3 with points pt 7 ps 1.2 palette title 'Data Points', \\\n");
    fprintf(gp2, "     '-' using 1:2 with points pt 4 ps 3.0 lc rgb 'green' lw 2 title 'Centroids'\n");
    for (int i = 0; i < point_num; i++) {
        fprintf(gp2, "%.4f %.4f %d\n", data_kmeans[i].x, data_kmeans[i].y, data_kmeans[i].cluster);
    }
    fprintf(gp2, "e\n");
    for (int i = 0; i < cl_num; i++) {
        fprintf(gp2, "%.4f %.4f\n", cents_kmeans[i].x, cents_kmeans[i].y);
    }
    fprintf(gp2, "e\n");
    fflush(gp2);
    pclose(gp2);
    free(data);
    free(data_kmeans);
    free(cents_kmeans);
    return 0;
}