// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"
#include "Engine/DataTable.h"

#include "Ck2Map.generated.h"


struct FProvinceUnit
{
	int32 ProvinceID;
	TArray<int32> AllCoordinate;
	TArray<int32> OutLineCoordinate;
	FColor ProvinceColor;
	FName ProvinceName;
	TArray<FVector2D> All2DCoordinate;
	TArray<FVector2D> OutLine2DCoordinate;

	FVector2D OrigineVector;
	FVector WorldVector;
	void InitProvince(int32 Width,int32 Height);

	void GetOutLine(int32 Width, int32 Height, TArray<FColor>&MapProvinceColorData);

};

USTRUCT(BlueprintType)
struct FDataTableMapData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FDataTableMapData()
	{}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 province;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 red;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 green;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		int32 blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable Test")
		FString name;
};



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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	int32 MapHeight;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ck2")
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MapMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Transient, Category = "Ck2")
	TArray<ATextRenderActor*> ProvincesText;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* MapDefine;


	TArray<FColor>MapProvinceColorData;

private:
	void CopyTextureToArray(UTexture2D* Texture);
	
	void SetMapScale();

	void InitMapTextureData();

	void SpawnText();

	//void GetTextureData(UTexture2D* Texture);
	TArray<FProvinceUnit> Provinces;

	FVector LocalMinPosition;
	FVector LocalMaxPosition;
	FVector WorldMinPosition;
	FVector CellSize;

};
