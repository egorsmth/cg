#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop

void DrawShit() {
    glBegin(GL_TRIANGLES);
        glColor3f( 0, 1, 1 );
        glVertex3f(-1, 1, 0.5);   // closer
        glVertex3f(-1, 0.5, 0.5);
        glVertex3f(-0.9, 1, 0.5);

        glColor3f( 1, 1, 1 );
        glVertex3f(-1, 1, 0.6);   // futher
        glVertex3f(-0.5, 1, 0.6);
        glVertex3f(-1, 0.9, 0.6);


        glColor3f( 1, 0.5, 1 );
        glVertex3f(-0.7, 1, 0.3);
        glVertex3f(-1, 0.7, 0.7);
        glVertex3f(-0.9, 0.6, 0.7);

    glEnd();
}

void DrawStar() {
    glBegin(GL_TRIANGLE_FAN);
        glColor3f( 0, 1, 1 );
        glVertex2f(0, 0);

        glColor3f( 1, 1, 1 );
        glVertex2f(0, 0.5);

        glColor3f( 0, 1, 1 );
        glVertex2f(-0.1, 0.1);

        glColor3f( 1, 1, 1 );
        glVertex2f(-0.5, 0.1);

        glColor3f( 0, 1, 1 );
        glVertex2f(-0.15, -0.05);

        glColor3f( 1, 1, 1 );
        glVertex2f(-0.3, -0.5);
        
        glColor3f( 0, 1, 1 );
        glVertex2f(0, -0.15);

        glColor3f( 1, 1, 1 );
        glVertex2f(0.3, -0.5);

        glColor3f( 0, 1, 1 );
        glVertex2f(0.15, -0.05);

        glColor3f( 1, 1, 1 );
        glVertex2f(0.5, 0.1);

        glColor3f( 0, 1, 1 );
        glVertex2f(0.1, 0.1);

        glColor3f( 1, 1, 1 );
        glVertex2f(0, 0.5);
    glEnd();
}

int main(int argc, char** argv)
{
    GLFWwindow* window;

	glfwInit();
	window = glfwCreateWindow(640, 480, argv[0], NULL, NULL);
	glfwMakeContextCurrent(window);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable( GL_DEPTH_TEST );

    while (!glfwWindowShouldClose(window))
    {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1, 1, 1);

        glLineWidth( 1 ); // Lines are n pixels wide
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Antialias lines
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel( GL_FLAT ); // or GL_SMOOTH

        DrawStar();

        DrawShit();

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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}