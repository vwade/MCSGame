// MCSUnits.h
// Header-only unit and coordinate conversion library for Modular Combat Systems.
// Handles meters-to-cm scaling and axis swizzling implicitly.
// Include this in any component for background conversions.

#pragma once

#include "CoreMinimal.h"  // For FVector, etc.

// Define the unit scale: 1 meter (internal) = 100 cm (UE)
constexpr float MCS_UNIT_SCALE = 100.0f;

// Templated scalar wrapper for units like length, speed, etc.
// Use specific typedefs below for type safety.
template<typename T>
struct MCSScalar {
    float Value;  // Stored in meters or equivalent (your mental unit)

    MCSScalar(float v = 0.0f) : Value(v) {}

    // Implicit conversion to float (UE cm units)
    operator float() const {
        return (float)Value * (float)MCS_UNIT_SCALE;
    }
    // operator int() const {
    //  return (int)(Value * MCS_UNIT_SCALE);
    // }
    // operator double() const {
    //  return (double)Value * (double)MCS_UNIT_SCALE;
    // }
    // // stopping double/long double refactor here. we should test first before this stretch goal.

    // Basic operators for math within your system (stays in meters)
    MCSScalar& operator+=(const MCSScalar& other) { Value += other.Value; return *this; }
    MCSScalar& operator-=(const MCSScalar& other) { Value -= other.Value; return *this; }
    MCSScalar& operator*=(float scalar) { Value *= scalar; return *this; }
    MCSScalar& operator/=(float scalar) { Value /= scalar; return *this; }
    // MCSScalar& operator+(const MCSScalar& other) { Value += other.Value; return *this; }
    // MCSScalar& operator-(const MCSScalar& other) { Value -= other.Value; return *this; }
    // MCSScalar& operator*(float scalar) { Value *= scalar; return *this; }
    // MCSScalar& operator/(float scalar) { Value /= scalar; return *this; }
    // Add more as needed (e.g., operator+ for chaining)
};

// Specific types for clarity (e.g., prevent mixing length and speed accidentally)
using MCSLength = MCSScalar<struct LengthTag>;  // e.g., positions in meters
using MCSSpeed = MCSScalar<struct SpeedTag>;    // e.g., velocities in m/s

// Vector wrapper: Your XYZ (X-right/lateral, Y-up/vertical, Z-forward/depth)
// Converts to UE FVector (X-forward, Y-right, Z-up) with optional scaling.
struct MCSVector {
    float X;  // Right (+) / Left (-)
    float Y;  // Up (+) / Down (-)
    float Z;  // Forward (+) / Backward (-)
    bool bIsDirection;  // If true, no unit scaling (for normals/directions)

    MCSVector(float x = 0.0f, float y = 0.0f, float z = 0.0f, bool isDir = false)
        : X(x), Y(y), Z(z), bIsDirection(isDir) {}

    // Implicit conversion to FVector: Swizzle axes and scale if physical
    operator FVector() const {
        float scale = bIsDirection ? 1.0f : MCS_UNIT_SCALE;
        return FVector(Z * scale, X * scale, Y * scale);
    }

    // Example math ops (add more as needed, e.g., Dot, Cross in your coords)
    MCSVector operator+(const MCSVector& other) const {
        return MCSVector(X + other.X, Y + other.Y, Z + other.Z, bIsDirection || other.bIsDirection);
    }
    // // more math ops, added by me
    // MCSVector operator-(const MCSVector& other) const {
    //  return MCSVector(X - other.X, Y - other.Y, Z - other.Z, bIsDirection || other.bIsDirection);
    // }
    // MCSVector operator*(const MCSVector& other) const {
    //  return MCSVector(X * other.X, Y * other.Y, Z * other.Z, bIsDirection || other.bIsDirection);
    // }
    // MCSVector operator/(const MCSVector& other) const {
    //  return MCSVector(X / other.X, Y / other.Y, Z / other.Z, bIsDirection || other.bIsDirection);
    // }
    // // need matrix math here

    MCSVector& Normalize() {
        float mag = FMath::Sqrt(X*X + Y*Y + Z*Z);
        if (mag > 0.0f) {
            X /= mag; Y /= mag; Z /= mag;
        }
        bIsDirection = true;
        return *this;
    }

    // Hook for SOI adaptation: Transform this vector relative to a planet's radial frame.
    // Example: Align Z to radial outward from gravity center.
    // Usage: In your navigation component, compute local adjustments here before conversion.
    void AdaptToSOI(const FVector& ueGravityCenter, const FVector& ueCurrentPos) {
        // Convert inputs to MCS coords (inverse swizzle/scale)
        MCSVector gravityCenter = ToMCS(ueGravityCenter, false);  // Assume physical
        MCSVector currentPos = ToMCS(ueCurrentPos, false);

        // Simple example: Reorient Z to point outward from gravity center
        MCSVector radial = currentPos - gravityCenter;
        radial.Normalize();  // Now unit direction outward

        // Rotate this vector to align with new frame (placeholder; use quaternion for real)
        // For now, just set Z component along radial if needed; expand with full basis.
        Z = radial.Z;  // Trivial example—replace with matrix transform for XY polar alignment.

        // Note: For realistic gravity effects (e.g., orbital mech), integrate with your flight controls here.
    }
};

// Utility: Convert UE FVector back to MCSVector (inverse swizzle/scale)
static MCSVector ToMCS(const FVector& ueVec, bool isDir = false) {
    float scale = isDir ? 1.0f : (1.0f / MCS_UNIT_SCALE);
    return MCSVector(ueVec.Y * scale, ueVec.Z * scale, ueVec.X * scale, isDir);
}

// Extension hook for rotations (e.g., FRotator): Swizzle axes for pitch/yaw/roll.
// UE: Pitch (Y-axis), Yaw (Z-axis), Roll (X-axis)
// Your: Pitch (X-axis? lateral), Yaw (Y-axis up), Roll (Z-axis forward)
// Implement as needed.
struct MCSRotator {
    float Pitch, Yaw, Roll;  // In your axis meanings

    operator FRotator() const {
        // Swizzle: Map your rotations to UE axes
        return FRotator(Yaw, Roll, Pitch);  // Example mapping; test/adjust for your flight controls
    }
};

// Add more (e.g., MCSQuaternion with similar implicit to FQuat, handling axis swaps)