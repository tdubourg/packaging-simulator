
package client;

import IHM.WelcomeFrame;
import java.io.IOException;
/** Main class, network client application. To be used together with the packaging-simulator server */
public class Client {
	
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) throws IOException {
		WelcomeFrame frame = new WelcomeFrame();
		frame.setVisible(true);
	}
}
