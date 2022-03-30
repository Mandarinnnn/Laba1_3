#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

GLuint VBO; // нужен для хранения указателя на буфер вершин

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);// очистка буфера кадра

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// привязываем указатель к названию цели
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);//функция для отрисовки

    glDisableVertexAttribArray(0);//отключение каждого атрибута вершины

    glutSwapBuffers();//функция, которая меняет фоновый буфер и буфер кадра местами
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[3];// создание массива из трех элементов
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 11.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// привязываем указатель к названию цели
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);//инициализация GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);//здесь задаются параметры окна 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 03");//создание окна

    InitializeGlutCallbacks();

    GLenum res = glewInit();//инициализируем glew
    if (res != GLEW_OK) {//проверяем на ошибки
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//устанавление цвета, который будет использован во время очистки буфера кадра

    CreateVertexBuffer();

    glutMainLoop();//передача контроля GLUT'у
}
