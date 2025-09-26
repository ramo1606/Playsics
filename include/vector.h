#ifndef VECTOR_H
#define VECTOR_H

#include "core.h"
#include "logging.h" 

#ifdef DEBUG
#include "logging.h"
#define VECTOR_ASSERT(condition, message) \
        do { if (!(condition)) { LOG_ERROR(message); } } while(0)
#else
#define VECTOR_ASSERT(condition, message) ((void)0)
#endif

/* ========================================================================== */
/* CONSTANTS                                                                  */
/* ========================================================================== */

static const float VECTOR_EPSILON = 1e-6f;

static const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
static const Vector2 VEC2_ONE = { 1.0f, 1.0f };

static const Vector3 VEC3_ZERO = { 0.0f, 0.0f, 0.0f };
static const Vector3 VEC3_ONE = { 1.0f, 1.0f, 1.0f };

/* ========================================================================== */
/* UTILITY FUNCTIONS                                                          */
/* ========================================================================== */

static inline bool float_equals(float a, float b) 
{
    return fabsf(a - b) < VECTOR_EPSILON;
}

static inline float float_clamp(float value, float min, float max) 
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

static inline float float_lerp(float a, float b, float t) 
{
    return a + t * (b - a);
}

/* ========================================================================== */
/* VEC2 BASIC OPERATIONS                                                      */
/* ========================================================================== */

/* Create a new Vector2 */
static inline Vector2 vec2_new(float x, float y)
{
    return (Vector2) { x, y };
}

/* Adds two Vector2 vectors */
static inline Vector2 vec2_add(Vector2 a, Vector2 b)
{
    return (Vector2) { a.x + b.x, a.y + b.y };
}

/* Subtracts Vector2 b from Vector2 a */
static inline Vector2 vec2_sub(Vector2 a, Vector2 b)
{
    return (Vector2) { a.x - b.x, a.y - b.y };
}

/* Scales a Vector2 by a scalar */
static inline Vector2 vec2_scale(Vector2 v, float scalar)
{
    return (Vector2) { v.x * scalar, v.y * scalar };
}

/* Component-wise multiplication of two Vector2 vectors */
static inline Vector2 vec2_multiply(Vector2 a, Vector2 b)
{
    return (Vector2) { a.x * b.x, a.y * b.y };
}

/* Divides a Vector2 by a scalar with zero-check */
static inline Vector2 vec2_divide(Vector2 v, float scalar)
{
    VECTOR_ASSERT(fabsf(scalar) > VECTOR_EPSILON, "Division by zero in vec2_divide");
    if (fabsf(scalar) < VECTOR_EPSILON) 
    {
        return VEC2_ZERO;
    }
    return (Vector2) { v.x / scalar, v.y / scalar };
}

/* Negates a Vector2 vector */
static inline Vector2 vec2_negate(Vector2 v)
{
    return (Vector2) { -v.x, -v.y };
}

/* ========================================================================== */
/* VEC2 ADVANCED OPERATIONS                                                   */
/* ========================================================================== */

/* Dot product of two Vector2 vectors */
static inline float vec2_dot(Vector2 a, Vector2 b)
{
    return a.x * b.x + a.y * b.y;
}

/* Cross product of two Vector2 vectors (returns scalar in 2D) */
static inline float vec2_cross(Vector2 a, Vector2 b)
{
    return a.x * b.y - a.y * b.x;
}

/* Length (magnitude) of a Vector2 vector */
static inline float vec2_length(Vector2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

/* Squared length of a Vector2 vector */
static inline float vec2_length_squared(Vector2 v)
{
    return v.x * v.x + v.y * v.y;
}

/* Normalizes a Vector2 vector */
static inline Vector2 vec2_normalize(Vector2 v)
{
    float len = vec2_length(v);
    VECTOR_ASSERT(len > VECTOR_EPSILON, "Cannot normalize zero-length vector in vec2_normalize");
    if (len < VECTOR_EPSILON) 
    {
        return VEC2_ZERO;
    }
    return vec2_divide(v, len);
}

/* Distance between two Vector2 vectors */
static inline float vec2_distance(Vector2 a, Vector2 b)
{
    return vec2_length(vec2_sub(b, a));
}

/* Squared distance between two Vector2 vectors */
static inline float vec2_distance_squared(Vector2 a, Vector2 b)
{
    return vec2_length_squared(vec2_sub(b, a));
}

/* Linear interpolation between two Vector2 vectors */
static inline Vector2 vec2_lerp(Vector2 a, Vector2 b, float t)
{
    t = float_clamp(t, 0.0f, 1.0f);
    return (Vector2) { float_lerp(a.x, b.x, t), float_lerp(a.y, b.y, t) };
}

/* Rotate a Vector2 by an angle in radians */
static inline Vector2 vec2_rotate(Vector2 v, float angle_rad)
{
    float cos_a = cosf(angle_rad);
    float sin_a = sinf(angle_rad);
    return (Vector2) { v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a };
}

/* Angle of a Vector2 in radians from the positive x-axis */
static inline float vec2_angle(Vector2 v) 
{
	return atan2f(v.y, v.x);
}

/* Reflects a vector off a surface with given normal */
static inline Vector2 vec2_reflect(Vector2 incident, Vector2 normal) 
{
    float dot_product = vec2_dot(incident, normal);
    return vec2_sub(incident, vec2_scale(normal, 2.0f * dot_product));
}

/* Projects vector a onto vector b */
static inline Vector2 vec2_project(Vector2 a, Vector2 b) 
{
    float b_length_squared = vec2_length_squared(b);
    VECTOR_ASSERT(b_length_squared > VECTOR_EPSILON, "Cannot project onto zero-length vector in vec2_project");
    if (b_length_squared < VECTOR_EPSILON) 
    {
        return VEC2_ZERO;
    }
    float scalar = vec2_dot(a, b) / b_length_squared;
	return vec2_scale(b, scalar);
}

/* ========================================================================== */
/* VEC2 COMPARISON OPERATIONS                                                 */
/* ========================================================================== */

/* Checks if two Vector2 vectors are equal (with epsilon tolerance) */
static inline bool vec2_equals(Vector2 a, Vector2 b) 
{
    return float_equals(a.x, b.x) && float_equals(a.y, b.y);
}

/* Checks if Vector2 is zero vector (with epsilon tolerance) */
static inline bool vec2_is_zero(Vector2 v) 
{
    return vec2_length_squared(v) < (VECTOR_EPSILON * VECTOR_EPSILON);
}

/* ========================================================================== */
/* CONVENIENCE MACROS                                                         */
/* ========================================================================== */

/* Shorthand macros for common operations */
#define VEC2(x, y) vec2_new(x, y)
// #define VEC3(x, y, z) vec3_create(x, y, z)

/* Component access macros */
#define VEC2_X(v) ((v).x)
#define VEC2_Y(v) ((v).y)
// #define VEC3_X(v) ((v).x)
// #define VEC3_Y(v) ((v).y)
// #define VEC3_Z(v) ((v).z)

/* Swizzle operations */
#define VEC2_XX(v) VEC2((v).x, (v).x)
#define VEC2_YY(v) VEC2((v).y, (v).y)
#define VEC2_YX(v) VEC2((v).y, (v).x)

// #define VEC3_XXX(v) VEC3((v).x, (v).x, (v).x)
// #define VEC3_XYZ(v) (v)
// #define VEC3_ZYX(v) VEC3((v).z, (v).y, (v).x)

#endif /* VECTOR_H */