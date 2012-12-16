/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import IHM.WelcomeFrame;
import java.io.IOException;
import java.util.concurrent.ConcurrentLinkedQueue;

/**
 *
 * @author pierre
 */
public class Client {
	
	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) throws IOException {
		//System.out.println("Hello World !!!");
		WelcomeFrame frame = new WelcomeFrame();
		frame.setVisible(true);
	}
}
