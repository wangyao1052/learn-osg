#include <osgViewer\Viewer>

float boxVertices[][3] = {
	// Top
	{ 1.0f, 1.0f,-1.0f},
	{-1.0f, 1.0f,-1.0f},
	{-1.0f, 1.0f, 1.0f},
	{ 1.0f, 1.0f, 1.0f},
	// Bottom
	{ 1.0f,-1.0f, 1.0f},
	{-1.0f,-1.0f, 1.0f},
	{-1.0f,-1.0f,-1.0f},
	{ 1.0f,-1.0f,-1.0f},
	// Front
	{ 1.0f, 1.0f, 1.0f},
	{-1.0f, 1.0f, 1.0f},
	{-1.0f,-1.0f, 1.0f},
	{ 1.0f,-1.0f, 1.0f},
	// Back
	{ 1.0f,-1.0f,-1.0f},
	{-1.0f,-1.0f,-1.0f},
	{-1.0f, 1.0f,-1.0f},
	{ 1.0f, 1.0f,-1.0f},
	// Left
	{-1.0f, 1.0f, 1.0f},
	{-1.0f, 1.0f,-1.0f},
	{-1.0f,-1.0f,-1.0f},
	{-1.0f,-1.0f, 1.0f},
	// Right
	{ 1.0f, 1.0f,-1.0f},
	{ 1.0f, 1.0f, 1.0f},
	{ 1.0f,-1.0f, 1.0f},
	{ 1.0f,-1.0f,-1.0f}
};

const float boxColors[][3] = {
	{0.0f, 1.0f, 0.0f},
	{1.0f, 0.5f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f}, 
	{1.0f, 0.0f, 1.0f}
};

osg::Node* createScene()
{
	osg::Geode* geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> boxGeometry = new osg::Geometry();
	{
		// vertices
		osg::Vec3Array* vertices = new osg::Vec3Array();
		int nVertices = sizeof(boxVertices) / sizeof(boxVertices[0]);
		for (int i = 0; i < nVertices; ++i)
		{
			vertices->push_back(osg::Vec3(boxVertices[i][0], boxVertices[i][1], boxVertices[i][2]));
		}
		boxGeometry->setVertexArray(vertices);

		// colors
		osg::Vec4Array* colors = new osg::Vec4Array();
		int nColors = sizeof(boxColors) / sizeof(boxColors[0]);
		for (int i = 0; i < nColors; ++i)
		{
			colors->push_back(osg::Vec4(boxColors[i][0], boxColors[i][1], boxColors[i][2], 1.0f));
		}
		boxGeometry->setColorArray(colors, osg::Array::BIND_PER_PRIMITIVE_SET);

		// primitive set
		int nVertsPerPrimitiveSet = 4;
		for (int i = 0, pos = 0; i < nVertices / nVertsPerPrimitiveSet; ++i, pos += nVertsPerPrimitiveSet)
		{
			boxGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, pos, nVertsPerPrimitiveSet));
		}
	}
	geode->addDrawable(boxGeometry);

	// state set
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	return geode;
}

int main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(createScene());
	return viewer.run();
}