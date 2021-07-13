// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "MapData.h"
#include "Province.h"
#include "MapConfig.h"

#include "Ck2Map.generated.h"



UCLASS()
class MYGAME_API ACk2Map : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACk2Map();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(CallInEditor, Category = "Ck2")
	virtual void InitMapData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
	UMapConfig* MapConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
	float CellSizeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MapMeshComponent;

	FMapColorData MapColorData;

public:
	FVector GetWorldMinPosition() { return WorldMinPosition; };

	FVector GetCellSize() { return CellSize; };

private:
	
	void SetMapScale();

	void InitMapTextureData();

	UPROPERTY()
	UProvinceManager* ProvinceManager;


	FVector LocalMinPosition;
	FVector LocalMaxPosition;
	FVector WorldMinPosition;
	FVector CellSize;

};
