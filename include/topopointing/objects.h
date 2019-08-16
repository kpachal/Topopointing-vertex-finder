#ifndef TOPOOBJECTS_H
#define TOPOOBJECTS_H

#include "TVector3.h"

class Topocluster {

  // Want a dual use class: 
  // can run on an AOD object or be given
  // relevant moments directly.

  public :

    // Default constructor
    Topocluster();

    // Constructor from AOD object
    // Topocluster();

    // Constructor from moments.
    // Delta alpha isn't necessary but can be used as a cross check to ensure 
    // calculations match.
    Topocluster(float x, float y, float z, float delta_phi, float delta_theta, float delta_alpha = -1);

  private :

    // Locations of cluster center
    float m_x;
    float m_y;
    float m_z;
    // Alternate representation (test)
    TVector3 m_clusterlocation;

    // Directions of cluster axis
    // with respect to global coordiante system
    // No third coordinate needed since there is
    // no equivalent of a radius parameter.
    float m_theta;
    float m_phi;
    // Alternate representation (test)
    TVector3 m_clusteraxis;

};


struct vertex_location {

  float x;
  float dx;
  float y;
  float dy;
  float z;
  float dz;

};

#endif
