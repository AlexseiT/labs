#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <malloc.h>
#include <cstring>
#include <cmath>
#include <vector>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

GLFWwindow* window;
chrono::high_resolution_clock::time_point timeCheck() {
	return chrono::high_resolution_clock::now();
}
const char* shaderSourceNaive =
R"(
	 #version 430

	 layout (local_size_x = 16, local_size_y = 16) in; 
	 layout(std430, binding = 0) buffer BufferA{float A[];};
	 layout(std430, binding = 1) buffer BufferB{float B[];};

	 uniform int coeff;

	 void main() {
	 uint indexX = gl_GlobalInvocationID.x;
	 uint indexY = gl_GlobalInvocationID.y;
	 B[indexX+coeff*indexY]=A[indexY+coeff*indexX];
	 }
	)";

const char* shaderSourceTransposing =
R"(
	#version 430

	layout (local_size_x = 1, local_size_y = 1) in;

	layout (std430, binding = 0) buffer bufferInput {float inputData[];};
	layout (std430, binding = 1) buffer bufferOutput {float outputData[];};

	void main() {
    uint globalIndex = gl_GlobalInvocationID.y * gl_WorkGroupSize.x + gl_GlobalInvocationID.x;

    uint N = 16;
    uint i = globalIndex / N;
    uint j = globalIndex % N;
    uint indexTranspose = j * N + i;
    outputData[indexTranspose] = inputData[globalIndex];
}
	)";

vector<vector<GLfloat>> Points;
GLuint shaderProgram;
GLuint computeShader;
GLuint buffer[2];

void Display(float* matrix)
{
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int i = 0; i < Points.size(); i++) {
		float color1 = matrix[i]/256;
		float color2 = 1 - color1;
		glColor3f(0.2, color2, color1);
		glVertex3f(Points[i][0], Points[i][1], 0);
	}
	glEnd();
}

void Point(GLfloat x, GLfloat y)
{
	vector<GLfloat> pos(3);
	pos[0] = x;
	pos[1] = y;
	pos[2] = 0.0f;
	Points.push_back(pos);
}

void initGL() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}

	window = glfwCreateWindow(400, 400, "Template window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
}

void InitMatrix(float* matrix, int N)
{
	for (GLuint i = 0; i < N; i++) {
		matrix[i] = i;
	}
}

void PrintMatrix(float* matrix, int size, string handle)
{
	cout << handle << endl << endl;
	Points.erase(Points.begin(), Points.end());
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			float x = (float)i / (2 * size) - 0.2;
			float y = (float)j / (2 * size) - 0.2;
			Point(x, y);
			cout << matrix[j + i * size] << "\t";
		}
		cout << endl;
	}
	printf("\n");
}

bool check = true;

void KeyController(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		check = false;
}

void drawPoints(float* matrix)
{
	check = true;
	while (check)
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Display(matrix);
		glfwSwapBuffers(window);
	}
}

void ÑompileShader()
{
	shaderProgram = glCreateProgram();
	computeShader = glCreateShader(GL_COMPUTE_SHADER);

	glShaderSource(computeShader, 1, &shaderSourceTransposing, NULL);
	glCompileShader(computeShader);
	glAttachShader(shaderProgram, computeShader);
	glLinkProgram(shaderProgram);
}

void ÑompileNaiveShader()
{
	glShaderSource(computeShader, 1, &shaderSourceNaive, NULL);
	glCompileShader(computeShader);
	glAttachShader(shaderProgram, computeShader);
	glLinkProgram(shaderProgram);
}

void InitBuffers(float* matrix, GLuint number)
{
	glGenBuffers(2, buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer[0]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, number * sizeof(float), matrix, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, number * sizeof(float), 0, GL_DYNAMIC_DRAW);
}

chrono::microseconds StartShader(GLuint N, int size)
{
	chrono::high_resolution_clock::time_point begin = timeCheck();
	glUseProgram(shaderProgram);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer[0]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buffer[1]);

	glDispatchCompute(N/size, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);
	chrono::high_resolution_clock::time_point end = timeCheck();
	return chrono::duration_cast<chrono::microseconds>(end - begin);
}
void GetResult(float* matrixTranspose, GLuint N)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer[1]);
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, N * sizeof(float), matrixTranspose);
}

int main()
{
	initGL();
	int size = 16;
	GLuint N = size * size;

	float* matrix = new float[N];

	InitMatrix(matrix, N);
	PrintMatrix(matrix, size, "<<< Matrix >>>");
	glfwSetKeyCallback(window, KeyController);
	drawPoints(matrix);
	ÑompileShader();
	InitBuffers(matrix, N);
	chrono::microseconds time = StartShader(N,1);
	float* matrixTranspose = new float[N];
	GetResult(matrixTranspose, N);
	PrintMatrix(matrixTranspose, size, "<<< Transposing >>>");
	drawPoints(matrixTranspose);

	//
	for (int i = 5; i < 11; ++i)
	{
		glDeleteShader(computeShader);
		glDeleteBuffers(1, &buffer[0]);
		glDeleteBuffers(1, &buffer[1]);

		size = pow(2, i);
		N = size * size;
		matrix = new float[N];

		InitMatrix(matrix, N);
		InitBuffers(matrix, N);

		GLuint id = glGetUniformLocation(shaderProgram, "coeff");
		int coeff = size;
		glUniform1f(id, coeff);

		chrono::microseconds time = StartShader(N,16);
		double timeMS = time.count() * 0.001;
		cout << "Transposing " << size << " x "<< size << " = " << timeMS << " ms" << endl;
	}
	//
	glDeleteProgram(shaderProgram);
	glDeleteShader(computeShader);
	glDeleteBuffers(1, &buffer[0]);
	glDeleteBuffers(1, &buffer[1]);
	//glDeleteBuffers(1, &inputBuffer);
}
