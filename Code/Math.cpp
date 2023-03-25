#include "Math.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>


Vector2d zeroVector2d()
{
    return {0.0f,0.0f};
}
Vector2d addVector2d(Vector2d a,Vector2d b)
{
    return {a.x + b.x, a.y + b.y};
}
Vector2d subsVector2d(Vector2d a,Vector2d b)
{
    return {a.x - b.x, a.y - b.y};
}
bool isEqualToVector2d(Vector2d a,Vector2d b)
{
    bool test = (a.x - b.x) >= -EPSILON  && (a.x - b.x) <= EPSILON && 
    (a.y - b.y) >= -EPSILON  && (a.y - b.y) <= EPSILON;

    return test;
}
Vector2d normalizeVector2d(Vector2d v)
{
    float length = lengthVector2d(v);
    if(length == 0.0f)
        return zeroVector2d();

    Vector2d vector;
    vector.x = v.x / length;
    vector.y = v.y / length;

    return vector;
}
Vector2d negateVector2d(Vector2d v)
{
    return {-v.x,-v.y};
}

float lengthSqVector2d(Vector2d v)
{
    return (v.x*v.x + v.y*v.y);
}
float lengthVector2d(Vector2d v)
{
    return sqrtf(lengthSqVector2d(v));
}

Vector2d scaleVector2d(Vector2d v,float scalar)
{
    return {v.x * scalar, v.y * scalar};
}
float distVector2d(Vector2d a, Vector2d b)
{
    return lengthVector2d(subsVector2d(a,b));
}

float dotProduct(Vector2d a,Vector2d b)
{
    return (a.x * b.x + a.y * b.y);
}

float lerp(float a,float b,float t)
{
    return (1.0f - t) * a + b * t;
}
float inverseLerp(float a,float b,float value)
{
    return (value - a) / (b - a);
}


Vector2d pointOnLineSegment(LineSegment segment, float t)
{
    Vector2d seg;
    seg.x = segment.start.x + subsVector2d(segment.start,segment.end).x * t;
    seg.y = segment.start.y + subsVector2d(segment.start,segment.end).y * t;

    return seg;
}
bool testPointCircle(Vector2d point,Circle c)
{
    float distSq =(distVector2d(point, c.center));
    distSq *= distSq;


    return distSq <= c.radius * c. radius;
}
bool testPointRect(Vector2d point, AABB rect)
{
    bool outside = point.x < rect.min.x ||
		point.y < rect.min.y ||
		point.x > rect.max.x ||
		point.y > rect.max.y;

    //If none of these are true, they must intersect
    return !outside; 
}
bool testRect(AABB r1,AABB r2)
{
    bool collision = r1.max.x < r2.min.x ||
		r1.max.y < r2.min.y ||
		r2.max.x < r1.min.x ||
		r2.max.y < r1.min.y;

    //If none of these are true, they must intersect
    return !collision;
}

bool testCircle(Circle c1,Circle c2)
{
    float distSq = distVector2d(c1.center,c2.center);
    distSq *= distSq;

    float radiSq = c1.radius + c2.radius;
    radiSq *= radiSq;

    return distSq <= radiSq;
}

bool testCircleRect(Circle c, AABB rect)
{
    float distX;
    float distY;

    if(c.center.x < rect.min.x) distX = rect.min.x;
    else if(c.center.x > rect.max.x) distX = rect.max.x;

    if(c.center.y < rect.min.y) distX = rect.min.y;
    else if(c.center.y > rect.max.y) distY = rect.max.y;

    float distSq = lengthSqVector2d({distX,distY});

    return distSq <= c.radius * c.radius;

}

/*int countVertices(PolygonShape)
{

}
*/

/*void getNumberOfVertices(PolygonShape shape,int type,int* nbVertices)
{
	//int count;
	shape.type = type;

    switch (shape.type)
    {
        case POINT_SHAPE:
		*nbVertices = 1;
		break;
        case SEGMENT_SHAPE:
		*nbVertices = 2;
		break;
        case TRIANGLE_SHAPE:
		*nbVertices = 3;
		break;
        case AABB_SHAPE:
		*nbVertices = 4;
		break;
        case OBB_SHAPE:
		*nbVertices = 4;
		break;
        case CONVEX_SHAPE:
		for(int i = 0; i < shape.shapes.convexPoly.nbPoints; i++)
		{
			Vector2d* p1 = &shape.shapes.convexPoly.points[i];
			//Next vertex;
			Vector2d* p2 = &shape.shapes.convexPoly.points[ i + 1 == shape.shapes.convexPoly.nbPoints ? 0 : i+1 ];

			if(!isEqualToVector2d(*p1,*p2))
			{
				*nbVertices += 1;
			}
		}
		break;
        default:
		break;
    }
}
*/

Range getMinRange(Range r1, Range r2)
{
	Range r = {0};
	r = (fabs(r1.max - r1.min) > fabs(r2.max - r2.min)) ? r2 : r1;
	return r;
}
Range getMaxRange(Range r1, Range r2)
{
	Range r = {0};
	r = (fabs(r1.max - r1.min) > fabs(r2.max - r2.min)) ? r1 : r2;
	return r;
}
bool rangeOverlapRange(Range r1, Range r2)
{
	return (r1.min <= r2.max) && (r2.min <= r1.max);
}
Vector2d getNormal(Vector2d a, Vector2d b)
{
	Vector2d result;

	result.x = -(b.y - a.y);
	result.y = (b.x - a.x);
	//result = normalizeVector2d(result);
	return (result);
}

Vector2d getLocalVector2d(Vector2d a, Vector2d b)
{
	Vector2d result = {b.x - a.x, b.y - a.y};

	return (result);
}

int satAlgorithm(Vector2d *a, Vector2d *b, int sizeA, int sizeB)
{
	float infinity = -log(0);
	float minusInfinity = log(0);

	for (int i = 0; i < sizeA - 1;i++)
	{
		Range range1 = {infinity, minusInfinity};
		Range range2 = range1;

		Vector2d normal = getNormal(a[i], a[i + 1]);
		printf("normal x.%f y.%f x.%f y.%f %f %f\n",a[i].x, a[i].y, a[i+1].x, a[i+1].y, normal.x, normal.y);
		Vector2d absNormal = normal;
		Vector2d normalized = absNormal;
		if (absNormal.x < 0)
			absNormal.x = -absNormal.x;
		if (absNormal.y < 0)
			absNormal.y = -absNormal.y;
		absNormal.x += a[i].x;
		absNormal.y += a[i].y;
		//DrawLine(absNormal.x, absNormal.y, absNormal.x + (10*normalized.x), absNormal.y + (10*normalized.y), WHITE);
		for (int j = 0; j < sizeA;j++)
		{
			float projection = dotProduct(a[j], normal);
			if (projection < range1.min)
				range1.min = projection;
			if (projection > range1.max)
				range1.max = projection;
		}

		for (int j = 0;j < sizeB;j++)
		{
			float projection = dotProduct(b[j], normal);

			if (projection < range2.min)
				range2.min = projection;
			if (projection > range2.max)
				range2.max = projection;
		}
		if(!rangeOverlapRange(range1,range2))
			return 0;
	}
	return 1;
}


int satAlgorithmPolygonCircle(Vector2d* v,int vSize,Circle* circle)
{
	Vector2d closestVertex;
	Vector2d closestNormalized;
	float mindist = log(0);
	
	Range circleRange;
	Range polyRange;

	//Get the normalized axis of the polygon
	//Vector2d axis[vSize];
	Vector2d* axis = NULL;
	axis = (Vector2d*)malloc(vSize * sizeof(Vector2d));
	for(int k = 0; k < vSize; k++)
	{
		axis[k] = normalizeVector2d(getNormal(v[k],v[k + 1 == vSize ? 0 : k+1]));
	}

	//Circle
	for(int i = 0; i < vSize; i++)
	{
		//delta between the circle position and the current vertex of the polygon
		Vector2d delta = subsVector2d(v[i],circle->center);
		float dist = lengthSqVector2d(delta);

		if(dist > mindist*mindist)
		{
			mindist = dist;
			closestVertex = delta;

			closestNormalized = normalizeVector2d(closestVertex);

			float projCircle = dotProduct(closestNormalized,circle->center);
			
			circleRange.min = projCircle - circle->radius;
			circleRange.max = projCircle + circle->radius;
		}

		//Vector2d closestNormalized = normalizeVector2d(closestVertex);

		//Project the center onto the closest vertex of the polygon
/* 		float projCircle = dotProduct(closestNormalized,circle->center);
		
		circleRange.min = projCircle - circle->radius;
		circleRange.max = projCircle + circle->radius; */


		//Loop over the polygon
		polyRange.min =polyRange.max = dotProduct(axis[0],v[0]);
		for(int j = 1; j < vSize - 1; j++)
		{
			float proj = dotProduct(axis[j],v[j]);
			if(proj < polyRange.min)
			{
				polyRange.min = proj;
			}
			if(proj > polyRange.max)
			{
				polyRange.max = proj;
			}
		}

		if(!rangeOverlapRange(polyRange,circleRange))
		{
			return 0;
		}

	}

	//Vector2d closestNormalized = normalizeVector2d(closestVertex);

	//Project the center onto the closest vertex of the polygon
/* 	float projCircle = dotProduct(closestNormalized,circle->center);
	
	circleRange.min = projCircle - circle->radius;
	circleRange.max = projCircle + circle->radius;
 */

/* 	//Get the normalized axis of the poygon
	Vector2d axis[vSize];
	for(int i = 0; i < vSize; i++)
	{
		axis[i] = normalizeVector2d(getNormal(v[i],v[i + 1 == vSize ? 0 : i+1]));
	} */

	/*loop over polygon*/
/* 	polyRange.min =polyRange.max = dotProduct(axis[0],v[0]);
	for(int i = 1; i < vSize - 1; i++)
	{
		float proj = dotProduct(axis[i],v[i]);
		if(proj < polyRange.min)
		{
			polyRange.min = proj;
		}
		if(proj > polyRange.max)
		{
			polyRange.max = proj;
		}
	} */
/* 	if(!rangeOverlapRange(polyRange,circleRange))
	{
		return 0;
	} */

	free(axis);

	return 1;
}