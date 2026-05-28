
typedef struct point{
    double x,y;
    int cluster;
}P;
int dbscan(P* dat,int len,int minPts,double R);
P* kmeans(P* dat,int clust_n);
P*centroid(P* dat,int len,int cl_num);