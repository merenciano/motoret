#include "render/geometry.h"

namespace motoret
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

        //  I've done this ugly thing in order to not spend time writing the
        //  cube data filling the Vertex struct (I copy-pasted from another project
        //  of mine and I was using array of floats).

        //  Actually trying to figure out how to cast to Vertex 
        //  without the void* temp has made me waste more time.
        void *ugly_temp = (void*)vertices_f;
        Vertex *vertex_ptr = (Vertex*)ugly_temp;
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