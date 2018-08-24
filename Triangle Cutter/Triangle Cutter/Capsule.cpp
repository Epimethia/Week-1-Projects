#include "Capsule.h"

Capsule::Capsule() {
	PointA = { -300.0f, -300.0f };
	PointB = { -300.0f, -300.0f };
	PointC = { -300.0f, -300.0f };
	radius = 0.0f;
}

void Capsule::Render(GLuint _Program) {
	//rendering the capsule
	glUseProgram(_Program);
	glBindVertexArray(VAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_LINE_LOOP, 0, 36);
	glBindVertexArray(0);
}

void Capsule::Init() {
	GenerateCapsule();

	//generating and binding the buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBindVertexArray(VAO);

	//Enabling the positional floats
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0
	);

	glEnableVertexAttribArray(0);

	//Enabling Color Floats
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Capsule::Update() {
	GenerateCapsule();

	//Generating and binding the buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBindVertexArray(VAO);

	//Enabling the positional floats
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0
	);

	glEnableVertexAttribArray(0);

	//Enabling Color Floats
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Capsule::GenerateCapsule() {

	//getting the angle between the two points
	float AngleOffset = std::atan2f(
		PointB.y - PointA.y,
		PointB.x - PointA.x
	);

	//converting to deg (for the for loops)
	AngleOffset = ((AngleOffset * (180.0f / 3.1415f)) - 90.0f) / 10.0f;
	radius = glm::length(PointB - PointC);

	int CurrentIndex = 0;
	//DRAWS A SEMICIRCLE AROUND POINT A
	//Top circle
	for (float i = 18.1f + AngleOffset; i < 36.0f + AngleOffset; i++) {
		float angle = (i * 3.1415f / 180.0f) * 10.0f;
		float x = radius * std::cos(angle) + PointA.x;
		float y = radius * std::sin(angle) + PointA.y;

		verts[CurrentIndex++] = x;
		verts[CurrentIndex++] = y;
		verts[CurrentIndex++] = 0.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
	}

	//JUMPS TO THE NEXT POINT AND DRAWS THE REMAINING HALF
	//Bottom circle
	for (float i = 0.0f + AngleOffset; i < 18.0f + AngleOffset; i++) {
		float angle = (i * 3.1415f / 180.0f) * 10.0f;
		float x = radius * std::cos(angle) + PointB.x;
		float y = radius * std::sin(angle) + PointB.y;

		verts[CurrentIndex++] = x;
		verts[CurrentIndex++] = y;
		verts[CurrentIndex++] = 0.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
	}
}

void Capsule::Reset() {
	PointA = { -300.0f, -300.0f };
	PointB = { -300.0f, -300.0f };
	PointC = { -300.0f, -300.0f };
	radius = 0.0f;
}