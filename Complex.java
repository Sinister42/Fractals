


public class Complex{
	private double re;
	private double im;
	
	public Complex(double re, double im){
		this.re = re;
		this.im = im;
	}
	
	public Complex pow2(Complex c){
		re = (c.getRe() * c.getRe())-(c.getIm() * c.getIm());
		im = 2 * c.getRe() * c.getIm();
		return new Complex(re,im);
	}
	
	public Complex pow4(Complex c){
		return pow2(pow2(c));
	}
	
	public Complex mul(double m, Complex c){
		re = c.getRe() * m;
		im = c.getIm() * m;
		return new Complex(re,im);
	}
	
	public double getRe(){
		return re;
	}
	public double getIm(){
		return im;
	}
	
}