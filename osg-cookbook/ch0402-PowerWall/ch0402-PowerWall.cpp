#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include "../common/CommonFunctions"

osg::Camera* createSlaveCamera(int x, int y, int width, int height)
{
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();
	traits->screenNum = 0;
	traits->x = x;
	traits->y = y;
	traits->width = width;
	traits->height = height;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);
	if (!gc) return NULL;

	osg::ref_ptr<osg::Camera> camera = new osg::Camera();
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(0, 0, width, height));

	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);

	return camera.release();
}

int main()
{
	int totalWidth = 1024;
	int totalHeight = 768;
	int numColumns = 3;
	int numRows = 3;

	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("cow.osg");
	osgViewer::Viewer viewer;
	int tileWidth = totalWidth / numColumns;
	int tileHeight = totalHeight / numRows;
	for (int i=0; i<numRows; ++i)
	{
		for (int j=0; j<numColumns; ++j)
		{
			osg::Camera* camera = createSlaveCamera(
				tileWidth*j, totalHeight - tileHeight*(i+1), tileWidth-1, tileHeight-1);
			osg::Matrix projOffset = osg::Matrix::scale(numColumns, numRows, 1.0) * 
				osg::Matrix::translate(numColumns - 1 - 2*j, numRows - 1 - 2*i, 0.0);
			viewer.addSlave(camera, projOffset, osg::Matrix(), true);
		}
	}

	viewer.setSceneData(scene);
	return viewer.run();
}