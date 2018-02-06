# RootCanvasCreator
A advanced plotting macro, that creates beautiful canvases

# Usage
The macro is used by calling the **newCanvas()** function.
The first arguments are *TObjArray*s, that are filled with the Objects to be drawn. 
The first object has to be a TH1, the following can be choosen freely. 


Short_t colors[]={kBlue-7,kGreen-2,kBlue-7,kGreen-2};
Short_t marker[]={21,33,7,7,1,3};

TCanvas *c1 = makeCanvas(array_one,array_two,"ControlString",colors,marker);

The control string includes all possible adjustments to the result:

Square

FullPage
BinLabels
Horizontal
SplitHalf
CenterTitle
LogX
LogY
RatioGridY
ThisWork
CMYK
Thick
Thin
Fill