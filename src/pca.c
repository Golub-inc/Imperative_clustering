#include "clustering.h"
#include <stdlib.h>
#include <math.h>
P *pca(P3D *data, int n)
{
    P *out = calloc(n, sizeof(P));
    double mx = 0, my = 0, mz = 0;
    for (size_t i = 0; i < n; i++)
    {
        mx += data[i].x;
        my += data[i].y;
        mz += data[i].z;
    }
    mx /= n;
    my /= n;
    mz /= n;
    double C[3][3] = {0};
    for (size_t i = 0; i < n; i++)
    {
        double cx = data[i].x - mx, cy = data[i].y - my, cz = data[i].z - mz;
        C[0][0] += cx * cx;
        C[0][1] += cx * cy;
        C[0][2] += cx * cz;
        C[1][1] += cy * cy;
        C[1][2] += cy * cz;
        C[2][2] += cz * cz;
    }
    C[1][0] = C[0][1];
    C[2][0] = C[0][2];
    C[2][1] = C[1][2];
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            C[i][j] /= n;
    double v1[3] = {1, 0, 0};
    for (size_t k = 0; k < 30; k++)
    {
        double nv[3] = {C[0][0] * v1[0] + C[0][1] * v1[1] + C[0][2] * v1[2], C[1][0] * v1[0] + C[1][1] * v1[1] + C[1][2] * v1[2], C[2][0] * v1[0] + C[2][1] * v1[1] + C[2][2] * v1[2]};
        double norm = sqrt(nv[0] * nv[0] + nv[1] * nv[1] + nv[2] * nv[2]);
        if (norm > 1e-9)
        {
            v1[0] = nv[0] / norm;
            v1[1] = nv[1] / norm;
            v1[2] = nv[2] / norm;
        }
    }
    double Cv1[3] = {C[0][0] * v1[0] + C[0][1] * v1[1] + C[0][2] * v1[2], C[1][0] * v1[0] + C[1][1] * v1[1] + C[1][2] * v1[2], C[2][0] * v1[0] + C[2][1] * v1[1] + C[2][2] * v1[2]};
    double lambda1 = v1[0] * Cv1[0] + v1[1] * Cv1[1] + v1[2] * Cv1[2];
    double C2[3][3];
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            C2[i][j] = C[i][j] - lambda1 * v1[i] * v1[j];
    double v2[3] = {0, 1, 0};
    for (size_t k = 0; k < 30; k++)
    {
        double nv[3] = {C2[0][0] * v2[0] + C2[0][1] * v2[1] + C2[0][2] * v2[2], C2[1][0] * v2[0] + C2[1][1] * v2[1] + C2[1][2] * v2[2], C2[2][0] * v2[0] + C2[2][1] * v2[1] + C2[2][2] * v2[2]};
        double norm = sqrt(nv[0] * nv[0] + nv[1] * nv[1] + nv[2] * nv[2]);
        if (norm > 1e-9)
        {
            v2[0] = nv[0] / norm;
            v2[1] = nv[1] / norm;
            v2[2] = nv[2] / norm;
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        double cx = data[i].x - mx, cy = data[i].y - my, cz = data[i].z - mz;
        out[i].x = cx * v1[0] + cy * v1[1] + cz * v1[2];
        out[i].y = cx * v2[0] + cy * v2[1] + cz * v2[2];
    }
    return out;
}