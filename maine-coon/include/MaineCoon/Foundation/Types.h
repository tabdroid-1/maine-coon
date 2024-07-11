#pragma once

#include <MaineCoon/Core/UUID.h>

namespace MaineCoon {

typedef uint8_t byte;
typedef float float32;
typedef double float64;

using BitMask = uint64_t;
using Flag = uint64_t;
using AssetHandle = UUID;

struct MiscData {
    byte* data;
    uint32_t size;
};

template <typename T = float>
struct vec2 {
    union {
        T values[2];
        struct {
            union {
                T x, r;
            };
            union {
                T y, g;
            };
        };
    };

    vec2() = default;

    vec2(T value)
    {
        x = value;
        y = value;
    }

    vec2(const T& x, const T& y)
    {
        this->x = x;
        this->y = y;
    }

    // template <typename T>
    explicit constexpr operator vec2<T>() const { return { (T)x, (T)y }; }
    vec2 operator+(const vec2& other) { return { x + other.x, y + other.y }; }
    vec2 operator-(const vec2& other) { return { x - other.x, y - other.y }; }

    vec2& operator+=(const vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2& operator-=(const vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

template <typename T = float>
struct vec3 {
    union {
        T x, r;
    };
    union {
        T y, g;
    };
    union {
        T z, b;
    };

    vec3() = default;

    vec3(T value)
    {
        x = value;
        y = value;
        z = value;
    }

    vec3(const T& x, const T& y, const T& z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // template <typename T>
    explicit constexpr operator vec3<T>() const { return { T(x), T(y), T(z) }; }
    vec3 operator+(const vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }
    vec3 operator-(const vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }

    vec3& operator+=(const vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec3& operator-=(const vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
};

template <typename T = float>
struct vec4 {
    union {
        T x, r;
    };
    union {
        T y, g;
    };
    union {
        T z, b;
    };
    union {
        T w, a;
    };

    vec4() = default;

    vec4(T value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
    }

    vec4(const T& x, const T& y, const T& z, const T& w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    // template <typename T>
    explicit constexpr operator vec4<T>() const { return { (T)x, (T)y, T(z), (T)w }; }

    vec4 operator+(const vec4& other) { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
    vec4 operator-(const vec4& other) { return { x - other.x, y - other.y, z - other.z, w - other.w }; }

    vec4& operator+=(const vec4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w -= other.w;
        return *this;
    }

    vec4& operator-=(const vec4& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }
};

using IntVector2 = vec2<int32_t>;
using IntVector3 = vec3<int32_t>;
using IntVector4 = vec4<int32_t>;

using UIntVector2 = vec2<uint32_t>;
using UIntVector3 = vec3<uint32_t>;
using UIntVector4 = vec4<uint32_t>;

using Vector2 = vec2<float>;
using Vector3 = vec3<float>;
using Vector4 = vec4<float>;

// Non-owning raw buffer class
struct Buffer {
    uint8_t* Data = nullptr;
    uint64_t Size = 0;

    Buffer() = default;

    Buffer(uint64_t size)
    {
        Allocate(size);
    }

    Buffer(const void* data, uint64_t size)
        : Data((uint8_t*)data)
        , Size(size)
    {
    }

    Buffer(const Buffer&) = default;

    static Buffer Copy(Buffer other)
    {
        Buffer result(other.Size);
        memcpy(result.Data, other.Data, other.Size);
        return result;
    }

    void Allocate(uint64_t size)
    {
        Release();

        Data = (uint8_t*)malloc(size);
        Size = size;
    }

    void Release()
    {
        free(Data);
        Data = nullptr;
        Size = 0;
    }

    template <typename T>
    T* As()
    {
        return (T*)Data;
    }

    operator bool() const
    {
        return (bool)Data;
    }
};

struct ScopedBuffer {
    ScopedBuffer(Buffer buffer)
        : m_Buffer(buffer)
    {
    }

    ScopedBuffer(uint64_t size)
        : m_Buffer(size)
    {
    }

    ~ScopedBuffer()
    {
        m_Buffer.Release();
    }

    uint8_t* Data() { return m_Buffer.Data; }
    uint64_t Size() { return m_Buffer.Size; }

    template <typename T>
    T* As()
    {
        return m_Buffer.As<T>();
    }

    operator bool() const { return m_Buffer; }

private:
    Buffer m_Buffer;
};

}
