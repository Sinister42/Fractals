
/**
* z(i+1) = z(i)^2 + c
* c = -0.4 + 0.6i
*/
public class JuliaSet {
	private final int DEFAULT_ITER = 150;
	private final int DEFAULT_WIDTH = 640;
	private final int DEFAULT_HEIGHT = 480;
	private final Complex c = new Complex(-0.4, 0.6);
	private final double XMAX = 2.0;
	private final double YMAX = 2.0;
	
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
		this.width = width;
		this.height = height;
		this.iter = iter;
	}
	public JuliaSet(int width, int height){
		this.width = width;
		this.height = height;
		xmax = XMAX;
		ymax = YMAX;
		xmin = -XMAX;
		ymin = -YMAX;
		iter = DEFAULT_ITER;
	}
	public JuliaSet(){
		width = DEFAULT_WIDTH;
		height = DEFAULT_HEIGHT;
		iter = DEFAULT_ITER;
		xmax = XMAX;
		ymax = YMAX;
		xmin = -XMAX;
		ymin = -YMAX;
	}
	
	public double[] juliaFractals(){
		double[] fractArr = new double[width*height];
		double horiz_move = (2*xmax)/width;
		double verti_move = (2*ymax)/height;
		Complex curr;
		
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				curr = new Complex(xmin + (i*horiz_move), ymin + (j*verti_move));
				for(int k = 0; k < iter; k++){
					if(curr.abs() > 4.0){
						fractArr[i*j] = (double)(k)/(double)iter;
						break;
					}
					curr = curr.pow2();
					curr = curr.add(c);
				}
			}
		}
		return fractArr;
	}
	/*
	public double[] juliaFractals(){
		x = xmin;
		y = ymax;
		double horiz_move = (2*xmax)/width;
		double verti_move = (2*ymax)/height;
		Complex curr = new Complex(x, y);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				for (int k = 0; k < iter; k++){
					double abso = curr.abs();
					System.out.print("1: K: " + k + " C: "+ curr.toString()+ " abs: "+ abso+ "\n");
					if(abso > 2.0){
						System.out.print("2: K: " + k + " C: "+ curr.toString()+ " abs: "+ abso+ "\n");
						try{
							Thread.sleep(100);
						} catch(InterruptedException e){
							System.out.println(e.getMessage());
						}
						double t =(double)(k-1)/(double)iter;
						// System.out.println("JS-T: "+t);
						fractArr[i*j] = t;
						break;
					}
					curr.pow2();
					curr.add(c);
				}
				// if(fractArr[i*j] == 0.0){
					// fractArr[i*j] = 1;
				// }
				curr.setRe_Im(x,y);
				curr.add(j*horiz_move,i*verti_move);
			}
			curr.setRe_Im(x, y);
			curr.add(0,i*verti_move);
		}
		return fractArr;
	*/
	
	public int getWidth(){
		return width;
	}
	public int getHeight(){
		return height;
	}
	
} 
