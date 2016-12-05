# RootMacros
tools for data analysis with Root


+++++++++ MakeTree ++++++++++

The file ./MakeTree/MakeTree.C provides an example of a root macro to store data (read from a text file) in a TTree object ("data"), which is saved to a Root TFile.
 

In an interactive Root session, load the macro and execute it with:
 
root [0] .L MakeTree.C+
root [1] MakeTree("test_input.txt","out.root", 16, 2)

This saves the TTree in the "out.root" file. Then you can use the Draw() function of TTrees to plot the data (among other options). In a new interactive Root session (the second line displays information about 'data' TTree, the third draws an histogram):

> root  out.root
root [0]
Attaching file out.root as _file0...
root [1] _file0->ls()
TFile**                out.root             
TFile*                 out.root             
  KEY: TTree        data;1   data
root [2] data->Print()
******************************************************************************
*Tree    :data      : data                                                   *
*Entries :       16 : Total =            2525 bytes  File  Size =       1035 *
*        :          : Tree compression factor =   1.46                       *
******************************************************************************
*Br    0 :x         : x[2]/D                                                 *
*Entries :       16 : Total  Size=        796 bytes  File Size  =        212 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.53     *
*............................................................................*
*Br    1 :y         : y[2]/D                                                 *
*Entries :       16 : Total  Size=        796 bytes  File Size  =        204 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.59     *
*............................................................................*
*Br    2 :n         : n/I                                                    *
*Entries :       16 : Total  Size=        590 bytes  File Size  =        118 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.12     *
*............................................................................*
root [3] data->Draw("x[0]:y[0]>>(20,-5,5,20,-5,5)","","colz")
Info in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1
(Long64_t)16



+++++++++ LoopTree ++++++++++

The file ./LoopTree/LoopTree.C provide an example on how to load a TTree saved in a Root file, and loop through each entry of the tree to make any new calculation with the data

The following is an example of its use, with the sample Root file generated in the MakeTree.C macro as an input:

root [0] .L LoopTree.C+
Info in <TUnixSystem::ACLiC>: creating shared library /home/popokelvis/macros/RootMacros/LoopTree/./LoopTree_C.so
root [1] LoopTree("../MakeTree/out.root")
Opened file ../MakeTree/out.root

Number of entries in input tree= 16

Looping over 16 entries.
Info in <TCanvas::Print>: file test.png has been created
