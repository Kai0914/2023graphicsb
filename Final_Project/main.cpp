#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * uparmR = NULL;
GLMmodel * lowarmR = NULL;
int show[4] = {1, 1, 1, 1};
int ID = 3;
void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    glutPostRedisplay();
}
FILE * fout = NULL; ///step02-2 一開始,檔案沒有開, NULL
FILE * fin = NULL; ///step02-2 要讀檔用的指標, 一開始也是 NULL
float teapotX=0, teapotY=0; ///幫我們看移動值
float angle=0, angle2=0, angle3=0;///step03-2 擺動作
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(0.2, 0.2, 0.2); ///week13_step02-2
        if(body==NULL){///week13 step02-1
            head = glmReadOBJ("model/head.obj");
            body = glmReadOBJ("model/body.obj");///week13 step02-1
            uparmR = glmReadOBJ("model/uparmR.obj");///Week13 step03-1
            lowarmR = glmReadOBJ("model/lowarmR.obj");///Week13 step03-1
            ///glmUnitize(body); ///week13 step02-1 這行之後會改
        }
        if(ID==0) glColor3f(1,0,0); ///選定的,設紅色
        else glColor3f(1,1,1); ///沒選定,設白色
        if(show[0]) glmDraw(head, GLM_MATERIAL);///Week13 step03-1

        if(ID==1) glColor3f(1,0,0); ///選定的,設紅色
        else glColor3f(1,1,1); ///沒選定,設白色
        if(show[1]) glmDraw(body, GLM_MATERIAL);///week13 step02-1這行之後會改

        glPushMatrix();
            glTranslatef(-1.200000, +0.453333, 0); ///wee14_step03-1 反過來
            glRotatef(angle, 0, 0, 1); ///week14_step03-1_TRT建出來
            //glTranslatef(teapotX, teapotY, 0); ///week14_step03-1_TRT建出來
            glTranslatef(1.200000, -0.453333, 0); ///week14_step03-1_的結果

            if(ID==2) glColor3f(1,0,0); ///選定的,設紅色
            else glColor3f(1,1,1); ///沒選定,設白色
            if(show[2]) glmDraw(uparmR, GLM_MATERIAL);///Week13 step03-1
            glPushMatrix();
                glTranslatef(-1.959999, +0.113333, 0);
                glRotatef(angle, 0, 0, 1);
                glTranslatef(1.959999, -0.113333, 0);

                if(ID==3) glColor3f(1,0,0); ///選定的,設紅色
                else glColor3f(1,1,1); ///沒選定,設白色
                if(show[3]) glmDraw(lowarmR, GLM_MATERIAL);///Week13 step03-1
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
    glColor3f(0, 1, 0);///week14_step03-1 放個小茶壼,在正中心,當成參考點
    glutSolidTeapot( 0.02 );///week14_step03-1 放個小茶壼,在正中心,當成參考點
    glutSwapBuffers();
}
int oldX = 0, oldY = 0; ///Week13 step03-2
void motion(int x, int y){ ///Week13 step03-2
    teapotX += (x - oldX)/150.0; ///Week13 step03-2
    teapotY -= (y - oldY)/150.0; ///Week13 step03-2
    oldX = x;
    oldY = y;
    angle = x; ///week14_step03-1
    printf("glTranslatef(%f, %f, 0);\n", teapotX, teapotY);
    glutPostRedisplay(); ///Week13 step03-2
} ///Week13 step03-2
void mouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN){
        oldX = x; ///teapotX = (x-150)/150.0;
        oldY = y; ///teapotY = (150-y)/150.0;
        angle = x;
        ///printf("glTranslatef(%f, %f, 0);\n", teapotX, teapotY);
        ///if(fout==NULL) fout = fopen("file4.txt", "w"); ///step02-2 沒開檔,就開
        ///fprintf(fout, "%f %f\n", teapotX, teapotY); ///step02-2 要再存座標
    }
    display();
}
//void keyboard(unsigned char key, int x, int y) ///step02-2 keyboard函式
//{
//    if(fin==NULL){ ///step02-2 如果檔案還沒 fopen(), 就開它
//        fclose(fout); ///前面mouse會開fout指標, 所以要關掉
//        fin = fopen("file4.txt", "r"); ///step02-2 沒開檔,就開
//    }
//    ///fscanf(fin, "%f %f", &teapotX, &teapotY); ///step02-2 真的讀檔
//    display(); ///step02-2 重畫畫面
//}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week12");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion); ///Week13 step03-3
    glutKeyboardFunc(keyboard); ///step02-2 keyboard要做事囉(開檔、讀檔)

    glutMainLoop();
}
