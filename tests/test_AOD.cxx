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

    // Pure tests, nothing else
    float z = 0;
    Topocluster cluster1(100,0,z,0,0);
    Topocluster cluster2(0,100,z,0,0);
    Topocluster cluster3(-100,0,z,0,0);
    Topocluster cluster4(0,-100,z,0,0);
    std::vector<Topocluster> toy_clusters = {cluster1, cluster2, cluster3, cluster4};

    vertex_location candidate = fitter.getBestFitVertex(toy_clusters);

    std::cout << "Candidate x, y, z: " << candidate.x << ", " << candidate.y << ", " << candidate.z << std::endl;

/*
    // Make the RDataFrame!
    RDataFrame frame(tree_name, files_to_use);

    // For each event, want to see if I can access aux data.
    auto hist_e = frame.Histo1D({"calE","calE",50,0,500.0}, "CaloCalTopoClustersAuxDyn.calE");
    auto hist_eta = frame.Histo1D({"calEta","calEta",50,-3.0,3.0}, "CaloCalTopoClustersAuxDyn.calEta");
    auto hist_avg_lar_q = frame.Histo1D({"AVG_LAR_Q","AVG_LAR_Q",50,0,5.0}, "CaloCalTopoClustersAuxDyn.AVG_LAR_Q");
    std::vector<ROOT::RDF::RResultPtr<TH1D> > hists_to_write = {hist_e,hist_eta,hist_avg_lar_q};

    // Make output file to save the histograms
    std::cout << "Making output file " << output_filename << std::endl;
    TFile * output_file = new TFile(output_filename.c_str(),"RECREATE");
    output_file->cd();
    for (auto hist: hists_to_write) hist.GetValue().Write();
    output_file->Close();
*/
    std::cout << "End." << std::endl;

}
