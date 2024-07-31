#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

void loadModel(const std::string& model);

struct Object {
    std::vector<std::vector<double>> vert;
    std::vector<std::vector<int>> face;
    std::vector<std::vector<int>> normals;
    std::vector<std::vector<double>> faceNormals;
};

#endif // OBJECT_H
