Double_t fitf(Double_t x,Double_t *par) 
{ 
	Double_t arg = 0; 
	if (par[2] != 0) arg = (x - par[1])/par[2]; 
	Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg); 
	return fitval; 
}

void graph_sub_gaus(char name[])
{
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	c1->SetGrid();
	
	std::vector<double> xv;
	std::vector<double> yv;
		
	Double_t x, y;
	FILE *f = fopen(name,"r");
	xv.clear();
	yv.clear();
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf\n", &x, &y);
		xv.push_back(x);
		yv.push_back(y);
	}
			
	//TGraph * gr = new TGraph(xv.size(), &xv[0], &yv[0]);
	//gr->SetMarkerColor(4);
	//gr->SetMarkerStyle(kFullCircle);
	//gr->Draw("AP");	
	
	double par[3] = {6675.1, -0.215767, 12.6479};
	
	for(int i=0; i<xv.size(); i++)
	{
		yv[i] -= fitf(xv[i], par); 
	}
	
	TGraph * gr2 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr2->SetMarkerColor(5);
	gr2->SetMarkerStyle(kFullCircle);
	gr2->Draw();	
		
	c1->Update();
}