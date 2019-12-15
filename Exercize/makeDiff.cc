void makeDiff () {
	TH1F *a[6]={DiffMCTrack2d, DiffMCAngle2d, DiffMCAllNoBs, DiffMCAllTrk, DiffMCRCNoBs, DiffMCRCOnly};
	int n=a[0]->GetNbinsX();
	ofstream out ("MCDiff.txt");
	for (int i=0; i<n; i++) {
		out<<a[0]->GetBinCenter(i)<<"\t";
		for (int j=0; j<6; j++) {
			out<<a[j]->GetBinCenter(i)<<"\t"<<a[j]->GetBinContent(i)<<"\t0.0\t"
				   <<a[j]->GetBinError(i)<<"\t";
		}
	out<<endl;
	}
}

/*
void TH1toTxt (TH1F *h, string outfile) {
	ofstream out (outfile);
	int n=h->GetNbinsX();
	for (int i=0; i<n; i++) out<<h->GetBinCenter(i)<<"\t"<<h->GetBinContent(i)<<"\t0.0\t"
				   <<h->GetBinError(i)<<endl;
}

*/
