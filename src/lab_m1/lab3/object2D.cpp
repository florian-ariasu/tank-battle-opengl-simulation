#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh *object2D::CreateTrapeze(const std::string &name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length - width, width, 0), color),
            VertexFormat(corner + glm::vec3(width, width, 0), color)
        };

    Mesh *trapeze = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2, 3};

    if (!fill)
    {
        trapeze->SetDrawMode(GL_LINE_LOOP);
    }
    else
    {
        indices.push_back(0);
        indices.push_back(2);
    }

    trapeze->InitFromData(vertices, indices);
    return trapeze;
}

Mesh *object2D::CreateSemiCircle(const std::string &name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    int numTriangles = 50;                 
    float angleStep = M_PI / numTriangles;

    if (fill)
    {
        vertices.push_back(VertexFormat(center, color));
    }

    for (int i = 0; i <= numTriangles; i++)
    {
        float angle = i * angleStep;
        glm::vec3 position = center + glm::vec3(radius * cos(angle), radius * sin(angle), 0);
        vertices.push_back(VertexFormat(position, color));
    }

    if (fill)
    {
        for (int i = 1; i <= numTriangles; i++)
        {
            indices.push_back(0);     
            indices.push_back(i);     
            indices.push_back(i + 1); 
        }
    }
    else
    {
        for (int i = 0; i < numTriangles; i++)
        {
            indices.push_back(i + 1); 
            indices.push_back(i + 2); 
        }
    }

    Mesh *semiCircle = new Mesh(name);

    semiCircle->SetDrawMode(fill ? GL_TRIANGLES : GL_LINE_STRIP);
    semiCircle->InitFromData(vertices, indices);

    return semiCircle;
}

Mesh *object2D::CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, width, 0), color),
            VertexFormat(corner + glm::vec3(0, width, 0), color)
        };

    Mesh *rectangle = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2, 3};

    if (!fill)
    {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else
    {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}
