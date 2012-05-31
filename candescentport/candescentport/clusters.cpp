#include "clusters.h"	

	void clusterfnc::clearall(clusterdat* c1) {
		c1->center.angle = 0.0f;
		c1->center.x = 0;
		c1->center.y = 0;
		c1->center.z = 0;
		c1->vol.depth = 0;
		c1->vol.height = 0;
		c1->vol.location.x = 0;
		c1->vol.location.y = 0;
		c1->vol.location.z = 0;
		c1->vol.location.angle = 0.0f;
		memset(c1->points,0,sizeof(c1->points));
		memset(c1->Allpoints,0,sizeof(c1->Allpoints));
		c1->allpointscnt =0;
		c1->pointscnt =0;
		
	}


	void clusterfnc::set(clusterdat* dest, point* pnt){
		dest->center = *pnt;
	}
	void clusterfnc::set(clusterdat* dest, clusterdat* src){
		dest->center = src->center;
		dest->vol = src->vol;
		memcpy(dest->points,src->points, sizeof(dest->points));
		dest->pointspnt = src->pointspnt;
		dest->pointscnt = src->pointscnt;
		memcpy(dest->Allpoints,src->Allpoints, sizeof(dest->Allpoints));
		dest->allpointpnt = src->allpointpnt;
		dest->allpointscnt = src->allpointscnt;
	}
	void clusterfnc::set(clusterdat* dest, unsigned short x, unsigned short y, unsigned short z){
		dest->center.x = x;
		dest->center.y = y;
		dest->center.z = z;
	}
	void clusterfnc::set(clusterdat* dest, point center, point** pnts){
		dest->center = center;
		memcpy(dest->points,*pnts,sizeof(dest->points));
	}

	double clusterfnc::Calc2DDistance(clusterdat* c1, point* pnt){
		return sqrt(pow((float)pnt->x - c1->center.x, 2) + pow((float)pnt->y - c1->center.y, 2) + pow((float)pnt->z - c1->center.z, 2));

	}
	point* clusterfnc::FindClosestpoint(clusterdat* c1, point** pnts,int count){
		double dist = 999999;
		double tempdist = 0;
		point* closest = 0;
		int index = 0;
		for (index=0; index<count; index++) {
			if (!(pnts[index]==0)) {
				tempdist = Calc2DDistance(c1,pnts[index]);
				if (tempdist<dist) {
					closest = pnts[index];
					dist = tempdist;
				}
			}
		}

		return closest;
	}
	void clusterfnc::Addpoint(clusterdat* c1, point* pnt){
		c1->points[c1->pointscnt] = pnt;
		c1->pointscnt++;
	}
	void clusterfnc::FindCenter(clusterdat* c1){
		if (c1->pointscnt == 0) {
			return;
		}
		int index = 0;
		int count = 0;

		unsigned __int64 x = 0;
		unsigned __int64 y = 0;
		unsigned __int64 z = 0;

		for (index=0;index<640*480;index++) {
			if (!(c1->points[index]==0)) {
				count++;
				x += c1->points[index]->x;
				y += c1->points[index]->y;
				z += c1->points[index]->z;	
			}
		}
		x /= count;
		y /= count;
		z /= count;
		c1->center.x = x;
		c1->center.y = y;
		c1->center.z = z;
	} 
	void clusterfnc::CalculateVolume(clusterdat* c1){
		if (c1->pointscnt == 0) {
			return;
		}
		unsigned short minx = 1000;
		unsigned short maxx = 0;
		unsigned short miny = 1000;
		unsigned short maxy = 0;
		unsigned short minz = 10000;
		unsigned short maxz = 0;

		int index = 0;
		for (index = 0;index<640*480;index++) {
			if (!(c1->points[index]==0)) {
				if (c1->points[index]->x<minx) {
					minx = c1->points[index]->x;
				}
				if (c1->points[index]->x>maxx) {
					maxx = c1->points[index]->x;
				}
				if (c1->points[index]->y<miny) {
					miny = c1->points[index]->y;
				}
				if (c1->points[index]->y>maxy) {
					maxy = c1->points[index]->y;
				}
				if (c1->points[index]->z<minz) {
					minz = c1->points[index]->z;
				}
				if (c1->points[index]->z>maxz) {
					maxz = c1->points[index]->z;
				}
			}
		}
		c1->vol.location.x = minx;
		c1->vol.location.y = miny;
		c1->vol.location.z = minz;
		c1->vol.width = maxx-minx;
		c1->vol.height = maxy-miny;
		c1->vol.depth = maxz-minz;

	}
	void clusterfnc::Clearpoints(clusterdat* c1){
		memset(c1->points,0,sizeof(c1->points)); 
		c1->pointscnt = 0;
	}
	void clusterfnc::Flatten(clusterdat* c1, int maxDepth){
		float maxZValue = c1->vol.location.z + maxDepth;
		if (c1->vol.depth > maxDepth) {
			int index = 0;
			for (index=0;index<640*480;index++) {
				if (!(c1->points[index]==0)) {
					if (c1->points[index]->z > maxDepth) {
						c1->points[index]->z = maxDepth; //ALTERED
					}
				}
			}
			FindCenter(c1);
			CalculateVolume(c1);
		}
	}
	int clusterfnc::Count(clusterdat* c1){
		return c1->pointscnt;
	}
	void clusterfnc::Area(rectdata* dest, clusterdat* src){ // RECTANGLEZ point change
		

		
		dest->location.x = src->vol.location.x;
		dest->location.y = src->vol.location.y;
		dest->size.Width = src->vol.width;
		dest->size.Height = src->vol.height;
	}
	double clusterfnc::DistanceMetric(clusterdat* c1, clusterdat* c2){ //c2 is the input, c1 is the self
		point* p1 = FindClosestpoint(c1, c2->points,c2->pointscnt);
		point* p2 = FindClosestpoint(c2, c1->points,c1->pointscnt);
		return c1->pntfnc.distance(p1,p2);
	}

	void clusterfnc::Merge(clusterdat* c1, clusterdat* c2){ //c2 and c1 are going to be in c3 from now on.
		int index = 0;
		for (index=0;index<640*480;index++) {
			if (!(c2->points[index]==0)) {
				c1->points[index] = c2->points[index];
			}
		}
		c1->pntfnc.Center(&c1->center,&c2->center,&c1->center);
		CalculateVolume(c1);
		FindCenter(c1);
	}



