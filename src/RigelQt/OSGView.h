#pragma once
#include <QQuickFramebufferObject>
#include <osg/Group>
#include <osg/Camera>
#include <osgViewer/Viewer>

#include <QSGSimpleTextureNode>
#include <QSGDynamicTexture>
#include <QOpenGLFramebufferObject>

class OSGRender;

class OSGView : public QQuickFramebufferObject
{
	Q_OBJECT
public:
    OSGView(QQuickItem *parent = Q_NULLPTR);
    virtual ~OSGView();
public:
	osg::Camera* getCamera();

    osgViewer::Viewer* getViewer();

    osg::Group* getSceneData();

public slots:
	Q_INVOKABLE void slotHome();

protected:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *uppData);
	void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry);

    /***事件处理***/
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	Renderer* createRenderer() const;

private:
	void initOSG();

private:
	friend class OSGRender;
	OSGView* m_pOSGItem;
	osg::Group* m_pRoot;
	osg::Camera* m_pCamera;
	osgViewer::Viewer* m_pViewer;
	osgGA::EventQueue* m_pEventQueue;
};