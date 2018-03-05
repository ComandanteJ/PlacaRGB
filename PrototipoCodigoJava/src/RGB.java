import java.util.Scanner;

public class RGB {

	public static void main(String[] args) {

		int R = 0,G = 0, B = 0, btn = 0;
		String color = "R";
		Scanner teclado = new Scanner(System.in);
		
		System.out.println("-- R: "+R+" G: "+G+" B: "+B+" --");
		
		while(true) {
			
			btn = teclado.nextInt();
			
			if(btn == 2) {
				
				System.out.println("Boton 2");
				
				if(color == "R") {
					
					color = "G";
					System.out.println("Cambio de color: R -> G");
					
				}else if(color == "G") {
									
						color = "B";
						System.out.println("Cambio de color: G -> B");
									
				}else if(color == "B") {
					
					color = "R";
					System.out.println("Cambio de color: B -> R");
					
				}
				
			}
			
			if(btn == 1) {
				
				if(color == "R") {
					
					if(R != 255) {
						R+= 15;
					}else {
						R = 0;
					}
				}else if(color == "G") {
					
					if(G != 255) {
						G+=15;
					}else {
						G = 0;
					}
				}else if(color == "B") {
					
					if(B != 255) {
						B+=15;
					}else {
						B = 0;
					}
				}
				
				
				System.out.println("Boton 1");
				System.out.println("-- R: "+R+" G: "+G+" B: "+B+" --");
				
				
			}
			
			
		}
		
		
		
	}

}
