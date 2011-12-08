#include "Character.h"
#include "../World.h"
#include "../../physics/HitDetection.h"

void Character::setVisible(int v){visible = v;}
int Character::getVisible(){return visible;}
Direction* Character::getLookDir(){return lookDir;}
void Character::clearSeen(){seen.clear();}

void Character::setLookDir(int lookInt){
	lookDir = World::getDir(lookInt);
	model = CharacterModelContainer::open(gender, lookInt, index);
	checkView();
}

void Character::lookAt(Coordinate* c){
	if(path != NULL)
		stopMoving();
	turn(dirTo(c));
}

Direction* Character::dirTo(Coordinate* c){
	int dx = c->get(X) - loc->get(X);
	int dz = c->get(Y) - loc->get(Y);
	int absdx = abs(dx);
	int absdz = abs(dz);

	int finalX, finalZ;
	if(absdx < absdz){
		if(absdx < absdz*0.42f)
			finalX = 0;
		else if(dx < 0)
			finalX = -1;
		else
			finalX = 1;
		if(dz < 0)
			finalZ = -1;
		else
			finalZ = 1;
	}
	else{
		if(absdz < absdx*0.42f)
			finalZ = 0;
		else if(dz < 0)
			finalZ = -1;
		else
			finalZ = 1;
		if(dx < 0)
			finalX = -1;
		else
			finalX = 1;
	}
	return World::getDir(finalX, finalZ);
}

void Character::turn(){
	int tmp = lookDir->getIndex() + lookIncr;
	if(tmp < 0)
		tmp = 7;
	else if(tmp > 7)
		tmp = 0;
	setLookDir(tmp);
	if(targetLook == lookDir)
		turning = false;
}

void Character::turn(Direction* next){
	targetLook = next;
	if(targetLook == lookDir){
		turning = false;
		return;	
	}
	int currentLook = lookDir->getIndex();
	if(currentLook > targetLook->getIndex()){
		int temp = currentLook - targetLook->getIndex();
		if(temp > 4)
			lookIncr = 1;
		else
			lookIncr = -1;
	}
	else{
		int temp = targetLook->getIndex() - currentLook;
		if(temp > 4)
			lookIncr = -1;
		else
			lookIncr = 1;
	}
	turning = true;
}

void Character::findVisible(){
	Character* chr;
	int cLook = lookDir->getIndex();
	int dLook;
	int dx, dy;
	Hit* hit;
	Ray* ray;
	Vertex* origin;
	Vertex* vert = model->getModelWrapper(HEAD)->getModel()->getCenter();
	Vertex* cVert;
	Coordinate* cCoord;
	Vector* vec;
	for(size_t i = 1; i < 3; i++){
		for(size_t j = 0; j < map->getCharacterSize(i); j++){
			chr = map->getCharacter(i, j);	
			cCoord = chr->getCoord();		
			dLook = abs(cLook - dirTo(cCoord)->getIndex());	
			if(dLook <= 1 || dLook == 7){
				dx = abs(loc->get(X) - cCoord->get(X));
				dy = abs(loc->get(Y) - cCoord->get(Y));
				if(dx + dy < 50){
					origin = new Vertex(vert->get(X) + loc->get(X),
							vert->get(Y), vert->get(Z) + loc->get(Y));
					cVert = chr->getCharModel()->getModelWrapper(TORSO)->getModel()->getCenter();
					vec = new Vector(cVert->get(X) + cCoord->get(X) - origin->get(X),
							cVert->get(Y) - origin->get(Y),
							cVert->get(Z) + cCoord->get(Y) - origin->get(Z));	
					ray = new Ray(origin, vec);
					hit = HitDetection::hitDetect(ray, 0, false);			
					if(hit->getType() < HIT_OBJECT && hit->getCoord() == cCoord){
						seen.insert(chr);
						chr->setVisible(VISIBLE);
					}
					delete ray;
					delete hit;
				}
			}
		}
	}
}

bool Character::isSeen(Character* c){
	if(seen.find(c) != seen.end())
		return true;		
	return false;
}

void Character::checkView(){
	seen.clear();
	map->clearVision(KNOWN, false);
	findVisible();
}
