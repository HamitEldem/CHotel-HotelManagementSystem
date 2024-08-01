//
//  glut_helper.h
//  HMS
//
//  Created by Efe Eldem on 1.08.2024.
//

#ifndef glut_helper_h
#define glut_helper_h

#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdarg.h>

//-----------------------------------------------------------------------------------
// Constants and Macros
#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800
#define TIMER_PERIOD 10000
#define D2R 0.0174532
#define PI 3.1415

//-----------------------------------------------------------------------------------
// Database connection
#include <sqlite3.h>
extern sqlite3 *db;

//-----------------------------------------------------------------------------------
// Global Variables
typedef struct employee {
    char id[6];
    char password[50];
    char name[50];
    char surname[50];
} employee;

extern employee user;
extern bool welcomeMessage;
extern int inputMode; // 0 for ID, 1 for password
extern bool userValid;
extern bool inputDone;

//-----------------------------------------------------------------------------------
// SQL function prototypes
int validateUser(const char *id, const char *password);
void getUser(const char *id, char *name, char *surname);

//-----------------------------------------------------------------------------------
// OpenGL function prototypes
void circle(int x, int y, int r);
void vprint(int x, int y, void *font, const char *string, ...);
void print(int x, int y, const char *string, void *font);
void drawGradient(int x1, int y1, int w, int h, float r, float g, float b);

//-----------------------------------------------------------------------------------
// Application function prototypes
void welcome();
void loginScreen();
void userScreen();

#endif /* glut_helper_h */

