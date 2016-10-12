#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <algorithm>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#include <iostream>

#include <string>





////Solution 1

//template<class TA>

//void print(const TA& i)

//{

//	std::cout << i << std::endl;

//}

//

//int main()

//{

//	print(1);

//	print(2.345f);

//	print("Hello World");

//

//	return 0;

//}



//Solution 2
//template<class TA>
//class vector2D
//{
//public:
//
//	TA x_, y_;
//
//	vector2D(const TA& xinput, const TA& yinput)
//
//		: x_(xinput), y_(yinput)
//
//	{}
//
//
//
//	void print()
//
//	{
//
//		std::cout << x_ << " " << y_ << std::endl;
//
//	}
//
//};
//

//int main()
//{
//
//	vector2D<int> abc(1, 3);
//
//	abc.print();
//
//	return 0;
//}

const int width = 1200;   const int height = 1000;
double xPos, yPos;
float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		int lines = abs(i - i0);
		int lines2 = abs(j1 - j0);
		int lines3 = abs(i1 - i0);
		const int j = (j1 - j0)*lines / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}



class Box // NO PARENT
{
public:
	int x = 100;
	int y = 100;
	int height = 100;
	int width = 100;
	void draw()
	{
		for (int a = 0; a <= width; a++)
		{
			drawPixel(x + a, y, 255, 0, 0);
			drawPixel(x + a, y - height, 255, 0, 0);

		}
		for (int a = 0; a <= height; a++)
		{
			drawPixel(x, y - a, 255, 0, 0);
			drawPixel(x + width, y - a, 255, 0, 0);
		}
	}
};

class Circle // NO PARENT
{
public:
	int x = 300;
	int y = 300;
	int r = 70;
	void draw()
	{
		for (int a = 0; a <= 2 * r; a++)
		{
			for (int b = 0; b <= 2 * r; b++)
			{
				int f = (r - b)*(r - b) + (r - a)*(r - a) - r*r;

				if (f < 0 && -1000 < f)
				{

					drawPixel(x - r + b, y - r + a, 0, 0, 255);



				}


			}
		}
	}
};

class bigmom
{
public:
	virtual void draw() = 0;
};

template <class TB>
class GeometricObjectInterface : public bigmom
{
public:
	void draw()
	{
		TB oper;
		oper.draw();
	}

};


int main(void)
{
	std::vector<bigmom*> obj_list;
	obj_list.push_back(new GeometricObjectInterface<Box>);
	obj_list.push_back(new GeometricObjectInterface<Circle>);
	
	return 0;


	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "2016112129 Taegun", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetCursorPos(window, &xPos, &yPos);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		std::fill_n(pixels, width*height * 3, 1.0f);

		for (auto itr : obj_list)
		{
			itr->draw();
		}

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	
	delete[] pixels;
	glfwTerminate();
	return 0;
}

