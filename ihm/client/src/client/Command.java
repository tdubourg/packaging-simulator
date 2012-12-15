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
public class Command {
	
	final static String INIT_MSG_PREFIX = "INIT";
	final static String CMD_MSG_PREFIX = "CMD";

    InetAddress serverAddress;
    Socket socketCommand;
    int serverPort;
    int nbA;
    int nbB;
    
    public Command() throws IOException {
		serverAddress = InetAddress.getLocalHost();
		serverPort = 13003;
		//creation socket
		socketCommand = new Socket(serverAddress,serverPort);	            
    }
    
    public Boolean sendParameters(String lot, int rebus, int box, int pal, int qte)
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
			toSend = INIT_MSG_PREFIX + "-" + lot + "-" + rebus + "-" + box + "-" + pal+ "-" + qte + "\r\n";
			//toSend = "DISCONNECT\r\n";
			out = new PrintWriter(socketCommand.getOutputStream());
			out.print(toSend);
			out.flush();
		} catch (IOException ex) {
			Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
		try {
			//écoute réponse
			in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
			String message_distant = in.readLine();
			System.out.println(message_distant);
		} catch (IOException ex) {
			Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
//	}
        return true;
    }
    
    public Boolean sendCommand(int A, int B)
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
			toSend = CMD_MSG_PREFIX + "-" + A + "-" + B + "\r\n";
			out = new PrintWriter(socketCommand.getOutputStream());
			out.print(toSend);
			out.flush();
		} catch (IOException ex) {
			Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
		try {
			//écoute réponse
			in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
			String message_distant = in.readLine();
			System.out.println(message_distant);
		} catch (IOException ex) {
			Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
//	}
        return true;
    }
    
}