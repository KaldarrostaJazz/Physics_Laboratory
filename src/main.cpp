#include <TCanvas.h>
#include <TGraph2D.h>
#include <TH1F.h>
#include <TMath.h>
#include <TPad.h>
#include <TPaveStats.h>
#include <TRandom.h>
#include <TStyle.h>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int main() {
  gStyle->SetPalette(1);
  gStyle->SetOptStat("neMRo");

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
  //
  // TH1::SetDefaultSumw2(kTRUE); every time TH1 object is created automatically
  // calls TH1::Sumw2();
  //
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
  phi_hist->SetLineWidth(1);
  TH1F* theta_hist = new TH1F("theta_angle", "Distribution of the polar angle",
                              1000, 0., TMath::Pi());
  theta_hist->GetXaxis()->SetTitle("Angle (rad)");
  theta_hist->GetYaxis()->SetTitle("Occurencies");
  theta_hist->SetFillColor(0);
  theta_hist->SetLineColor(kRed);
  theta_hist->SetLineWidth(1);
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
  TH1F* p_hist = new TH1F("p_hist", "Momentum Dist.", 1000, 0., 8.);
  p_hist->GetXaxis()->SetTitle("Momentum (GeV/c)");
  p_hist->GetYaxis()->SetTitle("Occurrencies");
  p_hist->SetLineColor(kBlack);
  p_hist->SetLineWidth(1);
  TH1F* trasvP_hist =
      new TH1F("trasvP_hist", "Trasversal Momentum Dist.", 1000, 0., 8.);
  trasvP_hist->GetXaxis()->SetTitle("Trasversal Momentum (GeV/c)");
  trasvP_hist->GetYaxis()->SetTitle("Occurrencies");
  trasvP_hist->SetLineColor(kBlack);
  trasvP_hist->SetLineWidth(1);

  // Histogram of particle energies
  TH1F* energy_histo =
      new TH1F("energy_histo", "Particle Energies Dist.", 1000, 0., 8.);
  energy_histo->GetXaxis()->SetTitle("Energy (GeV)");
  energy_histo->GetYaxis()->SetTitle("Occurrencies");
  energy_histo->SetLineColor(kYellow + 3);
  energy_histo->SetLineWidth(1);

  // Histogram of Invariant Masses
  TH1F* decay_inv =
      new TH1F("decay_inv", "Inv. Masses of decayment products", 1000, 0., 2.);
  decay_inv->GetXaxis()->SetTitle("Mass (Gev/c^2)");
  decay_inv->GetYaxis()->SetTitle("Occurrencies");
  decay_inv->SetLineColor(kBlue + 3);
  decay_inv->SetLineWidth(1);
  TH1F* tot_inv = new TH1F(
      "tot_inv", "Inv. Masses of total generated particles", 10000, 0., 10.);
  tot_inv->GetXaxis()->SetTitle("Mass (GeV/c^2)");
  tot_inv->GetYaxis()->SetTitle("Occurencies");
  tot_inv->SetLineColor(kRed + 3);
  tot_inv->SetLineWidth(1);
  TH1F* sameCharge_inv =
      new TH1F("sameCharge_inv", "Inv. Masses of particles with same charge",
               10000, 0., 10.);
  sameCharge_inv->GetXaxis()->SetTitle("Mass (GeV/c^2)");
  sameCharge_inv->GetYaxis()->SetTitle("Occurencies");
  sameCharge_inv->SetLineColor(kGreen + 3);
  sameCharge_inv->SetLineWidth(1);
  TH1F* diffCharge_inv = new TH1F(
      "diffCharge_inv", "Inv. Masses of particles with different charge", 10000,
      0., 10.);
  diffCharge_inv->GetXaxis()->SetTitle("Mass (GeV/c^2)");
  diffCharge_inv->GetYaxis()->SetTitle("Occurencies");
  diffCharge_inv->SetLineColor(kYellow + 3);
  diffCharge_inv->SetLineWidth(1);
  TH1F* piK_inv =
      new TH1F("Pione+/-_Kaone-/+",
               "Inv. Masses of couples Pions+/- and Kaons-/+", 10000, 0., 10.);
  piK_inv->GetXaxis()->SetTitle("Mass (GeV)");
  piK_inv->GetYaxis()->SetTitle("Occurrencies");
  piK_inv->SetLineColor(kBlue);
  TH1F* Kpi_inv =
      new TH1F("Kaone+/-_Pione+/-",
               "Inv. Masses of couples Pions+/- and Kaons+/-", 10000, 0., 10.);
  Kpi_inv->GetXaxis()->SetTitle("Mass (GeV)");
  Kpi_inv->GetYaxis()->SetTitle("Occurrencies");
  Kpi_inv->SetLineColor(kRed);

  // Loop generating the particles
  for (int i = 0; i != 1E5; ++i) {
    Particle array[130];
    int count = 0;

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
        array[count++] = particle;
        energy_histo->Fill(particle.getEnergy());
      }
      if (0.8 <= r && r < 0.9) {
        double a = Random->Rndm();
        if (a < 0.5) {
          particle.setIndex("Kaone+");
        } else {
          particle.setIndex("Kaone-");
        }
        array[count++] = particle;
        energy_histo->Fill(particle.getEnergy());
      }
      if (0.9 <= r && r < 0.99) {
        double a = Random->Rndm();
        if (a < 0.5) {
          particle.setIndex("Protone+");
        } else {
          particle.setIndex("Protone-");
        }
        array[count++] = particle;
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

        array[count++] = p1;
        array[count++] = p2;
        energy_histo->Fill(p1.getEnergy());
        energy_histo->Fill(p2.getEnergy());
        decay_inv->Fill(p1.getInvMass(p2));
      }

      p_hist->Fill(p);
      trasvP_hist->Fill(std::sqrt(px * px + py * py));
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
    for (int k = 0; k != count; ++k) {
      int k_charge = Particle::getPType(array[k].getIndex())->getCharge();
      for (int l = k + 1; l != count; ++l) {
        double invMass = array[k].getInvMass(array[l]);
        tot_inv->Fill(invMass);
        int l_charge = Particle::getPType(array[l].getIndex())->getCharge();
        if (k_charge == l_charge) {
          sameCharge_inv->Fill(invMass);
        } else if (k_charge != l_charge) {
          diffCharge_inv->Fill(invMass);
        }
        if ((array[k].getIndex() == 0 && array[l].getIndex() == 5) ||
            (array[k].getIndex() == 1 && array[l].getIndex() == 4)) {
          piK_inv->Fill(invMass);
        }
        if ((array[k].getIndex() == 0 && array[l].getIndex() == 4) ||
            (array[k].getIndex() == 1 && array[l].getIndex() == 5)) {
          Kpi_inv->Fill(invMass);
        }
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

  TCanvas* invMass_canva = new TCanvas("invMass_canva");
  invMass_canva->SetWindowSize(1000, 1000);
  invMass_canva->Divide(2, 2);
  invMass_canva->cd(1);
  tot_inv->Draw();
  invMass_canva->cd(2);
  decay_inv->Draw();
  invMass_canva->cd(3);
  sameCharge_inv->Draw();
  invMass_canva->cd(4);
  diffCharge_inv->Draw();

  TCanvas* couples_canva = new TCanvas("couples_canva");
  couples_canva->SetWindowSize(1200, 600);
  couples_canva->Divide(2, 1);
  couples_canva->cd(1);
  piK_inv->Draw();
  couples_canva->cd(2);
  Kpi_inv->Draw();

  // Printing pdfs
  types_canva->Print("../pdfs/types_canva.pdf");
  angles_canva->Print("../pdfs/angles_canva.pdf");
  p_canva->Print("../pdfs/p_canva.pdf");
  energy_canva->Print("../pdfs/energy_canva.pdf");
  invMass_canva->Print("../pdfs/invMass_canva.pdf");
  couples_canva->Print("../pdfs/couples_canva.pdf");

  // Printing canvas on .root files
  types_canva->Print("../rootfiles/types_canva.root");
  angles_canva->Print("../rootfiles/angles_canva.root");
  p_canva->Print("../rootfiles/p_canva.root");
  energy_canva->Print("../rootfiles/energy_canva.root");
  invMass_canva->Print("../rootfiles/invMass_canva.root");
  couples_canva->Print("../rootfiles/couples_canva.root");

  return 0;
}
