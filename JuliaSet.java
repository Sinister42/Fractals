
/**
* z(i+1) = z(i)^2 + c
* c = -0.4 + 0.6i
*/
public class JuliaSet {
	private final int DEFAULT_ITER = 150;
	private final int DEFAULT_WIDTH = 640;
	private final int DEFAULT_HEIGHT = 480;
	private final Complex c = new Complex(-0.4, 0.6);
	private final double XMAX = 1.6;
	private final double YMAX = 1;
	
	private double[] fractArr;
	private int iter;
	private int width;
	private int height;
	private double xmin;
	private double xmax;
	private double ymin;
	private double ymax;
	private double x;
	private double y;
	
	public JuliaSet(int width, int height, int iter, double xmax, double ymax){
		this.xmax = xmax; this.ymax = ymax;
		xmin = (-1)*xmax; ymin = (-1)*ymax;
		fractArr = new double[width*height];
		this.width = width;
		this.height = height;
		this.iter = iter;
	}
	public JuliaSet(int width, int height){
		fractArr = new double[width*height];
		this.width = width;
		this.height = height;
		xmax = XMAX;
		ymax = YMAX;
		xmin = -XMAX;
		ymin = -YMAX;
		iter = DEFAULT_ITER;
	}
	public JuliaSet(){
		fractArr = new double[DEFAULT_HEIGHT*DEFAULT_WIDTH];
		width = DEFAULT_WIDTH;
		height = DEFAULT_HEIGHT;
		iter = DEFAULT_ITER;
		xmax = XMAX;
		ymax = YMAX;
		xmin = -XMAX;
		ymin = -YMAX;
	}
	
	public double[] juliaFractals(){
		x = xmin;
		y = ymax;
		double horiz_move = (2*xmax)/width;
		double verti_move = (2*ymax)/height;
		Complex curr = new Complex(x, y);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				for (int k = 0; k < iter; k++){
					if(curr.abs() > 2){
						fractArr[i*j] = (double)(k-1)/(double)iter;
						break;
					}
					curr.pow2();
					curr.add(c);
				}
				if(fractArr[i*j] == 0.0){
					fractArr[i*j] = 1;
				}
				curr.add(horiz_move,0);
			}
			curr.setRe_Im(x, curr.getIm());
			curr.add(0,verti_move);
		}
	}
	
} 
