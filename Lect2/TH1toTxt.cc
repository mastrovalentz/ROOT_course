void TH1toTxt (TH1F *h, string outfile) {
	ofstream out (outfile);
	n=h->GetNbinsX();
	for (int i=0; i<n; i++) out<<h->GetBinCenter(i)<<"\t"<<h->GetBinCenter(i)<<endl;
}
