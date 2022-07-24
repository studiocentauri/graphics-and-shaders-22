#ifndef MESH_H
#define MESH_H

// Third-party Headers
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Custom Headers
#include "rendering/Texture.h"
#include "rendering/Shader.h"
#include "rendering/Renderer.h"

// Standard Headers
#include <vector>

// Struct for storing vertices in the renderer
struct Vertex
{
    glm::vec3 position; // Position of vertex
    glm::vec3 normal;   // Normal vector of vertex
    glm::vec2 uv;       // UV coordinate of vertex
};

// Mesh class for storing and rendering vertex data
class Mesh
{
public:
    std::vector<Vertex> vertices;      // List of Vertex in Mesh
    std::vector<unsigned int> indices; // List of indices for the faces of the Mesh
    std::vector<Texture> textures;     // List of textures for the Mesh
    VertexArray varray;                // Vertex Array to draw the Mesh

    // Default Mesh Constructor
    Mesh();
    // Value constructor for Mesh
    Mesh(std::vector<Vertex> vertices_, std::vector<unsigned int> indices_, std::vector<Texture> textures_);
    // Draws a mesh using a Shader as input
    void draw(Shader *shader);
    // Frees mesh data
    void free_data();

private:
    // Sets up the vertex array for the mesh
    void setup_mesh();
};

#endif // !MESH_H
