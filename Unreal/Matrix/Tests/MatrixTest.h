// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixTest.generated.h"

UCLASS()
class PENNYDEBYLMATHCOURSE_API AMatrixTest : public AActor
{
	GENERATED_BODY()

public:
	
	AMatrixTest();

protected:

	virtual void BeginPlay() override;
};
