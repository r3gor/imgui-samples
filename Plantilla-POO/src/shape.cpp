#include "shape.h"

#include <GL/glew.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <glm\glm.hpp>

Shape::Shape() { }

void Shape::initData() {
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void Shape::render() const {
    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

	glPointSize(10.0); // para ver los vertices del cubo
	glDrawArrays(GL_POINTS, 0, 36);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

