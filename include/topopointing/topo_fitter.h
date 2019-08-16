#ifndef TOPOFITTER_H
#define TOPOFITTER_H

#include "TVector3.h"
#include "Minuit2/Minuit2Minimizer.h"

#include "topopointing/objects.h"

class TopoFitter {

  public : 

    TopoFitter();

    vertex_location getBestFitVertex(std::vector<Topocluster> clusters);

  private :

    float logLikelihood(const float *params);


    ROOT::Minuit2::Minuit2Minimizer * m_MinuitMinimizer;

    std::vector<Topocluster> m_topoclusters;
    TVector3 m_decayLocation;

};

#endif
