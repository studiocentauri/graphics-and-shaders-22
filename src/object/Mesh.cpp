#include "object/Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> vertices_, std::vector<unsigned int> indices_, std::vector<Texture> textures_)
{
    vertices = vertices_;
    indices = indices_;
    textures = textures_;
    setup_mesh();
}

void Mesh::draw(Shader *shader)
{
    shader->use();
    unsigned int diffuseNR = 1;
    unsigned int specularNR = 1;

    set_active_texture(0);
    for (int i = 0; i < textures.size(); i++)
    {
        std::string number;
        if (textures[i].type == "diffuse")
        {
            number = std::to_string(diffuseNR++);
        }
        else if (textures[i].type == "specular")
        {
            number = std::to_string(specularNR++);
        }

        shader->set_texture("mat." + textures[i].type + number, &(textures[i]));
    }
    if (specularNR == 1)
    {
        shader->set_texture("mat.specular1", &(textures[0]));
    }
    set_active_texture(0);

    varray.draw_indices(indices.size());
}

void Mesh::free_data()
{
    varray.free_data();
}

void Mesh::setup_mesh()
{
    varray.generate_buffers();
    varray.bind_vao();
    varray.bind_vbo(vertices.size(), sizeof(Vertex), &(vertices[0]));
    varray.bind_ebo(indices.size(), &(indices[0]));
    varray.set_attribute_array(0, 3, sizeof(Vertex));
    varray.set_attribute_array(1, 3, sizeof(Vertex), (void *)(offsetof(Vertex, normal)));
    varray.set_attribute_array(2, 2, sizeof(Vertex), (void *)(offsetof(Vertex, uv)));
    varray.unbind_vbo();
    varray.unbind_vao();
}
