#pragma once
#include "glut.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <GSL/gsl_linalg.h>

// properties of physic world

#define WIDTH 400 //szerokosc wyswietlanego okna
#define HEIGHT 300 //wysokosc wyswietlanego okna
#define NX 100
#define DX ((double)((WIDTH)/(double)NX))
#define DX2 DX*DX
//#define epsilon 0.001

void InitSurface(void);

void CalculateSurface(void);

void DrawFluidSurface(void);

//void FillMatrixA(gsl_matrix*, double*, double*, double*);