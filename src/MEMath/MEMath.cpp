#include "MEMath.h"
#include <math.h>


MEMath::MEMath()
{
}


MEMath::~MEMath()
{
}

float MEMath::getLength(osg::Vec3Array* source)
{
	auto length = 0.0;
	if (source == nullptr)
	{
		return length;
	}

	auto iter = source->begin();
	auto iterNext = iter + 1;
	while (iterNext != source->end())
	{
		auto line = (*iterNext) - (*iter);
		length += line.length();
		iter++;
		iterNext++;
	}
	return length;
}

bool MEMath::intersectSegm(osg::Vec3 posA, osg::Vec3 posB, osg::Vec3 posC, osg::Vec3 posD, osg::Vec3& posInter)
{
	double delta = (posB.y() - posA.y())*(posD.x() - posC.x())
		- (posA.x() - posB.x())*(posC.y() - posD.y());
	if (delta <= (1e-6) && delta >= -(1e-6))
	{
		return false;
	}

	// 线段所在直线的交点坐标 (x , y)      
	posInter.x() = ((posB.x() - posA.x()) * (posD.x() - posC.x()) * (posC.y() - posA.y())
		+ (posB.y() - posA.y()) * (posD.x() - posC.x()) * posA.x()
		- (posD.y() - posC.y()) * (posB.x() - posA.x()) * posC.x()) / delta;

	posInter.y() = -((posB.y() - posA.y()) * (posD.y() - posC.y()) * (posC.x() - posA.x())
		+ (posB.x() - posA.x()) * (posD.y() - posC.y()) * posA.y()
		- (posD.x() - posC.x()) * (posB.y() - posA.y()) * posC.y()) / delta;

	if (
		// 交点在线段1上  
		(posInter.x() - posA.x()) * (posInter.x() - posB.x()) <= 0
		&& (posInter.y() - posA.y()) * (posInter.y() - posB.y()) <= 0
		// 且交点也在线段2上  
		&& (posInter.x() - posC.x()) * (posInter.x() - posD.x()) <= 0
		&& (posInter.y() - posC.y()) * (posInter.y() - posD.y()) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MEMath::intersectLine(osg::Vec3 pos1, osg::Vec3 pos2,
	osg::Vec3 pos3, osg::Vec3 pos4, osg::Vec3& posInter)
{
	//直线方程组
	//	Line A:
	//	x = P1x + (P2x - P1x) * S 
	//	y = P1y + (P2y - P1y) * S
	//	z = P1z + (P2z - P2z) * S
	//
	//	Line B:
	//	x = P3x + (P4x - P3x) * T
	//	y = P3y + (P4y - P3y) * T
	//	z = P3z + (P4z - P3z) * T

	//T = (P13y*P43x - P43y*P13x) / (P43y*P21x - P43x*P21y)
	//两直线已经相交
	if (pos1 == pos3 || pos1 == pos4)
	{
		posInter = pos1;
		return true;
	}
	if (pos2 == pos3 || pos2 == pos3)
	{
		posInter = pos2;
		return true;
	}
	
	float P13x = pos1.x() - pos3.x();
	float P13y = pos1.y() - pos3.y();

	float P43x = pos4.x() - pos3.x();
	float P43y = pos4.y() - pos3.y();

	float P21x = pos2.x() - pos1.x();
	float P21y = pos2.y() - pos1.y();
	
	float mem = P43x*P13y - P43y*P13x;//分子
	float den = P43y*P21x - P43x*P21y;//分母
	if (den == 0.0)
	{

		return false;
	}
	else
	{
		float T = mem / den;
		posInter = pos1 + (pos2 - pos1)*T;
		return true;
	}
}

bool MEMath::createStripBevel(float radius, osg::Vec3Array* source, osg::Vec3Array* lefts, osg::Vec3Array* rights)
{
	osg::Vec3d zero = osg::Vec3d(0.000000001, 0.000000001, 0.000000001);
	osg::Vec3Array* vecLine = new osg::Vec3Array;
	size_t size = source->size();
	if (size < 2)
	{
		return false;
	}

	osg::Vec3 currtVec, nextVec, vertlVec, nextVerl,
		normalVec, currtPos, nextPos, lastPos;

	for (size_t i = 0; i < size; i++)
	{
		if (i == 0)
		{
			currtPos = source->at(i);
			nextPos = source->at(i + 1);
			currtVec = nextPos - currtPos;
			currtVec.normalize();
			vertlVec = currtVec ^ osg::Z_AXIS;
			lefts->push_back(source->at(i) - vertlVec * radius);
			rights->push_back(source->at(i) + vertlVec * radius);
			continue;
		}
		else if (i == size - 1)
		{
			currtPos = source->at(i);
			lastPos = source->at(i - 1);
			currtVec = currtPos - lastPos;
			currtVec.normalize();
			vertlVec = currtVec ^ osg::Z_AXIS;
			lefts->push_back(source->at(i) - vertlVec * radius);
			rights->push_back(source->at(i) + vertlVec * radius);
			continue;
		}
		else
		{
			currtPos = source->at(i);
			lastPos = source->at(i - 1);
			nextPos = source->at(i + 1);
			currtVec = currtPos - lastPos;
			nextVec = nextPos - currtPos;
			currtVec.normalize();
			nextVec.normalize();
			vertlVec = currtVec ^ osg::Z_AXIS;
			nextVerl = nextVec ^ osg::Z_AXIS;
			osg::Vec3 A1, A2, B1, B2, C1, C2, D1, D2;
			A1 = lastPos - vertlVec * radius;
			A2 = currtPos - vertlVec * radius;
			B1 = lastPos + vertlVec * radius;
			B2 = currtPos + vertlVec * radius;
			C1 = currtPos - nextVerl * radius;
			C2 = nextPos - nextVerl * radius;
			D1 = currtPos + nextVerl * radius;
			D2 = nextPos + nextVerl * radius;

			float offset = 1.0;
			osg::Vec3 interA;
			bool isInter = intersectSegm(A1, A2, C1, C2, interA);
			if (isInter)
			{
				interA.z() = currtPos.z();
				lefts->push_back(interA);
				lefts->push_back(interA);
				rights->push_back(B2*offset);
				rights->push_back(D1*offset);
			}
			osg::Vec3 interB;
			isInter = intersectSegm(B1, B2, D1, D2, interB);
			if (isInter)
			{
				interB.z() = currtPos.z();
				rights->push_back(interB);
				rights->push_back(interB);
				lefts->push_back(A2*offset);
				lefts->push_back(C1*offset);
			}
		}

	}

	if (source->at(0) == source->at(size - 1))
	{
		osg::Vec3 interA, interB;
		bool isInter = intersectSegm(lefts->at(0), lefts->at(1), lefts->at(lefts->size() - 2), lefts->at(lefts->size() - 1), interA);
		if (isInter)
		{
			(*lefts)[0] = interA;
			lefts->pop_back();
			lefts->push_back(interA);
			lefts->push_back(interA);
		}
		else
		{
			lefts->push_back(lefts->at(0));
		}
		isInter = intersectSegm(rights->at(0), rights->at(1), rights->at(rights->size() - 2), rights->at(rights->size() - 1), interB);
		if (isInter)
		{
			(*rights)[0] = interB;
			rights->pop_back();
			rights->push_back(rights->at(0));
			rights->push_back(rights->at(0));
		}
		else
		{
			rights->push_back(rights->at(0));
		}
	}
	return true;
}

bool MEMath::createStripMiter(float radius, osg::Vec3Array* source, osg::Vec3Array* lefts, osg::Vec3Array* rights)
{
	osg::Vec3d zero = osg::Vec3d(0.000000001, 0.000000001, 0.000000001);
	osg::Vec3Array* vecLine = new osg::Vec3Array;
	size_t size = source->size();
	if (size < 2)
	{
		return false;
	}

	osg::Vec3 currtVec, nextVec, vertlVec, nextVerl,
		normalVec, currtPos, nextPos, lastPos;

	for (size_t i = 0; i < size; i++)
	{
		if (i == 0)
		{
			currtPos = source->at(i);
			nextPos = source->at(i + 1);
			currtVec = nextPos - currtPos;
			currtVec.normalize();
			vertlVec = currtVec ^ osg::Z_AXIS;
			lefts->push_back(source->at(i) - vertlVec * radius);
			rights->push_back(source->at(i) + vertlVec * radius);
			continue;
		}
		else if (i == size - 1)
		{
			currtPos = source->at(i);
			lastPos = source->at(i - 1);
			currtVec = currtPos - lastPos;
			currtVec.normalize();
			vertlVec = currtVec ^ osg::Z_AXIS;
			lefts->push_back(source->at(i) - vertlVec * radius);
			rights->push_back(source->at(i) + vertlVec * radius);
			continue;
		}
		else
		{
			currtPos = source->at(i);
			lastPos = source->at(i - 1);
			nextPos = source->at(i + 1);
			currtVec = currtPos - lastPos;
			nextVec = nextPos - currtPos;
			currtVec.normalize();
			nextVec.normalize();
			vertlVec = currtVec ^ osg::Z_AXIS;
			nextVerl = nextVec ^ osg::Z_AXIS;
			osg::Vec3 A1, A2, B1, B2, C1, C2, D1, D2;
			A1 = lastPos - vertlVec * radius;
			A2 = currtPos - vertlVec * radius;
			B1 = lastPos + vertlVec * radius;
			B2 = currtPos + vertlVec * radius;
			C1 = currtPos - nextVerl * radius;
			C2 = nextPos - nextVerl * radius;
			D1 = currtPos + nextVerl * radius;
			D2 = nextPos + nextVerl * radius;

			float offset = 1.0;
			osg::Vec3 intersect;
			intersectLine(A1, A2, C1, C2, intersect);
			lefts->push_back(intersect);
			intersectLine(B1, B2, D1, D2, intersect);
			rights->push_back(intersect);
			continue;
		}
	}
	return true;
}

osg::Vec2Array* MEMath::calcStripTexCoord(osg::Vec3Array* source)
{
	osg::Vec2Array* texCoords = new osg::Vec2Array;
	auto count = source->size();
	if (count < 2)
	{
		return texCoords;
	}
	float _fLength = MEMath::getLength(source);
	float theLength = 0.0;
	for (size_t i = 0; i < count; i++)
	{
		if (i == 0)
		{
			texCoords->push_back(osg::Vec2(0, 0));
			texCoords->push_back(osg::Vec2(0, 1));
		}
		else if ( i == count - 1)
		{
			texCoords->push_back(osg::Vec2(_fLength/10, 0));
			texCoords->push_back(osg::Vec2(_fLength/10, 1));
		}
		else
		{
			Segment seg(source->at(i - 1), source->at(i));
			float _length = seg.length();
			theLength += _length;
			texCoords->push_back(osg::Vec2(theLength/10, 0));
			texCoords->push_back(osg::Vec2(theLength/10, 1));
		}
	}
	return texCoords;
}

osg::Vec2Array* MEMath::calcPipeTexCoord(osg::Vec3Array* source, size_t parts)
{
	osg::Vec2Array* texCoords = new osg::Vec2Array;
	auto count = source->size();
	if (count < 2)
	{
		return texCoords;
	}
	float deltaV = 1.0 / parts;

	//外层循环控制拐点的遍历
	osg::Vec2 uvCoord;
	float _length = 0.0;
	float S = MEMath::getLength(source);
	for (size_t v = 0; v <= parts; v++)
	{
		size_t index = v; 
		bool mod = v % 2; //判断是否单数行
		if (mod)
		{
			_length = S;
			//奇数行
			for (int u = count - 1; u >= 0; u--)
			{
				index = v;
				size_t indexN = index + 1;
				if (v == parts)
				{
					indexN = 0;
				}
				if (u == 0)
				{//第一个点的时候u = 0
					
					uvCoord = osg::Vec2(0, index * deltaV);
					texCoords->push_back(uvCoord);
					uvCoord = osg::Vec2(0, indexN * deltaV);
					texCoords->push_back(uvCoord);
				}
				else if (u == count - 1)
				{//最后一个点的时候u = 总长度
					uvCoord = osg::Vec2(S / 10, index * deltaV);
					texCoords->push_back(uvCoord);
					uvCoord = osg::Vec2(S / 10, indexN * deltaV);
					texCoords->push_back(uvCoord);
				}
				else
				{
					Segment segment = Segment(source->at(u + 1), source->at(u));
					float dis = abs(segment.length());
					_length -= dis;
					uvCoord = osg::Vec2(_length / 10, index * deltaV);
					texCoords->push_back(uvCoord);
					uvCoord = osg::Vec2(_length / 10, indexN * deltaV);
					texCoords->push_back(uvCoord);
				}
			}
		}
		else
		{
			_length = 0.0;
			//偶数行
			for (size_t u = 0; u < count; u++)
			{
				index = v;
				size_t indexN = index + 1;
				if (v == parts)
				{
					indexN = 0;
				}
				if (u == 0)
				{//第一个点的时候u = 0
					uvCoord = osg::Vec2(0, index * deltaV);
					texCoords->push_back(uvCoord);
					uvCoord = osg::Vec2(0, indexN * deltaV);
					texCoords->push_back(uvCoord);
				}
				else if (u == count - 1)
				{//最后一个点的时候u = 总长度
					uvCoord = osg::Vec2(S / 10, index * deltaV);
					texCoords->push_back(uvCoord);
					uvCoord = osg::Vec2(S / 10, indexN * deltaV);
					texCoords->push_back(uvCoord);
				}
				else
				{
					Segment segment = Segment(source->at(u), source->at(u - 1));
					float dis = abs(segment.length());
					_length += dis;
					uvCoord = osg::Vec2(_length / 10, index * deltaV);
					texCoords->push_back(uvCoord);
					uvCoord = osg::Vec2(_length / 10, indexN * deltaV);
					texCoords->push_back(uvCoord);
				}
			}
		}
	}

	return texCoords;
}

osg::Vec3Array* MEMath::createPipe(osg::Vec3Array* source, float radius)
{
	osg::Vec3Array* vertex = new osg::Vec3Array;
	auto count = source->size();
	if (count < 2)
	{
		return nullptr;
	}
	if (count < 3)
	{
		for (int i = 0; i < count; i++)
		{
			size_t parts = radius * 10;
			const float angleDelta = 2.0f*osg::PI / radius * 10;
			float angle = 0.0f;
			for (size_t j = 0; j < parts; ++j, angle += angleDelta)
			{
				float c = cosf(angle);
				float s = sinf(angle);
				vertex->push_back(source->at(i) + osg::Vec3(c*radius, s*radius, 0.0f));
			}
		}
	}
	else
	{
		source = BezierCurve(source, 1.0, 10);
		count = source->size();
 		for (int i = 0; i < count; i++)
 		{
 			size_t parts = radius * 10;
 			const float angleDelta = 2.0f*osg::PI / radius * 10;
 			float angle = 0.0f;
 			for (size_t j = 0; j < parts; ++j, angle += angleDelta)
 			{
 				float c = cosf(angle);
 				float s = sinf(angle);
 				vertex->push_back(source->at(j) + osg::Vec3(c*radius, s*radius, 0.0f));
 			}
 		}
	}
	return vertex;
}

osg::Vec3Array* MEMath::BezierCurve(osg::Vec3Array* vertexs, float radius, size_t parts)
{
	auto controlPoints = new osg::Vec3Array;
	auto resultCurve = new osg::Vec3Array;

	auto countP = vertexs->size();
	if (countP < 3)
	{
		auto iter = resultCurve->end();
		resultCurve->insert(iter, vertexs->begin(), vertexs->end());
		return resultCurve;
	}
	
	//计算控制点
	for (int i = 1; i < countP; i++)
	{
		Segment segPP0(vertexs->at(i - 1), vertexs->at(i));
		float length = segPP0.length();
		float pp0Scale = radius/length;
		if (i == 1)
		{
			controlPoints->push_back(segPP0.vector() * (1 - pp0Scale) + vertexs->at(i - 1));
		}
		else if (i == countP - 1)
		{
			if (pp0Scale >= radius)
			{
				controlPoints->push_back(segPP0.vector() * pp0Scale + vertexs->at(i - 1));
				continue;
			}
			controlPoints->push_back(segPP0.vector() * pp0Scale + vertexs->at(i - 1));
		}
		else
		{
			
			controlPoints->push_back(segPP0.vector() * pp0Scale + vertexs->at(i - 1));
			controlPoints->push_back(segPP0.vector() * (1 - pp0Scale) + vertexs->at(i - 1));
		}
	}
	
	//进行插值
	for (int i = 0, j = 0; i < countP; i ++)
	{
		//第一个点和最后一个点都直接添加不插值
		if (i == 0 || i == countP - 1)
		{
			resultCurve->push_back(vertexs->at(i));
		}
		else
		{
			//	P0
			//	|
			//	|
			//	|
			//	↓-----------→ P1
			//	P
			// B(t) = (1-t)²*P0 + 2t*(1-t)P + t²*P1, t = [0, 1]			
			osg::Vec3 P0, P, P1;
			P0 = controlPoints->at(j);
			P = vertexs->at(i);
			P1 = controlPoints->at(j + 1);

 			auto delta = 1.0 / parts;
 			for (int n = 0; n <= parts; n++)
 			{
 				auto t = n * delta;
				float flag = 1 - t;
				osg::Vec3 pos;
				pos = P0*pow(flag, 2) + P * 2*t*flag + P1*pow(t, 2);
 				resultCurve->push_back(pos);
 			}
			j += 2;
		}
	}
	return resultCurve;
}

osg::Vec3Array* MEMath::createCircle(osg::Vec3 center, float radius, osg::Vec3 upDir, size_t parts /*= 10*/)
{
	osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array;
	const float angleDelta = 2.0f*osg::PI / parts;
	float angle = 0.0f;
	for (size_t j = 0; j < parts; ++j, angle += angleDelta)
	{
		float _x = cosf(angle);
		float _y = sinf(angle);
		osg::Matrix matrix;
		matrix.makeRotate(osg::Z_AXIS, upDir);
		osg::Vec3 pos = osg::Vec3(_x*radius, _y*radius, 0.0f);
		pos = pos * matrix;
		pos += center;
		points->push_back(pos);
	}
	return points.release();
}
