#pragma once

#include <vector>

#include <fstream>
#include <sstream>

#include "vector.h"

struct indexedTriangle
{
    unsigned int vertexIndex[3];
};

struct mesh
{
    std::vector<vec4> vertices;
    vec3 color;

    std::vector<indexedTriangle> indexedTriangles;
};

void copyMesh(mesh &sourceMesh,mesh &destinationMesh);
bool loadMesh(mesh &m, const char * modelPath);
