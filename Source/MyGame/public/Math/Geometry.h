// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FPoloygon
{

public:
	FPoloygon(TArray<FVector2D> Plist);

	//判断一个点是否在区域里
	bool IsInPoloygon(FVector Plist);


	//寻找多边形的最大内圆的圆心
	FVector GetCenterOfTheLargestInnerCircle(TArray<FVector> Points);
private:
	//寻找多边形的最大内圆的圆心私用函数，得到系数C
	FVector2D LICFindC(FVector2D A, FVector2D B, FVector2D Ori);

	//寻找多边形的最大内圆的圆心私用函数，新原点
	FVector2D LICGetNewOri(FVector2D C, FVector2D Temp, float a);

	//寻找多边形的最大内圆的圆心私用函数，得到图形里面的任意一点
	TArray<FVector2D> LICGetInPoint(TArray<FVector >pointList);

	//寻找多边形的最大内圆的圆心私用函数，寻找最小距离
	void LICGetTwoShortestDistance(FVector2D Ori, TArray<FVector> mPoints, FVector2D& A, FVector2D& B);


private:

	TArray<FVector2D> PointLists;
};

namespace CK2Math
{
	//寻找队列重心
	FVector GetCenterOfGravityPoint(TArray<FVector> Points);


}