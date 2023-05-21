// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CustomMatrix.generated.h"

/**
 * FCustomMatrix
 *
 * A custom matrix class created by me with the big help from the course udemy.com/course/games_mathematics.
 * Just for learning purposes.
 */
USTRUCT(BlueprintType)
struct FCustomMatrix
{
	GENERATED_BODY()

public:
	FCustomMatrix();

	FCustomMatrix(int Rows, int Columns, const TArray<float>& Values);

private:
	// Is this matrix a point or a vector ?.
	bool IsPointOrVector(const bool ShouldLogIfNot = true);

public:
	// Get this matrix as vector 4 and its w as 1.
	FVector4 AsPoint();

	// Get this matrix as vector 4 and its w as 0.
	FVector4 AsVector4();

	FVector AsVector();

	//	Returns this matrix as a new matrix in 4x4 form :
	//	1, 0, 0, Values[0],
	// 	0, 1, 0, Values[1],
	// 	0, 0, 1, Values[2],
	// 	0, 0, 0, 1
	// NOTE : This matrix has to be a 4 row 1 column matrix(point or vector) otherwise it will not calculate.
	FCustomMatrix AsTranslation();

	//	Returns this matrix as a new matrix in 4x4 form :
	//	Values[0], 0, 0, 0,
	// 	0, Values[1], 0, 0,
	// 	0, 0, Values[2], 0,
	// 	0, 0, 0, 1
	// NOTE : This matrix has to be a 4 row 1 column matrix(point or vector) otherwise it will not calculate.
	FCustomMatrix AsScale();

public:
	// Returns a new 4x4 matrix for XRoll based on Angle like this :
	// 1, 0, 0, 0,
	// 0, FMath::Cos(AngleAsRadian), -FMath::Sin(AngleAsRadian), 0,
	// 0, FMath::Sin(AngleAsRadian), FMath::Cos(AngleAsRadian), 0,
	// 0, 0, 0, 1
	static FCustomMatrix GetXRollMatrixFromAngle(const float Angle);

	// Returns a new 4x4 matrix for YRoll based on Angle like this :
	// 1, 0, 0, 0,
	// 0, FMath::Cos(AngleAsRadian), -FMath::Sin(AngleAsRadian), 0,
	// 0, FMath::Sin(AngleAsRadian), FMath::Cos(AngleAsRadian), 0,
	// 0, 0, 0, 1
	static FCustomMatrix GetYRollMatrixFromAngle(const float Angle);

	// Returns a new 4x4 matrix for ZRoll based on Angle like this :
	// FMath::Cos(AngleAsRadian), -FMath::Sin(AngleAsRadian), 0, 0,
	// FMath::Sin(AngleAsRadian), FMath::Cos(AngleAsRadian), 0, 0,
	// 0, 0, 1, 0,
	// 0, 0, 0, 1
	static FCustomMatrix GetZRollMatrixFromAngle(const float Angle);

public:
	// Get a 4x4 shear matrix with given Vector.
	// 1, Vector.Y, Vector.Z, 0,
	// Vector.X, 1, Vector.Z, 0,
	// Vector.X, Vector.Y, 1, 0,
	// 0, 0, 0, 1
	static FCustomMatrix GetShearMatrixFromVector(const FVector& Vector);

	// Get a 4x4 reflection matrix with given Vector where if axis is not 0, element '1' of matching row of the identity matrix.
	//	1, 0, 0, 0,
	//  0, (-1), 0, 0,
	//  0, 0, 1, 0,
	//  0, 0, 0, 1
	static FCustomMatrix GetReflectionMatrixWithVector(const FVector& Vector);

	// Get a 4x4 matrix as such :
	//	1, 0, 0, 0,
	//  0, 1, 0, 0,
	//  0, 0, 1, 0,
	//  0, 0, 0, 1
	static const FCustomMatrix IDENTITY_MATRIX;

public:
	// Convert given vector to a 4x1 matrix which its last value is 1.
	static FCustomMatrix PointAsMatrix(const FVector& Vector);

	// Convert given vector to a 4x1 matrix which its last value is 0.
	static FCustomMatrix VectorAsMatrix(const FVector& Vector);

public:
	// Gets the given column index of this matrix.
	// NOTE : this matrix has to be a 4x4 otherwise it will return all zero.
	FVector4 GetColumn(int Column);

	// Gets the given row index of this matrix.
	// NOTE : this matrix has to be a 4x4 otherwise it will return all zero.
	FVector4 GetRow(int Row);

	float ValueAt(int row, int column) const;

private:
	bool Is4X4Matrix();

public:
	FCustomMatrix operator+(FCustomMatrix& OtherMatrix);

	FCustomMatrix operator*(FCustomMatrix& OtherMatrix);

public:
	// Get this matrix as a string.
	FString ToString();

public:
	TArray<float> Values;

	int Rows;

	int Columns;
};
