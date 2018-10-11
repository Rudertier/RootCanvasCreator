void gaus(){
  gROOT->LoadMacro("../CanvasCreator.C");

  
  
  TH1D *hGaus_1 = new TH1D("hGaus_1", "Gaus 1", 100, -5, 5);
  TH1D *hGaus_2 = new TH1D("hGaus_2", "Gaus 2", 100, -5, 5);
  
  hGaus_1-> FillRandom("gaus", 10000);
  
  for (Int_t ii = 0; ii < 100; ii++){
    hGaus_1->SetBinError(ii,0.1*hGaus_1->GetBinContent(ii));
    
    if (ii > 10){
      hGaus_2->SetBinContent(ii,0.8 * hGaus_1->GetBinContent(ii-10));
      hGaus_2->SetBinError(ii,0.8 * hGaus_1->GetBinError(ii-10));
    }else{
      hGaus_2->SetBinContent(ii,0);
      hGaus_2->SetBinError(ii,0);
    }
  }

  TH1D* hDifference = hGaus_1->Clone("hDifference");
  for (Int_t ii = 0; ii < 100; ii++){
    hDifference->SetBinContent(ii, hGaus_1->GetBinContent(ii) - hGaus_2->GetBinContent(ii));
    hDifference->SetBinError(ii, 0);
  }
  
  
  TObjArray *array = new TObjArray();
  array->Add(hGaus_1);
  array->Add(hGaus_2);
  
  TObjArray *diffs = new TObjArray();
  diffs->Add(hDifference);
  
  TLegend *legend = new TLegend(0.15,0.5,0.3,0.8);
  legend->AddEntry(hGaus_1,"Gaus","lp");
  legend->AddEntry(hGaus_2,"Gaus (shifted)","lp");
  array->Add(legend);

  
  TPaveText *pavet = new TPaveText(0.7,0.65,0.7,0.8,"blNDC");
  pavet->AddText("Example plot");
  array->Add(pavet);
  

  TLine *line = new TLine(-5,0,5,0);
  diffs->Add(line);

  Double_t yMin = 1;
  Double_t yMax = 499;

  hGaus_1->SetAxisRange(yMin,yMax,"Y");
  hGaus_1->SetAxisRange(-5,4.99,"X");
  hGaus_1->GetYaxis()->SetTitle("y");
  hGaus_1->GetXaxis()->SetTitle("x");

  hDifference->SetAxisRange(-300,299,"Y");
  hDifference->SetAxisRange(-5,5,"X");
  hDifference->GetYaxis()->SetTitle("Difference");
  hDifference->GetXaxis()->SetTitle("x");
  
  Short_t colorArray[]  = {kBlue-7,kGreen+2};
  Short_t markerArray[] = {24,20};

  TCanvas *cnvs = makeCanvas(array,diffs,"Square SplitHalf ThisWork",colorArray,markerArray);
  cnvs->Draw();
  cnvs->SaveAs("gaus.png");
}