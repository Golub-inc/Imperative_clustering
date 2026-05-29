#include "clustering.h"

static double dist(P a, P b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}
double silhouette(P* dat, int len, int cl_num) {
    double silhouette = 0.0;
    int points = 0;
    for (int i = 0; i < len; i++) {
        if (dat[i].cluster <= 0) continue;
        double sum_a = 0.0;
        int count_a = 0;
        for (int j = 0; j < len; j++) {
            if (i != j && dat[j].cluster == dat[i].cluster) {
                sum_a += dist(dat[i], dat[j]);
                count_a++;
            }
        }
        double a_i = (count_a > 0) ? sum_a / count_a : 0.0;
        double b_i = __INT_MAX__;
        for (int c = 1; c <= cl_num; c++) {
            if (c == dat[i].cluster) continue;
            double sum_c = 0.0;
            int count_c = 0;
            for (int j = 0; j < len; j++) {
                if (dat[j].cluster == c) {
                    sum_c += dist(dat[i], dat[j]);
                    count_c++;
                }
            }
            if (count_c > 0) {
                double avg_c = sum_c / count_c;
                if (avg_c < b_i) b_i = avg_c;
            }
        }
        if (b_i == __INT_MAX__) {
            silhouette += 0.0;
        } 
        else {
            double denom =(a_i>b_i)?a_i:b_i;
            double s_i = (denom > 0) ? (b_i - a_i) / denom : 0.0;
            silhouette += s_i;
        }
        points++;
    }
    return (points > 0) ? silhouette / points : 0.0;
}