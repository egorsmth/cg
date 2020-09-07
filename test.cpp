#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>

// GLFW
#include <GLFW/glfw3.h>

// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop

void DrawShit()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 1);
    glVertex3f(-1, 1, 0.5); // closer
    glVertex3f(-1, 0.5, 0.5);
    glVertex3f(-0.9, 1, 0.5);

    glColor3f(1, 1, 1);
    glVertex3f(-1, 1, 0.6); // futher
    glVertex3f(-0.5, 1, 0.6);
    glVertex3f(-1, 0.9, 0.6);

    glColor3f(1, 0.5, 1);
    glVertex3f(-0.7, 1, 0.3);
    glVertex3f(-1, 0.7, 0.7);
    glVertex3f(-0.9, 0.6, 0.7);

    glEnd();
}

void DrawStar(float i)
{
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 1, 1);
    glVertex2f(0 + i, 0);

    glColor3f(1, 1, 1);
    glVertex2f(0, 0.5);

    glColor3f(0, 1, 1);
    glVertex2f(-0.1, 0.1);

    glColor3f(1, 1, 1);
    glVertex2f(-0.5, 0.1);

    glColor3f(0, 1, 1);
    glVertex2f(-0.15, -0.05);

    glColor3f(1, 1, 1);
    glVertex2f(-0.3, -0.5);

    glColor3f(0, 1, 1);
    glVertex2f(0, -0.15);

    glColor3f(1, 1, 1);
    glVertex2f(0.3, -0.5);

    glColor3f(0, 1, 1);
    glVertex2f(0.15, -0.05);

    glColor3f(1, 1, 1);
    glVertex2f(0.5, 0.1);

    glColor3f(0, 1, 1);
    glVertex2f(0.1, 0.1);

    glColor3f(1, 1, 1);
    glVertex2f(0, 0.5);
    glEnd();
}

void DrawPoints()
{

    glBegin(GL_POINTS);
    glVertex2f(0, 0.5);
    glVertex2f(0, -0.5);
    glVertex2f(0, -0.5);
    glVertex2f(0.5, 0);
    glVertex2f(-0.5, 0);
    glEnd();
}

void DrawF()
{

    glBegin(GL_LINES);
    glVertex2f(0, 0.5);
    glVertex2f(0, -0.5);

    glVertex2f(0.5, 0.5);
    glVertex2f(0, 0.5);

    glVertex2f(0.5, 0);
    glVertex2f(0, 0);
    glEnd();
}

void solar(float HourOfDay, float DayOfYear)
{
    glLoadIdentity();
    // Move 8 units away to be able to view from the origin.
    glTranslatef(0.0, 0.0, -9.0);
    // Tilt system 15 degrees downward in order to view
    // from above the xy-plane.
    glRotatef(15.0, 1.0, 0.0, 0.0);
    // Draw the sun -- as a yellow, wireframe sphere
    glColor3f(1.0, 1.0, 0.0);
    gluSphere(gluNewQuadric(), 0.8, 15, 15); // Radius = 0.8 units.
    
    // closer to sun planet
    glPushMatrix();
    glRotatef(360.0 * 2 * DayOfYear / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glColor3f(0.7, 0.7, 0.8);
    gluSphere(gluNewQuadric(), 0.2, 10, 10);
    glPopMatrix();

    // Draw the Earth
    // First position it around the sun
    // Use DayOfYear to determine its position
    glRotatef(360.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(4.0, 0.0, 0.0);
    // Second, rotate the earth on its axis.
    // Use HourOfDay to determine its rotation.

    glPushMatrix(); // Save matrix state
    glRotatef(360.0 * HourOfDay / 24.0, 0.0, 1.0, 0.0);
    // Third, draw as a blue, wireframe sphere.
    glColor3f(0.2, 0.2, 1.0);
    gluSphere(gluNewQuadric(), 0.4, 10, 10);
    glPopMatrix(); // Restore matrix state
    
    // geospatiol moon
    glPushMatrix(); // Save matrix state
    glRotatef(360.0 * 365.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(1.3, 0.0, 0.0);
    glColor3f(0.1, 0.9, 0.9);
    gluSphere(gluNewQuadric(), 0.1, 7, 7);
    glPopMatrix(); // Restore matrix state
    // Draw the moon.
    // Use DayOfYear to control its rotation around the earth
    glPushMatrix(); // Save matrix state
    glRotatef(360.0 * 12.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0);
    glTranslatef(0.7, 0.0, 0.0);
    glColor3f(0.3, 0.7, 0.3);
    gluSphere(gluNewQuadric(), 0.1, 7, 7);
    glPopMatrix(); // Restore matrix state

    // retrograd moon
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glPushMatrix(); // Save matrix state
    glRotatef(360.0 * 12.0 * DayOfYear / -365.0, 0.0, 1.0, 0.0);
    glTranslatef(0.7, 0.0, 0.0);
    glColor3f(0.7, 0.1, 0.7);
    gluSphere(gluNewQuadric(), 0.1, 7, 7);
    glPopMatrix(); // Restore matrix state
}

int main(int argc, char **argv)
{
    GLFWwindow *window;

    glfwInit();
    window = glfwCreateWindow(640, 480, argv[0], NULL, NULL);
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)640 / (float)480, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    //glTranslatef(0.5, 0, 0);
    //glRotatef(90, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 1, 1);

    glLineWidth(1); // Lines are n pixels wide
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Antialias lines
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT); // or GL_SMOOTH
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    long i = 1;
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1, 1, 1);
        //DrawStar(i);

        //DrawShit();

        //DrawF();
        //gluSphere(gluNewQuadric(), 0.8, 15, 15);
        solar(i % 24, ((int)(i / 24)) % 365);
        i += 6;
        glFlush();
        glfwSetTime(0);
        // Swap the screen buffers
        glfwSwapBuffers(window);
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}