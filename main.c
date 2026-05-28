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
    dbscan(data,300,5,5);
    for(int i=0;i<10;i++)printf("%d\n",data[i].cluster);
    FILE* gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set title 'DBSCAN Clustering'\n");
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'y'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set pointsize 1.5\n");
    fprintf(gp, "plot '-' using 1:2:3 with points pt 7 ps 1.5 palette notitle\n");
    for (int i = 0; i < 300; i++) {
        fprintf(gp, "%.4f %.4f %d\n", data[i].x, data[i].y, data[i].cluster);
    }
    fprintf(gp, "e\n");
    fflush(gp);
    pclose(gp);
    return 0;
}
