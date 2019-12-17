void TH1toTxt (TH1F *h, string outfile) {
	ofstream out (outfile);
	int n=h->GetNbinsX();
	for (int i=0; i<n; i++) out<<h->GetBinCenter(i)<<"\t"<<h->GetBinContent(i)<<endl;
	cout<<"converted TH1 "<<h->GetName()<<endl;
}
