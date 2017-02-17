import javafx.*;
import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;

public class JPGCreation{
	
	private String name;
	private JuliaSet js;
	private int width;
	private int height;
	
	public JPGCreation(String name){
		this.name = name;
		js - new JuliaSet();
		width = js.getWidth();
		height = js.getHeight();
	}
	
	public void create(){
		double[] fractArr = js.juliaFractals();
		WritableImage writableImg = new WritableImage(width,height);
		PixelWriter pWriter = writableImg.getPixelWriter();
		//TODO - write the colours onto the writableImg
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				//TODO
			}
		}
		File img = new File(name+".jpg");
		try{
			ImageIO.write(SwingFXUtils.fromFXImage(writableImg, null), "jpg", img);
		} catch (IOException ex){
			System.out.println(ex.getMessage());
		}
	}
} 
