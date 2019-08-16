#include "topopointing/objects.h"

#include <iostream>

Topocluster::Topocluster() :
  m_clusterlocation(),
  m_clusteraxis() {
  m_x = 0;
  m_y = 0;
  m_z = 0;
  m_theta = 0;
  m_phi = 0;
}

Topocluster::Topocluster(float x, float y, float z, float delta_phi, float delta_theta, float delta_alpha) :
  m_clusterlocation(),
  m_clusteraxis()
  {

  // Basic coordinates are easy.
  m_x = x;
  m_y = y;
  m_z = z;

  // Assume for now that location is still defined from (0,0,0):
  // this is the easier situation for us because we don't need to know about PV.
  m_clusterlocation.SetXYZ(m_x, m_y, m_z);

  // Now we have angles of cluster axis with respect to location vector.
  // Work backwards to get cluster axis.
  m_theta = delta_theta + m_clusterlocation.Theta();
  m_phi = delta_phi + m_clusterlocation.Phi();
  // This is just a unit vector giving us a direction.
  m_clusteraxis.SetMagThetaPhi(1.0,m_theta,m_phi);

  // Now we can do a cross check if we want!
  // Ensure that we get delta_alpha if we take the
  // angles between the cluster location and cluster axis.
  if (delta_alpha > 0) {
    float compare_angle = m_clusterlocation.Angle(m_clusteraxis);
    if ((compare_angle - delta_alpha)/delta_alpha > 0.01) {
      std::cout << "Angles not matching well! Delta alpha: " << delta_alpha << "; our angle " << compare_angle << std::endl;
    }

  } else {
    std::cout << "Delta alpha " << delta_alpha << "; not doing check" << std::endl;
  }


}
