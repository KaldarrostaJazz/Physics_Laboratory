#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

// #include "TH1F.h"
// #include "TGraph.h"
// #include "TMath.h"
// #include "TRandom.h"
// #include "TCanvas.h"
// #include "TStyle.h"
// #include "TPad.h"

int main() {
  gStyle->SetPalette(1);
  gStyle->SetOptStat("neMR");

  TRandom* Random = new TRandom();
  Random->SetSeed();

  // Adding the particle types
  Particle::addType("Pione+", 0.13957, 1);
  Particle::addType("Pione-", 0.13957, -1);
  Particle::addType("Protone+", 0.93827, 1);
  Particle::addType("Protone-", 0.93827, -1);
  Particle::addType("Kaone+", 0.49367, 1);
  Particle::addType("Kaone-", 0.49367, -1);
  Particle::addType("Kaone*", 0.89166, 0, 0.050);

  // Histogram of the generated particles
  TH1F* types = new TH1F("Particle_types", "Generated Particles", 7, -0.5, 6.5);
  types->GetXaxis()->SetTitle("Particles");
  types->GetYaxis()->SetTitle("Occurencies");
  types->GetXaxis()->SetBinLabel(1, "Pione+");
  types->GetXaxis()->SetBinLabel(2, "Pione-");
  types->GetXaxis()->SetBinLabel(3, "Protone+");
  types->GetXaxis()->SetBinLabel(4, "Protone-");
  types->GetXaxis()->SetBinLabel(5, "Kaone+");
  types->GetXaxis()->SetBinLabel(6, "Kaone-");
  types->GetXaxis()->SetBinLabel(7, "Kaone*");
  types->SetFillColor(kAzure + 2);
  types->SetLineColor(kBlue);
  types->SetLineWidth(2);

  // Histograms and graph of momentum directions (theta and phi angle)
  TH1F* phi_hist = new TH1F("phi_angle", "Distribution of the azimutal angle",
                            1000, 0., 2. * TMath::Pi());
  phi_hist->GetXaxis()->SetTitle("Angle (rad)");
  phi_hist->GetYaxis()->SetTitle("Occurencies");
  phi_hist->SetFillColor(0);
  phi_hist->SetLineColor(kBlue);
  phi_hist->SetLineWidth(2);
  TH1F* theta_hist = new TH1F("theta_angle", "Distribution of the polar angle",
                              1000, 0., TMath::Pi());
  theta_hist->GetXaxis()->SetTitle("Angle (rad)");
  theta_hist->GetYaxis()->SetTitle("Occurencies");
  theta_hist->SetFillColor(0);
  theta_hist->SetLineColor(kRed);
  theta_hist->SetLineWidth(2);
  TGraph2D* angles_graph = new TGraph2D(1E5);
  angles_graph->SetTitle(
      "Polar angles generation graph; X coordinate; Y coordinate; Z "
      "coordinate");
  angles_graph->GetXaxis()->SetTitleOffset(2.);
  angles_graph->GetYaxis()->SetTitleOffset(2.);
  angles_graph->GetZaxis()->SetTitleOffset(2.);
  angles_graph->SetMarkerStyle(kOpenCircle);
  int point_count{0};

  // Histogram of momentum and trasversal momentum values
  TH1F* p_hist = new TH1F("p_hist", "Momentum Dist.", 1000, 0., 7.5);
  p_hist->GetXaxis()->SetTitle("Momentum (GeV/c)");
  p_hist->GetYaxis()->SetTitle("Occurrencies");
  p_hist->SetLineColor(kBlack);
  p_hist->SetLineWidth(2);
  TH1F* trasvP_hist =
      new TH1F("trasvP_hist", "Trasversal Momentum Dist.", 1000, 0., 5);
  trasvP_hist->GetXaxis()->SetTitle("Trasversal Momentum (GeV/c)");
  trasvP_hist->GetYaxis()->SetTitle("Occurrencies");
  trasvP_hist->SetLineColor(kBlack);
  trasvP_hist->SetLineWidth(2);

  // Histogram of particle energies
  TH1F* energy_histo =
      new TH1F("energy_histo", "Particle Energies Dist.", 1000, 0., 5.);
  energy_histo->GetXaxis()->SetTitle("Energy (GeV)");
  energy_histo->GetYaxis()->SetTitle("Occurrencies");
  // energy_histo->SetLineColor(kYellow + 5);
  // energy_histo->SetLineWidth(2);

  // Loop generating the particles
  for (int i = 0; i != 1E5; ++i) {
    for (int j = 0; j != 100; ++j) {
      Particle particle;

      double phi = Random->Uniform(0., 2. * TMath::Pi());
      double theta = Random->Uniform(0., TMath::Pi());
      double p = Random->Exp(1.);
      double px = p * std::sin(theta) * std::cos(phi);
      double py = p * std::sin(theta) * std::sin(phi);
      double pz = p * std::cos(theta);
      particle.setP(px, py, pz);

      double r = Random->Rndm();
      if (r < 0.8) {
        double a = Random->Rndm();
        if (a < 0.5) {
          particle.setIndex("Pione+");
        } else {
          particle.setIndex("Pione-");
        }
        p_hist->Fill(p);
        trasvP_hist->Fill(std::sqrt(px * px + py * py));
        energy_histo->Fill(particle.getEnergy());
      }
      if (0.8 <= r && r < 0.9) {
        double a = Random->Rndm();
        if (a < 0.5) {
          particle.setIndex("Kaone+");
        } else {
          particle.setIndex("Kaone-");
        }
        p_hist->Fill(p);
        trasvP_hist->Fill(std::sqrt(px * px + py * py));
        energy_histo->Fill(particle.getEnergy());
      }
      if (0.9 <= r && r < 0.99) {
        double a = Random->Rndm();
        if (a < 0.5) {
          particle.setIndex("Protone+");
        } else {
          particle.setIndex("Protone-");
        }
        p_hist->Fill(p);
        trasvP_hist->Fill(std::sqrt(px * px + py * py));
        energy_histo->Fill(particle.getEnergy());
      }
      if (0.99 <= r && r < 1) {
        particle.setIndex("Kaone*");
        Particle p1;
        Particle p2;
        double a = Random->Rndm();
        if (a < 0.5) {
          p1.setIndex("Pione+");
          p2.setIndex("Kaone-");
          particle.decayTo(p1, p2);
        } else {
          p1.setIndex("Pione-");
          p2.setIndex("Kaone+");
          particle.decayTo(p1, p2);
        }
        p_hist->Fill(p1.getP());
        p_hist->Fill(p2.getP());
        trasvP_hist->Fill(
            std::sqrt(p1.getPx() * p1.getPx() + p1.getPy() * p1.getPy()));
        trasvP_hist->Fill(
            std::sqrt(p2.getPx() * p2.getPx() + p2.getPy() * p2.getPy()));
        energy_histo->Fill(p1.getEnergy());
        energy_histo->Fill(p2.getEnergy());
      }

      types->Fill(particle.getIndex());
      phi_hist->Fill(phi);
      theta_hist->Fill(theta);

      if (point_count < 1E5) {
        double x = std::sin(theta) * std::cos(phi);
        double y = std::sin(theta) * std::sin(phi);
        double z = std::cos(theta);
        angles_graph->SetPoint(point_count++, x, y, z);
      }
    }
  }

  // Plotting on canvas
  TCanvas* types_canva = new TCanvas("types_canva");
  types_canva->SetTitle("Particelle Generate");
  types->Draw();
  gPad->Update();
  TPaveStats* st = (TPaveStats*)types->FindObject("stats");
  st->SetOptStat(11);

  TCanvas* angles_canva = new TCanvas("angles_canva");
  angles_canva->SetWindowSize(1200, 900);
  angles_canva->SetTitle("Angoli Generati");
  angles_canva->Divide(2, 1);
  angles_canva->cd(1)->Divide(1, 2);
  angles_canva->cd(1)->cd(1);
  phi_hist->Draw();
  angles_canva->cd(1)->cd(2);
  theta_hist->Draw();
  angles_canva->cd(2);
  angles_graph->Draw("PCOL");

  TCanvas* p_canva = new TCanvas("p_canvas");
  p_canva->SetWindowSize(1200, 900);
  p_canva->SetTitle("Momentum Dist.");
  p_canva->Divide(1, 2);
  p_canva->cd(1);
  p_hist->Draw("C");
  p_canva->cd(2);
  trasvP_hist->Draw("C");

  TCanvas* energy_canva = new TCanvas("energy_canva");
  energy_canva->SetTitle("Energis Dist.");
  energy_histo->Draw("C");

  // Printing pdfs
  types_canva->Print("types_canva.pdf");
  angles_canva->Print("angles_canva.pdf");
  p_canva->Print("p_canva.pdf");
  energy_canva->Print("energy_canva.pdf");

  return 0;
}
