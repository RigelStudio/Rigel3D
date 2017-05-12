#include "GeometryFloor.h"
#include <osg/Material>
#include <osg/PolygonOffset>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osg/LineWidth>
#include <osg/Image>
#include <osg/Texture2D>

GeometryFloor::GeometryFloor(size_t lenght, size_t width)
{
	createFloor(lenght, width);
}

GeometryFloor::~GeometryFloor(void)
{
}

void GeometryFloor::createFloor(size_t lenght, size_t width)
{
	setName("Plane");
	osg::Geometry* plane = createPlane(lenght, lenght);
	addDrawable(plane);

	plane->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	
	//ÉèÖÃ¿ÌÏßäÖÈ¾×´Ì¬
	osg::Geometry* gird = createPlane(lenght, lenght);
	osg::StateSet* stateset = gird->getOrCreateStateSet();  
	osg::ref_ptr<osg::PolygonOffset> polyoffset = new osg::PolygonOffset;  
	polyoffset->setFactor(1.0f);  
	polyoffset->setUnits(1.0f);

 	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
 	colors->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));
 	gird->setColorArray(colors, osg::Array::BIND_OVERALL);

	osg::ref_ptr<osg::PolygonMode> polymode = new osg::PolygonMode;  
	polymode->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);  
	stateset->setAttribute(polymode);
	stateset->setAttribute(polyoffset);
	stateset->setAttribute(new osg::LineWidth(2.0));
	addDrawable(gird);
}

osg::Geometry*  GeometryFloor::createPlane(size_t lenght, size_t width)
{
	int sideL = 1;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec2Array> texCoord = new osg::Vec2Array;
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.1, 0.1, 0.1, 1.0));
	geom->setColorArray(colors, osg::Array::BIND_OVERALL);

	for (size_t row = 0; row < lenght; row++)
	{
		for (size_t col = 0; col < width; col++)
		{
			int RL = row + sideL;
			int CL = col + sideL;
			vertices->push_back(osg::Vec3(row, col, 0));
			vertices->push_back(osg::Vec3(RL, col, 0));
			vertices->push_back(osg::Vec3(RL, CL, 0));
			vertices->push_back(osg::Vec3(row, CL, 0));
			normals->push_back(osg::Z_AXIS);
			texCoord->push_back(osg::Vec2(row / 50., col / 50.));
			texCoord->push_back(osg::Vec2(RL / 50., col / 50.));
			texCoord->push_back(osg::Vec2(RL / 50., CL / 50.));
			texCoord->push_back(osg::Vec2(row / 50., CL / 50.));
		}
	}
	size_t count = vertices->size();
	for (size_t i = 0; i < count; i++)
	{
		vertices->at(i).x() -= lenght / 2;
		vertices->at(i).y() -= width / 2;
	}
	geom->setVertexArray(vertices);
	geom->setTexCoordArray(0, texCoord);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertices->size()));
	return geom.release();
}

void GeometryFloor::setTexture(std::string imagePath)
{
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(imagePath);
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setImage(image);
	texture->setInternalFormat(GL_RGBA);
	texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_BORDER);
	texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_BORDER);
	getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);
	getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
}
