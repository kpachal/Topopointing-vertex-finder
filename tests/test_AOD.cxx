#include <iostream>
#include <string>
#include <list>

#include <TH1I.h>
#include <TROOT.h>
#include <TTree.h>
#include <TStopwatch.h>
#include <TLorentzVector.h>
#include <ROOT/RDataFrame.hxx>

#include "topopointing/topo_fitter.h"
#include "topopointing/objects.h"

using namespace ROOT; // RDataFrame's namespace

std::vector<Topocluster> build_clusters(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& z, const std::vector<float>& dphi, const std::vector<float>& dtheta, const std::vector<float>& dalpha) {

  std::vector<Topocluster> clusters;
  for (unsigned int i=0; i<x.size(); i++) {
    Topocluster cluster(x.at(i),y.at(i),z.at(i),dphi.at(i),dtheta.at(i),dalpha.at(i));
    clusters.push_back(cluster);
  }
  return clusters;

}

// Do analysis
int main(int argc, char* argv[]) {

    std::string input_filename = "/eos/user/k/kpachal/TopoTesting/mc16_13TeV.361026.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ6W.deriv.DAOD_JETM13.e3569_e5984_s3126_r10201_r10210_p3947/DAOD_JETM13.18838480._000083.pool.root.1";

    std::string tree_name = "CollectionTree";
    std::string output_filename = "output.root";
    int ip=1;
    while (ip<argc) {

      if (std::string(argv[ip]).substr(0,2)=="--") {

          // Input file
          if (std::string(argv[ip])=="--input") {
            if (ip+1<argc && std::string(argv[ip+1]).substr(0,2)!="--") {
              input_filename = argv[ip+1];
              ip+=2;
            } else {std::cout<<"\nno input file name inserted"<<std::endl; break;}
          }

          // Tree name
          else if (std::string(argv[ip])=="--tree") {
            if (ip+1<argc && std::string(argv[ip+1]).substr(0,2)!="--") {
              tree_name = argv[ip+1];
              ip+=2;
            } else {std::cout<<"\nno tree name inserted"<<std::endl; break;}
          }
      }
    }

    std::cout << "Running over file: " << input_filename << std::endl;
    std::vector<std::string> files_to_use = {input_filename};

    // Make the fitter.
    TopoFitter fitter;

    // Make the RDataFrame!
    RDataFrame frame(tree_name, files_to_use);

    // Assemble cluster objects using the AOD information. 
    // Not trying to use xAOD objects right now - too complicated.
    auto has_clusters = frame.Define("clusters", build_clusters, 
                                     {"CaloCalTopoClustersAuxDyn.CENTER_X", "CaloCalTopoClustersAuxDyn.CENTER_Y", "CaloCalTopoClustersAuxDyn.CENTER_Z", "CaloCalTopoClustersAuxDyn.DELTA_PHI","CaloCalTopoClustersAuxDyn.DELTA_THETA", "CaloCalTopoClustersAuxDyn.DELTA_ALPHA"});

    auto has_fits = has_clusters.Define("vertex_candidate",
                                [&fitter](std::vector<Topocluster> clusters) 
                                { vertex_location candidate = fitter.getBestFitVertex(clusters);
                                  std::cout << "Candidate x, y, z: " << candidate.x << ", " << candidate.y << ", " << candidate.z << std::endl;
                                  return candidate;
                                }, 
                                {"clusters"} );

    // Store plots
    std::vector<ROOT::RDF::RResultPtr<TH1D> > outputs;    

    // First set of plots: results and AOD inputs alone.

    // Estimated vertex location
    auto vertex_x = has_fits.Define("vtx_x",[](vertex_location vertex){return vertex.x;}, {"vertex_candidate"}).Histo1D({"estimated_vertex_x","estimated_vertex_x",501,-10,5000},"vtx_x");
    outputs.push_back(vertex_x);

    // Error size as a function of estimated vertex location

    // Now do some things to compare estimated vertex to the analysis ntuples:
    // should this be in separate stopped particle code?


    // Make output file to save the histograms
    std::cout << "Making output file " << output_filename << std::endl;
    TFile * output_file = new TFile(output_filename.c_str(),"RECREATE");
    output_file->cd();
    for (auto hist: outputs) hist.GetValue().Write();
    output_file->Close();

    std::cout << "End." << std::endl;

}
