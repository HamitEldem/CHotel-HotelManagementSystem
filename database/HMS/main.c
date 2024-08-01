#include "helper.h"

//-----------------------------------------------------------------------------------

//GLUT functions that are being called in the main program

void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    
    welcomeMessage = false;
    
    glutPostRedisplay(); //display()
}

// To display onto window using OpenGL commands
void display() {
    // Draw window
    glClearColor(0.4, 0.6, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    welcome();
    
    if(userValid){
        userScreen();
    }
    else{
        loginScreen();
    }
    

   
    glutSwapBuffers();
}

// Key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
void onKeyDown(unsigned char key, int x, int y) {
    // Exit when ESC is pressed.
    if (key == 27)
        exit(0);
    if(!welcomeMessage){
        if (inputMode == 0 && (key == '\n' || key == '\r')){
            inputMode = 1;
        }
        else if(inputMode == 1 && (key == '\n' || key == '\r')){
            inputDone = true;
        }
        else if (key == 127) { // Backspace key
            if (inputMode == 0 && strlen(user.id) > 0) {
                user.id[strlen(user.id) - 1] = '\0';
            }
            else if (inputMode == 1 && strlen(user.password) > 0) {
                user.password[strlen(user.password) - 2] = '\0';
            }
        }
        else {
            if (inputMode == 0 && strlen(user.id) < 7) {
                user.id[strlen(user.id)] = key;
                user.id[strlen(user.id) + 1] = '\0';
            }
            else if (inputMode == 1 && strlen(user.password) < 49) {
                user.password[strlen(user.password)] = key;
                user.password[strlen(user.password) + 1] = '\0';
            }
        }
    }
    
    
    

    // To refresh the window it calls display() function
    glutPostRedisplay();
}


// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
void onSpecialKeyDown(int key, int x, int y) {

  
    
        
    
    // To refresh the window it calls display() function
    glutPostRedisplay();
}


// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.

void onClick(int button, int stat, int x, int y) {
    // Check if the game is over
  

    // To refresh the window it calls display() function
    glutPostRedisplay();
}


// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
void onResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Init() {
    //Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
}

//-----------------------------------------------------------------------------------


int main(int argc, char ** argv) {
    // Initialize the SQLite database
    int rc = sqlite3_open("/Users/efeeldem/Desktop/HotelManagementSystem/database/hotel_management_system.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Opened database successfully\n");
        
        glutInit(&argc, argv );
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutCreateWindow("Hotel Management System");
        

        // Window Events
        glutDisplayFunc(display);
        glutReshapeFunc(onResize);
  
        
        // Keyboard Events
        glutKeyboardFunc(onKeyDown);
        glutSpecialFunc(onSpecialKeyDown);
        
        // Mouse Events
        glutMouseFunc(onClick);
        
        // Timer Event
        glutTimerFunc(TIMER_PERIOD/3, onTimer, 0);



        Init();
        glutMainLoop();
        
        
    }

   
    // Close the SQLite database
    sqlite3_close(db);
    return 0;
}
