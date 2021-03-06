
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <cmath>

#define PI 3.14159265
float angle = 0.065;
float t = 0.005;
float count = 1;
float temp = 1.2;
//==============================================================================

class Point
{
public:
    float x;
    float y;
    Point(float _x = 0.0, float _y = 0.0) {
        x = _x;
        y = _y;
    }
};
//Chuyen dong thu nhat cua nguoi
Point person[11] = { {10,300},//Dau
                     {10,240},//Vai
                     {10,120},//Eo
                     {10,178},/*diem cui tro thu nhat*/
                     {35,110},         /*Diem mui tay thu nhat*/
                     {10,178}, /*Diem cui tro thu 2*/
                     {35,110},          /*Diem mui tay thu 2*/
                     {35,60},{10,2},/*Ong chan thu nhat*/
                     {35,60},{10,2} };/*Ong chan thu 2*/

//==============================================================================

void drawLine(Point a, Point b)
{
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();
    glFlush();

}

//==============================================================================
//Func rotate co 2 truong hop
//Point a la Vai, Point b la cui tro, Point c la ban tay, angle la goc quay, temp la he so quay
//Point a la Eo, Point b la dau goi, Point c la ban chan, angle la goc quay, temp la he so quay
void rotate(float angle, float temp, Point a, Point& b, Point& c)
{
    // recalculate coordinate of b and c based on angle and temp.
    
    float radius = angle * PI / 180;
    
    float c_radius = temp * radius;

    float b_x = (b.x - a.x) * cos(radius) - (b.y - a.y) * sin(radius) + a.x;
    float b_y = (b.x - a.x) * sin(radius) + (b.y - a.y) * cos(radius) + a.y;

    float c_x = (c.x - a.x) * cos(c_radius) - (c.y - a.y) * sin(c_radius) + a.x;
    float c_y = (c.x - a.x) * sin(c_radius) + (c.y - a.y) * cos(c_radius) + a.y;

    b = Point(b_x, b_y);
    c = Point(c_x, c_y);
}
//==============================================================================
void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-70.0, 600.0, -15, 480.0);
}

//==============================================================================
void drawAction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslated(t, 0, 0);
    //VE 2/3 PHAN TREN
    drawLine(person[0], person[2]);


    //VE CANH TAY 1
    rotate(-angle, temp, person[1], person[3], person[4]);
    //Vai toi cui tro
    drawLine(person[1], person[3]);
    //Cui tro toi ban tay
    drawLine(person[3], person[4]);

    //VE CANH TAY 2
    rotate(angle, temp, person[1], person[5], person[6]);
    //Vai toi cui tro
    drawLine(person[1], person[5]);
    //Cui tro toi ban tay
    drawLine(person[5], person[6]);

    //VE CHAN 1
    rotate(-1.5 * angle, temp, person[2], person[7], person[8]);
    //Eo toi dau goi
    drawLine(person[2], person[7]);
    //Dau goi toi ban chan
    drawLine(person[7], person[8]);

    //VE CHAN 2
    rotate(1.5 * angle, temp, person[2], person[9], person[10]);
    //Eo toi dau goi
    drawLine(person[2], person[9]);
    //Dau goi toi ban chan
    drawLine(person[9], person[10]);

    count++;
    glutSwapBuffers();
    if (count >= 700)
    {
        angle = -angle;
        count = 0;
    }

    glutPostRedisplay();
}


//==============================================================================
int main(int argc, char* argv[]) {
    // Initialize GLUT.
    glutInit(&argc, argv);
    // Set the mode to draw in.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // Set the window size in screen pixels.
    glutInitWindowSize(640, 480);
    // Set the window position in screen pixels.
    glutInitWindowPosition(100, 150);
    // Create the window.
    glutCreateWindow("Lab 06-1");
    // Set the callback funcion to call when we need to draw something.
    glutDisplayFunc(drawAction);
    // Initialize some things.
    myInit();
    // Now that we have set everything up, loop responding to events.
    glutMainLoop();
}

/* ----------------------------------------------------------------------- */
