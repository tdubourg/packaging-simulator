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
        BufferedReader in;
        while (true)
        {
            try {
                in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
                String message_distant = in.readLine();
                System.out.println(message_distant);
            } catch (IOException ex) {
                Logger.getLogger(ThreadCommand.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
}
