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
import java.net.UnknownHostException;

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
        //SocketClient socketClient = new SocketClient();
        
        // création des threads
        ThreadCommand threadCmd = new ThreadCommand();
        ThreadLog threadLog = new ThreadLog();
        // activation des threads
        threadCmd.start();
        threadLog.start();

    }
}
