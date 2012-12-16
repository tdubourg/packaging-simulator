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

public class ThreadLog extends Thread
{

	InetAddress serverAddress;
	Socket socketCommand;
	int serverPort;
	private final static String ERROR_BOX = "ERROR B";
	private final static String ERROR_PALETTE = "ERROR P";
	private final static String ERROR_PRINT = "ERROR A";
	private final static String ERROR_WAREHOUSE = "ERROR W";
	private final static String ERROR_PALETTE_QUEUE = "ERROR Q";
	private final static String ERROR_BOX_REFUSED = "ERROR R";
	private final static String ERROR_GAME_OVER = "GAME OVER";
	private final static String ERROR_EMERGENCY_STOP = "EMERGENCY_STOP_OCCURED";

	public enum ERROR
	{

		BOX, PALETTE, PRINT, PALETTE_QUEUE, BOX_REFUSED, EMERGENCY_STOP
	};
	private WeakReference<LogReceiver> logListener;

	/**
	 * constructor of thread creates the command socket
	 *
	 * @throws IOException
	 */
	public ThreadLog() throws IOException
	{
		serverAddress = InetAddress.getLocalHost();
		serverPort = 30035;
		//socket creation
		socketCommand = new Socket(serverAddress, serverPort);
	}

	/**
	 * sets the log receiver
	 *
	 * @param logListener logListener
	 */
	public void setLogReceiver(LogReceiver logListener)
	{
		this.logListener = new WeakReference<>(logListener);
	}

	public interface LogReceiver
	{

		public void onReveiveLog(String log);

		public void onReceiveError(ERROR error);

		public void onGameOver();
	}

	/**
	 * Listens on the socket, for new logs pushed from the server Pushes the
	 * logs towards the logReceiver If errors are detected in the log, raises
	 * errors
	 */
	@Override
	public void run()
	{
		// Listening on socket
		BufferedReader in;
		boolean openedSocket = true;
		while (openedSocket)
		{
			try
			{
				in = new BufferedReader(new InputStreamReader(socketCommand.getInputStream()));
				while (in.ready())
				{
					String message_distant = in.readLine();
					if (logListener != null && logListener.get() != null)
					{
						switch (message_distant)
						{
							case ERROR_BOX:
							{
								logListener.get().onReceiveError(ERROR.BOX);
								break;
							}
							case ERROR_PALETTE:
							{
								logListener.get().onReceiveError(ERROR.PALETTE);
								break;
							}
							case ERROR_PALETTE_QUEUE:
							{
								logListener.get().onReceiveError(ERROR.PALETTE_QUEUE);
								break;
							}
							case ERROR_PRINT:
							{
								logListener.get().onReceiveError(ERROR.PRINT);
								break;
							}
							case ERROR_BOX_REFUSED:
							{
								logListener.get().onReceiveError(ERROR.BOX_REFUSED);
								break;
							}
							case ERROR_GAME_OVER:
							{
								logListener.get().onGameOver();
								break;
							}
							case ERROR_EMERGENCY_STOP:
							{
								logListener.get().onReceiveError(ERROR.EMERGENCY_STOP);
								break;
							}
							default:
							{
								logListener.get().onReveiveLog(message_distant);
								break;
							}
						}
					}
				}
			}
			catch (IOException ex)
			{
				Logger.getLogger(Command.class.getName()).log(Level.SEVERE, null, ex);
				openedSocket = false;
			}
		}
	}
}
