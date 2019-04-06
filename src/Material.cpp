
#include "../inc/Material.h"

Material::Material(float aSpectularReflection, float aDiffuseReflection, float aAmbientReflection, float aShininess)
	: mySpecularReflection(aSpectularReflection)
	, myDiffuseReflection(aDiffuseReflection)
	, myAmbientReflection(aAmbientReflection)
	, myShininess(aShininess)
{

}

Material::~Material()
{

}
