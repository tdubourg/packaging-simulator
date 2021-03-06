package IHM;

import client.Command;
import client.ThreadLog;
import javax.swing.JFrame;
import javax.swing.JProgressBar;

/**
 * ManagementFrame displays the current progression of the production on the
 * serveur together with the logs sent by the server. It serves as the
 * LogReceiver for the ThreadLog and launches the GameOverPopup and ErrorPopup
 * when needed. This is the central JFrame, we will go from here to newCmdFrame,
 * GameOverPopup, ErrorPopup...
 */
public class ManagementFrame extends javax.swing.JFrame implements ThreadLog.LogReceiver
{

	Command threadCmd;
	ThreadLog threadLog;
	//warehouse disponibility 
	int palAWarehouse;
	int palBWarehouse;
	// number of pallets and box to produce
	int nbPalA;
	int nbPalB;
	int nbBoxPerPal;
	//current situation
	int nbCurrentBox;
	int nbCurrentBin;
	String currentLot;
	//previous situation
	int previousPalAWarehouse;
	int previousPalBWarehouse;
	//production state
	Boolean onProduction = true;
	//command frame
	private NewCmdFrame newCmdFrame = null;
	private ParametersFrame paramsFrame;

	/**
	 * Sets frame's parameters
	 *
	 * @param p parameters
	 */
	public void setParamsFrame(ParametersFrame p)
	{
		this.paramsFrame = p;
		this.goPopup.setParamsFrame(this.paramsFrame);
	}

	/**
	 * Gets the number of pallets A in warehouse
	 *
	 * @return number of pallets A in warehouse
	 */
	public int getPalAWarehouse()
	{
		return palAWarehouse;
	}

	/**
	 * Gets the production status
	 *
	 * @return true if production is active, false if not.
	 */
	public Boolean getOnProduction()
	{
		return onProduction;
	}

	/**
	 * Sets the onProduction property
	 *
	 * @param onProduction true if production, false if not.
	 */
	public void setOnProduction(Boolean onProduction)
	{
		this.onProduction = onProduction;
	}

	/**
	 * gets the number of pallets B in warehouse
	 *
	 * @return number of pallets B in warehouse
	 */
	public int getPalBWarehouse()
	{
		return palBWarehouse;
	}

	/**
	 * Sets the parameters of frame
	 *
	 * @param lot A or B
	 * @param qte Number of pallets for this lot
	 * @param pal number of box in each pallets
	 */
	public void setParameters(String lot, int qte, int pal)
	{
		this.currentLot = lot;
		this.descriptionLabel.setText("État de fabrication du lot" + currentLot);
		this.nbBoxPerPal = pal;
		//initialization of data
		if (currentLot.equalsIgnoreCase("A"))
		{
			this.nbPalA = qte;
		}
		else
		{ //lot == "B"
			this.nbPalB = qte;
		}

		//progress bar
		lotProgressBar.setMaximum(qte * pal);
		lotProgressBar.setValue(0);
		lotProgressBar.setStringPainted(true);

		//previous situation
		previousPalAWarehouse = palAWarehouse;
		previousPalBWarehouse = palBWarehouse;
	}

	/**
	 * Creates new form ManagementFrame
	 */
	public ManagementFrame(Command threadCmd, ThreadLog threadLog)
	{
		initComponents();
		this.threadCmd = threadCmd;
		this.threadLog = threadLog;
		threadLog.setLogReceiver(this);
		this.logTextArea.setEditable(false);
		//stock initialisation
		this.palAWarehouse = 0;
		this.palBWarehouse = 0;
		// Init related frames:
		this.goPopup = new GameOverPopup(this, this.threadCmd);
		this.goPopup.setCommand(threadCmd);
		this.newCmdFrame = new NewCmdFrame(this, this.threadCmd);
		this.newCmdFrame.setGoPopup(goPopup);
		this.goPopup.setCmdFrame(newCmdFrame);

	}
	boolean currentErrorState = false;

	/**
	 * Sets the visibility property
	 *
	 * @param visibility true or false. Visible if true, hidden if false
	 */
	@Override
	public void setVisible(boolean visibility)
	{
		if (currentErrorState)
		{// If we currently are in an error state, then ignore any ask for being visible/keeps being hidden
			visibility = false;
		}
		super.setVisible(visibility);
	}

	/**
	 * Adds a log in the text area
	 *
	 * @param log log to add
	 */
	public void addLog(String log)
	{
		logTextArea.append(log + "\r\n");
	}

	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always
	 * regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
	// <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
	private void initComponents() {

		descriptionLabel = new javax.swing.JLabel();
		newCmdButton = new javax.swing.JButton();
		logScrollPane = new javax.swing.JScrollPane();
		logTextArea = new javax.swing.JTextArea();
		lotProgressBar = new javax.swing.JProgressBar();
		currentBox = new javax.swing.JLabel();
		currentBin = new javax.swing.JLabel();
		currentPal = new javax.swing.JLabel();

		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
		setTitle("Suivi de la chaine de production");
		setResizable(false);

		descriptionLabel.setText("Etat de fabrication du lot");

		newCmdButton.setText("Nouvelle commande");
		newCmdButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				newCmdButtonActionPerformed(evt);
			}
		});

		logTextArea.setColumns(20);
		logTextArea.setRows(5);
		logScrollPane.setViewportView(logTextArea);

		currentBox.setText("Carton en cours de remplissage : ");

		currentBin.setText("Taux de rebus dans le carton en cours :");

		currentPal.setText("currentPal");

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
					.addGroup(layout.createSequentialGroup()
						.addGap(22, 22, 22)
						.addComponent(lotProgressBar, javax.swing.GroupLayout.PREFERRED_SIZE, 239, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(18, 18, 18)
						.addComponent(currentPal, javax.swing.GroupLayout.DEFAULT_SIZE, 198, Short.MAX_VALUE))
					.addGroup(layout.createSequentialGroup()
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
							.addGroup(layout.createSequentialGroup()
								.addContainerGap()
								.addComponent(currentBox))
							.addGroup(layout.createSequentialGroup()
								.addContainerGap()
								.addComponent(currentBin)))
						.addGap(0, 0, Short.MAX_VALUE))
					.addGroup(layout.createSequentialGroup()
						.addContainerGap()
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
							.addComponent(logScrollPane)
							.addGroup(layout.createSequentialGroup()
								.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
									.addComponent(descriptionLabel)
									.addComponent(newCmdButton, javax.swing.GroupLayout.PREFERRED_SIZE, 193, javax.swing.GroupLayout.PREFERRED_SIZE))
								.addGap(0, 0, Short.MAX_VALUE)))))
				.addContainerGap())
		);
		layout.setVerticalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addContainerGap()
				.addComponent(descriptionLabel)
				.addGap(18, 18, 18)
				.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
					.addComponent(lotProgressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addComponent(currentPal))
				.addGap(35, 35, 35)
				.addComponent(currentBox)
				.addGap(18, 18, 18)
				.addComponent(currentBin)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 42, Short.MAX_VALUE)
				.addComponent(logScrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 173, javax.swing.GroupLayout.PREFERRED_SIZE)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addComponent(newCmdButton)
				.addContainerGap())
		);

		pack();
	}// </editor-fold>//GEN-END:initComponents

	/**
	 * Opens the frame for new command
	 *
	 * @param evt click on "nouvelle commande" button
	 */
	private void newCmdButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_newCmdButtonActionPerformed

		newCmdFrame.setVisible(true);
	}//GEN-LAST:event_newCmdButtonActionPerformed
	// Variables declaration - do not modify//GEN-BEGIN:variables
	private javax.swing.JLabel currentBin;
	private javax.swing.JLabel currentBox;
	private javax.swing.JLabel currentPal;
	private javax.swing.JLabel descriptionLabel;
	private javax.swing.JScrollPane logScrollPane;
	private javax.swing.JTextArea logTextArea;
	private javax.swing.JProgressBar lotProgressBar;
	private javax.swing.JButton newCmdButton;
	// End of variables declaration//GEN-END:variables

	/**
	 * update date when receiving a log
	 *
	 * @param log
	 */
	@Override
	public void onReveiveLog(String log)
	{
		// if the log starts with STATE, it contains the current situation.
		if (log.substring(0, 5).equalsIgnoreCase("STATE"))
		{
			//update the data
			//the server has sent : STATE-NBA-NBB-NbBoitesProduite-NbPiecesRefusées
			this.nbCurrentBin = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			log = log.substring(0, log.lastIndexOf("-"));
			this.currentBin.setText("Nombre de pièces dans le rebut : " + nbCurrentBin);

			this.nbCurrentBox = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			log = log.substring(0, log.lastIndexOf("-"));
			this.currentBox.setText("Carton en cours de remplissage : n°" + nbCurrentBox);

			this.palBWarehouse = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			log = log.substring(0, log.lastIndexOf("-"));

			this.palAWarehouse = Integer.parseInt(log.substring(log.lastIndexOf("-") + 1));
			if (currentLot.equalsIgnoreCase("A"))
			{
				this.lotProgressBar.setValue(nbCurrentBox);
				this.currentPal.setText((nbCurrentBox / nbBoxPerPal) + "/" + nbPalA + " palettes");
			}
			else
			{
				this.lotProgressBar.setValue(nbCurrentBox);
				this.currentPal.setText((nbCurrentBox / nbBoxPerPal) + "/" + nbPalB + " palettes");
			}

			//updates the data of the newCmdFrame
			if (newCmdFrame != null)
			{
				newCmdFrame.setPalAWarehouse(palAWarehouse);
				newCmdFrame.setPalBWarehouse(palBWarehouse);
			}
		}
		else
		{
			//it is a log, we add it in the TextArea
			addLog(log);
			logTextArea.setCaretPosition(logTextArea.getDocument().getLength());
		}
	}
	ErrorPopup ep = new ErrorPopup();

	/**
	 * When receiving an error, checks what time of error it is
	 *
	 * @param error type of error
	 */
	@Override
	public void onReceiveError(ThreadLog.ERROR error)
	{
		String err = "";
		this.currentErrorState = true;

		switch (error)
		{
			case BOX:
				err = "Carton manquant.";
				break;
			case BOX_REFUSED:
				err = "Taux d'erreur trop élevé à la mise en carton.";
				break;
			case PALETTE:
				err = "Palette manquante.";
				break;
			case PALETTE_QUEUE:
				err = "File d'attente de la mise en palette surchargée.";
				break;
			case PRINT:
				err = "L'imprimante.";
				break;
			case EMERGENCY_STOP:
				err = "Le bouton d'arrêt d'urgence a été pressé.";
				break;
		}
		this.ep.setCommand(threadCmd);
		this.ep.setMgFrame(this);
		this.ep.getErrorNameLabel().setText(err);
		// WARNING /!\ These two following lines have to be in this order. If you ever put the second call before the first one
		// then when receiving an error at the very beginning of the logging, the ManagementFrame would not hide
		this.ep.setVisible(true);
		this.setVisible(false);
	}

	/**
	 * Sets current error state
	 *
	 * @param errorState if true, there is an error. If false, everything is ok
	 */
	public void setCurrentErrorState(boolean errorState)
	{
		this.currentErrorState = errorState;
	}
	GameOverPopup goPopup = null;

	/**
	 * Method after GameOver signal received in the log socket
	 */
	@Override
	public void onGameOver()
	{
		this.setVisible(false);
		this.newCmdFrame.setVisible(false);
		this.goPopup.setVisible(true);
	}
}
