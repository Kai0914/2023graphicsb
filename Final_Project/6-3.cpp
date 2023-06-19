#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
#include <windows.h>
GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * bot = NULL;
GLMmodel * arm1 = NULL, * arm2 = NULL;
GLMmodel * arm3 = NULL, * arm4 = NULL;
GLMmodel * leg1 = NULL, * leg2 = NULL;
GLMmodel * leg3 = NULL, * leg4 = NULL;
GLMmodel * foot1 = NULL, * foot2 = NULL;

float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
int ID = 0;
FILE * fout = NULL;
FILE * fin = NULL;

void timer(int t) {
    printf("現在timer(%d)\n", t);
    glutTimerFunc(20, timer, t+1);

    float alpha = (t%50) / 50.0;

    if(t%50==0){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin, "%f", &NewAngle[i] );
            fscanf(fin, "%f", &NewAngle2[i] );
        }
    }
    for(int i=0; i<20; i++){
        angle[i] = NewAngle[i] * alpha + OldAngle[i] * (1-alpha);
        angle2[i] = NewAngle2[i] * alpha + OldAngle2[i] * (1-alpha);
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    if(key=='4') ID = 4;
    if(key=='5') ID = 5;
    if(key=='6') ID = 6;
    if(key=='7') ID = 7;
    if(key=='8') ID = 8;
    if(key=='9') ID = 9;
    if(key=='-') ID = 10;
    if(key=='=') ID = 11;
    if(key=='s'){
        if(fout == NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("寫了一行\n");
    }
    if(key=='r'){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){
        glutTimerFunc(0, timer, 0);
    }
}
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {
    teapotX += (x - oldX) / 150.0 * 10;
    teapotY += (oldY - y) / 150.0 * 10;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(1.6, 1.6, 1.6);
        glTranslatef(0, -0.6, 0);
        glPushMatrix();
            glColor3f(0.88,0.08,0.08);
            glScalef(0.1, 0.1, 0.1);
            glRotatef(angle[0], 0, 1, 0);
            glmDraw(body, GLM_MATERIAL|GLM_TEXTURE);

            glPushMatrix();///左手
                glTranslatef(-4.07, +21.33, 0 );
                glRotatef(angle[1], 0, 1, 0);
                glRotatef(angle2[1], 1, 0, 0);
                glTranslatef( 4.07, -21.33, 0 );
                glmDraw(arm1, GLM_MATERIAL|GLM_TEXTURE);
            glPopMatrix();
                glPushMatrix();
                    glTranslatef(-4.40, +18.53, 0 );
                    glRotatef(angle[2], 0, 1, 0);
                    glRotatef(angle2[2], 1, 0, 0);
                    glTranslatef( 4.40, -18.53, 0 );
                    glmDraw(arm3, GLM_MATERIAL|GLM_TEXTURE);
                    glColor3f(1,0.742,0.627);
                glPopMatrix();


            glPushMatrix();
                glTranslatef(+4.07, +21.33, 0 );
                glRotatef(angle[3], 0, 1, 0);
                glRotatef(angle2[3], 1, 0, 0);
                glTranslatef(-4.07, -21.33, 0 );
                glmDraw(arm2, GLM_MATERIAL|GLM_TEXTURE);
            glPopMatrix();
                glPushMatrix();
                    glTranslatef(+4.40, +18.53, 0 );
                    glRotatef(angle[4], 0, 1, 0);
                    glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef(-4.40, -18.53, 0 );
                    glmDraw(arm4, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(+2.00, +14.27, 0 );
                    glRotatef(angle[9], 0, 1, 0);
                    glRotatef(angle2[9], 1, 0, 0);
                    glTranslatef(-2.00, -14.27, 0 );
                    glmDraw(leg2, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
                    glPushMatrix();
                        glTranslatef(+2.00, +9.87, 0 );
                        glRotatef(angle[10], 0, 1, 0);
                        glRotatef(angle2[10], 1, 0, 0);
                        glTranslatef(-2.00, -9.87, 0 );
                        glmDraw(leg4, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();

            glPushMatrix();
                glTranslatef(-0.00, +22.53, 0 );
                glRotatef(angle[5], 0, 1, 0);
                glRotatef(angle2[5], 1, 0, 0);
                glTranslatef( 0.00, -22.53, 0 );
                glmDraw(head, GLM_MATERIAL|GLM_TEXTURE);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0.5);
                glmDraw(bot, GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef(-2.00, +14.27, 0 );
                    glRotatef(angle[6], 0, 1, 0);
                    glRotatef(angle2[6], 1, 0, 0);
                    glTranslatef( 2.00, -14.27, 0 );
                    glmDraw(leg1, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
                    glPushMatrix();
                        glTranslatef(-2.00, +9.87, 0 );
                        glRotatef(angle[7], 0, 1, 0);
                        glRotatef(angle2[7], 1, 0, 0);
                        glTranslatef( 2.00, -9.87, 0 );
                        glmDraw(leg3, GLM_MATERIAL|GLM_TEXTURE);
                    glPopMatrix();

                        glPushMatrix();
                            glTranslatef(-2.13, +2.40, 0 );
                            glRotatef(angle[8], 0, 1, 0);
                            glRotatef(angle2[8], 1, 0, 0);
                            glTranslatef( 2.13, -2.40, 0 );
                            glColor3f(0,0,0);
                            glmDraw(foot1, GLM_MATERIAL|GLM_TEXTURE);
                        glPopMatrix();

                        glPushMatrix();
                            glTranslatef(+2.13, +2.40, 0 );
                            glRotatef(angle[11], 0, 1, 0);
                            glRotatef(angle2[11], 1, 0, 0);
                            glTranslatef(-2.13, -2.40, 0 );
                            glColor3f(0,0,0);
                            glmDraw(foot2, GLM_MATERIAL|GLM_TEXTURE);
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

        glPopMatrix();





    glPopMatrix();
    glutSwapBuffers();
}
#include "CMP3_MCI.h"
CMP3_MCI myMP3;
int main(int argc, char** argv)
{
    myMP3.Load("h.mp3");
    myMP3.Play();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("week16");
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    head = glmReadOBJ("k/head.obj");
    body = glmReadOBJ("k/body.obj");
    bot = glmReadOBJ("k/bot.obj");
    arm1 = glmReadOBJ("k/arm1.obj");
    arm2 = glmReadOBJ("k/arm2.obj");
    arm3 = glmReadOBJ("k/arm3.obj");
    arm4 = glmReadOBJ("k/arm4.obj");
    leg1 = glmReadOBJ("k/leg1.obj");
    leg2 = glmReadOBJ("k/leg2.obj");
    leg3 = glmReadOBJ("k/leg3.obj");
    leg4 = glmReadOBJ("k/leg4.obj");
    foot1 = glmReadOBJ("k/foot1.obj");
    foot2 = glmReadOBJ("k/foot2.obj");

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
