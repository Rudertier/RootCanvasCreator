
TCanvas *makeCanvas(TObjArray *histArray, TObjArray *ratioArray = 0,const char *controlstring="", Short_t *colorArray = 0, Short_t *markerArray = 0){

/// This fuction draws a canvas, which contains two panels. The upper one takes up the
/// most space and is designed to show spectra.
/// The lower panel is designed to show the ratio of the histograms shown in the upper
/// panel.The histograms and the ratios as well as the ledgend are created befor and
/// are part of the parameters.
///
/// The function expects a <b>TObjArray</b> for the Historgrams and a <b>Short_t</b> Array for the
/// colors
///
/// \param TObjArray Array of histograms
/// \param TObjArray Array of Ratios
/// \param Char String ("LogY"&"LogX" to set Axis)
/// \param Short_t Array of color integers
/// \param Short_t Array of marker integers
///
/// \return TCanvas with the drawn histograms
///
/// <b>String posibilities:</b>
/// \arg LogX     Set X-axis logarythmic
/// \arg LogY     Set Y-axis logarythmic
/// \arg Square   Produce a squared canvas
///
///
///
  cout<<" ____________________________________________________________________________"<<endl;
  cout<<"|"<<endl;
  cout<<"| Plots generated via makeCanvas"<<endl;

  gStyle->SetTextFont(43);
  TString control(controlstring);

//   Short_t colorArray[]={kRed,kOrange-3,kGreen-3,kGreen+3,kCyan+3,kBlue};
  if(!colorArray) {Short_t defaultColorArray[14]={kBlue-7,kRed+1,kGreen-3,6,8,9,11,12,13,14,15,16,17,18};} /// \remark If no colors are specified, use default: blue, red, green, magenta, wierd green, wierd blue and various grey
  if(!markerArray) {Short_t defaultMarkerArray[14]={20,21,22,23,24,25,26,27,28,29,30,20,20,20};} /// \remark If no markers are specified, use default.
  if(control.Contains("OwnColors")){DefineOwnColors(); Short_t defaultColorArray[14]={4001,4002,4003,4004,4005,4006,4007,4008,4009,4010,4011,4012,17,18};}

  Int_t nHist = histArray->GetEntries();
  if(nHist == 0){cout<<"| ERROR: Arrays empty"<<endl; return;}

  Float_t lableSize = 1.00; // Factor the label will be larger than the relative textsize
  Float_t titleSize = 1.20; // Factor the title will be larger than the relative textsize
  Float_t textSizeFactor = 14300;
  Int_t lableFont= 43;
  Int_t titleFont= 43;

  Float_t canvasWidth;
  Float_t canvasHeight;
  Float_t padFraction;
  Float_t titleOffsetY;
  Float_t titleOffsetX;
  Float_t sideMargin;
  Float_t topMargin;
  Float_t lowMargin;

  Float_t yshift=0;
  
  if(control.Contains("square")||control.Contains("Square")||control.Contains("SQUARE")){
    cout<<"| - Square Canvas"<<endl;
    cout<<"|   Optimized for 0.49 * textwidth"<<endl;
    canvasWidth=700;
    canvasHeight=canvasWidth;
    titleOffsetY=1.6;
    titleOffsetX=1.5;
    sideMargin=0.12;
    yshift = 0.08;
    topMargin=sideMargin-yshift;
    lowMargin=sideMargin+yshift;
    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.99 * textwidth"<<endl;
      canvasWidth=2*700;
      textSizeFactor = 2 * textSizeFactor;
      canvasHeight=canvasWidth;
    }
    if (control.Contains("BinLabels")){
      titleOffsetY=1.05;
      titleOffsetX=2.1;
//       lowMargin=0.19;
    }
    if(ratioArray){
      padFraction = 0.5+yshift;
      textSizeFactor = (padFraction-yshift) * textSizeFactor * (1-2*yshift);
      topMargin= topMargin / (1-padFraction);
      lowMargin= lowMargin / (padFraction);
      titleOffsetY=1.4;
      titleOffsetX=2.8;
    }
  }else if (control.Contains("horizontal")||control.Contains("Horizontal")||control.Contains("HORIZONTAL")){
    cout<<"| - Horizontal Canvas"<<endl;
    cout<<"|   Optimized for 0.69 * textwidth"<<endl;
    canvasHeight=700;
    canvasWidth=canvasHeight*1.414213562;
//     textSizeFactor = textSizeFactor/1.414213562;
    titleOffsetY=1.05;
    titleOffsetX=1.5;
//     sideMargin = 0.09*1.414213562;
//     topMargin=0.06;
//     lowMargin=0.12;
    sideMargin = 0.12/1.414213562;
    topMargin=0.12-0.05;
    lowMargin=0.12+0.05;
    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.99 * textwidth"<<endl;
      canvasHeight=1.43*700;
      textSizeFactor = 1.43 * textSizeFactor;
      canvasWidth=canvasHeight*1.414213562;
    }
    if (control.Contains("BinLabels")){
      titleOffsetY=1.05;
      titleOffsetX=2.1;
      lowMargin=0.19;
    }
    if(ratioArray){
      padFraction = 0.5;
      textSizeFactor = padFraction * textSizeFactor;
    }
 }else if (control.Contains("OldAspect")||control.Contains("oldaspect")){
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    canvasWidth=700;
    canvasHeight=800;
    titleOffsetY=1.7;
    titleOffsetX=3.5;
    sideMargin=0.12;
    topMargin=0.11;
    lowMargin=0.13;
    if(ratioArray){
      padFraction = 0.28;
      textSizeFactor = padFraction * textSizeFactor;
      titleOffsetY=1.7;
      titleOffsetX=4.1;
      topMargin=0.08;
      lowMargin=0.30;
    }
  }else if (control.Contains("SplitHalf")||control.Contains("splithalf")){
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    textSizeFactor = textSizeFactor;
    canvasWidth=700;
    canvasHeight=700*1.41421356;
    titleOffsetY=2;
    titleOffsetX=4.5;
    sideMargin = 0.14;
    topMargin = sideMargin * 1.414213562/2;
    lowMargin = sideMargin * 1.414213562/2;
    if(ratioArray){
      padFraction = 0.5;
      textSizeFactor = padFraction * textSizeFactor;
      titleOffsetY=2;
      titleOffsetX=4.5;
      topMargin = (sideMargin * 1.414213562/2)/(1-padFraction);
      lowMargin = (sideMargin * 1.414213562/2)/(padFraction);
    }
  }else{
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    canvasWidth=700;
    canvasHeight=700*1.41421356;
    titleOffsetY=2;
    titleOffsetX=4.5;
    sideMargin = 0.12;
    topMargin = 0.12 * 1.414213562/2;
    lowMargin = 0.12 * 1.414213562/2;
    if(ratioArray){
      padFraction = 0.25;
      titleOffsetY=2;
      titleOffsetX=4.5;
      topMargin = (0.12 * 1.414213562/2)/(1-padFraction);
      lowMargin = (0.12 * 1.414213562/2)/(padFraction);
    }
  }


  TRandom *random = new TRandom(histArray->Hash());
  Double_t xMin;
  Double_t xMax;

  /// Check if first element of th histogram array is indeed an Histogram.
  if(histArray->At(0)){
    if (!histArray->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist0 = (TH1D*) histArray->At(0);
    if(!hist0){cout<<"| ERROR: Histogram empty"<<endl;}
    TString title("default");
    title += Form("%f",random->Rndm());
    xMin = hist0->GetXaxis()->GetBinLowEdge(hist0->GetXaxis()->GetFirst())+0.0000001;
    xMax = hist0->GetXaxis()->GetBinUpEdge(hist0->GetXaxis()->GetLast())-0.0000001;
    cout<<"| - Axis range: "<<xMin<<"-"<<xMax<<endl;
    hist0->GetYaxis()->CenterTitle(0);
    if(control.Contains("CenterTitle")||control.Contains("centertitle")) hist0->GetYaxis()->CenterTitle(1);
  }
  /// Check if the first Element of the ratio array is an histogram.
  if(ratioArray){
    if(ratioArray->At(0)){
      if (!ratioArray->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
      TH1D *ratio0 = (TH1D*) ratioArray->At(0);
      if(!ratio0){cout<<"| ERROR: Histogram empty"<<endl;}
      ratio0->GetXaxis()->SetTickLength(0.06);
      ratio0->GetYaxis()->SetNdivisions(506);
      ratio0->SetLineWidth(2);
      ratio0->GetYaxis()->CenterTitle(1);

      /// Automatic range + zoom
      if(control.Contains("Zoom")){
	Double_t ratio0Maximum = ratio0->GetBinContent(ratio0->GetMaximumBin());
	Double_t ratio0Minimum = 1;
	for(Int_t ii = 0; ii < ratio0->GetNbinsX(); ii++){
          Double_t val = ratio0->GetBinContent(ii);
          if (val > 0){if (val < ratio0Minimum){ratio0Minimum = val;}}
        }
	Double_t zoom = 0.05;
	if(control.Contains("Zoom"))     zoom = 0.15;
	if(control.Contains("Zoom+"))    zoom = 0.30;
	if(control.Contains("Zoom++"))   zoom = 0.45;
	if(control.Contains("Zoom+++"))  zoom = 0.60;
	if(control.Contains("Zoom++++")) zoom = 0.75;
	if(control.Contains("Zoom+++++"))zoom = 0.90;
	if ( ( 1 - ratio0Minimum) > ( ratio0Maximum - 1) ){zoom = zoom*(1- ratio0Minimum); ratio0->SetAxisRange(ratio0Minimum+zoom,2-ratio0Minimum-zoom,"Y");}
	else{zoom = zoom*(ratio0Maximum -1); if ( ratio0Maximum > 2){ratio0->SetAxisRange(zoom,ratio0Maximum - zoom,"Y");}else{ ratio0->SetAxisRange(1-(ratio0Maximum-1)+zoom,ratio0Maximum - zoom,"Y");}}
      }
    }
  }



  /// Create Canvas in a given size
  TCanvas *newCanvas = new TCanvas(title,title,10,10,canvasWidth+10,canvasHeight+10);
  newCanvas->SetFillStyle(4000);
  newCanvas->cd();


 /// If ratioArray exist, split the Canvas in two and create a ratio panel
  if(ratioArray){

    TPad *upperPad = new TPad("upperPad","Distribution" ,0 ,padFraction ,1 ,1);
    TPad *lowerPad = new TPad("lowerPad","Ratio"        ,0 ,0           ,1 ,padFraction);

    upperPad->SetFillStyle(4000);
    upperPad->SetTopMargin(topMargin);
    upperPad->SetLeftMargin(sideMargin);
    upperPad->SetRightMargin(sideMargin);
    upperPad->SetBottomMargin(0.0);
    upperPad->SetTickx(1);
    upperPad->SetTicky(1);
    upperPad->Draw();

    lowerPad->SetFillStyle(4000);
    lowerPad->SetTopMargin(0.0);
    lowerPad->SetLeftMargin(sideMargin);
    lowerPad->SetRightMargin(sideMargin);
    lowerPad->SetBottomMargin(lowMargin);
    lowerPad->SetTickx(1);
    lowerPad->SetTicky(1);
    lowerPad->Draw();

    if(control.Contains("logX")||control.Contains("logx")||control.Contains("LogX")||control.Contains("LOGX")){
      upperPad->SetLogx(1); lowerPad->SetLogx(1); cout<<"| - LogX"<<endl;
    }
    if(control.Contains("logY")||control.Contains("logy")||control.Contains("LogY")||control.Contains("LOGY")){
      upperPad->SetLogy(1);  cout<<"| - LogY"<<endl;
    }
    if(control.Contains("RatioGridY")){lowerPad->SetGridy(1); cout<<"| - Ratio: GridY"<<endl;}

    newCanvas->cd();
    upperPad->cd();

    Double_t relativeTextSize;
    Double_t pad_width;
    Double_t pad_height;

    /// Calculate the relative text size, independent of the size of the pad
    pad_width  = gPad->XtoPixel(gPad->GetX2());
    pad_height = gPad->YtoPixel(gPad->GetY1());
    if (pad_width < pad_height){relativeTextSize = 1/pad_width;}
    else{relativeTextSize = 1/pad_height;}
    relativeTextSize = textSizeFactor * relativeTextSize;

    /// Use the standardtised PlotArray function to loop over the histogram an to draw the elements.
    if(!markerArray && !colorArray){PlotArray(histArray,controlstring,defaultColorArray,defaultMarkerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else if(!markerArray){PlotArray(histArray,controlstring,colorArray,defaultMarkerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else if(!colorArray){ PlotArray(histArray,controlstring,defaultColorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else{PlotArray(histArray,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}

    /// Go to the ratio pad and repeat the procedure
    lowerPad->cd();
    if(!markerArray && !colorArray){PlotArray(ratioArray,controlstring,defaultColorArray,defaultMarkerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else if(!markerArray){PlotArray(ratioArray,controlstring,colorArray,defaultMarkerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else if(!colorArray){PlotArray(ratioArray,controlstring,defaultColorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else{PlotArray(ratioArray,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    upperPad->cd();

  }else{// If no ratios are given:

    newCanvas->SetLeftMargin(sideMargin);
    newCanvas->SetRightMargin(sideMargin);
    newCanvas->SetTopMargin(topMargin);
    newCanvas->SetBottomMargin(lowMargin);


    newCanvas->SetTickx(1);
    newCanvas->SetTicky(1);


    if(control.Contains("logX")||control.Contains("logx")||control.Contains("LogX")||control.Contains("LOGX")){
      newCanvas->SetLogx(1); cout<<"| - LogX"<<endl;}
    if(control.Contains("logY")||control.Contains("logy")||control.Contains("LogY")||control.Contains("LOGY")){
      newCanvas->SetLogy(1); cout<<"| - LogY"<<endl;}
    if(control.Contains("gridY")||control.Contains("gridy")||control.Contains("GridY")||control.Contains("GRIDY")){
      if(!control.Contains("atio") ) newCanvas->SetGridy(1);cout<<"| - Grid Y"<<endl;
    }

    Double_t relativeTextSize;
    Double_t pad_width  = gPad->XtoPixel(gPad->GetX2());
    Double_t pad_height = gPad->YtoPixel(gPad->GetY1());
    if (pad_width < pad_height){relativeTextSize = 1/pad_width;}
    else{relativeTextSize = 1/pad_height;}
    relativeTextSize = textSizeFactor * relativeTextSize;

    if(!markerArray && !colorArray){PlotArray(histArray,controlstring,defaultColorArray,defaultMarkerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else if(!markerArray){PlotArray(histArray,controlstring,colorArray,defaultMarkerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else if(!colorArray){PlotArray(histArray,controlstring,defaultColorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
    else{PlotArray(histArray,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);}
  }

  /// Draw extras
  /// Timestamp
  if(!control.Contains("Notime")&&!control.Contains("NoTime")&&!control.Contains("notime")&&!control.Contains("NOTIME")){
    TTimeStamp time;
    TString stTime;
    stTime=Form("#color[16]{%i}",time.GetDate());
    TLatex *timeStamp = new TLatex();
    timeStamp->SetNDC();
    timeStamp->SetTextAlign(22);
    timeStamp->SetTextFont(63);
    timeStamp->SetTextSizePixels(10);
    timeStamp->DrawLatex(0.96,0.98,stTime);
    }else{
      cout<<"|         - No Timestamp"<<endl;
    }
  /// Text "This work"
  if(control.Contains("ThisWork")||control.Contains("Thiswork")||control.Contains("thiswork")||control.Contains("THISWORK")){
    TLatex *thsWrk = new TLatex();
    thsWrk->SetNDC();
    thsWrk->SetTextAlign(22);
    thsWrk->SetTextFont(43);
    thsWrk->SetTextSizePixels(20);
    if(control.Contains("square")||control.Contains("Square")||control.Contains("SQUARE")){
      if(ratioArray){thsWrk->DrawLatex(0.82,0.94,"#color[16]{this thesis}");}
      else{thsWrk->DrawLatex(0.82,0.98,"#color[16]{this thesis}");}
    }else if(control.Contains("horizontal")||control.Contains("Horizontal")||control.Contains("HORIZONTAL")){
      thsWrk->DrawLatex(0.87,0.95,"#color[16]{this thesis}");
    }else{
      thsWrk->DrawLatex(0.82,0.92,"#color[16]{this thesis}");
      
    }
  }

  if(ratioArray){upperPad->cd();}
  cout<<"|_____________________________________________________________________________"<<endl;
  cout<<" "<<endl;
  return newCanvas;
}

void PlotArray(TObjArray *arraytoplot, const char *controlstring ,Short_t *colorArray, Short_t *markerArray, Double_t relativeTextSize,Float_t lableSize,Float_t titleSize,  Int_t lableFont,Int_t titleFont,Float_t titleOffsetY,Float_t titleOffsetX,Float_t margin,Double_t xMin,Double_t xMax,Double_t yMin = 0,Double_t yMax = 0){
  TString control(controlstring);
  if (control.Contains("CMYK")||control.Contains("cmyk")){gStyle->SetColorModelPS(1);}
  Int_t nbrEntries = arraytoplot->GetEntries();
  for(Int_t hh=0;hh<=nbrEntries;hh++){
    if(!arraytoplot->At(hh)){break;}

    if (arraytoplot->At(hh)->InheritsFrom("TH1") && !arraytoplot->At(hh)->InheritsFrom("TH2")){
      cout<<"| Drawing a TH1 "<<hh<<endl;
      TH1D *hist = (TH1D*) arraytoplot->At(hh);
      hist->SetStats(0);
      hist->GetXaxis()->SetLabelSize(lableSize*relativeTextSize);
      hist->GetXaxis()->SetTitleSize(titleSize*relativeTextSize);
      hist->GetXaxis()->SetLabelFont(lableFont);
      hist->GetXaxis()->SetTitleFont(titleFont);
      hist->GetXaxis()->SetTitleOffset(titleOffsetX);

      hist->GetYaxis()->SetLabelSize(lableSize*relativeTextSize);
      hist->GetYaxis()->SetTitleSize(titleSize*relativeTextSize);
      hist->GetYaxis()->SetLabelFont(lableFont);
      hist->GetYaxis()->SetTitleFont(titleFont);
      hist->GetYaxis()->SetTitleOffset(titleOffsetY);
      hist->SetTitle("");

      hist->SetAxisRange(xMin,xMax,"X");



      TString xTitle(hist->GetXaxis()->GetTitle());
      if (xTitle.Contains("pt")  || xTitle.Contains("p_{T} (GeV/c)")){
	hist->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
      }else if(xTitle.Contains("mcPt")){
	hist->GetXaxis()->SetTitle("#it{p}_{T}^{MC} (GeV/#it{c})");
      }



      hist->SetMarkerStyle(markerArray[hh]);
      hist->SetMarkerColor(colorArray[hh]);
      hist->SetLineColor(colorArray[hh]);


      Double_t mrkSize = hist->GetMarkerSize();
      if(hist->GetMarkerStyle()== 33 || hist->GetMarkerStyle()== 27) hist->SetMarkerSize(1.4*mrkSize);
      if(hist->GetMarkerStyle()== 29 || hist->GetMarkerStyle()== 30) hist->SetMarkerSize(1.4*mrkSize);
      if(hist->GetMarkerStyle()== 5  || hist->GetMarkerStyle()== 5 ) hist->SetMarkerSize(1.4*mrkSize);
      if(hist->GetMarkerStyle()== 34 || hist->GetMarkerStyle()== 28) hist->SetMarkerSize(1.2*mrkSize);


      /// Set tick length independent of pad size
      Double_t pad_width  = gPad->XtoPixel(gPad->GetX2());
      Double_t pad_height = gPad->YtoPixel(gPad->GetY1());
      hist->SetTickLength(13/pad_height,"X");
      hist->SetTickLength(13/pad_width,"Y");

      if(control.Contains("Thick")||control.Contains("thick")){
	hist->SetLineWidth(4);
      }else if(control.Contains("Thin")||control.Contains("thin")){
	hist->SetLineWidth(1);
      }else{
	hist->SetLineWidth(2);
      }

      TString histName(hist->GetName());
      if(markerArray[hh]==0 || histName.Contains("dummy")){
	cout<<"|         - Don't draw dummy"<<endl;
        hist->SetLineWidth(0);
	hist->SetMarkerSize(0);
      }
      if(hist->GetMarkerStyle() <= 4 || control.Contains("Lines")||control.Contains("lines")){
	cout<<"|         - Lines No errors"<<endl;
	if(markerArray){ hist->SetLineStyle(markerArray[hh]);}
	if(control.Contains("Fill")){
          cout<<"|         - DrawFilled"<<endl;
          hist->SetLineColor(kBlack);
          hist->SetFillColor(colorArray[hh]);
          hist->SetFillStyle(1001);
        }
	if(hh==0) {hist->Draw("hist][");}
        else{hist->Draw("Same hist ][ ");}
      }else if(markerArray[hh]==999){
	hist->SetFillColor(kGray);
        hist->SetFillStyle(1001);
	hist->SetMarkerSize(0);
	if(hh==0) {hist->Draw("E2");}
	else{hist->Draw("Same E2");}
      }else if(histName.Contains("error")){
        if(hh==0) {hist->Draw("E3");}
	else{hist->Draw("Same E3");}
      }else{
	if(hh==0) {hist->Draw("");}
	else{hist->Draw("Same");}
      }
    }else if (arraytoplot->At(hh)->InheritsFrom("TH2")){
      cout<<"| Drawing a TH2 "<<hh<<endl;
      TH2D *hist2 = (TH2D*) arraytoplot->At(hh);
      hist2->SetStats(0);
      hist2->GetXaxis()->SetLabelSize(lableSize*relativeTextSize);
      hist2->GetXaxis()->SetTitleSize(titleSize*relativeTextSize);
      hist2->GetXaxis()->SetLabelFont(lableFont);
      hist2->GetXaxis()->SetTitleFont(titleFont);
      hist2->GetXaxis()->SetTitleOffset(titleOffsetX);

      hist2->GetYaxis()->SetLabelSize(lableSize*relativeTextSize);
      hist2->GetYaxis()->SetTitleSize(titleSize*relativeTextSize);
      hist2->GetYaxis()->SetLabelFont(lableFont);
      hist2->GetYaxis()->SetTitleFont(titleFont);
      hist2->GetYaxis()->SetTitleOffset(titleOffsetY);

      hist2->GetZaxis()->SetLabelSize(lableSize*relativeTextSize);
      hist2->GetZaxis()->SetTitleSize(titleSize*relativeTextSize);
      hist2->GetZaxis()->SetLabelFont(lableFont);
      hist2->GetZaxis()->SetTitleFont(titleFont);
      hist2->GetZaxis()->SetTitleOffset(titleOffsetY);
      hist2->SetTitle("");

      hist2->SetAxisRange(xMin,xMax,"X");
      hist2->SetAxisRange(yMin,yMax,"Y");


      TString xTitle(hist2->GetXaxis()->GetTitle());
      if (xTitle.Contains("pt")  || xTitle.Contains("p_{T} (GeV/c)")){
	hist2->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
      }else if(xTitle.Contains("mcPt")){
	hist2->GetXaxis()->SetTitle("#it{p}_{T}^{MC} (GeV/#it{c})");
      }


      /// Set tick length independent of pad size
      Double_t pad_width  = gPad->XtoPixel(gPad->GetX2());
      Double_t pad_height = gPad->YtoPixel(gPad->GetY1());
      hist2->SetTickLength(13/pad_height,"X");
      hist2->SetTickLength(13/pad_width,"Y");

      hist2->Draw("COLZ");

    }else if (arraytoplot->At(hh)->InheritsFrom("TLine")){
      cout<<"| Drawing line: "<<arraytoplot->At(hh)->GetName()<<endl;
      TLine *line = (TLine*) arraytoplot->At(hh);
      if (markerArray[hh]<11){line->SetLineStyle(markerArray[hh]);}
      line->Draw("Same");
    }else if (arraytoplot->At(hh)->InheritsFrom("TPaveText")){
      cout<<"| Drawing a TPaveText "<<hh<<endl;
      TPaveText *pt = (TPaveText*) arraytoplot->At(hh);
      if (! pt) cout<<"|Error with TPaveText"<<endl;
      cout<<"| Rel. text size: "<<relativeTextSize<<endl;
      pt->SetFillStyle(0);
      pt->SetFillColor(0);
      pt->SetBorderSize(0);
      pt->SetTextFont(titleFont);
      pt->SetTextSize(relativeTextSize);
      pt->Draw();
    }else if (arraytoplot->At(hh)->InheritsFrom("TLegend")){
      cout<<"| Drawing a Legend "<<hh<<endl;
      cout<<"| Rel. text size: "<<relativeTextSize<<endl;
      TLegend *leghh = (TLegend*) arraytoplot->At(hh);
      leghh->SetTextFont(titleFont);
      leghh->SetTextSize(relativeTextSize);
      leghh->SetFillColor(kWhite);
      leghh->SetFillStyle(0);
      leghh->SetBorderSize(0);
      leghh->Draw("same");
    }else if (arraytoplot->At(hh)->InheritsFrom("TBox")){
      cout<<"| Drawing a TBox"<<endl;
      TBox *box = (TBox*) arraytoplot->At(hh);
      box->Draw();
    }else if (arraytoplot->At(hh)->InheritsFrom("TGraphAsymmErrors")){
      cout<<"| Drawing a TGraphAsymmErrors "<<hh<<endl;
      TGraphAsymmErrors *asym = (TGraphAsymmErrors*) arraytoplot->At(hh);

      asym->SetLineColor(colorArray[hh]);
      asym->SetLineStyle(markerArray[hh]);
      asym->SetLineWidth(4);
      asym->Draw("SAME");
    }else if (arraytoplot->At(hh)->InheritsFrom("TGraph")){
      cout<<"| Drawing a TGraph "<<hh<<endl;
      TGraph *grph = (TGraphAsymmErrors*) arraytoplot->At(hh);

      if(markerArray[hh] == 999){
        cout<<"| - As sytematic error"<<endl;
        grph->SetFillColorAlpha(colorArray[hh],0.6);
//         grph->Draw("SAME a3");
        grph->Draw("SAME []");
//         grph->Draw("SAME 5");        
      }else if(markerArray[hh] == 998){      
        cout<<"| - Without markers"<<endl;
        grph->SetMarkerColor(colorArray[hh]);
        grph->SetMarkerSize(0);
        grph->Draw("SAME P");
      }else if (markerArray[hh] >= 3000 && markerArray[hh] <= 4000){
        cout<<"| - As band"<<endl;
        grph->SetFillColor(colorArray[hh]);
        grph->SetFillStyle(markerArray[hh]);
        grph->Draw("Same 3");
      }else{

        grph->SetMarkerColor(colorArray[hh]);
        grph->SetMarkerStyle(markerArray[hh]);
        Double_t mrkSize = grph->GetMarkerSize();
        if(grph->GetMarkerStyle()== 33 || grph->GetMarkerStyle()== 27)    grph->SetMarkerSize(1.4*mrkSize);
        if(grph->GetMarkerStyle()== 29 || grph->GetMarkerStyle()== 30)    grph->SetMarkerSize(1.4*mrkSize);
        if(grph->GetMarkerStyle()== 34 || grph->GetMarkerStyle()== 28)    grph->SetMarkerSize(1.2*mrkSize);
        grph->Draw("SAME P");


      }


    }else if (arraytoplot->At(hh)->InheritsFrom("TF1")){
      cout<<"| Drawing a TF1 "<<hh<<endl;
      TF1 *fun = (TF1*) arraytoplot->At(hh);
      fun->SetLineColor(colorArray[hh]);
      if (markerArray[hh]< 10){
	fun->SetLineStyle(markerArray[hh]);
      }else{
	fun->SetLineStyle(3);
      }
      if(control.Contains("Thick")||control.Contains("thick")){
	fun->SetLineWidth(4);
      }else if(control.Contains("Thin")||control.Contains("thin")){
	fun->SetLineWidth(1);
      }else{
	fun->SetLineWidth(2);
      }
      fun->Draw("SAME");
    }
    gPad->RedrawAxis();
  }
}

TCanvas *makeCanvas2D(TObjArray *histArray, const char *controlstring=""){
cout<<" ____________________________________________________________________________"<<endl;
  cout<<"|"<<endl;
  cout<<"| Plots generated via makeCanvas 2D"<<endl;

  gStyle->SetTextFont(43);
  gStyle->SetPalette(54); ///BlueYellow
  TString control(controlstring);


  if(control.Contains("LinearL")){
   const Int_t Number = 256;
   Double_t Red[Number]    = { 0.0143,0.0404,0.0516,0.0616,0.0699,0.0814,0.0857,0.0928,0.1008,0.1064,0.1110,0.1184,0.1224,0.1263,0.1308,0.1357,0.1413,0.1453,0.1506,0.1533,0.1569,0.1624,0.1654,0.1703,0.1742,0.1796,0.1809,0.1798,0.1783,0.1782,0.1765,0.1770,0.1761,0.1754,0.1773,0.1758,0.1751,0.1744,0.1735,0.1748,0.1747,0.1726,0.1731,0.1731,0.1731,0.1720,0.1730,0.1716,0.1710,0.1706,0.1664,0.1582,0.1487,0.1422,0.1352,0.1281,0.1254,0.1207,0.1167,0.1166,0.1147,0.1137,0.1091,0.1089,0.1074,0.1108,0.1096,0.1058,0.1048,0.1047,0.1068,0.1086,0.1067,0.1061,0.1059,0.1056,0.0969,0.0879,0.0832,0.0793,0.0686,0.0639,0.0586,0.0536,0.0388,0.0409,0.0345,0.0300,0.0290,0.0226,0.0154,0.0146,0.0169,0.0117,0.0055,0.0052,0.0008,0.0000,0.0003,0.0013,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0351,0.0797,0.1129,0.1392,0.1566,0.1765,0.1890,0.2030,0.2167,0.2299,0.2391,0.2517,0.2574,0.2679,0.2790,0.2878,0.2965,0.3052,0.3101,0.3187,0.3272,0.3345,0.3406,0.3604,0.3898,0.4169,0.4461,0.4681,0.4900,0.5089,0.5304,0.5500,0.5698,0.5825,0.5999,0.6173,0.6314,0.6487,0.6632,0.6757,0.6912,0.7061,0.7222,0.7305,0.7442,0.7580,0.7709,0.7833,0.7872,0.7972,0.8072,0.8116,0.8211,0.8308,0.8350,0.8450,0.8548,0.8602,0.8658,0.8758,0.8856,0.8895,0.8994,0.9077,0.9106,0.9205,0.9284,0.9343,0.9415,0.9512,0.9549,0.9622,0.9712,0.9708,0.9713,0.9691,0.9699,0.9703,0.9710,0.9695,0.9696,0.9686,0.9681,0.9688,0.9696,0.9703,0.9708,0.9691,0.9692,0.9699,0.9693,0.9714,0.9712,0.9700,0.9707,0.9713,0.9726,0.9738,0.9780,0.9824,0.9868,0.9912,0.9956,1.0000};
   Double_t Green[Number]  = { 0.0143,0.0125,0.0154,0.0184,0.0215,0.0229,0.0273,0.0305,0.0330,0.0356,0.0396,0.0415,0.0453,0.0489,0.0518,0.0541,0.0555,0.0590,0.0603,0.0637,0.0664,0.0678,0.0708,0.0729,0.0755,0.0768,0.0783,0.0807,0.0829,0.0843,0.0866,0.0886,0.0911,0.0933,0.0951,0.0972,0.0999,0.1025,0.1047,0.1071,0.1094,0.1122,0.1153,0.1175,0.1197,0.1224,0.1261,0.1285,0.1314,0.1340,0.1381,0.1482,0.1583,0.1653,0.1729,0.1796,0.1854,0.1904,0.1962,0.2004,0.2057,0.2093,0.2149,0.2190,0.2234,0.2270,0.2315,0.2367,0.2402,0.2444,0.2482,0.2521,0.2568,0.2607,0.2648,0.2690,0.2769,0.2847,0.2907,0.2972,0.3044,0.3106,0.3166,0.3227,0.3292,0.3343,0.3401,0.3458,0.3506,0.3564,0.3619,0.3670,0.3718,0.3773,0.3828,0.3873,0.3927,0.3977,0.4024,0.4072,0.4132,0.4179,0.4242,0.4302,0.4345,0.4395,0.4456,0.4508,0.4563,0.4613,0.4670,0.4716,0.4763,0.4820,0.4870,0.4918,0.4969,0.5024,0.5060,0.5118,0.5166,0.5214,0.5268,0.5315,0.5356,0.5407,0.5461,0.5519,0.5565,0.5624,0.5678,0.5727,0.5778,0.5829,0.5883,0.5931,0.5991,0.6036,0.6084,0.6138,0.6189,0.6239,0.6290,0.6345,0.6381,0.6438,0.6489,0.6536,0.6590,0.6645,0.6656,0.6644,0.6660,0.6703,0.6739,0.6776,0.6814,0.6847,0.6890,0.6928,0.6966,0.7003,0.7044,0.7081,0.7124,0.7162,0.7200,0.7240,0.7280,0.7319,0.7362,0.7402,0.7441,0.7482,0.7523,0.7549,0.7563,0.7574,0.7580,0.7594,0.7612,0.7627,0.7637,0.7649,0.7660,0.7688,0.7701,0.7713,0.7730,0.7741,0.7763,0.7782,0.7795,0.7808,0.7818,0.7852,0.7866,0.7880,0.7896,0.7915,0.7891,0.7903,0.7917,0.7949,0.7964,0.7980,0.8011,0.8026,0.8041,0.8073,0.8100,0.8116,0.8130,0.8164,0.8180,0.8202,0.8241,0.8257,0.8278,0.8307,0.8329,0.8348,0.8384,0.8408,0.8429,0.8482,0.8530,0.8591,0.8642,0.8691,0.8740,0.8800,0.8851,0.8908,0.8962,0.9013,0.9064,0.9115,0.9163,0.9224,0.9273,0.9323,0.9381,0.9425,0.9478,0.9537,0.9587,0.9638,0.9687,0.9738,0.9780,0.9824,0.9868,0.9912,0.9956,1.0000};
   Double_t Blue[Number]   = { 0.0143,0.0325,0.0443,0.0530,0.0615,0.0687,0.0763,0.0805,0.0846,0.0939,0.0979,0.1020,0.1062,0.1105,0.1150,0.1200,0.1256,0.1256,0.1309,0.1344,0.1385,0.1425,0.1471,0.1504,0.1542,0.1595,0.1775,0.1967,0.2159,0.2341,0.2514,0.2646,0.2782,0.2922,0.3026,0.3174,0.3290,0.3405,0.3534,0.3627,0.3739,0.3858,0.3940,0.4051,0.4161,0.4268,0.4330,0.4445,0.4540,0.4642,0.4739,0.4717,0.4683,0.4699,0.4694,0.4708,0.4719,0.4762,0.4773,0.4814,0.4823,0.4888,0.4904,0.4944,0.4984,0.5022,0.5056,0.5077,0.5145,0.5182,0.5223,0.5264,0.5290,0.5346,0.5386,0.5427,0.5343,0.5251,0.5218,0.5153,0.5068,0.5006,0.4955,0.4888,0.4817,0.4786,0.4722,0.4665,0.4647,0.4578,0.4529,0.4487,0.4464,0.4400,0.4334,0.4327,0.4267,0.4220,0.4200,0.4166,0.4107,0.4071,0.3977,0.3919,0.3890,0.3849,0.3776,0.3728,0.3666,0.3597,0.3542,0.3504,0.3464,0.3375,0.3331,0.3256,0.3198,0.3126,0.3101,0.3012,0.2938,0.2871,0.2816,0.2726,0.2675,0.2597,0.2552,0.2506,0.2469,0.2396,0.2360,0.2338,0.2287,0.2250,0.2180,0.2146,0.2089,0.2056,0.1999,0.1961,0.1899,0.1848,0.1759,0.1707,0.1638,0.1592,0.1519,0.1410,0.1322,0.1222,0.0909,0.0322,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0951,0.1988,0.2560,0.3001,0.3397,0.3710,0.4028,0.4292,0.4555,0.4735,0.4993,0.5184,0.5402,0.5602,0.5775,0.5918,0.6094,0.6253,0.6420,0.6576,0.6762,0.6868,0.7026,0.7170,0.7287,0.7409,0.7555,0.7655,0.7746,0.7871,0.7999,0.8067,0.8188,0.8278,0.8378,0.8467,0.8557,0.8647,0.8773,0.8838,0.8961,0.9051,0.9108,0.9230,0.9311,0.9381,0.9470,0.9560,0.9648,0.9711,0.9780,0.9824,0.9868,0.9912,0.9956,1.0000};
   Double_t Length[Number] = { 0,0.0039,0.0078,0.0117,0.0156,0.0195,0.0234,0.0273,0.0312,0.0351,0.0390,0.0429,0.0468,0.0507,0.0546,0.0585,0.0625,0.0664,0.0703,0.0742,0.0781,0.0820,0.0859,0.0898,0.0937,0.0976,0.1015,0.1054,0.1093,0.1132,0.1171,0.1210,0.1250,0.1289,0.1328,0.1367,0.1406,0.1445,0.1484,0.1523,0.1562,0.1601,0.1640,0.1679,0.1718,0.1757,0.1796,0.1835,0.1875,0.1914,0.1953,0.1992,0.2031,0.2070,0.2109,0.2148,0.2187,0.2226,0.2265,0.2304,0.2343,0.2382,0.2421,0.2460,0.2500,0.2539,0.2578,0.2617,0.2656,0.2695,0.2734,0.2773,0.2812,0.2851,0.2890,0.2929,0.2968,0.3007,0.3046,0.3085,0.3125,0.3164,0.3203,0.3242,0.3281,0.3320,0.3359,0.3398,0.3437,0.3476,0.3515,0.3554,0.3593,0.3632,0.3671,0.3710,0.3750,0.3789,0.3828,0.3867,0.3906,0.3945,0.3984,0.4023,0.4062,0.4101,0.4140,0.4179,0.4218,0.4257,0.4296,0.4335,0.4375,0.4414,0.4453,0.4492,0.4531,0.4570,0.4609,0.4648,0.4687,0.4726,0.4765,0.4804,0.4843,0.4882,0.4921,0.4960,0.5000,0.5039,0.5078,0.5117,0.5156,0.5195,0.5234,0.5273,0.5312,0.5351,0.5390,0.5429,0.5468,0.5507,0.5546,0.5585,0.5625,0.5664,0.5703,0.5742,0.5781,0.5820,0.5859,0.5898,0.5937,0.5976,0.6015,0.6054,0.6093,0.6132,0.6171,0.6210,0.6250,0.6289,0.6328,0.6367,0.6406,0.6445,0.6484,0.6523,0.6562,0.6601,0.6640,0.6679,0.6718,0.6757,0.6796,0.6835,0.6875,0.6914,0.6953,0.6992,0.7031,0.7070,0.7109,0.7148,0.7187,0.7226,0.7265,0.7304,0.7343,0.7382,0.7421,0.7460,0.7500,0.7539,0.7578,0.7617,0.7656,0.7695,0.7734,0.7773,0.7812,0.7851,0.7890,0.7929,0.7968,0.8007,0.8046,0.8085,0.8125,0.8164,0.8203,0.8242,0.8281,0.8320,0.8359,0.8398,0.8437,0.8476,0.8515,0.8554,0.8593,0.8632,0.8671,0.8710,0.8750,0.8789,0.8828,0.8867,0.8906,0.8945,0.8984,0.9023,0.9062,0.9101,0.9140,0.9179,0.9218,0.9257,0.9296,0.9335,0.9375,0.9414,0.9453,0.9492,0.9531,0.9570,0.9609,0.9648,0.9687,0.9726,0.9765,0.9804,0.9843,0.9882,0.9921,0.9960};

   if(control.Contains("Inverted")){
     Double_t Red[Number]    = {1.0000,0.9956,0.9912,0.9868,0.9824,0.9780,0.9738,0.9726,0.9713,0.9707,0.9700,0.9712,0.9714,0.9693,0.9699,0.9692,0.9691,0.9708,0.9703,0.9696,0.9688,0.9681,0.9686,0.9696,0.9695,0.9710,0.9703,0.9699,0.9691,0.9713,0.9708,0.9712,0.9622,0.9549,0.9512,0.9415,0.9343,0.9284,0.9205,0.9106,0.9077,0.8994,0.8895,0.8856,0.8758,0.8658,0.8602,0.8548,0.8450,0.8350,0.8308,0.8211,0.8116,0.8072,0.7972,0.7872,0.7833,0.7709,0.7580,0.7442,0.7305,0.7222,0.7061,0.6912,0.6757,0.6632,0.6487,0.6314,0.6173,0.5999,0.5825,0.5698,0.5500,0.5304,0.5089,0.4900,0.4681,0.4461,0.4169,0.3898,0.3604,0.3406,0.3345,0.3272,0.3187,0.3101,0.3052,0.2965,0.2878,0.2790,0.2679,0.2574,0.2517,0.2391,0.2299,0.2167,0.2030,0.1890,0.1765,0.1566,0.1392,0.1129,0.0797,0.0351,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0013,0.0003,0.0000,0.0008,0.0052,0.0055,0.0117,0.0169,0.0146,0.0154,0.0226,0.0290,0.0300,0.0345,0.0409,0.0388,0.0536,0.0586,0.0639,0.0686,0.0793,0.0832,0.0879,0.0969,0.1056,0.1059,0.1061,0.1067,0.1086,0.1068,0.1047,0.1048,0.1058,0.1096,0.1108,0.1074,0.1089,0.1091,0.1137,0.1147,0.1166,0.1167,0.1207,0.1254,0.1281,0.1352,0.1422,0.1487,0.1582,0.1664,0.1706,0.1710,0.1716,0.1730,0.1720,0.1731,0.1731,0.1731,0.1726,0.1747,0.1748,0.1735,0.1744,0.1751,0.1758,0.1773,0.1754,0.1761,0.1770,0.1765,0.1782,0.1783,0.1798,0.1809,0.1796,0.1742,0.1703,0.1654,0.1624,0.1569,0.1533,0.1506,0.1453,0.1413,0.1357,0.1308,0.1263,0.1224,0.1184,0.1110,0.1064,0.1008,0.0928,0.0857,0.0814,0.0699,0.0616,0.0516,0.0404,0.0143};
    Double_t Green[Number]  = {1.0000,0.9956,0.9912,0.9868,0.9824,0.9780,0.9738,0.9687,0.9638,0.9587,0.9537,0.9478,0.9425,0.9381,0.9323,0.9273,0.9224,0.9163,0.9115,0.9064,0.9013,0.8962,0.8908,0.8851,0.8800,0.8740,0.8691,0.8642,0.8591,0.8530,0.8482,0.8429,0.8408,0.8384,0.8348,0.8329,0.8307,0.8278,0.8257,0.8241,0.8202,0.8180,0.8164,0.8130,0.8116,0.8100,0.8073,0.8041,0.8026,0.8011,0.7980,0.7964,0.7949,0.7917,0.7903,0.7891,0.7915,0.7896,0.7880,0.7866,0.7852,0.7818,0.7808,0.7795,0.7782,0.7763,0.7741,0.7730,0.7713,0.7701,0.7688,0.7660,0.7649,0.7637,0.7627,0.7612,0.7594,0.7580,0.7574,0.7563,0.7549,0.7523,0.7482,0.7441,0.7402,0.7362,0.7319,0.7280,0.7240,0.7200,0.7162,0.7124,0.7081,0.7044,0.7003,0.6966,0.6928,0.6890,0.6847,0.6814,0.6776,0.6739,0.6703,0.6660,0.6644,0.6656,0.6645,0.6590,0.6536,0.6489,0.6438,0.6381,0.6345,0.6290,0.6239,0.6189,0.6138,0.6084,0.6036,0.5991,0.5931,0.5883,0.5829,0.5778,0.5727,0.5678,0.5624,0.5565,0.5519,0.5461,0.5407,0.5356,0.5315,0.5268,0.5214,0.5166,0.5118,0.5060,0.5024,0.4969,0.4918,0.4870,0.4820,0.4763,0.4716,0.4670,0.4613,0.4563,0.4508,0.4456,0.4395,0.4345,0.4302,0.4242,0.4179,0.4132,0.4072,0.4024,0.3977,0.3927,0.3873,0.3828,0.3773,0.3718,0.3670,0.3619,0.3564,0.3506,0.3458,0.3401,0.3343,0.3292,0.3227,0.3166,0.3106,0.3044,0.2972,0.2907,0.2847,0.2769,0.2690,0.2648,0.2607,0.2568,0.2521,0.2482,0.2444,0.2402,0.2367,0.2315,0.2270,0.2234,0.2190,0.2149,0.2093,0.2057,0.2004,0.1962,0.1904,0.1854,0.1796,0.1729,0.1653,0.1583,0.1482,0.1381,0.1340,0.1314,0.1285,0.1261,0.1224,0.1197,0.1175,0.1153,0.1122,0.1094,0.1071,0.1047,0.1025,0.0999,0.0972,0.0951,0.0933,0.0911,0.0886,0.0866,0.0843,0.0829,0.0807,0.0783,0.0768,0.0755,0.0729,0.0708,0.0678,0.0664,0.0637,0.0603,0.0590,0.0555,0.0541,0.0518,0.0489,0.0453,0.0415,0.0396,0.0356,0.0330,0.0305,0.0273,0.0229,0.0215,0.0184,0.0154,0.0125,0.0143};
    Double_t Blue[Number]   = {1.0000,0.9956,0.9912,0.9868,0.9824,0.9780,0.9711,0.9648,0.9560,0.9470,0.9381,0.9311,0.9230,0.9108,0.9051,0.8961,0.8838,0.8773,0.8647,0.8557,0.8467,0.8378,0.8278,0.8188,0.8067,0.7999,0.7871,0.7746,0.7655,0.7555,0.7409,0.7287,0.7170,0.7026,0.6868,0.6762,0.6576,0.6420,0.6253,0.6094,0.5918,0.5775,0.5602,0.5402,0.5184,0.4993,0.4735,0.4555,0.4292,0.4028,0.3710,0.3397,0.3001,0.2560,0.1988,0.0951,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0322,0.0909,0.1222,0.1322,0.1410,0.1519,0.1592,0.1638,0.1707,0.1759,0.1848,0.1899,0.1961,0.1999,0.2056,0.2089,0.2146,0.2180,0.2250,0.2287,0.2338,0.2360,0.2396,0.2469,0.2506,0.2552,0.2597,0.2675,0.2726,0.2816,0.2871,0.2938,0.3012,0.3101,0.3126,0.3198,0.3256,0.3331,0.3375,0.3464,0.3504,0.3542,0.3597,0.3666,0.3728,0.3776,0.3849,0.3890,0.3919,0.3977,0.4071,0.4107,0.4166,0.4200,0.4220,0.4267,0.4327,0.4334,0.4400,0.4464,0.4487,0.4529,0.4578,0.4647,0.4665,0.4722,0.4786,0.4817,0.4888,0.4955,0.5006,0.5068,0.5153,0.5218,0.5251,0.5343,0.5427,0.5386,0.5346,0.5290,0.5264,0.5223,0.5182,0.5145,0.5077,0.5056,0.5022,0.4984,0.4944,0.4904,0.4888,0.4823,0.4814,0.4773,0.4762,0.4719,0.4708,0.4694,0.4699,0.4683,0.4717,0.4739,0.4642,0.4540,0.4445,0.4330,0.4268,0.4161,0.4051,0.3940,0.3858,0.3739,0.3627,0.3534,0.3405,0.3290,0.3174,0.3026,0.2922,0.2782,0.2646,0.2514,0.2341,0.2159,0.1967,0.1775,0.1595,0.1542,0.1504,0.1471,0.1425,0.1385,0.1344,0.1309,0.1256,0.1256,0.1200,0.1150,0.1105,0.1062,0.1020,0.0979,0.0939,0.0846,0.0805,0.0763,0.0687,0.0615,0.0530,0.0443,0.0325,0.0143};
   }

   Int_t nb=256;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
  }




  Int_t nHist = histArray->GetEntries();
  if(nHist == 0){cout<<"| ERROR: Arrays empty"<<endl; return;}

  Float_t lableSize = 1.00; // Factor the label will be larger than the relative textsize
  Float_t titleSize = 1.20; // Factor the title will be larger than the relative textsize
  Float_t textSizeFactor = 14500;
  Int_t lableFont= 43;
  Int_t titleFont= 43;

  Float_t canvasWidth;
  Float_t canvasHeight;
  Float_t padFraction;
  Float_t titleOffsetY;
  Float_t titleOffsetX;
  Float_t sideMargin;
  Float_t topMargin;
  Float_t lowMargin;

  if(control.Contains("square")||control.Contains("Square")||control.Contains("SQUARE")){
    cout<<"| - Square Canvas"<<endl;
    cout<<"|   Optimized for 0.49 * textwidth"<<endl;
    canvasWidth=700;
    canvasHeight=canvasWidth;
    titleOffsetY=1.6;
    titleOffsetX=1.5;
    sideMargin=0.12;
    topMargin=sideMargin-0.05;
    lowMargin=sideMargin+0.05;
    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.99 * textwidth"<<endl;
      canvasWidth=2*700;
      textSizeFactor = 2 * textSizeFactor;
      canvasHeight=canvasWidth;
    }
  }else if (control.Contains("horizontal")||control.Contains("Horizontal")||control.Contains("HORIZONTAL")){
    cout<<"| - Horizontal Canvas"<<endl;
    cout<<"|   Optimized for 0.69 * textwidth"<<endl;
    canvasHeight=700;
    canvasWidth=canvasHeight*1.414213562;
    titleOffsetY=1.05;
    titleOffsetX=1.5;
    sideMargin = 0.14/1.414213562;
    topMargin=sideMargin-0.05;
    lowMargin=sideMargin+0.05;
    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.99 * textwidth"<<endl;
      canvasHeight=1.43*700;
      textSizeFactor = 1.43 * textSizeFactor;
      canvasWidth=canvasHeight*1.414213562;
    }
    if (control.Contains("BinLabels")){
      titleOffsetY=1.05;
      titleOffsetX=2.1;
      lowMargin=0.19;
    }
 }else if (control.Contains("OldAspect")||control.Contains("oldaspect")){
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    canvasWidth=700;
    canvasHeight=800;
    titleOffsetY=1.7;
    titleOffsetX=3.5;
    sideMargin=0.12;
    topMargin=0.11;
    lowMargin=0.13;
  }else if (control.Contains("SplitHalf")||control.Contains("splithalf")){
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    textSizeFactor = textSizeFactor;
    canvasWidth=700;
    canvasHeight=700*1.41421356;
    titleOffsetY=2;
    titleOffsetX=4.5;
    sideMargin = 0.14;
    topMargin = sideMargin * 1.414213562/2;
    lowMargin = sideMargin * 1.414213562/2;
  }else{
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    canvasWidth=700;
    canvasHeight=700*1.41421356;
    titleOffsetY=2;
    titleOffsetX=4.5;
    sideMargin = 0.12;
    topMargin = 0.12 * 1.414213562/2;
    lowMargin = 0.12 * 1.414213562/2;
  }


  if (control.Contains("CMYK")||control.Contains("cmyk")){gStyle->SetColorModelPS(1);}


  TPad *upperPad = 0x0;
  TRandom *random = new TRandom(histArray->Hash());


  /// Check if first element of th histogram array is indeed an Histogram.
  if(histArray->At(0)){
    if (!histArray->At(0)->InheritsFrom("TH2")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH2D *hist0 = (TH2D*) histArray->At(0);
    if(!hist0){cout<<"| ERROR: Histogram empty"<<endl;}
    TString title("default");
    title += Form("%f",random->Rndm());
    Double_t xMin = hist0->GetXaxis()->GetBinLowEdge(hist0->GetXaxis()->GetFirst())+0.0000001;
    Double_t xMax = hist0->GetXaxis()->GetBinUpEdge(hist0->GetXaxis()->GetLast())-0.0000001;
    Double_t yMin = hist0->GetYaxis()->GetBinLowEdge(hist0->GetYaxis()->GetFirst())+0.0000001;
    Double_t yMax = hist0->GetYaxis()->GetBinUpEdge(hist0->GetYaxis()->GetLast())-0.0000001;
    cout<<"| - Axis range X: "<<xMin<<"-"<<xMax<<endl;
    cout<<"| - Axis range Y: "<<yMin<<"-"<<yMax<<endl;
    hist0->GetYaxis()->CenterTitle(0);
    if(control.Contains("CenterTitle")||control.Contains("centertitle")) hist0->GetYaxis()->CenterTitle(1);
  }

    /// Create Canvas in a given size
    TCanvas *newCanvas = new TCanvas(title,title,10,10,canvasWidth+10,canvasHeight+10);
    newCanvas->SetFillStyle(4000);
    newCanvas->SetLeftMargin(sideMargin);
    newCanvas->SetRightMargin(sideMargin);
    newCanvas->SetTopMargin(topMargin);
    newCanvas->SetBottomMargin(lowMargin);
    newCanvas->SetTickx(1);
    newCanvas->SetTicky(1);
    newCanvas->cd();

    Double_t relativeTextSize;
    Double_t pad_width  = gPad->XtoPixel(gPad->GetX2());
    Double_t pad_height = gPad->YtoPixel(gPad->GetY1());
    if (pad_width < pad_height){relativeTextSize = 1/pad_width;}
    else{relativeTextSize = 1/pad_height;}
    relativeTextSize = textSizeFactor * relativeTextSize;

    Short_t defaultColorArray[14]={kBlue-7,kRed+1,kGreen-3,6,8,9,11,12,13,14,15,16,17,18};
    Short_t defaultMarkerArray[14]={20,21,22,23,24,25,26,27,28,29,30,2,3,5};

    PlotArray(histArray,controlstring,defaultColorArray,defaultMarkerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax,yMin,yMax);

    if(control.Contains("logX")||control.Contains("logx")||control.Contains("LogX")||control.Contains("LOGX")){
      newCanvas->SetLogx(1); cout<<"| - LogX"<<endl;}
    if(control.Contains("logY")||control.Contains("logy")||control.Contains("LogY")||control.Contains("LOGY")){
      newCanvas->SetLogy(1); cout<<"| - LogY"<<endl;}
    if(control.Contains("logZ")||control.Contains("logz")||control.Contains("LogZ")||control.Contains("LOGZ")){
      newCanvas->SetLogz(1); cout<<"| - LogZ"<<endl;}
    if(control.Contains("gridY")||control.Contains("gridy")||control.Contains("GridY")||control.Contains("GRIDY")){
      newCanvas->SetGridy(1);cout<<"| - Grid Y"<<endl;}

    /// Draw extras
  /// Timestamp
  if(!control.Contains("Notime")&&!control.Contains("NoTime")&&!control.Contains("notime")&&!control.Contains("NOTIME")){
    TTimeStamp time;
    TString stTime;
    stTime=Form("#color[16]{%i}",time.GetDate());
    TLatex *timeStamp = new TLatex();
    timeStamp->SetNDC();
    timeStamp->SetTextAlign(22);
    timeStamp->SetTextFont(63);
    timeStamp->SetTextSizePixels(10);
    timeStamp->DrawLatex(0.96,0.98,stTime);
    }else{
      cout<<"|         - No Timestamp"<<endl;
    }
  /// Text "This work"
  if(control.Contains("ThisWork")||control.Contains("Thiswork")||control.Contains("thiswork")||control.Contains("THISWORK")){
    TLatex *thsWrk = new TLatex();
    thsWrk->SetNDC();
    thsWrk->SetTextAlign(22);
    thsWrk->SetTextFont(43);
    thsWrk->SetTextSizePixels(20);
    thsWrk->DrawLatex(0.91,0.97,"#color[16]{this thesis}");
  }
  /// Unified or work logo
 if(control.Contains("Logo") ||control.Contains("logo") ||control.Contains("LOGO")){
    Double_t scale = 0.1;
    if(control.Contains("square")||control.Contains("Square")||control.Contains("SQUARE")){Double_t x1 = 0.7; Double_t y1 = 0.7;}
    else if (control.Contains("horizontal")||control.Contains("Horizontal")||control.Contains("HORIZONTAL")){Double_t x1 = 0.75; Double_t y1 = 0.8;}
    else{Double_t x1 = 0.7; Double_t y1 = 0.8;}
    Double_t x2 = x1+scale;
    Double_t y2 = y1+scale;

    if(control.Contains("Unified") ||control.Contains("unified") ||control.Contains("UNIFIED")){Char_t* logopath = "$TOOLS/graphics/einhorn.pdf";}
    if(control.Contains("Work") ||control.Contains("work") ||control.Contains("WORK")){Char_t* logopath = "$TOOLS/graphics/wrkprgs.png";}
    TImage* logo = TImage::Open(logopath);
    TPad *pad_logo = new TPad("pad_logo","pad_logo",x1,y1,x2,y2);
    pad_logo->SetMargin(0,0,0,0);
    newCanvas->cd();
    pad_logo->Draw();
    pad_logo->cd();
    logo->Draw();
  }

  cout<<"|_____________________________________________________________________________"<<endl;
  cout<<" "<<endl;
  return newCanvas;
}


TCanvas *makeCanvas(TObjArray *arrHist_top, TObjArray *arrHist_mid,TObjArray *arrHist_low,const char *controlstring="", Short_t *colorArray, Short_t *markerArray){

  cout<<" ____________________________________________________________________________"<<endl;
  cout<<"|"<<endl;
  cout<<"| Plots generated via makeCanvas for three"<<endl;

  gStyle->SetTextFont(43);
  TString control(controlstring);
  if(control.Contains("OwnColors")){DefineOwnColors();}

  Int_t nHist = arrHist_top->GetEntries();
  if(nHist == 0){cout<<"| ERROR: Arrays empty"<<endl; return;}

  Float_t lableSize = 1.00; // Factor the label will be larger than the relative textsize
  Float_t titleSize = 1.20; // Factor the title will be larger than the relative textsize
  Float_t textSizeFactor = 14500;
  Int_t lableFont= 43;
  Int_t titleFont= 43;

  Float_t canvasWidth;
  Float_t canvasHeight;
  Float_t padFraction;
  Float_t titleOffsetY;
  Float_t titleOffsetX;
  Float_t sideMargin;
  Float_t topMargin;
  Float_t lowMargin;

  if(control.Contains("square")||control.Contains("Square")||control.Contains("SQUARE")){
    cout<<"| - Square Canvas"<<endl;
    cout<<"|   Optimized for 0.49 * textwidth"<<endl;
    canvasWidth=700;
    canvasHeight=canvasWidth;
    titleOffsetY=1.6;
    titleOffsetX=1.5;
    sideMargin=0.24;
    padFraction = 1./3.;
    topMargin = (sideMargin);
    lowMargin = (sideMargin);
    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.99 * textwidth"<<endl;
      canvasWidth=2*700;
      textSizeFactor = 2 * textSizeFactor;
      canvasHeight=canvasWidth;
    }
    textSizeFactor = padFraction * textSizeFactor;
  }else if (control.Contains("horizontal")||control.Contains("Horizontal")||control.Contains("HORIZONTAL")){
    cout<<"| - Horizontal Canvas"<<endl;
    cout<<"|   Optimized for 0.69 * textwidth"<<endl;
    canvasHeight=700;
    canvasWidth=canvasHeight*1.414213562;
    titleOffsetY=3;
    titleOffsetX=1.5;
    padFraction = 1./3.;
    sideMargin = 3*0.12/1.414213562;
    topMargin=0.12;
    lowMargin=0.12;
    textSizeFactor=textSizeFactor/1.414213562;
    
    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.99 * textwidth"<<endl;
      canvasHeight=1.43*700;
      textSizeFactor = 1.43 * textSizeFactor;
      canvasWidth=canvasHeight*1.414213562;
    }
    if (control.Contains("BinLabels")){
      titleOffsetY=1.05;
      titleOffsetX=2.1;
      lowMargin=0.19;
    }
  }else{
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    cout<<"|   Optimized for 0.49 * textwidth"<<endl;
    canvasWidth=700;
    canvasHeight=700*1.41421356;
    titleOffsetY=2;
    titleOffsetX=4.5;
    padFraction = 1./3.;
    sideMargin = 0.12;
    topMargin = 0.45 * 1.414213562 *padFraction;
    lowMargin = topMargin;
    textSizeFactor = textSizeFactor*padFraction;

    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.85 * textwidth"<<endl;
      canvasWidth=1.735*700;
      canvasHeight=1.735*700*1.41421356;
      textSizeFactor = 3 * textSizeFactor;
    }
  }

  TRandom *random = new TRandom(arrHist_top->Hash());
  Double_t xMin;
  Double_t xMax;

  if(arrHist_top->At(0)){
    if (!arrHist_top->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist_top_0 = (TH1D*) arrHist_top->At(0);
    if(!hist_top_0){cout<<"| ERROR: Histogram empty"<<endl;}
    TString title("default");
    title += Form("%f",random->Rndm());
    xMin = hist_top_0->GetXaxis()->GetBinLowEdge(hist_top_0->GetXaxis()->GetFirst())+0.0000001;
    xMax = hist_top_0->GetXaxis()->GetBinUpEdge(hist_top_0->GetXaxis()->GetLast())-0.0000001;
    cout<<"| - Axis range: "<<xMin<<"-"<<xMax<<endl;
    hist_top_0->GetYaxis()->CenterTitle(0);
    if(control.Contains("CenterTitle")||control.Contains("centertitle")) hist_top_0->GetYaxis()->CenterTitle(1);
  }
  if(arrHist_mid->At(0)){
    if (!arrHist_mid->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist_mid_0 = (TH1D*) arrHist_mid->At(0);
    if(!hist_mid_0){cout<<"| ERROR: Histogram empty"<<endl;}
    hist_mid_0->GetXaxis()->SetTickLength(0.06);
    hist_mid_0->GetYaxis()->SetNdivisions(506);
    hist_mid_0->SetLineWidth(2);
    hist_mid_0->GetYaxis()->CenterTitle(1);
  }
  if(arrHist_low->At(0)){
    if (!arrHist_low->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist_low_0 = (TH1D*) arrHist_low->At(0);
    if(!hist_low_0){cout<<"| ERROR: Histogram empty"<<endl;}
    hist_low_0->GetXaxis()->SetTickLength(0.06);
    hist_low_0->GetYaxis()->SetNdivisions(506);
    hist_low_0->SetLineWidth(2);
    hist_low_0->GetYaxis()->CenterTitle(1);
  }



  /// Create Canvas in a given size
  TCanvas *newCanvas = new TCanvas(title,title,10,10,canvasWidth+10,canvasHeight+10);
  newCanvas->SetFillStyle(4000);
  newCanvas->cd();


  if (control.Contains("horizontal")||control.Contains("Horizontal")||control.Contains("HORIZONTAL")){
    TPad *pad_top = new TPad("pad_top","Top"     ,0     ,0  ,1./3.+ sideMargin/9 ,1);
    TPad *pad_mid = new TPad("pad_mid","Mid"     ,1./3. + sideMargin/9 ,0  ,2./3.- sideMargin/9 ,1);
    TPad *pad_low = new TPad("pad_low","Low"     ,2./3.- sideMargin/9,0  ,1     ,1);

    pad_top->SetFillStyle(4000);
    pad_top->SetTopMargin(topMargin);
    pad_top->SetLeftMargin(sideMargin);
    pad_top->SetRightMargin(0.0);
    pad_top->SetBottomMargin(lowMargin);
    pad_top->SetTickx(1);
    pad_top->SetTicky(1);
    pad_top->Draw();

    pad_mid->SetFillStyle(4000);
    pad_mid->SetTopMargin(topMargin);
    pad_mid->SetLeftMargin(0.0);
    pad_mid->SetRightMargin(0.0);
    pad_mid->SetBottomMargin(lowMargin);
    pad_mid->SetTickx(1);
    pad_mid->SetTicky(1);
    pad_mid->Draw();

    pad_low->SetFillStyle(4000);
    pad_low->SetTopMargin(topMargin);
    pad_low->SetLeftMargin(0.0);
    pad_low->SetRightMargin(sideMargin);
    pad_low->SetBottomMargin(lowMargin);
    pad_low->SetTickx(1);
    pad_low->SetTicky(1);
    pad_low->Draw();
  }else{
    TPad *pad_top = new TPad("pad_top","Top"     ,0  ,2./3.- topMargin/9. ,1, 1);
    TPad *pad_mid = new TPad("pad_mid","Mid"     ,0  ,1./3.+ topMargin/9. ,1, 2/3.- topMargin/9.);
    TPad *pad_low = new TPad("pad_low","Low"     ,0  ,0                ,1, 1./3.+ topMargin/9.);

    pad_top->SetFillStyle(4000);
    pad_top->SetTopMargin(topMargin);
    pad_top->SetLeftMargin(sideMargin);
    pad_top->SetRightMargin(sideMargin);
    pad_top->SetBottomMargin(0.0);
    pad_top->SetTickx(1);
    pad_top->SetTicky(1);
    pad_top->Draw();

    pad_mid->SetFillStyle(4000);
    pad_mid->SetTopMargin(0.0);
    pad_mid->SetLeftMargin(sideMargin);
    pad_mid->SetRightMargin(sideMargin);
    pad_mid->SetBottomMargin(0.0);
    pad_mid->SetTickx(1);
    pad_mid->SetTicky(1);
    pad_mid->Draw();

    pad_low->SetFillStyle(4000);
    pad_low->SetTopMargin(0.0);
    pad_low->SetLeftMargin(sideMargin);
    pad_low->SetRightMargin(sideMargin);
    pad_low->SetBottomMargin(lowMargin);
    pad_low->SetTickx(1);
    pad_low->SetTicky(1);
    pad_low->Draw();
  }

  if(control.Contains("logX")||control.Contains("logx")||control.Contains("LogX")||control.Contains("LOGX")){
    cout<<"| - LogX"<<endl;
    pad_top->SetLogx(1);
    pad_mid->SetLogx(1);
    pad_low->SetLogx(1);
  }
  if(control.Contains("logY")||control.Contains("logy")||control.Contains("LogY")||control.Contains("LOGY")){
    cout<<"| - LogY"<<endl;
    pad_top->SetLogy(1);
    pad_mid->SetLogy(1);
    pad_low->SetLogy(1);
  }

  newCanvas->cd();
  pad_top->cd();

  Double_t relativeTextSize;
  Double_t pad_width;
  Double_t pad_height;

  /// Calculate the relative text size, independent of the size of the pad
  pad_width  = gPad->XtoPixel(gPad->GetX2());
  pad_height = gPad->YtoPixel(gPad->GetY1());
  if (pad_width < pad_height){relativeTextSize = 1/pad_width;}
  else{relativeTextSize = 1/pad_height;}
  relativeTextSize = textSizeFactor * relativeTextSize;

  /// Use the standardtised PlotArray function to loop over the histogram an to draw the elements.
  PlotArray(arrHist_top,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);

  pad_mid->cd();
  PlotArray(arrHist_mid,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);

  pad_low->cd();
  PlotArray(arrHist_low,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);

  pad_top->cd();
  
  if(control.Contains("ThisWork")||control.Contains("Thiswork")||control.Contains("thiswork")||control.Contains("THISWORK")){
    TLatex *thsWrk = new TLatex();
    thsWrk->SetNDC();
    thsWrk->SetTextAlign(22);
    thsWrk->SetTextFont(43);
    thsWrk->SetTextSizePixels(20);
    thsWrk->DrawLatex(0.845,0.81,"#color[16]{this thesis}");
  }
  
  
  cout<<"|_____________________________________________________________________________"<<endl;
  cout<<" "<<endl;
  return newCanvas;
}




TCanvas *makeCanvas(TObjArray *arrHist_TL, TObjArray *arrHist_TR,TObjArray *arrHist_BL, TObjArray *arrHist_BR,const char *controlstring="", Short_t *colorArray, Short_t *markerArray){

  cout<<" ____________________________________________________________________________"<<endl;
  cout<<"|"<<endl;
  cout<<"| Plots generated via makeCanvas for four"<<endl;

  gStyle->SetTextFont(43);
  TString control(controlstring);
  if(control.Contains("OwnColors")){DefineOwnColors();}

  Int_t nHist = arrHist_TL->GetEntries();
  if(nHist == 0){cout<<"| ERROR: Arrays empty"<<endl; return;}

  Float_t lableSize = 1.00; // Factor the label will be larger than the relative textsize
  Float_t titleSize = 1.20; // Factor the title will be larger than the relative textsize
  Float_t textSizeFactor = 14500;
  Int_t lableFont= 43;
  Int_t titleFont= 43;

  Float_t canvasWidth;
  Float_t canvasHeight;
  Float_t padFraction;
  Float_t titleOffsetY;
  Float_t titleOffsetX;
  Float_t sideMargin;
  Float_t topMargin;
  Float_t lowMargin;

  if(control.Contains("square")||control.Contains("Square")||control.Contains("SQUARE")){
    cout<<"| - Square Canvas"<<endl;
    cout<<"|   Optimized for 0.49 * textwidth"<<endl;
    canvasWidth=700;
    canvasHeight=canvasWidth;
    titleOffsetY=1.6;
    titleOffsetX=1.5;
    sideMargin=0.24;
    padFraction = 0.5;
    topMargin = (sideMargin);
    lowMargin = (sideMargin);
    if(control.Contains("FullPage")||control.Contains("fullpage")){
      cout<<"|   Optimized for 0.99 * textwidth"<<endl;
      canvasWidth=2*700;
      textSizeFactor = 2 * textSizeFactor;
      canvasHeight=canvasWidth;
    }
    textSizeFactor = padFraction * textSizeFactor;
  }else{
    cout<<"| - Improved aspect ratio Canvas"<<endl;
    canvasWidth=700;
    canvasHeight=700*1.41421356;
    titleOffsetY=2;
    titleOffsetX=4.5;
    padFraction = 0.5;
    sideMargin = 0.24;
    topMargin = 0.24 * 1.414213562/2;
    lowMargin = 0.24 * 1.414213562/2;
    textSizeFactor = padFraction * textSizeFactor;
  }

  TRandom *random = new TRandom(arrHist_TL->Hash());
  Double_t xMin;
  Double_t xMax;

  if(arrHist_TL->At(0)){
    if (!arrHist_TL->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist_TL_0 = (TH1D*) arrHist_TL->At(0);
    if(!hist_TL_0){cout<<"| ERROR: Histogram empty"<<endl;}
    TString title("default");
    title += Form("%f",random->Rndm());
    xMin = hist_TL_0->GetXaxis()->GetBinLowEdge(hist_TL_0->GetXaxis()->GetFirst())+0.0000001;
    xMax = hist_TL_0->GetXaxis()->GetBinUpEdge(hist_TL_0->GetXaxis()->GetLast())-0.0000001;
    cout<<"| - Axis range: "<<xMin<<"-"<<xMax<<endl;
    hist_TL_0->GetYaxis()->CenterTitle(0);
    if(control.Contains("CenterTitle")||control.Contains("centertitle")) hist_TL_0->GetYaxis()->CenterTitle(1);
  }
  if(arrHist_TR->At(0)){
    if (!arrHist_TR->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist_TR_0 = (TH1D*) arrHist_TR->At(0);
    if(!hist_TR_0){cout<<"| ERROR: Histogram empty"<<endl;}
    hist_TR_0->GetXaxis()->SetTickLength(0.06);
    hist_TR_0->GetYaxis()->SetNdivisions(506);
    hist_TR_0->SetLineWidth(2);
    hist_TR_0->GetYaxis()->CenterTitle(1);
  }
  if(arrHist_BL->At(0)){
    if (!arrHist_BL->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist_BL_0 = (TH1D*) arrHist_BL->At(0);
    if(!hist_BL_0){cout<<"| ERROR: Histogram empty"<<endl;}
    hist_BL_0->GetXaxis()->SetTickLength(0.06);
    hist_BL_0->GetYaxis()->SetNdivisions(506);
    hist_BL_0->SetLineWidth(2);
    hist_BL_0->GetYaxis()->CenterTitle(1);
  }
  if(arrHist_BR->At(0)){
    if (!arrHist_BR->At(0)->InheritsFrom("TH1")){cout<<"|ERROR: First entry has to be an Histogram"<<endl;}
    TH1D *hist_BR_0 = (TH1D*) arrHist_BR->At(0);
    if(!hist_BR_0){cout<<"| ERROR: Histogram empty"<<endl;}
    hist_BR_0->GetXaxis()->SetTickLength(0.06);
    hist_BR_0->GetYaxis()->SetNdivisions(506);
    hist_BR_0->SetLineWidth(2);
    hist_BR_0->GetYaxis()->CenterTitle(1);
  }




  /// Create Canvas in a given size
  TCanvas *newCanvas = new TCanvas(title,title,10,10,canvasWidth+10,canvasHeight+10);
  newCanvas->SetFillStyle(4000);
  newCanvas->cd();

  /// Create upper pad for the histograms \remark upper pad has 72%
  TPad *pad_TL = new TPad("pad_TL","Top Left"     ,0            ,padFraction ,padFraction ,1);
  TPad *pad_TR = new TPad("pad_TR","Top Right"    ,padFraction  ,padFraction ,1           ,1);
  TPad *pad_BL = new TPad("pad_BL","Bottom Left"  ,0            ,0           ,padFraction ,padFraction);
  TPad *pad_BR = new TPad("pad_BR","Bottom Right" ,padFraction  ,0           ,1           ,padFraction);

  pad_TL->SetFillStyle(4000);
  pad_TL->SetTopMargin(topMargin);
  pad_TL->SetLeftMargin(sideMargin);
  pad_TL->SetRightMargin(0.0);
  pad_TL->SetBottomMargin(0.0);
  pad_TL->SetTickx(1);
  pad_TL->SetTicky(1);
  pad_TL->Draw();

  pad_TR->SetFillStyle(4000);
  pad_TR->SetTopMargin(topMargin);
  pad_TR->SetLeftMargin(0.0);
  pad_TR->SetRightMargin(sideMargin);
  pad_TR->SetBottomMargin(0.0);
  pad_TR->SetTickx(1);
  pad_TR->SetTicky(1);
  pad_TR->Draw();


  pad_BL->SetFillStyle(4000);
  pad_BL->SetTopMargin(0.0);
  pad_BL->SetLeftMargin(sideMargin);
  pad_BL->SetRightMargin(0.0);
  pad_BL->SetBottomMargin(lowMargin);
  pad_BL->SetTickx(1);
  pad_BL->SetTicky(1);
  pad_BL->Draw();


  pad_BR->SetFillStyle(4000);
  pad_BR->SetTopMargin(0.0);
  pad_BR->SetLeftMargin(0.0);
  pad_BR->SetRightMargin(sideMargin);
  pad_BR->SetBottomMargin(lowMargin);
  pad_BR->SetTickx(1);
  pad_BR->SetTicky(1);
  pad_BR->Draw();

  if(control.Contains("logX")||control.Contains("logx")||control.Contains("LogX")||control.Contains("LOGX")){
    cout<<"| - LogX"<<endl;
    pad_TL->SetLogx(1);
    pad_TR->SetLogx(1);
    pad_BL->SetLogx(1);
    pad_BR->SetLogx(1);
  }
  if(control.Contains("logY")||control.Contains("logy")||control.Contains("LogY")||control.Contains("LOGY")){
    cout<<"| - LogY"<<endl;
    pad_TL->SetLogy(1);
    pad_TR->SetLogy(1);
    pad_BL->SetLogy(1);
    pad_BR->SetLogy(1);
  }

  newCanvas->cd();
  pad_TL->cd();

  Double_t relativeTextSize;
  Double_t pad_width;
  Double_t pad_height;

  /// Calculate the relative text size, independent of the size of the pad
  pad_width  = gPad->XtoPixel(gPad->GetX2());
  pad_height = gPad->YtoPixel(gPad->GetY1());
  if (pad_width < pad_height){relativeTextSize = 1/pad_width;}
  else{relativeTextSize = 1/pad_height;}
  relativeTextSize = textSizeFactor * relativeTextSize;

  /// Use the standardtised PlotArray function to loop over the histogram an to draw the elements.
  PlotArray(arrHist_TL,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);

  pad_TR->cd();
  PlotArray(arrHist_TR,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);

  pad_BL->cd();
  PlotArray(arrHist_BL,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);

  pad_BR->cd();
  PlotArray(arrHist_BR,controlstring,colorArray,markerArray,relativeTextSize,lableSize, titleSize, lableFont, titleFont, titleOffsetY, titleOffsetX, sideMargin, xMin,xMax);

  pad_TL->cd();
  cout<<"|_____________________________________________________________________________"<<endl;
  cout<<" "<<endl;
  return newCanvas;
}


void *DefineOwnColors(const char *palette="std"){
  TString Palette(palette);
  if(Palette.Contains("TUD")){
    if(gROOT->GetColor(4202) && gROOT->GetColor(5202)){ return;}
    TColor * a1 =new TColor(4101,0.36,0.52,0.76);
    TColor * a2 =new TColor(4102,0.0,0.61,0.85);
    TColor * a3 =new TColor(4103,0.31,0.71,0.58);
    TColor * a4 =new TColor(4104,0.69,0.80,0.31);
    TColor * a5 =new TColor(4105,0.87,0.87,0.28);
    TColor * a6 =new TColor(4106,1.0,0.88,0.36);
    TColor * a7 =new TColor(4107,0.97,0.73,0.24);
    TColor * a8 =new TColor(4108,0.93,0.48,0.20);
    TColor * a9 =new TColor(4109,0.91,0.38,0.24);
    TColor * a10 =new TColor(4110,0.79,0.19,0.56);
    TColor * a11 =new TColor(4111,0.50,0.27,0.59);

    TColor * b1 =new TColor(4201,0.0,0.42,0.66);
    TColor * b2 =new TColor(4202,0.0,0.51,0.80);
    TColor * b2o =new TColor(5202,0.0,1.4*0.51,1);
    TColor * b3 =new TColor(4203,0.0,0.62,0.51);
    TColor * b4 =new TColor(4204,0.6,0.753,0.0);
    TColor * b4o =new TColor(5204,1.4*0.6,1,0.0);
    TColor * b5 =new TColor(4205,0.79,0.83,0.0);
    TColor * b6 =new TColor(4206,0.99,0.79,0.0);
    TColor * b7 =new TColor(4207,0.96,0.65,0.0);
    TColor * b8 =new TColor(4208,0.93,0.40,0.0);
    TColor * b9 =new TColor(4209,0.91,0.0,0.10);
    TColor * b90 =new TColor(5209,0.91,0.38,0.24);
    TColor * b10 =new TColor(4210,0.66,0.0,0.52);
    TColor * b11 =new TColor(4211,0.45,0.06,0.52);

    TColor * c1 =new TColor(4301,0.0,0.31,0.54);
    TColor * c2 =new TColor(4302,0.0,0.41,0.62);
    TColor * c3 =new TColor(4303,0.0,0.53,0.47);
    TColor * c4 =new TColor(4304,0.50,0.67,0.09);
    TColor * c5 =new TColor(4305,0.69,0.74,0.0);
    TColor * c6 =new TColor(4306,0.84,0.67,0.0);
    TColor * c7 =new TColor(4307,0.82,0.53,0.0);
    TColor * c8 =new TColor(4308,0.80,0.30,0.01);
    TColor * c9 =new TColor(4309,0.73,0.06,0.13);
    TColor * c10 =new TColor(4310,0.6,0.07,0.41);
    TColor * c11 =new TColor(4311,0.38,0.11,0.45);

    TColor * d1 =new TColor(4401,0.14,0.21,0.45);
    TColor * d2 =new TColor(4402,0.0,0.31,0.45);
    TColor * d3 =new TColor(4403,0.0,0.44,0.37);
    TColor * d4 =new TColor(4404,0.42,0.73,0.13);
    TColor * d5 =new TColor(4405,0.60,0.65,0.2);
    TColor * d6 =new TColor(4406,0.68,0.56,0.0);
    TColor * d7 =new TColor(4407,0.74,0.44,0.0);
    TColor * d8 =new TColor(4408,0.66,0.29,0.7);
    TColor * d9 =new TColor(4409,0.60,0.11,0.15);
    TColor * d10 =new TColor(4410,0.45,0.13,0.39);
    TColor * d11 =new TColor(4411,0.30,0.13,0.42);
  }

  else{
    if(gROOT->GetColor(4001)){
      cout<<"| Colors already defined"<<endl;
      return;
    }else{
      TColor * m01 =new TColor(4001,0.267, 0.467, 0.667);
      TColor * m02 =new TColor(4002,0.8, 0.4, 0.467);
      TColor * m03 =new TColor(4003,0.867, 0.8, 0.467);
      TColor * m04 =new TColor(4004,0.067, 0.467, 0.2);
      TColor * m05 =new TColor(4005,0.533, 0.8, 0.933);
      TColor * m06 =new TColor(4006,0.2, 0.133, 0.533);
      TColor * m07 =new TColor(4007,0.267, 0.667, 0.6);
      TColor * m08 =new TColor(4008,0.6, 0.6, 0.2);
      TColor * m09 =new TColor(4009,0.533, 0.133, 0.333);
      TColor * m10 =new TColor(4010,0.4, 0.067, 0);
      TColor * m11 =new TColor(4011,0.4, 0.6, 0.8);
      TColor * m12 =new TColor(4012,0.667, 0.267, 0.4);
    }
  }
}
