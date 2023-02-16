#pragma once

#include "fluid.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glut.h>

void Idle(void);

void Display(void);

void Reshape(int, int);

void Key(unsigned char key, int x, int y);

void SpecialKey(int key, int x, int y);

void Init(void);