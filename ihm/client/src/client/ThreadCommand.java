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
<<<<<<< HEAD
            serverAddress = InetAddress.getByName("127.0.0.1");
=======
            serverAddress = InetAddress.getByName("192.168.0.1");
>>>>>>> 5f37daf66067166835d0b4ae2c434c51483cd320
            serverPort = 13003;
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
