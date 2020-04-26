// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FPoloygon
{

public:
	FPoloygon(TArray<FVector2D> Plist);

	//�ж�һ�����Ƿ���������
	bool IsInPoloygon(FVector Plist);


	//Ѱ�Ҷ���ε������Բ��Բ��
	FVector GetCenterOfTheLargestInnerCircle(TArray<FVector> Points);
private:
	//Ѱ�Ҷ���ε������Բ��Բ��˽�ú������õ�ϵ��C
	FVector2D LICFindC(FVector2D A, FVector2D B, FVector2D Ori);

	//Ѱ�Ҷ���ε������Բ��Բ��˽�ú�������ԭ��
	FVector2D LICGetNewOri(FVector2D C, FVector2D Temp, float a);

	//Ѱ�Ҷ���ε������Բ��Բ��˽�ú������õ�ͼ�����������һ��
	TArray<FVector2D> LICGetInPoint(TArray<FVector >pointList);

	//Ѱ�Ҷ���ε������Բ��Բ��˽�ú�����Ѱ����С����
	void LICGetTwoShortestDistance(FVector2D Ori, TArray<FVector> mPoints, FVector2D& A, FVector2D& B);


private:

	TArray<FVector2D> PointLists;
};

namespace CK2Math
{
	//Ѱ�Ҷ�������
	FVector GetCenterOfGravityPoint(TArray<FVector> Points);


}