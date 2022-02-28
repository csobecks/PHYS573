//HW5 code
void code(){
    auto c = new TCanvas("c","2D Graph",0,0,500,500);
    double x, y, z, z1, r2=1.0, P = 6.0;
    int np = 300;
    auto dt = new TGraph2D();
    auto r  = new TRandom();
    for (int N=0; N<np; N++) {
        x = 2*P*(r->Rndm(N));
        y = 2*P*(r->Rndm(N));
        z=sqrt(r2*r2+x*x+y*y);
        z1=erf(z)-1;
        dt->SetPoint(N,x,y,z1);
    }
    dt->Draw("tri1 p0");
}