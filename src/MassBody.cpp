
#include "../inc/MassBody.hpp"

rt::MassBody::MassBody(float aGravityForce, float aGravitySphereRadius, const rt::VectorF& aGravityCenter)
	: myGravityForce(aGravityForce)
	, myGravitySphereRadius(aGravitySphereRadius)
	, myGravityCenter(aGravityCenter)
{

}
