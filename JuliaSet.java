
/**
* z(i+1) = z(i)^2 + c
* c = -0.4 + 0.6i
*/
public class JuliaSet {
	
	private double[] fractArr;
	private int iter;
	private final int DEFAULT_ITER = 150;
	private final DEFAULT = 640*480;
	private final Complex c = new Complex(-0.4, 0.6);
	
	public JuliaSet(int width, int height, int iter){
		fractArr = new double[width*height];
		this.iter = iter;
	}
	public JuliaSet(int width, int height){
		fractArr = new double[width*height];
		iter = 150;
	}
	public JuliaSet(){
		fractArr = new double[DEFAULT];
		iter = DEFAULT_ITER;
	}
	
	public double[] juliaFractals(){
		//TODO
	}
	
} 
