#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

//----------------------nk-------------------------
//Here we define everything needed to set up the library with glfw.
//Note that nuklear_glfw_gl3.h should be included after nuklear.h. 
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include <nuklear\nuklear.h>
#include <nuklear\demo\glfw_opengl3\nuklear_glfw_gl3.h>
//----------------------------------------------------

int main() {
	int width, height;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 800, "Graph", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		printf("failed creating window");
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("failed initializing glad");
		return -1;
	}

	//-------------------------nk-------------------------------
	//Here we set up the context for nuklear which contains info about the styles, fonts etc about the GUI 
	//We also set up the font here
	struct nk_context* context = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
	//set up font
	struct nk_font_atlas* atlas;
	nk_glfw3_font_stash_begin(&atlas);
	nk_glfw3_font_stash_end();
	//----------------------------------------------------------

	while (!glfwWindowShouldClose(window)) {
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glfwPollEvents();

		//--------------------------nk------------------------------
		nk_glfw3_new_frame(); // create a new frame for every iteration of the loop

							  //here we set up the nk_window
		if (nk_begin(context, "Nuklear Window", nk_rect(0, 0, 500, 500),
			NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE)) {

			nk_end(context);
		}
		//------------------------------------------------------------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//-------------------------nk------------------------------------
		//don't forget to draw your window!
		nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		//---------------------------------------------------------------
		glfwSwapBuffers(window);

	}
	//-------------------------nk------------------------------------
	nk_glfw3_shutdown();
	//-------------------------------------------------------------
	glfwTerminate();

	return 0;
}