//
//  main.c
//  3DHouse
//
//  Created by Mingjia Shi on 2018/2/23.
//  Copyright © 2018 Mingjia Shi 104467237. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#include <math.h>

typedef void (*GLUTdisplayCB) (void);

void myInit(int *, char **, GLUTdisplayCB);
void SpecialInput(int,int,int,int);
void createGlutMenu(void);
void menu(int);
void drawHouse(void);
void action(int,int);
void initialHouse(void);
void reshape(int,int);

int ldrx,ldry,ldrz,rdrx,rdry,rdrz,rurx,rury,rurz,lurx,lury,lurz;
int lufx,lufy,lufz,ldfx,ldfy,ldfz,rdfx,rdfy,rdfz,rufx,rufy,rufz;
double d,xl = 0.0,yh = 0.0,r = 3.0,oldmx,oldmy;
int mouseClick = 0;


int main(int argc, char * argv[]) {
    //    FILE* pFile = fopen("House", "rb");
    //    if(pFile == 0) exit(0);
    //   200 120 240 440 120 240 440 360 240 200 360 240 200 360 000 200 120 000 440 120 000 440 360 000
    /*    fread(&ldrx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&ldry, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&ldrz, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rdrx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rdry, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rdrz, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rurx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rury, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rurz, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&lurx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&lury, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&lurz, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&lufx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&lufy, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&lufz, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&ldfx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&ldfy, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&ldfz, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rdfx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rdfy, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rdfz, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rufx, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rufy, 3, 1, pFile);
     fread(NULL, 1, 1, pFile);
     fread(&rufz, 3, 1, pFile);*/
    ldrx=-1;ldry=-1;ldrz=1;rdrx=1;rdry=-1;rdrz=1;rurx=1;rury=1;rurz=1;lurx=-1;lury=1;lurz=1;
    ldfx=-1;ldfy=-1;ldfz=-1;rdfx=1;rdfy=-1;rdfz=-1;rufx=1;rufy=1;rufz=-1;lufx=-1;lufy=1;lufz=-1;
    
    d = M_PI/2;
    oldmx = -1;
    oldmy = -1;
    
    //    fclose(pFile);
    
    myInit(&argc, argv, drawHouse);
    
    glutMainLoop();
    return 0;
}

void myInit(int *argc, char ** argv,GLUTdisplayCB displayFunc) {
    glutInit(argc,argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    //glutReshapeFunc(reshape);
    glutDisplayFunc(displayFunc);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //glColor3f(((float) 222)/((float) 255.0), ((float) 222)/((float) 255.0), ((float) 222)/((float) 255.0));
    //glutIdleFunc(displayFunc);
    
    glutMouseFunc(SpecialInput);
    //glutMotionFunc(action);
    createGlutMenu();
}

void createGlutMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Close",1);
    glutAddMenuEntry("Away", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawHouse() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0f,640.0/480.0,1.0f,25.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xl, yh, r, 0, 0, 0, 0, 1, 0);
    initialHouse();
    glEnable(GL_DEPTH_TEST);
    glFlush();
    glutPostRedisplay();
}

void initialHouse() {
    glBegin(GL_QUADS);
     glColor3f(1.0,0.4,0.8);
     glVertex3f((float)ldrx,(float)ldry,(float)ldrz);
     glVertex3f((float)rdrx,(float)rdry,(float)rdrz);
     glVertex3f((float)rurx,(float)rury,(float)rurz);
     glVertex3f((float)lurx,(float)lury,(float)lurz);
     glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,0.8);
    glVertex3f(-0.2,(float)ldry,(float)ldrz + 0.01);
    glVertex3f(0.2,(float)rdry,(float)rdrz + 0.01);
    glVertex3f(0.2,-0.6,(float)rurz + 0.01);
    glVertex3f(-0.2,-0.6,(float)lurz + 0.01);
    glEnd();
     
     glBegin(GL_QUADS);
     glColor3f(1.0,0.2,0.2);
     glVertex3f((float)lurx,(float)lury,(float)lurz);
     glVertex3f((float)rurx,(float)rury,(float)rurz);
     glVertex3f((float)rufx,(float)rufy,(float)rufz);
     glVertex3f((float)lufx,(float)lufy,(float)lufz);
     glEnd();
     
     glBegin(GL_QUADS);
     glColor3f(1.0,0.4,1.0);
     glVertex3f((float)lurx,(float)lury,(float)lurz);
     glVertex3f((float)ldrx,(float)ldry,(float)ldrz);
     glVertex3f((float)ldfx,(float)ldfy,(float)ldfz);
     glVertex3f((float)lufx,(float)lufy,(float)lufz);
     glEnd();
    
    
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,0.8);
    glVertex3f(-1 - 0.01,-0.1,0.1);
    glVertex3f(-1 - 0.01,0.1,0.1);
    glVertex3f(-1 - 0.01,0.1,-0.1);
    glVertex3f(-1 - 0.01,-0.1,-0.1);
    glEnd();
    
     glBegin(GL_QUADS);
     glColor3f(1.0,0.4,1.0);
     glVertex3f((float)rurx,(float)rury,(float)rurz);
     glVertex3f((float)rdrx,(float)rdry,(float)rdrz);
     glVertex3f((float)rdfx,(float)rdfy,(float)rdfz);
     glVertex3f((float)rufx,(float)rufy,(float)rufz);
     glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,0.8);
    glVertex3f(1 + 0.01,-0.1,0.1);
    glVertex3f(1 + 0.01,0.1,0.1);
    glVertex3f(1 + 0.01,0.1,-0.1);
    glVertex3f(1 + 0.01,-0.1,-0.1);
    glEnd();
     
     glBegin(GL_QUADS);
     glColor3f(1.0,0.4,0.8);
     glVertex3f((float)ldfx,(float)ldfy,(float)ldfz);
     glVertex3f((float)rdfx,(float)rdfy,(float)rdfz);
     glVertex3f((float)rufx,(float)rufy,(float)rufz);
     glVertex3f((float)lufx,(float)lufy,(float)lufz);
     glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,0.8);
    glVertex3f(-0.1,-0.1,-1.0 - 0.01);
    glVertex3f(0.1,-0.1,-1.0 - 0.01);
    glVertex3f(0.1,0.1,-1.0 - 0.01);
    glVertex3f(-0.1,0.1,-1.0 - 0.01);
    glEnd();
     
     glBegin(GL_QUADS);
     glColor3f(1.0,0.2,0.2);
     glVertex3f((float)ldrx,(float)ldry,(float)ldrz);
     glVertex3f((float)rdrx,(float)rdry,(float)rdrz);
     glVertex3f((float)rdfx,(float)rdfy,(float)rdfz);
     glVertex3f((float)ldfx,(float)ldfy,(float)ldfz);
     glEnd();
    
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f,(float)w/h,1.0f,1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void menu(int value){
    if(value == 1){
        if(r >= 0)r -= 0.5;
    }
    else if(value == 2) {
        r += 0.5;
    }
    else if(value == 3) {
        exit(0);
    }
}
void SpecialInput(int button,int state,int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseClick = 1;
        
        xl += (x/640.0) - 0.5;
        yh += 0.5 - (y/480.0);
    }
}


void action(int x,int y) {
    d += (double)((x - oldmx) * M_PI / 180);
    xl = 0.03f * (x - oldmx);
    yh += 0.03f * (y - oldmy);
    if(yh > 1.0f) yh = 1.0f;
    else if(yh < -1.0f) yh = -1.0f;
    oldmx = x;
    oldmy = y;
}
