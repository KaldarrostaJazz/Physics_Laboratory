#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  // Style
  gStyle->SetOptStat("neMR");
  gStyle->SetOptFit(1111);

  // Reading .root file and getting histos
  TFile* file = new TFile("../rootfiles/data.root");

  TH1F* types = (TH1F*)file->Get("Particle_types");
  TH1F* phi_hist = (TH1F*)file->Get("phi_angle");
  TH1F* theta_hist = (TH1F*)file->Get("theta_angle");
  TH1F* p_hist = (TH1F*)file->Get("p_hist");
  TH1F* trasvP_hist = (TH1F*)file->Get("trasvP_hist");
  TH1F* energy_histo = (TH1F*)file->Get("energy_histo");
  TH1F* tot_inv = (TH1F*)file->Get("tot_inv");
  TH1F* decay_inv = (TH1F*)file->Get("decay_inv");
  TH1F* sameCharge_inv = (TH1F*)file->Get("sameCharge_inv");
  TH1F* diffCharge_inv = (TH1F*)file->Get("diffCharge_inv");
  TH1F* piK_inv = (TH1F*)file->Get("Pione+/-_Kaone-/+");
  TH1F* Kpi_inv = (TH1F*)file->Get("Kaone+/-_Pione+/-");

  std::cout << std::endl;

  // Printing histos properties

  types->Print();
  phi_hist->Print();
  theta_hist->Print();
  p_hist->Print();
  trasvP_hist->Print();
  energy_histo->Print();
  tot_inv->Print();
  decay_inv->Print();
  sameCharge_inv->Print();
  diffCharge_inv->Print();
  // piK_inv->Print();
  // Kpi_inv->Print();

  std::cout << std::endl;

  // Particle types generation
  std::cout << std::setw(60)
            << "Checking concretness of particles generation...\n\n";
  std::cout << std::setw(20) << "Particle type" << std::setw(20)
            << "Particles generated" << std::setw(20) << "Particles expected\n";
  std::cout << std::setw(17) << types->GetXaxis()->GetBinLabel(1)
            << std::setw(20) << types->GetBinContent(1) << std::setw(10)
            << types->GetEntries() * 0.4 << " +/- "
            << std::sqrt(types->GetEntries() * 0.4) << std::endl;
  std::cout << std::setw(17) << types->GetXaxis()->GetBinLabel(2)
            << std::setw(20) << types->GetBinContent(2) << std::setw(10)
            << types->GetEntries() * 0.4 << " +/- "
            << std::sqrt(types->GetEntries() * 0.4) << std::endl;
  std::cout << std::setw(17) << types->GetXaxis()->GetBinLabel(3)
            << std::setw(20) << types->GetBinContent(3) << std::setw(10)
            << types->GetEntries() * 0.045 << " +/- "
            << std::sqrt(types->GetEntries() * 0.045) << std::endl;
  std::cout << std::setw(17) << types->GetXaxis()->GetBinLabel(4)
            << std::setw(20) << types->GetBinContent(4) << std::setw(10)
            << types->GetEntries() * 0.045 << " +/- "
            << std::sqrt(types->GetEntries() * 0.045) << std::endl;
  std::cout << std::setw(17) << types->GetXaxis()->GetBinLabel(5)
            << std::setw(20) << types->GetBinContent(5) << std::setw(10)
            << types->GetEntries() * 0.05 << " +/- "
            << std::sqrt(types->GetEntries() * 0.05) << std::endl;
  std::cout << std::setw(17) << types->GetXaxis()->GetBinLabel(6)
            << std::setw(20) << types->GetBinContent(6) << std::setw(10)
            << types->GetEntries() * 0.05 << " +/- "
            << std::sqrt(types->GetEntries() * 0.05) << std::endl;
  std::cout << std::setw(17) << types->GetXaxis()->GetBinLabel(7)
            << std::setw(20) << types->GetBinContent(7) << std::setw(10)
            << types->GetEntries() * 0.01 << " +/- "
            << std::sqrt(types->GetEntries() * 0.01) << std::endl;

  std::cout << std::endl;

  // Fittings
  std::cout << std::setfill('-') << std::setw(80) << std::setfill(' ') << std::endl;
  std::cout << std::setw(60) << "FITTING HISTOGRAMS AND CHECKING MOTECARLO GEN.\n";

  phi_hist->Fit("pol0");
  TF1* f_phi = phi_hist->GetFunction("pol0");
  f_phi->SetLineColor(kBlack);

  std::cout << std::endl;

  theta_hist->Fit("pol0");
  TF1* f_theta = theta_hist->GetFunction("pol0");
  f_theta->SetLineColor(kBlack);

  std::cout << std::endl;

  p_hist->Fit("expo");
  TF1* f_mom = p_hist->GetFunction("expo");
  f_mom->SetLineColor(kRed+1);

  // Operations with histos
  TH1F* diff_same = new TH1F("diff_same", "Different charge minus same charge", 10000, 0., 10.);
  diff_same->Add(diffCharge_inv, sameCharge_inv, 1, -1);
  diff_same->SetLineColor(kAzure+1);
  diff_same->SetAxisRange(0.2, 2., "X");
  diff_same->Fit("gaus", "", "", 0.6, 1.2);
  TF1* fitFunc = diff_same->GetFunction("gaus");
  // fitFunc->SetRange(0.2, 2.);
  fitFunc->SetLineColor(kRed);

  // Drawing histos and fittings
  TCanvas* canva1 = new TCanvas("canva1");
  canva1->Divide(1,2);
  canva1->cd(1);
  phi_hist->Draw();
  f_phi->Draw("SAME");
  canva1->cd(2);
  theta_hist->Draw();
  f_theta->Draw("SAME");

  TCanvas* canva2 = new TCanvas("canva2");
  p_hist->Draw();
  f_mom->Draw("SAME");

  TCanvas* canva3 = new TCanvas("canva3");
  diff_same->Draw("HIST SAME C");
  fitFunc->Draw("SAME");

  // Printing canvas
  canva1->Print("canva1.pdf");
  canva2->Print("canva2.pdf");
  canva3->Print("canva3.pdf");

  canva1->Print("canva1.root");
  canva2->Print("canva2.root");
  canva3->Print("canva3.root");
}
