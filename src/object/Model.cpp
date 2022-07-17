#include "object/Model.h"

Model::Model()
{
}

Model::Model(std::string path, bool gamma_)
{
    gamma = gamma_;
    load_model(path);
}

void Model::draw(Shader *shader)
{
    for (int i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader);
    }
}

void Model::free_data()
{
    for (int i = 0; i < meshes.size(); i++)
    {
        meshes[i].free_data();
    }
}

void Model::load_model(std::string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Error::Assimp::" << importer.GetErrorString() << std::endl;
        return;
    }

    dir = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode *node, const aiScene *scene)
{
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vt;

        vt.position.x = mesh->mVertices[i].x;
        vt.position.y = mesh->mVertices[i].y;
        vt.position.z = mesh->mVertices[i].z;

        if (mesh->HasNormals())
        {
            vt.normal.x = mesh->mNormals[i].x;
            vt.normal.y = mesh->mNormals[i].y;
            vt.normal.z = mesh->mNormals[i].z;
        }

        if (mesh->mTextureCoords[0])
        {
            vt.uv.x = mesh->mTextureCoords[0][i].x;
            vt.uv.y = mesh->mTextureCoords[0][i].y;
        }

        vertices.push_back(vt);
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffusemaps = load_material_textures(mat, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffusemaps.begin(), diffusemaps.end());

        std::vector<Texture> specularmaps = load_material_textures(mat, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularmaps.begin(), specularmaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::load_material_textures(aiMaterial *mat, aiTextureType type, std::string textureType)
{
    std::vector<Texture> texs;

    for (int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString strs;
        mat->GetTexture(type, i, &strs);

        bool skip = false;

        for (int j = 0; j < textures.size(); j++)
        {
            if (std::strcmp(strs.C_Str(), textures[j].path.c_str()) == 0)
            {
                skip = true;
                texs.push_back(textures[j]);
                break;
            }
        }
        if (!skip)
        {
            std::string filePath = std::string(strs.C_Str());
            filePath = dir + "/" + filePath;
            Texture tex(filePath, ((gamma && (textureType == "diffuse")) ? (true) : (false)));
            tex.type = textureType;
            tex.path = std::string(strs.C_Str());
            textures.push_back(tex);
            texs.push_back(tex);
        }
    }

    return texs;
}
