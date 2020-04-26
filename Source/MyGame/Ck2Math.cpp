// Fill out your copyright notice in the Description page of Project Settings.


#include "Ck2Math.h"
#include "Ck2Line.h"

float Ck2OneDimensional::GetMinX(TArray<FVector> plist)
{
	float minl = MAX_FLT;

	for (auto a : plist)
	{
		if (a.X < minl)minl = a.X;
	}
	return minl;
}

float Ck2OneDimensional::GetMinX(TArray<FVector2D> plist)
{
	float minl = MAX_FLT;

	for (auto a : plist)
	{
		if (a.X < minl)minl = a.X;
	}
	return minl;
}

float Ck2OneDimensional::GetMaX(TArray<FVector> plist)
{
	float minr = -100000;
	for (auto a : plist)
	{
		if (a.X > minr)minr = a.X;
	}
	return minr;
}

float Ck2OneDimensional::GetMaX(TArray<FVector2D> plist)
{
	float minr = -100000;
	for (auto a : plist)
	{
		if (a.X > minr)minr = a.X;
	}
	return minr;
}

float Ck2OneDimensional::GetMinZ(TArray<FVector> plist)
{
	float minl = 1000000;

	for (auto a : plist)
	{
		if (a.Z < minl)minl = a.Z;
	}
	return minl;
}

float Ck2OneDimensional::GetMaZ(TArray<FVector> plist)
{
	float minr = -100000;
	for (auto a : plist)
	{
		if (a.Z > minr)minr = a.Z;
	}
	return minr;
}

float Ck2OneDimensional::GetMinY(TArray<FVector> plist)
{
	float minl = 1000000;

	for (auto a : plist)
	{
		if (a.Y < minl)minl = a.Y;
	}
	return minl;
}

float Ck2OneDimensional::GetMinY(TArray<FVector2D> plist)
{
	float minl = 1000000;

	for (auto a : plist)
	{
		if (a.Y < minl)minl = a.Y;
	}
	return minl;
}

float Ck2OneDimensional::GetMaY(TArray<FVector> plist)
{
	float minr = -100000;
	for (auto a : plist)
	{
		if (a.Y > minr)minr = a.Y;
	}
	return minr;
}

float Ck2OneDimensional::GetMaY(TArray<FVector2D> plist)
{
	float minr = -100000;
	for (auto a : plist)
	{
		if (a.Y > minr)minr = a.Y;
	}
	return minr;
}

TArray<FVector> Ck2OneDimensional::GetCoorNew(TArray<FVector> s, int XYZ, float height)
{
	TArray<FVector> out;
	for (int i = 0; i != s.Num(); i++)
	{
		if (XYZ == 0)
		{
			out.Add(FVector(height, s[i].Y, s[i].Z));
		}
		else if (XYZ == 1)
		{
			out.Add(FVector(s[i].X, height, s[i].Z));
		}
		else
		{
			out.Add(FVector(s[i].X, s[i].Y, height));
		}
	}
	return out;
}

void Ck2OneDimensional::SetCoorNew(TArray<FVector>& s, int XYZ, float height)
{
	if (XYZ > 2 && XYZ < 0) return;
	TArray<FVector> out;
	for (int i = 0; i != s.Num(); i++)
	{
		if (XYZ == 0)
		{
			out.Add(FVector(height, s[i].Y, s[i].Z));
		}
		else if (XYZ == 1)
		{
			out.Add(FVector(s[i].X, height, s[i].Z));
		}
		else
		{
			out.Add(FVector(s[i].X, s[i].Y, height));
		}
	}
	s.Empty();
	s = out;
}

FVector Ck2OneDimensional::GetNormalWithList(const TArray<FVector>& pointList)
{
	//??????????????????????????0?????????

	FVector V1 = pointList[1] - pointList[0];
	FVector V2 = pointList[2] - pointList[0];

	//return FVector::CrossProduct(V2, V1);
	V1.Normalize();

	//??????????????
	for (int i = 2; i != pointList.Num(); i++)
	{
		V2 = pointList[i] - pointList[0];
		V2.Normalize();

		if (V1.Equals(V2, 0.01))
		{
			if ((i + 1) == pointList.Num())
			{
				return FVector(0, 0, 0);
			}
			continue;
		}
		else
		{
			break;
		}
	}
	auto res = FVector::CrossProduct(V2, V1);
	res.Normalize();
	return res;
}

bool Ck2OneDimensional::isCounterclockwise(const TArray<FVector>& plist)
{
	auto PreNode = plist[0];
	auto MiddleNode = plist[1];
	auto AfterNode = plist[2];
	if (PreNode.Z * (MiddleNode.X * AfterNode.Y - MiddleNode.Y * AfterNode.X) - MiddleNode.Z * (PreNode.X * AfterNode.Y - PreNode.Y * AfterNode.X) +
		AfterNode.Z * (PreNode.X * MiddleNode.Y - PreNode.Y * MiddleNode.X) > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

TArray<FVector> Ck2OneDimensional::GetArrayReverse(TArray<FVector> list)
{
	auto num = list.Num();
	TArray<FVector> s;
	s.Empty();
	for (int i = 0; i != num; i++)
	{
		s.Add(list[num - i - 1]);
	}
	return s;
}

TArray<int> Ck2OneDimensional::GetArrayReverse(TArray<int> list)
{
	auto num = list.Num();
	TArray<int> s;
	s.Empty();
	for (int i = 0; i != num; i++)
	{
		s.Add(list[num - i - 1]);
	}

	return s;
}

void Ck2OneDimensional::SetArrayReverse(TArray<FVector2D>& list)
{
	auto num = list.Num();

	TArray<FVector2D> s;
	s.Empty();
	for (int i = 0; i != num; i++)
	{
		s.Add(list[num - i - 1]);
	}
	list = s;

}

void Ck2OneDimensional::SetArrayReverse(TArray<FVector>& list)
{
	auto num = list.Num();
	TArray<FVector> s;
	s.Empty();
	for (int i = 0; i != num; i++)
	{
		s.Add(list[num - i - 1]);
	}
	list = s;
}

void Ck2OneDimensional::SetArrayReverse(TArray<int>& list)
{
	auto num = list.Num();
	TArray<int> s;
	s.Empty();
	for (int i = 0; i != num; i++)
	{
		s.Add(list[num - i - 1]);
	}
	list = s;
}

bool Ck2OneDimensional::IsHoleOutEdge(TArray<FVector>ss, TArray<FVector>plist)
{
	//???????plist???????Сx
	float MinX = GetMinX(plist);
	float MaxX = GetMaX(plist);
	float MinY = GetMinY(plist);
	float MaxY = GetMaY(plist);
	float MinZ = GetMinZ(plist);
	float MaxZ = GetMaZ(plist);
	for (int j = 0; j != ss.Num(); j++)
	{
		if (ss[j].X <= MinX)return true;
		if (ss[j].X >= MaxX)return true;
		if (ss[j].Z <= MinZ)return true;
		if (ss[j].Z >= MaxZ)return true;
	}
	return false;
}

bool Ck2OneDimensional::IsIntersect(TArray<FVector>ss, TArray<FVector>plist)
{
	return true;
}

bool Ck2OneDimensional::isOfRegions(TArray<FVector>ss, TArray<FVector>plist)
{
	//????Y????
	if (IsHoleOutEdge(ss, plist))
		return false;
	else
	{
		return true;
	}
	return false;
}

void Ck2OneDimensional::MovePlist(TArray<FVector>ss, FVector v)
{
	for (auto& a : ss)
	{
		a = a + v;
	}
}

bool Ck2OneDimensional::isParallel(FVector2D A, FVector2D B, FVector2D C)
{
	FVector2D Line1 = A - B;
	FVector2D Line2 = C - B;
	if (Line1.Equals(FVector2D::ZeroVector))
		return true;
	if (Line1.X == 0)
	{
		float aa = Line2.Y / Line1.Y;
		if (Line2.X - aa * Line1.X<0.001 || Line2.X - aa * Line1.X >-0.001)
			return  true;
		else
		{
			return false;
		}
	}

	//如果Line1的x不为0的话
	else
	{
		float aa = Line2.X / Line1.X;
		auto ss = Line2.Y - aa * Line1.Y;
		if ((ss < 0.001 && ss>0) || (ss > -0.001 && ss < 0))
			return  true;
		else
		{
			return false;
		}
	}
	return true;
}

bool Ck2OneDimensional::isParallel(FVector A, FVector B, FVector C)
{
	FVector Line1 = A - B;
	FVector Line2 = C - B;
	if (Line1.Equals(FVector::ZeroVector))
		return true;

	//确定一个系数
	float xi = 0;
	if (Line1.X != 0)
	{
		xi = Line2.X / Line1.X;
		if (xi * Line1.Y == Line2.Y && xi * Line1.Z == Line2.Z)
			return true;
		else
		{
			return false;
		}
	}
	else if (Line1.Y != 0)
	{
		xi = Line2.Y / Line1.Y;
		if (xi * Line1.Z == Line2.Z && xi * Line1.X == Line2.X)
			return true;
		else
		{
			return false;
		}
	}
	else
	{
		xi = Line2.Z / Line1.Z;
		if (xi * Line1.Y == Line2.Y && xi * Line1.X == Line2.X)
			return true;
		else
		{
			return false;
		}
	}

	return true;
}

TArray<FVector2D> Ck2OneDimensional::TransformF3T2(TArray<FVector>ss, int t)
{
	TArray<FVector2D> out;
	for (auto& a : ss)
	{
		if (t == 0)
		{
			out.Add(FVector2D(a.Y, a.Z));
		}
		if (t == 1)
		{
			out.Add(FVector2D(a.X, a.Z));
		}
		if (t == 2)
		{
			out.Add(FVector2D(a.X, a.Y));
		}

	}
	return out;
}

FVector Ck2OneDimensional::GetCenterOfGravityPoint(TArray<FVector> mPoints)
{
	double area = 0.0;//多边形面积
	double Gx = 0.0, Gy = 0.0;// 重心的x、y

	for (int i = 1; i <= mPoints.Num(); i++)
	{
		double iLat = mPoints[(i % mPoints.Num())].X;
		double iLng = mPoints[(i % mPoints.Num())].Y;
		double nextLat = mPoints[(i - 1)].X;
		double nextLng = mPoints[(i - 1)].Y;
		double temp = (iLat * nextLng - iLng * nextLat) / 2.0;
		area += temp;
		Gx += temp * (iLat + nextLat) / 3.0;
		Gy += temp * (iLng + nextLng) / 3.0;
	}
	Gx = Gx / area;
	Gy = Gy / area;
	return  FVector(Gx, Gy, mPoints[0].Z);
}

//

FVector2D Ck2OneDimensional::InLine_FindC(FVector2D A, FVector2D B, FVector2D Ori)
{
	//如果三点共线的话，我们取A点作为参考点
	if (isParallel(A, B, Ori))
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

FVector2D Ck2OneDimensional::InLine_GetNewOri(FVector2D C, FVector2D Temp, float a)
{
	float tt = FMath::Sqrt(FMath::Pow(C.X - Temp.X, 2) + FMath::Pow(C.Y - Temp.Y, 2));
	float xxx = Temp.X + a * (Temp.X - C.X) / tt;
	float yyy = Temp.Y + a * (Temp.Y - C.Y) / tt;

	return FVector2D(xxx, yyy);
}

void Ck2OneDimensional::InLineGetTwoShortestDistance(FVector2D Ori, TArray<FVector> mPoints, FVector2D& A, FVector2D& B)
{
	float Arr = 100000000;
	float Brr = 100000000 - 1;
	for (int j = 0; j != mPoints.Num(); j++)
	{
		//得到我们需要的线段,
		FVector2D AA = FVector2D(mPoints[j].X, mPoints[j].Y);
		FVector2D BB = FVector2D(mPoints[(j + 1) % mPoints.Num()].X, mPoints[(j + 1) % mPoints.Num()].Y);
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

TArray<FVector> Ck2OneDimensional::SetNoSamePoint(TArray<FVector> plist)
{
	TArray<FVector> out;
	out.Add(plist[0]);
	for (int i = 0; i != plist.Num(); i++)
	{
		bool isEqual = false;
		for (int j = 0; j != out.Num(); j++)
		{
			if (out[j].Equals(plist[i]))
			{
				isEqual = true;
				break;
			}
		}
		if (!isEqual)
			out.Add(plist[i]);
	}
	return out;
}

TArray<FVector2D> Ck2OneDimensional::SetNoSamePoint(TArray<FVector2D> plist)
{
	TArray<FVector2D> out;
	out.Add(plist[0]);
	for (int i = 0; i != plist.Num(); i++)
	{
		bool isEqual = false;
		for (int j = 0; j != out.Num(); j++)
		{
			if (out[j].Equals(plist[i]))
			{
				isEqual = true;
				break;
			}
		}
		if (!isEqual)
			out.Add(plist[i]);
	}
	return out;
}

FVector Ck2OneDimensional::GetCenterOfTheLargestInnerCircle(TArray<FVector> Points)
{

	float a = 20;
	const float Mina = 5;
	float RR = 0;
	float outR = 0;
	FVector2D out;

	//确定一个初定的圆心Temp
	auto mPoints = SetNoSamePoint(Points);
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
		plist = GetInPoint(mPoints);
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

			InLineGetTwoShortestDistance(Temp, mPoints, A, B);

			//并且得到他们之间的距离
			float R1 = FVector2D::Distance(A, Temp);
			float R2 = FVector2D::Distance(B, Temp);

			//通过AB，找到最终C的点,并且还要初定圆心
			FVector2D C = InLine_FindC(A, B, Temp);

			//根据参考点C和初定圆心的位置，我们得到新的圆心的位置,并且还有步长因子
			FVector2D NewOri = InLine_GetNewOri(C, Temp, a);

			//求出NewOri后，进行判断

			FVector2D NewA;
			FVector2D NewB;
			InLineGetTwoShortestDistance(NewOri, mPoints, NewA, NewB);

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

bool Ck2OneDimensional::IsHas(TArray<int>A, TArray<TArray<int>>B)
{
	for (int i = 0; i != B.Num(); i++)
	{
		bool IsHas = true;
		if (A.Num() == B[i].Num())
		{
			A.Sort();
			B[i].Sort();
			for (int j = 0; j != A.Num(); j++)
			{
				if (A[j] == B[i][j])
					continue;
				else
				{
					IsHas = false;
				}
			}
			if (IsHas)
				return true;
		}
	}

	return false;
}

bool Ck2OneDimensional::isInPolygon(TArray<FVector2D> plist, FVector2D point)
{
	//做一条向上的射线，如果和所有的边的交点为偶数个，在外部，基数个，在内部
	TArray<FVector2D>Has;
	int num = 0;
	for (int i = 0; i != plist.Num(); i++)
	{
		FLineSegment xian(plist[i], plist[(i + 1) % plist.Num()]);
		if (FMath::Min(xian.pointA.MPosition.X, xian.pointB.MPosition.X) <= point.X && FMath::Max(xian.pointA.MPosition.X, xian.pointB.MPosition.X) >= point.X)
		{
			FLineSegment popo(point, point + FVector2D(0, 10));
			if (xian.pointA.MPosition.X == xian.pointB.MPosition.X)
				continue;

			auto inter = xian.GetIntersection(popo);

			/*if (Has.Find(inter) != INDEX_NONE)
				continue;*/
			if (inter.Y >= point.Y)
			{
				//如果在直线和左端点相等
				if (FMath::Min(xian.pointA.MPosition.X, xian.pointB.MPosition.X) == point.X)
					continue;
				Has.Add(inter);
				num++;
			}
		}
	}

	//如果交点个数是偶数个
	if (num % 2 == 0)
	{
		return false;
	}
	return true;
}

bool Ck2OneDimensional::RemoveCollinear(TArray<FVector>& plist)
{
	int len = plist.Num();
	if (len <= 2)return false;
	int a, b, c;
	TArray<int> deleteindex;//需要删除的点
	FVector ab;
	FVector bc;
	for (int i = 0; i < len + 2; i++)
	{
		a = i % len;
		b = (a + 1) % len;
		c = (a + 2) % len;
		ab = plist[b] - plist[a];
		bc = plist[c] - plist[b];
		if (ab.Size() <= 0.001f)
		{
			//ab共点
			deleteindex.AddUnique(b);
		}
		if (bc.Size() <= 0.001f)
		{
			//bc共点
			deleteindex.AddUnique(c);
		}
		if (ab.GetSafeNormal().Equals(bc.GetSafeNormal()))
		{
			//abc共线
			deleteindex.AddUnique(b);
		}
	}

	if (deleteindex.Num() >= 1)
	{
		//有顶点需要移除
		TArray<FVector> buffer = plist;
		plist.Empty();
		//
		for (int i = 0; i < len; i++)
		{
			if (!deleteindex.Contains(i))
			{
				plist.Add(buffer[i]);
			}
		}
		return plist.Num() >= 3;
	}
	return true;

	//首先删除掉所有的相同点
	auto ss = SetNoSamePoint(plist);
	if (ss.Num() < 3)
		return false;
	plist.Empty();
	plist.Add(ss[0]);
	for (int i = 1; i != ss.Num(); i++)
	{
		if (i == ss.Num() - 1)
		{
			if (!isParallel(ss[i - 1], ss[i], ss[0]))
			{
				plist.Add(ss[i]);
			}
			if (isParallel(plist[plist.Num() - 1], plist[0], plist[1]))
				plist.RemoveAt(0);
			break;
		}

		//如果这三个点是平行的
		if (isParallel(ss[i - 1], ss[i], ss[i + 1]))
		{
		}
		else
		{
			plist.Add(ss[i]);
		}
	}
	return true;
}

bool Ck2OneDimensional::ToLeftTest(FVector2D A, FVector2D B, FVector2D C)
{
	//注意，现在所有的都是点。而不是向量
	if (Ck2OneDimensional::HangLieShi(FVector(A.X, B.X, C.X), FVector(A.Y, B.Y, C.Y), FVector(1, 1, 1)) > 0)
	{
		return true;
	}

	return false;
}

TArray<FVector2D> Ck2OneDimensional::GetInPoint(TArray<FVector >pointList)
{
	return TArray<FVector2D>();
}

bool Ck2OneDimensional::ToLeftTest(FVector A, FVector B, FVector C)
{
	//注意，现在所有的都是点。而不是向量
	if (A.X == B.X && B.X == C.X)
	{
		return ToLeftTest(FVector2D(A.Y, A.Z), FVector2D(B.Y, B.Z), FVector2D(C.Y, C.Z));
	}
	if (A.Y == B.Y && B.Y == C.Y)
	{
		return ToLeftTest(FVector2D(A.X, A.Z), FVector2D(B.X, B.Z), FVector2D(C.X, C.Z));

	}
	if (A.Z == B.Z && B.Z == C.Z)
	{
		return ToLeftTest(FVector2D(A.X, A.Y), FVector2D(B.X, B.Y), FVector2D(C.X, C.Y));

	}
	return false;
}

float Ck2OneDimensional::HangLieShi(FVector A, FVector B, FVector C)
{
	auto a1 = A.X;
	auto a2 = A.Y;
	auto a3 = A.Z;
	auto b1 = B.X;
	auto b2 = B.Y;
	auto b3 = B.Z;
	auto c1 = C.X;
	auto c2 = C.Y;
	auto c3 = C.Z;
	return a1 * (b2 * c3 - b3 * c2) - a2 * (b1 * c3 - b3 * c1) + a3 * (b1 * c2 - b2 * c1);
}





bool DMThreeDimensional::IsInRange(FVector TEM, TArray<FVector> ranges)
{
	if (TEM.X< Ck2OneDimensional::GetMinX(ranges) || TEM.X>Ck2OneDimensional::GetMaX(ranges))
		return false;
	if (TEM.Y< Ck2OneDimensional::GetMinY(ranges) || TEM.Y>Ck2OneDimensional::GetMaY(ranges))
		return false;
	if (TEM.Z< Ck2OneDimensional::GetMinZ(ranges) || TEM.Z>Ck2OneDimensional::GetMaZ(ranges))
		return false;
	return true;
}

void DMThreeDimensional::TransformInPlist(FTransform T, TArray<FVector>& Plist)
{
	for (auto& vex : Plist)
	{
		vex = T.TransformPosition(vex);
	}

}

void DMThreeDimensional::TransformInPlist(FTransform T, TArray<FVector2D>& Plist)
{
	for (auto& vex : Plist)
	{
		FVector Temp = FVector(vex.X, vex.Y, 0);
		vex = FVector2D(T.TransformPosition(Temp));
	}
}
