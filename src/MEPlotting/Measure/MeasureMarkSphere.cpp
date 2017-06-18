#include <MeasureTool\MeasureMarkSphere.h>

MeasureMarkSphere::MeasureMarkSphere(void)
{
	getOrCreateStateSet()->setRenderBinDetails(10, "RenderBin");
}

MeasureMarkSphere::~MeasureMarkSphere(void)
{
}

void MeasureMarkSphere::addMarkSphere(const osg::Vec3 pos)
{
	osg::AutoTransform* autoTrans = new osg::AutoTransform;
	autoTrans->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_CAMERA);
	autoTrans->setAutoScaleToScreen(true);
	autoTrans->setMinimumScale(0.01);
	osg::ShapeDrawable* sphere = NULL;
	sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), 3));
	sphere->setColor(osg::Vec4(0, 0.8, 0, 0.8));
	osg::Geode* geode = new osg::Geode;
	geode->addDrawable(sphere);
	autoTrans->addChild(geode);
	autoTrans->setPosition(pos);
	this->addChild(autoTrans);
}
