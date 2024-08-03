//
//  main_helper.cpp
//  HMS
//
//  Created by Efe Eldem on 1.08.2024.
//

#include "helper.h"


//-----------------------------------------------------------------------------------
// Constants and Macros
#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800
#define TIMER_PERIOD 10000
#define D2R 0.0174532
#define PI 3.1415

//-----------------------------------------------------------------------------------
// Database connection
sqlite3 *db;

//-----------------------------------------------------------------------------------

// Global Variables
employee user;
bool welcomeMessage = true;
int inputMode = 0; // 0 for ID, 1 for password
bool userValid = false;
bool inputDone = false;
int viewMode = 0;
int roomFloor = 0;

//-----------------------------------------------------------------------------------
// SQL functions

int validateUser(const char *id, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM personnel WHERE personnel_id = ? AND password = ?";
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, id, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 1;
    } else {
        sqlite3_finalize(stmt);
        return 0;
    }
}

void getUser(const char *id, char *name, char *surname) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT name, surname FROM personnel WHERE personnel_id = ?";
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, id, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const unsigned char *db_name = sqlite3_column_text(stmt, 0);
        const unsigned char *db_surname = sqlite3_column_text(stmt, 1);

        strcpy(name, (const char *)db_name);
        strcpy(surname, (const char *)db_surname);
    } else {
        fprintf(stderr, "No user found with the given id.\n");
    }

    sqlite3_finalize(stmt);
}

//-----------------------------------------------------------------------------------
// OpenGL functions

void circle(int x, int y, int r) {
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void vprint(int x, int y, void *font, const char *string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, str[i]);
}

void print(int x, int y, const char *string, void *font) {
    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, string[i]);
}

void drawGradient(int x1, int y1, int w, int h, float r, float g, float b) {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(x1, y1);
    glVertex2f(x1 + w, y1);
    glColor3f(r + 0.4, g + 0.4, b + 0.4);
    glVertex2f(x1 + w, y1 - h);
    glVertex2f(x1, y1 - h);
    glEnd();

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x1 + w, y1);
    glVertex2f(x1 + w, y1 - h);
    glVertex2f(x1, y1 - h);
    glEnd();
}

//-----------------------------------------------------------------------------------
// Application Functions

void welcome() {
    if (welcomeMessage) {
        glColor3f(0, 0, 0);
        print(-100, 25, "Welcome to CHotel", GLUT_BITMAP_9_BY_15);
        print(-290, 0, "A Hotel Management System programmed with C and OpenGL GLUT", GLUT_BITMAP_9_BY_15);
        print(-100, -25, "by Hamit Efe Eldem", GLUT_BITMAP_9_BY_15);
    }
}

void loginScreen() {
    glColor3f(0, 0, 0);
    if (!welcomeMessage) {
        print(-100, 50, "CHotel Login Screen", GLUT_BITMAP_9_BY_15);
        print(-160, 0, "ID", GLUT_BITMAP_9_BY_15);
        print(-210, -25, "Password", GLUT_BITMAP_9_BY_15);

        glColor3f(1, 1, 1);
        glRectf(-100, -2, 70, 15);
        glRectf(-100, -10, 70, -27);

        if (inputDone) {
            if (validateUser(user.id, user.password)) {
                // User validated
                printf("User validated\n");
                userValid = true;
            } else {
                printf("User not found\n");
                userValid = false;
            }
        } else {
            // Create masked password with '*'
            char maskedPassword[50];
            for (int i = 0; i < strlen(user.password); i++) {
                maskedPassword[i] = '*';
            }
            maskedPassword[strlen(user.password)] = '\0';

            glColor3f(0.24, 0, .1);
            vprint(-95, 0, GLUT_BITMAP_9_BY_15, "%s", user.id);
            vprint(-95, -25, GLUT_BITMAP_9_BY_15, "%s", maskedPassword);
        }
    }
}

void userScreen() {
    // Get the name and surname of the user
    getUser(user.id, user.name, user.surname);

    // Sidebar
    glColor3f(0.3, 0.3, 0.3);
    glRectf(-WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, -WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 2);

    // Profile bar
    glColor3f(0.4, 0.55, 0.65);
    glRectf(-WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100, -WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 2);

    // Profile picture
    glColor3f(1, 1, 1);
    circle(-WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT / 2 - 50, 27);
    glColor3f(0, 0, 0);
    vprint(-WINDOW_WIDTH / 2 + 32, WINDOW_HEIGHT / 2 - 55, GLUT_BITMAP_TIMES_ROMAN_24, "%c%c", user.name[0], user.surname[0]);

    // Name printing
    glColor3f(1, 1, 1);
    vprint(-WINDOW_WIDTH / 2 + 90, WINDOW_HEIGHT / 2 - 55, GLUT_BITMAP_HELVETICA_18, "%s %s", user.name, user.surname);
    
    frontOfficeModule();
}


void frontOfficeModule(){
    //design of ui
    
    //sidebar
    
    //spec 1: room view
    glColor3f(0, 0, 0);
    
    //seperator line
    glBegin(GL_LINES);
        glVertex2f(-WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);
        glVertex2f(-WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 2 - 200);
    glEnd();
    
    //button box & text
    drawGradient(-WINDOW_WIDTH / 2 +50, WINDOW_HEIGHT / 2 - 135, 200, 30, 0.6, 0.6, 0.6);
    print(-WINDOW_WIDTH / 2 + 70,  WINDOW_HEIGHT / 2 - 155, "Room Management", GLUT_BITMAP_HELVETICA_18);
    
    switch (viewMode){
        case 1:
            //button box & text
            drawGradient(-WINDOW_WIDTH / 2 +50, WINDOW_HEIGHT / 2 - 135, 200, 30, 0.3, 0.9, 0.3);
            print(-WINDOW_WIDTH / 2 + 70,  WINDOW_HEIGHT / 2 - 155, "Room Management", GLUT_BITMAP_HELVETICA_18);
            
            roomManagement();
            
            
            
            
            
    }

    
}

void roomManagement(){
    int i;
    int roomNumber;
    
    glRectf(-350, -350  , 650, 300);
    
    
    
    glColor3f(1, 1, 1);
    
    
    for(i = 0; i < 19; i++){
        roomNumber = roomFloor * 100 + i;
    
        // draw rooms
        
        if(i < 10){
            drawLine(-350 + 100 * i, -350 + 100 * i, 300, 50);
        }
        else{
            drawLine(-350 + 100 * (i-9), -350 + 100 * (i-9), -350, -100);
        }
        
        drawLine(-350, 650, 50, 50);
        drawLine(-350, 650, -100, -100);
        
    }
}

void drawLine(int x1, int x2, int y1, int y2){
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}
