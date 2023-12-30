#include <GL/glew.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <chrono>
#include <iomanip>
using namespace std;

chrono::high_resolution_clock::time_point wtime() {
	return chrono::high_resolution_clock::now();
}

void errorCallback(int error, const char* description) {
	cerr << "GLFW ERROR " << error << ": " << description << endl;
}

class GPUAlgorithm
{
protected:
	const char* shaderString;
	GLuint shader;
	GLint compileTrue;
	GLuint program;
	GLuint N;
	double time;
	GLuint matrixBuffer;
	GLuint vectorBuffer;
	GLuint resultBuffer;
public:
	void SetSize(GLuint N)
	{
		this->N = N;
	}
	void CreateProgramm()
	{
		program = glCreateProgram();
		glAttachShader(program, shader);
		glLinkProgram(program);
	}
	void InitMatrix(vector<float>& matrix)
	{
		for (GLuint i = 0; i < N * N; i++) {
			matrix.push_back(i);
		}
	}
	void InitVector(vector<float>& vector)
	{
		for (GLuint i = 0; i < N; i++) {
			vector.push_back(i);
		}
	}
	void PrintMatrix(vector<float>& matrix)
	{
		cout << "--MATRIX--\n";
		for (int i = 0; i < N * N; ++i) {
			cout << setw(4) << matrix[i] << ' ';
			if (i > 0 && i % N == N - 1) cout << endl;
		}
	}
	void PrintVector(vector<float>& vector)
	{
		cout << "\n--VECTOR--\n";
		for (int i = 0; i < N; ++i) {
			cout << vector[i] << ' ';
		}
		cout << endl;
	}
	double GetTime()
	{
		return time;
	}
};
class Transposing: public GPUAlgorithm
{
private:
public:
	Transposing()
	{
		ifstream shaderFiles("transpose.comp");
		string shaderFile((istreambuf_iterator<char>(shaderFiles)), istreambuf_iterator<char>());
		shaderString = shaderFile.c_str();
		shader = glCreateShader(GL_COMPUTE_SHADER);   //<-- создаем новый шейдер
		glShaderSource(shader, 1, &shaderString, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileTrue); //<-- проверка на успешную компиляцию

		if (!compileTrue)
		{
			cout << "Transposing Shader ERROR" << endl;
			glDeleteShader(shader);
		}
		CreateProgramm();//Создание программы
	}
	void GetResult()
	{
		float* resultData = new float[N * N];
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, resultBuffer);
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, N * N * sizeof(float), resultData);


		cout << "--RESULT--\n";
		for (int i = 0; i < N * N; ++i) {
			cout << setw(4) << resultData[i] << ' ';
			if (i > 0 && i % N == N - 1) cout << endl;
		}

		delete[] resultData;
	}
	void Transpose()
	{
		vector<float> matrixA;
		//Заполнение матрицы
		InitMatrix(matrixA);
		//Заполнение вектора
		PrintMatrix(matrixA);
		cout << endl;

		chrono::high_resolution_clock::time_point start = wtime();// замер времени старт
		////Здесь работа шейдера
		GLuint matrixBufferBinding = 0;
		GLuint resultBufferBinding = 1;

		glGenBuffers(1, &matrixBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, matrixBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, N * N * sizeof(float), matrixA.data(), GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, matrixBuffer);

		glGenBuffers(1, &resultBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, resultBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, N * N * sizeof(float), nullptr, GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, resultBuffer);//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, resultBuffer);


		//Ставим мост между программой и контекстом
		glUseProgram(program);

		//Выполнение шейдера
		glDispatchCompute(1, 1, 1);

		//Ждем завершения вычисления
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		//Копируем результат из буфера
		GetResult();

		//Удаление буфферов
		glDeleteBuffers(1, &matrixBuffer);
		glDeleteBuffers(1, &vectorBuffer);
		glDeleteBuffers(1, &resultBuffer);

		chrono::high_resolution_clock::time_point end = wtime();
		chrono::milliseconds timer = std::chrono::duration_cast<chrono::milliseconds>(end - start);
		time = timer.count();


		glDeleteProgram(program);
		glDeleteShader(shader);
	}
};

class Multiplication : public GPUAlgorithm
{
private:
public:
	Multiplication()
	{
		ifstream shaderFiles("multiply.comp");
		string shaderFile((istreambuf_iterator<char>(shaderFiles)), istreambuf_iterator<char>());
		shaderString = shaderFile.c_str();
		shader = glCreateShader(GL_COMPUTE_SHADER);   //<-- создаем новый шейдер
		glShaderSource(shader, 1, &shaderString, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileTrue); //<-- проверка на успешную компиляцию

		if (!compileTrue) 
		{
			cout << "Multiplication Shader ERROR" << endl;
			glDeleteShader(shader);
		}
		CreateProgramm();//Создание программы
	}
	void GetResult()
	{
		float* resultData = new float[N];
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, resultBuffer);
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, N * sizeof(float), resultData);

		cout << "--RESULT--\n";
		for (int i = 0; i < N; i++) {
			cout << resultData[i] << " ";
		}
		delete[] resultData;
	}
	void Multiply()
	{
		vector<float> matrix;
		vector<float> vector;

		//Заполнение матрицы
		InitMatrix(matrix);
		//Заполнение вектора
		InitVector(vector);

		PrintMatrix(matrix);
		PrintVector(vector);
		cout << endl;

		chrono::high_resolution_clock::time_point start = wtime();// замер времени старт
		////Здесь работа шейдера
		GLuint matrixBufferBinding = 0;
		GLuint vectorBufferBinding = 1;
		GLuint resultBufferBinding = 2;

		glGenBuffers(1, &matrixBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, matrixBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, N * N * sizeof(float), matrix.data(), GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, matrixBuffer);

		glGenBuffers(1, &vectorBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, vectorBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, N * sizeof(float), vector.data(), GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, vectorBuffer);

		glGenBuffers(1, &resultBuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, resultBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, N * N * sizeof(float), nullptr, GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, resultBuffer);//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, resultBuffer);


		//Установка размера матрицы в шейдере
		GLuint matrixRowsLocation = glGetUniformLocation(program, "matrixRows");
		GLuint matrixColumnsLocation = glGetUniformLocation(program, "matrixColumns");

		//Ставим мост между программой и контекстом
		glUseProgram(program);
		glUniform1ui(matrixRowsLocation, N);
		glUniform1ui(matrixColumnsLocation, N);

		//Выполнение шейдера
		glDispatchCompute(N, N, 1);

		//Ждем завершения вычисления
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		//Копируем результат из буфера
		GetResult();

		//Удаление буфферов
		glDeleteBuffers(1, &matrixBuffer);
		glDeleteBuffers(1, &vectorBuffer);
		glDeleteBuffers(1, &resultBuffer);

		chrono::high_resolution_clock::time_point end = wtime();
		chrono::milliseconds timer = std::chrono::duration_cast<chrono::milliseconds>(end - start);
		time = timer.count();


		glDeleteProgram(program);
		glDeleteShader(shader);
	}
};

class Controller
{
private:
	GLFWwindow* window;
	GLuint size = 20;
	GLuint w = 600;
	GLuint h = 600;
public:
	Controller()
	{
		InitGLFW();
		glewInit();
		glViewport(0, 0, w, h);
	}
	void InitGLFW()
	{
		glfwSetErrorCallback(errorCallback);
		glfwInit();
		/* --- Установка OpenGL 4.x --- */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		/* --- Установка OpenGL 4.3 --- */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		/* --- Отключение старых функций OpenGL --- */
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		/* --- Окно не изменяет размер --- */
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		window = glfwCreateWindow(w, h, "OpenGL", nullptr, nullptr); //NULL или nullptr
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
	}

	void Compute()
	{

		Multiplication multiplicationObject;
		multiplicationObject.SetSize(size);
		multiplicationObject.Multiply();
		cout << "\nMultiply Time (20 x 20) = " << multiplicationObject.GetTime() << " milliseconds" << endl;

		Transposing transposingObject;
		transposingObject.SetSize(size);
		transposingObject.Transpose();
		cout << "\Transpose Matrix Time (20 x 20) = " << transposingObject.GetTime() << " milliseconds" << endl;

		glfwTerminate();
	}
};

int main() 
{
	Controller contoller;
	contoller.Compute();
	return 0;
}