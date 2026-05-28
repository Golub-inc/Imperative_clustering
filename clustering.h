
typedef struct point{
    double x,y;
    int cluster;
}P;
void dbscan(P* dat,int len,int minPts,double R);
P* kmeans(P* dat,int clust_n);