// Fill out your copyright notice in the Description page of Project Settings.


#include "Ck2Map.h"
#include "Logging/LogMacros.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACk2Map::ACk2Map()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TemStaticMesh(TEXT("StaticMesh'/Game/Mesh/Plane.Plane'"));

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	if (TemStaticMesh.Succeeded())

	{
		MapMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
		if (MapMeshComponent)
		{
			MapMeshComponent->SetStaticMesh(TemStaticMesh.Object);
			MapMeshComponent->SetupAttachment(RootComponent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail--------------"));
		}

	}


	if (!MapConfig)
	{
		MapConfig= CreateDefaultSubobject<UMapConfig>("MapConfig");
	}
}

// Called when the game starts or when spawned
void ACk2Map::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACk2Map::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACk2Map::InitMapData()
{
	if (!MapConfig)
	{
		MapConfig = NewObject<UMapConfig>();

	}
	if (!ProvinceManager)
	{
		ProvinceManager = NewObject<UProvinceManager>();
	}
	if (!MapConfig||!MapConfig->ProvinceTex || !MapMeshComponent)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("not Ready"));
		return;
	}	

	MapColorData= FMapConfigHelper::GetColorData(MapConfig->ProvinceTex);
	SetMapScale();

	InitMapTextureData();


}


void ACk2Map::SetMapScale()
{
	if (CellSizeScale == 0)
	{
		CellSizeScale = 1;
	}

	FVector WorldScale = FVector(MapColorData.Height * CellSizeScale, MapColorData .Width*CellSizeScale,1);
	//MapMeshComponent->SetWorldScale3D(WorldScale);
	
	MapMeshComponent->GetLocalBounds(LocalMinPosition, LocalMaxPosition);
	MapMeshComponent->SetRelativeScale3D(WorldScale);

	CellSize.X= WorldScale.X*(LocalMaxPosition - LocalMinPosition).X/ MapColorData.Height;
	CellSize.Y = WorldScale.Y*(LocalMaxPosition - LocalMinPosition).Y / MapColorData.Width;
	CellSize.Z = 0;
	WorldMinPosition=MapMeshComponent->GetComponentLocation()- FVector(MapColorData.Height /2, MapColorData.Width /2,0)*CellSize;

}

void ACk2Map::InitMapTextureData()
{
	FString ContextString;
	TArray<FDataTableMapData*> MapData;
	MapConfig->MapDefine->GetAllRows<FDataTableMapData>(ContextString, MapData);

	ProvinceManager->Init(this,MapColorData, MapData);
}




