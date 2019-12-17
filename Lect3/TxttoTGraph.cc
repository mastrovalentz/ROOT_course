void TxttoTGraph (string name) {
	TGraph * gr= new TGraph((name+".txt").c_str());
	TCanvas *c= new TCanvas("c", "c", 600, 600);
	c->cd();
	gr->Draw();
	c->Draw();
	c->Print((name+".png").c_str());
	cout<<"converted file "<<name<<endl;
}

//to execute in batch
//root -l -b 'TxttoTGraph.cc ("hAllout"); exit (0)'
