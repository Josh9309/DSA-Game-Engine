#include "GameObject.h"




GameObject::GameObject()
{
	transform.loc = vec3(0, 0, 0);
	transform.rot = vec3(0, 0, 0);
	transform.size = vec3(1, 1, 1);
	rigidBody.velocity = vec3(0, 0, 0);
	rigidBody.force = vec3(0, 0, 0);
	rigidBody.mass = 1.0f;
	colliderType = axis_Aligned_Bounding_Box;
}


GameObject::~GameObject()
{
}

GameObject::GameObject(Texture text, vec3 loc, vec3 rot, vec3 siz, Colliders collide)
{
	texture = text;
	transform.loc = loc;
	transform.rot = rot;
	transform.size = siz;
	colliderType = collide;
	rigidBody.mass = 1.0f;
}

void GameObject::addForce(vec3 addedForce, float deltaTime)
{
	////calculate velocity
	//vec3 vel = (addedForce / deltaTime) + rigidBody.velocity;
	////calculate acceleration
	//vec3 acceleration = (vel - rigidBody.velocity) / deltaTime;
	////calculate force 
	//rigidBody.force += rigidBody.mass * acceleration;
	////store new velocity
	//rigidBody.velocity = vel;

	////location change
	//vec3 deltaR = rigidBody.velocity * deltaTime;
	//transform.loc = (deltaR + transform.loc);

	
	rigidBody.force = addedForce;
	rigidBody.velocity += (rigidBody.force/rigidBody.mass) *deltaTime;
	rigidBody.force = vec3();
	transform.loc += rigidBody.velocity *deltaTime;
	
}

void GameObject::resetVelocity()
{
	rigidBody.velocity = vec3(0, 0, 0);
}

bool GameObject::collidesWith(GameObject & object2)
{
	//one of objects has  colliderType of colliderless
	if(object2.colliderType == colliderless || colliderType == colliderless)
	{
		return false;
	}
	
	//both objects has a colliderType of sphere
	if (colliderType == sphere && object2.colliderType == sphere) 
	{
		float dist = sqrt(pow((transform.loc.x - object2.transform.loc.x), 2) + pow((transform.loc.y - object2.transform.loc.y), 2));
		float sum = transform.size.x + object2.transform.size.x;

		if (dist > sum) 
		{
			return false;
		}
		else 
		{
			return true;
		}
	}

	//both objects have a colliderType of AABB
	if (colliderType == axis_Aligned_Bounding_Box && object2.colliderType == axis_Aligned_Bounding_Box)
	{ 
		float minXB = object2.transform.loc.x - object2.transform.size.x; //from origin subtract the size x
		float maxXB = object2.transform.loc.x + object2.transform.size.x;
		float minYB = object2.transform.loc.y - object2.transform.size.y; //from origin subtract the size x
		float maxYB = object2.transform.loc.y + object2.transform.size.y;
		float minZB = object2.transform.loc.z - object2.transform.size.z; //from origin subtract the size x
		float maxZB = object2.transform.loc.z + object2.transform.size.z;

		float minXA = transform.loc.x - transform.size.x; //from origin subtract the size x
		float maxXA = transform.loc.x + transform.size.x;
		float minYA = transform.loc.y - transform.size.y; //from origin subtract the size x
		float maxYA = transform.loc.y + transform.size.y;
		float minZA = transform.loc.z - transform.size.z; //from origin subtract the size x
		float maxZA = transform.loc.z + transform.size.z;

		if(minXB < maxXA && maxXB > minXA && minYB < maxYA && maxYB > minYA && minZB < maxZA && maxZB > minZA)
		{
			return true;
		}

		cout << "AABB" << endl;
		return false;
	}

	//this is AABB and object 2 is Sphere
	if(colliderType == axis_Aligned_Bounding_Box && object2.colliderType == sphere )
	{
		float dist =0.0f; //distance^2

		if(object2.transform.loc.x < transform.loc.x-transform.size.x)
		{
			//if sphere center is left of box
			dist += pow(((transform.loc.x - transform.size.x) - object2.transform.loc.x),2); //good
		}
		else if(object2.transform.loc.x > transform.loc.x-transform.size.x)
		{
			//if sphere center is right of box
			dist += pow((object2.transform.loc.x - (transform.loc.x + transform.size.x)), 2);//good
		}
		else
		{
		}

		//sphere is above the top of box
		if(object2.transform.loc.y < transform.loc.y-transform.size.y)
		{
			dist += pow((object2.transform.loc.y - (transform.loc.y + transform.size.y)), 2);
		}
		//sphere is bellow bottom box
		if(object2.transform.loc.y > transform.loc.y-transform.size.y)
		{
			dist += pow(((transform.loc.y - transform.size.y) - object2.transform.loc.y), 2);
		}
		else
		{}

		//sphere is in front of box
		if(object2.transform.loc.z > transform.loc.z-transform.size.z)
		{
			dist += pow((object2.transform.loc.z - (transform.loc.z + transform.size.z)), 2);
		}
		//sphere is behind box
		if(object2.transform.loc.z < transform.loc.z-transform.size.z)
		{
			dist += pow(((transform.loc.z - transform.size.z) - object2.transform.loc.z), 2);
		}
		else 
		{}

		if(dist < pow(object2.transform.size.x, 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//object2 is AABB and this is Sphere
	if (object2.colliderType == axis_Aligned_Bounding_Box && colliderType == sphere)
	{
		float dist = 0.0f; //distance^2

		if (transform.loc.x < object2.transform.loc.x)
		{
			//if sphere center is left of box
			dist += pow(((object2.transform.loc.x - object2.transform.size.x) - transform.loc.x), 2);
		}
		if (transform.loc.x > object2.transform.loc.x)
		{
			//if sphere center is right of box
			dist += pow((transform.loc.x - (object2.transform.loc.x + object2.transform.size.x)), 2);
		}
		else
		{}

		//sphere is above the top of box
		if (transform.loc.y > object2.transform.loc.y)
		{
			dist += pow((transform.loc.y - (object2.transform.loc.y + object2.transform.size.y)), 2);
		}
		//sphere is bellow bottom box
		if (transform.loc.y < object2.transform.loc.y)
		{
			dist += pow(((object2.transform.loc.y - object2.transform.size.y) - transform.loc.y), 2);
		}
		else
		{}

		//sphere is in front of box
		if (transform.loc.z > object2.transform.loc.z)
		{
			dist += pow((transform.loc.z - (object2.transform.loc.z + object2.transform.size.z)), 2);
		}
		//sphere is behind box
		if (transform.loc.z < object2.transform.loc.z)
		{
			dist += pow(((object2.transform.loc.z - object2.transform.size.z) - transform.loc.z), 2);
		}
		else
		{}

		if (dist < pow(transform.size.x, 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}



