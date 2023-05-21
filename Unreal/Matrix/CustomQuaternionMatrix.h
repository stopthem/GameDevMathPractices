// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomMatrix.h"

#include "CustomQuaternionMatrix.generated.h"

/**
 * FCustomQuaternionMatrix
 *
 * A custom quaternion matrix class created by me with the big help from the course udemy.com/course/games_mathematics.
 * Just for learning purposes.
 */
USTRUCT(BlueprintType)
struct FCustomQuaternionMatrix : public FCustomMatrix
{
	GENERATED_BODY()

public:
	FCustomQuaternionMatrix();

	using FCustomMatrix::FCustomMatrix;
};
