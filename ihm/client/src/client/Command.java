
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
 * @author H4102
 */
public class Command {
	
	final static String INIT_MSG_PREFIX = "INIT";
	final static String CMD_MSG_PREFIX = "CMD";
	final static String RESTART_MSG_PREFIX = "RESTART";
	final static String SHUTDOWN_MSG_PREFIX = "SHUTDOWN";

	InetAddress serverAddress;
	Socket socketCommand;
	int serverPort;
	int nbA;
	int nbB;
	
	/**
	 * constructor
	 * creates the command socket
	 * @throws IOException 
	 */
	public Command() throws IOException {
		serverAddress = InetAddress.getLocalHost();
		serverPort = 13003;
		//creation socket
		socketCommand = new Socket(serverAddress,serverPort);				
	}
	
	/**
	 * Sends the parameters to the server
	 * @param lot A or B
	 * @param rebus maximum number pf pieces in the rebus per box
	 * @param box number of pieces in each box
	 * @param palnumber of boxes in each pallets
	 * @param qte number of pallets to produce
	 * @return true
	 */
	public Boolean sendParameters(String lot, int rebus, int box, int pal, int qte)
	{
	//command writing
	BufferedReader in;
	PrintWriter out;
	String toSend;
	
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
				//listen to answer
				in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
				String message_distant = in.readLine();
				System.out.println(message_distant);
		} catch (IOException ex) {
				Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
		return true;
	}
	
	/**
	 * Sends the number of pallets commanded 
	 * @param A number of pallets for A
	 * @param B number of pallets for B
	 * @return true
	 */
	public Boolean sendCommand(int A, int B)
	{
	//command writing
	BufferedReader in;
	PrintWriter out;
	String toSend;
	
		try {
				toSend = CMD_MSG_PREFIX + "-" + A + "-" + B + "\r\n";
				out = new PrintWriter(socketCommand.getOutputStream());
				out.print(toSend);
				out.flush();
		} catch (IOException ex) {
				Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
		try {
				//listen to anwser
				in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
				String message_distant = in.readLine();
				System.out.println(message_distant);
		} catch (IOException ex) {
				Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
		return true;
	}

		/**
		 * Sends the restart signal to the server
		 */
	public void sendRestartProd() {
		this.sendSimpleCommand(RESTART_MSG_PREFIX);
	}

		/**
		 * sends the shutdown signal to the server
		 */
	public void sendShutdown() {
		this.sendSimpleCommand(SHUTDOWN_MSG_PREFIX);
	}

		/**
		 * Sends a command to the server
		 * @param commandPrefix prefix of command to send
		 */
	private void sendSimpleCommand(String commandPrefix) {
		PrintWriter out;
		String toSend;
		BufferedReader in;
		try {
			toSend = commandPrefix + "\r\n";
			out = new PrintWriter(socketCommand.getOutputStream());
			out.print(toSend);
			out.flush();
		} catch (IOException ex) {
			Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
		try {
			//listen to answer
			in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
			String message_distant = in.readLine();
			System.out.println(message_distant);
		} catch (IOException ex) {
			Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
	
	
}