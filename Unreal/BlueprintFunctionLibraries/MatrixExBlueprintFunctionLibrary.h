// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatrixExBlueprintFunctionLibrary.generated.h"

struct FCustomQuaternionMatrix;
struct FCustomMatrix;
/**
 * UMatrixExBlueprintFunctionLibrary
 *
 * Extra library functions for custom matrix class created by me with the big help from the course udemy.com/course/games_mathematics.
 * Just for learning purposes.
 */
UCLASS()
class UMatrixExBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static FVector Translate(const FVector& Location, const FVector& Direction);

public:
	UFUNCTION(BlueprintPure)
	static FVector Scale(const FVector& Location, const FVector& Scale);

	UFUNCTION(BlueprintPure)
	static FVector ScaleAroundCenter(const FVector& Location, const FVector& Scale, const FVector& Center);

public:
	UFUNCTION(BlueprintPure)
	static FVector Rotate(const FVector& Location, const FVector& AnglesVector);

	UFUNCTION(BlueprintPure)
	static FVector RotateAroundCenter(const FVector& Location, const FVector& AnglesVector, const FVector& Center);

public:
	UFUNCTION(BlueprintPure)
	static FVector QuaternionAngleAxis(const FVector& Location, const FVector& Axis, const float Angle);

	UFUNCTION(BlueprintPure)
	static FCustomMatrix GetRotationMatrixFromAngles(const FVector& AnglesVector);

	UFUNCTION(BlueprintPure)
	static float GetRotationAxisAngle(const FCustomMatrix& RotationMatrix);

	UFUNCTION(BlueprintPure)
	static FCustomMatrix GetRotationAxisMatrix(const FCustomMatrix& RotationMatrix, float Angle);

	UFUNCTION(BlueprintPure)
	static FQuat GetQuaternionFromAngleAndAxis(const FVector& AxisVector, const float Angle);

public:
	UFUNCTION(BlueprintPure)
	static FVector Shear(const FVector& Location, const FVector& ShearVector);

public:
	UFUNCTION(BlueprintPure)
	static FVector Reflection(const FVector& Location, const FVector& ReflectionVector);
};
