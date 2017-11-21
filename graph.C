std::vector<double> xv(10000000);
std::vector<double> yv(10000000);
std::vector<double> zv;

double with=6.25E-10;

//double fit_interval_left=-4.5E-7;
double fit_interval_left=-3E-7;
double fit_interval_right=5E-8;

TH1F *h1 = new TH1F;
TH1F *h2 = new TH1F;
TH1F *h3 = new TH1F;
TH1F *h4 = new TH1F;
TH1F *h5 = new TH1F;
TH1F *h_temp = new TH1F;

TF1 *fit_temp = new TF1;

Double_t fit_gaus(Double_t *x,Double_t *par) 
{ 
	Double_t arg = 0; 
	if (par[2] != 0) arg = (x[0] - par[1])/par[2]; 
	Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg); 
	return fitval; 
}


void canvas()
{
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	c1->SetGrid();
}

void h1_Draw()
{
	h1->SetFillColor(kRed);
	h1->SetFillStyle(3002);
	h1->Draw();
}

void h2_Draw()
{
	h2->SetFillColor(kGreen);
	h2->SetFillStyle(3002);
	h2->Draw("same");
}

void h3_Draw()
{
	h3->SetFillColor(kBlue);
	h3->SetFillStyle(3002);
	h3->Draw("same");
}

void h4_Draw()
{
	h4->SetFillColor(kMagenta);
	h4->SetFillStyle(3002);
	h4->Draw("same");
}

void h5_Draw()
{
	h5->SetFillColor(kOrange);
	h5->SetFillStyle(3002);
	h5->Draw("same");
}

void hist_fill_Xy(TH1F &histogram, char name[])
{
	FILE *f = fopen(name,"r");
	Double_t x, y;
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf\n", &x, &y);
		histogram.Fill(x);
	}
}

void hist_fill_xY(TH1F &histogram, char name[])
{
	FILE *f = fopen(name,"r");
	Double_t x, y;
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf\n", &x, &y);
		histogram.Fill(y);
	}
}

void hist_fill(TH1F &histogram, char name[])
{
	FILE *f = fopen(name,"r");
	Double_t x;
	while (!feof(f))
	{ 
		fscanf(f,"%lf\n",&x);
		histogram.Fill(x);
	}
}

void read(char name[])
{
	xv.clear();
	yv.clear();
	FILE *f = fopen(name,"r");
	Double_t x,y;
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf\n",&x,&y);
		xv.push_back(x);
		yv.push_back(y);
   }
   fclose(f);
}

void read_3(char name[])
{
	xv.clear();
	yv.clear();
	zv.clear();
	FILE *f = fopen(name,"r");
	Double_t x,y,z;
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf %lf\n",&x,&y,&z);
		xv.push_back(x);
		yv.push_back(y);
		zv.push_back(z);
   }
   fclose(f);
}

void read_3(char name[], int number_of_point)
{
	xv.clear();
	yv.clear();
	zv.clear();
	FILE *f = fopen(name,"r");
	Double_t x,y,z;
	for (int i=0; i<number_of_point; i++)
	{ 
		fscanf(f,"%lf %lf %lf\n",&x,&y,&z);
		xv.push_back(x);
		yv.push_back(y);
		zv.push_back(z);
   }
   fclose(f);
}

void read(char name[], int number_of_point)
{
	xv.clear();
	yv.clear();
	FILE *f = fopen(name,"r");
	Double_t x,y;
	for (int i=0; i<number_of_point; i++)
	{ 
		fscanf(f,"%lf %lf \n",&x,&y);
		xv.push_back(x);
		yv.push_back(y);
   }
   fclose(f);
}

void read_der(char name[], int number_of_point)
{
	xv.clear();
	yv.clear();
	FILE *f = fopen(name,"r");
	Double_t x,y;
	double y_old=0;
	
	for (int i=0; i<number_of_point; i++)
	{ 
		fscanf(f,"%lf %lf \n", &x, &y);
		xv.push_back(x);
		yv.push_back(y - y_old);
		y_old=y;
   }
   
   fclose(f);
}

void read3_der(char name[], int number_of_point)
{
	xv.clear();
	yv.clear();
	zv.clear();
	FILE *f = fopen(name,"r");
	Double_t x,y,z;
	double z_old=0;
	for (int i=0; i<number_of_point; i++)
	{ 
		fscanf(f,"%lf %lf %lf\n",&x,&y,&z);
		xv.push_back(x);
		yv.push_back(y);
		zv.push_back(z - z_old);
		z_old=z;
   }
   fclose(f);
   
   
   
}


void graph_xyz_xy(char name[], int number_of_point)
 {
	canvas();
	read_3(name, number_of_point);
	TGraph * gr = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(kFullCircle);
	gr->Draw("AP");
	c1->Update();

}

void graph_xyz_xz(char name[], int number_of_point)
 {
	canvas();
	
	read_3(name, number_of_point);
	TGraph * gr = new TGraph(xv.size(), &xv[0], &zv[0]);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(kFullCircle);
	gr->Draw("AP");
	c1->Update();

}

void graph_xyz(char name[], int number_of_point)
 {
	canvas();
	read_3(name, number_of_point);
	
	TGraph * gr1 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(kFullCircle);
	gr1->Draw("AP");
	
	TGraph * gr2 = new TGraph(xv.size(), &xv[0], &zv[0]);
	gr2->SetMarkerColor(kRed);
	gr2->Draw("*");
	

	c1->Update();
}

void graph_error(char name[])
{
	canvas();
	read_3(name);
	
	TGraphErrors *gr = new TGraphErrors(xv.size(), &xv[0], &yv[0], 0, &zv[0]);
	gr->SetLineColor(kRed);
	gr->SetMarkerStyle(kFullCircle);
	gr->Draw("AP");
	c1->Update();
}

void graph_error(char name1[], char name2[])
 {
	canvas();
	
	read_3(name1);
	TGraphErrors *gr = new TGraphErrors(xv.size(), &xv[0], &yv[0], 0, &zv[0]);
	//gr->SetLineColor(kRed);
	//gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(kFullCircle);
	//gr->SetTitle("spectrum");
	//gr->GetXaxis()->SetTitle("total energy [keV]");
	//gr->GetYaxis()->SetTitle("Number");
	gr->Draw("AP");
	
	
	read_3(name2);
	TGraphErrors *gr2 = new TGraphErrors(xv.size(), &xv[0], &yv[0], 0, &zv[0]);
	gr2->SetMarkerColor(kRed);
	gr2->Draw("*");
    
	c1->Update();
}


void graph(char name1[], char name2[]="zero", char name3[]="zero", char name4[]="zero", char name5[]="zero", char name6[]="zero", char name7[]="zero", char name8[]="zero")
 {
	canvas();

	read(name1);
	TGraph * gr = new TGraph(xv.size(), &xv[0], &yv[0]);
	//gr->SetLineColor(kRed);
	//gr->SetLineWidth(4);
	//gr->SetMarkerColor(4);
	gr->SetMarkerStyle(kFullCircle);
	//gr->SetTitle("spectrum");
	//gr->GetXaxis()->SetTitle("total energy [keV]");
	//gr->GetYaxis()->SetTitle("Number");
	//TAxis *axis_x = gr->GetXaxis();
	//axis_x->SetLimits(0, 1E-6);
	//TAxis *axis_y = gr->GetYaxis();
	//axis_y->SetLimits(-1E-4, 0);
	gr->Draw("AP");
	
	if(strcmp(name2, "zero")!=0)
	{
	read(name2);
	TGraph * gr2 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr2->SetMarkerColor(kRed);
	//gr2->SetMarkerStyle("*");	
	gr2->Draw("*");
	}
	
	if(strcmp(name3, "zero")!=0)
	{
	read(name3);
	TGraph * gr3 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr3->SetMarkerColor(kGreen);
	gr3->SetMarkerStyle(kCircle);	
	gr3->Draw("P");
	}
	
	if(strcmp(name4, "zero")!=0)
	{
	read(name4);
	TGraph * gr4 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr4->SetMarkerColor(kBlue);
	gr4->SetMarkerStyle(kCircle);	
	gr4->Draw("P");
	}
	
	if(strcmp(name5, "zero")!=0)
	{
	read(name5);
	TGraph * gr5 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr5->SetMarkerColor(kMagenta);
	gr5->SetMarkerStyle(kCircle);	
	gr5->Draw("P");
	}
	
	if(strcmp(name6, "zero")!=0)
	{
	read(name6);
	TGraph * gr6 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr6->SetMarkerColor(kOrange);
	//gr6->SetMarkerStyle("*");	
	gr6->Draw("*");
	}
	
	if(strcmp(name7, "zero")!=0)
	{
	read(name7);
	TGraph * gr7 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr7->SetMarkerColor(kCyan);
	//gr7->SetMarkerStyle("*");	
	gr7->Draw("*");
	}
	
	if(strcmp(name8, "zero")!=0)
	{
	read(name8);
	TGraph * gr8 = new TGraph(xv.size(), &xv[0], &yv[0]);
	gr8->SetMarkerColor(kPink);
	gr8->SetMarkerStyle(kCircle);	
	gr8->Draw("P");
	}
	
	
	
    
	c1->Update();
}

void graph(char name1[], int number_of_point, bool der = 0)
 {
	canvas();

	read(name1, number_of_point);
	TGraph * gr = new TGraph(xv.size(), &xv[0], &yv[0]);
	//gr->SetLineColor(kRed);
	//gr->SetLineWidth(4);
	//gr->SetMarkerColor(4);
	gr->SetMarkerStyle(kFullCircle);
	//gr->SetTitle("spectrum");
	//gr->GetXaxis()->SetTitle("total energy [keV]");
	//gr->GetYaxis()->SetTitle("Number");
	//TAxis *axis_x = gr->GetXaxis();
	//axis_x->SetLimits(0, 1E-6);
	//TAxis *axis_y = gr->GetYaxis();
	//axis_y->SetLimits(-1E-4, 0);
	gr->Draw("AP");
	
	if (der)
	{
		read_der(name1, number_of_point);
		TGraph * gr2 = new TGraph(xv.size(), &xv[0], &yv[0]);
		gr2->SetMarkerColor(kRed);
		gr2->Draw("*");
	}
	
	c1->Update();
}

void graph_xyz_xz(char name[], int number_of_point, bool der = 0)
 {
	canvas();
	
	read_3(name, number_of_point);
	TGraph * gr = new TGraph(xv.size(), &xv[0], &zv[0]);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(kFullCircle);
	gr->Draw("AP");
	
	if (der)
	{
		read3_der(name, number_of_point);
		TGraph * gr2 = new TGraph(xv.size(), &xv[0], &zv[0]);
		gr2->SetMarkerColor(kRed);
		gr2->Draw("*");
	}
		
	c1->Update();
}


void graph_error(char name1[], char name2[], char name3[])
 {
	canvas();

	read_3(name1);
	TGraphErrors *gr = new TGraphErrors(xv.size(), &xv[0], &yv[0], 0, &zv[0]);
	//gr->SetLineColor(kRed);
	//gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(kFullCircle);
	//gr->SetTitle("spectrum");
	//gr->GetXaxis()->SetTitle("total energy [keV]");
	//gr->GetYaxis()->SetTitle("Number");
	gr->Draw("AP");
	
	read_3(name2);
	TGraphErrors *gr2 = new TGraphErrors(xv.size(), &xv[0], &yv[0], 0, &zv[0]);
	gr2->SetMarkerColor(kRed);
	//gr2->SetMarkerStyle("*");	
	gr2->Draw("*");
	
	read_3(name3);
	TGraphErrors *gr3 = new TGraphErrors(xv.size(), &xv[0], &yv[0], 0, &zv[0]);
	gr3->SetMarkerColor(kGreen);
	gr3->SetMarkerStyle(kCircle);	
	gr3->Draw("P");
	
    
	c1->Update();
}


void graph_3d(char name[])
 {
	std::vector<double> xs;
	std::vector<double> ys;  
	std::vector<double> zs;	
	FILE *f = fopen(name,"r");
 
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

	c1->SetFillColor(42);
	c1->SetGrid();
		
	Double_t x,y,z;
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf %lf\n",&x,&y,&z);
		xs.push_back(x);
		ys.push_back(y);
		zs.push_back(z);
   }
   
	TGraph2D * gr = new TGraph2D(xs.size(), &xs[0], &ys[0], &zs[0]);
	//gr->SetLineColor(kRed);
	//gr->SetLineWidth(4);
	//gr->SetMarkerColor(4);
	//gr->SetMarkerStyle(kFullCircle);
	//gr->SetTitle("spectrum");
	//gr->GetXaxis()->SetTitle("total energy [keV]");
	//gr->GetYaxis()->SetTitle("Number");
	gr->Draw("CONT4Z");
    
	c1->Update();
	//TLine *l=new TLine(c1->GetUxmin(),9.0,c1->GetUxmax(),9.0);
	//l->SetLineColor(kRed);
	//l->SetLineWidth(6);
	//l->Draw();   
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
}

void graph_3d(char name1[], char name2[])
 {
	std::vector<double> xs;
	std::vector<double> ys;  
	std::vector<double> zs;	
	TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
	c1->SetFillColor(42);
	c1->SetGrid();
	Double_t x,y,z;	
	FILE *f = fopen(name1,"r");
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf %lf\n",&x,&y,&z);
		xs.push_back(x);
		ys.push_back(y);
		zs.push_back(z);
   }
   
	TGraph2D * gr = new TGraph2D(xs.size(), &xs[0], &ys[0], &zs[0]);
	gr->Draw("CONT4Z");
    
	c1->Update();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
	////////////////////////////////////////////////////////
	TCanvas *c2 = new TCanvas("c2","A Simple Graph Example",200,10,700,500);
	c2->SetFillColor(42);
	c2->SetGrid();
	Double_t x,y,z;	
	FILE *f = fopen(name2,"r");
	while (!feof(f))
	{ 
		fscanf(f,"%lf %lf %lf\n",&x,&y,&z);
		xs.push_back(x);
		ys.push_back(y);
		zs.push_back(z);
   }
   
	TGraph2D * gr2 = new TGraph2D(xs.size(), &xs[0], &ys[0], &zs[0]);
	gr2->Draw("CONT4Z");
    
	c2->Update();
	c2->GetFrame()->SetFillColor(21);
	c2->GetFrame()->SetBorderSize(12);
	c2->Modified();
	
	
}

void hist_Xy(char name[], int n_bins=200, double fit_interval_left=0, double fit_interval_right=1E-6)
{
	canvas();
	h1 = new TH1F("h1f","hist", n_bins, fit_interval_left, fit_interval_right);
	hist_fill_Xy(*h1, name);
	h1_Draw();
	c1->Update();
}

void hist_xY(char name[], int n_bins=200, double fit_interval_left=0, double fit_interval_right=1E-6)
{
	canvas();
	h1 = new TH1F("h1f","hist", n_bins, fit_interval_left, fit_interval_right);
	hist_fill_xY(*h1, name);
	h1_Draw();
	c1->Update();
}


void hist(char name[], int n_bins=200, double fit_interval_left=0, double fit_interval_right=1E-6)
{
	canvas();
	h1 = new TH1F("h1f","hist", n_bins, fit_interval_left, fit_interval_right);
	hist_fill(*h1, name);
	h1_Draw();
	c1->Update();
}

void hist_to_graph(char name[], int n_bins=200, double fit_interval_left=0, double fit_interval_right=1E-6)
{
	canvas();
	h1 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	hist_fill(*h1, name);
	h1_Draw();
	c1->Update();
}

void hist(char name1[], char name2[], int n_bins=100, double fit_interval_left=0, double fit_interval_right=1E-6)
 {
	canvas();
	
	h1 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h2 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	
	hist_fill(*h1, name1);
	hist_fill(*h2, name2);
		
	h1_Draw();
	h2_Draw();
	
	c1->Update();
}

void hist_compare(char name1[], char name2[], int n_bins=100, double fit_interval_left=0, double fit_interval_right=1E-6)
 {
	canvas();
	
	h1 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h2 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	
	hist_fill(*h1, name1);
	hist_fill(*h2, name2);
		
	h1->SetFillColor(kRed);
	h1->SetFillStyle(3002);
	h1->DrawNormalized();
	
	h2->SetFillColor(kGreen);
	h2->SetFillStyle(3002);
	h2->DrawNormalized("same");
	
	
	c1->Update();
}

void hist(char name1[], char name2[], char name3[], int n_bins=80, double fit_interval_left=0, double fit_interval_right=1E-6)
 {
	canvas();
	
	h1 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h2 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h3 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	
	hist_fill(*h1, name1);
	hist_fill(*h2, name2);
	hist_fill(*h3, name3);
		
	h1_Draw();
	h2_Draw();
	h3_Draw();
	
	c1->Update();
}


void fit_gaus3(char name[])
{
	canvas();
	int n_bins= int( (fit_interval_right - fit_interval_left)/(2*with) );
	h1 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	hist_fill(*h1, name);
	
	Double_t fitFunction(Double_t *x, Double_t *par) 
	{ 
		return fit_gaus(x,par) + fit_gaus(x, &par[3]) + fit_gaus(x, &par[6]); 
	}
	
	//TF1 *fitFcn = new TF1("fitFcn", fitFunction, -3E-7, 2.5E-8, 9);
	TF1 *fitFcn = new TF1("fitFcn", fitFunction, -2E-7, 2E-8, 9);
	
	// 850V
	
	fitFcn->SetParameter(0, 3.87930e+001);
	fitFcn->SetParameter(1, -2.43100e-007);
	fitFcn->SetParameter(2, 3.39971e-008);
		
	fitFcn->SetParameter(3, 1.57924e+003);
	fitFcn->SetParameter(4, -7e-008);
	fitFcn->SetParameter(5, 6.10243e-008);
	
	fitFcn->SetParameter(6, 1.68867e+005);
	fitFcn->SetParameter(7, 1.00389e-009);
	fitFcn->SetParameter(8, 6.66846e-009);
	
	
	//800V
	/*
	fitFcn->SetParameter(0, 3.60894e+001);
	fitFcn->SetParameter(1, -1.45142e-007);
	fitFcn->SetParameter(2, 1.69678e-008);	
	
	fitFcn->SetParameter(3, 2.36858e+003);
	fitFcn->SetParameter(4, -3.80395e-008);
	fitFcn->SetParameter(5, 3.61225e-008);
		
	fitFcn->SetParameter(6, 1.55014e+005);
	fitFcn->SetParameter(7, -2.45912e-009);
	fitFcn->SetParameter(8, 6.62455e-009);
	*/
	
	//750V
	/*
	fitFcn->SetParameter(0, 6.05352e+001);
	fitFcn->SetParameter(1, -6.73066e-008);
	fitFcn->SetParameter(2, 6.97341e-009);
	
	fitFcn->SetParameter(3, 7.15104e+002);
	fitFcn->SetParameter(4, -2.84681e-008);
	fitFcn->SetParameter(5, 1.50662e-008);
	
	fitFcn->SetParameter(6, 3.90523e+004);
	fitFcn->SetParameter(7, 2.28740e-009);
	fitFcn->SetParameter(8, 6.64710e-009);
	*/
	
	h1->Fit("fitFcn", "R");
	h1_Draw();	
	
	
	
	///////////////////////////////////////////////
	Double_t fit_final_1(Double_t x) 
	{ 
		double arg = (x - ( fitFcn->GetParameter(1) ))/( fitFcn->GetParameter(2) ); 
		Double_t fitval = ( fitFcn->GetParameter(0) )*TMath::Exp(-0.5*arg*arg); 
		return fitval; 
	}
	TF1 *fit_final_func_1 = new TF1("func_1", "fit_final_1(x) ", fit_interval_left, fit_interval_right);
	fit_final_func_1->SetLineColor(kGreen);
	fit_final_func_1->Draw("same");
	//////////////////////////////////////////////////
	
	Double_t fit_final_2(Double_t x) 
	{ 
		double arg = (x - ( fitFcn->GetParameter(4) ))/( fitFcn->GetParameter(5) ); 
		Double_t fitval = ( fitFcn->GetParameter(3) )*TMath::Exp(-0.5*arg*arg); 
		return fitval; 
	}
	TF1 *fit_final_func_2 = new TF1("func", "fit_final_2(x) ", fit_interval_left, fit_interval_right);	
	fit_final_func_2->SetLineColor(kBlue);
	fit_final_func_2->Draw("same");
	/////////////////////////////////////////////////
	
	Double_t fit_final_3(Double_t x) 
	{ 
		double arg = (x - ( fitFcn->GetParameter(7) ))/( fitFcn->GetParameter(8) ); 
		Double_t fitval = ( fitFcn->GetParameter(6) )*TMath::Exp(-0.5*arg*arg); 
		return fitval; 
	}
	TF1 *fit_final_func_3 = new TF1("func", "fit_final_3(x) ", fit_interval_left, fit_interval_right);	
	fit_final_func_3->SetLineColor(kMagenta);
	fit_final_func_3->Draw("same");
	/////////////////////////////////////////////////
	
	
	h_temp = new TH1F("h1f_temp","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h3 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	hist_fill(*h3, name);
	
	for (int i=0; i<n_bins; i++)
	{
		h_temp->SetBinContent( i, fit_final_func_3->Eval( h_temp->GetBinCenter(i) ) );
	}	
	
	h3->Add(h_temp, -1);
	h3_Draw();
	
	
	//ofstream test_out("H:\\LED\\one_electron\\850V.dat");
	double temp_counter=0;
	double temp_square=0;
	
	for (int i=0; i<n_bins; i++)
	{
		//test_out << h3->GetBinCenter(i) << "\t" << h3->GetBinContent(i) << endl;
		temp_counter+=( h3->GetBinCenter(i) )*( h3->GetBinContent(i) );
		temp_square+= h3->GetBinContent(i);
	}
	
	double x_mean=temp_counter/(temp_square);
	
	double rms=0;
	for (int i=0; i<n_bins; i++)
	{
		rms+=( h3->GetBinCenter(i) - x_mean ) * ( h3->GetBinCenter(i) - x_mean ) * ( h3->GetBinContent(i) )/temp_square;
		//test_out << h3->GetBinCenter(i) << "\t" << h3->GetBinContent(i) << endl;
	}
	
		
	cout << "temp_counter=\t" << temp_counter << endl;
	cout << "temp_square=\t" << (temp_square)  << endl;
	cout << "x_mean=\t" << temp_counter/(temp_square) << endl;
	cout << "rms=\t" << sqrt(rms) << endl;
	cout << "n_bins=\t" << n_bins << endl;
	
	
	c1->Update();	
}

void fit(char name[], int n_bins=70)
 {
	canvas();
	h1 = new TH1F("h1f","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	hist_fill(*h1, name);
		
	Double_t fitFunction(Double_t *x, Double_t *par) 
	{ 
		return fit_gaus(x,par) + fit_gaus(x,&par[3]); 
	}
	
	TF1 *fitFcn = new TF1("fitFcn", fitFunction, fit_interval_left, fit_interval_right, 6);
	
	
	/*
	fitFcn->SetParLimits(0,  1.5e+005,  1.7e+005); 
	fitFcn->SetParLimits(1, -0.9e-008, -1.1e-008); 
	fitFcn->SetParLimits(2, 2.4e-008, 2.6e-008); 
	
	fitFcn->SetParLimits(3, 1.5e+003, 1.7e+003); 
	fitFcn->SetParLimits(4, -1.6e-007, -1.8e-007); 
	fitFcn->SetParLimits(5, 1.6e-007, 1.8e-007); 
	*/
	
	// 750V
	/*
	fitFcn->SetParameter(0, 1.59492e+003);
	fitFcn->SetParameter(1, -1.80355e-007);
	fitFcn->SetParameter(2, 1.63042e-007);
	
	fitFcn->SetParameter(3, 1.60960e+005);
	fitFcn->SetParameter(4, -1.09934e-008);
	fitFcn->SetParameter(5, 2.54067e-008);
	*/
	
	/* 800V
	fitFcn->SetParameter(0, 8.93384e+002);
	fitFcn->SetParameter(1, -3.42444e-007);
	fitFcn->SetParameter(2, 2.58322e-007);
	
	fitFcn->SetParameter(3, 1.63089e+005);
	fitFcn->SetParameter(4, -4.59648e-009);
	fitFcn->SetParameter(5, 2.49063e-008);
	*/
	
	// 850V
	fitFcn->SetParameter(0, 1.90003e+003);
	fitFcn->SetParameter(1, -1.50882e-008);
	fitFcn->SetParameter(2, 2.24990e-008);
	
	fitFcn->SetParameter(3, 7.69263e+004);
	fitFcn->SetParameter(4, 2.33787e-009);
	fitFcn->SetParameter(5, 6.80315e-009);
		
	h1->Fit("fitFcn");
	h1_Draw();
	
	c1->Update();
}


void hist_sub(char name1[], double fit_interval_left = -7E-8, double fit_interval_right= 3E-8, int n_bins=80)
{
	canvas();
	std::vector<double> xs;
	
	h1 = new TH1F("h1f_red","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h3 = new TH1F("h1f_sub","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h_temp = new TH1F("h1f_temp","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	
	Double_t x;
	FILE *f = fopen(name1,"r");
	while (!feof(f))
	{ 
		fscanf(f,"%lf\n",&x);
		h1->Fill(x);
		h3->Fill(x);
	}
	
		
	Double_t fitf(Double_t *x,Double_t *par) 
	{ 
		Double_t arg = 0; 
		if (par[2] != 0) arg = (x[0] - par[1])/par[2]; 
		Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg); 
		return fitval; 
	}
		
		
	//TF1 *fitFcn = new TF1("fitFcn", fitf, -2.7E-8, 2.2E-8, 3);
			
	//fitFcn->SetLineColor(kMagenta);
	//fitFcn->SetLineStyle(2);
	
	
	//h3->Add(h2,-1); 
	
	
	//h1->Scale(	1/hist_peak(*h1, n_bins)	);
	//h3->Scale(	1/hist_peak(*h3, n_bins)	);
	//h2->Scale(	1/hist_peak(*h2, n_bins)	);
	
	/* 750V
	fitFcn->SetParameter(0, 3.87206e+004);
	fitFcn->SetParameter(1, 2.48744e-009);
	fitFcn->SetParameter(2, 6.62880e-009);
	*/
	
	//800V
	/*
	fitFcn->SetParameter(0, 1.33370e+005);
	fitFcn->SetParameter(1, -2.23294e-009);
	fitFcn->SetParameter(2, 6.73291e-009);
	*/
	
	//850V
	/*
	fitFcn->SetParameter(0, 1.52805e+005);
	fitFcn->SetParameter(1, 6.91334e-010);
	fitFcn->SetParameter(2, 6.63787e-009);
	*/
	
	
	//h1->Fit("fitFcn");
	
	for (int i=0; i<n_bins; i++)
	{
		float x_temp=h_temp->GetBinCenter(i);
		float y_temp=fit_temp->Eval(x_temp);
		h_temp->SetBinContent(i, y_temp);
	}
	
	/*
	for(int i=0; i<n_bins; i++)
	{
		cout << h_temp->GetBinCenter(i) << "\t" << h_temp->GetBinContent(i) << endl;
	}
	*/
	
	h3->Add(h_temp, -1);
	
	/*
	for(int i=0; i<n_bins; i++)
	{
		h3->SetBinContent(i, h1->GetBinContent(i) - h2->GetBinContent(i) );
	}
	*/
			
	//h1->SetFillColor(kGreen);
	//h1->SetFillStyle(3002);
	
	h1->SetLineColor(kRed);
	h1->Draw();
	
	/*h2->SetFillColor(kRed);
	h2->SetFillStyle(3002);*/
	//h2->SetLineColor(kGreen);
	//h2->Draw("same");
	//h2->Draw();
	
	//h_temp->Draw("same");
	//h_temp->Draw("same");
	
	h3->SetLineColor(kBlue);
	h3->Draw("same");
	
	c1->Update();
}


void hist_to_fit(char name[], double fit_interval_left=-1.6E-8, double fit_interval_right=2.2E-8, int n_bins=30)
 {
	canvas();
	std::vector<double> xs;
	
	h1_fit = new TH1F("h1f_red","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	h_temp_fit = new TH1F("h1f_temp","One electron spectrum", n_bins, fit_interval_left, fit_interval_right);
	
	Double_t x;
	FILE *f = fopen(name,"r");
	while (!feof(f))
	{ 
		fscanf(f,"%lf\n",&x);
		h1_fit->Fill(x);
	}

	Double_t fitf(Double_t *x, Double_t *par) 
	{ 
		Double_t arg = 0; 
		if (par[2] != 0) arg = (x[0] - par[1])/par[2]; 
		Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg); 
		return fitval; 
	}
			
	fit_temp = new TF1("fit_temp", fitf, fit_interval_left, fit_interval_right, 3);
			
	fit_temp->SetLineColor(kMagenta);
	fit_temp->SetLineStyle(2);
	
	fit_temp->SetParameter(0, 3.93225e+004);
	fit_temp->SetParameter(1, 1.20161e-009);
	fit_temp->SetParameter(2, 6.52298e-009);

	h1_fit->Fit("fit_temp");	
	
	h1_fit->SetFillColor(kRed);
	h1_fit->SetFillStyle(3002);
	h1_fit->Draw();	

	c1->Update();
}

double hist_peak(TH1F &histogram, double n_bins)
{
	double bin_max=0;
	double temp;
	
	for(int i=0; i<n_bins; i++)
	{
		temp = histogram.GetBinContent(i);
		if (temp>bin_max)
			bin_max=temp;
	}
	cout << "bin_max=\t" << bin_max << endl;
	return bin_max;
}

