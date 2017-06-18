#ifndef PLOTTINGARROW_H
#define PLOTTINGARROW_H

#include "Export.h"

#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/StateSet>

#include <osgUtil/Tessellator>
#include <osgUtil/SmoothingVisitor>

#include <osg/BlendColor>
#include <osg/BlendFunc>
#include <osg/PolygonMode>
#include <osg/ShapeDrawable>
#include <osg/AutoTransform>
#include <osgDB/ReadFile>
#include <osg/Texture2D>

#include <iostream>
#include <sstream>

#include <Effect/ShaderTool.h>
#include "IconTool.h"
#include "BezierCurve.h"

#include <Modeling/TextNode.h>

//--注释开始
//--2015年4月26日--王莹
//1.修改箭头头部和尾部形状，不在上述两处进行插值;
//2.修改箭头中部的插值计算方法，只在拐点处插值;
//3.利用shader设置箭头的颜色;
//4.添加箭头的管理;
//5.添加关闭按钮，方便箭头的删除，具体实现类似于测量中的删除按钮;
//--注释结束

class PLOTTING_EXPORT PlottingArrow : public osg::Group
{
public:

	typedef std::vector<Bezier::Point> PointVec;

	//创建新的箭头，并添加关闭按钮
	bool create(const std::string& name, osg::Vec3Array* points, const osg::Vec4& color, float width)
	{
		if(name.empty()) return false;
		if(!points || points->size() < 2) return false;

		_points = new osg::Vec3Array(*points,osg::CopyOp::DEEP_COPY_ARRAYS);

		osg::ref_ptr<osg::Vec3Array> sample1 = samplePoint_Distance(points, 8.f); //数据采样1
		if(!sample1) return false;
		osg::ref_ptr<osg::Vec3Array> sample2 = samplePoint_Angle(sample1, 10.f); //数据采样2
		if(!sample2) return false;
		osg::ref_ptr<osg::Vec3Array> finalpoints = computePoint_One_Ver2(sample2, width);
		if(!finalpoints) return false;

		setArrowHeight(finalpoints, 1.f);

		arrow = GeometryDrawer::createPolygonGeode(finalpoints);
		
		addChild(arrow);

		ShaderTool::setColorByShader(arrow->getOrCreateStateSet(), color);

		//添加删除图标
		closeBtn = IconTool::Image::createImageAT(resPath, 20, false) ;
		closeBtn->setPosition(finalpoints->at(0)); //在尾部右侧添加删除图标
		closeBtn->setName("arrow_close_button");
		
		addChild(closeBtn);

		//文字编辑
		textNode = new TextNode;
		//textNode->setText("PlottingArrow");

		tipNode = new osg::AutoTransform;
		tipNode->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_AXIS);
		tipNode->setAxis(osg::Z_AXIS);

		tipNode->addChild(textNode);
		tipNode->setPosition(finalpoints->at(1) + osg::Z_AXIS);

		addChild(tipNode);

		setName(name); //标绘箭头

		_color = color;
		_width = width;
		_name = name;

		return true;
	}

	//static std::string getCloseBtnName() { return closeBtnName; }

	void setArrowText(const std::string& text)
	{
		textNode->setText(text);
		tipNode->setNodeMask(0x1);
	}

	void hideArrowText()
	{
		tipNode->setNodeMask(0x0);
	}

	static void setResPath(const std::string& path) 
	{
		resPath = path;
	}

	osg::Vec4 color() { return _color; }
	float width() { return _width; }
	std::string name() { return _name; }
	osg::Vec3Array *points() { return _points.get(); }

protected:
	osg::ref_ptr<osg::Geode> arrow;
	osg::ref_ptr<osg::AutoTransform> closeBtn;
	//static std::string closeBtnName;
	static std::string resPath;
	osg::ref_ptr<TextNode> textNode;
	osg::ref_ptr<osg::AutoTransform> tipNode;

	osg::Vec4 _color;
	float _width;
	std::string _name;
	osg::ref_ptr<osg::Vec3Array> _points;

	//箭头绘制部分
	osg::Vec3Array* computePoint_One_Ver2(osg::Vec3Array* points, int width) 
	{
		//if(!points || points->size() < 10) return NULL;
		//头部
		osg::Vec3Array* head= new osg::Vec3Array;
		computePoint_One_Head(points, width, head);

		//尾部
		osg::Vec3Array* tail = new osg::Vec3Array;
		computePoint_One_Tail(points, width, tail);

		//中部
		osg::Vec3Array* left = new osg::Vec3Array;
		osg::Vec3Array* right = new osg::Vec3Array;
		computePoint_One_Mid(points, width, left, right);
		//加上尾部两侧的点
		left->insert(left->begin(), tail->at(2));
		left->push_back(head->at(0));
        //加上头部两侧的点
		right->insert(right->begin(), tail->at(0));
		right->push_back(head->at(4));
		//拐点处插值计算
		osg::ref_ptr<osg::Vec3Array> betterleft = insertPoint_ForMidd(left);
		osg::ref_ptr<osg::Vec3Array> betterright = insertPoint_ForMidd(right);

		osg::ref_ptr<osg::Vec3Array> final = new osg::Vec3Array;

		for(osg::Vec3Array::iterator itr = tail->begin();
			itr != tail->end(); ++itr)
		{
			final->push_back(*itr);
		}
		
		for(osg::Vec3Array::iterator itr = betterleft->begin();
			itr != betterleft->end(); ++itr)
		{
			final->push_back(*itr);
		}

		for(osg::Vec3Array::iterator itr = head->begin();
			itr != head->end(); ++itr)
		{
			final->push_back(*itr);
		}
		for(osg::Vec3Array::reverse_iterator ritr = betterright->rbegin();
			ritr != betterright->rend(); ++ritr)
		{
			final->push_back(*ritr);
		}

		return final.release();
	}

	//拐点处插值计算，仅在拐点处插值
	osg::Vec3Array* insertPoint_ForMidd(osg::Vec3Array* initpoint)
	{
		//if(!initpoint || initpoint->size() < 3) return NULL;

		osg::ref_ptr<osg::Vec3Array> insertpoint = new osg::Vec3Array;
		insertpoint->push_back(initpoint->at(0));

		unsigned int number = initpoint->size();
		for(unsigned int i = 1; i < number - 1; ++i)
		{
			insertpoint->push_back(initpoint->at(i));

			osg::Vec3 predir = initpoint->at(i) - initpoint->at(i - 1);
			float prelength = predir.length();
			predir.normalize();
			osg::Vec3 backdir = initpoint->at(i + 1) - initpoint->at(i);
			float backlength = backdir.length();
			backdir.normalize();

			osg::Vec3 pre = initpoint->at(i) - predir * 2.5; //偏移量不宜太大
			osg::Vec3 back = initpoint->at(i) + backdir * 2.5; //偏移量不宜太大

			osg::Vec3 mid = (pre + back) * 0.5;
			osg::Vec3 midmid = (mid + initpoint->at(i)) * 0.5;

			osg::Vec3 premid = (pre + midmid) * 0.5;
			osg::Vec3 backmid = (back + midmid) * 0.5;

			PointVec cpoints;
			cpoints.push_back(pre);
			cpoints.push_back(premid);
			cpoints.push_back(backmid);
			cpoints.push_back(back);

			PointVec bpoints = Bezier::createBezier(cpoints, 0.005);

			for(PointVec::iterator itr = bpoints.begin();
				itr != bpoints.end(); ++itr)
			{
				osg::Vec3 point = osg::Vec3(itr->x, itr->y, itr->z);
				insertpoint->push_back(point);
			}
		}

		insertpoint->push_back(initpoint->at(number - 1));

		return insertpoint.release();
	}

	
	//计算尾部三个控制点
	void computePoint_One_Tail(osg::Vec3Array* points, int width, osg::Vec3Array* & tail)
	{
		if(!points || points->size() < 2) return;

		//tail两点计算
		osg::Vec3 dir = points->at(1) - points->at(0);
		dir.normalize();

		osg::Vec3 vert = osg::Vec3(dir.y(), -dir.x(), dir.z());

		osg::Vec3 left = points->at(0)- vert * width * 1.5f  - dir * width ;
		osg::Vec3 right = points->at(0) + vert * width * 1.5f  - dir * width;
		osg::Vec3 mid = points->at(0); //for better shape, - dir * width;

		tail->push_back(right);
		tail->push_back(mid);
		tail->push_back(left);
	}

	//计算头部五个控制点
	void computePoint_One_Head(osg::Vec3Array* points, int width, osg::Vec3Array* &head)
	{
		if(!points || points->size() < 2) return;

		unsigned int pointnumber = points->size();

		osg::Vec3 dir = points->at(pointnumber - 1) - points->at(pointnumber - 2);
		dir.normalize();

		osg::Vec3 vert = osg::Vec3(dir.y(), -dir.x(), dir.z());

		osg::Vec3 left1 = points->at(pointnumber - 1) - vert * width * 0.9;
		osg::Vec3 right1 = points->at(pointnumber - 1) + vert * width * 0.9;
		osg::Vec3 left2 = points->at(pointnumber - 1) - vert * width * 3  - dir; //for better shape
		osg::Vec3 right2 = points->at(pointnumber - 1) + vert * width * 3  - dir; //for better shape
		osg::Vec3 headmid = points->at(pointnumber - 1) + dir * width * 3;

		head->push_back(left1);
		head->push_back(left2);
		head->push_back(headmid);
		head->push_back(right2);
		head->push_back(right1);
	}

	//计算中间控制点
	void computePoint_One_Mid(osg::Vec3Array* points, int width, osg::Vec3Array* &leftvec, osg::Vec3Array* &rightvec)
	{
		if(!points || points->size() < 2) return;

		unsigned int pointnumber = points->size();

		for(unsigned int i = 1; i < pointnumber - 1; ++i)
		{
			osg::Vec3 backdir = points->at(i) - points->at(i - 1);
			osg::Vec3 predir = points->at(i + 1) - points->at(i);

			backdir.normalize(); 
			predir.normalize();

			//解决问题：当拐点角度较大时，箭头宽度变窄，适当加宽
			float angle = acos(backdir * predir);

			float widthparam;
			if(angle > osg::PI_2)  widthparam = angle / osg::PI_4;
			else widthparam = 1.f;

			osg::Vec3 backvert = osg::Vec3(backdir.y(), -backdir.x(), backdir.z());
			osg::Vec3 prevert = osg::Vec3(predir.y(), -predir.x(), predir.z());

			//计算某个关键点在前后两个方向的左右点并计算平均值
			//解决的问题：当拐角幅度比较大时，箭头形状发生扭曲
			osg::Vec3 left1 = points->at(i) - backvert * width * widthparam;
			osg::Vec3 right1 = points->at(i) + backvert * width * widthparam;

			osg::Vec3 left2 = points->at(i) - prevert * width * widthparam;
			osg::Vec3 right2 = points->at(i) + prevert * width * widthparam;

			osg::Vec3 left = (left1 + left2) * 0.5;
			osg::Vec3 right = (right1 + right2) * 0.5;

			leftvec->push_back(left);
			rightvec->push_back(right);

		}
	}

	PointVec arrayToPoint(osg::Vec3Array* pArray)
	{
		PointVec pVec;
		for(osg::Vec3Array::iterator itr = pArray->begin(); 
			itr != pArray->end(); ++itr)
		{
			pVec.push_back(*itr);
		}
		return pVec;
	}

	osg::Vec3Array* pointToArray(const PointVec& pVec)
	{
		osg::Vec3Array* pArray = new osg::Vec3Array;
		for (PointVec::const_iterator itr = pVec.begin(); 
			itr != pVec.end(); ++itr)
		{
			pArray->push_back(osg::Vec3(itr->x, itr->y, itr->z));
		}
		return pArray;
	}

	//设置箭头的高度，保证其在一个水平面上
	float setArrowHeight(osg::Vec3Array* pArray, float addheight)
	{
		osg::Vec3Array::iterator itr = pArray->begin(); 
		float height = itr->z();
		for(; itr != pArray->end(); ++itr)
		{
			if(height < itr->z()) height = itr->z();
		}

		osg::Vec3Array::iterator itr1 = pArray->begin();
		for(; itr1 != pArray->end(); ++itr1)
		{
			itr1->_v[2] = height + addheight;
		}
		return height;
	}

	//按照角度采样，只有当拐点的角度大于指定角度时才取该点
	osg::Vec3Array* samplePoint_Angle(osg::Vec3Array* pArray, float angle)
	{
		std::cout<<"origin point number angle: "<<pArray->size()<<std::endl;

		if(!pArray || pArray->size() < 2) return NULL;

		osg::Vec3Array* newpoints = new osg::Vec3Array;
		unsigned int number = pArray->size();
		newpoints->push_back(pArray->at(0));
		osg::Vec3 lastpoint = pArray->at(0);

		for(unsigned int i = 1; i < number - 1; ++i)
		{
			osg::Vec3 backdir = pArray->at(i) - lastpoint;
			osg::Vec3 predir = pArray->at(i + 1) - pArray->at(i);
			backdir.normalize();
			predir.normalize();
			float cosangle = (acos(backdir * predir) / osg::PI) * 180.f;
			if(cosangle > angle)
			{
				newpoints->push_back(pArray->at(i));
				lastpoint = pArray->at(i);
			}
		}
		newpoints->push_back(pArray->at(number - 1));
		std::cout<<"sample point number angle: "<<newpoints->size()<<std::endl;
		return newpoints;
	}
	//按照距离采样，主要针对的是鼠标move或drag事件下取点过多的情况
	osg::Vec3Array* samplePoint_Distance(osg::Vec3Array* pArray, float sampledis) //dis为采样距离
	{
		std::cout<<"origin point number: "<<pArray->size()<<std::endl;

		if(!pArray || pArray->size() < 2) return NULL;

		osg::Vec3Array* newpoints = new osg::Vec3Array;
		osg::Vec3 currPoint, lastPoint;

		lastPoint = pArray->at(0);
		newpoints->push_back(lastPoint);

		for(unsigned int i = 1; i < pArray->size(); ++i)
		{
			currPoint = pArray->at(i);
			float dis = (currPoint - lastPoint).length();

			if(dis > sampledis)
			{
				newpoints->push_back(currPoint);
				lastPoint = currPoint;
			}
		}
		std::cout<<"sample point number: "<<newpoints->size()<<std::endl;
		return newpoints;
	}


public:


	class GeometryDrawer
	{
	public:
		static osg::Geometry* createPolygon(osg::Vec3Array* vertices/*, const osg::Vec4& color*/)
		{
			if (!vertices || vertices->size() < 2) return NULL;

			osg::ref_ptr<osg::Geometry> path = new osg::Geometry;

			osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
			osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

			normals->push_back(osg::Vec3(0.0, 0.0, 1.0));
			colors->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

			path->setVertexArray(vertices);
			path->setNormalArray(normals);
			path->setColorArray(colors);

			path->setNormalBinding(osg::Geometry::BIND_OVERALL);	
			path->setColorBinding(osg::Geometry::BIND_OVERALL);

			osg::StateSet * state = path->getOrCreateStateSet();

			state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN );
			state->setRenderBinDetails(10, "RenderBin");
			state->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			state->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
			state->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);

			path->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON, 0, vertices->size()));

			return path.release();
		}

		//static osg::Geometry* createLineLoop(osg::Vec3Array* vertices, /*const osg::Vec4& color, */float linewidth)
		//{
		//	if (!vertices || vertices->size() < 2) return NULL;

		//	osg::ref_ptr<osg::Geometry> path = new osg::Geometry;

		//	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
		//	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

		//	normals->push_back(osg::Vec3(0.0, 0.0, 1.0));
		//	colors->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

		//	path->setVertexArray(vertices);
		//	path->setNormalArray(normals);
		//	path->setColorArray(colors);

		//	path->setNormalBinding(osg::Geometry::BIND_OVERALL);	
		//	path->setColorBinding(osg::Geometry::BIND_OVERALL);

		//	osg::StateSet * state = path->getOrCreateStateSet();

		//	state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN );
		//	state->setRenderBinDetails(10, "RenderBin");
		//	state->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
		//	state->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
		//	state->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);

		//	osg::LineWidth * lw = new osg::LineWidth;
		//	lw->setWidth(linewidth);
		//	state->setAttributeAndModes(lw, osg::StateAttribute::ON);

		//	path->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, vertices->size()));

		//	return path.release();
		//}

		static osg::Geode* createPolygonGeode(osg::Vec3Array* vertices/*, const osg::Vec4& color*/)
		{
			osg::Geode * geode = new osg::Geode;

			osg::Geometry* geom = createPolygon(vertices/*, color*/);
			osg::ref_ptr<osgUtil::Tessellator> tess = new osgUtil::Tessellator;
			tess->setTessellationType(osgUtil::Tessellator::TESS_TYPE_POLYGONS);
			tess->setBoundaryOnly(false);
			tess->setWindingType(osgUtil::Tessellator::TESS_WINDING_NONZERO);
			tess->retessellatePolygons(*geom);

			geode->addDrawable(geom);

			return geode;
		}

		//static osg::Geode* createLineLoopGeode(osg::Vec3Array* vertices, /*const osg::Vec4& color, */float linewidth)
		//{
		//	osg::Geode * geode = new osg::Geode;

		//	osg::Geometry* geom = createLineLoop(vertices, /*color, */linewidth);
		//	osg::ref_ptr<osgUtil::Tessellator> tess = new osgUtil::Tessellator;
		//	tess->setTessellationType(osgUtil::Tessellator::TESS_TYPE_GEOMETRY);
		//	tess->setBoundaryOnly(false);
		//	tess->setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD);
		//	tess->retessellatePolygons(*geom);

		//	geode->addDrawable(geom);

		//	return geode;
		//}

	};


};

class PLOTTING_EXPORT PlottingArrowMgr
{
public:
	static PlottingArrowMgr* ins()
	{
		static PlottingArrowMgr* pa = new PlottingArrowMgr;
		return pa;
	}

	~PlottingArrowMgr() {}

	void setParent(osg::Group* parent) 
	{ 
		_parent = parent; 
	}

	void init()
	{
		if (_parent && _group == NULL)
		{
			_group = new osg::Group;
			_parent->addChild(_group);
			_color = osg::Vec4(1.f, 0.f, 0.f, 0.6f);
			_width = 2.f;
		}
	}

	void setColor(const osg::Vec4& color = osg::Vec4(1.f, 0.f, 0.f, 1.f))
	{
		_color = color;
	}

	//
	void setImage(const std::string& image)
	{
		m_strImage = image;
	}

	void setArray(osg::Vec3Array* pArray)
	{
		_array = pArray;
	}

	void setWidth(float width)
	{
		_width = width;
	}

	void add(std::string& name = std::string(""))
	{
		if(!_array || _array->size() < 2) return;

		if(name.empty()) //若name为空，则设置缺省名称
		{
			//unsigned int number = _group->getNumChildren();
			static int number = 1;
			std::ostringstream os; os<<number++;
			name = std::string("plotting_arrow_") + os.str();
		}

		if(isExist(name)) return; //存在该名称的箭头

		osg::ref_ptr<PlottingArrow> arrow = new PlottingArrow;
		arrow->setResPath(m_strImage);
		if (arrow->create(name, _array, _color, _width))
		{
			_arrowList.push_back(arrow.get());
			
			_group->addChild(arrow);
		}
	}

	void remove(const std::string& name)
	{
		unsigned int number = _group->getNumChildren();
		if(!number) return;

		if(name.empty()) return;

		for(unsigned int i = 0; i < number; ++i)
		{
			osg::Node* child = _group->getChild(i);
			if(child->getName() == name) 
			{
				_arrowList.erase(std::find(_arrowList.begin(),_arrowList.end(),child));

				_group->removeChild(child);

				return;
			}
		}
	}

	void remove(osg::Node* node)
	{
		if(!node) return;

		unsigned int number = _group->getNumChildren();
		if(!number) return;

		for(unsigned int i = 0; i < number; ++i)
		{
			osg::Node* child = _group->getChild(i);
			if(child == node) 
			{
				_arrowList.erase(std::find(_arrowList.begin(),_arrowList.end(),child));

				_group->removeChild(child);
				
				return;
			}
		}
	}

	bool isExist(const std::string& name)
	{
		unsigned int number = _group->getNumChildren();
		if(!number) return false;

		for(unsigned int i = 0; i < number; ++i)
		{
			osg::Node* child = _group->getChild(i);
			if(child->getName() == name) 
			{
				return true;
			}
		}

		return false;
	}

	void clear()
	{
		if(_group) _group->removeChildren(0, _group->getNumChildren());

		_arrowList.clear();
	}

	std::vector<PlottingArrow *> &getArrowList() { return _arrowList; }

protected:
	PlottingArrowMgr() {}
	
	osg::ref_ptr<osg::Group> _parent;
	osg::ref_ptr<osg::Group> _group;

	osg::Vec4 _color;
	osg::ref_ptr<osg::Vec3Array> _array;
	float _width;
	std::string m_strImage;
	std::vector<PlottingArrow *> _arrowList;
};

#endif