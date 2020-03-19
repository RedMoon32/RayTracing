#include "anti_aliasing.h"

AntiAliasing::AntiAliasing(short width, short height) :Refraction(width, height)
{
}

AntiAliasing::~AntiAliasing()
{
}

void AntiAliasing::DrawScene()
{
	camera.SetRenderTargetSize(width * 2, height * 2);

#pragma omp parallel for
	for (short x = 0; x < width; x++)
	{

#pragma omp parallel for
		for (short y = 0; y < height; y++)
		{

			Ray ray0 = camera.GetCameraRay(2 * x, 2 * y);
			Ray ray1 = camera.GetCameraRay(2 * x + 1, 2 * y);
			Ray ray2 = camera.GetCameraRay(2 * x, 2 * y + 1);
			Ray ray3 = camera.GetCameraRay(2 * x + 1, 2 * y + 1);

			Payload payload0 = TraceRay(ray0, raytracing_depth);
			Payload payload1 = TraceRay(ray1, raytracing_depth);
			Payload payload2 = TraceRay(ray2, raytracing_depth);
			Payload payload3 = TraceRay(ray3, raytracing_depth);

			float3 color = payload0.color + payload1.color + payload2.color + payload3.color;
			SetPixel(x, y, color / 4.f);
		}

	}
}