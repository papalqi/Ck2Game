// Fill out your copyright notice in the Description page of Project Settings.


#include "Ck2Map.h"
#include "Logging/LogMacros.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ACk2Map::ACk2Map()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	if (!ProvinceTex || !MapMeshComponent)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("not Ready"));
		return;
	}	

	CopyTextureToArray(ProvinceTex);

	SetMapScale();

	InitMapTextureData();


}

void ACk2Map::CopyTextureToArray(UTexture2D* Texture)
{

	TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
	bool OldSRGB = Texture->SRGB;
	Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Texture->SRGB = false;
	Texture->UpdateResource();
	MapWidth = Texture->GetSizeX();
	MapHeight = Texture->GetSizeY();
	const FColor* FormatedImageData = static_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.LockReadOnly());


	MapColorData = FMapColorData(MapHeight, MapWidth);

	MapColorData.Init(FormatedImageData);


	Texture->PlatformData->Mips[0].BulkData.Unlock();

	Texture->CompressionSettings = OldCompressionSettings;
	Texture->MipGenSettings = OldMipGenSettings;
	Texture->SRGB = OldSRGB;
	Texture->UpdateResource();
	
}

void ACk2Map::SetMapScale()
{
	if (CellSizeScale == 0)
	{
		CellSizeScale = 1;
	}

	FVector WorldScale = FVector(MapHeight * CellSizeScale,MapWidth*CellSizeScale,1);
	//MapMeshComponent->SetWorldScale3D(WorldScale);
	
	MapMeshComponent->GetLocalBounds(LocalMinPosition, LocalMaxPosition);
	MapMeshComponent->SetRelativeScale3D(WorldScale);

	CellSize.X= WorldScale.X*(LocalMaxPosition - LocalMinPosition).X/MapHeight;
	CellSize.Y = WorldScale.Y*(LocalMaxPosition - LocalMinPosition).Y / MapWidth;
	CellSize.Z = 0;
	WorldMinPosition=MapMeshComponent->GetComponentLocation()- FVector(MapHeight/2, MapWidth/2,0)*CellSize;

}

void ACk2Map::InitMapTextureData()
{
	ProvinceManager=NewObject<UProvinceManager>();
	FString ContextString;
	TArray<FDataTableMapData*> MapData;
	MapDefine->GetAllRows<FDataTableMapData>(ContextString, MapData);

	ProvinceManager->Init(this,MapColorData, MapData);
}




