#include <Geometry/GeometryBase.h>
#include <osgDB/ReadFile>

GeometryBase::GeometryBase(void)
{
	m_pColorArray = NULL;
	m_pVertexArray = NULL;
	m_pNormalArray = NULL;
	m_pTextureArray = NULL;
	m_pStateSet = NULL;
	m_pTexture2D = new osg::Texture2D;
	setDataVariance(osg::Object::DYNAMIC);
	init();
}

GeometryBase::~GeometryBase(void)
{
	m_pVertexArray = NULL;
	m_pColorArray = NULL;
	m_pNormalArray = NULL;
	m_pTextureArray = NULL;
	m_pStateSet = NULL;
	m_pSouceArray = NULL;
}

void GeometryBase::addPoint(const osg::Vec3 &pos)
{
	if (pos == osg::Vec3())
	{
		std::cout<<"add the null point"<<std::endl;
	}
	//m_pVertexArray->push_back(pos);
	m_pSouceArray->push_back(pos);
	updateGeomtry();
}

void GeometryBase::setPoint(size_t index, const osg::Vec3 &pos)
{
	if (pos == osg::Vec3())
	{
		std::cout<<"add the null point"<<std::endl;
	}
	size_t size = m_pSouceArray->size();
	if (size > index)
	{
		(*m_pSouceArray)[index] = pos;
	}
	else
	{
		m_pSouceArray->resize(index + 1);
		(*m_pSouceArray)[index] = pos;
	}
	updateGeomtry();
}


osg::Vec3 GeometryBase::firstPoint()
{
	if (m_pSouceArray != NULL)
	{
		if (m_pSouceArray->size() > 0)
		{
			return m_pSouceArray->at(0);
		}
		return osg::Vec3d();
	}
	else
	{
		return osg::Vec3d();
	}
}

void GeometryBase::init()
{
	m_pVertexArray = new osg::Vec3Array;
	m_pVertexArray->clear();
	m_pColorArray = new osg::Vec4Array;
	m_pColorArray->clear();
	m_pNormalArray = new osg::Vec3Array;
	m_pNormalArray->push_back(osg::Z_AXIS);
	m_pTextureArray = new osg::Vec2Array;
	m_pStateSet = getOrCreateStateSet();
	m_pSouceArray = new osg::Vec3Array;
	setVertexArray(m_pVertexArray);
	setColorArray(m_pColorArray);
	setNormalArray(m_pNormalArray);
	setTexCoordArray(0, m_pTextureArray);
	setNormalBinding(Geometry::BIND_OVERALL);
	setUseVertexBufferObjects(true);
	setUseDisplayList(false);
}

size_t GeometryBase::pointSize()
{
	if (m_pSouceArray != NULL)
	{
		return m_pSouceArray->size();
	}
	return 0.0;
}

osg::Vec3 GeometryBase::atPoint(size_t index)
{
	return m_pVertexArray->at(index);
}

osg::Vec3 GeometryBase::lastPoint()
{
	return m_pSouceArray->back();
}

void GeometryBase::setTexture(std::string path)
{
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(path);
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

void GeometryBase::setVertexs(osg::Vec3Array* array)
{
	m_pSouceArray = array;
	updateGeomtry();
}

osg::Vec3Array* GeometryBase::getSouceArray()
{
	return m_pSouceArray;
}
