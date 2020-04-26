#pragma once

#include "CoreMinimal.h"
struct LinePoint
{
	int Pointid = -1;
	FVector2D MPosition = FVector2D::ZeroVector;
	LinePoint(int id, FVector2D mPosition)
	{
		Pointid = id;
		MPosition = mPosition;
	}
	LinePoint()
	{

	}
};

class  FLineSegment
{
public:
	FLineSegment();
	FLineSegment(FVector2D a, FVector2D b);
	FLineSegment(FVector a, FVector b);
	FLineSegment(FVector a, FVector b, int i1, int i2);
	FLineSegment(FVector2D a, FVector2D b, int i1, int i2);
	FLineSegment(LinePoint a, LinePoint b);

	//�������߶εľ���
	float Distance(FVector2D point);
	bool isIntersect(FLineSegment& other);
	//�����߶�����ֱ�ߵĽ���
	FVector2D GetIntersection(FLineSegment other);
	FVector2D GetCenterPoint();
	//�ж��Ƿ���ƽ�е�
	bool isParallel(FLineSegment other);
	bool isInSegment(FVector2D other);
	bool isMyPoint(FVector2D);

public:
	LinePoint pointA;
	LinePoint pointB;
	int id;
};
