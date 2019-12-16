#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
using namespace RooFit ;

// execute with 
// .x DrawFitPV.cc (PvMCAngCalc,-0.01, 0.01)
// inside 100mSim

void DrawFitPV( TH1F* histo, double xmin, double xmax, string title=" ", bool print=false){

//definizione delle variabili
  RooRealVar x    ( "x"    , "PV z difference", xmin, xmax , "cm" );

  RooRealVar mean ( "mean", "mean"    , 0   ,     -0.01 ,     0.01  , "." );
  RooRealVar widt1( "widt1", "Width1"   , 0.0017 , 0.00001 , 0.1, "." );
  RooRealVar widt2( "widt2", "Width2"   , 0.0044 , 0.00001 , 0.1, "." );

//definisco il modello gaussiano
  RooGaussian    gauss1( "gauss1", "Gaussian 1" , x, mean, widt1 );
  RooGaussian    gauss2( "gauss2", "Gaussian 2" , x, mean, widt2 );
//definisco la frazione reciproca delle due
  RooRealVar gfrac1( "gfrac1", "fraction 1"   , 0.5 ,   0.0, 1.0  );
//prendo i dati
  RooDataHist data("data","data",x, Import(*histo)) ;
 //sommo le gaussiane
  RooAddPdf GaussSum ( "GaussSum", "Gauss 1+2", RooArgList ( gauss1, gauss2 ), gfrac1  );
 
//preparo il canvas-
 string name=histo->GetName();
  TCanvas* can = new TCanvas( (name).c_str(), (name).c_str(), 800, 600 );
  can->SetLeftMargin( 0.15 );
  can->cd();
 
//creo e setto il frame
  RooPlot* frame = x.frame() ;
  data.plotOn(frame) ;
//fitto
  GaussSum.fitTo(data) ;
//plotto
  GaussSum.plotOn(frame) ;
  GaussSum.plotOn( frame, Components( "gauss1" ), LineStyle( kDashed ), LineColor( kRed   ) );
  GaussSum.plotOn( frame, Components( "gauss2" ), LineStyle( kDashed ), LineColor( kGreen ) );

  RooArgSet params = RooArgList(mean, widt1, widt2) ;
  GaussSum.paramOn(frame,Layout(0.7, 0.95, 0.9), Format("NE", AutoPrecision()), Parameters(params));

  frame->SetYTitle("Events");
  frame->SetTitle (title.c_str());
  frame->getAttText()->SetTextSize(0.02) ;
  ofstream out ((name+"Params.txt").c_str());

  out <<"mean :  "  <<mean.getVal()  <<" +/- "<<mean.getError()<<endl;
  out <<"widt1 :  " <<widt1.getVal() <<" +/- "<<widt1.getError()<<endl;
  out <<"widt2 :  " <<widt2.getVal() <<" +/- "<<widt2.getError()<<endl;
  out <<"gfrac1 : " <<gfrac1.getVal()<<" +/- "<<gfrac1.getError()<<endl;


 float Sigma=     gfrac1.getVal() * pow(widt1.getVal(),2) + 
              (1- gfrac1.getVal()) * pow(widt2.getVal(),2);

  frame->Draw();
  
  if(print) can->Print((name+"Fit.pdf").c_str());
  if(print) can->Print((name+"Fit.png").c_str());

  return;
}
