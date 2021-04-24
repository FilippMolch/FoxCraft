#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int sizeX, unsigned int sizeY) : x(sizeX), y(sizeY){

    float quadVertices[] = {
        // координаты      // текстурные координаты
       -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
       -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    // Установка VAO плоскости
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &hdrFBO);

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, x, y);

    // Прикрепление буферов
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    while (true)
    {
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
            break;
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBuffer::bindFrameBuffer(bool trigg){
    if (trigg)
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    else
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bindColorBuffer(bool trigg, GLFWwindow* window){
    if (trigg){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        
    }
    else{
        glBindTexture(GL_TEXTURE_2D, 0);
    }
 
}

void FrameBuffer::bindColorBuffer(bool trigg) {
    if (trigg) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
     
    }
    else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}

void FrameBuffer::renderCuadForColorBuffer()
{
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}