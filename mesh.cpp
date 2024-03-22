#include "mesh.h"

#define LINE_SIZE 128

void copyMesh(mesh &sourceMesh,mesh &destinationMesh)
{
    for(vec4 verticesIndex : sourceMesh.vertices)
        destinationMesh.vertices.push_back(verticesIndex);

    for(indexedTriangle indxTri : sourceMesh.indexedTriangles)
        destinationMesh.indexedTriangles.push_back(indxTri);

    destinationMesh.color = sourceMesh.color;
}

void processLine(mesh &m, std::stringstream &ss)
{
    std::string fieldType;

    ss >> fieldType;

    if(fieldType.compare("v") == 0)
    {
        vec4 vertex;
        ss >> vertex.x >> vertex.y >> vertex.z;
        m.vertices.push_back(vertex);
    }

    else if(fieldType.compare("c") == 0)
    {
        vec3 color;
        ss >> color.x >> color.y >> color.z;
        m.color = color;
    }
    else if(fieldType.compare("f") == 0)
    {
        indexedTriangle tri;

        for(int i = 0; i < 3; i++)
        {
            ss >> tri.vertexIndex[i];
            tri.vertexIndex[i]--;
        }

        m.indexedTriangles.push_back(tri);
    }
}

bool loadMesh(mesh &m, const char * modelPath)
{
    std::fstream fs;

    fs.open(modelPath,std::fstream::in);

    if(!fs.is_open())
        return false;

    while(!fs.eof())
    {
        char line[LINE_SIZE];
        fs.getline(line,LINE_SIZE);

        std::stringstream ss;
        ss << line;

        processLine(m, ss);
    }
    fs.close();

    return true;
}
