#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdbool.h>

#include "logging.h" 

#ifdef DEBUG
#include "logging.h"
#define VECTOR_ASSERT(condition, message) \
        do { if (!(condition)) { LOG_ERROR(message); } } while(0)
#else
#define VECTOR_ASSERT(condition, message) ((void)0)
#endif

/* ========================================================================== */
/* TYPE DEFINITIONS                                                           */
/* ========================================================================== */

typedef struct
{
    float x;
    float y;
} vec2_t;

typedef struct
{
    float x;
    float y;
    float z;
} vec3_t;

/* ========================================================================== */
/* CONSTANTS                                                                  */
/* ========================================================================== */

static const float VECTOR_EPSILON = 1e-6f;

static const vec2_t VEC2_ZERO = { 0.0f, 0.0f };
static const vec2_t VEC2_ONE = { 1.0f, 1.0f };

static const vec3_t VEC3_ZERO = { 0.0f, 0.0f, 0.0f };
static const vec3_t VEC3_ONE = { 1.0f, 1.0f, 1.0f };

/* ========================================================================== */
/* UTILITY FUNCTIONS                                                          */
/* ========================================================================== */

static inline bool float_equal(float a, float b) 
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

/* Create a new vec2_t */
static inline vec2_t vec2_new(float x, float y)
{
    return (vec2_t) { x, y };
}

/* Adds two vec2_t vectors */
static inline vec2_t vec2_add(vec2_t a, vec2_t b)
{
    return (vec2_t) { a.x + b.x, a.y + b.y };
}

/* Subtracts vec2_t b from vec2_t a */
static inline vec2_t vec2_sub(vec2_t a, vec2_t b)
{
    return (vec2_t) { a.x - b.x, a.y - b.y };
}

/* Scales a vec2_t by a scalar */
static inline vec2_t vec2_scale(vec2_t v, float scalar)
{
    return (vec2_t) { v.x * scalar, v.y * scalar };
}

/* Component-wise multiplication of two vec2_t vectors */
static inline vec2_t vec2_multiply(vec2_t a, vec2_t b)
{
    return (vec2_t) { a.x * b.x, a.y * b.y };
}

/* Divides a vec2_t by a scalar with zero-check */
static inline vec2_t vec2_divide(vec2_t v, float scalar)
{
    VECTOR_ASSERT(fabsf(scalar) > VECTOR_EPSILON, "Division by zero in vec2_divide");
    if (fabsf(scalar) < VECTOR_EPSILON) 
    {
        return VEC2_ZERO;
    }
    return (vec2_t) { v.x / scalar, v.y / scalar };
}

/* Negates a vec2_t vector */
static inline vec2_t vec2_negate(vec2_t v)
{
    return (vec2_t) { -v.x, -v.y };
}

/* ========================================================================== */
/* VEC2 ADVANCED OPERATIONS                                                   */
/* ========================================================================== */

/* Dot product of two vec2_t vectors */
static inline float vec2_dot(vec2_t a, vec2_t b)
{
    return a.x * b.x + a.y * b.y;
}

/* Cross product of two vec2_t vectors (returns scalar in 2D) */
static inline float vec2_cross(vec2_t a, vec2_t b)
{
    return a.x * b.y - a.y * b.x;
}

/* Length (magnitude) of a vec2_t vector */
static inline float vec2_length(vec2_t v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

/* Squared length of a vec2_t vector */
static inline float vec2_length_squared(vec2_t v)
{
    return v.x * v.x + v.y * v.y;
}

/* Normalizes a vec2_t vector */
static inline vec2_t vec2_normalize(vec2_t v)
{
    float len = vec2_length(v);
    VECTOR_ASSERT(len > VECTOR_EPSILON, "Cannot normalize zero-length vector in vec2_normalize");
    if (len < VECTOR_EPSILON) 
    {
        return VEC2_ZERO;
    }
    return vec2_divide(v, len);
}

/* Distance between two vec2_t vectors */
static inline float vec2_distance(vec2_t a, vec2_t b)
{
    return vec2_length(vec2_sub(b, a));
}

/* Squared distance between two vec2_t vectors */
static inline float vec2_distance_squared(vec2_t a, vec2_t b)
{
    return vec2_length_squared(vec2_sub(b, a));
}

/* Linear interpolation between two vec2_t vectors */
static inline vec2_t vec2_lerp(vec2_t a, vec2_t b, float t)
{
    t = float_clamp(t, 0.0f, 1.0f);
    return (vec2_t) { float_lerp(a.x, b.x, t), float_lerp(a.y, b.y, t) };
}

/* Rotate a vec2_t by an angle in radians */
static inline vec2_t vec2_rotate(vec2_t v, float angle_rad)
{
    float cos_a = cosf(angle_rad);
    float sin_a = sinf(angle_rad);
    return (vec2_t) { v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a };
}

/* Angle of a vec2_t in radians from the positive x-axis */
static inline float vec2_angle(vec2_t v) 
{
	return atan2f(v.y, v.x);
}

/* Reflects a vector off a surface with given normal */
static inline vec2_t vec2_reflect(vec2_t incident, vec2_t normal) 
{
    float dot_product = vec2_dot(incident, normal);
    return vec2_sub(incident, vec2_scale(normal, 2.0f * dot_product));
}

/* Projects vector a onto vector b */
static inline vec2_t vec2_project(vec2_t a, vec2_t b) 
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

/* Checks if two vec2_t vectors are equal (with epsilon tolerance) */
static inline bool vec2_equals(vec2_t a, vec2_t b) 
{
    return float_equals(a.x, b.x) && float_equals(a.y, b.y);
}

/* Checks if vec2_t is zero vector (with epsilon tolerance) */
static inline bool vec2_is_zero(vec2_t v) 
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