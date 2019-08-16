#include <cmath>

#include "topopointing/topo_fitter.h"

TopoFitter::TopoFitter() :
  m_decayLocation() {

  return;

}

float TopoFitter::logLikelihood(const float *params) {

  // Set up vector to our hypothesised vertex.
  m_decayLocation.SetXYZ(params[0], params[1], params[2]);

  // Log likelihood form: 
  // If alpha is the angle between vector from vertex to cluster center
  // and cluster shower axis, then cos(alpha) gives degree of agreement:
  // 1 if they are aligned, -1 if anti-aligned, 0 if perpendicular.
  // Product of cos(alpha_i) for all i clusters is a likelihood with maximum 1.

  // To get a log likelihood:
  // sum of log(cos(alpha_i)).

  float log_l = 0;
  for (auto topo : m_topoclusters) {
    TVector3 vertexToTopo = topo.location() - m_decayLocation;
    float alpha = vertexToTopo.Angle(topo.axis());
    log_l += log(cos(alpha));
  }

  return log_l;

}

vertex_location TopoFitter::getBestFitVertex(std::vector<Topocluster> clusters) {

  // Object will hold output of fit
  vertex_location vertex;

  // Need to set topoclusters as dataset somehow...

  return vertex;
}
