void photonInvariantMass() {
    // Open the ROOT file containing the data
    TFile *file = TFile::Open("test.root");
    
    // Access the TTree named "output" from the file
    TTree *tree = (TTree*)file->Get("output");

    // Create a histogram to store the invariant mass of the two photons
    TH1F *h_pt = new TH1F("h_pt", "Transverse Momentum of Two Photons", 100, 0, 500);

    TH1F *m_met1 = new TH1F("m_met1", "m_met Distribution", 20, 0, 3);

    TH1F *third_h_pt = new TH1F("third_h_pt","Third Photon Transverse Momentum", 100, 0, 250);
    // Declare variables to hold the values from the tree branches
    Float_t ph_pt1, ph_eta1, ph_phi1;
    Float_t ph_pt2, ph_eta2, ph_phi2;
    
    Float_t ph_pt3, ph_eta3, ph_phi3;
    Float_t m_met;

    // 1.  Draw a distribution of the transverse momentum of the diphoton system
    // 2.  Draw the distribution of m_met
    // 3. Draw the pT distribution of the third photon ph_*3
    
    // Link the above variables to the branches in the tree


    tree->SetBranchAddress("ph_pt1", &ph_pt1);
    tree->SetBranchAddress("ph_eta1", &ph_eta1);
    tree->SetBranchAddress("ph_phi1", &ph_phi1);
    tree->SetBranchAddress("ph_pt2", &ph_pt2);
    tree->SetBranchAddress("ph_eta2", &ph_eta2);
    tree->SetBranchAddress("ph_phi2", &ph_phi2);
    tree->SetBranchAddress("m_met", &m_met);
    tree->SetBranchAddress("ph_pt3", &ph_pt3);
    // Get the number of entries (events) in the tree
    Long64_t nentries = tree->GetEntries();

    // Loop over each event in the tree
    for (Long64_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);  // Load the data for the current event

        // Create Lorentz vectors to store the 4-momenta of the photons
        TLorentzVector photon1, photon2;

        // Set the 4-momenta for each photon (using SetPtEtaPhiM method as we have pT, eta, and phi)
        photon1.SetPtEtaPhiM(ph_pt1, ph_eta1, ph_phi1, 0);  // Photons are massless, so m = 0
        photon2.SetPtEtaPhiM(ph_pt2, ph_eta2, ph_phi2, 0);

	// pT of photons needs to be greater than 30 GeV

	if(photon1.Pt() < 30 || photon2.Pt() < 30)
	  continue;
        // Calculate the invariant mass of the two photons
       // float mgg = (photon1 + photon2).M();
        float pt  = (photon1 + photon2).Pt();

	//        cout << mgg << endl;
        // Fill the histogram with the calculated invariant mass
       // h_mgg->Fill(mgg);
	h_pt ->Fill(pt);
	m_met1 ->Fill(m_met);
        third_h_pt ->Fill(ph_pt3);
    }

    // Create a canvas to draw the histogram
    TCanvas *c = new TCanvas("c", "Photon Transverse Momentum", 800, 600);
    TCanvas *c1 = new TCanvas("c1", "m_met", 800, 600);
    TCanvas *c2 = new TCanvas("c2", "Third Photon Transverse Momentum", 800, 600);
    // Draw the histogram on the canvas
    h_pt->Draw();
    m_met1->Draw();
    third_h_pt ->Draw();
    // Save the canvas as an image
    c->SaveAs("PhotoTransverseMomentum.png");
    c1->SaveAs("m_metDistribution.png");
    c2->SaveAs("ThirdPhotonTransverseMomentum.png");
 // Close the file
    file->Close();
}
