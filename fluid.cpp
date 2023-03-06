#include "fluid.h"

// fluid surface tables

double U[NX + 1] = { 0 }; //horizontal velocity
double S[NX + 1] = { 0 }; //fluid height
double B[NX + 1] = { 0 }; //bottom height
double H[NX + 1] = { 0 }; //H=S-B (fluid column height)
double X[NX + 1] = { 0 }; //table of DX positions
double DT = 0.05;

double g = 9.8;

//void FillMatrixA(gsl_matrix* A, double* H, double* S, double* B)
//{
//	double e = 0;
//	double f = 0;
//
//	//gsl_vector_view H = gsl_vector_view_array(H, NX+1);
//	//gsl_vector_view S = gsl_vector_view_array(S, NX + 1);
//	//gsl_vector_view B = gsl_vector_view_array(B, NX + 1);
//
//	for (size_t i = 0; i < NX+1; i++)
//	{
//		if (i == 0)
//		{
//			e = 1 + g * DT * DT * (H[0]+H[1])/(2*DX2);
//		}
//		else if (i == NX)
//		{
//			e = 1 + g * DT * DT * (H[NX-1] + H[NX]) / (2 * DX2);
//		}
//		else
//		{
//			e = 1 + g * DT * DT * (H[i-1] + 2*H[i] + H[i+1]) / (2 * DX2);
//		}
//		gsl_matrix_set(A, i, i, e);
//	}
//
//	for (size_t i = 0; i < NX; i++)
//	{
//		f = (-1) * g * DT * DT * (H[i] + H[i + 1]) / (2 * DX2);
//		gsl_matrix_set(A, i + 1, i, f);
//		gsl_matrix_set(A, i, i+1, f);
//	}
//}

void InitSurface(void)
{
//	 define table of DXs

	for (int i = 1; i < NX; i++)
		X[i] = X[i - 1] + DX;

//	 define bottom

	for (int i = 0; i < NX; i++)
	{
		//B[i] = sin((double)i / 22) / 4;
		//B[i] = 0.1+sin((double)i / 30) / 6;
		B[i] = 0.2;
		if (B[i] < 0) B[i] = 0;
	}

	// define surface + added rain drop

	for (int i = 0; i < NX; i++)
	{
		S[i] = 0.45 - (cos((double)i / 25) / 15);
		//S[i] = 0.3;
		//S[i] += 0.2 * exp(-(pow((X[i] - X[NX / 3]) / 10, 2)));
		if (S[i] < B[i])
			S[i] = B[i];
	}
}

void CalculateSurface(void)
{
	double u;
		
	//calculate H
	for (int i = 0; i < NX; i++)
	{
		if (S[i] < B[i])
			S[i] = B[i];
		H[i] = S[i] - B[i];
	}

	//calculate U
	for (int i = 1; i < NX; i++)
	{
		u = H[i] * (S[i - 1] - 2 * S[i] + S[i + 1]);
		u += H[i - 1] * (S[i - 1] - S[i]);
		u += H[i + 1] * (S[i + 1] - S[i]);
		u /= (2.0f * DX2);
		u *= g;
		U[i] = U[i] + u * DT;
	}

	//calculate S
	for (int i = 1; i < NX; i++)
		S[i] = S[i] + U[i] * DT;

	S[0] = S[1];
	S[NX] = S[NX-1];
	
}

void DrawFluidSurface(void)
{
	glLineWidth(DX);
	glBegin(GL_LINES);
	for (int i = 0; i < NX+1; i++)
	{
		// fluid
		glColor3f(0.4f, 0.25, 0.85);
		glVertex2f((double)(2 * i) / (double)NX - 1, B[i]);
		glVertex2f((double)(2 * i) / (double)NX - 1, S[i]);

		// bottom
		glColor3f(0.4f, 0.25, 0.15);
		glVertex2f((double)(2 * i) / (double)NX - 1, 0);
		glVertex2f((double)(2 * i) / (double)NX - 1, B[i]);
	}
	glEnd();

	glLineWidth(11);
	glColor3f(0, 0, 0);

	glBegin(GL_LINE_STRIP);
	glVertex2f(-1, 0);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, 0);
	glVertex2f(-1, 0);
	glEnd();
}