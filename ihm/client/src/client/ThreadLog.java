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
    
    public ThreadLog() {
        try {
            System.out.println("ici");
            serverAddress = InetAddress.getByName("192.168.16.40");
            System.out.println("plouf");
            serverPort = 8080;
            //creation socket
            socketCommand = new Socket(serverAddress,serverPort);	
            System.out.println("Connexion socket log");
            
        } catch (IOException ex) {
            Logger.getLogger(ThreadCommand.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void run() {
        //écoute sur socket
        BufferedReader in;
        try {
            in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
            String message_distant = in.readLine();
            System.out.println(message_distant);
        } catch (IOException ex) {
            Logger.getLogger(ThreadCommand.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
