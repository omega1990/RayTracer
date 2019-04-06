#pragma once

class Material
{
public:
	Material(float aSpectularReflection, float aDiffuseReflection, float aAmbientReflection, float aShininess);
	~Material();

	float mySpecularReflection;
	float myDiffuseReflection;
	float myAmbientReflection;
	float myShininess;
};

namespace materials
{
	static Material chrome { 0.774f, 0.4f, 0.14f, 128.f * 0.6f };
	static Material bronze{ 0.393f, 0.714f, 0.2125f, 128.f * 0.2f };

}
