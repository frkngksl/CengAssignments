#pragma once
typedef struct Matrix4x4Result{
    double matrix[4][4];
}Matrix4x4;

typedef struct Matrix4x1{
    double matrix[4][1];
}Matrix4x1;

typedef struct BaryParams{
    double alpha;
    double beta;
    double gamma;
}BaryParams;

typedef struct ColorTexel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    int mode;
} ColorTexel;
