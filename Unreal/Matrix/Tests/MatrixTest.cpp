// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixTest.h"

#include "PennyDeBylMathCourse/Matrix/CustomMatrix.h"

AMatrixTest::AMatrixTest()
{
}

void AMatrixTest::BeginPlay()
{
	Super::BeginPlay();

	FCustomMatrix Matrix(2, 3, TArray<float>{1, 2, 3, 4, 5, 6});

	// UE_LOG(LogTemp, Warning, TEXT("%s"), *matrix.ToString());

	FCustomMatrix MatrixSecond(3, 2, TArray<float>{1, 2, 3, 4, 5, 6});

	UE_LOG(LogTemp, Warning, TEXT("%s"), *(Matrix * MatrixSecond).ToString());
}
