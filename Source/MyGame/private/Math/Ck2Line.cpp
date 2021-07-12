#include "Math/Ck2Line.h"
#include "Math/Ck2Math.h"


FLineSegment::FLineSegment(FVector2D a, FVector2D b)
{
	pointA.MPosition = a;
	pointB.MPosition = b;
}

FLineSegment::FLineSegment(FVector a, FVector b, int i1, int i2)
{
	pointA.MPosition = FVector2D(a[0], a[1]);
	pointB.MPosition = FVector2D(b[0], b[1]);
	pointA.Pointid = i1;
	pointB.Pointid = i2;
}

FLineSegment::FLineSegment(FVector2D a, FVector2D b, int i1, int i2)
{
	pointA.MPosition = a;
	pointB.MPosition = b;
	pointA.Pointid = i1;
	pointB.Pointid = i2;
}

FLineSegment::FLineSegment(FVector a, FVector b)
{
	pointA.MPosition = FVector2D(a[0], a[1]);
	pointB.MPosition = FVector2D(b[0], b[1]);
}

FLineSegment::FLineSegment()
{
}

FLineSegment::FLineSegment(LinePoint a, LinePoint b)
{
	pointA = a;
	pointB = b;
}

float FLineSegment::Distance(FVector2D point)
{
	//首先判定我们的点的垂线和线段是否相交，如果相交的话，直接取得距离，如果不相交的话，取两个点距离的最小值
//	point.()

	//确定直线的方程，

	return 0;
}


bool FLineSegment::isIntersect(FLineSegment& other)
{
	if ((Ck2OneDimensional::ToLeftTest(pointA.MPosition, pointB.MPosition, other.pointA.MPosition) ^
		Ck2OneDimensional::ToLeftTest(pointA.MPosition, pointB.MPosition, other.pointB.MPosition)) &&
		(Ck2OneDimensional::ToLeftTest(other.pointA.MPosition, other.pointB.MPosition, pointB.MPosition) ^
			Ck2OneDimensional::ToLeftTest(other.pointA.MPosition, other.pointB.MPosition, pointA.MPosition)))
	{
		return true;
	}
	return false;

}

FVector2D FLineSegment::GetIntersection(FLineSegment other)
{
	{
		//对于本体的线段
		float a1 = pointA.MPosition.Y - pointB.MPosition.Y;
		float b1 = pointB.MPosition.X - pointA.MPosition.X;
		float c1 = pointA.MPosition.X * pointB.MPosition.Y - pointB.MPosition.X * pointA.MPosition.Y;

		//对于other
		float a3 = other.pointA.MPosition.Y - other.pointB.MPosition.Y;
		float b3 = other.pointB.MPosition.X - other.pointA.MPosition.X;
		float c3 = other.pointA.MPosition.X * other.pointB.MPosition.Y - other.pointB.MPosition.X * other.pointA.MPosition.Y;
		float D = a1 * b3 - a3 * b1;
		float x = (b1 * c3 - b3 * c1) / D;
		float y = (a3 * c1 - a1 * c3) / D;
		return FVector2D(x, y);
	}
}

FVector2D FLineSegment::GetCenterPoint()
{
	return (pointA.MPosition + pointB.MPosition) / 2;
}

bool FLineSegment::isParallel(FLineSegment other)
{
	//对于本体的线段
	float a1 = pointA.MPosition.Y - pointB.MPosition.Y;
	float b1 = pointA.MPosition.X - pointB.MPosition.X;
	float c1 = pointA.MPosition.X * pointB.MPosition.Y - pointB.MPosition.X * pointA.MPosition.Y;

	//对于other
	float a3 = other.pointA.MPosition.Y - other.pointB.MPosition.Y;
	float b3 = other.pointA.MPosition.X - other.pointB.MPosition.X;
	float c3 = other.pointA.MPosition.X * other.pointB.MPosition.Y - other.pointB.MPosition.X * other.pointA.MPosition.Y;
	float D = a1 * b3 - a3 * b1;
	if (D == 0)
		return true;
	return false;
}

bool FLineSegment::isInSegment(FVector2D other)
{
	if (other.X > FMath::Max(pointA.MPosition.X, pointB.MPosition.X) + 0.1
		|| other.Y > FMath::Max(pointA.MPosition.Y, pointB.MPosition.Y) + 0.1
		|| other.X < FMath::Min(pointA.MPosition.X, pointB.MPosition.X) - 0.1
		|| other.Y < FMath::Min(pointA.MPosition.Y, pointB.MPosition.Y) - 0.1)
		return false;
	return true;
}

bool FLineSegment::isMyPoint(FVector2D mpoint)
{
	//
	FLineSegment other(mpoint, pointA.MPosition);

	//如果这都平行的话，那铁定处于这条直线上
	if (isParallel(other))
	{
		if (mpoint.X >= FMath::Min(pointA.MPosition.X, pointB.MPosition.X) && mpoint.X <= FMath::Max(pointA.MPosition.X, pointB.MPosition.X))
		{
			return true;
		}
	}
	return false;
}