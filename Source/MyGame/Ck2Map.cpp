// Fill out your copyright notice in the Description page of Project Settings.


#include "Ck2Map.h"
#include "Logging/LogMacros.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACk2Map::ACk2Map()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<UStaticMesh> TemStaticMesh(TEXT("/Game/Mesh/SM_Template_Map_Floor"));

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	if (TemStaticMesh.Succeeded())

	{
		MapMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
		if (MapMeshComponent)
		{
			// "Components/SkeletalMeshComponent.h"
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
}

void ACk2Map::CopyTextureToArray(UTexture2D* Texture)
{

	TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
	bool OldSRGB = Texture->SRGB;
	MapProvinceColorData.Empty();
	Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Texture->SRGB = false;
	Texture->UpdateResource();
	MapWidth = Texture->GetSizeX();
	MapHeight = Texture->GetSizeY();
	const FColor* FormatedImageData = static_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.LockReadOnly());
	MapProvinceColorData.Reserve(MapHeight* MapWidth);

	for (int32 X = 0; X < MapWidth; X++)
	{
		for (int32 Y = 0; Y < MapHeight; Y++)
		{
			FColor PixelColor = FormatedImageData[Y * MapWidth + X];
			//�����ɲ���
			MapProvinceColorData.Add(PixelColor);
		}
	}

	Texture->PlatformData->Mips[0].BulkData.Unlock();

	Texture->CompressionSettings = OldCompressionSettings;
	Texture->MipGenSettings = OldMipGenSettings;
	Texture->SRGB = OldSRGB;
	Texture->UpdateResource();
	
}
