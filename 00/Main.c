#include "Renderer.h"

int main(int argc, const char *argv[])
{
	FxsImage *img = FxsImageCreate(640, 480, 3);
	ObjectPtr o = ObjectCreate("bunny.obj");
    FxsMatrix4 c2w;
    FxsVector3 eye, foc, up;
    FxsVector3Make(&eye, 0.0f, 0.0f, 5.0f);
    FxsVector3Make(&foc, 0.0f, 0.0f, 0.0f);
    FxsVector3Make(&up, 0.0f, 1.0f, 0.0f);
    FxsMatrix4MakeCameraToWorld(&c2w, &eye, &foc, &up);
//    FxsMatrix4MakeIdentity(&c2w);
	RenderContext rc;
	rc.object = o;
	rc.image = img;
    rc.cameraToWorld = c2w;
	rc.bgColor[0] = 0;
	rc.bgColor[1] = 0;
	rc.bgColor[2] = 0;
	rc.defaultColor[0] = 255;
	rc.defaultColor[1] = 0;
	rc.defaultColor[2] = 0;

	RendererPtr r = RendererCreate(&rc);

	RendererRender(r, "Test.bmp", 60.0f);

    return 0;
}
