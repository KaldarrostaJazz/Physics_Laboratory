#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TPad.h>

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  //
  // Style
  //
  gStyle->SetOptStat("neMR");
  gStyle->SetOptFit(1111);

  //
  // Reading .root file and getting histos
  //
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
  TH1F* piK_inv = (TH1F*)file->Get("Pione_Kaone_diff");
  TH1F* Kpi_inv = (TH1F*)file->Get("Kaone_Pione_same");

  std::cout << std::endl;

  //
  // Printing histos properties
  //

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
  piK_inv->Print();
  Kpi_inv->Print();

  std::cout << std::endl;

  //
  // Particle types generation
  //
  std::cout << std::setw(60)
            << "Checking concretness of particles generation...\n\n";

  std::cout << std::setw(22) << "|Particle type|" << std::setw(21)
            << "Particles generated|" << std::setw(21)
            << "Particles expected|\n";

  std::cout << std::setw(8) << '|' << std::setw(13) << std::left
            << types->GetXaxis()->GetBinLabel(1) << '|' << std::setw(20)
            << std::left << types->GetBinContent(1) << '|' << std::setw(8)
            << std::left << types->GetEntries() * 0.4 << " +/- " << std::setw(7)
            << std::left << std::sqrt(types->GetEntries() * 0.4) << '|'
            << std::endl;

  std::cout << std::setw(8) << std::right << '|' << std::setw(13) << std::left
            << types->GetXaxis()->GetBinLabel(2) << '|' << std::setw(20)
            << std::left << types->GetBinContent(2) << '|' << std::setw(8)
            << std::left << types->GetEntries() * 0.4 << " +/- " << std::setw(7)
            << std::left << std::sqrt(types->GetEntries() * 0.4) << '|'
            << std::endl;

  std::cout << std::setw(8) << std::right << '|' << std::setw(13) << std::left
            << types->GetXaxis()->GetBinLabel(3) << '|' << std::setw(20)
            << std::left << types->GetBinContent(3) << '|' << std::setw(8)
            << std::left << types->GetEntries() * 0.045 << " +/- "
            << std::setw(7) << std::left
            << std::sqrt(types->GetEntries() * 0.045) << '|' << std::endl;

  std::cout << std::setw(8) << std::right << '|' << std::setw(13) << std::left
            << types->GetXaxis()->GetBinLabel(4) << '|' << std::setw(20)
            << std::left << types->GetBinContent(4) << '|' << std::setw(8)
            << std::left << types->GetEntries() * 0.045 << " +/- "
            << std::setw(7) << std::left
            << std::sqrt(types->GetEntries() * 0.045) << '|' << std::endl;

  std::cout << std::setw(8) << std::right << '|' << std::setw(13) << std::left
            << types->GetXaxis()->GetBinLabel(5) << '|' << std::setw(20)
            << std::left << types->GetBinContent(5) << '|' << std::setw(8)
            << std::left << types->GetEntries() * 0.05 << " +/- "
            << std::setw(7) << std::left
            << std::sqrt(types->GetEntries() * 0.05) << '|' << std::endl;

  std::cout << std::setw(8) << std::right << '|' << std::setw(13) << std::left
            << types->GetXaxis()->GetBinLabel(6) << '|' << std::setw(20)
            << std::left << types->GetBinContent(6) << '|' << std::setw(8)
            << std::left << types->GetEntries() * 0.05 << " +/- "
            << std::setw(7) << std::left
            << std::sqrt(types->GetEntries() * 0.05) << '|' << std::endl;

  std::cout << std::setw(8) << std::right << '|' << std::setw(13) << std::left
            << types->GetXaxis()->GetBinLabel(7) << '|' << std::setw(20)
            << std::left << types->GetBinContent(7) << '|' << std::setw(8)
            << std::left << types->GetEntries() * 0.01 << " +/- "
            << std::setw(7) << std::left
            << std::sqrt(types->GetEntries() * 0.01) << '|' << std::endl;

  std::cout << std::endl;

  //
  // Operations on histos and fittings
  //
  std::cout << std::setfill('-') << std::setw(60) << std::right
            << "FITTING HISTOGRAMS AND CHECKING MONTECARLO GEN."
            << std::setw(30) << '\n';

  // Canva 1: Angles
  TCanvas* canva1 = new TCanvas("canva1", "Angles");
  canva1->Divide(1, 2);

  canva1->cd(1);
  phi_hist->Fit("pol0");
  TF1* f_phi = phi_hist->GetFunction("pol0");
  f_phi->SetLineColor(kBlack);
  phi_hist->Draw();
  f_phi->Draw("SAME");

  std::cout << std::endl;

  canva1->cd(2);
  theta_hist->Fit("pol0");
  TF1* f_theta = theta_hist->GetFunction("pol0");
  f_theta->SetLineColor(kBlack);
  theta_hist->Draw();
  f_theta->Draw("SAME");

  std::cout << std::endl;

  // Canva 2: Momentum
  TCanvas* canva2 = new TCanvas("canva2", "Momentum");
  p_hist->Fit("expo");
  TF1* f_mom = p_hist->GetFunction("expo");
  f_mom->SetLineColor(kRed);
  p_hist->SetFillColor(kGreen + 1);
  p_hist->Draw();
  f_mom->Draw("SAME");

  //
  // Operations with histos
  //
  TH1F* diff_same = new TH1F("diff_same", "Different charge minus same charge",
                             10000, 0., 10.);
  diff_same->Add(diffCharge_inv, sameCharge_inv, 1, -1);
  diff_same->SetLineColor(kAzure + 1);

  TF1* zero = new TF1("zero", "0", 0., 10.);
  zero->SetLineColor(kGreen + 2);
  zero->SetLineStyle(9);
  zero->SetLineWidth(2);

  TH1F* pion_kaon = new TH1F("pion_kaon", "Pions and Kaons", 10000, 0., 10.);
  pion_kaon->Add(piK_inv, Kpi_inv, 1, -1);
  pion_kaon->SetLineColor(kAzure + 1);
  pion_kaon->SetAxisRange(0.2, 2., "X");

  TCanvas* canva3 = new TCanvas("canva3", "All particles");
  diff_same->Fit("gaus", "", "", 0.6, 1.2);
  TF1* func = diff_same->GetFunction("gaus");
  func->SetLineColor(kRed);
  diff_same->Draw("HIST");
  func->Draw("SAME");
  zero->Draw("SAME");
  gPad->Update();
  TPaveStats* st = (TPaveStats*)diff_same->FindObject("stats");
  st->SetY1NDC(0.6);

  TCanvas* canva4 = new TCanvas("canva4", "All particles");
  TH1F* diff_same_ranged = new TH1F(*diff_same);
  diff_same_ranged->SetAxisRange(0.7, 1.1, "X");
  diff_same_ranged->SetAxisRange(-100, 2000, "Y");
  diff_same_ranged->Fit("gaus", "", "", 0.6, 1.2);
  TF1* fitFunc = diff_same_ranged->GetFunction("gaus");
  fitFunc->SetLineColor(kRed);
  diff_same_ranged->Draw("HIST");
  fitFunc->Draw("SAME");
  zero->Draw("SAME");

  std::cout << std::endl;

  TCanvas* canva5 = new TCanvas("canva5", "Pions and Kaons");
  pion_kaon->Fit("gaus", "", "", 0.6, 1.4);
  TF1* funky = pion_kaon->GetFunction("gaus");
  funky->SetLineColor(kRed);
  pion_kaon->Draw();
  funky->Draw("SAME");
  zero->Draw("SAME");

  std::cout << std::endl;

  TCanvas* canva6 = new TCanvas("canva6", "Pions and Kaons");
  TH1F* pion_kaon_ranged = new TH1F(*pion_kaon);
  pion_kaon_ranged->SetAxisRange(0.6, 1.4, "X");
  pion_kaon_ranged->SetAxisRange(-200, 1500, "Y");
  pion_kaon_ranged->SetLineColor(kAzure + 1);
  pion_kaon_ranged->Fit("gaus", "", "", 0.6, 1.4);
  TF1* fitFunky = pion_kaon_ranged->GetFunction("gaus");
  fitFunky->SetLineColor(kRed);
  pion_kaon_ranged->Draw();
  fitFunky->Draw("SAME");
  zero->Draw("SAME");

  //
  // Printing canvas
  //
  canva1->Print("analysis_pdfs/angles_fit.pdf");
  canva2->Print("analysis_pdfs/momentum_fit.pdf");
  canva3->Print("analysis_pdfs/all_fit.pdf");
  canva4->Print("analysis_pdfs/all_particular.pdf");
  canva5->Print("analysis_pdfs/pk_fit.pdf");
  canva6->Print("analysis_pdfs/pk_particular.pdf");

  /*
  canva1->Print("canva1.root");
  canva2->Print("canva2.root");
  canva3->Print("canva3.root");
  canva4->Print("canva4.root");
  canva5->Print("canva5.root");
  canva6->Print("canva6.root");
  */
}
