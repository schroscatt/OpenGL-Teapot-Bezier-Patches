#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ply.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 model;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = model * vec4(aPos, 1.0);;\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.8f, 0.5f, 1.0f);\n"
    "}\n\0";


int screen_width=800, screen_height=600;

struct vertex { GLfloat x, y, z; };
struct vertex teapot_cp_vertices[] = {
  // 1
  {  1.4   ,   0.0   ,  2.4     },
  {  1.4   ,  -0.784 ,  2.4     },
  {  0.784 ,  -1.4   ,  2.4     },
  {  0.0   ,  -1.4   ,  2.4     },
  {  1.3375,   0.0   ,  2.53125 },
  {  1.3375,  -0.749 ,  2.53125 },
  {  0.749 ,  -1.3375,  2.53125 },
  {  0.0   ,  -1.3375,  2.53125 },
  {  1.4375,    0.0  ,  2.53125 },
  {  1.4375,  -0.805 ,  2.53125 },
  // 11
  {  0.805 ,  -1.4375,  2.53125 },
  {  0.0   ,  -1.4375,  2.53125 },
  {  1.5   ,   0.0   ,  2.4     },
  {  1.5   ,  -0.84  ,  2.4     },
  {  0.84  ,  -1.5   ,  2.4     },
  {  0.0   ,  -1.5   ,  2.4     },
  { -0.784 ,  -1.4   ,  2.4     },
  { -1.4   ,  -0.784 ,  2.4     },
  { -1.4   ,   0.0   ,  2.4     },
  { -0.749 ,  -1.3375,  2.53125 },
  // 21
  { -1.3375,  -0.749 ,  2.53125 },
  { -1.3375,   0.0   ,  2.53125 },
  { -0.805 ,  -1.4375,  2.53125 },
  { -1.4375,  -0.805 ,  2.53125 },
  { -1.4375,   0.0   ,  2.53125 },
  { -0.84  ,  -1.5   ,  2.4     },
  { -1.5   ,  -0.84  ,  2.4     },
  { -1.5   ,   0.0   ,  2.4     },
  { -1.4   ,   0.784 ,  2.4     },
  { -0.784 ,   1.4   ,  2.4     },
  // 31
  {  0.0   ,   1.4   ,  2.4     },
  { -1.3375,   0.749 ,  2.53125 },
  { -0.749 ,   1.3375,  2.53125 },
  {  0.0   ,   1.3375,  2.53125 },
  { -1.4375,   0.805 ,  2.53125 },
  { -0.805 ,   1.4375,  2.53125 },
  {  0.0   ,   1.4375,  2.53125 },
  { -1.5   ,   0.84  ,  2.4     },
  { -0.84  ,   1.5   ,  2.4     },
  {  0.0   ,   1.5   ,  2.4     },
  // 41
  {  0.784 ,   1.4   ,  2.4     },
  {  1.4   ,   0.784 ,  2.4     },
  {  0.749 ,   1.3375,  2.53125 },
  {  1.3375,   0.749 ,  2.53125 },
  {  0.805 ,   1.4375,  2.53125 },
  {  1.4375,   0.805 ,  2.53125 },
  {  0.84  ,   1.5   ,  2.4     },
  {  1.5   ,   0.84  ,  2.4     },
  {  1.75  ,   0.0   ,  1.875   },
  {  1.75  ,  -0.98  ,  1.875   },
  // 51
  {  0.98  ,  -1.75  ,  1.875   },
  {  0.0   ,  -1.75  ,  1.875   },
  {  2.0   ,   0.0   ,  1.35    },
  {  2.0   ,  -1.12  ,  1.35    },
  {  1.12  ,  -2.0   ,  1.35    },
  {  0.0   ,  -2.0   ,  1.35    },
  {  2.0   ,   0.0   ,  0.9     },
  {  2.0   ,  -1.12  ,  0.9     },
  {  1.12  ,  -2.0   ,  0.9     },
  {  0.0   ,  -2.0   ,  0.9     },
  // 61
  { -0.98  ,  -1.75  ,  1.875   },
  { -1.75  ,  -0.98  ,  1.875   },
  { -1.75  ,   0.0   ,  1.875   },
  { -1.12  ,  -2.0   ,  1.35    },
  { -2.0   ,  -1.12  ,  1.35    },
  { -2.0   ,   0.0   ,  1.35    },
  { -1.12  ,  -2.0   ,  0.9     },
  { -2.0   ,  -1.12  ,  0.9     },
  { -2.0   ,   0.0   ,  0.9     },
  { -1.75  ,   0.98  ,  1.875   },
  // 71
  { -0.98  ,   1.75  ,  1.875   },
  {  0.0   ,   1.75  ,  1.875   },
  { -2.0   ,   1.12  ,  1.35    },
  { -1.12  ,   2.0   ,  1.35    },
  {  0.0   ,   2.0   ,  1.35    },
  { -2.0   ,   1.12  ,  0.9     },
  { -1.12  ,   2.0   ,  0.9     },
  {  0.0   ,   2.0   ,  0.9     },
  {  0.98  ,   1.75  ,  1.875   },
  {  1.75  ,   0.98  ,  1.875   },
  // 81
  {  1.12  ,   2.0   ,  1.35    },
  {  2.0   ,   1.12  ,  1.35    },
  {  1.12  ,   2.0   ,  0.9     },
  {  2.0   ,   1.12  ,  0.9     },
  {  2.0   ,   0.0   ,  0.45    },
  {  2.0   ,  -1.12  ,  0.45    },
  {  1.12  ,  -2.0   ,  0.45    },
  {  0.0   ,  -2.0   ,  0.45    },
  {  1.5   ,   0.0   ,  0.225   },
  {  1.5   ,  -0.84  ,  0.225   },
  // 91
  {  0.84  ,  -1.5   ,  0.225   },
  {  0.0   ,  -1.5   ,  0.225   },
  {  1.5   ,   0.0   ,  0.15    },
  {  1.5   ,  -0.84  ,  0.15    },
  {  0.84  ,  -1.5   ,  0.15    },
  {  0.0   ,  -1.5   ,  0.15    },
  { -1.12  ,  -2.0   ,  0.45    },
  { -2.0   ,  -1.12  ,  0.45    },
  { -2.0   ,   0.0   ,  0.45    },
  { -0.84  ,  -1.5   ,  0.225   },
  // 101
  { -1.5   ,  -0.84  ,  0.225   },
  { -1.5   ,   0.0   ,  0.225   },
  { -0.84  ,  -1.5   ,  0.15    },
  { -1.5   ,  -0.84  ,  0.15    },
  { -1.5   ,   0.0   ,  0.15    },
  { -2.0   ,   1.12  ,  0.45    },
  { -1.12  ,   2.0   ,  0.45    },
  {  0.0   ,   2.0   ,  0.45    },
  { -1.5   ,   0.84  ,  0.225   },
  { -0.84  ,   1.5   ,  0.225   },
  // 111
  {  0.0   ,   1.5   ,  0.225   },
  { -1.5   ,   0.84  ,  0.15    },
  { -0.84  ,   1.5   ,  0.15    },
  {  0.0   ,   1.5   ,  0.15    },
  {  1.12  ,   2.0   ,  0.45    },
  {  2.0   ,   1.12  ,  0.45    },
  {  0.84  ,   1.5   ,  0.225   },
  {  1.5   ,   0.84  ,  0.225   },
  {  0.84  ,   1.5   ,  0.15    },
  {  1.5   ,   0.84  ,  0.15    },
  // 121
  { -1.6   ,   0.0   ,  2.025   },
  { -1.6   ,  -0.3   ,  2.025   },
  { -1.5   ,  -0.3   ,  2.25    },
  { -1.5   ,   0.0   ,  2.25    },
  { -2.3   ,   0.0   ,  2.025   },
  { -2.3   ,  -0.3   ,  2.025   },
  { -2.5   ,  -0.3   ,  2.25    },
  { -2.5   ,   0.0   ,  2.25    },
  { -2.7   ,   0.0   ,  2.025   },
  { -2.7   ,  -0.3   ,  2.025   },
  // 131
  { -3.0   ,  -0.3   ,  2.25    },
  { -3.0   ,   0.0   ,  2.25    },
  { -2.7   ,   0.0   ,  1.8     },
  { -2.7   ,  -0.3   ,  1.8     },
  { -3.0   ,  -0.3   ,  1.8     },
  { -3.0   ,   0.0   ,  1.8     },
  { -1.5   ,   0.3   ,  2.25    },
  { -1.6   ,   0.3   ,  2.025   },
  { -2.5   ,   0.3   ,  2.25    },
  { -2.3   ,   0.3   ,  2.025   },
  // 141
  { -3.0   ,   0.3   ,  2.25    },
  { -2.7   ,   0.3   ,  2.025   },
  { -3.0   ,   0.3   ,  1.8     },
  { -2.7   ,   0.3   ,  1.8     },
  { -2.7   ,   0.0   ,  1.575   },
  { -2.7   ,  -0.3   ,  1.575   },
  { -3.0   ,  -0.3   ,  1.35    },
  { -3.0   ,   0.0   ,  1.35    },
  { -2.5   ,   0.0   ,  1.125   },
  { -2.5   ,  -0.3   ,  1.125   },
  // 151
  { -2.65  ,  -0.3   ,  0.9375  },
  { -2.65  ,   0.0   ,  0.9375  },
  { -2.0   ,  -0.3   ,  0.9     },
  { -1.9   ,  -0.3   ,  0.6     },
  { -1.9   ,   0.0   ,  0.6     },
  { -3.0   ,   0.3   ,  1.35    },
  { -2.7   ,   0.3   ,  1.575   },
  { -2.65  ,   0.3   ,  0.9375  },
  { -2.5   ,   0.3   ,  1.1255  },
  { -1.9   ,   0.3   ,  0.6     },
  // 161
  { -2.0   ,   0.3   ,  0.9     },
  {  1.7   ,   0.0   ,  1.425   },
  {  1.7   ,  -0.66  ,  1.425   },
  {  1.7   ,  -0.66  ,  0.6     },
  {  1.7   ,   0.0   ,  0.6     },
  {  2.6   ,   0.0   ,  1.425   },
  {  2.6   ,  -0.66  ,  1.425   },
  {  3.1   ,  -0.66  ,  0.825   },
  {  3.1   ,   0.0   ,  0.825   },
  {  2.3   ,   0.0   ,  2.1     },
  // 171
  {  2.3   ,  -0.25  ,  2.1     },
  {  2.4   ,  -0.25  ,  2.025   },
  {  2.4   ,   0.0   ,  2.025   },
  {  2.7   ,   0.0   ,  2.4     },
  {  2.7   ,  -0.25  ,  2.4     },
  {  3.3   ,  -0.25  ,  2.4     },
  {  3.3   ,   0.0   ,  2.4     },
  {  1.7   ,   0.66  ,  0.6     },
  {  1.7   ,   0.66  ,  1.425   },
  {  3.1   ,   0.66  ,  0.825   },
  // 181
  {  2.6   ,   0.66  ,  1.425   },
  {  2.4   ,   0.25  ,  2.025   },
  {  2.3   ,   0.25  ,  2.1     },
  {  3.3   ,   0.25  ,  2.4     },
  {  2.7   ,   0.25  ,  2.4     },
  {  2.8   ,   0.0   ,  2.475   },
  {  2.8   ,  -0.25  ,  2.475   },
  {  3.525 ,  -0.25  ,  2.49375 },
  {  3.525 ,   0.0   ,  2.49375 },
  {  2.9   ,   0.0   ,  2.475   },
  // 191
  {  2.9   ,  -0.15  ,  2.475   },
  {  3.45  ,  -0.15  ,  2.5125  },
  {  3.45  ,   0.0   ,  2.5125  },
  {  2.8   ,   0.0   ,  2.4     },
  {  2.8   ,  -0.15  ,  2.4     },
  {  3.2   ,  -0.15  ,  2.4     },
  {  3.2   ,   0.0   ,  2.4     },
  {  3.525 ,   0.25  ,  2.49375 },
  {  2.8   ,   0.25  ,  2.475   },
  {  3.45  ,   0.15  ,  2.5125  },
  // 201
  {  2.9   ,   0.15  ,  2.475   },
  {  3.2   ,   0.15  ,  2.4     },
  {  2.8   ,   0.15  ,  2.4     },
  {  0.0   ,   0.0   ,  3.15    },
  {  0.0   ,  -0.002 ,  3.15    },
  {  0.002 ,   0.0   ,  3.15    },
  {  0.8   ,   0.0   ,  3.15    },
  {  0.8   ,  -0.45  ,  3.15    },
  {  0.45  ,  -0.8   ,  3.15    },
  {  0.0   ,  -0.8   ,  3.15    },
  // 211
  {  0.0   ,   0.0   ,  2.85    },
  {  0.2   ,   0.0   ,  2.7     },
  {  0.2   ,  -0.112 ,  2.7     },
  {  0.112 ,  -0.2   ,  2.7     },
  {  0.0   ,  -0.2   ,  2.7     },
  { -0.002 ,   0.0   ,  3.15    },
  { -0.45  ,  -0.8   ,  3.15    },
  { -0.8   ,  -0.45  ,  3.15    },
  { -0.8   ,   0.0   ,  3.15    },
  { -0.112 ,  -0.2   ,  2.7     },
  // 221
  { -0.2   ,  -0.112 ,  2.7     },
  { -0.2   ,   0.0   ,  2.7     },
  {  0.0   ,   0.002 ,  3.15    },
  { -0.8   ,   0.45  ,  3.15    },
  { -0.45  ,   0.8   ,  3.15    },
  {  0.0   ,   0.8   ,  3.15    },
  { -0.2   ,   0.112 ,  2.7     },
  { -0.112 ,   0.2   ,  2.7     },
  {  0.0   ,   0.2   ,  2.7     },
  {  0.45  ,   0.8   ,  3.15    },
  // 231
  {  0.8   ,   0.45  ,  3.15    },
  {  0.112 ,   0.2   ,  2.7     },
  {  0.2   ,   0.112 ,  2.7     },
  {  0.4   ,   0.0   ,  2.55    },
  {  0.4   ,  -0.224 ,  2.55    },
  {  0.224 ,  -0.4   ,  2.55    },
  {  0.0   ,  -0.4   ,  2.55    },
  {  1.3   ,   0.0   ,  2.55    },
  {  1.3   ,  -0.728 ,  2.55    },
  {  0.728 ,  -1.3   ,  2.55    },
  // 241
  {  0.0   ,  -1.3   ,  2.55    },
  {  1.3   ,   0.0   ,  2.4     },
  {  1.3   ,  -0.728 ,  2.4     },
  {  0.728 ,  -1.3   ,  2.4     },
  {  0.0   ,  -1.3   ,  2.4     },
  { -0.224 ,  -0.4   ,  2.55    },
  { -0.4   ,  -0.224 ,  2.55    },
  { -0.4   ,   0.0   ,  2.55    },
  { -0.728 ,  -1.3   ,  2.55    },
  { -1.3   ,  -0.728 ,  2.55    },
  // 251
  { -1.3   ,   0.0   ,  2.55    },
  { -0.728 ,  -1.3   ,  2.4     },
  { -1.3   ,  -0.728 ,  2.4     },
  { -1.3   ,   0.0   ,  2.4     },
  { -0.4   ,   0.224 ,  2.55    },
  { -0.224 ,   0.4   ,  2.55    },
  {  0.0   ,   0.4   ,  2.55    },
  { -1.3   ,   0.728 ,  2.55    },
  { -0.728 ,   1.3   ,  2.55    },
  {  0.0   ,   1.3   ,  2.55    },
  // 261
  { -1.3   ,   0.728 ,  2.4     },
  { -0.728 ,   1.3   ,  2.4     },
  {  0.0   ,   1.3   ,  2.4     },
  {  0.224 ,   0.4   ,  2.55    },
  {  0.4   ,   0.224 ,  2.55    },
  {  0.728 ,   1.3   ,  2.55    },
  {  1.3   ,   0.728 ,  2.55    },
  {  0.728 ,   1.3   ,  2.4     },
  {  1.3   ,   0.728 ,  2.4     },
};
#define TEAPOT_NB_PATCHES 28
#define ORDER 3
GLushort teapot_patches[][ORDER+1][ORDER+1] = {
  // rim
  { {   1,   2,   3,   4 }, {   5,   6,   7,   8 }, {   9,  10,  11,  12 }, {  13,  14,  15,  16, } },
  { {   4,  17,  18,  19 }, {   8,  20,  21,  22 }, {  12,  23,  24,  25 }, {  16,  26,  27,  28, } },
  { {  19,  29,  30,  31 }, {  22,  32,  33,  34 }, {  25,  35,  36,  37 }, {  28,  38,  39,  40, } },
  { {  31,  41,  42,   1 }, {  34,  43,  44,   5 }, {  37,  45,  46,   9 }, {  40,  47,  48,  13, } },
  // body
  { {  13,  14,  15,  16 }, {  49,  50,  51,  52 }, {  53,  54,  55,  56 }, {  57,  58,  59,  60, } },
  { {  16,  26,  27,  28 }, {  52,  61,  62,  63 }, {  56,  64,  65,  66 }, {  60,  67,  68,  69, } },
  { {  28,  38,  39,  40 }, {  63,  70,  71,  72 }, {  66,  73,  74,  75 }, {  69,  76,  77,  78, } },
  { {  40,  47,  48,  13 }, {  72,  79,  80,  49 }, {  75,  81,  82,  53 }, {  78,  83,  84,  57, } },
  { {  57,  58,  59,  60 }, {  85,  86,  87,  88 }, {  89,  90,  91,  92 }, {  93,  94,  95,  96, } },
  { {  60,  67,  68,  69 }, {  88,  97,  98,  99 }, {  92, 100, 101, 102 }, {  96, 103, 104, 105, } },
  { {  69,  76,  77,  78 }, {  99, 106, 107, 108 }, { 102, 109, 110, 111 }, { 105, 112, 113, 114, } },
  { {  78,  83,  84,  57 }, { 108, 115, 116,  85 }, { 111, 117, 118,  89 }, { 114, 119, 120,  93, } },
  // handle
  { { 121, 122, 123, 124 }, { 125, 126, 127, 128 }, { 129, 130, 131, 132 }, { 133, 134, 135, 136, } },
  { { 124, 137, 138, 121 }, { 128, 139, 140, 125 }, { 132, 141, 142, 129 }, { 136, 143, 144, 133, } },
  { { 133, 134, 135, 136 }, { 145, 146, 147, 148 }, { 149, 150, 151, 152 }, {  69, 153, 154, 155, } },
  { { 136, 143, 144, 133 }, { 148, 156, 157, 145 }, { 152, 158, 159, 149 }, { 155, 160, 161,  69, } },
  // spout
  { { 162, 163, 164, 165 }, { 166, 167, 168, 169 }, { 170, 171, 172, 173 }, { 174, 175, 176, 177, } },
  { { 165, 178, 179, 162 }, { 169, 180, 181, 166 }, { 173, 182, 183, 170 }, { 177, 184, 185, 174, } },
  { { 174, 175, 176, 177 }, { 186, 187, 188, 189 }, { 190, 191, 192, 193 }, { 194, 195, 196, 197, } },
  { { 177, 184, 185, 174 }, { 189, 198, 199, 186 }, { 193, 200, 201, 190 }, { 197, 202, 203, 194, } },
  // lid
  { { 204, 204, 204, 204 }, { 207, 208, 209, 210 }, { 211, 211, 211, 211 }, { 212, 213, 214, 215, } },
  { { 204, 204, 204, 204 }, { 210, 217, 218, 219 }, { 211, 211, 211, 211 }, { 215, 220, 221, 222, } },
  { { 204, 204, 204, 204 }, { 219, 224, 225, 226 }, { 211, 211, 211, 211 }, { 222, 227, 228, 229, } },
  { { 204, 204, 204, 204 }, { 226, 230, 231, 207 }, { 211, 211, 211, 211 }, { 229, 232, 233, 212, } },
  { { 212, 213, 214, 215 }, { 234, 235, 236, 237 }, { 238, 239, 240, 241 }, { 242, 243, 244, 245, } },
  { { 215, 220, 221, 222 }, { 237, 246, 247, 248 }, { 241, 249, 250, 251 }, { 245, 252, 253, 254, } },
  { { 222, 227, 228, 229 }, { 248, 255, 256, 257 }, { 251, 258, 259, 260 }, { 254, 261, 262, 263, } },
  { { 229, 232, 233, 212 }, { 257, 264, 265, 234 }, { 260, 266, 267, 238 }, { 263, 268, 269, 242, } },
  // no bottom!
};
#define RESU 10
#define RESV 10
struct vertex teapot_vertices[TEAPOT_NB_PATCHES * RESU*RESV];
GLushort teapot_elements[TEAPOT_NB_PATCHES * (RESU-1)*(RESV-1) * 2*3];

float bernstein_polynomial(int i, int n, float u);
float binomial_coefficient(int i, int n);
int factorial(int n);


void build_control_points(int patch, struct vertex control_points[][ORDER+1]) {
  for (int i = 0; i <= ORDER; i++)
    for (int j = 0; j <= ORDER; j++)
      control_points[i][j] = teapot_cp_vertices[teapot_patches[patch][i][j] - 1];
}

struct vertex compute_position(struct vertex control_points[][ORDER+1], float u, float v) {
  struct vertex result = { 0.0, 0.0, 0.0 };
  for (int i = 0; i <= ORDER; i++) {
    float poly_i = bernstein_polynomial(i, ORDER, u);
    for (int j = 0; j <= ORDER; j++) {
      float poly_j = bernstein_polynomial(j, ORDER, v);
      //sum from the equation 
      result.x += poly_i * poly_j * control_points[i][j].x;
      result.y += poly_i * poly_j * control_points[i][j].y;
      result.z += poly_i * poly_j * control_points[i][j].z;
    }
  }
  return result;
}

void build_teapot() {
  // Vertices
  for (int patch = 0; patch < TEAPOT_NB_PATCHES; patch++) {
    struct vertex control_points[ORDER+1][ORDER+1];
    build_control_points(patch, control_points);
    for (int ru = 0; ru <= RESU-1; ru++) {
      float u = 1.0 * ru / (RESU-1);
      for (int rv = 0; rv <= RESV-1; rv++) {
	        float v = 1.0 * rv / (RESV-1);
	        teapot_vertices[patch*RESU*RESV + ru*RESV + rv] = compute_position(control_points, u, v);
      }
    }
  }

  // Elements
  int n = 0;
  for (int p = 0; p < TEAPOT_NB_PATCHES; p++)
    for (int ru = 0; ru < RESU-1; ru++)
      for (int rv = 0; rv < RESV-1; rv++) {
	    // 1 square ABCD = 2 triangles ABC + CDA
	    // ABC
	      teapot_elements[n] = p*RESU*RESV +  ru   *RESV +  rv; 
	      teapot_elements[n + 1] = p*RESU*RESV +  ru   *RESV + (rv+1);
	      teapot_elements[n + 2] = p*RESU*RESV + (ru+1)*RESV + (rv+1);

	    // CDA
	      teapot_elements[n + 3] = p*RESU*RESV + (ru+1)*RESV + (rv+1);
	      teapot_elements[n + 4] = p*RESU*RESV + (ru+1)*RESV +  rv;
	      teapot_elements[n + 5] = p*RESU*RESV +  ru   *RESV +  rv;

        n += 6;
      }
}

float bernstein_polynomial(int i, int n, float u) {
  return binomial_coefficient(i, n) * powf(u, i) * powf(1-u, n-i);
}

float binomial_coefficient(int i, int n) {
  assert(i >= 0); assert(n >= 0);
  return 1.0f * factorial(n) / (factorial(i) * factorial(n-i));
}
int factorial(int n) {
  assert(n >= 0);
  int result = 1;
  for (int i = n; i > 1; i--)
    result *= i;
  return result;
}

int main()
{
    build_teapot();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(teapot_vertices), teapot_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(teapot_elements), teapot_elements, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 


    glBindVertexArray(0); 


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.3f, 0.4f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);

        glm::mat4 model  = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, sizeof(teapot_elements), GL_UNSIGNED_SHORT, 0);        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}