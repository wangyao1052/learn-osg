#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/CompositeViewer>

#include "../common/CommonFunctions"

osgViewer::View* create2DView(int x, int y, int width, int height,
	const osg::Vec3d& lookDir, const osg::Vec3d& up,
	osg::GraphicsContext* gc, osg::Node* scene)
{
	osg::ref_ptr<osgViewer::View> view = new osgViewer::View();
	view->getCamera()->setGraphicsContext(gc);
	view->getCamera()->setViewport(x, y, width, height);
	view->setSceneData(scene);

	osg::Vec3d center = scene->getBound().center();
	double radius = scene->getBound().radius();
	view->getCamera()->setViewMatrixAsLookAt(center - lookDir*radius*3.0, center, up);
	view->getCamera()->setProjectionMatrixAsPerspective(30.0f, (double)width/(double)height, 1.0f, 10000.0f);
	
	return view.release();
}

int main()
{
	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("cessna.osg");
	unsigned int width = 800;
	unsigned int height = 600;
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
	if (wsi)
	{
		wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
	}

	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();
	traits->x = 0;
	traits->y = 0;
	traits->width = width;
	traits->height = height;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);
	if (!gc || !scene) return 1;

	int w_2 = width / 2;
	int h_2 = height / 2;
	osg::ref_ptr<osgViewer::View> top = create2DView(0, h_2, w_2, h_2, -osg::Z_AXIS, osg::Y_AXIS, gc, scene);
	osg::ref_ptr<osgViewer::View> front = create2DView(w_2, h_2, w_2, h_2, osg::Y_AXIS, osg::Z_AXIS, gc, scene);
	osg::ref_ptr<osgViewer::View> left = create2DView(0, 0, w_2, h_2, osg::X_AXIS, osg::Z_AXIS, gc, scene);

	osg::ref_ptr<osgViewer::View> mainView = new osgViewer::View();
	mainView->getCamera()->setGraphicsContext(gc);
	mainView->getCamera()->setViewport(w_2, 0, w_2, h_2);
	mainView->setSceneData(scene);
	mainView->setCameraManipulator(new osgGA::TrackballManipulator());

	osgViewer::CompositeViewer viewer;
	viewer.addView(top);
	viewer.addView(front);
	viewer.addView(left);
	viewer.addView(mainView);

	while (!viewer.done())
	{
		viewer.frame();
	}
	return 0;
}