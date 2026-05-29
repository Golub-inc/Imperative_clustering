
typedef struct point
{
    double x, y;
    int cluster;
} P;
typedef struct Point3D
{
    double x, y, z;
} P3D;
int dbscan(P *dat, int len, int minPts, double R);
P *kmeans(P *dat, int len, int clust_n);
P *centroid(P *dat, int len, int cl_num);
double silhouette(P *dat, int len, int cl_num);
P *pca(P3D *data, int n);