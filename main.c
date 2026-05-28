#include "clustering.h"
#include <stdio.h>
#include <stdlib.h>
int main(void){
    FILE* inp=fopen("data.csv", "r");
    P* data=calloc(300,sizeof(P));
    char trash;
    fscanf(inp,"%c,%c",&trash,&trash);
    for(size_t i=0;i<300;i++){
        fscanf(inp,"%lf,%lf",&data[i].x,&data[i].y);
    }
    int cl_num=dbscan(data,300,5,5);
    P*cents=centroid(data,300,cl_num);
    printf("%f %f\n",cents[0].x,cents[0].y);
    FILE* gp = popen("gnuplot -persist", "w");
            fprintf(gp, "set title 'DBSCAN: Точки и Центроиды'\n");
        fprintf(gp, "set xlabel 'x'\n");
        fprintf(gp, "set ylabel 'y'\n");
        fprintf(gp, "set grid\n");
        fprintf(gp, "set pointsize 1.5\n");
        fprintf(gp, "plot '-' using 1:2:3 with points pt 7 ps 1.2 palette title 'Data Points', \\\n");
        fprintf(gp, "     '-' using 1:2 with points pt 4 ps 3.0 lc rgb 'red' lw 2 title 'Centroids'\n");
        for (int i = 0; i < 300; i++) {
            fprintf(gp, "%.4f %.4f %d\n", data[i].x, data[i].y, data[i].cluster);
        }
        fprintf(gp, "e\n");
        for (int i = 0; i < cl_num; i++) {
            if (cents[i].cluster > 0) {
                fprintf(gp, "%.4f %.4f\n", cents[i].x, cents[i].y);
            }
        }
        fprintf(gp, "e\n");
        fflush(gp);
        pclose(gp);
    return 0;
}
