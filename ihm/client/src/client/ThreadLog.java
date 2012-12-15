/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Elodie
 */
public class ThreadLog extends Thread {
    InetAddress serverAddress;
    Socket socketCommand;
    int serverPort;
    
    public ThreadLog() throws IOException {
		serverAddress = InetAddress.getLocalHost();
		serverPort = 30035;
		//creation socket
		socketCommand = new Socket(serverAddress,serverPort);
    }
    
    @Override
    public void run() {
        //écoute sur socket
        InputStreamReader in;
		boolean openedSocket = true;
        while (openedSocket)
        {
			char[] buffer = new char[256];
            try {
                in = new InputStreamReader (socketCommand.getInputStream());
                in.read(buffer);
				/*if (buffer != null){
					System.out.println(buffer);
				}else{
					openedSocket = false;
				}*/
				System.out.println("_");
				System.out.println(buffer);
            } catch (IOException ex) {
                Logger.getLogger(ThreadCommand.class.getName()).log(Level.SEVERE, null, ex);
				openedSocket = false;
            }
        }
    }
    
}