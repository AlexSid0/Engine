#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <sstream>
#include <object.h>

extern std::vector<Object> Objects;

std::vector<double> calculateVector(const std::string& data) {
    std::vector<double> vector;
    std::istringstream iss(data);
    double value;
    while (iss >> value) {
        vector.push_back(value);
    }
    return vector;
}

std::vector<int> calculateVectorInt(const std::string& data) {
    std::vector<int> vector;
    std::istringstream iss(data);
    int value;
    while (iss >> value) {
        vector.push_back(value);
    }
    return vector;
}

std::vector<std::string> calculateVectorSections(const std::string& data) {
    std::vector<std::string> vector;
    std::istringstream iss(data);
    std::string section;
    while (iss >> section) {
        vector.push_back(section);
    }
    return vector;
}

std::vector<int> calculateVectorPointers(const std::string& data) {
    std::vector<int> vector;
    std::istringstream iss(data);
    std::string part;
    while (std::getline(iss, part, '/')) {
        vector.push_back(std::stoi(part));
    }
    return vector;
}

void loadModel(const std::string& model) {
    
    std::string projectPath = std::filesystem::current_path().parent_path();
    
    
    std::ifstream f(projectPath + "/resources/objects/" + model + ".obj");
    if (f.is_open()) {
        std::string fileLine;
        Object object;
        std::vector<std::vector<double>> vert;
        std::vector<std::vector<int>> face;
        std::vector<std::vector<int>> normalPointers;
        std::vector<std::vector<double>> faceNormals;

        while (std::getline(f, fileLine)) {
            if (fileLine.find("vn ") != std::string::npos) {
                faceNormals.push_back(calculateVector(fileLine.substr(3)));
            }

            if (fileLine.find("v ") != std::string::npos) {
                vert.push_back(calculateVector(fileLine.substr(2)));
            }

            if (fileLine.find("f ") != std::string::npos) {
                std::vector<std::string> sections = calculateVectorSections(fileLine.substr(2));
                std::vector<int> section1 = calculateVectorPointers(sections[0]);
                std::vector<int> section2 = calculateVectorPointers(sections[1]);
                std::vector<int> section3 = calculateVectorPointers(sections[2]);

                face.push_back({section1[0], section2[0], section3[0]});
                normalPointers.push_back({section1[2], section2[2], section3[2]});
            }
        }

        object.vert = vert;
        object.face = face;
        object.normals = normalPointers;
        object.faceNormals = faceNormals;
        Objects.push_back(object);
    } else {
        std::string response;
        std::cout << "Failed to open file: " << model << ".obj\n";
        std::cout << "Do you want to try again? [Y/N]\n";
        std::cin >> response;
        if (response == "Y") {
            std::string newModel;
            std::cout << "New file [model.obj]:\n";
            std::cin >> newModel;
            loadModel(newModel);
        }
    }

}