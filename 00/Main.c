#include "Renderer.h"

int main(int argc, const char *argv[])
{
	FxsImage *img = FxsImageCreate(640, 480, 3);
	ObjectPtr o = ObjectCreate("cube.obj");
	RendererPtr r = RendererCreate(img, o);

	RendererRender(r, "Test.bmp", 60.0f);

    return 0;
}
