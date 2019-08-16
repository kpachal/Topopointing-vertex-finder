#ifndef TOPOFITTER_H
#define TOPOFITTER_H

#include "topopointing/objects.h"
#include "Minuit2/Minuit2Minimizer.h"

class TopoFitter {

  public : 

    TopoFitter();

    vertex_location getBestFitVertex(std::vector<topocluster> clusters);

  private :


    ROOT::Minuit2::Minuit2Minimizer * m_MinuitMinimizer;


};

#endif
