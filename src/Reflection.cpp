#include "../inc/Reflection.h"
#include "../inc/Shape.hpp"
#include "../inc/Shading.h"

Reflection::Reflection()
{

}

Reflection::~Reflection()
{

}

void Reflection::GetPixelReflection(const Material& aMaterial, const rt::Shape* aShape, const std::vector<rt::Shape*>& aShapes, const std::vector<rt::LightSource*>& aLightSources, const rt::VectorF& aPixelNormal, const rt::VectorF& aHitPosition, const rt::VectorF& aCameraPosition, rt::Color& aOutColor, int aRecursionStep /*= 0*/)
{
	/*if (aRecursionStep++ > 1)
		return;*/

	rt::VectorF rayVectorN = (aHitPosition - aCameraPosition).Normalize();

	// Nadi reflektirajuci vektor
	rt::VectorF reflectedRay = rayVectorN - aPixelNormal * (rayVectorN * aPixelNormal) * 2.f;
	
	// Nadi intersekciju s najblizim objektom
	float distance;
	float minDistance = INT_MAX;
	rt::VectorF hitPosition;
	rt::VectorF hitNormal;
	rt::Shape* reflectedShape = nullptr;
	for (const auto& shape : aShapes)
	{
		if (!shape->GetIsObject())
			continue;

		if (shape == aShape)
			continue;

		if (shape->IsIntersecting(reflectedRay, aHitPosition, distance, hitPosition, hitNormal))
		{
			if (distance < minDistance)
			{
				reflectedShape = shape;
				minDistance = distance;
			}
		}
	}

	if (!reflectedShape)
		return;

	rt::Color color = reflectedShape->GetColor();

	// Izracunaj shade od inters. objekta
	Phong phongShading;
	phongShading.GetPixelShade(reflectedShape->GetMaterial(), reflectedShape, aShapes, aLightSources, hitNormal, hitPosition, aCameraPosition, color);

	aOutColor.Red = (int)(aMaterial.mySpecularReflection * color.Red + aOutColor.Red) / 2;
	aOutColor.Green = (int)(aMaterial.mySpecularReflection * color.Green + aOutColor.Green) / 2;
	aOutColor.Blue = (int)(aMaterial.mySpecularReflection * color.Blue + aOutColor.Blue) / 2;
}
