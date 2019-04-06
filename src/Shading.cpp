#include "../inc/Shading.h"

#include <cmath>

Shading::Shading()
{

}

Shading::~Shading()
{

}

Phong::Phong()
{

}

Phong::~Phong()
{

}

void Phong::GetPixelShade(const Material& aMaterial, const rt::Shape* aShape, const std::vector<rt::Shape*>& aShapes, const std::vector<rt::LightSource>& aLightSources, const rt::VectorF& aPixelNormal, const rt::VectorF& aHitPosition, const rt::VectorF& aCameraPosition, rt::Color& aOutColor)
{
	float intensity = aMaterial.myAmbientReflection;

	for (const auto& lightSource : aLightSources)
	{
		for (const auto& shape : aShapes)
		{
			if (shape == aShape)
				continue;

			rt::VectorF rayVector = (lightSource.myPosition - aHitPosition).Normalize();

			float distance = 0.f;
			rt::VectorF hitPosition;
			rt::VectorF hitNormal;

			if (shape->IsIntersecting(rayVector, aHitPosition, distance, hitPosition, hitNormal))
			{
				aOutColor = aOutColor * aMaterial.myAmbientReflection;
				return;
			}
		}

		const rt::VectorF L = (lightSource.myPosition - aHitPosition).Normalize();
		const rt::VectorF& N = aPixelNormal;
		const rt::VectorF V = (aCameraPosition - aHitPosition).Normalize();

		const float diffuse = (L.GetMaxDot(N) * aMaterial.myDiffuseReflection);

		const rt::VectorF R = (N * N.GetMaxDot(L) * 2.f) - L;
		const float RV = R.GetMaxDot(V);
		const float specular = (std::powf(RV, aMaterial.myShininess) * aMaterial.mySpecularReflection);

		intensity += (diffuse + specular) * lightSource.myIntensity;
	}

	aOutColor = aOutColor * intensity;
}
