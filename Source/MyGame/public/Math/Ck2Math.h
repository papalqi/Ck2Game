// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


namespace  Ck2OneDimensional
{

	//�õ���СX
	float  GetMinX(TArray<FVector> plist);
	float  GetMinX(TArray<FVector2D> plist);
	//�õ����X
	float   GetMaX(TArray<FVector> plist);
	float   GetMaX(TArray<FVector2D> plist);
	//�õ���СZ
	float  GetMinZ(TArray<FVector> plist);
	//�õ����Z
	float  GetMaZ(TArray<FVector> plist);
	//�õ���СY
	float  GetMinY(TArray<FVector> plist);
	float  GetMinY(TArray<FVector2D> plist);
	//�õ����Y
	float  GetMaY(TArray<FVector> plist);
	float  GetMaY(TArray<FVector2D> plist);

	//�������������е�XYZ
	TArray<FVector>  GetCoorNew(TArray<FVector> s, int XYZ, float height);
	//�������������е�XYZֵ��
	void  SetCoorNew(TArray<FVector>& s, int XYZ, float height);
	//�õ�����ǰ����ķ��߷���
	FVector  GetNormalWithList(const TArray<FVector>& pointList);
	//�ж��Ƿ�����ʱ��
	bool  isCounterclockwise(const TArray<FVector>& plist);
	//�����з�ת
	TArray<FVector>GetArrayReverse(TArray<FVector> list);
	void SetArrayReverse(TArray<FVector2D>& list);
	TArray<int>GetArrayReverse(TArray<int> list);
	void SetArrayReverse(TArray<FVector>& list);
	void SetArrayReverse(TArray<int>& list);
	//�Ƿ�����
	bool  IsHoleOutEdge(TArray<FVector>ss, TArray<FVector>plist);
	//�Ƿ��ཻ
	bool IsIntersect(TArray<FVector>ss, TArray<FVector>plist);
	//�Ƿ����
	bool  isOfRegions(TArray<FVector>ss, TArray<FVector>plist);
	//�����ƶ�
	void MovePlist(TArray<FVector>ss, FVector v);
	//�����Ƿ�ƽ��
	bool isParallel(FVector2D A, FVector2D B, FVector2D C);
	bool isParallel(FVector A, FVector  B, FVector C);
	TArray<FVector2D>TransformF3T2(TArray<FVector>ss, int t);
	//Ѱ������
	FVector GetCenterOfGravityPoint(TArray<FVector> mPoints);

	//�õ���С����
	void InLineGetTwoShortestDistance(FVector2D Ori, TArray<FVector> mPoints, FVector2D& A, FVector2D& B);
	//�Ƴ���ͬ��
	TArray<FVector> SetNoSamePoint(TArray<FVector> plist);
	//�Ƴ���ͬ��
	TArray<FVector2D> SetNoSamePoint(TArray<FVector2D> plist);
	//Ѱ�Ҷ���ε������Բ��Բ��
	FVector GetCenterOfTheLargestInnerCircle(TArray<FVector> mPoints);
	//�Ƿ����
	bool IsEqual(TArray<int>A, TArray<int>B);
	//�Ƿ����
	bool IsHas(TArray<int>A, TArray<TArray<int>>B);
	//�Ƿ���ͼ����,Ӧ���ǲ������ڱ��ϵ����
	bool isInPolygon(TArray<FVector2D>, FVector2D);

	//��ϴ���� ȥ�����߻��ص��ĵ�
	bool RemoveCollinear(TArray<FVector>& plist);

	//���Ƚ��м򵥵�ӳ�䣨ƽ���������ᣩ��Ȼ�󼰽���ToLeftTest
	bool ToLeftTest(FVector A, FVector B, FVector C);
	//��������ʽ
	float HangLieShi(FVector A, FVector B, FVector C);
	//�ж��ж�C���Ƿ�����AB�����߶ε���ࡣ
	bool ToLeftTest(FVector2D A, FVector2D B, FVector2D C);
	//�õ�ͼ�����������һ��


	TArray<FVector2D> GetInPoint(TArray<FVector >pointList);

	//inline_�õ�ϵ��C
	FVector2D InLine_FindC(FVector2D A, FVector2D B, FVector2D Ori);
	//inline_�Ķ���ԭ��
	FVector2D InLine_GetNewOri(FVector2D C, FVector2D Temp, float a);

};

namespace  DMThreeDimensional
{
	bool IsInRange(FVector TEM, TArray<FVector> ranges);
	void TransformInPlist(FTransform T, TArray<FVector>& Plist);
	void TransformInPlist(FTransform T, TArray<FVector2D>& Plist);

};