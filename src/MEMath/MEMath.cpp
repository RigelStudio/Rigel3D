#include "MEMath.h"



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

bool MEMath::intersect(osg::Vec3 posA, osg::Vec3 posB, osg::Vec3 posC, osg::Vec3 posD, osg::Vec3& posInter)
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

bool MEMath::createStrip(float radius, osg::Vec3Array* source, osg::Vec3Array* lefts, osg::Vec3Array* rights)
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
			bool isInter = intersect(A1, A2, C1, C2, interA);
			if (isInter)
			{
				interA.z() = currtPos.z();
				lefts->push_back(interA);
				lefts->push_back(interA);
				rights->push_back(B2*offset);
				rights->push_back(D1*offset);
			}
			osg::Vec3 interB;
			isInter = intersect(B1, B2, D1, D2, interB);
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
		bool isInter = intersect(lefts->at(0), lefts->at(1), lefts->at(lefts->size() - 2), lefts->at(lefts->size() - 1), interA);
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
		isInter = intersect(rights->at(0), rights->at(1), rights->at(rights->size() - 2), rights->at(rights->size() - 1), interB);
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
