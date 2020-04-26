// Fill out your copyright notice in the Description page of Project Settings.


#include "Geometry.h"
#include "Ck2Line.h"
#include "Ck2Math.h"



FVector CK2Math::GetCenterOfGravityPoint(TArray<FVector> Points)
{
	double area = 0.0;//��������
	double Gx = 0.0, Gy = 0.0;// ���ĵ�x��y

	for (int i = 1; i <= Points.Num(); i++)
	{
		double iLat = Points[(i % Points.Num())].X;
		double iLng = Points[(i % Points.Num())].Y;
		double nextLat = Points[(i - 1)].X;
		double nextLng = Points[(i - 1)].Y;
		double temp = (iLat * nextLng - iLng * nextLat) / 2.0;
		area += temp;
		Gx += temp * (iLat + nextLat) / 3.0;
		Gy += temp * (iLng + nextLng) / 3.0;
	}
	Gx = Gx / area;
	Gy = Gy / area;
	return  FVector(Gx, Gy, Points[0].Z);
}


FPoloygon::FPoloygon(TArray<FVector2D> Plist)
{
	PointLists = Plist;
}

bool FPoloygon::IsInPoloygon(FVector Plist)
{
	if (Ck2OneDimensional::isInPolygon(PointLists, FVector2D(Plist)))
	{
		return true;

	}
	return false;
}

FVector FPoloygon::GetCenterOfTheLargestInnerCircle(TArray<FVector> Points)
{
	float a = 20;
	const float Mina = 5;
	float RR = 0;
	float outR = 0;
	FVector2D out;

	//ȷ��һ��������Բ��Temp
	auto mPoints = Ck2OneDimensional::SetNoSamePoint(Points);
	TArray<FVector2D> plist;
	if (mPoints.Num() == 3)
	{
		auto Temp = FVector2D(mPoints[0].X, mPoints[0].Y) +
			(FVector2D(mPoints[2].X, mPoints[2].Y) - FVector2D(mPoints[0].X, mPoints[0].Y)) * 0.1
			+ (FVector2D(mPoints[1].X, mPoints[1].Y) - FVector2D(mPoints[0].X, mPoints[0].Y)) * 0.2;
		plist.Add(Temp);
	}
	else
	{
		plist = LICGetInPoint(mPoints);
		if (plist.Num() == 0)
			return FVector::ZeroVector;
	}

	for (auto Temp : plist)
	{
		//���ȣ������еĵ���б�������
		//�жϵ��Ƿ��ڶ������
		a = 20;
		int num = 0;
		while (a > Mina)
		{
			//�ο���A��B
			FVector2D A;
			FVector2D B;

			//Ѱ�ҳ���Բ�ĺ����еı���С������ֵ�Ľ��㣬��䵽AB����
			if (Temp.X > 10000 || Temp.X < -10000 || num>20)
			{
				Temp = FVector2D::ZeroVector;
				RR = 0;
				break;
			}

			LICGetTwoShortestDistance(Temp, mPoints, A, B);

			//���ҵõ�����֮��ľ���
			float R1 = FVector2D::Distance(A, Temp);
			float R2 = FVector2D::Distance(B, Temp);

			//ͨ��AB���ҵ�����C�ĵ�,���һ�Ҫ����Բ��
			FVector2D C = LICFindC(A, B, Temp);

			//���ݲο���C�ͳ���Բ�ĵ�λ�ã����ǵõ��µ�Բ�ĵ�λ��,���һ��в�������
			FVector2D NewOri = LICGetNewOri(C, Temp, a);

			//���NewOri�󣬽����ж�

			FVector2D NewA;
			FVector2D NewB;
			LICGetTwoShortestDistance(NewOri, mPoints, NewA, NewB);

			//���ҵõ�����֮��ľ���
			float NR1 = FVector2D::Distance(NewA, NewOri);
			float NR2 = FVector2D::Distance(NewB, NewOri);

			//������ǵ���ֵ��֮ǰ�Ĵ�
			RR = FMath::Max(FMath::Min(R1, R2), FMath::Min(NR1, NR2));
			if (FMath::Min(R1, R2) < FMath::Min(NR1, NR2))
			{
				//��ô���Ǿʹ�ͷ��ʼ���¼���
				Temp = NewOri;
				num++;
				continue;
			}
			else
			{
				a = a * 0.618;
				continue;
			}
		}
		if (RR > outR)
		{
			outR = RR;
			out = Temp;
		}
	}

	return FVector(out.X, out.Y, mPoints[0].Z);
}

FVector2D FPoloygon::LICFindC(FVector2D A, FVector2D B, FVector2D Ori)
{
	//������㹲�ߵĻ�������ȡA����Ϊ�ο���
	if (Ck2OneDimensional::isParallel(A, B, Ori))
	{
		return A;
	}

	//�õ�R1.R2
	float R1 = FVector2D::Distance(A, Ori);
	float R2 = FVector2D::Distance(B, Ori);
	float xxx = A.X + (R1 / (R1 + R2)) * (B.X - A.X);
	float yyy = A.Y + (R1 / (R1 + R2)) * (B.Y - A.Y);
	return FVector2D(xxx, yyy);
}

FVector2D FPoloygon::LICGetNewOri(FVector2D C, FVector2D Temp, float a)
{
	float tt = FMath::Sqrt(FMath::Pow(C.X - Temp.X, 2) + FMath::Pow(C.Y - Temp.Y, 2));
	float xxx = Temp.X + a * (Temp.X - C.X) / tt;
	float yyy = Temp.Y + a * (Temp.Y - C.Y) / tt;

	return FVector2D(xxx, yyy);
}



TArray<FVector2D> FPoloygon::LICGetInPoint(TArray<FVector >pointList)
{

	return TArray<FVector2D>();


}

void FPoloygon::LICGetTwoShortestDistance(FVector2D Ori, TArray<FVector> Points, FVector2D& A, FVector2D& B)
{
	float Arr = 100000000;
	float Brr = 100000000 - 1;
	for (int j = 0; j != Points.Num(); j++)
	{
		//�õ�������Ҫ���߶�,
		FVector2D AA = FVector2D(Points[j].X, Points[j].Y);
		FVector2D BB = FVector2D(Points[(j + 1) % Points.Num()].X, Points[(j + 1) % Points.Num()].Y);
		auto tem = AA - BB;
		FLineSegment other(AA, BB);

		//����֮��Ĵ���
		FLineSegment UU(Ori, Ori + FVector2D(-tem.Y, tem.X));

		//���ߵĽ���
		FVector2D inter = UU.GetIntersection(other);

		//������ǵĽ������߶��ڵĻ�
		float Rs = 0;
		if (other.isInSegment(inter))
		{
			Rs = FVector2D::Distance(inter, Ori);
		}//������ǵĻ�
		else
		{
			Rs = FMath::Min(FVector2D::Distance(AA, Ori), FVector2D::Distance(BB, Ori));
			if (FVector2D::Distance(AA, Ori) > FVector2D::Distance(BB, Ori))
				inter = BB;
			else
			{
				inter = AA;
			}
		}
		if (Rs < FMath::Max(Arr, Brr))
		{
			if (Arr > Brr)
			{
				Arr = Rs;
				A = inter;
				continue;
			}
			else
			{
				Brr = Rs;
				B = inter;
				continue;
			}
		}

		//����ÿһ���߶Σ����о����ж�
	}
}
