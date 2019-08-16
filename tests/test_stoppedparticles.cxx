#include <iostream>
#include <string>
#include <list>

#include <TH1I.h>
#include <TROOT.h>
#include <TTree.h>
#include <TStopwatch.h>
#include <TLorentzVector.h>
#include <ROOT/RDataFrame.hxx>

using namespace ROOT; // RDataFrame's namespace


// Do analysis
int main(int argc, char* argv[]) {

    std::string input_filename = "/eos/atlas/atlascerngroupdisk/phys-susy/Stopped_ANA-SUSY-2018-15/ntuple/testFiles/signal/v3/output_g1400_n1200_mass5_cosmicsReco_20190813_15-36-32_v3/hist-g1400_n1200_mass5_cosmicsReco.root";

    std::string tree_name = "Nominal/BaseSelection_tree_finalSelection";

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

    // Make the RDataFrame!
    RDataFrame frame(tree_name, files_to_use);

    std::cout << "End." << std::endl;

}
