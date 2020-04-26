// Fill out your copyright notice in the Description page of Project Settings.


#include "Geometry.h"
#include "Ck2Line.h"
#include "Ck2Math.h"



FVector CK2Math::GetCenterOfGravityPoint(TArray<FVector> Points)
{
	double area = 0.0;//多边形面积
	double Gx = 0.0, Gy = 0.0;// 重心的x、y

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

	//确定一个初定的圆心Temp
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
		//首先，将所有的点进行遍历查找
		//判断点是否在多边形内
		a = 20;
		int num = 0;
		while (a > Mina)
		{
			//参考点A和B
			FVector2D A;
			FVector2D B;

			//寻找初定圆心和所有的边最小的两个值的交点，填充到AB里面
			if (Temp.X > 10000 || Temp.X < -10000 || num>20)
			{
				Temp = FVector2D::ZeroVector;
				RR = 0;
				break;
			}

			LICGetTwoShortestDistance(Temp, mPoints, A, B);

			//并且得到他们之间的距离
			float R1 = FVector2D::Distance(A, Temp);
			float R2 = FVector2D::Distance(B, Temp);

			//通过AB，找到最终C的点,并且还要初定圆心
			FVector2D C = LICFindC(A, B, Temp);

			//根据参考点C和初定圆心的位置，我们得到新的圆心的位置,并且还有步长因子
			FVector2D NewOri = LICGetNewOri(C, Temp, a);

			//求出NewOri后，进行判断

			FVector2D NewA;
			FVector2D NewB;
			LICGetTwoShortestDistance(NewOri, mPoints, NewA, NewB);

			//并且得到他们之间的距离
			float NR1 = FVector2D::Distance(NewA, NewOri);
			float NR2 = FVector2D::Distance(NewB, NewOri);

			//如果我们的新值比之前的大
			RR = FMath::Max(FMath::Min(R1, R2), FMath::Min(NR1, NR2));
			if (FMath::Min(R1, R2) < FMath::Min(NR1, NR2))
			{
				//那么我们就从头开始重新计算
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
	//如果三点共线的话，我们取A点作为参考点
	if (Ck2OneDimensional::isParallel(A, B, Ori))
	{
		return A;
	}

	//得到R1.R2
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
		//得到我们需要的线段,
		FVector2D AA = FVector2D(Points[j].X, Points[j].Y);
		FVector2D BB = FVector2D(Points[(j + 1) % Points.Num()].X, Points[(j + 1) % Points.Num()].Y);
		auto tem = AA - BB;
		FLineSegment other(AA, BB);

		//他们之间的垂线
		FLineSegment UU(Ori, Ori + FVector2D(-tem.Y, tem.X));

		//垂线的交点
		FVector2D inter = UU.GetIntersection(other);

		//如果我们的交点在线段内的话
		float Rs = 0;
		if (other.isInSegment(inter))
		{
			Rs = FVector2D::Distance(inter, Ori);
		}//如果不是的话
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

		//对于每一条线段，进行距离判定
	}
}
