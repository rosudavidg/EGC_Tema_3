#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::GenerateRoadMatrix() {
	// Fill road_matrix with 0 (not road)
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			road_matrix[i][j] = 0;
		}
	}

	int no = 8 + std::rand() % ((10 + 1) - 4);

	int selected_x[30];
	int selected_y[30];

	for (int i = 0; i < 30; i++) {
		selected_x[i] = 0;
		selected_y[i] = 0;
	}

	for (int i = 0; i < no; i++) {
		int x = 0 + std::rand() % ((28 + 1) - 0);

		while (selected_x[x] == 1) {
			x = 0 + std::rand() % ((28 + 1) - 0);
		}

		selected_x[x] = 1;
	}

	no = 8 + std::rand() % ((10 + 1) - 4);
	for (int i = 0; i < no; i++) {
		int y = 0 + std::rand() % ((28 + 1) - 0);

		while (selected_y[y] == 1) {
			y = 0 + std::rand() % ((28 + 1) - 0);
		}

		selected_y[y] = 1;
	}

	for (int i = 0; i < 30 - 4; i++) {
		if (selected_x[i] == 1) {
			for (int j = 1; j < 5; j++) {
				selected_x[i + j] = 0;
			}
		}
	}
	for (int i = 0; i < 30 - 4; i++) {
		if (selected_y[i] == 1) {
			for (int j = 1; j < 5; j++) {
				selected_y[i + j] = 0;
			}
		}
	}

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (selected_x[i] == 1 && selected_y[j] == 1) {
				road_matrix[i][j] = 3;
			}
		}
	}

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (road_matrix[i][j] == 3) {
				if (i != 0) {
					road_matrix[i - 1][j] = 5;
				}
				if (i != 29) {
					road_matrix[i + 1][j] = 5;
				}
				if (j != 0) {
					road_matrix[i][j - 1] = 2;
				}
				if (j != 29) {
					road_matrix[i][j + 1] = 2;
				}
			}
		}
	}

	for (int i = 0; i < 30; i++) {
		if (selected_x[i] == 1) {
			for (int j = 0; j < 30; j++) {
				if (road_matrix[i][j] == 0) {
					road_matrix[i][j] = 4;
				}
			}
		}
	}

	for (int i = 0; i < 30; i++) {
		if (selected_y[i] == 1) {
			for (int j = 0; j < 30; j++) {
				if (road_matrix[j][i] == 0) {
					road_matrix[j][i] = 1;
				}
			}
		}
	}

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (road_matrix[i][j] == 0) {
				road_matrix[i][j] = 6 + std::rand() % ((10 + 1) - 6);
			}
		}
	}
}

void Tema3::GenerateBuildings() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			buildings[i][j][0] = 1 + std::rand() % ((8 + 1) - 1);
			buildings[i][j][1] = 1 + std::rand() % ((8 + 1) - 1);
			buildings[i][j][2] = 1 + std::rand() % ((8 + 1) - 1);

			buildings[i][j][3] = 1 + std::rand() % ((8 + 1) - 1);
			buildings[i][j][4] = 1 + std::rand() % ((8 + 1) - 1);
			buildings[i][j][5] = 1 + std::rand() % ((8 + 1) - 1);

			buildings[i][j][6] = 1 + std::rand() % ((3 + 1) - 1);
		}
	}
}

void Tema3::Init()
{
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "simple_road.png").c_str(), GL_REPEAT);
		mapTextures["simple_road"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pass_road.png").c_str(), GL_REPEAT);
		mapTextures["pass_road"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "parkinglot_2.jpg").c_str(), GL_REPEAT);
		mapTextures["parkinglot"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "crossing_road.png").c_str(), GL_REPEAT);
		mapTextures["crossing_road"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass.jpg").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "ground.jpg").c_str(), GL_REPEAT);
		mapTextures["ground"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pool.jpg").c_str(), GL_REPEAT);
		mapTextures["pool"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "glass_1.jpg").c_str(), GL_REPEAT);
		mapTextures["glass_1"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "glass_2.jpg").c_str(), GL_REPEAT);
		mapTextures["glass_2"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "glass_3.jpg").c_str(), GL_REPEAT);
		mapTextures["glass_3"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "crate.jpg").c_str(), GL_REPEAT);
		mapTextures["crate"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "earth.png").c_str(), GL_REPEAT);
		mapTextures["earth"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Table/garden_table.png", GL_REPEAT);
		mapTextures["table"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Lambo/lambo.jpeg", GL_REPEAT);
		mapTextures["lambo"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Girl/girl.jpg", GL_REPEAT);
		mapTextures["girl"] = texture;
	}

	{
		mapTextures["random"] = CreateRandomTexture(25, 25);
	}


	// Load meshes
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("table");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Table/", "garden_table.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("lambo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Lambo/", "lambo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("girl");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Girl/", "girl.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	// Create a simple quad
	{
		vector<glm::vec3> vertices
		{
			// x y z
			glm::vec3(1.0f, 0.0f, 1.0f),	// Top Right
			glm::vec3(1.0f, 0.0f, 0.0f),	// Bottom Right
			glm::vec3(0.0f, 0.0f, 0.0f),	// Bottom Left
			glm::vec3(0.0f, 0.0f, 1.0f),	// Top Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderTema3");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	GenerateRoadMatrix();
	GenerateBuildings();
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Tema3::AddTable(float x, float z) {
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0, z));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderSimpleMesh(meshes["table"], shaders["ShaderTema3"], modelMatrix, mapTextures["table"]);
	}
}

void Tema3::AddBuilding(int i, int j) {

	for (int k = 0; k < 3; k++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.5, (float)buildings[i][j][k] / 2, j + 0.5));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
		modelMatrix *= Transform3D::Scale((float) buildings[i][j][k + 3] / 8, buildings[i][j][k], (float)buildings[i][j][k + 3] / 8);

		if (buildings[i][j][6] == 1) {
			RenderSimpleMesh(meshes["box"], shaders["ShaderTema3"], modelMatrix, mapTextures["glass_1"]);
		}
		else if (buildings[i][j][6] == 2) {
			RenderSimpleMesh(meshes["box"], shaders["ShaderTema3"], modelMatrix, mapTextures["glass_2"]);
		}
		else if (buildings[i][j][6] == 3) {
			RenderSimpleMesh(meshes["box"], shaders["ShaderTema3"], modelMatrix, mapTextures["glass_3"]);
		}
	}
}

void Tema3::AddWater() {
	for (int i = 0; i < 30; i++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, -1));
			RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, 30));
			RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
		}
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.0f, -1));
		RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.0f, 30));
		RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(30, 0.0f, -1));
		RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(30, 0.0f, 30));
		RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
	}
}

void Tema3::Update(float deltaTimeSeconds)
{
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (road_matrix[i][j] == 3) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, j));
				RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["crossing_road"]);
			}
			else if (road_matrix[i][j] == 2) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, j));
				RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pass_road"]);
			}
			else if (road_matrix[i][j] == 5) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, j));
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.0f, 0.5f));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
				modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, 0.0f, -0.5f));
				RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pass_road"]);
			}
			else if (road_matrix[i][j] == 4) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, j));
				RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["simple_road"]);
			}
			else if (road_matrix[i][j] == 1) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, j));
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.0f, 0.5f));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
				modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, 0.0f, -0.5f));
				RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["simple_road"]);
			}
			else if (road_matrix[i][j] == 6) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, j));
				RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

				AddTable(i + 0.3f, j + 0.2);
				AddTable(i + 0.6f, j + 0.2);

			}
			else if (road_matrix[i][j] > 6 && road_matrix[i][j] <= 10) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.0f, j));
				RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["crossing_road"]);

				AddBuilding(i, j);
			}

		}
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.2f, 0, 5.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.001));
		RenderSimpleMesh(meshes["lambo"], shaders["ShaderTema3"], modelMatrix, mapTextures["lambo"]);
	}

	for (int j = 0; j < 30; j++) {
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.0f, j));
			RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(30, 0.0f, j));
			RenderSimpleMesh(meshes["square"], shaders["ShaderTema3"], modelMatrix, mapTextures["pool"]);
		}
	}

	AddWater();


}

void Tema3::FrameEnd()
{
	DrawCoordinatSystem();
}

void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		//TODO : activate texture location 0
		//TODO : Bind the texture1 ID
		//TODO : Send texture uniform value
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}


	if (texture2)
	{
		//TODO : activate texture location 1
		//TODO : Bind the texture2 ID
		//TODO : Send texture uniform value
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
	GLuint textureID = 0;
	unsigned int channels = 3;
	unsigned int size = width * height * channels;
	unsigned char* data = new unsigned char[size];

	// TODO: generate random texture data
	for (int i = 0; i < size; i++) {
		data[i] = rand() % 256;
	}

	// Generate and bind the new texture ID
	unsigned int gl_texture_object;
	glGenTextures(1, &gl_texture_object);
	glBindTexture(GL_TEXTURE_2D, gl_texture_object);
	// TODO: Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	CheckOpenGLError();

	// TODO: Use glTextImage2D to set the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// TODO: Generate texture mip-maps
	glGenerateMipmap(GL_TEXTURE_2D);

	CheckOpenGLError();

	// Save the texture into a wrapper Texture2D class for using easier later during rendering phase
	Texture2D* texture = new Texture2D();
	texture->Init(textureID, width, height, channels);

	SAFE_FREE_ARRAY(data);
	return texture;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
