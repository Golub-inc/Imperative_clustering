#include "clustering.h"
#include <stdlib.h>
P*centroid(P* dat,int len,int cl_num){
    P* centroids=calloc(cl_num,sizeof(P));
    for(size_t i=0;i<cl_num;i++){
        double sum_x=0,sum_y=0;
        int num=0;
        for(size_t e=0;e<len;e++){
            if(dat[e].cluster==i+1){
                sum_x+=dat[e].x;
                sum_y+=dat[e].y;
                num++;
            }
        }
        centroids[i].x=sum_x/num;
        centroids[i].y=sum_y/num;
        centroids[i].cluster=i+1;
    }
    return centroids;
}