void TH1toTxt (TH1F *h, string outfile) {
	ofstream out (outfile);
	int n=h->GetNbinsX();
	for (int i=0; i<n; i++) out<<h->GetBinCenter(i)<<"\t"<<h->GetBinContent(i)<<"\t0.0\t"
				   <<h->GetBinError(i)<<endl;
}
