#include "starfield.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVersionFunctionsFactory>

Starfield::Starfield()
	: timer(new QTimer(this))
	, elapsedTimer(new QElapsedTimer)
{
	connect(timer, &QTimer::timeout, this, &Starfield::onTimeout);

	timer->start();
	elapsedTimer->start();
}

Starfield::~Starfield()
{
	auto *f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>();

	// Make sure the context is current before deleting resources
	makeCurrent();

	delete vShader;
	delete fShader;
	delete program;
	f->glDeleteVertexArrays(1, &vao);
	f->glDeleteBuffers(1, &vbo);

	doneCurrent();

	delete elapsedTimer;
}

void Starfield::initializeGL()
{
	// Load shaders, initialize vertex data, etc.

	auto *f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>();

	vShader = new QOpenGLShader(QOpenGLShader::Vertex);
	vShader->compileSourceFile(":/shaders/vshader.glsl");

	fShader = new QOpenGLShader(QOpenGLShader::Fragment);
	fShader->compileSourceFile(":/shaders/fshader.glsl");

	program = new QOpenGLShaderProgram;
	program->addShader(vShader);
	program->addShader(fShader);
	program->link();
	program->bind();

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	f->glGenVertexArrays(1, &vao);
	f->glGenBuffers(1, &vbo);

	f->glBindVertexArray(vao);
	f->glBindBuffer(GL_ARRAY_BUFFER, vbo);

	f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	f->glEnableVertexAttribArray(0);
}

void Starfield::resizeGL(int w, int h)
{
	Q_UNUSED(w);
	Q_UNUSED(h);

	// Do nothing
}

void Starfield::paintGL()
{
	// Draw the scene

	auto *f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>();

	program->setUniformValue("iResolution", this->width(), this->height());

	GLfloat elapsed = elapsedTimer->elapsed();
	program->setUniformValue("iTime", elapsed / 1000);

	f->glBindVertexArray(vao);
	f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

// SLOTS

void Starfield::onTimeout()
{
	update();
}
