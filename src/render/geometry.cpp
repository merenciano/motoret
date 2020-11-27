#include "render/geometry.h"

namespace leep
{
    Geometry::Geometry()
    {

    }

    Geometry::Geometry(const Geometry &other)
    {
        vertex_buffer_ = other.vertex_buffer_;
        index_buffer_ = other.index_buffer_;
    }

    Geometry::~Geometry()
    {

    }

    Geometry& Geometry::operator=(const Geometry &other)
    {
        vertex_buffer_ = other.vertex_buffer_;
        index_buffer_ = other.index_buffer_;
        return *this;
    }

    Buffer Geometry::vertex_buffer() const
    {
        return vertex_buffer_;
    }

    Buffer Geometry::index_buffer() const
    {
        return index_buffer_;
    }

    void Geometry::createCube()
    {
        float vertices_f[] = {
            // positions          // normals           // uv 
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  // 4
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  // 8
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, // 12
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, // 16
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, // 20
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        };

        //  I'm lazy and didn't want to rewrite the data above as a Vertex
        Vertex *vertex_ptr = reinterpret_cast<Vertex*>(vertices_f);
        std::vector<Vertex> vertex_vector(vertex_ptr, 24 + vertex_ptr);

        uint32_t indices[] = {
             0,  2,  1,  2,  0,  3,
             4,  5,  6,  6,  7,  4,
             8,  9, 10, 10, 11,  8,
            13, 12, 14, 12, 15, 14,
            16, 17, 18, 18, 19, 16,
            23, 22, 20, 22, 21, 20,
        };

        std::vector<uint32_t> index_vector(std::begin(indices), std::end(indices));

        vertex_buffer_.create(BufferType::VERTEX_BUFFER);
        vertex_buffer_.set_data(vertex_vector);
        index_buffer_.create(BufferType::INDEX_BUFFER);
        index_buffer_.set_data(index_vector);
    }
}