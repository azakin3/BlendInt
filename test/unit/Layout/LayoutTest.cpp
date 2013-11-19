// cpp

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <stdio.h>

#include "LayoutTest.h"

#include <BlendInt/Interface.hpp>
#include <BlendInt/Label.hpp>
#include <BlendInt/Button.hpp>
#include <BlendInt/FontConfig.hpp>
#include <BlendInt/Rect.hpp>
#include <BlendInt/HorizontalLayout.hpp>
#include <BlendInt/VerticalLayout.hpp>
#include <BlendInt/Types.hpp>

using namespace BlendInt;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(LayoutTest);

LayoutTest::LayoutTest ()
{

}

LayoutTest::~LayoutTest ()
{

}

void LayoutTest::setUp ()
{
#ifdef DEBUG
	int mapsize = AbstractWidget::map_size();

	if(mapsize > 0) {
		map<uint64_t, AbstractWidget*>::const_iterator it;
    for (it = AbstractWidget::get_map().begin(); it != AbstractWidget::get_map().end(); it++)
		{
			cout << "id: " << it->first << " was not deleted!" << endl;
		}
	}

	CPPUNIT_ASSERT(mapsize == 0);
#endif
}

void LayoutTest::tearDown ()
{
#ifdef DEBUG
	int mapsize = AbstractWidget::map_size();

	if(mapsize > 0) {
		map<uint64_t, AbstractWidget*>::const_iterator it;
		for (it = AbstractWidget::get_map().begin(); it != AbstractWidget::get_map().end(); it++)
		{
			cout << "id: " << it->first << " was not deleted!" << endl;
		}
	}

	CPPUNIT_ASSERT(mapsize == 0);
#endif
}

void LayoutTest::horizontal_layout1()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	glfwSetErrorCallback(&cbError);

	GLFWwindow* window = glfwCreateWindow(1200, 800, __func__, NULL, NULL);
	if (!window) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	glfwSetWindowSizeCallback(window, &cbWindowSize);
	glfwSetKeyCallback(window, &cbKey);
	glfwSetMouseButtonCallback(window, &cbMouseButton);
	glfwSetCursorPosCallback(window, &cbCursorPos);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* initialize BlendInt after OpenGL content is created */
	if (!Interface::initialize()) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	Interface* app = Interface::instance();
	app->Resize(1200, 800);

	HorizontalLayout layout1;
	layout1.SetPosition(100, 100);
	layout1.set_alignment(BlendInt::AlignHorizontalCenter);

	Label label1(L"Hello");
	label1.SetPosition(100, 100);

	Button button1(L"Sample Button");
	button1.SetPosition(200, 200);

	layout1.add(&label1);
	layout1.add(&button1);

	HorizontalLayout layout2;
	layout2.SetPosition(300, 200);
	layout2.set_alignment(BlendInt::AlignTop);

	Label label2(L"Hello");
	label2.SetPosition(100, 100);

	Button button2(L"Sample Button");
	button2.SetPosition(200, 200);

	layout2.add(&label2);
	layout2.add(&button2);

	HorizontalLayout layout3;
	layout3.SetPosition(500, 300);
	layout3.set_alignment(BlendInt::AlignBottom);

	Label label3(L"Hello");
	label3.SetPosition(100, 100);

	Button button3(L"Sample Button");
	button3.SetPosition(200, 200);

	layout3.add(&label3);
	layout3.add(&button3);

	app->bind(&layout1);
	app->bind(&layout2);
	app->bind(&layout3);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		app->Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	layout1.unbind();
	layout2.unbind();
	layout3.unbind();

	/* release BlendInt */
	Interface::release();

	glfwTerminate();
	CPPUNIT_ASSERT(true);
}

void LayoutTest::vertical_layout1()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	glfwSetErrorCallback(&cbError);

	GLFWwindow* window = glfwCreateWindow(1200, 800, __func__, NULL, NULL);
	if (!window) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	glfwSetWindowSizeCallback(window, &cbWindowSize);
	glfwSetKeyCallback(window, &cbKey);
	glfwSetMouseButtonCallback(window, &cbMouseButton);
	glfwSetCursorPosCallback(window, &cbCursorPos);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* initialize BlendInt after OpenGL content is created */
	if (!Interface::initialize()) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	Interface* app = Interface::instance();
	app->Resize(1200, 800);

	VerticalLayout layout1;
	layout1.SetPosition(100, 100);
	layout1.set_alignment(BlendInt::AlignVerticalCenter);

	Label label1(L"Hello");
	label1.SetPosition(100, 100);

	Button button1(L"Sample Button");
	button1.SetPosition(200, 200);

	layout1.add(&label1);
	layout1.add(&button1);

	VerticalLayout layout2;
	layout2.SetPosition(250, 100);
	layout2.set_alignment(BlendInt::AlignLeft);

	Label label2(L"Hello");
	label2.SetPosition(100, 100);

	Button button2(L"Sample Button");
	button2.SetPosition(200, 200);

	layout2.add(&label2);
	layout2.add(&button2);

	VerticalLayout layout3;
	layout3.SetPosition(500, 100);
	layout3.set_alignment(BlendInt::AlignRight);

	Label label3(L"Hello");
	label3.SetPosition(100, 100);

	Button button3(L"Sample Button");
	button3.SetPosition(200, 200);

	layout3.add(&label3);
	layout3.add(&button3);

	app->bind(&layout1);
	app->bind(&layout2);
	app->bind(&layout3);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		app->Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	layout1.unbind();
	layout2.unbind();
	layout3.unbind();

	/* release BlendInt */
	Interface::release();

	glfwTerminate();
	CPPUNIT_ASSERT(true);
}

void LayoutTest::layout_mix1()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	glfwSetErrorCallback(&cbError);

	GLFWwindow* window = glfwCreateWindow(1200, 800, __func__, NULL, NULL);
	if (!window) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	glfwSetWindowSizeCallback(window, &cbWindowSize);
	glfwSetKeyCallback(window, &cbKey);
	glfwSetMouseButtonCallback(window, &cbMouseButton);
	glfwSetCursorPosCallback(window, &cbCursorPos);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* initialize BlendInt after OpenGL content is created */
	if (!Interface::initialize()) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	Interface* app = Interface::instance();
	app->Resize(1200, 800);

	VerticalLayout* layout1 = new VerticalLayout;
	layout1->SetPosition(100, 100);
	layout1->set_alignment(BlendInt::AlignVerticalCenter);

	Label* label1 = new Label(L"la1");
	label1->SetPosition(100, 100);

	Button* button1 = new Button(L"Button1");
	button1->SetPosition(200, 200);

	layout1->add(label1);
	layout1->add(button1);

	HorizontalLayout* layout2 = new HorizontalLayout;

	Label* label2 = new Label(L"Hello Blender");
	label2->SetPosition(500, 500);

	Button* button2 = new Button(L"Sample Button");
	button2->SetPosition(200, 200);

	layout2->add(label2);
	layout2->add(layout1);
	layout2->add(button2);

	layout2->SetPosition (400, 500);

	app->bind(layout2);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		app->Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	//delete layout2;
	/* release BlendInt */
	Interface::release();

	glfwTerminate();

	CPPUNIT_ASSERT(true);
}

void LayoutTest::layout_mix2()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	glfwSetErrorCallback(&cbError);

	GLFWwindow* window = glfwCreateWindow(1200, 800, __func__, NULL, NULL);
	if (!window) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	glfwSetWindowSizeCallback(window, &cbWindowSize);
	glfwSetKeyCallback(window, &cbKey);
	glfwSetMouseButtonCallback(window, &cbMouseButton);
	glfwSetCursorPosCallback(window, &cbCursorPos);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* initialize BlendInt after OpenGL content is created */
	if (!Interface::initialize()) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	Interface* app = Interface::instance();
	app->Resize(1200, 800);

	VerticalLayout layout1;
	layout1.SetPosition(100, 100);
	layout1.set_alignment(BlendInt::AlignVerticalCenter);

	Label label1(L"Hello");
	label1.SetPosition(100, 100);

	Button button1(L"Sample Button");
	button1.SetPosition(200, 200);

	layout1.add(&label1);
	layout1.add(&button1);

	VerticalLayout layout2;
	layout2.SetPosition(250, 100);
	layout2.set_alignment(BlendInt::AlignLeft);

	Label label2(L"Hello");
	label2.SetPosition(100, 100);

	Button button2(L"Sample Button");
	button2.SetPosition(200, 200);

	layout2.add(&label2);
	layout2.add(&button2);

	VerticalLayout layout3;
	layout3.SetPosition(500, 100);
	layout3.set_alignment(BlendInt::AlignRight);

	Label label3(L"Hello");
	label3.SetPosition(100, 100);

	Button button3(L"Sample Button");
	button3.SetPosition(200, 200);

	layout3.add(&label3);
	layout3.add(&button3);

	HorizontalLayout layout4;
	Button button4(L"Button4");

	layout4.add(&button4);
	layout4.add(&layout1);
	layout4.add(&layout2);
	layout4.add(&layout3);
	layout4.SetPosition(400, 200);

	app->bind(&layout4);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		app->Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	layout4.unbind();
	layout3.unbind();
	layout2.unbind();
	layout1.unbind();

	/* release BlendInt */
	Interface::release();

	glfwTerminate();
	CPPUNIT_ASSERT(true);
}

void LayoutTest::cbError (int error, const char* description)
{
	std::cerr << "Error: " << description
			<< " (error code: " << error << ")"
			<< std::endl;
}

void LayoutTest::cbWindowSize (GLFWwindow* window, int w, int h)
{
	BlendInt::Interface::instance()->resizeEvent(w, h);
}

void LayoutTest::cbKey (GLFWwindow* window, int key, int scancode, int action,
        int mods)
{
	BlendInt::Interface::instance()->keyEvent(key, scancode, action, mods);
}

void LayoutTest::cbMouseButton (GLFWwindow* window, int button, int action,
        int mods)
{
	BlendInt::Interface::instance()->mouseButtonEvent(button, action, mods);
}

void LayoutTest::cbCursorPos (GLFWwindow* window, double xpos, double ypos)
{
	BlendInt::Interface::instance()->cursorPosEvent(xpos, ypos);
}

