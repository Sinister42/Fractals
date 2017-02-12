


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
	
	public Complex add(Complex c1, Complex c2){
		return new Complex(c1.getRe()+c2.getRe(), c1.getIm()+c2.getIm());
	}
	
	public Complex mul(double m, Complex c){
		re = c.getRe() * m;
		im = c.getIm() * m;
		return new Complex(re,im);
	}
	
	public Complex div(Complex c1, Complex c2){
		double d = (c2.getRe()*c2.getRe()) + (c2.getIm()*c2.getIm());
		double re = ((c1.getRe()*c2.getRe()) - (c1.getIm()*c2.getIm()));
		double im = ((c1.getRe()*c2.getIm()) + (c2.getRe()*c1.getIm()));
		return new Complex((re/d), (im/d));
	}
	
	public double getRe(){
		return re;
	}
	public double getIm(){
		return im;
	}
	
}