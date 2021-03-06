
import java.lang.Math;

public class Complex{
	private double re;
	private double im;
	
	public Complex(double re, double im){
		this.re = re;
		this.im = im;
	}
	
	public Complex pow2(Complex c){
		double real = (c.getRe() * c.getRe())-(c.getIm() * c.getIm());
		double img = 2 * c.getRe() * c.getIm();
		return new Complex(real,img);
	}
	public Complex pow2(){
		double real = (re * re)-(im * im);
		double img = 2 * re * im;
		return new Complex(real,img);
	}
	
	
	
	public Complex pow4(Complex c){
		return pow2(pow2(c));
	}
	public void pow4(){
		pow2();
		pow2();
	}
	
	public Complex add(Complex c1, Complex c2){
		return new Complex(c1.getRe()+c2.getRe(), c1.getIm()+c2.getIm());
	}
	public Complex add(Complex c){
		re += c.getRe();
		im += c.getIm();
		return new Complex(re,im);
	}
	public void add(double re_c, double im_c){
		re += re_c;
		im += im_c;
	}
	
	public void mul(double m){
		re *= m;
		im *= m;
	}
	
	public Complex div(Complex c1, Complex c2){
		double d = (c2.getRe()*c2.getRe()) + (c2.getIm()*c2.getIm());
		double real = ((c1.getRe()*c2.getRe()) - (c1.getIm()*c2.getIm()));
		double img = ((c1.getRe()*c2.getIm()) + (c2.getRe()*c1.getIm()));
		return new Complex((real/d), (img/d));
	}
	public void div(Complex c){
		double d = (c.getRe()*c.getRe()) + (c.getIm()*c.getIm());
		re = ((re*c.getRe()) - (im*c.getIm())) / d;
		im = ((re*c.getIm()) + (im*c.getRe())) / d;
	}
	
	public double abs(){
		return Math.sqrt((re*re) + (im*im));
	}
	
	public double getRe(){
		return re;
	}
	public double getIm(){
		return im;
	}
	public void setRe_Im(double re_c, double im_c){
		re = re_c;
		im = im_c;
	}
	@Override
	public String toString(){
		return re + " " + im;
	}
}