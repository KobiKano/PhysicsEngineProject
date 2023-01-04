#pragma once

//This header is used to store various shader configurations for use in rendering
//avoids unessicary file searches and clutter
static const char* vert1 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos, 1.0);\n"
"}\0";

static const char* frag1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
