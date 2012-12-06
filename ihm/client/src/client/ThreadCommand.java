/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Elodie
 */
public class ThreadCommand extends Thread {

    InetAddress serverAddress;
    Socket socketCommand;
    int serverPort;
    int nbA;
    int nbB;
    
    public ThreadCommand() {
        try {
            serverAddress = InetAddress.getByName("192.168.16.40");
            serverPort = 8081;
            //creation socket
            socketCommand = new Socket(serverAddress,serverPort);	
            System.out.println("Connexion socket command");
            
        } catch (IOException ex) {
            Logger.getLogger(ThreadCommand.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    @Override
    public void run() {
        //écriture commande
        BufferedReader in;
        PrintWriter out;
        try {
            out = new PrintWriter(socketCommand.getOutputStream());
            out.println(nbA);
            out.flush();
            System.out.println("Envoi de " + nbA + " + flush");
        } catch (IOException ex) {
            Logger.getLogger(ThreadCommand.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            //écoute réponse
            in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
            String message_distant = in.readLine();
            System.out.println(message_distant);
        } catch (IOException ex) {
            Logger.getLogger(ThreadCommand.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
}
