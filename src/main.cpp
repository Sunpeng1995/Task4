#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "Utils.h"

const int screen_width = 1280;
const int screen_height = 720;

GLuint CreateCube();
GLuint CreateCubeWithTangent();

int main() {
    // Init window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window
    auto window = glfwCreateWindow(screen_width, screen_height, "OpenGL", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to Create OpenGL Context" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    // Specify the view size
    glViewport(0, 0, screen_width, screen_height);

    GLuint cube_VAO = CreateCube();
    GLuint cube_with_tangent_VAO = CreateCubeWithTangent();

    GLuint cube_diffuse_texture = LoadTextureFromFile("res/texture/cube_diffuse.jpg");
    GLuint cube_normal_texture = LoadTextureFromFile("res/texture/cube_normal.jpg");

    Shader normalmap_shader("res/shader/normal.vs", "res/shader/normal.fs");
    Shader normalmap_shader_in_tangent("res/shader/normal_tangent.vs", "res/shader/normal_tangent.fs");
    Camera camera(screen_width, screen_height);

    Model bunny("res/models/bunny/bunny.obj");
    Shader bunny_shader("res/shader/bunny.vs", "res/shader/bunny.fs");

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the cube with normal map
        normalmap_shader.use();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0, 0));
        model = glm::scale(model, glm::vec3(0.5f));
        model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.5f, 1.0f, 0.0f));
        normalmap_shader.setMat4("model", model);
        normalmap_shader.setMat4("view", camera.GetViewMatrix());
        normalmap_shader.setMat4("projection", camera.GetProjectionMatrix());
        normalmap_shader.setVec3("view_position", camera.GetPosition());

        normalmap_shader.setVec3("light_direction", glm::vec3(-0.3f, 0.0f, -1.0f));
        normalmap_shader.setVec3("light_ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        normalmap_shader.setVec3("light_diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        normalmap_shader.setVec3("light_specular", glm::vec3(1.0f, 1.0f, 1.0f));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cube_diffuse_texture);
        normalmap_shader.setInt("texture_material", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, cube_normal_texture);
        normalmap_shader.setInt("texture_normal", 1);

        glBindVertexArray(cube_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        // Draw the cube with normal map in tangent space
        normalmap_shader_in_tangent.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0, 0));
        model = glm::scale(model, glm::vec3(0.5f));
        model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.5f, 1.0f, 0.0f));
        normalmap_shader_in_tangent.setMat4("model", model);
        normalmap_shader_in_tangent.setMat4("view", camera.GetViewMatrix());
        normalmap_shader_in_tangent.setMat4("projection", camera.GetProjectionMatrix());
        normalmap_shader_in_tangent.setVec3("view_position", camera.GetPosition());

        normalmap_shader_in_tangent.setVec3("light_direction", glm::vec3(-0.3f, 0.0f, -1.0f));
        normalmap_shader_in_tangent.setVec3("light_ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        normalmap_shader_in_tangent.setVec3("light_diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        normalmap_shader_in_tangent.setVec3("light_specular", glm::vec3(1.0f, 1.0f, 1.0f));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cube_diffuse_texture);
        normalmap_shader_in_tangent.setInt("texture_material", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, cube_normal_texture);
        normalmap_shader_in_tangent.setInt("texture_normal", 1);

        glBindVertexArray(cube_with_tangent_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        bunny_shader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        //model = glm::rotate(model, (float)glfwGetTime() * 0.3f, glm::vec3(0.0f, 1.0f, 0.0f));
        bunny_shader.setMat4("model", model);
        bunny_shader.setMat4("view", camera.GetViewMatrix());
        bunny_shader.setMat4("projection", camera.GetProjectionMatrix());
        bunny_shader.setVec3("view_position", camera.GetPosition());

        bunny_shader.setVec3("light_direction", glm::vec3(0.3f, 0.0f, -1.0f));
        bunny_shader.setVec3("light_ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        bunny_shader.setVec3("light_diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        bunny_shader.setVec3("light_specular", glm::vec3(1.0f, 1.0f, 1.0f));

        bunny.draw(&bunny_shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLuint CreateCube() {
    // Create and bind the VAO&VBO of a cube
    GLuint vertex_array_object; // == VAO
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    GLuint vertex_buffer_object; // == VBO
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    // Transfer the vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind the VAO&VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vertex_array_object;
}

GLuint CreateCubeWithTangent() {
    // Create and bind the VAO&VBO of a cube
    GLuint vertex_array_object; // == VAO
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    GLuint vertex_buffer_object; // == VBO
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    // Transfer the vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_with_tangent), vertices_with_tangent, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    // Unbind the VAO&VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vertex_array_object;
}