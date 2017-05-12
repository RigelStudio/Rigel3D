#include "TextureRolling.h"
#include "MECore\FileUtils.h"
#include "Core.h"
#include <osg/Program>
#include <osgDB/ReadFile>


TextureRolling::TextureRolling()
{
	m_pStrip = nullptr;
	m_pStateSet = getOrCreateStateSet();
	m_pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON |
		osg::StateAttribute::OVERRIDE);
	createStrip();
}


TextureRolling::~TextureRolling()
{
}

void TextureRolling::createStrip()
{
	if (m_pStrip == nullptr)
	{
		auto _array = new osg::Vec3Array;
		_array->push_back(osg::Vec3(0, 0, 0));
		_array->push_back(osg::Vec3(20, 0, 0));
		_array->push_back(osg::Vec3(5, 10, 0));
		//_array->push_back(osg::Vec3(8, 3, 0));
		m_pStrip = new GeometryStrip(_array);
		m_pStrip->setTexture(FileUtils::ins()->getPath(std::string("Data/Images/arraw_strip.png")));
	}
	addChild(m_pStrip);

	createShader();
}

void TextureRolling::createShader()

{
	osg::Program* profram = new osg::Program;
	osg::Shader* vertShader = osgDB::readShaderFile(osg::Shader::VERTEX, 
		FileUtils::ins()->getPath(std::string("Data/Shaders/texRolling.vert")));

	osg::Shader* fragShader = osgDB::readShaderFile(osg::Shader::FRAGMENT, 
		FileUtils::ins()->getPath(std::string("Data/Shaders/texRolling.frag")));

	profram->addShader(vertShader);
	profram->addShader(fragShader);

	m_pStateSet->addUniform(new osg::Uniform("sampler", 0));
	m_pStateSet->setAttributeAndModes(profram);
}
