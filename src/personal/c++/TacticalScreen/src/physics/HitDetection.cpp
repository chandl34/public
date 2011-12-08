#include "HitDetection.h"
#include "../models/types/mapModels/DoorModel.h"
#include "../world/World.h"

HitDetection::HitDetection(){}
HitDetection::~HitDetection(){}

Hit* HitDetection::hitDetect(Ray* r, float grav, bool proj){
	float ox = r->getOrigin()->get(X);
	float oy = r->getOrigin()->get(Y);
	float oz = r->getOrigin()->get(Z);
	float ody = r->getDirection()->get(Y);
	
	float x = ox, y = oy, z = oz;
	float dx = r->getDirection()->get(X)*0.01f;
	float dy = ody*0.01f;
	float dz = r->getDirection()->get(Z)*0.01f;
	
	float g = grav*0.0001f;
		
	float time = 0;
		
	Coordinate* c = World::getCoord((int)x, (int)z);
	Coordinate* temp = c;
	bool firstTime = true;

	Hit* hit = new Hit(proj);
	while(hit->getDuration() < -1){
		if(y < 0){
			//cout << "HIT GROUND!" << endl << endl;
			hit->setType(HIT_GROUND);
			hit->setDuration(1000);  // Arbitrary
			r->getOrigin()->set(ox, oy, oz);
			r->getDirection()->set(Y, ody);
			return hit;
		}
		else if(c == NULL){
			//cout << "WENT OUT OF BOUNDS!" << endl << endl;
			hit->setType(HIT_BOUNDS);
			hit->setDuration(1000);  // Arbitrary
			r->getOrigin()->set(ox, oy, oz);
			r->getDirection()->set(Y, ody);
			return hit;
		}
		if(firstTime)
			firstTime = false;
		else // Prevents shooting/seeing self
			intersectCharacter(r, c, hit, time);	
		intersectBreakable(r, c, hit, time);

		while(temp == c){
			dy -= g; 
			x += dx; 
			y += dy; 
			z += dz;
			r->getOrigin()->set(x, y, z);
			r->getDirection()->set(Y, dy);	
			temp = World::getCoord((int)x, (int)z);	
			time += 0.01f;
		}
		c = temp;
	}

	r->getOrigin()->set(ox, oy, oz);
	r->getDirection()->set(Y, ody);
	return hit;
}

void HitDetection::intersectBreakable(Ray* r, Coordinate* c, Hit* hit, float time){
	BreakableModel* breakable;
	Block* block = World::getSelectedMap()->getBlock(c);

	breakable = block->getObject()->getModel();
	if(breakable != NULL){ 
		if(intersectModel(r, breakable->getModel(), c, hit, time) == CLOSEST){
			hit->setType(HIT_OBJECT);
			hit->setCoord(c);
			/*
			if(breakable->getType() == FENCE)
				cout << "HIT FENCE!" << endl << endl;
			else
				cout << "HIT OBJECT!" << endl << endl;
			 */
		}
	}

	for(int j = 0; j < 2; j++){
		if(block->getWall(j)->getBlockingDoors() > 0){
			Coordinate* temp;
			DoorModel* d;
			if(j == LEFT){				
				temp = World::getCoord(c->get(X), c->get(Y) - 1);
				if(temp != NULL){
					d = World::getSelectedMap()->getBlock(temp)->getWall(RIGHT)->getDoor();
					if(d != NULL && !d->getMirror() && !d->getShift() && d->getAngle() == OPEN)
						intersectDoor(r, RIGHT, temp, hit, time);
				}
			}
			else{
				temp = World::getCoord(c->get(X) + 1, c->get(Y));
				if(temp != NULL){
					d = World::getSelectedMap()->getBlock(temp)->getWall(LEFT)->getDoor();
					if(d != NULL && !d->getMirror() && !d->getShift() && d->getAngle() == OPEN)
						intersectDoor(r, LEFT, temp, hit, time);
				}
			}
		}

		breakable = block->getWall(j)->getFrame();
		if(breakable != NULL){ 
			if(intersectModel(r, breakable->getModel(), c, hit, time) == CLOSEST){
				if(breakable->getType() == WINDOWFRAME){
					hit->setType(HIT_WINDOWFRAME);
					hit->setSide(j);
				}
				else
					hit->setType(HIT_OBJECT);
				hit->setCoord(c);
				/*
				cout << "HIT WALL!";
				if(j == LEFT)
					cout << " - LEFT!" << endl << endl;
				else
					cout << " - RIGHT!" << endl << endl;
				 */
			}
			if(breakable->getType() == WINDOWFRAME && hit->isProjectile()){
				breakable = block->getWall(j)->getWindow();
				float temp = hit->getDuration();
				if(intersectModel(r, breakable->getModel(), c, hit, time) == CLOSEST){
					hit->addWindow((int)hit->getDuration() + 1, c, breakable);
					hit->setDuration(temp);	// Prevents window from stopping the bullet
					/*
					cout << "WENT THROUGH WINDOW!";
					if(j == LEFT)
						cout << " - LEFT!" << endl << endl;
					else
						cout << " - RIGHT!" << endl << endl;
					 */
				}			
			}
			else if(breakable->getType() == DOORFRAME)
				intersectDoor(r, j, c, hit, time);
		}
	}
}

void HitDetection::intersectDoor(Ray* r, int mir, Coordinate* c, Hit* hit, float time){
	DoorModel* d = World::getSelectedMap()->getBlock(c)->getWall(mir)->getDoor();
	if(intersectModel(r, d->getModel(), c, hit, time) == CLOSEST){
		hit->setType(HIT_OBJECT);
		hit->setCoord(c);
		/*
		cout << "HIT DOOR!";
		if(mir == LEFT)
			cout << " - LEFT!" << endl;
		else
			cout << " - RIGHT!" << endl;
		 */
	}
}

void HitDetection::intersectCharacter(Ray* r, Coordinate* c, Hit* hit, float time){
	Character* character = World::getSelectedMap()->getBlock(c)->getCharacter();
	ModelWrapper* charModel;
	int test;
	if(character != NULL){
		charModel = character->getCharModel()->getModelWrapper(HEAD);
		test = intersectModel(r, charModel->getModel(), c, hit, time);
		if(test != FALSE){
			if(test == CLOSEST){
				//cout << "HIT HEAD!" << endl << endl;
				hit->setType(HEAD);
				hit->setCoord(c);
			}
			return;
		}
		charModel = character->getCharModel()->getModelWrapper(TORSO);
		test = intersectModel(r, charModel->getModel(), c, hit, time);
		if(test != FALSE){
			if(test == CLOSEST){
				//cout << "HIT TORSO!" << endl << endl;
				hit->setType(TORSO);
				hit->setCoord(c);
			}
			return;
		}
		charModel = character->getCharModel()->getModelWrapper(RIGHTLEG);
		test = intersectModel(r, charModel->getModel(), c, hit, time);
		if(test != FALSE){
			if(test == CLOSEST){
				//cout << "HIT LEGS!" << endl << endl;
				hit->setType(RIGHTLEG);
				hit->setCoord(c);
			}
			return;
		}
		charModel = character->getCharModel()->getModelWrapper(LEFTLEG);
		test = intersectModel(r, charModel->getModel(), c, hit, time);
		if(test != FALSE){
			if(test == CLOSEST){
				//cout << "HIT LEGS!" << endl << endl;
				hit->setType(LEFTLEG);
				hit->setCoord(c);
			}
			return;
		}
		charModel = character->getCharModel()->getModelWrapper(RIGHTARM);
		test = intersectModel(r, charModel->getModel(), c, hit, time);
		if(test != FALSE){
			if(test == CLOSEST){
				//cout << "HIT TORSO!" << endl << endl;
				hit->setType(TORSO);
				hit->setCoord(c);
			}
			return;
		}
		charModel = character->getCharModel()->getModelWrapper(LEFTARM);
		test = intersectModel(r, charModel->getModel(), c, hit, time);
		if(test != FALSE){
			if(test == CLOSEST){
				//cout << "HIT TORSO!" << endl << endl;
				hit->setType(TORSO);
				hit->setCoord(c);
			}
			return;
		}
	}
}

int HitDetection::intersectModel(Ray* r, Model* m, Coordinate* c, Hit* hit, float time){
	if(m == NULL)
		return FALSE;
	int test;
	for(size_t i = 0; i < m->getShapeCount(); i++){
		for(size_t j = 0; j < m->getShape(i)->getTriangleCount(); j++){		
			test = intersectTriangle(r, m->getShape(i)->getTriangle(j), c, hit, time);
			if(test != FALSE)
				return test;
		}
	}
	return FALSE;
}

int HitDetection::intersectTriangle(Ray* r, Triangle* tri, Coordinate* c, Hit* hit, float time){
	Vector* edge1 = new Vector(tri->get(1), tri->get(0));
	Vector* edge2 = new Vector(tri->get(2), tri->get(0));
	Vector* pvec = r->getDirection()->crossProduct(edge2);
	float det = edge1->dotProduct(pvec);
	if(det < EPSILON){	
		delete edge1;
		delete edge2;
		delete pvec;
		return FALSE;
	}
	Vertex* vert0 = new Vertex(tri->get(0)->get(X) + c->get(X), 
			tri->get(0)->get(Y), tri->get(0)->get(Z) + c->get(Y));
	Vector* tvec = new Vector(r->getOrigin(), vert0);
	delete vert0;
	float u = tvec->dotProduct(pvec);
	delete pvec;
	if(u < 0.0f || u > det){
		delete edge1;
		delete edge2;
		delete tvec;
		return FALSE;
	}
	Vector* qvec = tvec->crossProduct(edge1);
	delete tvec;
	delete edge1;
	float v = r->getDirection()->dotProduct(qvec);
	if(v < 0.0f || u + v > det){
		delete edge2;
		delete qvec;	
		return FALSE;	
	}
	float t = edge2->dotProduct(qvec)/det + time;
	delete edge2;
	delete qvec;
	if(hit->getDuration() < -1 || t < hit->getDuration()){
		cout << "Time: " <<  t << endl;
		hit->setDuration(t);
		return CLOSEST;
	}
	return TRUE;	
}
