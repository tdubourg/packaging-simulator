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
public class ThreadCommand {

    InetAddress serverAddress;
    Socket socketCommand;
    int serverPort;
    int nbA;
    int nbB;
    
    public ThreadCommand() throws IOException {
		serverAddress = InetAddress.getLocalHost();
		serverPort = 13003;
		//creation socket
		socketCommand = new Socket(serverAddress,serverPort);	            
    }
    
    public Boolean sendParameters(int rebus, int box, int pal)
    {
	//écriture commande
	BufferedReader in;
	PrintWriter out;
	String toSend;
	
//	InputStreamReader isr=new InputStreamReader(System.in);
//	BufferedReader keyboardInput=new BufferedReader(isr);
	
//	boolean openSocket = true;
//	while (openSocket){
		try {
			toSend = rebus + "-" + box + "-" + pal+ "\r\n";
			out = new PrintWriter(socketCommand.getOutputStream());
			out.print(toSend);
			out.flush();
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
//	}
        return true;
    }
}