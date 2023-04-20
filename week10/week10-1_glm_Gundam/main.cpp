#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
#include "glm.h" ///step02-1 把 source.zip裡的 glm.h 放在同目錄中
///step03-1也要把step02-1的 glm.h也準備好
///glm.cpp 也要加到你的程式目錄裡
GLMmodel * pmodel = NULL; ///step02-1 模型的指標,一開始NULL空的
GLMmodel * phand = NULL;
float angle=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ///step03-1執行前,確認Gundam.obj Gundam.mtl 都在freeglut的bin
    if(pmodel==NULL){ ///第一次會進來 step02-1
        pmodel = glmReadOBJ("body.obj");///檔名照你的檔名 step02-1
        glmUnitize(pmodel);///step02-2 縮放成Unit單位大小(-1..+1)
        glmFacetNormals(pmodel);///step03-1
        glmVertexNormals(pmodel, 90);///step03-1
    }
    if(phand==NULL){ ///第一次會進來 step02-1
        phand = glmReadOBJ("lefthand.obj");///檔名照你的檔名 step02-1
        glmUnitize(phand);///step02-2 縮放成Unit單位大小(-1..+1)
        glmFacetNormals(phand);///step03-1
        glmVertexNormals(phand, 90);///step03-1
    }
    glutSolidSphere(0.1,30,30);
    glPushMatrix();
        glRotatef(angle, 0,1,0);
        glTranslatef(0,-0.1,0);
        glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE); ///step02-1
    glPopMatrix();
    ///glutSolidTeapot( 0.3 );
    angle++;
    glutSwapBuffers();
}
int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week08");
    myTexture("Diffuse.jpg");///step03-2圖檔也是放freeglut的bin
    glEnable(GL_DEPTH_TEST);///下週再教3D的glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
