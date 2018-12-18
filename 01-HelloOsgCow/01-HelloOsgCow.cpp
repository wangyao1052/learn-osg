#include <osgViewer\Viewer>
#include <osgDB\ReadFile>

int main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile("cow.osg"));
	return viewer.run();
}