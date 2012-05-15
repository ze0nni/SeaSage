#ifndef MATH_H
#define MATH_H

#include "math.h"
#include <stdio.h>
#include <string.h>

struct Matrix4d {
    union {
        float vector[16];
        float matrix[4][4];
        struct {
            float c11, c12, c13, c14;
            float c21, c22, c23, c24;
            float c31, c32, c33, c34;
            float c41, c42, c43, c44;
        };
    };

    float* data() {
        return vector;
    }

    void set(float c11, float c12, float c13, float c14,
             float c21, float c22, float c23, float c24,
             float c31, float c32, float c33, float c34,
             float c41, float c42, float c43, float c44) {
        //Комируем значения из стека
        memcpy(vector, &c11, sizeof(vector));
    }

    static Matrix4d get(float c11, float c12, float c13, float c14,
             float c21, float c22, float c23, float c24,
             float c31, float c32, float c33, float c34,
             float c41, float c42, float c43, float c44) {
        Matrix4d m;
        memcpy(m.vector, &c11, sizeof(vector));
        return m;
    }

    void setIdentity() {
        set(1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Matrix4d getIdentity() {
        Matrix4d m; m.setIdentity();
        return m;
    }

    void setTranslate(float x, float y, float z) {
        set(1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            x,    y,    z,    1.0f);
    }

    static Matrix4d getTranslate(float x, float y, float z) {
        Matrix4d m; m.setTranslate(x, y, z);
        return m;
    }

    void setScale(float x, float y, float z) {
        set(x   , 0.0f, 0.0f, 0.0f,
            0.0f, y    , 0.0f, 0.0f,
            0.0f, 0.0f, z    , 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Matrix4d getScale(float x, float y, float z) {
        Matrix4d m; m.setScale(x, y, z);
        return m;
    }

    void setScale(float s) {
        set(1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, s);
    }

    static Matrix4d getScale(float s) {
        Matrix4d m; m.setScale(s);
        return m;
    }
};

struct Vector3d {
    union {
        float coors[3];
        struct {
            float x;
            float y;
            float z;
        };
    };

    void set(float _x, float _y, float _z) {
        x=_x;
        y=_y;
        z=_z;
    }

    static Vector3d get(float _x, float _y, float _z) {
        Vector3d v;
        v.x = _x;
        v.y = _y;
        v.z = _z;
        return v;
    }

    void setIdentity() {
        set(0.0f, 0.0f, 0.0f);
    }

    const Vector3d operator+ (const Vector3d v) {
        Vector3d res;
        res.x = x + v.x;
        res.y = y + v.y;
        res.z = z + v.z;
        return res;
    }

    void add(float _x, float _y, float _z) {
        this->x += _x;
        this->y += _y;
        this->z += _z;
    }

    void add(Vector3d* v) {
        this->x += v->x;
        this->y += v->y;
        this->z += v->z;
    }

    const Vector3d operator- (const Vector3d v) {
        Vector3d res;
        res.x = x - v.x;
        res.y = y - v.y;
        res.z = z - v.z;
        return res;
    }

    void sub(float _x, float _y, float _z) {
        this->x += _x;
        this->y += _y;
        this->z += _z;
    }

    void sub(Vector3d* v) {
        this->x += v->x;
        this->y += v->y;
        this->z += v->z;
    }

    const Vector3d operator- () {
        Vector3d res;
        res.x = -x;
        res.y = -y;
        res.z = -z;
        return res;
    }


    const Vector3d operator* (const float s) {
        Vector3d res;
        res.x = x * s;
        res.y = y * s;
        res.z = z * s;
        return res;
    }

    const Vector3d operator* (const Matrix4d m) {
        Vector3d res;
        float w = m.c14 * x + m.c24 * y + m.c34 * z + m.c44;
        res.x = (m.c11 * x + m.c21 * y + m.c31 * z + m.c41)/w;
        res.y = (m.c12 * x + m.c22 * y + m.c32 * z + m.c42)/w;
        res.z = (m.c13 * x + m.c23 * y + m.c33 * z + m.c43)/w;
        return res;
    }

    float length() {
        return sqrt(pow(x,2.0f) + pow(y,2.0f) + pow(z,2.0f));
    }
};

#endif // MATH_H
