#include <string>
#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Util.h"
#include "BreakAll.h"
#include "GameScreen.h"

namespace BreakAll {

// ============================================== //
// ============================================== //

/* Annonymous namespace to hold data */
namespace {

	// Things used in the game loop
	const int kTicksPerSecond = 50;
	const sf::Time kTickDuration = sf::seconds(1.0 / kTicksPerSecond);
	const int kMaxFrameSkip = 10;

	// Window and its properties
	sf::Window window;
	int resWidth = 1024;
	int resHeight = 768;
	std::string windowTitle = "BreakAll 0.2";

	// Game internal clock
	sf::Clock clock;

	// Current Game State
	GameScreen* currentScreen = 0;
	bool isRunning = false;

	// OpenGL GLSL Program and sources
	const char* vertexShaderSource = "simple.v.glsl";
	const char* fragmentShaderSource = "simple.f.glsl";
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLint modelViewProjection;
	GLint colorFact;
};

// ============================================== //
// ============================================== //

/**
 * Set up the OpenGL stuff (shaders, atributes, etc)
 */
void SetOpenGL() {

	// Print some version stuff
	std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Using OpenGL " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Using GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION)
		<< std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	// Load and compile the shaders
	vertexShader = CreateShader(vertexShaderSource, GL_VERTEX_SHADER);
	fragmentShader = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	if (vertexShader + fragmentShader == 0)  {
		PrintLog(vertexShader);
		PrintLog(fragmentShader);
		throw OpenGLError;
	}

	// Link the Program
	GLint link_ok = GL_FALSE;
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		std::cerr << "glLinkProgram: " << std::endl;
		PrintLog(program);
		throw OpenGLError;
	}

	// Get the Uniform location
	modelViewProjection = glGetUniformLocation(program, "mvp");
	if (modelViewProjection == -1) {
		std::cerr << "glGetUniformLocation: " << std::endl;
		PrintLog(program);
		throw OpenGLError;
	}

	// Get the Uniform location
	colorFact = glGetUniformLocation(program, "colorFact");
	if (colorFact == -1) {
		std::cerr << "glGetUniformLocation: " << std::endl;
		PrintLog(program);
		throw OpenGLError;
	}

	// Start using the program
	glUseProgram(program);

	// Set the color to clear the buffers
	glClearColor(0.8, 1.0, 0.5, 1.0);

	// Enable alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable Depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable Polygon Offset to draw better lines
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);
}

// ============================================== //

/**
 * Initialize the game, set up the context, read configs and do
 * anything needed before the game starts to run.
 * TODO: Load Configs
 */
void Initialize() {

	// Initialize GLEW and check for OpenGL 4.0 support
	if ((glewInit() != GLEW_OK) || (!GLEW_VERSION_4_0)) {
		throw GLEWError;
	}

	// Reset the clock
	clock.restart();

	// Create the windows (and the underlying GL Context)
	window.create(
		sf::VideoMode(resWidth, resHeight),
		windowTitle,
		sf::Style::Close | sf::Style::Resize
	);

	// Set some OpenGL stuff up!
	SetOpenGL();

	// Set up the initial game state
	currentScreen = new GameScreen(resWidth, resHeight);

}

// ============================================== //

/**
 * Handle the events (user inputs, window events, etc)
 */
void HandleEvents() {
	// Poll and dispatch the events
	sf::Event event;
	while ( window.pollEvent(event) ) {
		if (event.type == sf::Event::Closed)
		{
			// Stop when the window is closed
			isRunning = false;
		}
		else if (event.type == sf::Event::Resized)
		{
			// Adjust the viewport when the window is resized
			resWidth = event.size.width;
			resHeight = event.size.height;
			glViewport(0, 0, resWidth, resHeight);
		}
		// TODO: Create a proper Key Handler
		else if (event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Q ||
			   event.key.code == sf::Keyboard::Escape) {

				isRunning = false;
			}
		}
		// TODO: Dispatch the events to the client classes
	}
}

// ============================================== //

/**
 * Perform a game step
 */
void Step() {
	if (currentScreen) currentScreen->step();
}

// ============================================== //

/**
 * Draw the game
 */
void Draw() {

	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the screen
	if (currentScreen) currentScreen->draw();

	// Display what was drawn on the window
	window.display();
}

// ============================================== //

/**
 * Run the game. The game loop is inside here.
 */
void Run() {

	// Define some important control variables
	sf::Time elapsed = sf::milliseconds(0);
	int skippedFrames = 0;

	// Restart the clock
	clock.restart();

	// This is the main loop
	isRunning = true;
	while( isRunning ) {

		// Reset the clock, the frame skip count and
		// sum the elapsed time
		skippedFrames = 0;
		elapsed += clock.restart();

		// If enough time has passed we should update the game state, unless
		// we have skipped more frames than the limit, in which case we skip
		// the update and draw
		while( elapsed > kTickDuration &&
			   skippedFrames < kMaxFrameSkip)
		{
			// Handle events, update the game, count the (possibly) skipped
			// frame and adjust the time elapsed to account for the current
			// tick, trying to keep a constant game update rate
			HandleEvents();
			Step();
			elapsed -= kTickDuration;
			skippedFrames++;
		}

		// Draw a new frame with the current game state
		Draw();

		// Super trick to avoid waisting so much CPU time
		// Of course, this limit our FPS (max=980 FPS)
		// since we must sleep for one milisecond
		// In practice it doesn't hurt that much.
		sf::sleep(sf::milliseconds(2));
	}
}

// ============================================== //

/**
 * After the game has stopped, clean up what is needed and
 * terminate the game.
 */
void Terminate() {
	// TODO: Save any config needed

	// Make sure we are not running
	if (isRunning) isRunning = false;

	// Delete and free OpenGL stuff
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Close the window
	if (window.isOpen()) window.close();
}

// ============================================== //

/**
 * Set the Model View Projection matrix on the shader
 */
void SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	//glm::mat4 MVP = model * view * projection;
	glm::mat4 MVP = projection * view * model;
	glUniformMatrix4fv(modelViewProjection, 1, GL_FALSE, &MVP[0][0]);
}

// ============================================== //

void SetColorFact(float fact) {
	glUniform1f(colorFact, fact);
}

// ============================================== //

} /* BreakAll */

