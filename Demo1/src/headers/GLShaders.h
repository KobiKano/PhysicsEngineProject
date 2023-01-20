#pragma once

//This header is used to store various shader configurations for use in rendering
//avoids unessicary file searches and clutter
static const char* vert1 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"out vec3 Normal;\n"
"out vec3 FragPos;\n"

"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"	Normal = aNormal;\n"
"	FragPos = vec3(model * vec4(aPos, 1.0));\n"
"}\0";

static const char* frag1 = "#version 330 core\n"
"uniform vec3 color;\n"
"uniform vec3 lightColor;\n"
"uniform vec3 lightPos;\n"

"in vec3 Normal;\n"
"in vec3 FragPos;\n"
"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"	float ambientStrength = 0.7;\n"
"	vec3 ambient = ambientStrength * lightColor;\n"

"	vec3 norm = normalize(Normal);\n"
"	vec3 lightDir = normalize(lightPos - FragPos);\n"
"	vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;\n"

"	vec3 fragResult = (ambient + diffuse) * color;\n"
"	FragColor = vec4(fragResult, 1.0);\n"
"}\0";
