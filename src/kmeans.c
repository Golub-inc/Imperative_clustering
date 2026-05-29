#include "clustering.h"
#include <stdlib.h>
P *kmeans(P *dat, int len, int cl_num)
{
    P *centroids = malloc(cl_num * sizeof(P));
    for (size_t i = 0; i < cl_num; i++)
    {
        int idx = rand() % len;
        centroids[i].x = dat[idx].x;
        centroids[i].y = dat[idx].y;
        centroids[i].cluster = i + 1;
    }
    for (size_t j = 0; j < 10; j++)
    {
        for (size_t i = 0; i < len; i++)
        {
            int centroid_id, min_centroid_distance = __INT_MAX__;
            for (size_t e = 0; e < cl_num; e++)
            {
                double dx = dat[i].x - centroids[e].x;
                double dy = dat[i].y - centroids[e].y;
                double dist = dx * dx + dy * dy;
                if (min_centroid_distance > dist)
                {
                    min_centroid_distance = dist;
                    centroid_id = e;
                }
            }
            dat[i].cluster = centroid_id + 1;
        }
        centroids = centroid(dat, len, cl_num);
    }
    return centroids;
}