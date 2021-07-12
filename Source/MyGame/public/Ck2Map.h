// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/TextRenderComponent.h"

#include "MapData.h"
#include "Province.h"

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
		UTexture2D * ProvinceTex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
		int32 MapWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
		int32 MapHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
		FVector OriginVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
		FRotator OriginRotation;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
		UStaticMesh*  MapMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
		float CellSizeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MapMeshComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite,Transient, Category = "Ck2")
	//TArray<ATextRenderActor*> ProvincesText;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* MapDefine;

	FMapColorData MapColorData;

	//TArray<FColor>MapProvinceColorData;
public:
	FVector GetWorldMinPosition() { return WorldMinPosition; };

	FVector GetCellSize() { return CellSize; };

private:
	void CopyTextureToArray(UTexture2D* Texture);
	
	void SetMapScale();

	void InitMapTextureData();


	UPROPERTY()
	UProvinceManager* ProvinceManager;
	//TArray<FProvinceUnit> Provinces;

	//UPROPERTY()
	//TArray<UProvince*> AllProvinces;
	FVector LocalMinPosition;
	FVector LocalMaxPosition;
	FVector WorldMinPosition;
	FVector CellSize;

};
