#pragma once
#include <math.h>


#define EPSILON    pow(10,-9)

//For SAT 
typedef struct Range
{
    float min;
    float max;
} Range;

//2D vector
typedef struct Vector2d
{
    float x;
    float y;

} Vector2d;

//Line segment
typedef struct LineSegment
{
    Vector2d start;
    Vector2d end;

} LineSegment;

//Circle
typedef struct Circle
{
    Vector2d center;
    float radius;

} Circle;

//Rectangle
typedef struct AABB
{
    Vector2d min;
    Vector2d max;
    //Vector2d position;
    //Vector2d size;
} AABB;
//Oriented box
typedef struct OBB
{
    Vector2d start;
    Vector2d extends;
    float rotation;

} OBB;

typedef struct Triangle
{
    Vector2d v1;
    Vector2d v2;
    Vector2d v3;

} Triangle;

//Convex Polygon
typedef struct ConvexPolygon
{
    int nbPoints;
    Vector2d* points;

} ConvexPolygon;

//Union for store all polygon
typedef union Shapes
{
    Vector2d vector;
    LineSegment segment;
    AABB rectAB;
    OBB  rectOB;
    Triangle triangle;
    ConvexPolygon convexPoly;
    //Circle circle;

} Shapes;


//Type's of shape
//typedef enum ShapeType{POINT_SHAPE = 1,SEGMENT_SHAPE,AABB_SHAPE,
                        //OBB_SHAPE,TRIANGLE_SHAPE,CONVEX_SHAPE} ShapeType;
	//OBB_SHAPE,TRIANGLE_SHAPE,CONVEX_SHAPE} ShapeType;

//Polygon
//typedef struct PolygonShape
//{
    //ShapeType type;
    //Shapes shapes;

//} PolygonShape;


//2D Vector functions
Vector2d zeroVector2d();
Vector2d addVector2d(Vector2d a,Vector2d b);
Vector2d subsVector2d(Vector2d a,Vector2d b);
bool isEqualToVector2d(Vector2d a,Vector2d b);
Vector2d normalizeVector2d(Vector2d v);
Vector2d negateVector2d(Vector2d v);

float lengthSqVector2d(Vector2d v);
float lengthVector2d(Vector2d v);
Vector2d getNormal(Vector2d a, Vector2d b);

Vector2d scaleVector2d(Vector2d v,float scalar);
float distVector2d(Vector2d a, Vector2d b);
float dotProduct(Vector2d a,Vector2d b);

//Some utilites fonctions
float lerp(float a,float b,float t);
float inverseLerp(float a,float b,float value);

//Collisions
Vector2d pointOnLineSegment(LineSegment segment, float t);
bool testPointRect(Vector2d point, AABB rect);
bool testPointCircle(Vector2d point,Circle c);
bool testRect(AABB r1,AABB r2);
bool testCircle(Circle c1,Circle c2);
bool testCircleRect(Circle c, AABB rect);


//Fonctions for the SAT
Range getPointProjOnVector(Vector2d vector, Vector2d point);
//void getNumberOfVertices(PolygonShape shape,int type,int* nbVertices);
Range getMinRange(Range r1, Range r2);
Range getMaxRange(Range r1, Range r2);
bool rangeOverlapRange(Range r1, Range r2);


//bool intersect(PolygonShape shape1,int type1,PolygonShape shape2,int type2);
//void getNumberOfVertices(PolygonShape shape,int type,int* nbVertices);

int satAlgorithm(Vector2d *a, Vector2d *b, int sizeA, int sizeB);
int satAlgorithmPolygonCircle(Vector2d* v,int vSize,Circle* circle);