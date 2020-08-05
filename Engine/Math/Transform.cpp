#include "pch.h"
#include "Transform.h"

namespace nc {
    std::istream& operator >> (std::istream& stream, Transform& transform)
    {
        stream >> transform.position;

        std::string line;

        std::getline(stream, line);
        transform.scale = stof(line);

        std::getline(stream, line);
        transform.angle = stof(line);

        return stream;
    }

    void Transform::Update() {
        nc::Matrix33 mxs;
        mxs.Scale(scale);
        nc::Matrix33 mxr;
        mxr.Rotate(angle);
        nc::Matrix33 mxt;
        mxt.Translate(position);

        matrix = mxs * mxr * mxt;
    }

    void Transform::Update(const Matrix33& mx) {
        nc::Matrix33 mxs;
        mxs.Scale(scale);
        nc::Matrix33 mxr;
        mxr.Rotate(angle);
        nc::Matrix33 mxt;
        mxt.Translate(position);

        matrix = mxs * mxr * mxt * mx;
    }
}