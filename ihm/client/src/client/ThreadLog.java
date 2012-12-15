/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import IHM.ManagementFrame;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.ref.WeakReference;
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
	
	private WeakReference<LogReceiver> listener;
    
    public ThreadLog() throws IOException {
		serverAddress = InetAddress.getLocalHost();
		serverPort = 30035;
		//creation socket
		socketCommand = new Socket(serverAddress,serverPort);
    }
	
	public void setLogReceiver(LogReceiver listener){
		this.listener = new WeakReference<>(listener);
	}
	
	public interface LogReceiver{
		public void onReveiveLog(String log);
	}
    
    @Override
    public void run() {
        //écoute sur socket
        BufferedReader in;
		boolean openedSocket = true;
        while (openedSocket)
        {
            try {
                in = new BufferedReader (new InputStreamReader (socketCommand.getInputStream()));
                while (in.ready()){
					String message_distant = in.readLine();
					if(listener!= null && listener.get()!=null){
						listener.get().onReveiveLog(message_distant);
					}
				}
				/*if (message_distant != null){
					System.out.println(message_distant);
				}else{
					openedSocket = false;
				}*/
            } catch (IOException ex) {
                Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
				openedSocket = false;
            }
        }
    }
}
