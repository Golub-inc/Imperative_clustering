#include "clustering.h"
#include <stdlib.h>
typedef struct queue
{
    int val;
    struct queue *next;
} Q;
Q *queue(int val, Q *end)
{
    Q *temp = malloc(sizeof(Q));
    temp->val = val;
    temp->next = NULL;
    end->next = temp;
    return temp;
}
int dbscan(P *dat, int len, int minPts, double R)
{
    double R_sq = R * R;
    int cluster_id = 1;
    for (int i = 0; i < len; i++)
    {
        if (dat[i].cluster != 0)
            continue;
        int n_count = 0;
        for (int j = 0; j < len; j++)
        {
            double dx = dat[i].x - dat[j].x;
            double dy = dat[i].y - dat[j].y;
            if (dx * dx + dy * dy < R_sq)
                n_count++;
        }
        if (n_count < minPts)
        {
            dat[i].cluster = -1;
            continue;
        }
        Q *start = calloc(1, sizeof(Q)), *end = start;
        start->val = i;
        dat[i].cluster = cluster_id;
        while (start != NULL)
        {
            for (int j = 0; j < len; j++)
            {
                if (dat[j].cluster == 0)
                {
                    double dx = dat[start->val].x - dat[j].x;
                    double dy = dat[start->val].y - dat[j].y;
                    if (dx * dx + dy * dy < R_sq)
                    {
                        dat[j].cluster = cluster_id;
                        end = queue(j, end);
                    }
                }
            }
            Q *temp = start->next;
            free(start);
            start = temp;
        }
        cluster_id++;
    }
    return cluster_id - 1;
}