#include "fluid.h"

// fluid surface tables

double U[NX + 1] = { 0 }; //predkosc pozioma slupa cieczy
double S[NX + 1] = { 0 }; //wysokosc cieczy
double B[NX + 1] = { 0 }; //wysokosc podloza
double H[NX + 1] = { 0 }; //H=S-B (glebokosc cieczy)
double X[NX + 1] = { 0 }; //tablica pozycji o d³ugoœci DX
//double Y[NY + 1] = { 0 }; //tablica pozycji o d³ugoœci DY
double DT = 0.04;

double g = 9.8;

void InitSurface(void)
{

	for (int i = 1; i < NX; i++)
		X[i] = X[i - 1] + DX;

	//for (int i = 1; i < NY; i++)
	//	Y[i] = Y[i - 1] + DY;

//	 define bottom

	for (int i = 0; i < NX; i++)
		//for (int j = 0; i < NY; j++)
		{
			//B[i] = sin((double)i / 22) / 12;
			//if (B[i] < 0) B[i] = 0;
			//B[i] = 0.05+sin((double)i / 10) / 6;
			//B[i,j] = 0.2;
			B[i] = 0.2;
		}


	// define surface + added rain drop

	for (int i = 0; i < NX; i++)

	{
		//S[i] = 0.45 - (cos((double)i / 25) / 15);
		S[i] = 0.3;
		S[i] += 0.2 * exp(-(pow((X[i] - X[NX / 3]) / 6, 2)));
		if (S[i] < B[i])
			S[i] = B[i];
	}

}

void CalculateSurface(void)
{
	double u;
	//	double as;
	//std::cout << "calc\n";
	//{
		
	//calculate H
	for (int i = 0; i < NX; i++)
	{
		if (S[i] < 0)
			S[i] = B[i];
		H[i] = S[i] - B[i];
	}

	//calculate UX
	for (int i = 1; i < NX; i++)
	{
		u = H[i] * (S[i - 1] - 2 * S[i] + S[i + 1]);
		u += H[i - 1] * (S[i - 1] - S[i]);
		u += H[i + 1] * (S[i + 1] - S[i]);
		u /= (2.0f * DX);
		u *= g;
		U[i] = U[i] + u * DT;
	}

	////calculate UY
	//for (int i = 1; i < NX; i++)
	//	for (int j = 1; j < NY; j++)
	//{
	//	u = H[i] * (S[i - 1] - 2 * S[i] + S[i + 1]);
	//	u += H[i - 1] * (S[i - 1] - S[i]);
	//	u += H[i + 1] * (S[i + 1] - S[i]);
	//	u /= (2.0f * DX);
	//	u *= g;
	//	U[i] = U[i] + u * DT;
	//}

	//calculate S
	for (int i = 1; i < NX; i++)
		S[i] = S[i] + U[i] * DT;

	S[0] = S[1];
	S[NX] = S[NX-1];
	
	

}

void DrawFluidSurface(void)
{
	glLineWidth(DX);
	//std::cout << "draw\n";
	glBegin(GL_LINES);
	for (int i = 0; i < NX; i++)
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