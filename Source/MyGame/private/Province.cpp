#include "Province.h"
#include "MapData.h"
#include "Engine/TextRenderActor.h"
#include "Ck2Map.h"
#include "Components/TextRenderComponent.h"
#include "EngineUtils.h"
static TArray<FVector2D> OutlineBias
{
	FVector2D(1,0), FVector2D(0,1),
	FVector2D(-1,0),  FVector2D(0,-1),
	FVector2D(-1,1),  FVector2D(1,-1),
	FVector2D(-1,-1),  FVector2D(1,1)
};


void AProvince::CreateOutLine(int32 Width, int32 Height, TArray<FColor>& MapProvinceColorData)
{
	TArray<FVector2D> TempOutLine2DCoordinate;
	TArray<int32> TempOutLineCoordinateIndex;
	for (auto& Coord : All2DCoordinate)
	{
		//如果在map的边缘,就说明是边缘
		if (Coord.X == 0 || Coord.Y == 0 || Coord.X == Height - 1 || Coord.Y == Width - 1)
		{
			TempOutLine2DCoordinate.Add(Coord);
			TempOutLineCoordinateIndex.Add(Coord.X * Width + Coord.Y);
			continue;
		}

		for (auto &bias : OutlineBias)
		{

			FVector2D b = Coord + bias;
			FColor OtherColor = MapProvinceColorData[b.X * Width + b.Y];
			if (OtherColor != ProvinceColor)
			{
				TempOutLine2DCoordinate.Add(Coord);
				TempOutLineCoordinateIndex.Add(Coord.X * Width + Coord.Y);
				break;
			}
		}
	}
	//找有顺序的边界
	OutLineCoordinateIndex.Empty();
	OutLine2DCoordinate.Empty();

	TArray<int32>NotStoredIndex;
	for (int i = 0; i != TempOutLine2DCoordinate.Num(); i++)
	{
		NotStoredIndex.Add(i);
	}

	for (int i=0;i!= TempOutLine2DCoordinate.Num();i++)
	{
		if (OutLine2DCoordinate.Num()==0)
		{
			OutLine2DCoordinate.Add(TempOutLine2DCoordinate[0]);
			OutLineCoordinateIndex.Add(TempOutLineCoordinateIndex[0]);
		}
		else
		{
			FVector2D PreOutLine=OutLine2DCoordinate.Last();
			float MinDistance=1000;
			int32 Index=-1;

			for (int j = 0; j != NotStoredIndex.Num(); j++)
			{
				float Distance=FVector2D::Distance(PreOutLine, TempOutLine2DCoordinate[NotStoredIndex[j]]);
				if (Distance < MinDistance&& Distance!=0&& INDEX_NONE==OutLine2DCoordinate.Find(TempOutLine2DCoordinate[NotStoredIndex[j]]))
				{
				
					MinDistance= Distance;
					Index=j;
					if (MinDistance == 1.0)
					{
						break;
					}
				}
			}
			if (Index != -1)
			{
				OutLine2DCoordinate.Add(TempOutLine2DCoordinate[Index]);
				OutLineCoordinateIndex.Add(TempOutLineCoordinateIndex[Index]);
				NotStoredIndex.RemoveAt(Index);
			}

		}
	}

	FVector2D Temp;
	for (auto& Coord : All2DCoordinate)
	{
		Temp = Temp + Coord;
	}


	//由于是从上向下，从左到右，所以我们需要
	OrigineVector = Temp / All2DCoordinate.Num();


	SplineComponent=NewObject<USplineComponent>(this);
	SplineComponent->AttachTo(RootComponent);
	TArray<FVector> OutLineWorldPositions = GetOutLineWorldPositions();
	SplineComponent->SetSplineWorldPoints(OutLineWorldPositions);
	SplineComponent->UpdateSpline();
	SplineComponent->RegisterComponent();
}

AProvince::AProvince()
{
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NewTextRenderComponent"));
	RootComponent = TextRenderComponent;
}


TArray<FVector> AProvince::GetOutLineWorldPositions()
{
	TArray<FVector> OutLineWorldPositions;
	for (auto& Position : OutLine2DCoordinate)
	{
		OutLineWorldPositions.Add(WorldBias + CellScale * FVector(Position.X, Position.Y, 0));
	}
	return  OutLineWorldPositions;
}

void AProvince::InitProvince(int32 Width, int32 Height)
{

	if (AllCoordinateIndex.Num() == 0)
	{
		return;
	}
	for (auto& a : AllCoordinateIndex)
	{
		All2DCoordinate.Add(FVector2D(a / Width, a % Width));
	}
}

void AProvince::SpawnText()
{
	SetActorLocation(WorldVector);
	SetActorRotation(FRotator(90, 0, 0));
	SetActorScale3D(FVector(0.5, 0.5, 0.5));
	if (GetWorld())
	{
		TextRenderComponent->SetText(FText::FromName(ProvinceName));
		//TextRenderComponent->SetActorLocation(WorldVector);
		//TextRenderComponent->SetActorRotation(FRotator(90, 0, 0));
		//TextRenderComponent->SetActorScale3D(FVector(0.5, 0.5, 0.5));
	}

}

void UProvinceManager::Init(ACk2Map* InMapActor,FMapColorData& MapColorData, TArray<FDataTableMapData*> &MapData)
{
	MapActor= InMapActor;


	//清理场景中的Province
	ColorToProcince.Empty();

	for (TActorIterator<AProvince> ActorItr(InMapActor->GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AProvince* Mesh = *ActorItr;
		Mesh->Destroy();
	}


	int32 MapHeight= MapColorData.Height;
	int32 MapWidth = MapColorData.Width;

	for (int32 X = 0; X < MapHeight; X++)
	{
		for (int32 Y = 0; Y < MapWidth; Y++)
		{
			FColor PixelColor = MapColorData.GetColor(X * MapWidth + Y);
			AProvince** ProvinceUnit = ColorToProcince.Find(PixelColor);
			//如果我们找到的话
			if (ProvinceUnit)
			{
				(*ProvinceUnit)->AllCoordinateIndex.Add(X * MapWidth + Y);
			}
			else
			{
				FDataTableMapData* TempMap = nullptr;
				for (auto &a : MapData)
				{
					FColor MapColor(a->red, a->green, a->blue);
					if (MapColor == PixelColor)
					{
						TempMap = a;
					}
				}
				//如果没有值，我们新建
				AProvince* temp= MapActor->GetWorld()->SpawnActor<AProvince>();
				temp->ProvinceColor = PixelColor;
				if (TempMap != nullptr)
				{
					temp->ProvinceName = *TempMap->name;
					temp->ProvinceID = TempMap->province;
				}
				else
				{
					temp->ProvinceName = FName(*FString::FromInt(X * MapWidth + Y));
					temp->ProvinceID = MapData.Num();
				}

				temp->AllCoordinateIndex.Add(X * MapWidth + Y);

				ColorToProcince.Add(PixelColor, temp);
			}
		}
	}



	for (TMap<FColor, AProvince*>::TConstIterator It = ColorToProcince.CreateConstIterator(); It; ++It)
	{
		It->Value->InitProvince(MapWidth, MapHeight);
	}

	for (TMap<FColor, AProvince*>::TConstIterator  It = ColorToProcince.CreateConstIterator(); It; ++It)
	{
		It->Value->WorldBias= MapActor->GetWorldMinPosition() +FVector(0, 0, 5);
		It->Value->CellScale= MapActor->GetCellSize();

		FVector Location = MapActor->GetWorldMinPosition() + MapActor->GetCellSize() * FVector(It->Value->OrigineVector.X, MapWidth - It->Value->OrigineVector.Y - 1, 0) + FVector(0, 0, 5);
		It->Value->WorldVector  = Location;

		It->Value->CreateOutLine(MapWidth, MapHeight, MapColorData.ColorData);

		
	}
	SpawnText();

}

void UProvinceManager::SpawnText()
{
	for (auto It = ColorToProcince.CreateConstIterator(); It; ++It)
	{
		It->Value->SpawnText();
	}
}

void UProvinceManager::ClearText()
{

}
