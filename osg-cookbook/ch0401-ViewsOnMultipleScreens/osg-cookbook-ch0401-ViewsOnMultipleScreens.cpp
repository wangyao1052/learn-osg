#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/CompositeViewer>

#include "..\common\CommonFunctions"

osgViewer::View* createView(int screenNum)
{
	unsigned int width = 800;
	unsigned int height = 600;
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
	if (wsi)
	{
		wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(screenNum), width, height);
	}

	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();
	traits->screenNum = screenNum;
	traits->x = 0;
	traits->y = 0;
	traits->width = width;
	traits->height = height;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);
	if (!gc) return NULL;

	osg::ref_ptr<osg::Camera> camera = new osg::Camera();
	camera->setGraphicsContext(gc);
	camera->setViewport(0, 0, width, height);
	camera->setProjectionMatrixAsPerspective(
		30.0f, (double)width / (double)height, 1.0f, 1000.0f);

	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);

	osg::ref_ptr<osgViewer::View> view = new osgViewer::View();
	view->setCamera(camera);
	view->setCameraManipulator(new osgGA::TrackballManipulator());
	return view.release();
}

int main()
{
	osgViewer::CompositeViewer viewer;

	osgViewer::View* view1 = createView(0);
	if (view1)
	{
		view1->setSceneData(osgDB::readNodeFile("cessna.osg"));
		viewer.addView(view1);
	}

	osgViewer::View* view2 = createView(1);
	if (view2)
	{
		view2->setSceneData(osgDB::readNodeFile("cow.osg"));
		viewer.addView(view2);
	}

	return viewer.run();
}