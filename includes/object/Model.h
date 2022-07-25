#ifndef MODEL_H
#define MODEL_H

// Third-party Headers
#include "glad/glad.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Custom Headers
#include "object/Mesh.h"
#include "rendering/Texture.h"
#include "rendering/Shader.h"

// Standard Headers
#include <vector>

// Model class for storing Meshes and textures of a 3D Model file
class Model
{
public:
    std::vector<Mesh> meshes;      // List of meshes in a model
    std::vector<Texture> textures; // List of textures in a model
    std::string dir;               // Directory of model file
    bool gamma;                    // Whether to correct gamma of textures
    // Default Model constructor
    Model();
    // Path constructor for Model
    Model(std::string path, bool gamma_ = false);
    // Draw function to draw a model using a Shader
    void draw(Shader *shader);
    // Frees the data in the model
    void free_data();

private:
    // Loads the model file and starts loading process
    void load_model(std::string path);
    // Loads the meshes in the model recursively starting from the root node
    void process_node(aiNode *node, const aiScene *scene);
    // Process a Mesh present in Node into the Mesh Class
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    // Loads all the textures in a given Material based on its type
    std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string textureType);
};

#endif // !MODEL_H
