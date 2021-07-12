// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


namespace  Ck2OneDimensional
{

	//得到最小X
	float  GetMinX(TArray<FVector> plist);
	float  GetMinX(TArray<FVector2D> plist);
	//得到最大X
	float   GetMaX(TArray<FVector> plist);
	float   GetMaX(TArray<FVector2D> plist);
	//得到最小Z
	float  GetMinZ(TArray<FVector> plist);
	//得到最大Z
	float  GetMaZ(TArray<FVector> plist);
	//得到最小Y
	float  GetMinY(TArray<FVector> plist);
	float  GetMinY(TArray<FVector2D> plist);
	//得到最大Y
	float  GetMaY(TArray<FVector> plist);
	float  GetMaY(TArray<FVector2D> plist);

	//整体设置序列中的XYZ
	TArray<FVector>  GetCoorNew(TArray<FVector> s, int XYZ, float height);
	//整体设置序列中的XYZ值。
	void  SetCoorNew(TArray<FVector>& s, int XYZ, float height);
	//得到序列前三点的法线方向
	FVector  GetNormalWithList(const TArray<FVector>& pointList);
	//判断是否是逆时针
	bool  isCounterclockwise(const TArray<FVector>& plist);
	//将序列反转
	TArray<FVector>GetArrayReverse(TArray<FVector> list);
	void SetArrayReverse(TArray<FVector2D>& list);
	TArray<int>GetArrayReverse(TArray<int> list);
	void SetArrayReverse(TArray<FVector>& list);
	void SetArrayReverse(TArray<int>& list);
	//是否相离
	bool  IsHoleOutEdge(TArray<FVector>ss, TArray<FVector>plist);
	//是否相交
	bool IsIntersect(TArray<FVector>ss, TArray<FVector>plist);
	//是否包含
	bool  isOfRegions(TArray<FVector>ss, TArray<FVector>plist);
	//整体移动
	void MovePlist(TArray<FVector>ss, FVector v);
	//三点是否平行
	bool isParallel(FVector2D A, FVector2D B, FVector2D C);
	bool isParallel(FVector A, FVector  B, FVector C);
	TArray<FVector2D>TransformF3T2(TArray<FVector>ss, int t);
	//寻找重心
	FVector GetCenterOfGravityPoint(TArray<FVector> mPoints);

	//得到最小长度
	void InLineGetTwoShortestDistance(FVector2D Ori, TArray<FVector> mPoints, FVector2D& A, FVector2D& B);
	//移除相同点
	TArray<FVector> SetNoSamePoint(TArray<FVector> plist);
	//移除相同点
	TArray<FVector2D> SetNoSamePoint(TArray<FVector2D> plist);
	//寻找多边形的最大内圆的圆心
	FVector GetCenterOfTheLargestInnerCircle(TArray<FVector> mPoints);
	//是否相等
	bool IsEqual(TArray<int>A, TArray<int>B);
	//是否包含
	bool IsHas(TArray<int>A, TArray<TArray<int>>B);
	//是否在图形内,应该是不包括在边上的情况
	bool isInPolygon(TArray<FVector2D>, FVector2D);

	//清洗顶点 去除共线或重叠的点
	bool RemoveCollinear(TArray<FVector>& plist);

	//首先进行简单的映射（平行于坐标轴），然后及进行ToLeftTest
	bool ToLeftTest(FVector A, FVector B, FVector C);
	//计算行列式
	float HangLieShi(FVector A, FVector B, FVector C);
	//判断判断C点是否是在AB所在线段的左侧。
	bool ToLeftTest(FVector2D A, FVector2D B, FVector2D C);
	//得到图形里面的任意一点


	TArray<FVector2D> GetInPoint(TArray<FVector >pointList);

	//inline_得到系数C
	FVector2D InLine_FindC(FVector2D A, FVector2D B, FVector2D Ori);
	//inline_的都新原点
	FVector2D InLine_GetNewOri(FVector2D C, FVector2D Temp, float a);

};

namespace  DMThreeDimensional
{
	bool IsInRange(FVector TEM, TArray<FVector> ranges);
	void TransformInPlist(FTransform T, TArray<FVector>& Plist);
	void TransformInPlist(FTransform T, TArray<FVector2D>& Plist);

};