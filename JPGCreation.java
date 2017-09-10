import javafx.scene.image.*;
import javafx.scene.paint.Color;
import javafx.embed.swing.SwingFXUtils;
import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;
import java.lang.Math;
import java.util.Arrays;

public class JPGCreation{
	
	private String name;
	private JuliaSet js;
	private int width;
	private int height;
	
	public JPGCreation(String name){
		this.name = name;
		js = new JuliaSet();
		width = js.getWidth();
		height = js.getHeight();
	}
	
	public void create(){
		double[][] fractArr = js.juliaFractals();
		for(double[] d : fractArr){System.out.println(Arrays.toString(d));}
		WritableImage writableImg = new WritableImage(width,height);
		PixelWriter pWriter = writableImg.getPixelWriter();
		//TODO - write the colours onto the writableImg
		for(int i = 0; i < height-1; i++){
			for(int j = 0; j < width-1; j++){
				//TODO - p = (a<<24) | (r<<16) | (g<<8) | b
				double t = fractArr[j][i];
				int r = (int)(9*(1-t)*(Math.pow(t,3))*255);
				int g = (int)(15*(Math.pow((1-t),2))*(Math.pow(t,2))*255);
				int b = (int)(8.5*(Math.pow((1-t),3))*t*255);
				// int p = (r << 16) | (g << 8) | b;
				// if(r < 0){r=0;}
				// if(g < 0){g=0;}
				// if(b < 0){b=0;}
				
				//System.out.println("T: " + t + "\n r: " + r + " g: " + g + " b: " + b);
				Color c = Color.rgb(r,g,b);
				pWriter.setColor(j,i,c);
			}
		}
		File img = new File(name+"_tmp.png");
		try{
			ImageIO.write(SwingFXUtils.fromFXImage(writableImg, null), "png", img);
		} catch (IOException ex){
			System.out.println(ex.getMessage());
		}
	}
} 
