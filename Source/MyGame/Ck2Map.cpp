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
	}

	GetTextureData(ProvinceTex);
	
}




void ACk2Map::GetTextureData(UTexture2D* m_Texture)
{

	FColor* FormatedImageData = static_cast<FColor*>(m_Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY));

	int32 SizeY = m_Texture->PlatformData->Mips[0].SizeY;
	int32 SizeX = m_Texture->PlatformData->Mips[0].SizeX;
	MapProvinceColorData.Empty();
	MapProvinceColorData.Reserve(SizeY*SizeX);
	MapProvinceColorData.AddZeroed(SizeY*SizeX);

	for (int32 y = 0; y < SizeY; y++)
	{
		for (int32 x = 0; x < SizeX; x++)
		{
			int32 curPixelIndex = (y * m_Texture->PlatformData->Mips[0].SizeX) + x;
			FColor pixel = FormatedImageData[curPixelIndex];
			MapProvinceColorData[y*SizeX + x] = pixel;
		}
	}
	m_Texture->PlatformData->Mips[0].BulkData.Unlock();

	//m_Texture->CompressionSettings = OldCompressionSettings;
	////m_Texture->MipGenSettings = OldMipGenSettings;
	//m_Texture->SRGB = OldSRGB;
	m_Texture->UpdateResource();


	//GEngine->AddOnScreenDebugMessage((uint64)-1, 2.0f, FColor::Emerald, FString::Printf(TEXT("width = %d height = %d num = %d"), m_Texture->PlatformData->Mips[0].SizeX, m_Texture->PlatformData->Mips[0].SizeY));
}

