#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/CompositeViewer>

int main()
{
	osg::ref_ptr<osgViewer::View> view1 = new osgViewer::View();
	view1->setUpViewInWindow(0, 50, 320, 240);
	view1->setSceneData(osgDB::readNodeFile("cow.osg"));

	osg::ref_ptr<osgViewer::View> view2 = new osgViewer::View();
	view2->setUpViewInWindow(320, 50, 320, 240);
	view2->setSceneData(osgDB::readNodeFile("cessna.osg"));

	osg::ref_ptr<osgViewer::View> view3 = new osgViewer::View();
	view3->setUpViewInWindow(640, 50, 320, 240);
	view3->setSceneData(osgDB::readNodeFile("axes.osgt"));

	osgViewer::CompositeViewer compositeViewer;
	compositeViewer.addView(view1);
	compositeViewer.addView(view2);
	compositeViewer.addView(view3);
	return compositeViewer.run();
}